#ifndef RSH_EVENTS_H
#define RSH_EVENTS_H

#include <Redshift/Types.h>

///////////////////////////////////////////////////////////
// Event definition
///////////////////////////////////////////////////////////

namespace rsh
{
  class World;

  class Events
  {
  public:
    enum KeyCode
    {
      eKeyCodeA = 65,
      eKeyCodeB = 66,
      eKeyCodeC = 67,
      eKeyCodeD = 68,
      eKeyCodeE = 69,
      eKeyCodeF = 70,
      eKeyCodeG = 71,
      eKeyCodeH = 72,
      eKeyCodeI = 73,
      eKeyCodeJ = 74,
      eKeyCodeK = 75,
      eKeyCodeL = 76,
      eKeyCodeM = 77,
      eKeyCodeN = 78,
      eKeyCodeO = 79,
      eKeyCodeP = 80,
      eKeyCodeQ = 81,
      eKeyCodeR = 82,
      eKeyCodeS = 83,
      eKeyCodeT = 84,
      eKeyCodeU = 85,
      eKeyCodeV = 86,
      eKeyCodeW = 87,
      eKeyCodeX = 88,
      eKeyCodeY = 89,
      eKeyCodeZ = 90,
    };

    enum MouseCode
    {
      eMouseCode1 = 0,
      eMouseCode2 = 1,
      eMouseCode3 = 2,
      eMouseCode4 = 3,
      eMouseCode5 = 4,
      eMouseCode6 = 5,
      eMouseCode7 = 6,
      eMouseCode8 = 7,
      eMouseCodeLeft = 0,
      eMouseCodeRight = 1,
      eMouseCodeMiddle = 2,
    };

  private:
    enum EventState
    {
      eEventStateNone,
      eEventStateDown,
      eEventStateHeld,
      eEventStateUp,
    };

    struct EventRecord
    {
      EventState Curr;
      EventState Prev;
    };

  public:
    Events(World* world);

  public:
    void Poll();

  public:
    inline U32 KeyDown(U32 key) const { return mKeyboardKeys[key].Curr == eEventStateDown; }
    inline U32 KeyHeld(U32 key) const { return mKeyboardKeys[key].Curr == eEventStateHeld; }
    inline U32 KeyUp(U32 key) const { return mKeyboardKeys[key].Curr == eEventStateUp; }

  public:
    inline U32 MouseDown(U32 key) const { return mMouseKeys[key].Curr == eEventStateDown; }
    inline U32 MouseHeld(U32 key) const { return mMouseKeys[key].Curr == eEventStateHeld; }
    inline U32 MouseUp(U32 key) const { return mMouseKeys[key].Curr == eEventStateUp; }

  private:
    World* mWorld{};

    EventRecord mKeyboardKeys[348];
    EventRecord mMouseKeys[7];
  };
}

#endif