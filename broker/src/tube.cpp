#include <tube.hpp>

Tube::Tube(const std::string &id)
{
    this->id = id;
}

Tube::~Tube()
{
    kill();
}

int Tube::push_job(Job::Job job)
{
    this->q.push(job);
    return 1;
}

Job::Job Tube::peek_top_job()
{
    return this->q.top();
}

bool Tube::can_reserve_job()
{
    if (this->q.empty())
        return false;

    Job::Job front = this->q.top();
    return !front.status;
}

Job::Job Tube::reserve_job()
{
    Job::Job front = this->q.top();

    //TODO mark front.status as true

    return front;
}

bool Tube::can_delete_job(const std::string &id)
{
    if (this->q.empty())
        return false;

    Job::Job front = this->q.top();
    if (!front.status)
        return false;

    return front.id == id;
}

void Tube::delete_job()
{
    this->q.pop();
}

void kill()
{
}