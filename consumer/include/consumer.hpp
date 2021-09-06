#ifndef CONSUMER_HPP
#define CONSUMER_HPP

#include <string>
#include <vector>
#include <job.hpp>
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>

class Consumer
{
public:
    std::vector<std::string> watchlist;
    std::string remote;

    Consumer(const std::string &remote = "http://localhost:15000");

    void watch(const std::string &t_id);

    Job reserve_job();
    int delete_job(const std::string &j_id);
};

#endif // CONSUMER_HPP