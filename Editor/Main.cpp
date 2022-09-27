#include <cstdio>
#include <format>

#include <Redshift/Types.h>
#include <Redshift/Debug.h>

#include <Editor/HotLoader.h>

#include <Vendor/Glad/glad.h>

#include <Vendor/Glfw/glfw3.h>

///////////////////////////////////////////////////////////
// Locals
///////////////////////////////////////////////////////////

static rsh::U32 sWindowWidth{ 1366 };
static rsh::U32 sWindowHeight{ 768 };

static rsh::U32 sFps{};
static rsh::U32 sRenderFps{ 60 };
static rsh::U32 sPhysicFps{ 60 };
static rsh::U32 sHotLoadFps{ 1 };

static rsh::R32 sTime{};
static rsh::R32 sTimePrev{};
static rsh::R32 sTimeDelta{};

static rsh::R32 sTimeFpsPrev{};
static rsh::R32 sTimeRenderPrev{};
static rsh::R32 sTimePhysicPrev{};
static rsh::R32 sTimeHotLoadPrev{};

///////////////////////////////////////////////////////////
// Debug callbacks
///////////////////////////////////////////////////////////

static void GlfwDebugCallback(rsh::I32 error, char const* message)
{
  RSH_LOG("{}", message);
}

static void GlDebugCallback(rsh::U32 source, rsh::U32 type, rsh::U32 id, rsh::U32 severity, rsh::I32 length, char const* msg, void const* userParam)
{
  switch (severity)
  {
    case GL_DEBUG_SEVERITY_NOTIFICATION: break;
    case GL_DEBUG_SEVERITY_LOW: RSH_LOG("Severity:Low Type:0x%x Message:%s\n", type, msg); break;
    case GL_DEBUG_SEVERITY_MEDIUM: RSH_LOG("Severity:Medium Type:0x%x Message:%s\n", type, msg); break;
    case GL_DEBUG_SEVERITY_HIGH: RSH_LOG("Severity:High Type:0x%x Message:%s\n", type, msg); break;
  }
}

///////////////////////////////////////////////////////////
// Entry point
///////////////////////////////////////////////////////////

rsh::I32 main()
{
  glfwSetErrorCallback(GlfwDebugCallback);

  if (glfwInit())
  {
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_SAMPLES, 0);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow* window{ glfwCreateWindow(sWindowWidth, sWindowHeight, "", nullptr, nullptr) };

    if (window)
    {
      glfwMakeContextCurrent(window);

      if (gladLoadGL())
      {
        glEnable(GL_DEBUG_OUTPUT);
        glDebugMessageCallback(GlDebugCallback, 0);

        glfwSwapInterval(0);

        while (!glfwWindowShouldClose(window))
        {
          sTime = (rsh::R32)glfwGetTime();
          sTimeDelta = sTime - sTimePrev;
          sTimePrev = sTime;

          sFps++;
          if ((sTime - sTimeFpsPrev) > 1.0f)
          {
            sTimeFpsPrev = sTime;
            glfwSetWindowTitle(window, std::format("Editor Fps:{}", sFps).c_str());
            sFps = 0;
          }

          glfwPollEvents();

          glfwSwapBuffers(window);
        }
      }
      else
      {
        RSH_LOG("Failed initializing GL\n");
      }

      glfwDestroyWindow(window);

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