#include <iostream>
#include <GLFW/glfw3.h>
//#include <glad/glad.h>
#include <cmath>
#include <string>
#include <sstream>
#include <ctime>

constexpr auto pi = 3.14159265358979323846;

const int sides = 9;

int fps = 60;

void drawCircle(GLfloat x, GLfloat y, GLfloat z, GLfloat radius, GLint sides, std::string hex)
{
	hex = hex.substr(1, hex.length() - 1);
	hex.insert(0, "0x");

	int hexInteger;

	std::stringstream ss;
	ss << std::hex << hex;
	ss >> hexInteger;

	float red = ((hexInteger >> 16) & 0xFF) / 255.0;
	float green = ((hexInteger >> 8) & 0xFF) / 255.0;
	float blue = ((hexInteger)&0xFF) / 255.0;
	/////////////////////////////////////////////////////////////////////////////
	int numberOfVertices = sides + 2;

	GLfloat twicePi = 2.0f * pi;

	GLfloat *circleVerticesX = new GLfloat[numberOfVertices];
	GLfloat *circleVerticesY = new GLfloat[numberOfVertices];
	GLfloat *circleVerticesZ = new GLfloat[numberOfVertices];

	circleVerticesX[0] = x;
	circleVerticesY[0] = y;
	circleVerticesZ[0] = z;

	for (int i = 1; i < numberOfVertices; i++)
	{
		circleVerticesX[i] = x + (radius * cos(i * twicePi / sides));
		circleVerticesY[i] = y + (radius * sin(i * twicePi / sides));
		circleVerticesZ[i] = z;
	}

	GLfloat *allCircleVertices = new GLfloat[numberOfVertices * 3];

	for (int i = 0; i < numberOfVertices; i++)
	{
		allCircleVertices[i * 3] = circleVerticesX[i];
		allCircleVertices[(i * 3) + 1] = circleVerticesY[i];
		allCircleVertices[(i * 3) + 2] = circleVerticesZ[i];
	}

	glColor3f(red, green, blue);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, allCircleVertices);
	glDrawArrays(GL_TRIANGLE_FAN, 0, numberOfVertices);
	glDisableClientState(GL_VERTEX_ARRAY);

	delete[] circleVerticesX;
	delete[] circleVerticesY;
	delete[] circleVerticesZ;
	delete[] allCircleVertices;
}

void drawHollowCircle(GLfloat x = 0.0f, GLfloat y = 0.0f, GLfloat z = 0.0f, GLfloat radius = 0.5f, GLint sides = 50, std::string hex = "#000000")
{
	hex = hex.substr(1, hex.length() - 1);
	hex.insert(0, "0x");

	int hexInteger;

	std::stringstream ss;
	ss << std::hex << hex;
	ss >> hexInteger;

	float red = ((hexInteger >> 16) & 0xFF) / 255.0;
	float blue = ((hexInteger >> 8) & 0xFF) / 255.0;
	float green = ((hexInteger)&0xFF) / 255.0;
	/////////////////////////////////////////////////////////////////////////////
	GLint numberOfVertices = sides + 1;

	GLfloat doublePi = 2.0f * pi;

	GLfloat *circleVerticesX = new GLfloat[numberOfVertices];
	GLfloat *circleVerticesY = new GLfloat[numberOfVertices];
	GLfloat *circleVerticesZ = new GLfloat[numberOfVertices];

	circleVerticesX[0] = x;
	circleVerticesY[0] = y;
	circleVerticesZ[0] = z;

	for (int i = 0; i < numberOfVertices; i += 1)
	{
		circleVerticesX[i] = x + (radius * cos(i * doublePi / sides));
		circleVerticesY[i] = y + (radius * sin(i * doublePi / sides));
		circleVerticesZ[i] = z;
	}

	GLfloat *allCircleVertices = new GLfloat[numberOfVertices * 3];

	for (int i = 0; i < numberOfVertices; i++)
	{
		allCircleVertices[i * 3] = circleVerticesX[i];
		allCircleVertices[(i * 3) + 1] = circleVerticesY[i];
		allCircleVertices[(i * 3) + 2] = circleVerticesZ[i];
	}

	glColor3f(red, blue, green);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, allCircleVertices);
	glDrawArrays(GL_LINE_STRIP, 0, numberOfVertices);
	glDisableClientState(GL_VERTEX_ARRAY);

	delete[] circleVerticesX;
	delete[] circleVerticesY;
	delete[] circleVerticesZ;
	delete[] allCircleVertices;
}

