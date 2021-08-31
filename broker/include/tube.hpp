#ifndef TUBE_HPP
#define TUBE_HPP

#include <queue>
#include <vector>
#include <job.hpp>

class Compare // Job Priority (for priority queue)
{
public:
    bool operator()(Job::Job a, Job::Job b)
    {
        return a.priority < b.priority;
    }
};

class Tube
{
public:
    // Tube Id
    std::string id;

    // Priority Queue for Tube
    std::priority_queue<Job::Job, std::vector<Job::Job>, Compare> q;

    // Constructor
    Tube() = default;
    Tube(const std::string &id);

    // Destructor
    ~Tube();

    // Queue Helper methods
    int push_job(Job::Job job);

    Job::Job peek_top_job();

    bool can_reserve_job();
    Job::Job reserve_job();

    bool can_delete_job(const std::string &id);
    void delete_job();

    // Kill Tube
    void kill();
};

#endif // TUBE_HPP