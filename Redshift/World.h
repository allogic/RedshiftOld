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
#include <Redshift/Event.h>
#include <Redshift/Texture.h>
#include <Redshift/Material.h>

#include <Redshift/Renderer/DebugRenderer.h>
#include <Redshift/Renderer/PhysicalBasedRenderer.h>

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

  public:
    inline void SetWindowWidth(U32 width) { mWindowWidth = width; }
    inline void SetWindowHeight(U32 height) { mWindowHeight = height; }

  public:
    void Update(R32 timeDelta);

  private:
    GLFWwindow* mGlfwContext{};
    ImGuiContext* mImGuiContext{};

    U32 mWindowWidth{};
    U32 mWindowHeight{};

    /*
    * Module specific
    */

  public:
    inline std::map<std::string, ModuleProxy> const& GetModules() const { return mModules; }

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
    inline std::map<std::string, Shader> const& GetShaders() const { return mShaders; }
    inline Shader& GetShader(std::string const& shaderName) { return mShaders[shaderName]; }

  public:
    U32 ShaderCreate(std::string const& shaderName, std::string const& shaderFile);
    U32 ShaderDestroy(std::string const& shaderName);

  private:
    std::map<std::string, Shader> mShaders{};

    /*
    * Material specific
    */

  public:
    inline std::map<std::string, Material> const& GetMaterials() const { return mMaterials; }
    inline Material& GetMaterial(std::string const& materialName) { return mMaterials[materialName]; }

  private:
    std::map<std::string, Material> mMaterials{};

    /*
    * Mesh specific
    */

  public:
    inline std::map<std::string, Mesh> const& GetMeshes() const { return mMeshes; }
    inline Mesh& GetMesh(std::string const& meshName) { return mMeshes[meshName]; }

  private:
    std::map<std::string, Mesh> mMeshes{};

    /*
    * Texture specific
    */

  public:
    inline std::map<std::string, Texture> const& GetTextures() const { return mTextures; }
    inline Texture& GetTexture(std::string const& textureName) { return mTextures[textureName]; }

  private:
    std::map<std::string, Texture> mTextures{};

    /*
    * Debug renderer specific
    */

  public:
    inline void DebugRender() { mDebugRenderer.Render(); }

  public:
    inline void DebugLine(R32V3 p0, R32V3 p1, R32V4 c) { mDebugRenderer.DebugLine(p0, p1, c); }
    inline void DebugBox(R32V3 p, R32V3 s, R32V4 c, R32Q r = R32Q{}) { mDebugRenderer.DebugBox(p, s, c, r); }

  private:
    DebugRenderer mDebugRenderer{ this };

    /*
    * Physical based renderer specific
    */

  public:
    inline void PbRender() { mPhysicalBasedRenderer.Render(); }

  private:
    PhysicalBasedRenderer mPhysicalBasedRenderer{ this };

    /*
    * Event specific
    */

  public:
    inline void PollEvents() { mEvent.Poll(); }

  public:
    inline U32 KeyDown(U32 key) const { return mEvent.KeyDown(key); }
    inline U32 KeyHeld(U32 key) const { return mEvent.KeyHeld(key); }
    inline U32 KeyUp(U32 key) const { return mEvent.KeyUp(key); }

  public:
    inline U32 MouseDown(U32 key) const { return mEvent.MouseDown(key); }
    inline U32 MouseHeld(U32 key) const { return mEvent.MouseHeld(key); }
    inline U32 MouseUp(U32 key) const { return mEvent.MouseUp(key); }

  public:
    inline R32V2 const& GetMousePosition() const { return mEvent.GetMousePosition(); }

  public:
    inline void SetMousePosition(R32V2 position) { mEvent.SetMousePosition(position); }

  private:
    Event mEvent{ this };
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