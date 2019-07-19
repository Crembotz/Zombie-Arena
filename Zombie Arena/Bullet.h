#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;
class Bullet
{
private:
	//Where is the bullet?
	Vector2f m_Position;

	//What each bullet looks like
	RectangleShape m_BulletShape;

	//Is this bullet currently whizzing through the air?
	bool m_InFlight = false;

	//How fast does a bullet travel?
	float m_BulletSpeed = 1000;

	/*What fraction of 1 pixel does
	the bullet travel horizontally
	and vertically each frame?*/
	float m_BulletDistanceX, m_BulletDistanceY;

	//Some boundaries so the bullet doesn't fly forever
	float m_MaxX, m_MinX,
		m_MaxY, m_MinY;

	//Public function prototypes go here
public:
	//The constructor
	Bullet();

	//Stop the bullet
	void stop();

	//Returns the value of m_InFlight
	bool isInFlight();

	//Launch a new bullet

	void shoot(float startX, float startY, float targetX, float targetY);

	//Get the current position
	FloatRect getPosition();

	//Returns the actual shape for drawing
	RectangleShape getShape();

	//Update the bullet each frame
	void update(float elapsedTime);
};
