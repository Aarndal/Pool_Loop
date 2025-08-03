#pragma once
#include <olcPixelGameEngine.h>
#include "IScene.h"

struct PlayerData : public ISceneData
{
	PlayerData(unsigned int id, float airResistance, float linearSpeed, float angularSpeed, float maxFallSpeed) : m_id(id), m_airResistance(airResistance), m_linearSpeed(linearSpeed), m_angularSpeed(angularSpeed), m_maxFallSpeed(maxFallSpeed)
	{
	}
public:
	bool init(const std::vector<std::filesystem::path>& vecImagePaths);

	// Getters and Setters
	const unsigned int getId() const { return m_id; }

	const float getAirResistance() const { return m_airResistance; }
	const float getLinearSpeed() const { return m_linearSpeed; }
	const float getAngularSpeed() const { return m_angularSpeed; }
	const float getMaxFallSpeed() const { return m_maxFallSpeed; }

	const std::vector<olc::Renderable>& getImages() const { return m_images; }

private:

	unsigned int m_id{ 0 };

	float m_airResistance{ 1.0f };
	float m_linearSpeed{ 1.0f };
	float m_angularSpeed{ 5.0f };
	float m_maxFallSpeed{ 1.0f };

	std::vector<olc::Renderable> m_images{};
};

