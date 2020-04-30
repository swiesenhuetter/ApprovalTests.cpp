#pragma once

#include "ApprovalTests/core/Reporter.h"
#include <memory>
#include <vector>

namespace ApprovalTests
{
    class FirstWorkingReporter : public Reporter
    {
    private:
        std::vector<std::shared_ptr<Reporter>> reporters;

    public:
        // Note that FirstWorkingReporter takes ownership of the given Reporter objects
        explicit FirstWorkingReporter(const std::vector<Reporter*>& theReporters)
        {
            for (auto r : theReporters)
            {
                reporters.push_back(std::shared_ptr<Reporter>(r));
            }
        }

        explicit FirstWorkingReporter(
            const std::vector<std::shared_ptr<Reporter>>& reporters_)
        {
            this->reporters = reporters_;
        }

        bool report(std::string received, std::string approved) const override
        {
            for (auto& r : reporters)
            {
                if (r->report(received, approved))
                {
                    return true;
                }
            }
            return false;
        }
    };
}
