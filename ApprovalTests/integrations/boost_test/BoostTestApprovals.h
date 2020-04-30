#pragma once

#include "ApprovalTests/namers/ApprovalTestNamer.h"
#include "ApprovalTests/integrations/CheckFileMacroIsAbsolute.h"

#ifdef APPROVALS_BOOSTTEST

namespace ApprovalTests
{

    class BoostApprovalListener : public boost::unit_test::test_observer
    {
        ApprovalTests::TestName currentTest;

        void test_unit_start(boost::unit_test::test_unit const& test) override
        {
            std::string path(test.p_file_name.begin(), test.p_file_name.end());
            currentTest.setFileName(path);

            currentTest.sections.push_back(test.p_name);
            ApprovalTests::ApprovalTestNamer::currentTest(&currentTest);
        }

        void test_unit_finish(boost::unit_test::test_unit const& /*test*/,
                              unsigned long) override
        {
            currentTest.sections.pop_back();
        }
    };

    int register_our_listener(BoostApprovalListener& t)
    {
        boost::unit_test::framework::register_observer(t);
        return 1;
    }

    BoostApprovalListener o;
    auto dummy_variable = register_our_listener(o);
}

#endif // APPROVALS_BOOSTTEST