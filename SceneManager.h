#pragma once
#include <memory>
#include <map>

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
		game
	};
	void changeScene(Scene newSchene, olc::PixelGameEngine* pge);
	IScene* getCurrentScene();
private:
	std::unique_ptr<IScene> m_currentScene;

};

