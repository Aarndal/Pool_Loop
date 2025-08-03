#pragma once
class Score
{
public: 
	static Score& getInstance();

	void addRotation();
	void finaliseScore(float angleOfEntry, bool isRotating, float distanceToTarget);

	int getFinalScore();
	int getHighScore();
	void resetScore();

private:
	Score() = default;
	int m_currentPoints{};
	int m_highScore{ 0 };
};

