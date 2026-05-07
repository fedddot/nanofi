#ifndef	PROCESS_GROUP_HPP
#define	PROCESS_GROUP_HPP

#include <memory>
#include <vector>

#include "connection.hpp"
#include "processor.hpp"

namespace nanofi {
	class ProcessGroup {
	public:
        ProcessGroup() = default;
        ProcessGroup(const ProcessGroup& other) = delete;
        ProcessGroup(ProcessGroup&& other) noexcept = default;
        ProcessGroup& operator=(const ProcessGroup& other) = delete;
        ProcessGroup& operator=(ProcessGroup&& other) noexcept = default;
		virtual ~ProcessGroup() noexcept = default;

        void add_processor(std::unique_ptr<Processor>&& processor) {
            m_processors.emplace_back(std::move(processor));
        }
        void add_connection(const Connection& connection) {
            m_connections.emplace_back(connection);
        }
	private:
        std::vector<std::unique_ptr<Processor>> m_processors;
        std::vector<Connection> m_connections;
	};
}

#endif // PROCESS_GROUP_HPP