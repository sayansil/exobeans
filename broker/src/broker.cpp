#include <broker.hpp>

Broker::Broker()
{
    this->create_tube("default");
}

void Broker::create_tube(const std::string &t_id)
{
    // Check if Tube id already exists
    if (this->pipeline.count(t_id))
    {
        Tube::Tube new_tube(t_id);
        this->pipeline[t_id] = new_tube;
    }
}

void Broker::add_job(const std::string &t_id, Job::Job job)
{
    create_tube(t_id);

    int status = this->pipeline[t_id].push_job(job);
}

Job::Job Broker::reserveJob(const std::vector<std::string> &t_ids)
{
    int n = t_ids.size();

    for (int i = 0;; i = (i + 1) % n)
    {
        if (this->pipeline[t_ids[i]].can_reserve_job())
        {
            return this->pipeline[t_ids[i]].reserve_job();
        }
    }
}

bool Broker::deleteJob(const std::vector<std::string> &t_ids, const std::string &j_id)
{
    int n = t_ids.size();

    for (int i = 0; i < n; ++i)
    {
        if (pipeline[t_ids[i]].can_delete_job(j_id))
        {
            this->pipeline[t_ids[i]].delete_job();
            return true;
        }
    }

    return false;
}