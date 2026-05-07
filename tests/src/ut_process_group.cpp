#include "gtest/gtest.h"

#include "process_group.hpp"

using namespace nanofi;

class TestProcessor : public Processor {
public:
    void on_schedule(const ProcessContext& context, const ProcessSessionFactory& session_factory) override {
        // No-op
    }
    void on_unschedule() override {
        // No-op
    }
    void on_trigger(const ProcessContext& context, ProcessSession *session) override {
        // No-op
    }
};


TEST(ut_process_group, process_group_sanity) {
    // WHEN
    ProcessGroup test_group;

    // THEN
    ASSERT_NO_THROW(test_group.);
}