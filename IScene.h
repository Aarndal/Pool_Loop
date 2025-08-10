#pragma once

namespace olc {
	class PixelGameEngine;
}

class ISceneData
{
public:
	virtual ~ISceneData() = default;
};


class IScene
{
public:
	virtual void init(olc::PixelGameEngine& engine, const std::shared_ptr<ISceneData>& data = nullptr) = 0;
	virtual void update(olc::PixelGameEngine& engine, float elapsedTime) = 0;
};