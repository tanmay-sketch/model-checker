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
#include <functional>
using namespace mc;

class ExecutionGraph {
    private:
        /*
            Event collections:
            ------------------
            G.e: Set of events
            G.write_events: Unordered map of write event IDs of write events
            G.read_events: Unordered map of read event IDs of read events
            G.fence_events: Unordered map of fence event IDs of fence events
            G.revisit_set: Unordered map of read event IDs of read events that may need to be revisited when new writes are added

            Base Relations:
            ------------------
            G.sb: Sequenced before relation (set of (e1,e2) pairs where e1 sequenced before e2)
            G.rf: Reads from (unordered map of read event IDs to write event IDs)
            G.mo: Modification order (unordered map of variable "IDs" to ordered list of write events)

            Derived Relations:
            ------------------
            1. Release Sequence (rseq)
                - Derived from: sb, rf
                - Formula: [Wx];sb?;[W⊒rlx];(rf;rmw)*
                - Contains: write itself + later writes in same thread + RMWs reading from such writes

            2. Synchronizes-with (sw)
                - Derived from: sb, rf, rseq
                - Formula: [E⊒rel];([F];sb)?;rseq;rf;[R⊒rlx];(sb;[F])?;[E⊒acq]
                - Links release operations with acquire operations

            3. Happens-before (hb)
                - Derived from: sb, sw
                - Formula: (sb ∪ sw)+
                - Transitive closure of program order and synchronization

            4. Extended Coherence Order (eco)
                - Derived from: mo, rf
                - Used to maintain coherence constraints

            5. Read-Modify-Write pairs (rmw)
                - Derived from: sb, rf
                - Formula: [Rex];sb|imm
                - Links read and write parts of atomic operations

            6. Program Order (po)
                - Same as sb (sequenced-before)
                - No need to store separately

            7. Partial SC Order (psc)
                - Derived from: sb, hb, mo, rf
                - Used for sequential consistency constraints
        */

        u_int16_t current_event_ = 0;

        // Base Relations
        std::map<EventId, EventId> rf;
        std::map<EventId, EventId> sb;
        std::map<std::string, std::vector<EventId>> mo;

        // Events collection
        std::unordered_map<std::string, std::unordered_map<EventId, Event*>> events;

        // Derived Relations: not sure about what's written below
        std::set<std::pair<Event*, Event*>> compute_rseq(Event* write) const;
        std::set<std::pair<Event*, Event*>> compute_sw(Event* release, Event* acquire) const;
        std::set<std::pair<Event*, Event*>> compute_hb(Event* e1, Event* e2) const;
        std::set<std::pair<Event*, Event*>> compute_eco(Event* e1, Event* e2) const;
        std::set<std::pair<Event*, Event*>> compute_rmw(Event* read, Event* write) const;
        std::set<std::pair<Event*, Event*>> compute_psc(Event* e1, Event* e2) const;


    public:
        ExecutionGraph();
        ~ExecutionGraph();
        
        u_int16_t generate_event_id() {
            static u_int16_t counter = 0;
            return counter++;
        }
        
        //Event management
        void add_write_event(WriteEvent* write_event);
        void add_read_event(ReadEvent* read_event);
        void add_fence_event(FenceEvent* fence_event);

        // Relation management
        void add_rf_edge(WriteEvent* write_event, ReadEvent* read_event);
        void add_sb_edge(Event* e1, Event* e2);
        void add_mo_edge(WriteEvent* write_event1, WriteEvent* write_event2);

        // Methods to manage revisit set
        void add_to_revisit_set(Event* read_event);
        void remove_from_revisit_set(Event* read_event);
        bool is_in_revisit_set(Event* read_event) const;
        const std::set<Event*>& get_revisit_set() const;
};