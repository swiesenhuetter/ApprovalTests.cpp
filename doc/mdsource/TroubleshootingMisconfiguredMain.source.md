<a id="top"></a>

# Troubleshooting Misconfigured Main

toc

## Symptoms

Running tests gives the following output:

snippet: ForgottenToConfigure.HelpMessage.approved.txt 

## Solutions

These are the things to check.

### Check the instructions for your test framework

Approval Tests needs to know which test framework to connect to, and that usually involves making small changes to the `main()` function for your test program.

This error usually indicates that a problem in your test program's `main()` means that ApprovalTests.cpp is not correctly set up for your test framework. 

The following resources should help:

* The text in the error message above may be enough to get you going.
* If not, see [Getting Started - Creating your main()](/doc/GettingStarted.md#top) to find out what you need to do for your chosen test framework, or to select one, if you have not yet done so.

### Check Google Test Framework

* Have you created a `main.cpp` that sets up ApprovalTests?
    * If not, the default Google Test `main()` will be used, which will not set up Approval Tests
    * To fix, copy in the non-comment code from [tests/GoogleTest_Tests/main.cpp](/tests/GoogleTest_Tests/main.cpp)
* Is your `main.cpp` included in your project's build?
    * If not, the default Google Test `main()` will be used, which will not set up Approval Tests
    * To fix, e.g. check your `CMakeLists.txt` file
* Does your Google Test have its own custom `main.cpp`?
    * If so, perhaps you haven't yet added the code to set up Approval Tests?
    * To fix, copy in the Approvals-specific lines from [examples/googletest_existing_main/main.cpp](/examples/googletest_existing_main/main.cpp)

### Other Issues

* Is your code calling `Approvals::verify()` or any other methods in this library from outside a Google Test?
    * This is much less likely to be the cause, but the file-naming code in Approval Tests (`ApprovalTestNamer`) does require that approvals are used from inside a test method in a supported test framework. 
---

[Back to User Guide](/doc/README.md#top)
