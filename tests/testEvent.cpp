#include <iostream>
#include "../include/Event.h"

using namespace mc;

bool checkReadEvent(const ReadEvent& event) {
    if (event.getLabel() != EventLabel::READ) {
        return false;
    }

    event.printEvent();

    return true;
}

bool checkWriteEvent(const WriteEvent& event) {
    if (event.getLabel() != EventLabel::WRITE) {
        return false;
    }

    event.printEvent();

    return true;
}

bool checkFenceEvent(const FenceEvent& event) {
    if (event.getLabel() != EventLabel::FENCE) {
        return false;
    }

    event.printEvent();

    return true;
}

int main() {
    ReadEvent readEvent(1, 1, "x", 1);
    checkReadEvent(readEvent);
    std::cout << std::endl;

    WriteEvent writeEvent(2, 1, "x", 2);
    checkWriteEvent(writeEvent);
    std::cout << std::endl;

    FenceEvent fenceEvent(3, 1);
    checkFenceEvent(fenceEvent);
    std::cout << std::endl;

    return 0;
}