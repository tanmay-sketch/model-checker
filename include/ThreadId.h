/* 
    ThreadId.h 
    Path: /include/ThreadId.h
*/
#pragma once
#include <cstdint>

namespace mc {
    using ThreadId = uint8_t;
    
    // Simple function to generate unique thread IDs
    inline ThreadId generate_thread_id() {
        // static because next_id has to persist between function calls
        static ThreadId next_id = 0;
        return next_id++;
    }
}