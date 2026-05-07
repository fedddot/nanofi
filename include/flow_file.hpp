#ifndef	FLOW_FILE_HPP
#define	FLOW_FILE_HPP

#include <string>
#include <vector>

namespace nanofi {
	class FlowFile {
	public:
        using Content = std::vector<char>;
        FlowFile(const std::string& id);
        FlowFile(const FlowFile& other) = default;
        FlowFile& operator=(const FlowFile& other) = default;
        FlowFile(FlowFile&& other) = default;
        FlowFile& operator=(FlowFile&& other) = default;
        virtual ~FlowFile() noexcept = default;
        
        const std::string& id() const;

        Content content;
    private:
        std::string m_id;
    };
}

#endif // FLOW_FILE_HPP