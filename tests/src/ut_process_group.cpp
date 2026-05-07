#include <memory>
#include <stdexcept>

#include "gtest/gtest.h"

#include "process_group.hpp"

using namespace nanofi;

class TestProcessor : public Processor {
public:
    void on_schedule(const ProcessContext& context, const ProcessSessionFactory& session_factory) override {
        throw std::runtime_error("NOT IMPLEMENTED");
    }
    void on_unschedule() override {
        throw std::runtime_error("NOT IMPLEMENTED");
    }
    void on_trigger(const ProcessContext& context, ProcessSession *session) override {
        throw std::runtime_error("NOT IMPLEMENTED");
    }
    std::string id() const override {
        return "test_processor";
    }
};

TEST(ut_process_group, process_group_sanity) {
    // WHEN
    ProcessGroup test_group;

    // THEN
    ASSERT_NO_THROW(test_group.add_processor(std::make_unique<TestProcessor>()));
}