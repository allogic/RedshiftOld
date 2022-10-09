#ifndef RSH_WORLD_H
#define RSH_WORLD_H

#include <string>
#include <map>

#include <Redshift/Types.h>
#include <Redshift/Module.h>
#include <Redshift/Actor.h>
#include <Redshift/Vertex.h>
#include <Redshift/Shader.h>
#include <Redshift/Mesh.h>

///////////////////////////////////////////////////////////
// World definition
///////////////////////////////////////////////////////////

struct GLFWwindow;
struct ImGuiContext;

namespace rsh
{
  class Camera;

  class World
  {
    /*
    * Constructor/Destructor
    */

  public:
    World(U32 windowWidth, U32 windowHeight);
    virtual ~World();

    /*
    * Global specific
    */

  public:
    inline GLFWwindow* GetGlfwContext() const { return mGlfwContext; }
    inline ImGuiContext* GetImGuiContext() const { return mImGuiContext; }

    inline U32 GetWindowWidth() const { return mWindowWidth; }
    inline U32 GetWindowHeight() const { return mWindowHeight; }
    inline R32 GetAspectRatio() const { return (R32)mWindowWidth / mWindowHeight; }

    inline R32V2 GetMousePosition() { return mMousePosition; }

  public:
    inline void SetWindowWidth(U32 width) { mWindowWidth = width; }
    inline void SetWindowHeight(U32 height) { mWindowHeight = height; }

    inline void SetMousePosition(R32V2 position) { mMousePosition = position; }

  public:
    void Update(R32 timeDelta);

  private:
    GLFWwindow* mGlfwContext{};
    ImGuiContext* mImGuiContext{};

    U32 mWindowWidth{};
    U32 mWindowHeight{};

    R32V2 mMousePosition{};

    /*
    * Module specific
    */

  public:
    U32 ModuleCreate(std::string const& moduleName, std::string const& moduleFile);
    U32 ModuleDestroy(std::string const& moduleName);

  private:
    void ModuleUnloadAll();

  private:
    std::map<std::string, ModuleProxy> mModules{};

    /*
    * Actor specific
    */

  public:
    template<typename A>
    A* ActorCreate(std::string const& actorName, Actor* parent = nullptr);
    void ActorDestroy(Actor* actor);
    void ActorDestroy(std::string const& actorName);

  public:
    inline std::map<std::string, Actor*> const& GetActors() const { return mActors; }
    inline Actor* GetActor(std::string const& actorName) { return mActors[actorName]; }
    inline Actor* GetMainEditorActor() const { return mMainEditorActor; }
    inline Actor* GetMainGameActor() const { return mMainGameActor; }

  public:
    inline void SetMainEditorActor(Actor* actor) { mMainEditorActor = actor; }
    inline void SetMainGameActor(Actor* actor) { mMainGameActor = actor; }

  private:
    std::map<std::string, Actor*> mActors{};

    Actor* mMainEditorActor{};
    Actor* mMainGameActor{};

    /*
    * Component specific
    */

  public:
    Camera* GetMainCamera() const;

    /*
    * Shader specific
    */

  public:
    U32 ShaderCreate(std::string const& shaderName, std::string const& shaderFile);
    inline Shader& GetShader(std::string const& shaderName) { return mShaders[shaderName]; }
    U32 ShaderDestroy(std::string const& shaderName);

  private:
    std::map<std::string, Shader> mShaders{};

    /*
    * Mesh specific
    */

  public:
    U32 MeshCreate(std::string const& meshName);
    inline Mesh& GetMesh(std::string const& meshName) { return mMeshes[meshName]; }
    U32 MeshDestroy(std::string const& meshName);

  private:
    std::map<std::string, Mesh> mMeshes{};

    /*
    * Event specific
    */

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
      eMouseCode1      = 0,
      eMouseCode2      = 1,
      eMouseCode3      = 2,
      eMouseCode4      = 3,
      eMouseCode5      = 4,
      eMouseCode6      = 5,
      eMouseCode7      = 6,
      eMouseCode8      = 7,
      eMouseCodeLeft   = 0,
      eMouseCodeRight  = 1,
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
    void PollEvents();

  private:
    EventRecord mKeyboardKeys[348];
    EventRecord mMouseKeys[7];

  public:
    inline U32 KeyDown(U32 key) const { return mKeyboardKeys[key].Curr == eEventStateDown; }
    inline U32 KeyHeld(U32 key) const { return mKeyboardKeys[key].Curr == eEventStateHeld; }
    inline U32 KeyUp(U32 key) const { return mKeyboardKeys[key].Curr == eEventStateUp; }

  public:
    inline U32 MouseDown(U32 key) const { return mMouseKeys[key].Curr == eEventStateDown; }
    inline U32 MouseHeld(U32 key) const { return mMouseKeys[key].Curr == eEventStateHeld; }
    inline U32 MouseUp(U32 key) const { return mMouseKeys[key].Curr == eEventStateUp; }

    /*
    * Debug specific
    */

  public:
    void DebugLine(R32V3 p0, R32V3 p1, R32V4 c);
    void DebugBox(R32V3 p, R32V3 s, R32V4 c, R32Q r = R32Q{});
    void DebugRender();

  private:
    U32 mDebugVertexBufferSize{ 65535 * 3 };
    U32 mDebugElementBufferSize{ mDebugVertexBufferSize * 2 };

    VertexDebug* mDebugVertexBuffer{ new VertexDebug[mDebugVertexBufferSize] };
    U32* mDebugElementBuffer{ new U32[mDebugElementBufferSize] };

    Mesh& mDebugMesh{ GetMesh("Debug").Create<VertexDebug, U32>(mDebugVertexBufferSize, mDebugVertexBuffer, mDebugElementBufferSize, mDebugElementBuffer) };
    Shader& mDebugShader{ GetShader("Debug") };

    U32 mDebugVertexOffset{};
    U32 mDebugElementOffset{};
  };
}

///////////////////////////////////////////////////////////
// Inline world implementation
///////////////////////////////////////////////////////////

template<typename A>
A* rsh::World::ActorCreate(std::string const& actorName, Actor* parent)
{
  auto const findIt{ mActors.find(actorName) };
  if (findIt == mActors.end())
  {
    auto const [emplaceIt, inserted] { mActors.emplace(actorName, new A{ this, actorName }) };
    if (parent)
    {
      Actor* actor{ emplaceIt->second };

      // Link actors
      actor->SetParent(parent);
      parent->AddChild(actor);

      // Apply parent transform
      actor->GetTransform()->ApplyTransform(parent->GetTransform());
    }
    return (A*)emplaceIt->second;
  }
  return (A*)findIt->second;
}

#endif