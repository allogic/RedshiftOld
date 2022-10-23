#include <cstdio>

#include <Redshift/Types.h>
#include <Redshift/Debug.h>
#include <Redshift/World.h>

#include <Runtime/HotLoader.h>

#include <Vendor/Glad/glad.h>

#include <Vendor/Glfw/glfw3.h>

#include <Vendor/ImGui/imgui.h>
#include <Vendor/ImGui/imgui_impl_glfw.h>
#include <Vendor/ImGui/imgui_impl_opengl3.h>

using namespace rsh;

///////////////////////////////////////////////////////////
// Locals
///////////////////////////////////////////////////////////

static U32 const sWindowWidth{ 1920 };
static U32 const sWindowHeight{ 1080 };

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
static void GlfwResizeProc(GLFWwindow* context, I32 width, I32 height)
{
  if (sWorld)
  {
    sWorld->SetWindowWidth((U32)width);
    sWorld->SetWindowHeight((U32)height);
  }
}
static void GlfwMouseProc(GLFWwindow* context, R64 x, R64 y)
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

static void UpdateFps(GLFWwindow* context)
{
  sFps++;
  if ((sTime - sTimeFpsPrev) > 1.0f)
  {
    sTimeFpsPrev = sTime;
    glfwSetWindowTitle(context, std::string{ std::string{ "Redshift Fps:" } + std::to_string(sFps) }.c_str());
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

    GLFWwindow* glfwContext = glfwCreateWindow(sWindowWidth, sWindowHeight, "", nullptr, nullptr);

    if (glfwContext)
    {
      glfwSetWindowSizeCallback(glfwContext, GlfwResizeProc);
      glfwSetCursorPosCallback(glfwContext, GlfwMouseProc);

      glfwMakeContextCurrent(glfwContext);
      glfwSwapInterval(0);

      if (gladLoadGL())
      {
        glEnable(GL_DEBUG_OUTPUT);
        glDebugMessageCallback(GlDebugCallback, 0);

        IMGUI_CHECKVERSION();
        ImGuiContext* imGuiContext{ ImGui::CreateContext() };

        ImGuiIO& imGuiIo{ ImGui::GetIO() };
        imGuiIo.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        imGuiIo.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        imGuiIo.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

        ImGuiStyle& imGuiStyle{ ImGui::GetStyle() };
        imGuiStyle.WindowRounding = 0.0f;
        imGuiStyle.FrameBorderSize = 0.0f;
        imGuiStyle.Colors[ImGuiCol_WindowBg].w = 1.0f;

        ImGui_ImplGlfw_InitForOpenGL(glfwContext, 1);
        ImGui_ImplOpenGL3_Init("#version 450 core");

        World world{ sWindowWidth, sWindowHeight };
        HotLoader hotLoader{
          &world,
          MODULE_DIR, MODULE_EXT, MODULE_STREAMING_DIR,
          SHADER_DIR, SHADER_EXT, SHADER_STREAMING_DIR,
        };

        sWorld = &world;
        while (!glfwWindowShouldClose(glfwContext))
        {
          sTime = (R32)glfwGetTime();
          sTimeDelta = sTime - sTimePrev;
          sTimePrev = sTime;

          glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
          glClear(GL_COLOR_BUFFER_BIT);
          glViewport(0, 0, world.GetWindowWidth(), world.GetWindowHeight());

          UpdateFps(glfwContext);
          UpdateHotLoader(hotLoader);
          
          ImGui_ImplGlfw_NewFrame();
          ImGui_ImplOpenGL3_NewFrame();

          ImGui::NewFrame();
          ImGui::DockSpaceOverViewport(ImGui::GetMainViewport(), ImGuiDockNodeFlags_PassthruCentralNode);

          world.PollEvents();
          world.Update(sTimeDelta);
          world.DebugRender();

          ImGui::Render();

          ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

          ImGui::UpdatePlatformWindows();
          ImGui::RenderPlatformWindowsDefault();

          glfwMakeContextCurrent(glfwContext);
          glfwSwapBuffers(glfwContext);
        }
        sWorld = nullptr;

        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();

        ImGui::DestroyContext(imGuiContext);
      }
      else
      {
        RSH_LOG("Failed initializing GL\n");
      }

      glfwDestroyWindow(glfwContext);
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