void drawFirstHalf(GLfloat x = 0.0f, GLfloat y = 0.0f, GLfloat z = 0.0f, GLfloat radius = 0.5f, GLint sides = 50, std::string hex = "#000000")
{
	hex = hex.substr(1, hex.length() - 1);
	hex.insert(0, "0x");

	int hexInteger;

	std::stringstream ss;
	ss << std::hex << hex;
	ss >> hexInteger;

	float red = ((hexInteger >> 16) & 0xFF) / 255.0;
	float blue = ((hexInteger >> 8) & 0xFF) / 255.0;
	float green = ((hexInteger)&0xFF) / 255.0;
	/////////////////////////////////////////////////////////////////////////////
	GLint numberOfVertices = sides + 1;

	GLfloat doublePi = 2.0f * pi;

	GLfloat *circleVerticesX = new GLfloat[numberOfVertices];
	GLfloat *circleVerticesY = new GLfloat[numberOfVertices];
	GLfloat *circleVerticesZ = new GLfloat[numberOfVertices];

	circleVerticesX[0] = x;
	circleVerticesY[0] = y;
	circleVerticesZ[0] = z;

	for (int i = 0; i < numberOfVertices; i += 1)
	{
		circleVerticesX[i] = x + (radius * cos(i * doublePi / sides));
		circleVerticesY[i] = y + (0.5f * radius * sin(i * doublePi / sides));
		circleVerticesZ[i] = z;
	}

	GLfloat *allCircleVertices = new GLfloat[numberOfVertices * 3];

	for (int i = 0; i < numberOfVertices; i++)
	{
		allCircleVertices[i * 3] = circleVerticesX[i];
		allCircleVertices[(i * 3) + 1] = circleVerticesY[i];
		allCircleVertices[(i * 3) + 2] = circleVerticesZ[i];
	}

	glColor3f(red, blue, green);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, allCircleVertices);
	glDrawArrays(GL_LINE_STRIP, 0, numberOfVertices / 2);
	glDisableClientState(GL_VERTEX_ARRAY);

	delete[] circleVerticesX;
	delete[] circleVerticesY;
	delete[] circleVerticesZ;
	delete[] allCircleVertices;
}

void drawSecondHalf(GLfloat x = 0.0f, GLfloat y = 0.0f, GLfloat z = 0.0f, GLfloat radius = 0.5f, GLint sides = 50, std::string hex = "#000000")
{
	hex = hex.substr(1, hex.length() - 1);
	hex.insert(0, "0x");

	int hexInteger;

	std::stringstream ss;
	ss << std::hex << hex;
	ss >> hexInteger;

	float red = ((hexInteger >> 16) & 0xFF) / 255.0;
	float blue = ((hexInteger >> 8) & 0xFF) / 255.0;
	float green = ((hexInteger)&0xFF) / 255.0;
	/////////////////////////////////////////////////////////////////////////////
	GLint numberOfVertices = (sides + 1);

	GLfloat doublePi = 2.0f * pi;

	GLfloat *circleVerticesX = new GLfloat[numberOfVertices];
	GLfloat *circleVerticesY = new GLfloat[numberOfVertices];
	GLfloat *circleVerticesZ = new GLfloat[numberOfVertices];

	circleVerticesX[0] = x;
	circleVerticesY[0] = y;
	circleVerticesZ[0] = z;

	for (int i = 0; i < numberOfVertices; i += 1)
	{
		circleVerticesX[i] = x + (radius * cos(i * doublePi / sides));
		circleVerticesY[i] = y + (0.5f * radius * sin(i * doublePi / sides));
		circleVerticesZ[i] = z;
	}

	GLfloat *allCircleVertices = new GLfloat[numberOfVertices * 3];

	for (int i = 0; i < numberOfVertices; i++)
	{
		allCircleVertices[i * 3] = circleVerticesX[i];
		allCircleVertices[(i * 3) + 1] = circleVerticesY[i];
		allCircleVertices[(i * 3) + 2] = circleVerticesZ[i];
	}

	glColor3f(red, blue, green);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, allCircleVertices);
	glDrawArrays(GL_LINE_STRIP, (numberOfVertices / 2) - 1, (numberOfVertices / 2) + 2);
	glDisableClientState(GL_VERTEX_ARRAY);

	delete[] circleVerticesX;
	delete[] circleVerticesY;
	delete[] circleVerticesZ;
	delete[] allCircleVertices;
}

