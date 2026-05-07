#ifndef	CONNECTION_HPP
#define	CONNECTION_HPP

#include <queue>
#include <string>

#include "flow_file.hpp"

namespace nanofi {
    struct Connection {
        Connection(
            const std::string& source_id = "",
            const std::string& source_relationship = "",
            const std::string& destination_id = ""
        ): source_id(source_id), source_relationship(source_relationship), destination_id(destination_id) {

        }
        Connection(const Connection& other) = delete;
        Connection& operator=(const Connection& other) = delete;
        Connection(Connection&& other) = default;
        Connection& operator=(Connection&& other) = default;
        ~Connection() noexcept = default;

	    std::string source_id;
        std::string source_relationship;
        std::string destination_id;
        std::queue<FlowFile> queue;
	};
}

#endif // CONNECTION_HPP