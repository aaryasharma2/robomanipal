#include "Tema1.h"

#include <vector>
#include <iostream>

#include <Core/Engine.h>
#include "Transform2D.h"
#include "Objects2D.h"

using namespace std;

Tema1::Tema1()
{
}

Tema1::~Tema1()
{
}


void Tema1::initTranslationSteps() {
	translateX_low1 = 0.f;
	translateX_low2 = 0.f;
	translateX_low3 = 0.f;
	translateX_low4 = 0.f;
	
	translateY_low1 = 0.f;
	translateY_low2 = 0.f;
	translateY_low3 = 0.f;
	translateY_low4 = 0.f;

	translateY_up1 = 150.f;
	translateY_up2 = 150.f;
	translateY_up3 = 150.f;
	translateY_up4 = 150.f;

	translateX_up1 = 0.f;
	translateX_up2 = 0.f;
	translateX_up3 = 0.f;
	translateX_up4 = 0.f;

	fall_1 = 500;
	fall_2 = 527;
	fall_3 = 520;

	m1 = 0;
	m2 = 0;
	m3 = 0;
	m4 = 0;
}

void Tema1::initRandomPicker(glm::vec2 resolution) {

	pairHeights.push_back(make_pair(0, 150));
	pairHeights.push_back(make_pair(-60, 170));
	pairHeights.push_back(make_pair(50, 77));
	pairHeights.push_back(make_pair(-50, 161));
	pairHeights.push_back(make_pair(25, 127));
	pairHeights.push_back(make_pair(35, 99));
}

void Tema1::initMovementRight() {
	moveRight1 = false;
	moveRight2 = false;
	moveRight3 = false;
	moveRight4 = false;
	moveRight5 = false;
	moveRight6 = false;
	moveRight7 = false;
	moveRight8 = false;
}

void Tema1::Init()
{
	glm::ivec2 resolution = window->GetResolution();
	auto camera = GetSceneCamera();
	camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
	camera->SetPosition(glm::vec3(0, 0, 50));
	camera->SetRotation(glm::vec3(0, 0, 0));
	camera->Update();
	GetCameraInput()->SetActive(false);
	GameStatus = true;
	glm::vec3 corner = glm::vec3(0, 0, 0);
	float squareSide = SQUARE_SIDE;
	float triagleSide = TRIANGLE_SIDE;

	/* Draw bird */
	Mesh* body = Objects2D::CreateSquare("body", corner, squareSide, glm::vec3(1.f, 0.4706f, 0.498f), true);
	AddMeshToList(body);
	
	Mesh* head = Objects2D::CreateCircle("head", corner, RADIUS, squareSide, glm::vec3(1.f, 0.4706f, 0.498f), true);
	AddMeshToList(head);

	Mesh* eye = Objects2D::CreateCircle("eye", corner, RADIUS - 0.8 * RADIUS, squareSide, glm::vec3(0.4706f, 0.2392f, 0.2471f), true);
	AddMeshToList(eye);

	Mesh* beak = Objects2D::CreateTriangle("beak", corner, triagleSide, glm::vec3(0.7608f, 0.2314f, 0.1333f), true);
	AddMeshToList(beak);
	
	/*Draw column */
	Mesh* column = Objects2D::CreateRectangle("column", corner, WALL_WIDTH, resolution.y / 2, glm::vec3(0.4784f, 0.2863f, 0.7529f), true);
	AddMeshToList(column);

	/* Draw foreground*/
	Mesh* ground = Objects2D::CreateRectangle("ground", corner, resolution.x, resolution.y / 5, glm::vec3(0.761f, 0.698f, 0.502f), true);
	AddMeshToList(ground);

	Mesh* grass = Objects2D::CreateRectangle("grass", corner, resolution.x, resolution.y / 11, glm::vec3(0.3255f, 0.5176f, 0.2471f), true);
	AddMeshToList(grass);

	screen = 0;
	jump = false;
	/* Bird coordinates Y */
	b1 = 155, b2 = 193, b3 = 190, b4 = 204;
	ty1 = 500, ty2 = 525, ty3 = 520;
	angularStep = 0;
	scaleX = 1;
	scaleY = 0.5;
	GameStatus = true;
	Score = 0;
	initTranslationSteps();
	initMovementRight();
	initRandomPicker(resolution);


	cout << "=======================		SCORE		=======================" << endl;
}

void Tema1::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0.5f, 1.0f, 1.0f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
	
}

