#include <consumer.hpp>

Consumer::Consumer(const std::string &remote)
{
    this->remote = remote;
    this->watchlist.push_back("default");
}

void Consumer::watch(const std::string &t_id)
{
    this->watchlist.push_back(t_id);
}

Job Consumer::reserve_job()
{
    //*  /reserve
    //*  {
    //*      "t_ids": "default1,default2"
    //*  }

    std::string t_ids = "";
    for (const auto &el : this->watchlist)
        t_ids.append(el + ",");

    if (t_ids.length() > 0 && t_ids.back() == ',')
        t_ids.erase(t_ids.end() -1);

    cpr::Response r = cpr::Get(cpr::Url{this->remote + "/reserve"},
                               cpr::Parameters{{"t_ids", t_ids}});

    nlohmann::json response = nlohmann::json::parse(r.text);

    return Job(response["data"]["j_id"], response["data"]["j_d"]);
}

int Consumer::delete_job(const std::string &j_id)
{
    //*  /delete
    //*  {
    //*      "t_ids": "default1,default2",
    //*      "j_id": "id01"
    //*  }

    std::string t_ids = "";
    for (const auto &el: this->watchlist)
        t_ids.append(el + ",");

    if (t_ids.length() > 0 && t_ids.back() == ',')
        t_ids.erase(t_ids.end() - 1);

    cpr::Response r = cpr::Get(cpr::Url{this->remote + "/delete"},
                               cpr::Parameters{
                                   {"t_ids", t_ids},
                                   {"j_id", j_id}});

    nlohmann::json response = nlohmann::json::parse(r.text);

    if (response["status"] == "success")
        return 1;
    return 0;
}