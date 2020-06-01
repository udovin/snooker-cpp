#pragma once

#include "Event.h"
#include "EventListener.h"

#include <map>
#include <vector>
#include <string>

namespace app { namespace events {

class EventDispatcher
{
private:
    std::map< std::string, std::vector<EventListener *> > listeners;

public:
    EventDispatcher();
    ~EventDispatcher();

    void dispatchEvent(const Event &);

    void addEventListener(const std::string &, EventListener *);
};

}};
