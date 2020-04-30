// ReSharper disable once CppUnusedIncludeDirective
// begin-snippet: googletest_main
// main.cpp:
#define APPROVALS_GOOGLETEST // This tells Approval Tests to provide a main() - only do this in one cpp file
#include "ApprovalTests.hpp"
// end-snippet

using namespace ApprovalTests;

auto directoryDisposer = Approvals::useApprovalsSubdirectory("approval_tests");
