#include "Event.h"

namespace app { namespace events {

Event::Event(const std::string &type)
    : type(type)
{}

Event::~Event()
{}

}};
