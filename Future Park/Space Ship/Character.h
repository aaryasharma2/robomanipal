#ifndef _CHARACTER_H_
#define _CHARACTER_H_

#include "GameObject.h"

class Character : public GameObject
{
public:
	Character() { ; }
	virtual ~Character() { ; }

	inline void					SetProjectileSize(const float size) { m_projectileSize = size; }
	inline float				GetProjectileSize() const { return m_projectileSize; }

protected:
	int							m_health;

	float						m_speed;
	float						m_projectileSize;
	float						m_projectileSpeed;
};

#endif