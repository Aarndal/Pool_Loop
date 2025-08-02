#pragma once
struct PlayerData
{
	PlayerData(unsigned int id, float mass, float linearSpeed, float maxFallSpeed)
		: m_id(id), m_mass(mass), m_linearSpeed(linearSpeed), m_maxFallSpeed(maxFallSpeed) {}
	

public:
	unsigned int getId() const { return m_id; }
	float getMass() const { return m_mass; }
	float getLinearSpeed() const { return m_linearSpeed; }
	float getMaxFallSpeed() const { return m_maxFallSpeed; }

private:
	unsigned int m_id{};

	float m_mass{};
	float m_linearSpeed{};
	float m_maxFallSpeed{};
};

