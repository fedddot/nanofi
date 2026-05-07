#ifndef	PROCESS_SESSION_HPP
#define	PROCESS_SESSION_HPP

#include <functional>
#include <optional>
#include <string>

#include "connection.hpp"
#include "flow_file.hpp"

namespace nanofi {
	class ProcessSession {
	public:
        using UidGenerator = std::function<std::string()>;
        ProcessSession(
            Connection *input_connection,
            const std::vector<Connection *>& output_connections,
            const UidGenerator& uid_generator
        ): m_input_connection(input_connection), m_output_connections(output_connections), m_uid_generator(uid_generator) {
            if (m_input_connection == nullptr) {
                throw std::invalid_argument("input_connection cannot be null");
            }
            for (const auto& output_connection : m_output_connections) {
                if (output_connection == nullptr) {
                    throw std::invalid_argument("output_connections cannot contain null");
                }
            }
            if (!m_uid_generator) {
                throw std::invalid_argument("uid_generator cannot be null");
            }
        }
        ProcessSession(const ProcessSession& other) = delete;
        ProcessSession& operator=(const ProcessSession& other) = delete;
        ProcessSession(ProcessSession&& other) noexcept = default;
        ProcessSession& operator=(ProcessSession&& other) noexcept = default;

		virtual ~ProcessSession() noexcept = default;

        FlowFile create() const {
            return FlowFile(m_uid_generator());
        }
        std::optional<FlowFile> read() {
            if (m_input_connection->queue.empty()) {
                return std::nullopt;
            }
            FlowFile flow_file = std::move(m_input_connection->queue.front());
            m_input_connection->queue.pop();
            return flow_file;
        }
        void transfer(FlowFile&& flow_file, const std::string& relationship) {
            Connection *output_connection = find_output_connection(relationship);
            output_connection->queue.push(std::move(flow_file));
        }
    private:
        Connection *m_input_connection;
        std::vector<Connection *> m_output_connections;
        UidGenerator m_uid_generator;

        Connection *find_output_connection(const std::string& relationship) const {
            for (const auto& output_connection : m_output_connections) {
                if (output_connection->source_relationship == relationship) {
                    return output_connection;
                }
            }
            throw std::invalid_argument("No output connection found for relationship: " + relationship);
        }
	};
}

#endif // PROCESS_SESSION_HPP