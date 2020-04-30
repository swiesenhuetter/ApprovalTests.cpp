#pragma once

#include <string>
#include <functional>
#include <exception>

#include "ApprovalTests/ApprovalTestsVersion.h"
#include "ApprovalTests/core/FileApprover.h"
#include "reporters/DefaultReporter.h"
#include "reporters/DefaultReporterDisposer.h"
#include "ApprovalTests/core/Reporter.h"
#include "namers/ApprovalTestNamer.h"
#include "writers/ExistingFile.h"
#include "namers/ExistingFileNamer.h"
#include "namers/SubdirectoryDisposer.h"
#include "namers/DefaultNamerDisposer.h"
#include "scrubbers/Scrubbers.h"

namespace ApprovalTests
{

    class Approvals
    {
    private:
        Approvals() = default;

        ~Approvals() = default;

    public:
        static std::shared_ptr<ApprovalNamer> getDefaultNamer()
        {
            return DefaultNamerFactory::getDefaultNamer()();
        }

        static void verify(std::string contents,
                           const Reporter& reporter = DefaultReporter())
        {
            verifyScrubbed(contents, Scrubbers::doNothing, reporter);
        }

        static void verifyScrubbed(std::string contents,
                                   Scrubber scrubber,
                                   const Reporter& reporter = DefaultReporter())
        {
            verifyWithExtension(scrubber(contents), ".txt", reporter);
        }

        static void verifyWithExtension(std::string contents,
                                        const std::string& fileExtensionWithDot,
                                        const Reporter& reporter = DefaultReporter())
        {
            StringWriter writer(contents, fileExtensionWithDot);
            FileApprover::verify(*getDefaultNamer(), writer, reporter);
        }

        static void verify(const ApprovalWriter& writer,
                           const Reporter& reporter = DefaultReporter())
        {
            FileApprover::verify(*getDefaultNamer(), writer, reporter);
        }

        template <typename T>
        using IsNotDerivedFromWriter =
            typename std::enable_if<!std::is_base_of<ApprovalWriter, T>::value,
                                    int>::type;

        template <typename T, typename = IsNotDerivedFromWriter<T>>
        static void verify(const T& contents,
                           const Reporter& reporter = DefaultReporter())
        {
            verify(StringUtils::toString(contents), reporter);
        }

        template <typename T, typename = IsNotDerivedFromWriter<T>>
        static void verifyWithExtension(const T& contents,
                                        const std::string& fileExtensionWithDot,
                                        const Reporter& reporter = DefaultReporter())
        {
            verifyWithExtension(
                StringUtils::toString(contents), fileExtensionWithDot, reporter);
        }

        template <typename T,
                  typename Function,
                  typename = Detail::EnableIfNotDerivedFromReporter<Function>>
        static void verify(const T& contents,
                           Function converter,
                           const Reporter& reporter = DefaultReporter())
        {
            std::stringstream s;
            converter(contents, s);
            verify(s.str(), reporter);
        }

        template <typename T,
                  typename Function,
                  typename = Detail::EnableIfNotDerivedFromReporter<Function>>
        static void verifyWithExtension(const T& contents,
                                        Function converter,
                                        const std::string& fileExtensionWithDot,
                                        const Reporter& reporter = DefaultReporter())
        {
            std::stringstream s;
            converter(contents, s);
            verifyWithExtension(s.str(), fileExtensionWithDot, reporter);
        }

        static void verifyExceptionMessage(std::function<void(void)> functionThatThrows,
                                           const Reporter& reporter = DefaultReporter())
        {
            std::string message = "*** no exception thrown ***";
            try
            {
                functionThatThrows();
            }
            catch (const std::exception& e)
            {
                message = e.what();
            }
            verify(message, reporter);
        }

        template <typename Iterator>
        static void verifyAll(
            std::string header,
            const Iterator& start,
            const Iterator& finish,
            std::function<void(typename Iterator::value_type, std::ostream&)> converter,
            const Reporter& reporter = DefaultReporter())
        {
            std::stringstream s;
            if (!header.empty())
            {
                s << header << "\n\n\n";
            }
            for (auto it = start; it != finish; ++it)
            {
                converter(*it, s);
                s << '\n';
            }
            verify(s.str(), reporter);
        }

        template <typename Container>
        static void verifyAll(
            std::string header,
            const Container& list,
            std::function<void(typename Container::value_type, std::ostream&)> converter,
            const Reporter& reporter = DefaultReporter())
        {
            verifyAll<typename Container::const_iterator>(
                header, list.begin(), list.end(), converter, reporter);
        }

        template <typename T>
        static void verifyAll(std::string header,
                              const std::vector<T>& list,
                              const Reporter& reporter = DefaultReporter())
        {
            int i = 0;
            verifyAll<std::vector<T>>(
                header,
                list,
                [&](T e, std::ostream& s) { s << "[" << i++ << "] = " << e; },
                reporter);
        }

        template <typename T>
        static void verifyAll(const std::vector<T>& list,
                              const Reporter& reporter = DefaultReporter())
        {
            verifyAll<T>("", list, reporter);
        }

        static void verifyExistingFile(const std::string filePath,
                                       const Reporter& reporter = DefaultReporter())
        {
            ExistingFile writer(filePath);
            ExistingFileNamer namer(filePath);
            FileApprover::verify(namer, writer, reporter);
        }

        static SubdirectoryDisposer
        useApprovalsSubdirectory(std::string subdirectory = "approval_tests")
        {
            return SubdirectoryDisposer(subdirectory);
        }

        static DefaultReporterDisposer
        useAsDefaultReporter(const std::shared_ptr<Reporter>& reporter)
        {
            return DefaultReporterDisposer(reporter);
        }

        static FrontLoadedReporterDisposer
        useAsFrontLoadedReporter(const std::shared_ptr<Reporter>& reporter)
        {
            return FrontLoadedReporterDisposer(reporter);
        }

        static DefaultNamerDisposer useAsDefaultNamer(NamerCreator namerCreator)
        {
            return DefaultNamerDisposer(namerCreator);
        }
    };
}
