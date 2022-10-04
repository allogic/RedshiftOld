#include <cstdio>

#include <Redshift/Types.h>
#include <Redshift/Debug.h>
#include <Redshift/World.h>
#include <Redshift/Event.h>

#include <Editor/HotLoader.h>

#include <Vendor/Glad/glad.h>

#include <Vendor/Glfw/glfw3.h>

using namespace rsh;

///////////////////////////////////////////////////////////
// Locals
///////////////////////////////////////////////////////////

static U32 const sEditorWidth{ 1280 };
static U32 const sEditorHeight{ 720 };

static GLFWwindow* sWindow{};
static World* sWorld{};

static U32 sFps{};
static U32 sRenderFps{ 60 };
static U32 sPhysicFps{ 60 };
static U32 sHotLoadFps{ 1 };

static R32 sTime{};
static R32 sTimePrev{};
static R32 sTimeDelta{};

static R32 sTimeFpsPrev{};
static R32 sTimeRenderPrev{};
static R32 sTimePhysicPrev{};
static R32 sTimeHotLoadPrev{};

///////////////////////////////////////////////////////////
// Glfw callbacks
///////////////////////////////////////////////////////////

static void GlfwDebugProc(I32 error, char const* message)
{
  RSH_LOG("%s\n", message);
}
static void GlfwResizeProc(GLFWwindow* window, I32 width, I32 height)
{
  if (sWorld)
  {
    sWorld->SetEditorWidth((U32)width);
    sWorld->SetEditorHeight((U32)height);
  }
}
static void GlfwMouseProc(GLFWwindow* window, R64 x, R64 y)
{
  if (sWorld)
  {
    sWorld->SetMousePosition(R32V2{ x, y });
  }
}

///////////////////////////////////////////////////////////
// Gl callbacks
///////////////////////////////////////////////////////////

static void GlDebugCallback(U32 source, U32 type, U32 id, U32 severity, I32 length, char const* msg, void const* userParam)
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
// Main loop abstraction
///////////////////////////////////////////////////////////

static void UpdateFps()
{
  sFps++;
  if ((sTime - sTimeFpsPrev) > 1.0f)
  {
    sTimeFpsPrev = sTime;
    glfwSetWindowTitle(sWindow, std::string{ std::string{ "Editor Fps:" } + std::to_string(sFps) }.c_str());
    sFps = 0;
  }
}

static void UpdateHotLoader(HotLoader& hotLoader)
{
  if ((sTime - sTimeHotLoadPrev) > (1.0f / sHotLoadFps))
  {
    sTimeHotLoadPrev = sTime;
    hotLoader.Update();
  }
}

///////////////////////////////////////////////////////////
// Entry point
///////////////////////////////////////////////////////////

I32 main()
{
  glfwSetErrorCallback(GlfwDebugProc);

  if (glfwInit())
  {
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_SAMPLES, 0);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    sWindow = glfwCreateWindow(sEditorWidth, sEditorHeight, "", nullptr, nullptr);

    if (sWindow)
    {
      glfwSetWindowSizeCallback(sWindow, GlfwResizeProc);
      glfwSetCursorPosCallback(sWindow, GlfwMouseProc);

      glfwMakeContextCurrent(sWindow);

      if (gladLoadGL())
      {
        glEnable(GL_DEBUG_OUTPUT);
        glDebugMessageCallback(GlDebugCallback, 0);

        glfwSwapInterval(0);

        World world{ sEditorWidth, sEditorHeight };
        HotLoader hotLoader{
          &world,
          SCENE_DIR, SCENE_EXT, SCENE_STREAMING_DIR,
          SHADER_DIR, SHADER_EXT, SHADER_STREAMING_DIR,
        };

        sWorld = &world;
        while (!glfwWindowShouldClose(sWindow))
        {
          sTime = (R32)glfwGetTime();
          sTimeDelta = sTime - sTimePrev;
          sTimePrev = sTime;

          UpdateFps();
          UpdateHotLoader(hotLoader);
          
          world.Update(sTimeDelta);

          glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
          glClear(GL_COLOR_BUFFER_BIT);
          glViewport(0, 0, world.GetEditorWidth(), world.GetEditorHeight());

          world.DebugRender();

          Event::Poll(sWindow);

          glfwSwapBuffers(sWindow);
        }
        sWorld = nullptr;
      }
      else
      {
        RSH_LOG("Failed initializing GL\n");
      }

      glfwDestroyWindow(sWindow);
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