void drawSun(float sunX, float sunY, float sunOuterRadius, float sunInnerRadius, int sides, std::string outerColor = "#ffdf80", std::string innerColor = "#ffbf00")
{
	drawCircle(sunX, sunY, 0.0f, sunOuterRadius, sides, outerColor);
	drawCircle(sunX, sunY, 0.0f, sunInnerRadius, sides, innerColor);
}

void drawSaturn(float SaturnX, float SaturnY, float SaturnRadius, int sides, std::string color = "#ffdf80")
{
	drawCircle(SaturnX, SaturnY, 0.0f, SaturnRadius, sides, color);
	drawFirstHalf(SaturnX, SaturnY, 0.0f, SaturnRadius + 0.015f, sides, "#EA7F5E");
	drawCircle(SaturnX, SaturnY, 0.0f, SaturnRadius, sides, color);
	drawSecondHalf(SaturnX, SaturnY, 0.0f, SaturnRadius + 0.015f, sides, "#EA7F5E");
}
void updateCoordsSpeed(float &x, float &y, float orbit, float &speed, float acceleration)
{
	x = (orbit * cos(speed * (2.0f * pi) / sides));
	y = (orbit * sin(speed * ((2.0f * pi)) / sides));
	speed += acceleration;
}

void drawMoon(float moonX, float moonY, float moonRadius, int sides, std::string hex = "#efefef")
{
	drawCircle(moonX, moonY, 0.0f, moonRadius, sides, hex);
}

void drawPlanet(float planetX, float planetY, float planetRadius, int sides, bool isMoon, float moonX, float moonY, std::string color = "#ffdf80")
{
	drawCircle(planetX, planetY, 0.0f, planetRadius, sides, color);

	if (isMoon)
	{
		drawMoon(moonX, moonY, 0.004f, sides, "#efefef");
	}
}

