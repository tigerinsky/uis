#ifndef  __MS_FLAG_H_ 
#define  __MS_FLAG_H_

#include "google/gflags.h"

namespace tis {

DECLARE_int32(server_port);
DECLARE_int32(server_thread_num);
DECLARE_int32(topic_num);
DECLARE_string(topic_names);

}
#endif
