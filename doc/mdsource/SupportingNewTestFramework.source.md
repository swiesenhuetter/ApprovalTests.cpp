<a id="top"></a>

# Supporting a new test framework

toc


## Introduction

ApprovalTests.cpp is designed to work with multiple C++ test frameworks.

If your test framework is not already supported, this section offers help to add that support. 

## Test Framework Requirements

ApprovalTests.cpp can be made to work with any test framework that supplies the following:

* The current test's name 
* The current test's full source file path (with correct case of filename) 
* Ability to report unexpected exceptions as test failures, including reporting the text in `exception.what()`, and ideally also the exception type.
* Ability to return a non-zero exit status from the test program if there were any unexpected exceptions.

## Steps to add support

* Provide some code to add to the test's `main()` function, to listen out for the running of test cases
* Give that code a `TestName` instance, that will store information about the test being executed
* As each test case starts, update the `TestName` instance with details of the source file name, and test case name
* Ideally, provide a mechanism (such as a macro) that makes it easy for users to use this code in their own tests

## Examples

This is perhaps best understood by reviewing the implementations for frameworks that are already supported - see [/ApprovalTests/integrations/](/ApprovalTests/integrations/).
 

## Adding new framework to documentation

1. Add a new file about the customisation, such as [UsingCatch.source.md](/doc/mdsource/UsingCatch.source.md#top)
2. Record the new framework support in:
    * The `getMisconfiguredMainHelp()` help message in [HelpMessages.h](/ApprovalTests/namers/HelpMessages.h)
    * [include_using_test_frameworks_list.include.md](/doc/mdsource/include_using_test_frameworks_list.include.md#top)
    * [GettingStarted.source.md](/doc/mdsource/GettingStarted.source.md#top) - see "Choosing a testing framework"
    * [Setup.source.md](/doc/mdsource/Setup.source.md#top) - see the bullet list starting "Set up your `main()`"
    * Other documentation links: see [Definition of Done](/doc/Contributing.md#definition-of-done)


---

[Back to User Guide](/doc/README.md#top)
