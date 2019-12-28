#include "pch.h"
#include "MapLayer.h"
#include "Util/FileLoader.h"

MapLayer::MapLayer()
	: mPlayer(Engine::AssetManager::GetModelLibrary().Load("nanosuit/nanosuit.obj", "player"))
	, mCamera(mPlayer)
	, mSkybox(std::make_shared<Engine::Skybox>("Skyboxes/Day", "skybox"))
{
}

MapLayer::~MapLayer()
{
}

void MapLayer::OnAttach()
{
	/*   AXIS   y
				|   z
				|  /
				| /
		x_______|/

	*/

	mMap = FileLoader::LoadMap("Assets/MapFiles/maze.map");
	
	mPlayer.SetPosition(mMap->GetEntry());
	mPlayer.SetScale(0.05f);
	
	// Shader
	auto& shader		 = Engine::AssetManager::GetShaderLibrary().Load("lights_materials.glsl", "scene");
	auto& shaderPBR		 = Engine::AssetManager::GetShaderLibrary().Load("lights_PBR.glsl", "player");
	auto& shaderSkybox	 = Engine::AssetManager::GetShaderLibrary().Load("skybox.glsl");
	Engine::AssetManager::GetShaderLibrary().Load("colliders.glsl", "collider");


	Engine::AssetManager::GetTexture2DLibrary().Load("snow.jpg");
	Engine::AssetManager::GetTexture2DLibrary().Load("hedge.jpg");
	Engine::AssetManager::GetTexture2DLibrary().Load("floor.jpg");

	// Lights
	mLights.push_back(std::make_shared<Engine::DirectionalLight>(Engine::Vec3(0.7f, -1.0f, .0f)));
	
	for (unsigned int i = 0; i < mLights.size(); ++i)
	{
		mLights[i]->Load(shader, i);
		mLights[i]->Load(shaderPBR, i);
	}

	// Skybox
	mSkybox->Load(shaderSkybox);

	/// For Clear color : https://www.toutes-les-couleurs.com/code-couleur-rvb.php
	Engine::RenderCommand::SetClearColor(Engine::Color::Aqua);
	Engine::Input::ToggleCursor();
}

void MapLayer::OnDetach()
{
}

void MapLayer::OnUpdate(const double& delta)
{
	mPlayer.OnUpdate(delta);

	mCamera.OnUpdate(delta);

	// Textures
	auto& snow  = Engine::AssetManager::GetTexture2DLibrary().Get("snow");
	auto& floor = Engine::AssetManager::GetTexture2DLibrary().Get("floor");
	auto& wall  = Engine::AssetManager::GetTexture2DLibrary().Get("hedge");

	// Shader
	auto shader			  = Engine::AssetManager::GetShaderLibrary().Get("scene");
	auto shaderPBR	      = Engine::AssetManager::GetShaderLibrary().Get("player");
	auto shader_collider  = Engine::AssetManager::GetShaderLibrary().Get("collider");
	auto shaderSkybox	  = Engine::AssetManager::GetShaderLibrary().Load("skybox");
	auto openglShader     = std::dynamic_pointer_cast<Engine::OpenGLShader>(shader);
	auto openglShaderPBR  = std::dynamic_pointer_cast<Engine::OpenGLShader>(shaderPBR);

	// Model
		// Loaded in player.cpp
	auto player = Engine::AssetManager::GetModelLibrary().Get("player");
		// Loaded in Map.cpp
	auto cube   = Engine::AssetManager::GetModelLibrary().Get("cube");
	
	// Materials
	Engine::Ref<Engine::Material> material;
	
	// --- Rendering ---
	
	Engine::RenderCommand::Clear();

	Engine::Renderer::BeginScene(mCamera, shader);

	// Draw Walls
	material = std::make_shared<Engine::RawMaterial>(Engine::RawMaterial::Emerald);
	cube->SetMaterial(material);

	for (auto& wall : mMap->GetWalls())
	{
		Engine::Renderer::Submit(*wall.GetModel(), wall.GetTransform());
	}

	// Draw Floor
	for (auto& floor : mMap->GetFloor())
	{
		Engine::Renderer::Submit(*floor.GetModel() , floor.GetTransform());
	}
	
	Engine::Renderer::EndScene();

	// -----------------
	
	Engine::Renderer::BeginScene(mCamera, shaderPBR);
	
	// Draw Player
	Engine::Renderer::Submit(*player, mPlayer.GetTransform());

	Engine::Renderer::EndScene();
	
	// -----------------

	Engine::Renderer::BeginScene(mCamera, shader_collider);
	
	Engine::Renderer::Submit(*cube, mPlayer.GetComponent<Engine::BoxCollider>());

	Engine::Renderer::EndScene();

	// -----------------

	// Skybox
	Engine::Renderer::BeginScene(mCamera, shaderSkybox);

	Engine::Renderer::Submit(*mSkybox);

	Engine::Renderer::EndScene();

	// -----------------
}

void MapLayer::OnEvent(Engine::Event& event)
{
	mCamera.OnEvent(event);
	mPlayer.OnEvent(event);
}
