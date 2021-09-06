#include <consumer.hpp>
#include <job.hpp>
#include <iostream>

int main()
{
    Consumer consumer;

    consumer.watch("newtube");
    Job job = consumer.reserve_job();

    std::cout << job.desc << "\n";

    consumer.delete_job(job.id);

    return 0;
}