#include "Bullet.h"

//The constructor
Bullet::Bullet()
{
	m_BulletShape.setSize(sf::Vector2f(2, 2));
}

void Bullet::shoot(float startX, float startY, float targetX, float targetY)
{
	m_InFlight = true;
	m_Position.x = startX;
	m_Position.y = startY;

	//Calculate the gradient of the flight path
	float gradient = (startY - targetY) / (startX - targetX);
	// Every gradient has to be positive, because the bullet has to move towards its target every frame
	if (gradient < 0)
		gradient *= -1;

	// Calculate the ratio between x and y
	float ratioXY = m_BulletSpeed / (1 + gradient);/*This variable is kind of pointless, it's simply here to enable us
												   to adjust the bullet's speed in accordance with the distance
												   it has to travel, the name is also very misleading. */
	// Set the "speed" horizontally and vertically
	/*The axis that is in the nominator of the gradient calculation must be multiplied by it to ensure
	that the bullet travels the right amount of pixels each frame across it, thus making it move in the intended direction*/
	m_BulletDistanceY = ratioXY * gradient;//Can be multiplied by any other number, let's call it a,  besides ratioXY
	m_BulletDistanceX = ratioXY;//Can be that same a we mentioned earlier
	// Point the bullet in the right direction
	if (targetX < startX)
	{
		m_BulletDistanceX *= -1;
	}
	if (targetY < startY)
	{
		m_BulletDistanceY *= -1;
	}
	// Set a max range of 1000 pixels
	float range = 1000;
	m_MinX = startX - range;
	m_MaxX = startX + range;
	m_MinY = startY - range;
	m_MaxY = startY + range;
	// Position the bullet ready to be drawn
	m_BulletShape.setPosition(m_Position);
}
void Bullet::stop()
{
	m_InFlight = false;
}
bool Bullet::isInFlight()
{
	return m_InFlight;
}
FloatRect Bullet::getPosition()
{
	return m_BulletShape.getGlobalBounds();
}
RectangleShape Bullet::getShape()
{
	return m_BulletShape;
}
void Bullet::update(float elapsedTime)
{
	// Update the bullet position variables
	m_Position.x += m_BulletDistanceX * elapsedTime;
	m_Position.y += m_BulletDistanceY * elapsedTime;
	// Move the bullet
	m_BulletShape.setPosition(m_Position);
	// Has the bullet gone out of range?
	if (m_Position.x < m_MinX || m_Position.x > m_MaxX ||
		m_Position.y < m_MinY || m_Position.y > m_MaxY)
	{
		m_InFlight = false;
	}
}