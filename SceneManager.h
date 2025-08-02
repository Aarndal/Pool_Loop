#pragma once
#include <memory>
#include <map>
#include <optional>

class IScene;
namespace olc {
	class PixelGameEngine;
}
class SceneManager
{
public:
	static SceneManager& getInstance();

	enum class Scene
	{
		mainMenu,
		characterSelection,
		game,
		quit
	};
	void changeScene(Scene newSchene);
	IScene* getCurrentScene(olc::PixelGameEngine* pge);
private:
	std::unique_ptr<IScene> m_currentScene;
	std::optional<Scene> m_nextScene;
};

