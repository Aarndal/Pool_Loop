#pragma once
struct PlayerData
{
	PlayerData(unsigned int id, float mass, float linearSpeed, float maxFallSpeed)
		: m_id(id), m_mass(mass), m_linearSpeed(linearSpeed), m_maxFallSpeed(maxFallSpeed) {}

public:
	// Getters and Setters
	unsigned int getId() const { return m_id; }
	
	float getMass() const { return m_mass; }
	float getLinearSpeed() const { return m_linearSpeed; }
	float getMaxFallSpeed() const { return m_maxFallSpeed; }

private:

	unsigned int m_id{0};

	float m_mass{1.0f};
	float m_linearSpeed{1.0f};
	float m_maxFallSpeed{1.0f};
};

