#pragma once

class ISceneData
{
public:
	virtual ~ISceneData() = default;
};


class IScene
{
public:
	virtual void init(const std::shared_ptr<ISceneData>& data = nullptr) = 0;
	virtual void update(float time) = 0;
};