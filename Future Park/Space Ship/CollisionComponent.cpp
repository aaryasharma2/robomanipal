#include "CollisionComponent.h"

CollisionComponent::CollisionComponent()
{
}

CollisionComponent::~CollisionComponent()
{
}

bool CollisionComponent::Collision(const CollisionComponent &collisionComponent) const
{
	bool within = false;

	Vector4 vertI;
	Vector4 vertJ;

	for (const Vector4 &vec : GetVertices())
	{
		for (unsigned i = 0, j = m_vertices.size() - 1; i < m_vertices.size(); j = i++)
		{
			vertI = collisionComponent.GetVertex(i);
			vertJ = collisionComponent.GetVertex(j);

			if ((vertI.GetY() > vec.GetY()) != (vertJ.GetY() > vec.GetY()) && (vec.GetX() < (vertJ.GetX() - vertI.GetX()) * (vec.GetY() - vertI.GetY()) / (vertJ.GetY() - vertI.GetY()) + vertI.GetX()))
			{
				within = !within;
			}
		}

		if (within)
			return within;
	}

	return within;
}

const std::vector<Vector4> CollisionComponent::GetVertices() const
{
	std::vector<Vector4> vertices;

	for (Vector4 vec : m_vertices)
	{
		vertices.push_back(m_transformComponent->Transformation(vec));
	}

	return vertices;
}