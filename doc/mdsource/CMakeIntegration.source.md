<a id="top"></a>

# CMake Integration

toc

## Part 1: Reference

### Integration Points

Because we use CMake to build ApprovalTests.cpp, we also provide integration points for our users.

#### CMake target

Approval Tests' CMake build exports an interface target `ApprovalTests::ApprovalTests`. Linking
against it will add the proper include path and all necessary capabilities
to the resulting binary.

This target is provided when ApprovalTests.cpp is used as a subdirectory.
Assuming that ApprovalTests.cpp has been cloned to `lib/ApprovalTests.cpp`:

```cmake
add_subdirectory(lib/ApprovalTests.cpp)
target_link_libraries(tests ApprovalTests::ApprovalTests)
```

#### CMake project options

ApprovalTests.cpp's CMake project also provides some options for other projects
that consume it.
 
They are:

* Options to control what targets are built.
    * Note that these are always built if this is the top-level project.
    * `APPROVAL_TESTS_BUILD_TESTING` -- When `ON`, the self-tests are run.  Defaults to `OFF`.
    * `APPROVAL_TESTS_BUILD_EXAMPLES` -- When `ON`, the examples are run.  Defaults to `OFF`.
* Options to control which of our copies of header-only third_party libraries are made available.
    * Note that these are always included if this is the top-level project.
    * `APPROVAL_TESTS_BUILD_THIRD_PARTY_CATCH2` --  When `ON`, this project's copy of the Catch2 test framework is included.  Defaults to `OFF`.
    * `APPROVAL_TESTS_BUILD_THIRD_PARTY_DOCTEST` --  When `ON`, this project's copy of the doctest test framework is included.  Defaults to `OFF`.
    * `APPROVAL_TESTS_BUILD_THIRD_PARTY_UT` --  When `ON`, this project's copy of the Boost.UT test framework is included.  Defaults to `OFF`.
