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
	backgroundObject->AddComponent<dae::TextureComponent>("background.tga");
	scene.Add(backgroundObject);

	// Create the logo object
	auto logoObject{ std::make_shared<dae::GameObject>(std::move(dae::Transform(216.f, 180.f))) };
	logoObject->AddComponent<dae::TextureComponent>("logo.tga");
	scene.Add(logoObject);

	// Create the title object
	auto font{ dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36) };

	auto titleObject{ std::make_shared<dae::GameObject>(std::move(dae::Transform(80.f, 20.f))) };
	titleObject->AddComponent<dae::TextComponent>("Programming 4 Assignment", font);
	scene.Add(titleObject);

	// Create the FPS object
	font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 16);

	auto fpsObject{ std::make_shared<dae::GameObject>() };
	fpsObject->AddComponent<dae::TextComponent>("FPS", font);
	fpsObject->AddComponent<dae::FpsComponent>();
	scene.Add(fpsObject);
}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}