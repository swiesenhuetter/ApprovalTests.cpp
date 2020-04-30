#pragma once

#include "ApprovalTests/core/Reporter.h"
#include "ApprovalTests/utilities/SystemUtils.h"

#include <string>

namespace ApprovalTests
{
    class ClipboardReporter : public Reporter
    {
    public:
        static std::string getCommandLineFor(const std::string& received,
                                             const std::string& approved,
                                             bool isWindows)
        {
            if (isWindows)
            {
                return std::string("move /Y ") + "\"" + received + "\" \"" + approved +
                       "\"";
            }
            else
            {
                return std::string("mv ") + "\"" + received + "\" \"" + approved + "\"";
            }
        }

        virtual bool report(std::string received, std::string approved) const override
        {
            copyToClipboard(
                getCommandLineFor(received, approved, SystemUtils::isWindowsOs()));
            return true;
        }

        static void copyToClipboard(const std::string& newClipboard)
        {
            /*
         This will probably not work on Linux.

         From https://stackoverflow.com/a/750466/104370
         In case of X, yes, there's xclip (and others). xclip -selection c will send data to the clipboard that
         works with Ctrl-C, Ctrl-V in most applications.

         If you're trying to talk to the Mac OS X clipboard, there's pbcopy.

         If you're in Linux terminal mode (no X) then maybe you need to look into gpm.

         There's also GNU screen which has a clipboard. To put stuff in there, look at the screen command "readreg".

         Under Windows/cygwin, use /dev/clipboard or clip for newer versions of Windows (at least Windows 10).
         */

            std::string clipboardCommand;
            if (SystemUtils::isWindowsOs())
            {
                clipboardCommand = "clip";
            }
            else if (SystemUtils::isMacOs())
            {
                clipboardCommand = "pbcopy";
            }
            else
            {
                clipboardCommand = "pbclip";
            }
            auto cmd = std::string("echo ") + newClipboard + " | " + clipboardCommand;
            SystemUtils::runSystemCommandOrThrow(cmd);
        }
    };
}
