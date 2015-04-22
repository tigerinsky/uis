#include <sys/time.h>
#include <unistd.h>

#include "glog/logging.h"

#include "uid_server_handler.h"

using std::endl;

namespace tis {

//生成topic的数据
int UidServerHandler::init(
        int32_t machine,
        int topic_num,
        std::string& topic_names) {
    machine_ = machine;

    topic_data temp;
    topic_datas_[default_topic_] = temp;
    if (topic_names.size() <= 0) {
        return 0;
    }

    string::size_type start = 0;
    string::size_type position = topic_names.find_first_of(';');
    while (topic_names.npos != position) {
        std::string topic(topic_names.substr(start, position - start));
        topic_data temp;
        topic_datas_[topic] = temp;
        start = position + 1;
        position = topic_names.find_first_of(';', start);
    }

    if (start < topic_names.npos) {
        std::string topic(topic_names.substr(start));
        topic_data temp;
        topic_datas_[topic] = temp;
    }

    return 0;
}

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
    TOPIC_MAP::iterator iter = topic_datas_.find(topic);
    if (topic_datas_.end() == iter) {
        iter = topic_datas_.find(default_topic_);
    }

    pthread_mutex_lock(&((iter->second).mutex_));
    uint64_t timestamp = get_time();
    if ((iter->second).last_timestamp_ == timestamp) {
        (iter->second).sequence_ = ((iter->second).sequence_ + 1) & 0xFFF;
        if (0 == (iter->second).sequence_) {
            //todo 等到获取下一个毫秒时间戳
        }
    } else {
        (iter->second).sequence_ = 0;
    }
    (iter->second).last_timestamp_ = timestamp;

    uid = (timestamp - time_epoch_) << 22;
    uid |= (machine_ & 0x3FF) << 12;
    uid |= (iter->second).sequence_;

    pthread_mutex_unlock(&((iter->second).mutex_));
    return uid;
}

}

