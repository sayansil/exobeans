#ifndef BROKER_HPP
#define BROKER_HPP

#include <tube.hpp>
#include <map>

class Broker
{
public:
    // Map of all tubes
    std::map<std::string, Tube> pipeline;

    // Constructor
    Broker();

    // Helper actions
    void create_tube(const std::string &t_id); // used by: use, watch

    // Producer actions
    void add_job(const std::string &t_id, Job job); // used by: put,

    // Worker actions
    Job reserveJob(const std::vector<std::string> &t_ids); // used by: reserve
    bool deleteJob(const std::vector<std::string> &t_ids, const std::string &j_id); // used by: delete
};

#endif // BROKER_HPP