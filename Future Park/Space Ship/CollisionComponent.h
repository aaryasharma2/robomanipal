#ifndef _COLLISION_COMPONENT_H_
#define _COLLISION_COMPONENT_H_

#include "Object.h"
#include "Vector4.h"
#include <vector>

class CollisionComponent : public Object
{
public:
	CollisionComponent();
	~CollisionComponent();

	inline void						AddVertex(const Vector4 vec)
	{
		m_vertices.push_back(vec);
	}

	inline void						AddVertex(const std::vector<Vector4> vec)
	{
		m_vertices = vec;
	}

	inline Vector4					GetVertex(unsigned index) const
	{
		return m_transformComponent->Transformation(m_vertices[index]);
	}

	const std::vector<Vector4>		GetVertices() const;

	virtual bool					Collision(const CollisionComponent &collisionComponent) const;

protected:
	std::vector<Vector4>			m_vertices;
};

#endif