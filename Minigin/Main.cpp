#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#endif
#endif

#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "TextureComponent.h"
#include "TextComponent.h"
#include "Scene.h"
#include "FpsComponent.h"

static void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	// Create the background object
	auto backgroundTransformComponent{ std::make_unique<dae::TransformComponent>() };
	auto backgroundTextureComponent{ std::make_unique<dae::TextureComponent>("background.tga") };

	auto backgroundObject{ std::make_shared<dae::GameObject>() };
	backgroundObject->AddComponent(std::move(backgroundTransformComponent));
	backgroundObject->AddComponent(std::move(backgroundTextureComponent));
	scene.Add(backgroundObject);

	// Create the logo object
	auto logoTransformComponent{ std::make_unique<dae::TransformComponent>(216.f, 180.f) };
	auto logoTextureComponent{ std::make_unique<dae::TextureComponent>("logo.tga") };

	auto logoObject{ std::make_shared<dae::GameObject>() };
	logoObject->AddComponent(std::move(logoTransformComponent));
	logoObject->AddComponent(std::move(logoTextureComponent));
	scene.Add(logoObject);

	// Create the title object
	auto font{ dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36) };

	auto titleTransformComponent{ std::make_unique<dae::TransformComponent>(80.f, 20.f) };
	auto titleTextComponent{ std::make_unique<dae::TextComponent>("Programming 4 Assignment", font) };

	auto titleObject{ std::make_shared<dae::GameObject>() };
	titleObject->AddComponent(std::move(titleTransformComponent));
	titleObject->AddComponent(std::move(titleTextComponent));
	scene.Add(titleObject);

	// Create the FPS object
	font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 16);

	auto fpsTransformComponent{ std::make_unique<dae::TransformComponent>() };
	auto fpsTextComponent{ std::make_unique<dae::TextComponent>("FPS", font) };
	auto fpsComponent{ std::make_unique<dae::FpsComponent>() };

	auto fpsObject{ std::make_shared<dae::GameObject>() };
	fpsObject->AddComponent(std::move(fpsTransformComponent));
	fpsObject->AddComponent(std::move(fpsTextComponent));
	fpsObject->AddComponent(std::move(fpsComponent));
	scene.Add(fpsObject);
}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}