#pragma once

#include "ApprovalTests/core/Reporter.h"
#include "ApprovalTests/utilities/FileUtilsSystemSpecific.h"

#include <iostream>

namespace ApprovalTests
{
    class AutoApproveReporter : public Reporter
    {
    public:
        bool report(std::string received, std::string approved) const override
        {
            std::cout << "file " << approved
                      << " automatically approved - next run should succeed\n";
            FileUtilsSystemSpecific::copyFile(received, approved);
            return true;
        }
    };
}
