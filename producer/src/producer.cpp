#include <producer.hpp>

Producer::Producer(const std::string &remote)
{
    this->remote = remote;
    this->current_tube = "default";
}

void Producer::use_tube(const std::string &t_id)
{
    this->current_tube = t_id;
}

int Producer::push_job(const Job &job)
{
    cpr::Get(cpr::Url{this->remote + "/create"},
             cpr::Parameters{{"t_id", this->current_tube}});

    cpr::Response r = cpr::Get(cpr::Url{this->remote + "/put"},
                                cpr::Parameters{
                                    {"t_id", this->current_tube},
                                    {"j_id", job.id},
                                    {"j_d", job.desc},
                                    {"j_p", std::to_string(job.priority)}});

    nlohmann::json response = nlohmann::json::parse(r.text);

    if (response["status"] == "success")
        return 1;
    return 0;
}