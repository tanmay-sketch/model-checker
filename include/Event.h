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
            Event(EventId id, ThreadId tid, EventLabel l) : event_id(id), thread_id(tid), label(l) {}

            // Copy constructor
            Event(const Event& other) : event_id(other.event_id), thread_id(other.thread_id), label(other.label) {}

            // Move constructor
            Event(Event&& other) noexcept : event_id(std::move(other.event_id)), thread_id(std::move(other.thread_id)), label(std::move(other.label)) {}
            
            // Virtual destructor
            virtual ~Event() = default;

            // Copy assignment
            Event& operator=(const Event& other) {
                if (this != &other) {
                    event_id = other.event_id;
                    thread_id = other.thread_id;
                    label = other.label;
                }
                return *this;
            }

            // Move assignment
            Event& operator=(Event&& other) noexcept {
                if (this != &other) {
                    event_id = std::move(other.event_id);
                    thread_id = std::move(other.thread_id);
                    label = std::move(other.label);
                }
                return *this;
            }
            
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

            // Copy constructor
            ReadEvent(const ReadEvent& other);

            // Move constructor
            ReadEvent(ReadEvent&& other) noexcept;

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

            // Copy constructor
            WriteEvent(const WriteEvent& other);

            // Move constructor
            WriteEvent(WriteEvent&& other) noexcept;

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

    // Fence event types have to be added later
    class FenceEvent : public Event {
        public:
            // Constructor
            FenceEvent(EventId id, ThreadId tid);

            // Copy constructor
            FenceEvent(const FenceEvent& other);

            // Move constructor
            FenceEvent(FenceEvent&& other) noexcept;

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