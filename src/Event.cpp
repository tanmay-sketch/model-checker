/* 
    Event.cpp
    Path: /src/Event.cpp
*/
#include <cstdint>
#include <string>
#include <iostream>
#include "../include/ThreadId.h"
#include "../include/Event.h"
using namespace mc;

// ReadEvent implementations
ReadEvent::ReadEvent(EventId id, ThreadId tid, std::string var, int val)
    : Event(id, tid, EventLabel::READ), variable(var), value(val) {}

ReadEvent::ReadEvent(const ReadEvent& other)
    : Event(other), variable(other.variable), value(other.value) {}

ReadEvent::ReadEvent(ReadEvent&& other) noexcept
    : Event(std::move(other)), variable(std::move(other.variable)), value(std::move(other.value)) {}

ReadEvent& ReadEvent::operator=(const ReadEvent& other) {
    if (this != &other) {
        Event::operator=(other);
        variable = other.variable;
        value = other.value;
    }
    return *this;
}

ReadEvent& ReadEvent::operator=(ReadEvent&& other) noexcept {
    if (this != &other) {
        Event::operator=(std::move(other));
        variable = std::move(other.variable);
        value = std::move(other.value);
    }
    return *this;
}

// WriteEvent implementations
WriteEvent::WriteEvent(EventId id, ThreadId tid, std::string var, int val)
    : Event(id, tid, EventLabel::WRITE), variable(var), value(val) {}

WriteEvent::WriteEvent(const WriteEvent& other)
    : Event(other), variable(other.variable), value(other.value) {}

WriteEvent::WriteEvent(WriteEvent&& other) noexcept
    : Event(std::move(other)), variable(std::move(other.variable)), value(std::move(other.value)) {}

WriteEvent& WriteEvent::operator=(const WriteEvent& other) {
    if (this != &other) {
        Event::operator=(other);
        variable = other.variable;
        value = other.value;
    }
    return *this;
}

WriteEvent& WriteEvent::operator=(WriteEvent&& other) noexcept {
    if (this != &other) {
        Event::operator=(std::move(other));
        variable = std::move(other.variable);
        value = std::move(other.value);
    }
    return *this;
}

// FenceEvent implementations
FenceEvent::FenceEvent(EventId id, ThreadId tid)
    : Event(id, tid, EventLabel::FENCE) {}

FenceEvent::FenceEvent(const FenceEvent& other)
    : Event(other) {}

FenceEvent::FenceEvent(FenceEvent&& other) noexcept
    : Event(std::move(other)) {}

FenceEvent& FenceEvent::operator=(const FenceEvent& other) {
    if (this != &other) {
        Event::operator=(other);
    }
    return *this;
}

FenceEvent& FenceEvent::operator=(FenceEvent&& other) noexcept {
    if (this != &other) {
        Event::operator=(std::move(other));
    }
    return *this;
}

// Print implementations
void ReadEvent::printEvent() const {
    EventId event_id = getEventId();
    ThreadId tid = getThreadId();
    EventLabel label = getLabel();
    std::string variable = getVariable();
    int value = getValue();

    std::cout << "Event (" << event_id << "): " 
              << "in thread: " << tid << std::endl
              << "Event type: " << (label == EventLabel::READ ? "READ" : "UNKNOWN") << std::endl
              << "Value in " << variable << " that is being read: " << value << std::endl;
}

void WriteEvent::printEvent() const {
    EventId event_id = getEventId();
    ThreadId tid = getThreadId();
    EventLabel label = getLabel();
    std::string variable = getVariable();
    int value = getValue();

    std::cout << "Event (" << event_id << "): " 
              << "in thread: " << tid << std::endl
              << "Event type: " << (label == EventLabel::WRITE ? "WRITE" : "UNKNOWN") << std::endl
              << "Value in " << variable << " that is being written: " << value << std::endl;
}

void FenceEvent::printEvent() const {
    EventId event_id = getEventId();
    ThreadId tid = getThreadId();
    EventLabel label = getLabel();

    std::cout << "Event (" << event_id << "): " 
              << "in thread: " << tid << std::endl
              << "Event type: " << (label == EventLabel::FENCE ? "FENCE" : "UNKNOWN") << std::endl;
}
