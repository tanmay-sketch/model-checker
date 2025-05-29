#include <vector>
#include <map>
#include <set>
#include "Event.h"
#include "ThreadId.h"
#include "ExecutionGraph.h"
using namespace mc;

ExecutionGraph::ExecutionGraph() {
    this->current_event_ = 0;
}