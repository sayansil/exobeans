#ifndef PRODUCER_HPP
#define PRODUCER_HPP

#include <string>
#include <job.hpp>
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>

class Producer
{
public:

    // The tube where jobs will be pushed
    std::string current_tube;
    std::string remote;

    Producer(const std::string &remote = "http://localhost:15000");

    void use_tube(const std::string &t_id);
    int push_job(const Job &job);
};

#endif // PRODUCER_HPP