#include "EventDispatcher.h"

namespace app { namespace events {

EventDispatcher::EventDispatcher()
    : listeners()
{}

EventDispatcher::~EventDispatcher()
{
    listeners.clear();
}

void EventDispatcher::dispatchEvent(const Event &event)
{
    std::vector<EventListener *> &list = listeners[event.type];

    for (std::size_t i = 0; i < list.size(); i++)
        (*list[i])(event);
}

void EventDispatcher::addEventListener(const std::string &type, EventListener *listener)
{
    listeners[type].push_back(listener);
}

}};
