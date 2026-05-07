#ifndef	PROCESSOR_HPP
#define	PROCESSOR_HPP

namespace nanofi {
    class ProcessContext;
    class ProcessSessionFactory;
    class ProcessSession;

	class Processor {
	public:
		virtual ~Processor() noexcept = default;
        virtual void on_schedule(const ProcessContext& context, const ProcessSessionFactory& session_factory) = 0;
        virtual void on_unschedule() = 0;
        virtual void on_trigger(const ProcessContext& context, ProcessSession *session) = 0;
	};
}

#endif // PROCESSOR_HPP