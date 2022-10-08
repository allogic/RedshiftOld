#include <Redshift/Event.h>

#include <Vendor/Glfw/glfw3.h>

namespace rsh
{
  static Event::EventRecord sKeyboardKeys[GLFW_KEY_LAST];
  static Event::EventRecord sMouseKeys[GLFW_MOUSE_BUTTON_LAST];

  void Event::Poll(GLFWwindow* context)
  {
    glfwPollEvents();

    for (U32 i{ GLFW_KEY_SPACE }; i < GLFW_KEY_LAST; i++)
    {
      I32 action{ glfwGetKey(context, i) };

      sKeyboardKeys[i].Prev = sKeyboardKeys[i].Curr;

      if (action == GLFW_PRESS)
      {
        if (sKeyboardKeys[i].Curr != eEventStateDown && sKeyboardKeys[i].Prev != eEventStateHeld)
        {
          sKeyboardKeys[i].Curr = eEventStateDown;
        }
        else
        {
          sKeyboardKeys[i].Curr = eEventStateHeld;
        }
      }

      if (action == GLFW_RELEASE)
      {
        if (sKeyboardKeys[i].Curr != eEventStateUp && sKeyboardKeys[i].Prev == eEventStateHeld)
        {
          sKeyboardKeys[i].Curr = eEventStateUp;
        }
        else
        {
          sKeyboardKeys[i].Curr = eEventStateNone;
        }
      }
    }

    for (U32 i{}; i < GLFW_MOUSE_BUTTON_LAST; i++)
    {
      I32 action{ glfwGetMouseButton(context, i) };

      sMouseKeys[i].Prev = sMouseKeys[i].Curr;

      if (action == GLFW_PRESS)
      {
        if (sMouseKeys[i].Curr != eEventStateDown && sMouseKeys[i].Prev != eEventStateHeld)
        {
          sMouseKeys[i].Curr = eEventStateDown;
        }
        else
        {
          sMouseKeys[i].Curr = eEventStateHeld;
        }
      }

      if (action == GLFW_RELEASE)
      {
        if (sMouseKeys[i].Curr != eEventStateUp && sMouseKeys[i].Prev == eEventStateHeld)
        {
          sMouseKeys[i].Curr = eEventStateUp;
        }
        else
        {
          sMouseKeys[i].Curr = eEventStateNone;
        }
      }
    }
  }

  U32 Event::KeyDown(U32 key)
  {
    return sKeyboardKeys[key].Curr == eEventStateDown;
  }

  U32 Event::KeyHeld(U32 key)
  {
    return sKeyboardKeys[key].Curr == eEventStateHeld;
  }

  U32 Event::KeyUp(U32 key)
  {
    return sKeyboardKeys[key].Curr == eEventStateUp;
  }

  U32 Event::MouseDown(U32 key)
  {
    return sMouseKeys[key].Curr == eEventStateDown;
  }

  U32 Event::MouseHeld(U32 key)
  {
    return sMouseKeys[key].Curr == eEventStateHeld;
  }

  U32 Event::MouseUp(U32 key)
  {
    return sMouseKeys[key].Curr == eEventStateUp;
  }
}