#pragma once

class IScene
{
public:
	virtual void init() = 0;
	virtual void update(float time) = 0;
};