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
	auto backgroundObject{ std::make_shared<dae::GameObject>() };

	auto backgroundTransformComponent{ std::make_unique<dae::TransformComponent>(*backgroundObject.get()) };
	backgroundObject->AddComponent(std::move(backgroundTransformComponent));

	auto backgroundTextureComponent{ std::make_unique<dae::TextureComponent>(*backgroundObject.get(), "background.tga") };
	backgroundObject->AddComponent(std::move(backgroundTextureComponent));
	scene.Add(backgroundObject);

	// Create the logo object
	auto logoObject{ std::make_shared<dae::GameObject>() };

	auto logoTransformComponent{ std::make_unique<dae::TransformComponent>(*logoObject.get(), 216.f, 180.f) };
	logoObject->AddComponent(std::move(logoTransformComponent));

	auto logoTextureComponent{ std::make_unique<dae::TextureComponent>(*logoObject.get(), "logo.tga") };
	logoObject->AddComponent(std::move(logoTextureComponent));

	scene.Add(logoObject);

	// Create the title object
	auto titleObject{ std::make_shared<dae::GameObject>() };
	auto titleTransformComponent{ std::make_unique<dae::TransformComponent>(*titleObject.get(), 80.f, 20.f) };
	titleObject->AddComponent(std::move(titleTransformComponent));

	auto font{ dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36) };
	auto titleTextComponent{ std::make_unique<dae::TextComponent>(*titleObject.get(), "Programming 4 Assignment", font) };
	titleObject->AddComponent(std::move(titleTextComponent));

	scene.Add(titleObject);

	// Create the FPS object
	font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 16);

	auto fpsObject{ std::make_shared<dae::GameObject>() };
	auto fpsTransformComponent{ std::make_unique<dae::TransformComponent>(*fpsObject.get()) };
	fpsObject->AddComponent(std::move(fpsTransformComponent));
	auto fpsTextComponent{ std::make_unique<dae::TextComponent>(*fpsObject.get(), "FPS", font) };
	fpsObject->AddComponent(std::move(fpsTextComponent));
	auto fpsComponent{ std::make_unique<dae::FpsComponent>(*fpsObject.get()) };
	fpsObject->AddComponent(std::move(fpsComponent));
	scene.Add(fpsObject);
}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}