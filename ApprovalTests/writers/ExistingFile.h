#pragma once

#include <string>
#include <utility>
#include "ApprovalTests/core/ApprovalWriter.h"
#include "ApprovalTests/utilities/FileUtils.h"

namespace ApprovalTests
{
    class ExistingFile : public ApprovalWriter
    {
        std::string filePath;

    public:
        explicit ExistingFile(std::string filePath_) : filePath(std::move(filePath_))
        {
        }
        virtual std::string getFileExtensionWithDot() const override
        {
            return FileUtils::getExtensionWithDot(filePath);
        }
        virtual void write(std::string /*path*/) const override
        {
            // do nothing
        }
        virtual void cleanUpReceived(std::string /*receivedPath*/) const override
        {
            // do nothing
        }
    };
}