void Tema1::DrawColumn1(float deltaTimeSeconds, glm::vec2 resolution, int i) {

	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(resolution.x / 2 + i * OFFSET, translateY_low1);
	int randomIndex_1 = rand() % pairHeights.size();
	Column1 = randomIndex_1;
	if (moveRight1) {
		translateX_low1 = resolution.x / 2 - i * OFFSET + 2 * WALL_WIDTH;
		translateY_low1 = pairHeights.at(randomIndex_1).first;
		modelMatrix *= Transform2D::Translate(translateX_low1, translateY_low1);
		moveRight1 = false;
	}

	if (!moveRight1)
	{
		translateX_low1 -= MOVE_RATIO * deltaTimeSeconds * resolution.x;
		modelMatrix *= Transform2D::Translate(translateX_low1, translateY_low1);
		if (translateX_low1 <= -resolution.x * LIMIT - i * OFFSET - WALL_WIDTH) {
			moveRight1 = true;
		}
	}
	RenderMesh2D(meshes["column"], shaders["VertexColor"], modelMatrix);

	modelMatrix = glm::mat3(1);
	
	modelMatrix *= Transform2D::Translate(resolution.x / 2 + i * OFFSET, resolution.y - translateY_up1);
	if (moveRight5){
		translateX_up1 = resolution.x / 2 - i * OFFSET + 2 * WALL_WIDTH;
		translateY_up1 = pairHeights.at(randomIndex_1).second;
		modelMatrix *= Transform2D::Translate(translateX_up1, resolution.y -translateY_up1);
		moveRight5 = false;
	}
	if (!moveRight5){
		translateX_up1 -= MOVE_RATIO * deltaTimeSeconds * resolution.x;
		modelMatrix *= Transform2D::Translate(translateX_up1, translateY_up1 - translateY_up1);

		if (translateX_up1 <= - resolution.x * LIMIT - i * OFFSET - WALL_WIDTH)
			moveRight5 = true;
	}
	RenderMesh2D(meshes["column"], shaders["VertexColor"], modelMatrix);
	
}

void Tema1::DrawColumn2(float deltaTimeSeconds, glm::vec2 resolution, int i) {

	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(resolution.x / 2 + i * OFFSET, translateY_low2 + 20);
	int randomIndex_2 = rand() % pairHeights.size();
	if (moveRight2) {
		translateX_low2 = resolution.x / 2 - i * OFFSET + 2 * WALL_WIDTH;
		translateY_low2 = pairHeights.at(randomIndex_2).first;
		modelMatrix *= Transform2D::Translate(translateX_low2, translateY_low2);
		moveRight2 = false;
	}

	if (!moveRight2)
	{
		translateX_low2 -= MOVE_RATIO * deltaTimeSeconds * resolution.x;
		modelMatrix *= Transform2D::Translate(translateX_low2, translateY_low2);
		if (translateX_low2 <= -resolution.x * LIMIT - i * OFFSET - WALL_WIDTH) {
			moveRight2 = true;
		}
	}
	RenderMesh2D(meshes["column"], shaders["VertexColor"], modelMatrix);


	modelMatrix = glm::mat3(1);

	modelMatrix *= Transform2D::Translate(resolution.x / 2 + i * OFFSET, resolution.y - translateY_up2 - 20);
	if (moveRight6) {
		translateX_up2 = resolution.x / 2 - i * OFFSET + 2 * WALL_WIDTH;
		translateY_up2 = pairHeights.at(randomIndex_2).second;
		modelMatrix *= Transform2D::Translate(translateX_up2, resolution.y - translateY_up2);
		moveRight6 = false;
	}
	if (!moveRight6) {
		translateX_up2 -= MOVE_RATIO * deltaTimeSeconds * resolution.x;
		modelMatrix *= Transform2D::Translate(translateX_up2, translateY_up2 - translateY_up2);

		if (translateX_up2 <= -resolution.x * LIMIT - i * OFFSET - WALL_WIDTH)
			moveRight6 = true;
	}
	RenderMesh2D(meshes["column"], shaders["VertexColor"], modelMatrix);

}

