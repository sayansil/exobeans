#ifndef JOB_HPP
#define JOB_HPP

#include <string>

class Job
{
    public:
        // Job priority
        int priority;

        // Job ID
        std::string id;

        // Job Description
        std::string desc;

        // Constructor
        Job() = default;
        Job(
            const std::string &id,
            const std::string &desc,
            const int &priority = 1);

        // Destructor
        ~Job();

        // Kill Job
        void kill();
};

#endif // JOB_HPP