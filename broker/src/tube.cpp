#include <tube.hpp>

Tube::Tube(const std::string &id)
{
    this->id = id;
}

Tube::~Tube()
{
    kill();
}

int Tube::push_job(Job job)
{
    this->q.push(job);
    return 1;
}

Job Tube::peek_top_job()
{
    return this->q.top();
}

bool Tube::can_reserve_job()
{
    if (this->q.empty() || this->reserved)
        return false;

    return true;
}

Job Tube::reserve_job()
{
    const Job &front = this->q.top();
    this->reserved = true;

    return front;
}

bool Tube::can_delete_job(const std::string &id)
{
    if (this->q.empty() || !this->reserved)
        return false;

    const Job &front = this->q.top();

    return front.id == id;
}

void Tube::delete_job()
{
    this->q.pop();
    this->reserved = false;
}

void Tube::kill()
{
}