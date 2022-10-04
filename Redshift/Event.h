#ifndef RSH_EVENT_H
#define RSH_EVENT_H

#include <Redshift/Types.h>

struct GLFWwindow;

namespace rsh
{
  class Event
  {
  public:
    enum EventState
    {
      eEventStateNone,
      eEventStateDown,
      eEventStateHeld,
      eEventStateUp,
    };

  public:
    struct EventRecord
    {
      EventState Curr;
      EventState Prev;
    };

  public:
    static void Poll(GLFWwindow* window);

  public:
    static U32 KeyDown(U32 key);
    static U32 KeyHeld(U32 key);
    static U32 KeyUp(U32 key);

  public:
    static U32 MouseDown(U32 key);
    static U32 MouseHeld(U32 key);
    static U32 MouseUp(U32 key);
  };
}

#endif