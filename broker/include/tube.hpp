#ifndef TUBE_HPP
#define TUBE_HPP

#include <queue>
#include <vector>
#include <job.hpp>

class Compare // Job Priority (for priority queue)
{
public:
    bool operator()(Job a, Job b)
    {
        return a.priority < b.priority;
    }
};

class Tube
{
public:
    // Tube Id
    std::string id;

    // Reserved flag
    bool reserved = false;

    // Priority Queue for Tube
    std::priority_queue<Job, std::vector<Job>, Compare> q;

    // Constructor
    Tube() = default;
    Tube(const std::string &id);

    // Destructor
    ~Tube();

    // Queue Helper methods
    int push_job(Job job);

    Job peek_top_job();

    bool can_reserve_job();
    Job reserve_job();

    bool can_delete_job(const std::string &id);
    void delete_job();

    // Kill Tube
    void kill();
};

#endif // TUBE_HPP