int main()
{
	GLFWwindow *window;
	if (!glfwInit())
	{
		std::cout << "Init error";
		return -1;
	}

	window = glfwCreateWindow(1000, 1000, "Hello", 0, 0);
	if (!window)
	{
		std::cout << "Window creation error";
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	float x = 0.0f, y = 0.0f;
	float sunX = 0.0f, sunY = 0.0f, sunOuterRadius = 0.15f, sunInnerRadius = 0.11f;
	float mercuryX = 0.2f, mercuryY = 0.0f, mercuryRadius = 0.007f, mercuryOrbit = mercuryX, mercurySpeed = 0.001f;
	float venusX = 0.25f, venusY = 0.0f, venusRadius = 0.015f, venusOrbit = venusX, venusSpeed = 0.0007f;
	float earthX = 0.3f, earthY = 0.0f, earthRadius = 0.015f, earthOrbit = earthX, earthSpeed = 0.0005f, earthMoonX = earthX + earthRadius / 2 + 0.03f, earthMoonY = 0.0f, earthMoonSpeed = earthSpeed;
	float marsX = 0.35f, marsY = 0.0f, marsRadius = 0.01f, marsOrbit = marsX, marsSpeed = 0.0005f, marsMoonX = marsX + marsRadius / 2 + 0.03f, marsMoonY = 0.0f, marsMoonSpeed = marsSpeed;
	float jupiterX = 0.47f, jupiterY = 0.0f, jupiterRadius = 0.05f, jupiterOrbit = jupiterX, jupiterSpeed = 0.0008f, jupiterMoonX = jupiterX + jupiterRadius / 2 + 0.03f, jupiterMoonY = 0.0f, jupiterMoonSpeed = jupiterSpeed;
	float saturnX = 0.68f, saturnY = 0.0f, saturnRadius = 0.045f, saturnOrbit = saturnX, saturnSpeed = 0.0003f;
	float uranusX = 0.82f, uranusY = 0.0f, uranusRadius = 0.03f, uranusOrbit = uranusX, uranusSpeed = 0.0001f, uranusMoonX = uranusX + uranusRadius / 2 + 0.03f, uranusMoonY = 0.0f, uranusMoonSpeed = uranusSpeed;
	float neptuneX = 0.9f, neptuneY = 0.0f, neptuneRadius = 0.03f, neptuneOrbit = neptuneX, neptuneSpeed = 0.00005f, neptuneMoonX = neptuneX + neptuneRadius / 2 + 0.03f, neptuneMoonY = 0.0f, neptuneMoonSpeed = neptuneSpeed;
	// glEnable(GL_MULTISAMPLE);

	int newSides = 100;
	//////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////loop///////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.0, 0.0, 0.10f, 0.0);
		glClear(GL_COLOR_BUFFER_BIT);

		drawHollowCircle(x, y, 0.0f, mercuryOrbit, newSides, "#ffffff");
		drawHollowCircle(x, y, 0.0f, venusOrbit, newSides, "#ffffff");
		drawHollowCircle(x, y, 0.0f, earthOrbit, newSides, "#ffffff");
		drawHollowCircle(x, y, 0.0f, marsOrbit, newSides, "#ffffff");
		drawHollowCircle(x, y, 0.0f, jupiterOrbit, newSides, "#ffffff");
		drawHollowCircle(x, y, 0.0f, saturnOrbit, newSides, "#ffffff");
		drawHollowCircle(x, y, 0.0f, uranusOrbit, newSides, "#ffffff");
		drawHollowCircle(x, y, 0.0f, neptuneOrbit, newSides, "#ffffff");

		drawSun(sunX, sunY, sunOuterRadius, sunInnerRadius, sides);
		drawPlanet(mercuryX, mercuryY, mercuryRadius, newSides, 0, 0.0f, 0.0f, "#AAAB97");
		drawPlanet(venusX, venusY, venusRadius, newSides, 0, 0.0f, 0.0f, "#E3BFA0");
		drawPlanet(earthX, earthY, earthRadius, newSides, 1, earthMoonX, earthMoonY, "#255998");
		drawPlanet(marsX, marsY, marsRadius, newSides, 1, marsMoonX, marsMoonY, "#EA7F5E");
		drawPlanet(jupiterX, jupiterY, jupiterRadius, newSides, 1, jupiterMoonX, jupiterMoonY, "#FCE0A5");
		drawSaturn(saturnX, saturnY, saturnRadius, newSides, "#FACB93");
		drawPlanet(uranusX, uranusY, uranusRadius, newSides, 1, uranusMoonX, uranusMoonY, "#82BAE7");
		drawPlanet(neptuneX, neptuneY, neptuneRadius, newSides, 1, neptuneMoonX, neptuneMoonY, "#1B83D8");

		updateCoordsSpeed(mercuryX, mercuryY, mercuryOrbit, mercurySpeed, 0.0005f);
		updateCoordsSpeed(venusX, venusY, venusOrbit, venusSpeed, 0.0003f);
		updateCoordsSpeed(earthX, earthY, earthOrbit, earthSpeed, 0.0002f);
		updateCoordsSpeed(marsX, marsY, marsOrbit, marsSpeed, 0.0001f);
		updateCoordsSpeed(jupiterX, jupiterY, jupiterOrbit, jupiterSpeed, 0.00002f);
		updateCoordsSpeed(saturnX, saturnY, saturnOrbit, saturnSpeed, 0.00001f);
		updateCoordsSpeed(uranusX, uranusY, uranusOrbit, uranusSpeed, 0.000007f);
		updateCoordsSpeed(neptuneX, neptuneY, neptuneOrbit, neptuneSpeed, 0.000005f);

		// Moons
		// updateCoordsSpeed(float& x, float& y, float orbit, float& speed, float acceleration)
		updateCoordsSpeed(earthMoonX, earthMoonY, earthOrbit + 0.02f, earthMoonSpeed, 0.0002f);
		updateCoordsSpeed(marsMoonX, marsMoonY, marsOrbit + 0.015f, marsMoonSpeed, 0.0001f);
		updateCoordsSpeed(jupiterMoonX, jupiterMoonY, jupiterOrbit + 0.055f, jupiterMoonSpeed, 0.00002f);
		updateCoordsSpeed(uranusMoonX, uranusMoonY, uranusOrbit + 0.035f, uranusMoonSpeed, 0.000007f);
		updateCoordsSpeed(neptuneMoonX, neptuneMoonY, neptuneOrbit + 0.035f, neptuneMoonSpeed, 0.000005f);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
}