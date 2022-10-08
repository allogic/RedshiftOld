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
  class World
  {
    /*
    * Constructor/Destructor
    */

  public:
    World(U32 editorWidth, U32 editorHeight);
    virtual ~World();

    /*
    * Global specific
    */

  public:
    inline GLFWwindow* GetGlfwContext() const { return mGlfwContext; }
    inline ImGuiContext* GetImGuiContext() const { return mImGuiContext; }

    inline U32 GetEditorWidth() { return mEditorWidth; }
    inline U32 GetEditorHeight() { return mEditorHeight; }

    inline R32V2 GetMousePosition() { return mMousePosition; }

  public:
    inline void SetEditorWidth(U32 width) { mEditorWidth = width; }
    inline void SetEditorHeight(U32 height) { mEditorHeight = height; }

    inline void SetMousePosition(R32V2 position) { mMousePosition = position; }

  public:
    void Update(R32 timeDelta);

  private:
    GLFWwindow* mGlfwContext{};
    ImGuiContext* mImGuiContext{};

    U32 mEditorWidth{};
    U32 mEditorHeight{};

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
    inline Actor* GetActor(std::string const& actorName) { return mActors[actorName]; }
    inline void SetMainActor(Actor* actor) { mMainActor = actor; }
    inline Actor* GetMainActor() { return mMainActor; }
    void ActorDestroy(Actor* actor);
    void ActorDestroy(std::string const& actorName);

  private:
    std::map<std::string, Actor*> mActors{};

    Actor* mMainActor{};

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