void Tema1::DrawColumn3(float deltaTimeSeconds, glm::vec2 resolution, int i) {

	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(resolution.x / 2 + i * OFFSET, translateY_low3 - 20);
	int randomIndex_3 = rand() % pairHeights.size();
	if (moveRight3) {
		translateX_low3 = resolution.x / 2 - i * OFFSET + 2 * WALL_WIDTH;
		translateY_low3 = pairHeights.at(randomIndex_3).first;
		modelMatrix *= Transform2D::Translate(translateX_low3, translateY_low3);
		moveRight3 = false;
	}

	if (!moveRight3)
	{
		translateX_low3 -= MOVE_RATIO * deltaTimeSeconds * resolution.x;
		modelMatrix *= Transform2D::Translate(translateX_low3, translateY_low3);
		if (translateX_low3 <= -resolution.x * LIMIT - i * OFFSET - WALL_WIDTH) {
			moveRight3 = true;
		}
	}
	RenderMesh2D(meshes["column"], shaders["VertexColor"], modelMatrix);


	modelMatrix = glm::mat3(1);

	modelMatrix *= Transform2D::Translate(resolution.x / 2 + i * OFFSET, resolution.y - translateY_up3 + 20);
	if (moveRight7) {
		translateX_up3 = resolution.x / 2 - i * OFFSET + 2 * WALL_WIDTH;
		translateY_up3 = pairHeights.at(randomIndex_3).second;
		modelMatrix *= Transform2D::Translate(translateX_up3, resolution.y - translateY_up3);
		moveRight7 = false;
	}
	if (!moveRight7) {
		translateX_up3 -= MOVE_RATIO * deltaTimeSeconds * resolution.x;
		modelMatrix *= Transform2D::Translate(translateX_up3, translateY_up3 - translateY_up3);

		if (translateX_up3 <= -resolution.x * LIMIT - i * OFFSET - WALL_WIDTH)
			moveRight7 = true;
	}
	RenderMesh2D(meshes["column"], shaders["VertexColor"], modelMatrix);
}

void Tema1::DrawColumn4(float deltaTimeSeconds, glm::vec2 resolution, int i) {

	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(resolution.x / 2 + i * OFFSET,translateY_low4 + 10);
	int randomIndex_4 = rand() % pairHeights.size();
	if (moveRight4) {
		translateX_low4 = resolution.x / 2 - i * OFFSET + 2 * WALL_WIDTH;
		translateY_low4 = pairHeights.at(randomIndex_4).first;
		modelMatrix *= Transform2D::Translate(translateX_low4, translateY_low4);
		moveRight4 = false;
	}

	if (!moveRight4)
	{
		translateX_low4 -= MOVE_RATIO * deltaTimeSeconds * resolution.x;
		modelMatrix *= Transform2D::Translate(translateX_low4, translateY_low4);
		if (translateX_low4 <= -resolution.x * LIMIT - i * OFFSET - WALL_WIDTH) {
			moveRight4 = true;
		}
	}
	RenderMesh2D(meshes["column"], shaders["VertexColor"], modelMatrix);


	modelMatrix = glm::mat3(1);

	modelMatrix *= Transform2D::Translate(resolution.x / 2 + i * OFFSET, resolution.y - translateY_up4 - 55);
	if (moveRight8) {
		translateX_up4 = resolution.x / 2 - i * OFFSET + 2 * WALL_WIDTH;
		translateY_up4 = pairHeights.at(randomIndex_4).second;
		modelMatrix *= Transform2D::Translate(translateX_up4, resolution.y - translateY_up4);
		moveRight8 = false;
	}
	if (!moveRight8) {
		translateX_up4 -= MOVE_RATIO * deltaTimeSeconds * resolution.x;
		modelMatrix *= Transform2D::Translate(translateX_up4, translateY_up4 - translateY_up4);

		if (translateX_up4 <= -resolution.x * LIMIT - i * OFFSET - WALL_WIDTH)
			moveRight8 = true;
	}
	RenderMesh2D(meshes["column"], shaders["VertexColor"], modelMatrix);
}

