#include <vector>
#include <map>
#include <set>
#include "Event.h"
#include "ThreadId.h"
using namespace mc;

class ExecutionGraph {
    
    u_int16_t generate_event_id() {
        return this->current_event_ += 1;
    };

};