#include "Score.h"
#include <cmath>

namespace
{
	const int scorePerRotation{10};
}



Score& Score::getInstance()
{
	static Score instance;
	return instance;
}

void Score::addRotation()
{
	m_currentPoints += scorePerRotation;
}

void Score::finaliseScore(float angleOfEntry, bool isRotating, float distanceToTarget)
{
	const float factor{isRotating ? 1.f : std::lerp(2.0f, 10.0f,std::fabs(std::cosf(angleOfEntry))) };
	m_currentPoints *= factor * 100.f/ distanceToTarget;

	m_highScore = m_highScore < m_currentPoints ? m_currentPoints : m_highScore;
}

int Score::getFinalScore()
{
	return m_currentPoints;
}

int Score::getHighScore()
{
	return m_highScore;
}

void Score::resetScore()
{
	m_currentPoints = 0;
}
