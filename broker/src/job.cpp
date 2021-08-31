#include <job.hpp>

Job::Job(const std::string &id, const std::string &desc, const int &priority)
{
    this->id = id;
    this->desc = desc;
    this->priority = priority;
}

Job::~Job()
{
    kill();
}

void kill()
{
}