void Tema1::delimitArea(float tx_low, float ty_low, float tx_up, float ty_up, glm::vec2 resolution, int nameColumn, int multipleOffset) {

	if (nameColumn == 1) {
		if (tx_low  > FIRST_COLUMN_LOW && tx_up  < FIRST_COLUMN_UP + 20) { //bird box
			if (multipleOffset == 0) {
				if (fall_1 < resolution.y / 2 - ty_low || fall_1 > resolution.y / 2 + ty_up) {
					GameStatus = false;
					cout << "1" << endl;
					cout << "GAME OVER" << endl;
					cout << "You Lost with the final score : " << Score << "! Retry?" << endl << "Please press Space Key." << endl << endl;
				}
			}
			else if (multipleOffset > 0) {
				if (fall_1 < resolution.y / 2 - ty_low - 70 || fall_1 > resolution.y / 2 + ty_up + 85) {
					GameStatus = false;
					cout << "1" << endl;

					cout << "GAME OVER" << endl;
					cout << "You Lost with the final score : " << Score << "! Retry?" << endl << "Please press Space Key." << endl << endl;
				}
			}
		}
		if ((int)tx_low + WALL_WIDTH >= FIRST_COLUMN_UP - 3 && (int)tx_low + WALL_WIDTH <= FIRST_COLUMN_UP)
		{
			Score++;
			cout << "current SCORE: " << Score << endl;
			m1++;
		}
	}
	else if (nameColumn == 2) {
	 if (tx_up < SECOND_COLUMN_UP + 60 && tx_low > SECOND_COLUMN_LOW - 60)//bird box
		 if (multipleOffset == 0) {
			 if (fall_1 < resolution.y / 2 - ty_low || fall_1 > resolution.y / 2 + ty_up) {
				 GameStatus = false;
				 cout << "2" << endl;

				 cout << "GAME OVER" << endl;
				 cout << "You Lost with the final score : " << Score << "! Retry?" << endl << "Please press Space Key." << endl << endl;
			 }
		 }
		 else if (multipleOffset > 0) {
			 if (fall_1 < resolution.y / 2 - ty_low  - 20 || fall_1 > resolution.y / 2 + ty_up + 40) {
				 GameStatus = false;
				 cout << "2" << endl;

				 cout << "GAME OVER" << endl;
				 cout << "You Lost with the final score : " << Score << "! Retry?" << endl << "Please press Space Key." << endl << endl;
			 }
		 }

	 if ((int)tx_low + WALL_WIDTH == SECOND_COLUMN_UP)
	 {
		 Score++;
		 cout << "current SCORE: " << Score << endl;
	 }
		}
	else if (nameColumn == 3) {
		 if (tx_up < THIRD_COLUMN_UP && tx_low > THIRD_COLUMN_LOW)//bird box
			if (fall_1 < resolution.y / 2 - ty_low || fall_1 > resolution.y / 2 + ty_up) {
				GameStatus = false;
				cout << "GAME OVER" << endl;
				cout << "You Lost with the final score : " << Score << "! Retry?" << endl << "Please press Space Key." << endl << endl;
			}
		 if ((int)tx_low + WALL_WIDTH == THIRD_COLUMN_UP)
		 {
			 Score++;
			 cout << "current SCORE: " << Score << endl;
		 }
	}
	else if (nameColumn == 4) {
		 if (tx_up > FORTH_COLUMN_UP && tx_low < FORTH_COLUMN_LOW)//bird box
			if (fall_1 < resolution.y / 2 - ty_low || fall_1 > resolution.y / 2 + ty_up) {
				GameStatus = false;
				cout << "GAME OVER" << endl;
				cout << "You Lost with the final score : " << Score << "! Retry?" << endl << "Please press Space Key." << endl << endl;
			}
		 if ((int)tx_low + WALL_WIDTH == FORTH_COLUMN_UP)
		 {
			 Score++;
			 cout << "current SCORE: " << Score << endl;
		 } 
	}
	

}

