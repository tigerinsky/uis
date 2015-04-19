#ifndef __UID_SERVER_H_
#define __UID_SERVER_H_

namespace apache { namespace thrift {namespace server {
            //class TThreadPoolServer;
            class TNonblockingServer;
}}}

namespace tis {

class UidServer {
public:
    UidServer();
    ~UidServer();

    int init();
    int run();
    void stop();
private:
    //apache::thrift::server::TThreadPoolServer *_server;
    apache::thrift::server::TNonblockingServer *_server;
};

}

#endif

