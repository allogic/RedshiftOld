#include <cstdio>

#include <Redshift/Types.h>
#include <Redshift/Debug.h>

#include <Vendor/Glfw/glfw3.h>
#include <Vendor/Glad/glad.h>

///////////////////////////////////////////////////////////
// Locals
///////////////////////////////////////////////////////////

static rsh::U32 sWindowWidth{ 1366 };
static rsh::U32 sWindowHeight{ 768 };

///////////////////////////////////////////////////////////
// Debug callbacks
///////////////////////////////////////////////////////////

static void GlfwErrorCallback(rsh::I32 error, const char* message)
{
  RSH_LOG(message);
}

///////////////////////////////////////////////////////////
// Entry point
///////////////////////////////////////////////////////////

rsh::I32 main()
{
  if (glfwInit())
  {
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_SAMPLES, 0);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow* window{ glfwCreateWindow(sWindowWidth, sWindowHeight, "Redshift", nullptr, nullptr)};

    if (window)
    {
      glfwMakeContextCurrent(window);

      if (gladLoadGL())
      {

      }
      else
      {
        RSH_LOG("Failed initializing GL\n");
      }

      glfwTerminate();
    }
    else
    {
      RSH_LOG("Failed creating window\n");
    }
  }
  else
  {
    RSH_LOG("Failed initializing GLFW\n");
  }

  return 0;
}