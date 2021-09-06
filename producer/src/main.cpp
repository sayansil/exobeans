#include <producer.hpp>
#include <job.hpp>

int main()
{
    Producer producer;

    Job job("shanti_id", "shanti chai");

    producer.use_tube("newtube");
    producer.push_job(job);

    return 0;
}