* Options to control the behaviour of our builds.
    * `APPROVAL_TESTS_ENABLE_CODE_COVERAGE` -- When `ON`, Approval Test's own tests are run with code coverage enabled. This uses [Lars Bilke's CodeCoverage.cmake](https://github.com/bilke/cmake-modules/blob/master/CodeCoverage.cmake).  Defaults to `OFF`.

The file [CMake/ApprovalTestsOptions.cmake](https://github.com/approvals/ApprovalTests.cpp/blob/master/CMake/ApprovalTestsOptions.cmake) defines these options.

#### CMake commands support

* `add_subdirectory()`
    * See [Use own ApprovalTests.cpp and Catch2 clones](/doc/CMakeIntegration.md#use-own-approvaltestscpp-and-catch2-clones) below, for an example using [`add_subdirectory()`](https://cmake.org/cmake/help/latest/command/add_subdirectory.html).
    * **Use case:** This is typically for you have your own copy of the Approval Tests project directory that you want to re-use.
* `FetchContent`
    * See [Make CMake clone ApprovalTests.cpp and Catch2](/doc/CMakeIntegration.md#make-cmake-clone-approvaltestscpp-and-catch2)
 below, for an example using the [`FetchContent` module](https://cmake.org/cmake/help/latest/module/FetchContent.html).
    * The examples below use `FetchContent_MakeAvailable()`, which requires CMake 3.14 or above.
    * If you only have CMake 3.11 or above, see [FetchContent (CMake 3.11+)](https://cliutils.gitlab.io/modern-cmake/chapters/projects/fetch.html) for how to use `FetchContent_Populate()`.
    * **Use case:** This is typically for when you want CMake to download a specific version of Approval Tests for you, behind the scenes.
* `ExternalProject`
    * With CMake before 3.11, see the [`ExternalProject` module](https://cmake.org/cmake/help/latest/module/ExternalProject.html). The `FetchContent` examples below should help get started with `ExternalProject`.
    * **Use case:** This is typically for when you want CMake to download a specific version of Approval Tests for you, behind the scenes, and you are using an older version of CMake.
* `find_package()` - not supported
    * There is not yet support for [`find_package()`](https://cmake.org/cmake/help/latest/command/find_package.html).

### Single header or CMake Integration?

There are two main options for incorporating Approval Tests in to your project:

1. Download the single-header file from the [Releases page](https://github.com/approvals/ApprovalTests.cpp/releases) and, typically, add the header to your source code.
2. Obtain a copy of the entire ApprovalTests.cpp repository and incorporate it in to your CMake build scripts.

Options for obtaining the repository typically include:

* cloning it
* forking it
* including it as a sub-repository
* having a build tool, such as CMake, download it for you automatically as part of your builds

#### CMake Integration Benefits

We recommend using the CMake integration route, which has several user benefits over the single header:

* Automatic prevention of most of the scenarios listed in [Troubleshooting Misconfigured Build](/doc/TroubleshootingMisconfiguredBuild.md#top).
* Source-code compatibility with the single header download:
    * For convenience, we provide a wrapper header file [ApprovalTests.hpp](https://github.com/approvals/ApprovalTests.cpp/blob/master/ApprovalTests/ApprovalTests.hpp), which can be used to access all the features of this library, without having to know which features are provided by which header files.
* Flexibility in how many of the Approval Tests include files you include:
    * There is also the option to include just the headers in [ApprovalTests/](https://github.com/approvals/ApprovalTests.cpp/blob/master/ApprovalTests) that you use.
    * This may slightly improve build speeds.
* It may occasionally [provide workarounds to bugs](https://github.com/approvals/ApprovalTests.cpp/issues/90).

## Part 2: Optional Explanatory Examples

### Scenarios when using Approval Tests 

#### Context

**Example Project**

Suppose you are writing some tests that use ApprovalTests.cpp with the Catch2 test framework.

Your top-level `CMakeLists.txt` file might look something like this:

include: inc_fetch_content_approvaltests_cmakelists

The important thing to note, for following the examples below, is the `add_subdirectory(dependencies)` line. It makes CMake load a file `dependencies/CMakeLists.txt`.

Each example below shows a `dependencies/CMakeLists.txt`, for the corresponding scenario. All other code is identical between the example directories.

Here is [this example project](https://github.com/claremacrae/ApprovalTests.cpp.CMakeSamples/tree/master/fetch_content_approvaltests).

**Example Tests**

Your `tests/CMakeLists.txt` file might look something like this:

include: inc_fetch_content_approvaltests_tests_cmakelists

This says that the libraries `ApprovalTests::ApprovalTests` and `Catch2::Catch2` are required by the `tests` executable.

Here is [this example project's test directory](https://github.com/claremacrae/ApprovalTests.cpp.CMakeSamples/tree/master/fetch_content_approvaltests/tests).

**Dependencies**

How might you enable CMake to provide those libraries? In other words, what are the options for the contents of `dependencies/CMakeLists.txt`?

The next few sections describe some options.

#### Make CMake clone ApprovalTests.cpp and Catch2

**Note:** The files in this section can be viewed and downloaded from [fetch_content_approvaltests_catch2](https://github.com/claremacrae/ApprovalTests.cpp.CMakeSamples/tree/master/fetch_content_approvaltests_catch2).

The following is for when you just want ApprovalTests.cpp and Catch2 to be downloaded as part of your project's build. You don't particularly want to see their source code, although you're happy if your debugger steps in to them.

It also needs CMake 3.14 or above.

We use this `dependencies/CMakeLists.txt` file:

include: inc_fetch_content_approvaltests_catch2_dependencies_cmakelists

Note the `GIT_TAG` values: This tells CMake which revision of dependencies to use. The value can be a tag or a git commit ID. Here we use `master`, to always test our integrations with the latest Approval Tests code. However, it is generally recommended to pin your dependencies to specific versions, and test behaviour before updating to newer versions. 

After CMake has generated the build files, the directory structure would look something like this, where the `cmake-build-debug` directory is the build space, and the `cmake-build-debug/_deps` contains the downloaded and built ApprovalTests.cpp and Catch2 repositories:

```
fetch_content_approvaltests_catch2/
  .git/
  cmake-build-debug/
    _deps/
      approvaltests-build/
      approvaltests-src/
      approvaltests-subbuild/
      catch2-build
      catch2-src
      catch2-subbuild
    ...
  CMakeLists.txt
  dependencies/
    CMakeLists.txt
  tests/
    ...
```

#### Make CMake clone ApprovalTests.cpp

**Note:** The files in this section can be viewed and downloaded from [fetch_content_approvaltests](https://github.com/claremacrae/ApprovalTests.cpp.CMakeSamples/tree/master/fetch_content_approvaltests).

The only difference between the previous example and this one is that here we use the Catch2 header that is in the ApprovalTests.cpp project.

We use this `dependencies/CMakeLists.txt` file:

include: inc_fetch_content_approvaltests_dependencies_cmakelists

We have set `APPROVAL_TESTS_BUILD_THIRD_PARTY_CATCH2` to `ON`, so that CMake will use the copy of Catch2 that is included in the ApprovalTests.cpp repository.

There are also options to enable use of ApprovalTests.cpp's copies of all other supported test frameworks except GoogleTest, including:

* `APPROVAL_TESTS_BUILD_THIRD_PARTY_DOCTEST`
* `APPROVAL_TESTS_BUILD_THIRD_PARTY_UT`

#### Use own ApprovalTests.cpp and Catch2 clones

**Note:** The files in this section can be viewed and downloaded from [add_subdirectory_approvaltests_catch2](https://github.com/claremacrae/ApprovalTests.cpp.CMakeSamples/tree/master/add_subdirectory_approvaltests_catch2).

Here, instead of getting CMake to download ApprovalTests.cpp and Catch2, we have got our own clones or forks of them, which we want to use with our own tests.

In this example, the directory structure looks like this:

```
ApprovalTests.cpp/
  .git/
  CMakeLists.txt
  ...
Catch2/
  .git/
  CMakeLists.txt
  ...

add_subdirectory_approvaltests_catch2/
  .git/
  CMakeLists.txt
  dependencies/
    CMakeLists.txt
  tests/
```

We use this `dependencies/CMakeLists.txt` file:

include: inc_add_subdirectory_approvaltests_catch2_dependencies_cmakelists

Here we use `add_subdirectory()`. This works with older versions of CMake, unlike the `FetchContent` examples above.

The above was tested with CMake 3.8.

If your directory layout differed from the above, you would change the relative paths in the `add_subdirectory()` lines.

#### Using other supported test frameworks

To save space and repetition, the examples above only show the Catch2 test framework.

The same principles apply when using all the other test frameworks supported by ApprovalTests.cpp.

### Scenarios when developing ApprovalTests.cpp 

#### Developing ApprovalTests.cpp with test framework sources

**Note:** The files in this section can be viewed and downloaded from [develop_approvaltests](https://github.com/claremacrae/ApprovalTests.cpp.CMakeSamples/tree/master/develop_approvaltests).

For Approval Tests project maintainers, it is useful to be able to edit and debug both this project and the test frameworks that it depends upon. It helps to be able to see the source of these frameworks, rather than just the single-header releases that are copied in to the third_party directory here.

This also allows us to checkout different commits of any of these projects.

Here we want to enable and run all the ApprovalTests.cpp tests, unlike the cases above, where we only want to run the tests of the project that is being developed.

Consider this directory structure, where the repositories for all these projects are checked out side-by-side, and there is an extra directory `develop_approvaltests/` that will contain just a `CMakeLists.txt` file, to set up a project containing all the other directories:

```
ApprovalTests.cpp/
  .git/
  CMakeLists.txt
  ...
Catch2/
  .git/
  CMakeLists.txt
  ...
doctest/
  .git/
  CMakeLists.txt
  ...
googletest/
  .git/
  CMakeLists.txt
  ...
ut/
  .git/
  CMakeLists.txt
  ...

develop_approvaltests/
  CMakeLists.txt
```

The file `develop_approvaltests/CMakeLists.txt` creates a kind of "super build": one project for developing ApprovalTests.cpp and all the projects it depends on:

include: inc_develop_approvaltests_cmakelists

---

[Back to User Guide](/doc/README.md#top)
