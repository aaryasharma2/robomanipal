#pragma once

#include <Component/SimpleScene.h>
#include <string>
#include <Core/Engine.h>
#include <utility>
#include <time.h>
#include <unordered_map>
#include <dos.h> //for delay

#define MOVE_RATIO			(.1f)
#define MOVE_RATIO_FAST		(.75f)
#define LIMIT				(.5f)
#define ROTATION_SPEEDUP	(1.25f)
#define SQUARE_SIDE			(35.f)
#define SQUARES_DISTANCE	(10.f)
#define START_FALL			(1000.f)
#define RADIUS				(15.f)
#define TRIANGLE_SIDE		(12.f)
#define WALL_WIDTH			(75.f)
#define OFFSET				(400.f)
#define GROUND_COLLISION	(147.f)
#define FIRST_COLUMN_LOW	(-505)
#define FIRST_COLUMN_UP		(-445)
#define SECOND_COLUMN_LOW	(-950)
#define SECOND_COLUMN_UP	(-890)
#define THIRD_COLUMN_LOW	(-1360)
#define THIRD_COLUMN_UP		(-1300)
#define FORTH_COLUMN_LOW	(-1765)
#define FORTH_COLUMN_UP		(-1705)

class Tema1 : public SimpleScene
{
public:
	Tema1();
	~Tema1();

	void Init() override;

private:
	void initTranslationSteps();
	void initMovementRight();
	void initRandomPicker(glm::vec2 resolution);
	void FrameStart() override;
	void DrawColumn1(float deltaTimeSeconds, glm::vec2 resolution, int i);
	void DrawColumn2(float deltaTimeSeconds, glm::vec2 resolution, int i);
	void DrawColumn3(float deltaTimeSeconds, glm::vec2 resolution, int i);
	void DrawColumn4(float deltaTimeSeconds, glm::vec2 resolution, int i);
	void delimitArea(float tx_low, float ty_low, float tx_up, float ty_up, glm::vec2 resolution, int nameColumn, int multipleOffset);
	void Update(float deltaTimeSeconds) override;
	void FrameEnd() override;
	void OnInputUpdate(float deltaTime, int mods) override;
	void OnKeyPress(int key, int mods) override;
	void OnKeyRelease(int key, int mods) override;
	void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
	void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
	void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
	void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
	void OnWindowResize(int width, int height) override;

protected:
	glm::mat3 modelMatrix;
	GLfloat	translateX_up1, translateX_up2, translateX_up3, translateX_up4,
			translateX_low1, translateX_low2, translateX_low3, translateX_low4,
			translateY_up1, translateY_up2, translateY_up3, translateY_up4,
			translateY_low1, translateY_low2, translateY_low3, translateY_low4;
	GLfloat fall_1, fall_2, fall_3, fall_4;
	float scaleX, scaleY;
	float angularStep, angularStep2;
	GLboolean moveRight1, moveRight2, moveRight3, moveRight4;
	GLboolean moveRight5, moveRight6, moveRight7, moveRight8;
	int screen,ty1,ty2,ty3;
	int timeToGenerate;
	bool jump;
	std::vector<Mesh*> columnsLow, columnsUp;
	int b1, b2, b3, b4, k = 0;
	std::vector<std::pair<float, float>> pairHeights;
	GLboolean GameStatus;
	int Score;
	int Column1;
	int nameColumn;
	int m1, m2, m3, m4;

};
