<!--
GENERATED FILE - DO NOT EDIT
This file was generated by [MarkdownSnippets](https://github.com/SimonCropp/MarkdownSnippets).
Source File: /doc/how_tos/mdsource/SubmitANewReporterToApprovalTests.source.md
To change this file edit the source file and then execute ./run_markdown_templates.sh.
-->

<a id="top"></a>

# How to Submit a New Reporter to ApprovalTests

<!-- toc -->
## Contents

  * [Adding a new Mac reporter](#adding-a-new-mac-reporter)
    * [Edit ApprovalTests/reporters/DiffPrograms.h](#edit-approvaltestsreportersdiffprogramsh)
    * [Edit ApprovalTests/reporters/MacReporters.h](#edit-approvaltestsreportersmacreportersh)
    * [Edit tests/DocTest_Tests/reporters/CommandLineReporterTests.cpp](#edit-testsdoctest_testsreporterscommandlinereportertestscpp)
  * [Adding a new Windows reporter](#adding-a-new-windows-reporter)
  * [Adding a new Linux reporter](#adding-a-new-linux-reporter)<!-- endtoc -->

This guide is for figuring out how to make a more robust custom reporter, that you might want to submit back to us as a Pull Request.

For creating the ability to use a custom reporter that works on your machine, see [How To Use A Custom Reporter](/doc/how_tos/UseACustomReporter.md#top)

## Adding a new Mac reporter

By way of an example, for supporting a new Reporter on macOS, the steps are:

### Edit [ApprovalTests/reporters/DiffPrograms.h](https://github.com/approvals/ApprovalTests.cpp/blob/master/ApprovalTests/reporters/DiffPrograms.h)

* Add a new `APPROVAL_TESTS_MACROS_ENTRY` value to the `Mac` namespace.
* If you are adding a tool that is already supported on an existing platform, please try to be consistent with naming.

<!-- snippet: add_reporter_macro -->
<a id='snippet-add_reporter_macro'/></a>
```h
APPROVAL_TESTS_MACROS_ENTRY(
    ARAXIS_MERGE,
    DiffInfo("/Applications/Araxis Merge.app/Contents/Utilities/compare",
             Type::TEXT_AND_IMAGE))
```
<sup><a href='/ApprovalTests/reporters/DiffPrograms.h#L26-L31' title='File snippet `add_reporter_macro` was extracted from'>snippet source</a> | <a href='#snippet-add_reporter_macro' title='Navigate to start of snippet `add_reporter_macro`'>anchor</a></sup>
<!-- endsnippet -->

### Edit [ApprovalTests/reporters/MacReporters.h](https://github.com/approvals/ApprovalTests.cpp/blob/master/ApprovalTests/reporters/MacReporters.h)

* In the most common case, you will add a new implementation of `GenericDiffReporter`, that uses the `APPROVAL_TESTS_MACROS_ENTRY` you added in the first step.

<!-- snippet: add_reporter_class -->
<a id='snippet-add_reporter_class'/></a>
```h
class AraxisMergeReporter : public GenericDiffReporter
{
public:
    AraxisMergeReporter() : GenericDiffReporter(DiffPrograms::Mac::ARAXIS_MERGE())
    {
    }
};
```
<sup><a href='/ApprovalTests/reporters/MacReporters.h#L19-L27' title='File snippet `add_reporter_class` was extracted from'>snippet source</a> | <a href='#snippet-add_reporter_class' title='Navigate to start of snippet `add_reporter_class`'>anchor</a></sup>
<!-- endsnippet -->

* Scroll to the end of this file, and add an instance of the new reporter class to the `MacDiffReporter`
    * The reporters are searched in order, so more commonly-used or highly-featured ones should go nearer the start.
    * Paid-for ones should go before free ones.

<!-- snippet: mac_diff_reporters -->
<a id='snippet-mac_diff_reporters'/></a>
```h
new AraxisMergeReporter(),
new BeyondCompareReporter(),
new DiffMergeReporter(),
new KaleidoscopeReporter(),
new P4MergeReporter(),
new SublimeMergeReporter(),
new KDiff3Reporter(),
new TkDiffReporter(),
new VisualStudioCodeReporter()
```
<sup><a href='/ApprovalTests/reporters/MacReporters.h#L94-L104' title='File snippet `mac_diff_reporters` was extracted from'>snippet source</a> | <a href='#snippet-mac_diff_reporters' title='Navigate to start of snippet `mac_diff_reporters`'>anchor</a></sup>
<!-- endsnippet -->

### Edit [tests/DocTest_Tests/reporters/CommandLineReporterTests.cpp](https://github.com/approvals/ApprovalTests.cpp/blob/master/tests/DocTest_Tests/reporters/CommandLineReporterTests.cpp)

* Add an instance of the new Reporter class

<!-- snippet: add_reporter_command_test -->
<a id='snippet-add_reporter_command_test'/></a>
```cpp
// Mac
std::make_shared<Mac::AraxisMergeReporter>(),
std::make_shared<Mac::BeyondCompareReporter>(),
std::make_shared<Mac::DiffMergeReporter>(),
std::make_shared<Mac::KaleidoscopeReporter>(),
std::make_shared<Mac::P4MergeReporter>(),
std::make_shared<Mac::SublimeMergeReporter>(),
std::make_shared<Mac::KDiff3Reporter>(),
std::make_shared<Mac::TkDiffReporter>(),
std::make_shared<Mac::VisualStudioCodeReporter>(),
```
<sup><a href='/tests/DocTest_Tests/reporters/CommandLineReporterTests.cpp#L26-L37' title='File snippet `add_reporter_command_test` was extracted from'>snippet source</a> | <a href='#snippet-add_reporter_command_test' title='Navigate to start of snippet `add_reporter_command_test`'>anchor</a></sup>
<!-- endsnippet -->

* Run this test, review and accept the changes.

## Adding a new Windows reporter

The steps are the same as above, except that in the second step, you will edit [ApprovalTests/reporters/WindowsReporters.h](https://github.com/approvals/ApprovalTests.cpp/blob/master/ApprovalTests/reporters/WindowsReporters.h).

## Adding a new Linux reporter

The steps are the same as above, except that in the second step, you will edit [ApprovalTests/reporters/LinuxReporters.h](https://github.com/approvals/ApprovalTests.cpp/blob/master/ApprovalTests/reporters/LinuxReporters.h).


---

[Back to User Guide](/doc/README.md#top)
