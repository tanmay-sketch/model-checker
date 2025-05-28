/* 
    ExecutionGraph.h 
    Path: /include/ExecutionGraph.h
*/
#pragma once
#include <vector>
#include <map>
#include <set>
#include "Event.h"
#include "ThreadId.h"
using namespace mc;

class ExecutionGraph {
    private:
        /*
            G.e: Vector of events
            G.po: Program order (order in which events are executed)
            G.rf: Read from (maps read event id to write event id)
            G.hb: Happens before (set of (e1, e2) pairs where e1 happens before e2)
            G.eco: Extended coherence order (set of (e1, e2) pairs)
            G.mo: Modification order (maps variable id to ordered list of write events)
            G.psc: Partial SC order (set of (e1, e2) pairs)
            G.write_events: Set of write event IDs
            G.read_events: Set of read event IDs
        */
        u_int16_t current_event_ = 0;

        std::vector<Event*> events;
        std::map<ThreadId,std::vector<int>> program_order;
        std::map<Event*, Event*> reads_from;  
        std::set<std::pair<Event*, Event*>> happens_before;
        std::set<std::pair<Event*, Event*>> extended_coherence_order; 
        std::map<Event*, std::vector<Event*>> modification_order; 
        std::set<std::pair<Event*, Event*>> partial_sc_order;
        std::set<Event*> write_events;
        std::set<Event*> read_events;
        std::set<Event*> fence_events;

    public:
        ExecutionGraph();
        ~ExecutionGraph();
        bool initialize_execution_graph();

        
        u_int16_t generate_event_id();
        
        void add_write_event(WriteEvent* write_event);
        void add_read_event(ReadEvent* read_event);
        void add_fence_event(FenceEvent* fence_event);
};