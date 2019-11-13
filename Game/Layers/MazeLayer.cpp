#include "pch.h"
#include "MazeLayer.h"
#include "Util/FileLoader.h"

MazeLayer::MazeLayer()
	: m_camera(m_player, Engine::Vec3(0.0f, 5.0f, -3.0f))
{
}

MazeLayer::~MazeLayer()
{
}

void MazeLayer::onAttach()
{
	/*   AXIS   y
				|   z
				|  /
				| /
		x_______|/

	*/

	// Shader
	auto& shader = Engine::AssetManager::getShaderLibrary().load("specular.glsl");

	m_maze = FileLoader::loadMaze("Assets/MazeFiles/maze.mz");

	Cube cube(1.0f);

	m_player.setVao(cube.getVao());
	m_player.setPosition(m_maze->getEntry());
	m_player.setScale(0.5f);

	Engine::AssetManager::getTexture2DLibrary().load("snow.jpg");
	Engine::AssetManager::getTexture2DLibrary().load("hedge.jpg");
	Engine::AssetManager::getTexture2DLibrary().load("ground.jpg");

	/// For clear color : https://www.toutes-les-couleurs.com/code-couleur-rvb.php
	Engine::RenderCommand::setClearColor(Engine::Color::Black);
	Engine::Input::toggleCursor();

	auto& openglShader = std::dynamic_pointer_cast<Engine::OpenGLShader>(shader);
	openglShader->bind();
	openglShader->uploadUniform("u_ambient", 0.5f);
	openglShader->uploadUniform("u_specular", 64.0f);
	openglShader->uploadUniform("u_light.color", Engine::Vec3(Engine::Color::White));
	openglShader->uploadUniform("u_light.direction", Engine::Vec3(0.0f, 1.0f, 1.0f));
}

void MazeLayer::onDetach()
{
}

void MazeLayer::onUpdate(const double& delta)
{
	m_player.onUpdate(delta);

	m_camera.onUpdate(delta);

	// --- Rendering ---
	Engine::RenderCommand::clear();

	Engine::Renderer::BeginScene(m_camera);

	//auto& snow = Engine::AssetManager::getTexture2DLibrary().get("snow");
	//auto& ground = Engine::AssetManager::getTexture2DLibrary().get("ground");
	//auto& wall = Engine::AssetManager::getTexture2DLibrary().get("hedge");
	auto& shader  = Engine::AssetManager::getShaderLibrary().get("specular");
	auto& openglShader = std::dynamic_pointer_cast<Engine::OpenGLShader>(shader);

	Engine::Color* drawColor;

	//wall->bind();
	
	openglShader->bind();
	openglShader->uploadUniform("u_cameraPosition", m_camera.getPosition());
	
	/* Draw Walls */
	drawColor = &Engine::Color::Navy;
	openglShader->uploadUniform("u_color", *drawColor);
	
	for (auto& cube : m_maze->getWalls())
	{
		Engine::Renderer::Submit(
			openglShader,
			cube->getVao(),
			cube->getTransform()
		);
	}

	//snow->bind();

	/* Draw Floor */
	drawColor = &Engine::Color::Teal;
	openglShader->uploadUniform("u_color", *drawColor);
	
	for (auto& cube : m_maze->getGround())
	{
		Engine::Renderer::Submit(
			openglShader,
			cube->getVao(),
			cube->getTransform()
		);
	}

	//ground->bind()

	/* Draw Player */
	drawColor = m_player.isColliding() ? &Engine::Color::Red : &Engine::Color::Yellow;
	openglShader->uploadUniform("u_color", *drawColor);

	Engine::Renderer::Submit(
		openglShader,
		m_player.getVao(),
		m_player.getTransform()
	);

	Engine::Renderer::EndScene();
	// -----------------
}

void MazeLayer::onEvent(Engine::Event& event)
{
	m_camera.onEvent(event);
	m_player.onEvent(event);
}
