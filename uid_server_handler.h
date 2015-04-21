#ifndef __UID_SERVER_HANDLER_H_
#define __UID_SERVER_HANDLER_H_

#include <string>
#include "Thriftfiles/UidServer.h"

using namespace ::apache::thrift;
using std::string;

namespace tis {

class UidServerHandler : virtual public UidServerIf {
public:
    UidServerHandler():sequence_(0L), last_timestamp_(0L) {
        // Your initialization goes here
        time_epoch_ = 1288834974657L;
    }

    int64_t get_id(const std::string& topic);

private:
    uint64_t get_time();

private:
    int32_t sequence_;
    uint64_t last_timestamp_;
    uint64_t time_epoch_; 
};

}
#endif
