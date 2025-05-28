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
