#ifndef _SHAPE_RECTANGLE_H_
#define _SHAPE_RECTANGLE_H_

#include "ShapeComponent.h"

class ShapeRectangle : public ShapeComponent
{
public:
	ShapeRectangle(float x);
	ShapeRectangle(float x, float originX, float originY);
	ShapeRectangle(float width, float height);
	ShapeRectangle(float width, float height, float originX, float originY);
	~ShapeRectangle();

	void					Resize(float x);
	void					Resize(float x, float originX, float originY);
	void					Resize(float width, float height);
	void					Resize(float width, float height, float originX, float originY);

	std::vector<Vector4>	GetVertexList() const;

	void					Render() const;

private:
	Vector4					m_topRight;
	Vector4					m_topLeft;
	Vector4					m_bottomRight;
	Vector4					m_bottomLeft;
};

#endif