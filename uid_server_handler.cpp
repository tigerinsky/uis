#include <sys/time.h>
#include <unistd.h>

#include "glog/logging.h"

#include "uid_server_handler.h"

using std::endl;

namespace tis {

uint64_t UidServerHandler::get_time() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    uint64_t time = tv.tv_usec;
    time /= 1000;
    time += (tv.tv_sec * 1000);
    return time;
}

int64_t UidServerHandler::get_id(const std::string& topic) {
    // Your implementation goes here
    LOG(INFO) << "get_id" << endl;
    int64_t uid = 0L;
    
    uint64_t timestamp = get_time();
    if (last_timestamp_ == timestamp) {

    } else {

    }

    return uid;
}

}

