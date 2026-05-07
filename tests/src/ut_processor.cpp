#include "gtest/gtest.h"
#include <optional>
#include <string>

#include "connection.hpp"
#include "flow_file.hpp"
#include "processor.hpp"

using namespace nanofi;

namespace nanofi {
    class ProcessContext {};
    class ProcessSessionFactory {};
}

class TestProcessor : public Processor {
public:
    void on_schedule(const ProcessContext& context, const ProcessSessionFactory& session_factory) override {
        throw std::runtime_error("NOT IMPLEMENTED");
    }
    void on_unschedule() override {
        throw std::runtime_error("NOT IMPLEMENTED");
    }
    void on_trigger(const ProcessContext& context, ProcessSession *session) override {
        auto flow_file = session->read()
            .or_else([]()-> std::optional<FlowFile> {
                throw std::runtime_error("FlowFile should be available");
            })
            .value();
        session->transfer(std::move(flow_file), "success");
    }
    std::string id() const override {
        return "test_processor";
    }
};

TEST(ut_processor, processor_sanity) {
    // GIVEN
    TestProcessor processor;
    Connection input_connection(
        "input_source",
        "source_relationship",
        processor.id()
    );
    Connection output_connection(
        processor.id(),
        "success",
        "output_destination"
    );

    // WHEN
    std::size_t id = 0;
    ProcessSession session(
        &input_connection,
        { &output_connection },
        [&id]() {
            return std::string("id") + std::to_string(id++);
        }
    );

    // THEN
    FlowFile flow_file = session.create();
    input_connection.queue.push(std::move(flow_file));
    processor.on_trigger(ProcessContext(), &session);
    ASSERT_TRUE(input_connection.queue.empty());
    ASSERT_FALSE(output_connection.queue.empty());
}