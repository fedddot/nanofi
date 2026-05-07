#ifndef	FLOW_FILE_HPP
#define	FLOW_FILE_HPP

#include <string>

namespace nanofi {
	class FlowFile {
	public:
        FlowFile(const std::string& id);
        FlowFile(const FlowFile& other) = delete;
        FlowFile& operator=(const FlowFile& other) = delete;
        FlowFile(FlowFile&& other) = default;
        FlowFile& operator=(FlowFile&& other) = default;
        
        virtual ~FlowFile() noexcept = default;
        
        const std::string& id() const;
    private:
        std::string m_id;
    };
}

#endif // FLOW_FILE_HPP