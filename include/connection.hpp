#ifndef	CONNECTION_HPP
#define	CONNECTION_HPP

#include <string>

namespace nanofi {
    struct Connection {
	    std::string source_id;
        std::string source_relationship;
        std::string destination_id;
	};
}

#endif // CONNECTION_HPP