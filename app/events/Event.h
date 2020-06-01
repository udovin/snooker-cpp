#pragma once

#include <string>

namespace app { namespace events {

class Event {
public:
    const std::string type;

    Event(const std::string &);
    ~Event();
};

}};