void Tema1::Update(float deltaTimeSeconds)
{

	// Update steps for translation, rotation, scale, in order to create animations
	glm::ivec2 resolution = window->GetResolution();

	if (GameStatus == true) {
		/* Draw bird */

		fall_1 -= MOVE_RATIO * deltaTimeSeconds * resolution.y;
		//check collision with the ground 
		if (fall_1 <= GROUND_COLLISION) {
			cout << " GAME OVER !";
			GameStatus = false;
		}

		//rotate body
		modelMatrix = Transform2D::Translate(b1, fall_1);
		if (jump == true && angularStep <= 0.5) {
			angularStep += deltaTimeSeconds;
			modelMatrix *= Transform2D::Translate(SQUARE_SIDE / 2, SQUARE_SIDE / 2);
			modelMatrix *= Transform2D::Rotate(angularStep);
			modelMatrix *= Transform2D::Translate(-SQUARE_SIDE / 2, -SQUARE_SIDE / 2);
		}
		else {
			modelMatrix *= Transform2D::Rotate(angularStep);
			modelMatrix *= Transform2D::Translate(-10, 15);
		}
		RenderMesh2D(meshes["body"], shaders["VertexColor"], modelMatrix);

		//rotate eye
		fall_2 -= MOVE_RATIO * deltaTimeSeconds * resolution.y;
		modelMatrix = Transform2D::Translate(b2, fall_2 + 2);
		if (jump == true && angularStep <= 0.5) {
			angularStep += deltaTimeSeconds;
			b2 = b2 - 2 * angularStep;
			fall_2 = fall_2 + 1 - angularStep;
			modelMatrix *= Transform2D::Translate(b2, fall_2);
		}
		else {
			modelMatrix *= Transform2D::Rotate(angularStep);
			modelMatrix *= Transform2D::Translate(-7, 25);
		}
		RenderMesh2D(meshes["eye"], shaders["VertexColor"], modelMatrix);

		//rotate head
		fall_3 -= MOVE_RATIO * deltaTimeSeconds * resolution.y;
		modelMatrix = Transform2D::Translate(b3, fall_2 - 8);
		if (jump == true && angularStep <= 0.5) {
			angularStep += deltaTimeSeconds;
			modelMatrix *= Transform2D::Translate(b3 - 10 * angularStep, fall_2 - 2 + 10 * angularStep);
		}
		else {
			modelMatrix *= Transform2D::Rotate(angularStep);
			modelMatrix *= Transform2D::Translate(-7, 30);
		}
		RenderMesh2D(meshes["head"], shaders["VertexColor"], modelMatrix);

		//rotate beak
		fall_4 -= MOVE_RATIO * deltaTimeSeconds * resolution.y;
		modelMatrix = Transform2D::Translate(b4, fall_3);
		if (jump == true && angularStep <= 0.5) {
			angularStep += deltaTimeSeconds;
			modelMatrix *= Transform2D::Translate(b4 - 10 * angularStep, fall_3 - 10 * angularStep);
		}
		else {
			modelMatrix *= Transform2D::Rotate(angularStep);
			modelMatrix *= Transform2D::Translate(-8, 30);
		}
		RenderMesh2D(meshes["beak"], shaders["VertexColor"], modelMatrix);

		/* Draw grass */
		modelMatrix = Transform2D::Translate(150, 150);
		RenderMesh(meshes["grass"], shaders["VertexColor"], modelMatrix);

		/* Draw ground */
		modelMatrix = Transform2D::Translate(300, 300);
		RenderMesh(meshes["ground"], shaders["VertexColor"], modelMatrix);

		/* Draw columns */
		jump = false;
		DrawColumn1(deltaTimeSeconds, resolution, 0);
		DrawColumn2(deltaTimeSeconds, resolution, 1);
		DrawColumn3(deltaTimeSeconds, resolution, 2);
		DrawColumn4(deltaTimeSeconds, resolution, 3);

		delimitArea(translateX_low1, translateY_low1, translateX_up1, translateY_up1, resolution, 1, m1);
		delimitArea(translateX_low2, translateY_low2, translateX_up2, translateY_up2, resolution, 2, m2);
		delimitArea(translateX_low3, translateY_low3, translateX_up3, translateY_up3, resolution, 3, m3);
		delimitArea(translateX_low4, translateY_low4, translateX_up4, translateY_up4, resolution, 4, m4);
	}

	else {
		/* Draw grass */
		modelMatrix = Transform2D::Translate(150, 150);
		RenderMesh(meshes["grass"], shaders["VertexColor"], modelMatrix);

		/* Draw ground */
		modelMatrix = Transform2D::Translate(300, 300);
		RenderMesh(meshes["ground"], shaders["VertexColor"], modelMatrix);

		DrawColumn1(deltaTimeSeconds, resolution, 0);
		DrawColumn2(deltaTimeSeconds, resolution, 1);
		DrawColumn3(deltaTimeSeconds, resolution, 2);
		DrawColumn4(deltaTimeSeconds, resolution, 3);
	}
}

void Tema1::FrameEnd()
{
	
}


void Tema1::OnInputUpdate(float deltaTime, int mods)
{

}

void Tema1::OnKeyPress(int key, int mods)
{	
	// add key press event
	if (GameStatus == true && key == GLFW_KEY_SPACE) {
		 fall_1 += 50; 
		 fall_2 += 50; 
		 fall_3 += 50;
		 fall_4 += 50;
		 jump = true;
	}
	else if (GameStatus == false && key == GLFW_KEY_SPACE) {
		Init();
	}
		
}

void Tema1::OnKeyRelease(int key, int mods)
{
	// add key release event

}

void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// add mouse move event
}

void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
}

void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Tema1::OnWindowResize(int width, int height)
{
}
