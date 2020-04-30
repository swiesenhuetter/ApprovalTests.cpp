#pragma once

#include "ApprovalTests/utilities/WinMinGWUtils.h"
#ifdef _WIN32
// ReSharper disable once CppUnusedIncludeDirective
#include <io.h>
#include <direct.h>
#else
// ReSharper disable once CppUnusedIncludeDirective
#include <unistd.h>
#endif

#include "ApprovalTests/utilities/FileUtils.h"
#include "ApprovalTests/utilities/StringUtils.h"
#include "ApprovalTests/utilities/Macros.h"

#include <stdexcept>

namespace ApprovalTests
{
    class SystemUtils
    {
    public:
        static bool isWindowsOs()
        {
#ifdef _WIN32
            return true;
#else
            return false;
#endif
        }

        static bool isCygwin()
        {
#ifdef __CYGWIN__
            return true;
#else
            return false;
#endif
        }

        static bool isMacOs()
        {
#ifdef __APPLE__
            return true;
#else
            return false;
#endif
        }

        static std::string getDirectorySeparator()
        {
            return isWindowsOs() ? "\\" : "/";
        }

        // Properly cases the filename, but not the directories, on Windows.
        static std::string checkFilenameCase(const std::string& fullPath)
        {
            if (!isWindowsOs() || !FileUtils::fileExists(fullPath))
            {
                return fullPath;
            }
#ifdef _WIN32

            _finddata_t findFileData;
            auto hFind = _findfirst(fullPath.c_str(), &findFileData);

            if (hFind != -1)
            {
                const std::string fixedFilename = findFileData.name;
                const std::string fixedPath = StringUtils::replaceAll(
                    fullPath, StringUtils::toLower(fixedFilename), fixedFilename);
                _findclose(hFind);
                return fixedPath;
            }

#endif
            return fullPath;
        }

        static std::string safeGetEnvForWindows(char const* name)
        {
            APPROVAL_TESTS_UNUSED(name);
#ifdef _WIN32
            // We use getenv_s on Windows, as use of getenv there gives:
            //      warning C4996: 'getenv': This function or variable may be unsafe. Consider using _dupenv_s instead.
            //      To disable deprecation, use _CRT_SECURE_NO_WARNINGS. See online help for details.

            size_t size;
            getenv_s(&size, nullptr, 0, name);

            if (size != 0)
            {
                std::string result;
                result.resize(size);
                getenv_s(&size, &*result.begin(), size, name);
                result.pop_back();
                return result;
            }
#endif
            return std::string();
        }

        static std::string safeGetEnvForNonWindows(char const* name)
        {
            APPROVAL_TESTS_UNUSED(name);
            char* p = nullptr;
#ifndef _WIN32
            p = getenv(name);
#endif
            return (p != nullptr) ? p : std::string();
        }

        //! Return the value of the environment variable, or an empty string if the variable is not set.
        static std::string safeGetEnv(char const* name)
        {
            return isWindowsOs() ? safeGetEnvForWindows(name)
                                 : safeGetEnvForNonWindows(name);
        }

        static std::string getMachineName()
        {
            auto name = safeGetEnv("COMPUTERNAME");
            if (!name.empty())
            {
                return name;
            }

            name = safeGetEnv("HOSTNAME");
            if (!name.empty())
            {
                return name;
            }

            return "Unknown Computer";
        }

        static void makeDirectoryForWindows(const std::string& directory)
        {
            APPROVAL_TESTS_UNUSED(directory);
#ifdef _WIN32
            int nError = _mkdir(directory.c_str());
            if (nError != 0)
            {
                std::string helpMessage =
                    std::string("Unable to create directory: ") + directory;
                throw std::runtime_error(helpMessage);
            }
#endif
        }

        static void makeDirectoryForNonWindows(const std::string& directory)
        {
            APPROVAL_TESTS_UNUSED(directory);
#ifndef _WIN32
            mode_t nMode = 0733; // UNIX style permissions
            int nError = mkdir(directory.c_str(), nMode);
            if (nError != 0)
            {
                std::string helpMessage =
                    std::string("Unable to create directory: ") + directory;
                throw std::runtime_error(helpMessage);
            }
#endif
        }

        static void makeDirectory(const std::string& directory)
        {
            makeDirectoryForWindows(directory);
            makeDirectoryForNonWindows(directory);
        }

        static void ensureDirectoryExists(const std::string& fullFilePath)
        {
            if (!FileUtils::fileExists(fullFilePath))
            {
                makeDirectory(fullFilePath);
            }
        }

        static void runSystemCommandOrThrow(const std::string& command)
        {
            int exitCode = system(command.c_str());

            if (exitCode != 0)
            {
                throw std::runtime_error(command + ": failed with exit code " +
                                         std::to_string(exitCode));
            }
        }
    };
}
