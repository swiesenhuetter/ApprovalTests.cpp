<a id="top"></a>

# ApprovalTests.cpp User Guide

To get the most out of ApprovalTests, start with the  [Tutorial](/doc/Tutorial.md#top).
Once you're up and running, consider the following reference material. 

toc

## Preparation

### Introduction

* [Overview](/doc/Overview.md#top)
* [Approval Testing (the concept)](/doc/ApprovalTestingConcept.md#top)
* What is Approval Testing?
* Why Approval Tests?
* [The Path to Approval Testing](/doc/PathToApprovalTesting.md#top)
* [Glossary](/doc/Glossary.md#top)

### Setup

There are three different places you might be starting your setup from.

Here's how to set up from:

* [I have nothing](/doc/Setup.md#i-have-nothing)
* [I have code but no tests](/doc/Setup.md#i-have-code-but-no-tests)
* [I have tests and code and want to add Approval Tests](/doc/Setup.md#i-have-tests-and-code-and-want-to-add-approval-tests)

## Use

### Writing Tests

* [Tutorial](/doc/Tutorial.md#top)
* [Testing single objects](/doc/TestingSingleObjects.md#top)
* [Testing containers](/doc/TestingContainers.md#top)
* [Testing exceptions](/doc/TestingExceptions.md#top)
* [Testing combinations](/doc/TestingCombinations.md#top) - containers of containers (of containers...)
* [To String](/doc/ToString.md#top)
* Worked example of getting to 'make the thing; verify the thing' - 'do; verify'
* [Features](/doc/Features.md#top) - recent additions

### Test Frameworks

include: include_using_test_frameworks_list
* [Supporting a new test framework](/doc/SupportingNewTestFramework.md#top)

### Customising behaviour

* [Reporters](/doc/Reporters.md#top)
* [Custom Comparators](/doc/CustomComparators.md#top)
* [Writers](/doc/Writers.md#top)
* [Namers](/doc/Namers.md#top)
* [Configuration](/doc/Configuration.md#top)
* [All Customizations of Approval Tests](/doc/AllCustomizations.md#top)

### Common Challenges

* Unstable output, e.g. with Dates and Times
* Non-deterministic code
* [Multiple output files per test](/doc/MultipleOutputFilesPerTest.md#top)
* Testing images
* Embedded development

### Common Scenarios

* Non-graphical environments
* [Build Machines and Continuous Integration servers](/doc/BuildMachinesAndCI.md#top)

## How-to Guides

* [How to Test the Contents of a Container](/doc/how_tos/TestContainerContents.md#top).
* [How to Test a Variety of Values for One Input](/doc/how_tos/TestAVarietyOfValues.md#top).
* [How to Use A Custom Reporter](/doc/how_tos/UseACustomReporter.md#top)
* [How to Submit a New Reporter to ApprovalTests](/doc/how_tos/SubmitANewReporterToApprovalTests.md#top).

## Miscellaneous

### Build Systems

* [CMake Integration](/doc/CMakeIntegration.md#top)
* [Conan Integration](/doc/ConanIntegration.md#top)

### Extras

* [Frequently Asked Questions](/doc/FAQ.md#top)
* [Utilities](/doc/Utilities.md#top)
* [Videos](/doc/Videos.md#top)
* [Troubleshooting](/doc/Troubleshooting.md#top)
    * [Troubleshooting Misconfigured Build](/doc/TroubleshootingMisconfiguredBuild.md#top)
    * [Troubleshooting Misconfigured Main](/doc/TroubleshootingMisconfiguredMain.md#top)
* 4 benefits of testing
    * Spec
    * Feedback
    * Regression
    * Granularity

### Advanced Topics

* [Contributing to ApprovalTests.cpp](/doc/Contributing.md#top)

### Suggested Examples
* [ApprovalTests](https://github.com/approvals/ApprovalTests.cpp/blob/master/tests/DocTest_Tests/ApprovalsTests.cpp)

