#ifndef	PROCESSOR_HPP
#define	PROCESSOR_HPP

#include <string>

#include "process_session.hpp"
#include "process_context.hpp"

namespace nanofi {
    class ProcessSessionFactory;

	class Processor {
	public:
		virtual ~Processor() noexcept = default;
        virtual void on_schedule(const ProcessContext& context, const ProcessSessionFactory& session_factory) = 0;
        virtual void on_unschedule() = 0;
        virtual void on_trigger(const ProcessContext& context, ProcessSession *session) = 0;
        virtual std::string id() const = 0;
	};
}

#endif // PROCESSOR_HPP