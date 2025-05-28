/* 
    Event.h 
    Path: /include/Event.h
*/
#pragma once
#include <cstdint>
#include <string>
#include <iostream>
#include "ThreadId.h"

namespace mc {
    using EventId = uint16_t;
    enum class EventLabel : uint8_t {
        READ = 0,
        WRITE = 1,
        FENCE = 2,
        ERROR = 3,
        BLOCK = 4
    };

    class Event {
        protected:
            EventId event_id;
            ThreadId thread_id;
            EventLabel label;

        public:
            // Constructor
            Event(EventId id, ThreadId tid, EventLabel l);
            
            // Virtual destructor
            virtual ~Event() = default;

            // Copy assignment
            Event& operator=(const Event& other);

            // Move assignment
            Event& operator=(Event&& other) noexcept;
            
            // Getters
            EventId getId() const { return event_id; }
            ThreadId getThreadId() const { return thread_id; }
            EventLabel getLabel() const { return label; }

            // Virtual methods
            virtual void printEvent() const = 0;
    };

    class ReadEvent : public Event {
        private:
            std::string variable;
            int value;

        public:
            // Constructor
            ReadEvent(EventId id, ThreadId tid, std::string var, int val);

            // Destructor
            ~ReadEvent() override = default;

            // Copy assignment
            ReadEvent& operator=(const ReadEvent& other);

            // Move assignment
            ReadEvent& operator=(ReadEvent&& other) noexcept;

            // Getters
            EventId getEventId() const { return Event::getId(); }
            ThreadId getThreadId() const { return Event::getThreadId(); }
            EventLabel getEventLabel() const { return Event::getLabel(); }
            std::string getVariable() const { return variable; }
            int getValue() const { return value; }

            void printEvent() const override;
    };

    class WriteEvent : public Event {
        private:
            std::string variable;
            int value;

        public:
            // Constructor
            WriteEvent(EventId id, ThreadId tid, std::string var, int val);

            // Destructor
            ~WriteEvent() override = default;

            // Copy assignment
            WriteEvent& operator=(const WriteEvent& other);

            // Move assignment
            WriteEvent& operator=(WriteEvent&& other) noexcept;

            // Getters
            EventId getEventId() const { return Event::getId(); }
            ThreadId getThreadId() const { return Event::getThreadId(); }
            EventLabel getEventLabel() const { return Event::getLabel(); }
            std::string getVariable() const { return variable; }
            int getValue() const { return value; }

            void printEvent() const override;
    };

    class FenceEvent : public Event {
        public:
            // Constructor
            FenceEvent(EventId id, ThreadId tid);

            // Destructor
            ~FenceEvent() override = default;

            // Copy assignment
            FenceEvent& operator=(const FenceEvent& other);

            // Move assignment
            FenceEvent& operator=(FenceEvent&& other) noexcept;

            // Getters
            EventId getEventId() const { return Event::getId(); }
            ThreadId getThreadId() const { return Event::getThreadId(); }
            EventLabel getEventLabel() const { return Event::getLabel(); }
            
            void printEvent() const override;
    };
}