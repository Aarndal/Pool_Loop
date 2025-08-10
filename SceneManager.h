#pragma once
#include <memory>
#include <map>
#include <optional>


class IScene;
class ISceneData;
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
		gameOver,
		quit
	};
	void changeScene(Scene newSchene, const std::shared_ptr<ISceneData>& data = nullptr);
	IScene* getCurrentScene(olc::PixelGameEngine& pge);

	struct NextScene
	{
		Scene id;
		std::shared_ptr<ISceneData> data;
	};
private:
	std::unique_ptr<IScene> m_currentScene;
	std::optional<NextScene> m_nextScene;

};

