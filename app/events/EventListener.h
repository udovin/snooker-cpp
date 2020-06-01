#pragma once

#include "Event.h"

namespace app { namespace events {

class EventListener
{
public:
    virtual ~EventListener();

    virtual void operator()(const Event &) = 0;
};

}};
