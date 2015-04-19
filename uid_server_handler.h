#ifndef __UID_SERVER_HANDLER_H_
#define __UID_SERVER_HANDLER_H_

#include "Thriftfiles/UidServer.h"

using namespace ::apache::thrift;

namespace tis {

class UidServerHandler : virtual public UidServerIf {
public:
    UidServerHandler() {
    // Your initialization goes here
    }

    int64_t get_id(const std::string& topic);
};

}
#endif
