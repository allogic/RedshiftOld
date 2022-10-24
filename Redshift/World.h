#ifndef RSH_WORLD_H
#define RSH_WORLD_H

#include <string>
#include <vector>
#include <map>

#include <Redshift/Types.h>
#include <Redshift/Module.h>
#include <Redshift/Actor.h>
#include <Redshift/Shader.h>
#include <Redshift/Mesh.h>
#include <Redshift/Events.h>

#include <Redshift/Renderer/DebugRenderer.h>
#include <Redshift/Renderer/PbRenderer.h>

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
    template<typename A, typename ... Args>
    A* ActorCreate(std::string const& actorName, Actor* parent, Args&& ... args);
    void ActorDestroy(Actor* actor);

  public:
    inline std::vector<Actor*> const& GetActors() const { return mActors; }
    inline Actor* GetMainEditorActor() const { return mMainEditorActor; }
    inline Actor* GetMainGameActor() const { return mMainGameActor; }

  public:
    inline void SetMainEditorActor(Actor* actor) { mMainEditorActor = actor; }
    inline void SetMainGameActor(Actor* actor) { mMainGameActor = actor; }

  private:
    std::vector<Actor*> mActors{};

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
    inline Mesh& GetMesh(std::string const& meshName) { return mMeshes[meshName]; }

  private:
    std::map<std::string, Mesh> mMeshes{};

    /*
    * Debug specific
    */

  private:
    DebugRenderer mDebugRenderer{ this };

  public:
    inline void DebugRender() { mDebugRenderer.Render(); }

  public:
    inline void DebugLine(R32V3 p0, R32V3 p1, R32V4 c) { mDebugRenderer.DebugLine(p0, p1, c); }
    inline void DebugBox(R32V3 p, R32V3 s, R32V4 c, R32Q r = R32Q{}) { mDebugRenderer.DebugBox(p, s, c, r); }

    /*
    * PBR specific
    */

  private:
    PbRenderer mPbRenderer{ this };

  public:
    inline void PbRender() { mPbRenderer.Render(); }

    /*
    * Event specific
    */

  private:
    Events mEvents{ this };

  public:
    inline void PollEvents() { mEvents.Poll(); }

  public:
    inline U32 KeyDown(U32 key) const { return mEvents.KeyDown(key); }
    inline U32 KeyHeld(U32 key) const { return mEvents.KeyHeld(key); }
    inline U32 KeyUp(U32 key) const { return mEvents.KeyUp(key); }

  public:
    inline U32 MouseDown(U32 key) const { return mEvents.MouseDown(key); }
    inline U32 MouseHeld(U32 key) const { return mEvents.MouseHeld(key); }
    inline U32 MouseUp(U32 key) const { return mEvents.MouseUp(key); }
  };
}

///////////////////////////////////////////////////////////
// World implementation
///////////////////////////////////////////////////////////

template<typename A, typename ... Args>
A* rsh::World::ActorCreate(std::string const& actorName, Actor* parent, Args&& ... args)
{
  Actor* actor{ mActors.emplace_back(new A{ this, actorName, std::forward<Args>(args) ... }) };
  if (parent)
  {
    actor->SetParent(parent);
    parent->AddChild(actor);
  }
  return (A*)actor;
}

#endif