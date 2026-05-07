#ifndef	PROCESS_SESSION_HPP
#define	PROCESS_SESSION_HPP

#include <string>

#include "flow_file.hpp"

namespace nanofi {
	class ProcessSession {
	public:
		virtual ~ProcessSession() noexcept = default;
        FlowFile create() const;
        void transfer(FlowFile&& flow_file, const std::string& relationship) const;
	};
}

#endif // PROCESS_SESSION_HPP