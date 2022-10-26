#include <Redshift/Event.h>
#include <Redshift/World.h>

#include <Vendor/Glfw/glfw3.h>

///////////////////////////////////////////////////////////
// Event implementation
///////////////////////////////////////////////////////////

namespace rsh
{
  Event::Event(World* world)
    : mWorld{ world }
  {

  }

  void Event::Poll()
  {
    glfwPollEvents();

    for (U32 i{ GLFW_KEY_SPACE }; i < GLFW_KEY_LAST; i++)
    {
      I32 action{ glfwGetKey(mWorld->GetGlfwContext(), i)};

      mKeyboardKeys[i].Prev = mKeyboardKeys[i].Curr;

      if (action == GLFW_PRESS)
      {
        if (mKeyboardKeys[i].Curr != eEventStateDown && mKeyboardKeys[i].Prev != eEventStateHeld)
        {
          mKeyboardKeys[i].Curr = eEventStateDown;
        }
        else
        {
          mKeyboardKeys[i].Curr = eEventStateHeld;
        }
      }

      if (action == GLFW_RELEASE)
      {
        if (mKeyboardKeys[i].Curr != eEventStateUp && mKeyboardKeys[i].Prev == eEventStateHeld)
        {
          mKeyboardKeys[i].Curr = eEventStateUp;
        }
        else
        {
          mKeyboardKeys[i].Curr = eEventStateNone;
        }
      }
    }

    for (U32 i{}; i < GLFW_MOUSE_BUTTON_LAST; i++)
    {
      I32 action{ glfwGetMouseButton(mWorld->GetGlfwContext(), i)};

      mMouseKeys[i].Prev = mMouseKeys[i].Curr;

      if (action == GLFW_PRESS)
      {
        if (mMouseKeys[i].Curr != eEventStateDown && mMouseKeys[i].Prev != eEventStateHeld)
        {
          mMouseKeys[i].Curr = eEventStateDown;
        }
        else
        {
          mMouseKeys[i].Curr = eEventStateHeld;
        }
      }

      if (action == GLFW_RELEASE)
      {
        if (mMouseKeys[i].Curr != eEventStateUp && mMouseKeys[i].Prev == eEventStateHeld)
        {
          mMouseKeys[i].Curr = eEventStateUp;
        }
        else
        {
          mMouseKeys[i].Curr = eEventStateNone;
        }
      }
    }
  }
}