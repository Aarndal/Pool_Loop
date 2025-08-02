#pragma once
#include <olcPixelGameEngine.h>

struct PlayerData
{
	PlayerData(unsigned int id, float mass, float linearSpeed, float maxFallSpeed)
		: m_id(id), m_mass(mass), m_linearSpeed(linearSpeed), m_maxFallSpeed(maxFallSpeed) 
	{
	}

public:
	bool init(const std::vector<std::filesystem::path>& vecImagePaths);

	// Getters and Setters
	const unsigned int getId() const { return m_id; }
	
	const float getMass() const { return m_mass; }
	const float getLinearSpeed() const { return m_linearSpeed; }
	const float getMaxFallSpeed() const { return m_maxFallSpeed; }

	const std::vector<olc::Renderable>& getImages() const { return m_images; }

private:

	unsigned int m_id{0};

	float m_mass{1.0f};
	float m_linearSpeed{1.0f};
	float m_maxFallSpeed{1.0f};

	std::vector<olc::Renderable> m_images{};
};

