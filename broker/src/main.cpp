#include <broker.hpp>
#include <helper.hpp>
#include <iostream>
#include <string_view>
#include <App.h>
#include <memory>
#include <mutex>
#include <thread>
#include <algorithm>
#include <nlohmann/json.hpp>

std::unique_ptr<Broker> broker;
std::mutex m;

void run_app()
{
    broker = std::make_unique<Broker>();

    uWS::SSLApp()
        .get("/", [](auto *res, auto *req)
             {
                 nlohmann::json response = {
                     {"status", ""},
                     {"log", ""},
                     {"data", ""}};

                 response["status"] = "success";
                 response["log"] = "broker ok";
                 res->writeHeader("Content-Type", "application/json; charset=utf-8")
                     ->end(response.dump());
             })

        .get("/create", [](auto *res, auto *req)
             //*  SYNTAX :
             //*  {
             //*      "t_id": "default"
             //*  }
             {
                 nlohmann::json response = {
                     {"status", ""},
                     {"log", ""},
                     {"data", ""}};

                 auto query_map = helper::fetch_params(req->getQuery());

                 m.lock();
                 if (query_map.count("t_id") && query_map["t_id"].length() > 0)
                 {
                     broker->create_tube(query_map["t_id"]);
                     response["status"] = "success";
                 }
                 else
                 {
                     response["status"] = "failure";
                     response["log"] = "No tube id provided";
                 }

                 res->writeHeader("Content-Type", "application/json; charset=utf-8")
                     ->end(response.dump());
                 m.unlock();
             })

        .get("/put", [](auto *res, auto *req)
             //*  SYNTAX :
             //*  {
             //*      "t_id": "default",
             //*      "j_id": "id01",
             //*      "j_d": "Description",
             //*      "j_p": "1"
             //*  }
             {
                 nlohmann::json response = {
                     {"status", ""},
                     {"log", ""},
                     {"data", ""}};

                 auto query_map = helper::fetch_params(req->getQuery());

                 if (query_map.count("t_id") && query_map.count("j_id") && query_map.count("j_d") && query_map["t_id"].length() > 0 && query_map["j_id"].length() > 0 && query_map["j_d"].length() > 0)
                 {
                     m.lock();
                     try
                     {
                         int priority = 1;
                         if (query_map.count("j_p"))
                         {
                             priority = std::stoi(query_map["j_p"]);
                         }

                         Job job(query_map["j_id"], query_map["j_d"], priority);

                         broker->add_job(query_map["t_id"], job);

                         response["status"] = "success";
                         response["log"] = "Job added";
                     }
                     catch (...)
                     {
                         response["status"] = "failure";
                         response["log"] = "Job could not be created";
                     }
                     m.unlock();
                 }
                 else
                 {
                     response["status"] = "failure";
                     response["log"] = "No job details provided";
                 }

                 res->writeHeader("Content-Type", "application/json; charset=utf-8")
                     ->end(response.dump());
             })

        .get("/reserve", [](auto *res, auto *req)
             //*  SYNTAX :
             //*  {
             //*      "t_ids": "default1,default2"
             //*  }
             {
                 nlohmann::json response = {
                     {"status", ""},
                     {"log", ""},
                     {"data", ""}};

                 auto query_map = helper::fetch_params(req->getQuery());

                 if (query_map.count("t_ids") && query_map["t_ids"].length() > 0)
                 {
                     m.lock();
                     try
                     {
                         std::vector<std::string> tubes = helper::tokenize(query_map["t_ids"], ",");

                         Job job = broker->reserveJob(tubes);

                         response["status"] = "success";
                         response["log"] = "Job reserved";
                         response["data"] = {
                             {"j_id", job.id},
                             {"j_d", job.desc}};
                     }
                     catch (...)
                     {
                         response["status"] = "failure";
                         response["log"] = "Job could not be reserved";
                     }
                     m.unlock();
                 }
                 else
                 {
                     response["status"] = "failure";
                     response["log"] = "Not watching any tube";
                 }

                 res->writeHeader("Content-Type", "application/json; charset=utf-8")
                     ->end(response.dump());
             })

        .get("/delete", [](auto *res, auto *req)
             //*  SYNTAX :
             //*  {
             //*      "t_ids": "default1,default2",
             //*      "j_id": "id01"
             //*  }
             {
                 nlohmann::json response = {
                     {"status", ""},
                     {"log", ""},
                     {"data", ""}};

                 auto query_map = helper::fetch_params(req->getQuery());

                 if (query_map.count("t_ids") && query_map["t_ids"].length() > 0 && query_map.count("j_id") && query_map["j_id"].length() > 0)
                 {
                     m.lock();
                     try
                     {
                         std::vector<std::string> tubes = helper::tokenize(query_map["t_ids"], ",");

                         if (broker->deleteJob(tubes, query_map["j_id"]))
                         {
                             response["status"] = "success";
                             response["log"] = "Job deleted";
                         }
                         else
                         {
                             response["status"] = "failure";
                             response["log"] = "Job could not be found";
                         }
                     }
                     catch (...)
                     {
                         response["status"] = "failure";
                         response["log"] = "Job could not be deleted";
                     }
                     m.unlock();
                 }
                 else
                 {
                     response["status"] = "failure";
                     response["log"] = "Not watching any tube / Invalid Job id";
                 }

                 res->writeHeader("Content-Type", "application/json; charset=utf-8")
                     ->end(response.dump());
             })

        .listen(15000, [](auto *listen_socket)
                {
                    if (listen_socket)
                    {
                        std::cout << "Listening on port " << 15000 << std::endl;
                    }
                })
        .run();

    std::cout << "Failed to listen on port 15000" << std::endl;
}

int main(int argc, char **argv)
{
    std::vector<std::thread *> threads(std::thread::hardware_concurrency());
    std::transform(threads.begin(), threads.end(), threads.begin(), [](std::thread *t)
                   { return new std::thread(&run_app); });
    for (auto &i : threads)
        i->join();
}