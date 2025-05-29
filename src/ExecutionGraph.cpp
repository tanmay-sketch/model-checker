#include <vector>
#include <map>
#include <set>
#include "Event.h"
#include "ThreadId.h"
#include "ExecutionGraph.h"
using namespace mc;

u_int16_t ExecutionGraph::generate_event_id() {
    return this->current_event_ += 1;
}