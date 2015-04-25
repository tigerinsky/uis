#ifndef __UID_SERVER_HANDLER_H_
#define __UID_SERVER_HANDLER_H_

#include <string>
#include <map>
#include <pthread.h>
#include "Thriftfiles/UidServer.h"

using namespace ::apache::thrift;
using std::string;
using std::map;

namespace tis {

struct topic_data {
    pthread_mutex_t mutex_;
    int32_t topic_id_;
    int32_t sequence_;
    uint64_t last_timestamp_;

    topic_data() {
        pthread_mutex_init(&mutex_, NULL);
        topic_id_ = 0;
        sequence_ = 0;
        last_timestamp_ = 0L;
    }

    explicit topic_data(int32_t topic_id): topic_id_(topic_id) {
        pthread_mutex_init(&mutex_, NULL);
        sequence_ = 0;
        last_timestamp_ = 0L;
    }

    ~topic_data() {
        pthread_mutex_destroy(&mutex_);
    }

    topic_data(const topic_data& other) {
        this->mutex_ = other.mutex_;
        this->topic_id_ = other.topic_id_;
        this->sequence_ = other.sequence_;
        this->last_timestamp_ = other.last_timestamp_;
    }
    
    topic_data& operator = (const topic_data& other) {
        this->mutex_ = other.mutex_;
        this->topic_id_ = other.topic_id_;
        this->sequence_ = other.sequence_;
        this->last_timestamp_ = other.last_timestamp_;
        return *this;
    }
};

typedef std::map<std::string, topic_data> TOPIC_MAP;

class UidServerHandler : virtual public UidServerIf {
public:
    UidServerHandler() {
        // Your initialization goes here
        machine_ = 0;
        time_epoch_ = 1288834974657L;
        default_topic_.assign("default");
    }

    int init(int32_t machine, int topic_num, std::string& topic_names);

    int64_t get_id(const std::string& topic);

private:
    uint64_t get_time();

private:
    TOPIC_MAP topic_datas_;
    std::string default_topic_;
    int32_t machine_;       //机器id
    uint64_t time_epoch_; 
};

}
#endif
