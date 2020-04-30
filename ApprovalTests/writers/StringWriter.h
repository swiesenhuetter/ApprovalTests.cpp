#pragma once

#include <string>
#include <fstream>
#include <stdexcept>
#include <utility>
#include "ApprovalTests/core/ApprovalWriter.h"

namespace ApprovalTests
{
    class StringWriter : public ApprovalWriter
    {
    private:
        std::string s;
        std::string ext;

    public:
        explicit StringWriter(std::string contents,
                              std::string fileExtensionWithDot = ".txt")
            : s(std::move(contents)), ext(std::move(fileExtensionWithDot))
        {
        }

        std::string getFileExtensionWithDot() const override
        {
            return ext;
        }

        void write(std::string path) const override
        {
            std::ofstream out(path.c_str(), std::ofstream::out);
            if (!out)
            {
                throw std::runtime_error("Unable to write file: " + path);
            }
            this->Write(out);
            out.close();
        }

        void Write(std::ostream& out) const
        {
            out << s << "\n";
        }

        virtual void cleanUpReceived(std::string receivedPath) const override
        {
            remove(receivedPath.c_str());
        }
    };
}
