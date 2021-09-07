#include <producer.hpp>
#include <job.hpp>

int main()
{
    Producer producer;

    Job job("random_job_id", "This is how to do a random job");

    producer.use_tube("newtube");
    producer.push_job(job);

    return 0;
}