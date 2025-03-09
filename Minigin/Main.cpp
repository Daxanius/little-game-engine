#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "TextureComponent.h"
#include "TextComponent.h"
#include "Scene.h"
#include "FpsComponent.h"
#include "RotatorComponent.h"
#include "ThrashTheCacheComponent.h"
#include "InputManager.h"
#include "InputDevice.h"
#include "Gamepad.h"
#include "Keyboard.h"
#include "LogCommand.h"
#include "MoveCommand.h"

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

	auto player1{ std::make_shared<dae::GameObject>() };
	player1->AddComponent<dae::TextureComponent>("qbert_char.png");
	scene.Add(player1);

	// Child of orbit object
	auto player2{ std::make_shared<dae::GameObject>() };
	player2->AddComponent<dae::TextureComponent>("qbert_char.png");
	scene.Add(player2);

	const float speed{ 5.f };

	// Keyboard player
	std::unique_ptr<dae::InputDevice> keyboard{ std::make_unique<dae::Keyboard>(0) };

	keyboard->BindButton(
		static_cast<int>(SDLK_a),
		dae::InputDevice::InputAction{
			dae::InputDevice::InputActionType::Hold,
			std::move(std::make_unique<dae::MoveCommand>(player1.get(), glm::vec2(-1, 0), speed))
		});

	keyboard->BindButton(
		static_cast<int>(SDLK_d),
		dae::InputDevice::InputAction{
			dae::InputDevice::InputActionType::Hold,
			std::move(std::make_unique<dae::MoveCommand>(player1.get(), glm::vec2(1, 0), speed))
		});

	keyboard->BindButton(
		static_cast<int>(SDLK_s),
		dae::InputDevice::InputAction{
			dae::InputDevice::InputActionType::Hold,
			std::move(std::make_unique<dae::MoveCommand>(player1.get(), glm::vec2(0, 1), speed))
		});


	keyboard->BindButton(
		static_cast<int>(SDLK_w),
		dae::InputDevice::InputAction{
			dae::InputDevice::InputActionType::Hold,
			std::move(std::make_unique<dae::MoveCommand>(player1.get(), glm::vec2(0, -1), speed))
		});

	dae::InputManager::GetInstance().AddInputDevice(std::move(keyboard));

	// Controller player
	std::unique_ptr<dae::InputDevice> gamepad{ std::make_unique<dae::Gamepad>(1, 0) };

	gamepad->BindButton(
		static_cast<int>(dae::Gamepad::Button::Left),
		dae::InputDevice::InputAction{
			dae::InputDevice::InputActionType::Hold,
			std::move(std::make_unique<dae::MoveCommand>(player2.get(), glm::vec2(-1, 0), speed * 2.f))
		});

	gamepad->BindButton(
		static_cast<int>(dae::Gamepad::Button::Right),
		dae::InputDevice::InputAction{
			dae::InputDevice::InputActionType::Hold,
			std::move(std::make_unique<dae::MoveCommand>(player2.get(), glm::vec2(1, 0), speed * 2.f))
		});

	gamepad->BindButton(
		static_cast<int>(dae::Gamepad::Button::Down),
		dae::InputDevice::InputAction{
			dae::InputDevice::InputActionType::Hold,
			std::move(std::make_unique<dae::MoveCommand>(player2.get(), glm::vec2(0, 1), speed * 2.f))
		});


	gamepad->BindButton(
		static_cast<int>(dae::Gamepad::Button::Up),
		dae::InputDevice::InputAction{
			dae::InputDevice::InputActionType::Hold,
			std::move(std::make_unique<dae::MoveCommand>(player2.get(), glm::vec2(0, -1), speed * 2.f))
		});

	dae::InputManager::GetInstance().AddInputDevice(std::move(gamepad));
}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
	return 0;
}