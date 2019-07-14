#include "Objects2D.h"

#include <Core/Engine.h>

Mesh* Objects2D::CreateSquare(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill)
{
	glm::vec3 corner = leftBottomCorner;

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner, color),
		VertexFormat(corner + glm::vec3(length, 0, 0), color),
		VertexFormat(corner + glm::vec3(length, length, 0), color),
		VertexFormat(corner + glm::vec3(0, length, 0), color)
	};

	Mesh* square = new Mesh(name);
	std::vector<unsigned short> indices = { 0, 1, 2, 3 };

	if (!fill) {
		square->SetDrawMode(GL_LINE_LOOP);
	}
	else {
		// draw 2 triangles. Add the remaining 2 indices
		indices.push_back(0);
		indices.push_back(2);
	}

	square->InitFromData(vertices, indices);
	return square;
}

Mesh* Objects2D::ChangeColor(Mesh* mesh, glm::vec3 color) {
	return mesh;
}
Mesh* Objects2D::CreateCircle(std::string name, glm::vec3 center, float radius, int nrVertices, glm::vec3 color, bool fill)
{
	std::vector<VertexFormat> vertices;
	
	for (int i = 1; i <= nrVertices; i++) {
		glm::vec3 auxCenter = center;
		double angle = i * D_PI / nrVertices;
		auxCenter.x = radius * cos(angle) + center.x;
		auxCenter.y = radius * sin(angle) + center.y;
		vertices.push_back(VertexFormat(auxCenter, color));
	}

	std::vector<unsigned short> indices(nrVertices + 1);
	for (int i = 0; i <= nrVertices; i++) {
		indices[i] = i;
	}
	vertices.push_back(VertexFormat(center, color));
	Mesh* circle = new Mesh(name);
	circle->SetDrawMode(GL_TRIANGLE_FAN);

	circle->InitFromData(vertices, indices);
	return circle;
}

Mesh* Objects2D::CreateTriangle(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill) {
	glm::vec3 corner = leftBottomCorner;

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner, color),
		VertexFormat(corner + glm::vec3(length, 0, 0), color),
		VertexFormat(corner + glm::vec3(0, length, 0), color)
	};

	Mesh* triangle = new Mesh(name);
	std::vector<unsigned short> indices = { 0, 1, 2 };

	if(!fill)
		triangle->SetDrawMode(GL_LINE_LOOP);

	triangle->InitFromData(vertices, indices);
	return triangle;
}

Mesh* Objects2D::CreateRectangle(std::string name, glm::vec3 leftBottomCorner, float width, float height, glm::vec3 color, bool fill)
{
	glm::vec3 corner = leftBottomCorner;

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner, color),
		VertexFormat(corner + glm::vec3(width, 0, 0), color),
		VertexFormat(corner + glm::vec3(width, height, 0), color),
		VertexFormat(corner + glm::vec3(0, height, 0), color)
	};

	Mesh* rectangle = new Mesh(name);
	std::vector<unsigned short> indices = { 0, 1, 2, 3 };

	if (!fill) {
		rectangle->SetDrawMode(GL_LINE_LOOP);
	}
	else {
		// draw 2 triangles. Add the remaining 2 indices
		indices.push_back(0);
		indices.push_back(2);
	}

	rectangle->InitFromData(vertices, indices);
	return rectangle;
}