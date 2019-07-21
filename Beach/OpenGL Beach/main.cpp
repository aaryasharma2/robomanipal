//----------------------------------------------------------------------------------------
/**
 * \file    main.cpp
 * \author  Joran Jiri, Jaroslav Sloup, Tomas Barak, Petr Felkel
 * \date    2021
 * \brief   Simple implementation of beach scenery
 */
 //----------------------------------------------------------------------------------------

#include <time.h>
#include <list>
#include <iostream>
#include "pgr.h"
#include "render_stuff.h"
#include "spline.h"
#include <fstream>

using namespace std;

extern SCommonShaderProgram shaderProgram;
extern SkyboxFarPlaneShaderProgram skyboxProgram;
extern bool useLighting;

typedef std::list<void *> GameObjectsList; 

struct GameState {

  int windowWidth;    // set by reshape callback
  int windowHeight;   // set by reshape callback

  bool freeCameraMode;        // false;
  float cameraElevationAngle; // in degrees = initially 0.0f
  bool cameraSetup = false;

  bool gameOver;              // false;
  bool keyMap[KEYS_COUNT];    // false

  bool fog;
  bool lampPointLight;
  bool dayDirectionalLight;
  bool lighthouseSpotLight;

  bool boatCamera;
  bool droneCamera;
  bool drone2Camera;

  float defaultSpotLightPosition;

  float elapsedTime;
  float elapsedTimeSinceStop;

  bool changeElipse;

  float configData[80];

  int deletePalm[70];

  bool bannerDisplay;

  float skyboxIntensity;

  float sunAngle;

  bool move;
  
  
} gameState;

struct GameObjects {

  CameraObject* camera;

  IslandObject* island;
  BeachUmbrellaObject* beachUmbrella[22];
  PalmObject* palm[70];
  WaterObject* water;
  ChairObject* chair[22];
  BoatObject* boat;
  DroneObject* drone;
  SecondBoatObject* secondBoat;
  LighthouseObject* lighthouse;
  LampObject* lamp;
  BannerObject* banner;
  DroneObject* drone2;

  Fire* fire;
  ExplosionObject* explosion;

  GameObjectsList explosions;

  ConeObject* cone;

} gameObjects;

void moveForwardCameraFaster(float deltaSpeed = gameState.configData[7]) {
    if (gameState.freeCameraMode) {
        gameObjects.camera->speed =
            std::min(gameObjects.camera->speed + deltaSpeed, gameState.configData[7]);
    }
}


void moveBackwardCameraFaster(float deltaSpeed = gameState.configData[7]) {
    if (gameState.freeCameraMode) {
        gameObjects.camera->speed =
            std::min(gameObjects.camera->speed - deltaSpeed, -gameState.configData[7]);
    }
}



void increaseCameraSpeed(float deltaSpeed = gameState.configData[6]) {
    if (gameState.freeCameraMode) {
        gameObjects.camera->speed =
        std::min(gameObjects.camera->speed + deltaSpeed, gameState.configData[7]);
    }
}



void decreaseCameraSpeed(float deltaSpeed = gameState.configData[6]) {
    if (gameState.freeCameraMode) {
        gameObjects.camera->speed =
        std::max(gameObjects.camera->speed - deltaSpeed, -gameState.configData[7]);
    }
}

void increaseBoatSpeed(float deltaSpeed = gameState.configData[8]) {
    gameObjects.boat->speed =
    std::min(gameObjects.boat->speed + deltaSpeed, gameState.configData[9]);
}

void decreaseBoatSpeed(float deltaSpeed = gameState.configData[8]) {
        gameObjects.boat->speed =
        std::max(gameObjects.boat->speed - deltaSpeed, 0.0f);
}


void turnCameraLeft(float deltaAngle) {

    gameObjects.camera->viewAngle += deltaAngle;

    if (gameObjects.camera->viewAngle > 360.0f)
        gameObjects.camera->viewAngle -= 360.0f;

    float angle = glm::radians(gameObjects.camera->viewAngle);

    gameObjects.camera->direction.x = cos(angle);
    gameObjects.camera->direction.y = sin(angle);
}

void turnCameraRight(float deltaAngle) {

    gameObjects.camera->viewAngle -= deltaAngle;

    if (gameObjects.camera->viewAngle < 0.0f)
        gameObjects.camera->viewAngle += 360.0f;

    float angle = glm::radians(gameObjects.camera->viewAngle);

    gameObjects.camera->direction.x = cos(angle);
    gameObjects.camera->direction.y = sin(angle);
}

void turnBoatRight(float deltaAngle) {

    gameObjects.boat->viewAngle -= deltaAngle;

    if (gameObjects.boat->viewAngle < 0.0f)
        gameObjects.boat->viewAngle += 360.0f;

    float angle = glm::radians(gameObjects.boat->viewAngle);

    gameObjects.boat->direction.x = cos(angle);
    gameObjects.boat->direction.y = sin(angle);
}

void turnBoatLeft(float deltaAngle) {

  gameObjects.boat->viewAngle += deltaAngle;

  if(gameObjects.boat->viewAngle > 360.0f)
    gameObjects.boat->viewAngle -= 360.0f;

  float angle = glm::radians(gameObjects.boat->viewAngle);

  gameObjects.boat->direction.x = cos(angle);
  gameObjects.boat->direction.y = sin(angle);
}


void cleanUpObjects(void) {

    delete gameObjects.camera;
    gameObjects.camera = NULL;
    delete gameObjects.drone;
    gameObjects.drone = NULL;
    delete gameObjects.drone2;
    gameObjects.drone2 = NULL;
    delete gameObjects.cone;
    gameObjects.cone = NULL;
    delete gameObjects.boat;
    gameObjects.boat = NULL;
    delete gameObjects.secondBoat;
    gameObjects.secondBoat = NULL;
    delete gameObjects.lighthouse;
    gameObjects.lighthouse = NULL;
    delete gameObjects.lamp;
    gameObjects.lamp = NULL;
    delete gameObjects.island;
    gameObjects.island = NULL;
    delete gameObjects.water;
    gameObjects.water = NULL;

    for (int i = 0; i < 70; i++) {
        delete gameObjects.palm[i];
        gameObjects.palm[i] = NULL;
    }

    for (int i = 0; i < 22; i++) {
        delete gameObjects.chair[i];
        gameObjects.chair[i] = NULL;
    }

    for (int i = 0; i < 22; i++) {
        delete gameObjects.beachUmbrella[i];
        gameObjects.beachUmbrella[i] = NULL;
    }

}

void loadConfig() {
    string line;
    std::ifstream config("config.txt");
    int counter = 0;
    int number = 0;
    int everyOther = 1;
    bool skip = true;
    int index = 0;
    if (config.is_open()) {
        while (getline(config, line)) {
            if (line.size() == 0) {
                continue;
            }
            if (index <= 27) {
                if (number == everyOther) {
                    cout << "INDEX: " << index << " , is line: " << line << endl;
                    gameState.configData[index] = stof(line);
                    index++;
                    everyOther += 2;
                }

                number++;
            }
            else if(index >= 28){
                if (skip) {
                    skip = false;
                    continue;
                }
                cout << "here" << endl;
                if (counter < 3) {
                    cout << line << endl;
                    gameState.configData[index++] = stof(line);
                    counter++;
                }
                else if (counter == 3) {
                    counter = 0;
                    continue;
                }

            }

        }

        config.close();
    }
}

void restartGame(void) {

  cleanUpObjects();
  loadConfig();

  gameState.elapsedTime = 0.001f * (float)glutGet(GLUT_ELAPSED_TIME); // milliseconds => seconds

  // SETUP OF CAMERA
  if (gameObjects.camera == NULL)
      gameObjects.camera = new CameraObject;

      gameObjects.camera->position = glm::vec3(0.4f, +2.8f, -0.7f);
      gameObjects.camera->viewAngle = +90.0; // degrees
      gameObjects.camera->direction = glm::vec3(cos(glm::radians(gameObjects.camera->viewAngle)), sin(glm::radians(gameObjects.camera->viewAngle)), 0.0f);
      gameObjects.camera->speed = 0.0f;
      gameObjects.camera->startTime = gameState.elapsedTime;
      gameObjects.camera->currentTime = gameObjects.camera->startTime;
      gameState.cameraElevationAngle = 10.0f;


  // SETUP OF ISLAND
  if (gameObjects.island == NULL) {
      gameObjects.island = new IslandObject;
      gameObjects.island->size = gameState.configData[15];
      gameObjects.island->direction = glm::vec3(1.0f, 5.0f, 5.0f);
      gameObjects.island->direction = glm::normalize(gameObjects.island->direction);
      gameObjects.island->position = glm::vec3(gameState.configData[28], gameState.configData[29], gameState.configData[30]);
  }
  
  // SETUP OF BEACH UMBRELLA
  float changePositionX = 1.8f;
  float changePositionY = 1.0f;
  for (int i = 0; i < 16; i++) {
      if (gameObjects.beachUmbrella[i] == NULL) {
          gameObjects.beachUmbrella[i] = new BeachUmbrellaObject;
          gameObjects.beachUmbrella[i]->size = gameState.configData[17];
          gameObjects.beachUmbrella[i]->direction = glm::vec3(1.0f, 0.0f, 0.0f);
          gameObjects.beachUmbrella[i]->direction = glm::normalize(gameObjects.beachUmbrella[i]->direction);
          if (i == 3) {
              changePositionY += 0.5f;
          }
          if (i == 7) {
              changePositionY -= 1.0f;
              changePositionX = 1.8;
          }
          if (i == 10) {
              changePositionY += 0.5f;
          }
          gameObjects.beachUmbrella[i]->position = glm::vec3(changePositionX, changePositionY, -0.9f);
          changePositionX -= 0.4f;
      }
  }

  // SETUP OF BEACH CHAIR
  changePositionX = 1.72f;
  changePositionY = 0.98f;
  for (int i = 0; i < 16; i++) {
      if (gameObjects.chair[i] == NULL) {
          gameObjects.chair[i] = new ChairObject;
          gameObjects.chair[i]->size = gameState.configData[19];
          gameObjects.chair[i]->direction = glm::vec3(0.0f, 1.0f, 0.0f);
          gameObjects.chair[i]->direction = glm::normalize(gameObjects.chair[i]->direction);
          if (i == 3) {
              changePositionY += 0.5f;
          }
          if (i == 7) {
              changePositionY -= 1.0f;
              changePositionX = 1.72;
          }
          if (i == 10) {
              changePositionY += 0.5f;
          }
          gameObjects.chair[i]->position = glm::vec3(changePositionX, changePositionY, -0.92f);
          changePositionX -= 0.4f;

      }
  }

  // SETUP OF RANDOM GENERATING PALMS IN A SPECIFIC RANGE
  changePositionX = -0.3f;
  changePositionY = -1.1f;
  for (int i = 0; i < 45; i++) {
      if (gameObjects.palm[i] == NULL) {
          gameState.deletePalm[i] = false;

          gameObjects.palm[i] = new PalmObject;
          gameObjects.palm[i]->size = gameState.configData[18];
          gameObjects.palm[i]->direction = glm::vec3(1.0f, 0.0f, 0.0f);
          gameObjects.palm[i]->direction = glm::normalize(gameObjects.palm[0]->direction);
          changePositionY += static_cast <float> (rand()) / static_cast <float> (RAND_MAX/(1.5-0));
          changePositionX -= static_cast <float> (rand()) / static_cast <float> (RAND_MAX/(1.5-0));
          gameObjects.palm[i]->position = glm::vec3(changePositionX, changePositionY, -0.8f);
          changePositionX = -0.3f;
          changePositionY = -1.1f;
      }
  }
  changePositionX = +2.2f;
  changePositionY = -1.3f;
  for (int i = 45; i < 70; i++) {
      if (gameObjects.palm[i] == NULL) {
          gameState.deletePalm[i] = false;

          gameObjects.palm[i] = new PalmObject;
          gameObjects.palm[i]->size = gameState.configData[18];
          gameObjects.palm[i]->direction = glm::vec3(1.0f, 0.0f, 0.0f);
          gameObjects.palm[i]->direction = glm::normalize(gameObjects.palm[0]->direction);
          changePositionY += static_cast <float> (rand()) / static_cast <float> (RAND_MAX / (1.5 - 0));
          changePositionX -= static_cast <float> (rand()) / static_cast <float> (RAND_MAX / (1.5 - 0));
          gameObjects.palm[i]->position = glm::vec3(changePositionX, changePositionY, -0.8f);
          changePositionX = +2.2f;
          changePositionY = -1.3f;
      }
  }

  // SETUP OF WATER
  if (gameObjects.water == NULL) {
      gameObjects.water = new WaterObject;
      gameObjects.water->wSize = glm::vec3(8, 8, 8);
      gameObjects.water->viewAngle = 0.0f;
      gameObjects.water->direction = glm::vec3(cos(glm::radians(gameObjects.water->viewAngle)), sin(glm::radians(gameObjects.water->viewAngle)), 0.0f);
      gameObjects.water->position = glm::vec3(0.0f, 0.0f, -1.2);
  }

  // SETUP OF LIGHTHOUSE
  if (gameObjects.lighthouse == NULL) {
      gameObjects.lighthouse = new LighthouseObject;
      gameObjects.lighthouse->size = gameState.configData[27];
      gameObjects.lighthouse->direction = glm::vec3(1.0f, 0.0f, 0.0f);
      gameObjects.lighthouse->direction = glm::normalize(gameObjects.palm[0]->direction);
      gameObjects.lighthouse->direction = glm::vec3(cos(glm::radians(gameObjects.water->viewAngle)), sin(glm::radians(gameObjects.water->viewAngle)), 0.0f);
      gameObjects.lighthouse->position = glm::vec3(gameState.configData[31], gameState.configData[32], gameState.configData[33]);
  }

  // SETUP OF LAMP
  if (gameObjects.lamp == NULL) {
      gameObjects.lamp = new LampObject;
      gameObjects.lamp->size = gameState.configData[26];
      gameObjects.lamp->direction = glm::vec3(1.0f, 0.0f, 0.0f);
      gameObjects.lamp->direction = glm::normalize(gameObjects.palm[0]->direction);
      gameObjects.lamp->direction = glm::vec3(cos(glm::radians(gameObjects.water->viewAngle)), sin(glm::radians(gameObjects.water->viewAngle)), 0.0f);
      gameObjects.lamp->position = glm::vec3(gameState.configData[34], gameState.configData[35], gameState.configData[36]);
  }

  // SETUP OF BOAT
  if (gameObjects.boat == NULL) {
      gameObjects.boat = new BoatObject;
      gameObjects.boat->size = gameState.configData[20];
      gameObjects.boat->viewAngle = 90.0f;
      gameObjects.boat->direction = glm::vec3(cos(glm::radians(gameObjects.camera->viewAngle)), sin(glm::radians(gameObjects.camera->viewAngle)), 0.0f);
      gameObjects.boat->position = glm::vec3(gameState.configData[37], gameState.configData[38], gameState.configData[39]);
      gameObjects.boat->speed = 0.0f;
      gameObjects.boat->destroyed = false;
      gameObjects.boat->startTime = gameState.elapsedTime;
      gameObjects.boat->currentTime = gameObjects.boat->startTime;
  }

  // SETUP OF DRONE
  if (gameObjects.drone == NULL) {
      gameObjects.drone = new DroneObject;
      gameObjects.drone->size = gameState.configData[24];
      gameObjects.drone->viewAngle = 0.0f;
      gameObjects.drone->direction = glm::vec3(cos(glm::radians(gameObjects.drone->viewAngle)), sin(glm::radians(gameObjects.drone->viewAngle)), 0.0f);
      gameObjects.drone->position = glm::vec3(gameState.configData[43], gameState.configData[44], gameState.configData[45]);
      gameObjects.drone->initPosition = glm::vec3(gameState.configData[43], gameState.configData[44], gameState.configData[45]);
      gameObjects.drone->speed = 1.2f;
      gameObjects.drone->startTime = gameState.elapsedTime;
      gameObjects.drone->currentTime = gameObjects.boat->startTime;
  }

  // SETUP OF DRONE2
  if (gameObjects.drone2 == NULL) {
      gameObjects.drone2 = new DroneObject;
      gameObjects.drone2->size = gameState.configData[24];
      gameObjects.drone2->viewAngle = 0.0f;
      gameObjects.drone2->direction = glm::vec3(cos(glm::radians(gameObjects.drone->viewAngle)), sin(glm::radians(gameObjects.drone->viewAngle)), 0.0f);
      gameObjects.drone2->position = glm::vec3(gameState.configData[46], gameState.configData[47], gameState.configData[48]);
      gameObjects.drone2->initPosition = glm::vec3(gameState.configData[46], gameState.configData[47], gameState.configData[48]);
      gameObjects.drone2->speed = 1.2f;
      gameObjects.drone2->startTime = gameState.elapsedTime;
      gameObjects.drone2->currentTime = gameObjects.boat->startTime;
  }

  // SETUP OF SECOND BOAT
  if (gameObjects.secondBoat == NULL) {
      gameObjects.secondBoat = new SecondBoatObject;
      gameObjects.secondBoat->size = gameState.configData[21];
      gameObjects.secondBoat->explode = false;
      gameObjects.secondBoat->viewAngle = 180.0f;
      gameObjects.secondBoat->direction = glm::vec3(cos(glm::radians(gameObjects.secondBoat->viewAngle)), sin(glm::radians(gameObjects.secondBoat->viewAngle)), 0.0f);
      gameObjects.secondBoat->position = glm::vec3(gameState.configData[40], gameState.configData[41], gameState.configData[42]);
      gameObjects.secondBoat->initPosition = glm::vec3(0.0f, 0.0f, -1.0f);
      gameObjects.secondBoat->speed = 0.0f;
      gameObjects.secondBoat->startTime = gameState.elapsedTime;
      gameObjects.secondBoat->currentTime = gameObjects.secondBoat->startTime;
  }

  // SETUP OF HARD CODED CONE
  if (gameObjects.cone == NULL) {
      gameObjects.cone = new ConeObject;
      gameObjects.cone->size = gameState.configData[23];
      gameObjects.cone->direction = glm::vec3(1.0f, 5.0f, 5.0f);
      gameObjects.cone->position = glm::vec3(gameState.configData[49], gameState.configData[50], gameState.configData[51]);
  }



  // reset key map
  for(int i=0; i<KEYS_COUNT; i++)
    gameState.keyMap[i] = false;

  gameState.lampPointLight = false;
  gameState.dayDirectionalLight = true;
  gameState.lighthouseSpotLight = false;
  gameState.fog = false;
  gameState.boatCamera = false;
  gameState.droneCamera = false;
  gameState.drone2Camera = false;
  gameState.bannerDisplay = false;
  gameState.changeElipse = false;
  gameState.move = false;
  gameState.skyboxIntensity = 1;
  gameState.defaultSpotLightPosition = -0.3f;

}

void createExplosion()
{
    gameObjects.explosion = new ExplosionObject;
    gameObjects.explosion->startTime = gameState.elapsedTime;
    gameObjects.explosion->currentTime = gameObjects.explosion->startTime;
    gameObjects.explosion->size = gameState.configData[21];
    gameObjects.explosion->direction = glm::vec3(0.0f, 0.0f, 1.0f);
    gameObjects.explosion->frameDuration = 0.1f;
    gameObjects.explosion->textureFrames = 20;
    gameObjects.explosion->finished = false;
    gameObjects.explosion->position = gameObjects.secondBoat->position;
    gameObjects.explosions.push_back(gameObjects.explosion);
}

void createBanner(void) {
    gameObjects.banner = new BannerObject;
    gameObjects.banner->size = gameState.configData[3];
    gameObjects.banner->position = glm::vec3(0.0f, 0.0f, 0.0f);
    gameObjects.banner->direction = glm::vec3(0.0f, 1.0f, 0.0f);
    gameObjects.banner->speed = 0.0f;
    gameObjects.banner->size = 1.0f;
    gameObjects.banner->destroyed = false;
    gameObjects.banner->startTime = gameState.elapsedTime;
    gameObjects.banner->currentTime = gameObjects.banner->startTime;
}


void drawWindowContents() {
  // setup parallel projection

  glm::mat4 orthoProjectionMatrix = glm::ortho(
    -gameState.configData[10], gameState.configData[10],
    -gameState.configData[11], gameState.configData[11],
    -10.0f* gameState.configData[12], 10.0f* gameState.configData[12]
  );
  // static viewpoint - top view
  glm::mat4 orthoViewMatrix = glm::lookAt(
    glm::vec3(0.0f, 0.0f, 1.0f),
    glm::vec3(0.0f, 0.0f, 0.0f),
    glm::vec3(0.0f, 1.0f, 0.0f)
  );

  glm::mat4 viewMatrix  = orthoViewMatrix;
  glm::mat4 projectionMatrix = orthoProjectionMatrix;
  glm::vec3 cameraUpVector = glm::vec3(0.0f, -3.0f, 0.0f);
  glm::vec3 cameraCenter = glm::vec3(-0.2f, -2.0f, -2.8f) + gameObjects.camera->direction;



  if(gameState.cameraSetup) {
      glm::vec3 cameraPosition;
      glm::vec3 cameraUpVector;
      glm::vec3 cameraViewDirection;
      if (gameState.boatCamera) {
          cameraPosition = glm::vec3(gameObjects.boat->position.x, gameObjects.boat->position.y, gameObjects.boat->position.z+0.1f);
          cameraUpVector = glm::vec3(0.0f, 0.0f, 2.0f);
          cameraViewDirection = gameObjects.boat->direction;
      }
      else if (gameState.droneCamera) {
          cameraPosition = glm::vec3(gameObjects.drone->position.x, gameObjects.drone->position.y, gameObjects.drone->position.z);
          cameraUpVector = glm::vec3(0.0f, 0.0f, +2.0f);
          cameraViewDirection = gameObjects.drone->direction + glm::vec3(0.0f, 0.0f, -1.0f);
      }
      else if (gameState.drone2Camera) {
          cameraPosition = glm::vec3(gameObjects.drone2->position.x, gameObjects.drone2->position.y, gameObjects.drone2->position.z);
          cameraUpVector = glm::vec3(0.0f, 0.0f, +2.0f);
          cameraViewDirection = gameObjects.drone2->direction + glm::vec3(0.0f, 0.0f, -1.0f);
      }
      else {
          cameraPosition = gameObjects.camera->position;
          cameraUpVector = glm::vec3(0.0f, 0.0f, 1.0f);
          cameraViewDirection = gameObjects.camera->direction;
      }
    glm::vec3 cameraCenter;

    glm::vec3 rotationAxis = glm::cross(cameraViewDirection, glm::vec3(0.0f, 0.0f, 1.0f));
    glm::mat4 cameraTransform = glm::rotate(glm::mat4(1.0f), glm::radians(gameState.cameraElevationAngle), rotationAxis);

    cameraUpVector = glm::vec3(cameraTransform * glm::vec4(cameraUpVector, 0.0f));
    cameraViewDirection = glm::vec3(cameraTransform * glm::vec4(cameraViewDirection, 0.0f));

    cameraCenter = cameraPosition + cameraViewDirection;

    viewMatrix = glm::lookAt(
      cameraPosition,
      cameraCenter,
      cameraUpVector
    );

    projectionMatrix = glm::perspective(glm::radians(60.0f), gameState.windowWidth/(float)gameState.windowHeight, 0.1f, 10.0f);
  }


  glUseProgram(shaderProgram.program);
  glUniform3fv(shaderProgram.spotlightPosition, 1, glm::value_ptr(glm::vec3(gameObjects.lighthouse->position + glm::vec3(-0.3f,-0.2f,0.5f))));
  glUniform3fv(shaderProgram.spotlightDirection, 1, glm::value_ptr(glm::vec3(gameObjects.lighthouse->direction + glm::vec3(+0.2f, gameState.defaultSpotLightPosition, -0.6f))));
  glUniform1f(shaderProgram.timeLocation, gameState.elapsedTime);
  glUniform1i(shaderProgram.sunLoc, gameState.dayDirectionalLight);
  glUniform1i(shaderProgram.flashLoc, gameState.lighthouseSpotLight);
  glUniform1i(shaderProgram.ptLightOnLoc, gameState.lampPointLight);
  glUniform1i(shaderProgram.fogLoc, gameState.fog);

  glUseProgram(skyboxProgram.program);
  gameState.skyboxIntensity = sin(gameState.elapsedTime * 0.1f);
  if (gameState.skyboxIntensity < 0) {
      glUniform1f(skyboxProgram.intensity, 0.1f);
  }
  else {
      if (gameState.skyboxIntensity < 0.1f || !gameState.dayDirectionalLight) {
          glUniform1f(skyboxProgram.intensity, 0.1f);
      }
      else {
          glUniform1f(skyboxProgram.intensity, gameState.skyboxIntensity);
      }
  }
  
  glUseProgram(0);


  glEnable(GL_STENCIL_TEST);
  glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

  glStencilFunc(GL_ALWAYS, 1, 255);
  drawIsland(gameObjects.island, viewMatrix, projectionMatrix);
  glStencilFunc(GL_ALWAYS, 2, 255);
  drawWater(gameObjects.water, viewMatrix, projectionMatrix, gameState.elapsedTime);
  glStencilFunc(GL_ALWAYS, 3, 255);
  drawCone(gameObjects.cone, viewMatrix, projectionMatrix);
  for (int i = 0; i < 16; i++) {
      glStencilFunc(GL_ALWAYS, 4+i, 255);
      drawBeachUmbrella(gameObjects.beachUmbrella[i], viewMatrix, projectionMatrix);
  }

  for (int i = 0; i < 16; i++) {
      glStencilFunc(GL_ALWAYS, 20 + i, 255);
      drawChair(gameObjects.chair[i], viewMatrix, projectionMatrix);
  }

  for (int i = 0; i < 70; i++) {
      glStencilFunc(GL_ALWAYS, 36 + i, 255);
      if (!gameState.deletePalm[i]) {
          drawPalm(gameObjects.palm[i], viewMatrix, projectionMatrix);
      }
  }

  glStencilFunc(GL_ALWAYS, 106, 255);
  drawBoat(gameObjects.boat, viewMatrix, projectionMatrix);

  glStencilFunc(GL_ALWAYS, 107, 255);
  drawDrone(gameObjects.drone, viewMatrix, projectionMatrix);
  drawDrone2(gameObjects.drone2, viewMatrix, projectionMatrix);

  glStencilFunc(GL_ALWAYS, 108, 255);
  drawSecondBoat(gameObjects.secondBoat, viewMatrix, projectionMatrix);

  glStencilFunc(GL_ALWAYS, 109, 255);
  drawSkybox(viewMatrix, projectionMatrix, gameState.elapsedTime);

  drawLighthouse(gameObjects.lighthouse, viewMatrix, projectionMatrix);

  drawLamp(gameObjects.lamp, viewMatrix, projectionMatrix);

  glDisable(GL_DEPTH_TEST);

  for (GameObjectsList::iterator it = gameObjects.explosions.begin(); it != gameObjects.explosions.end(); ++it)
  {
      ExplosionObject* explosion = static_cast<ExplosionObject*>(*it);
      drawExplosion(explosion, viewMatrix, projectionMatrix);
  }
  glEnable(GL_DEPTH_TEST);

  if (gameState.bannerDisplay == true) {
          cout << "Drawing banner" << endl;
          drawBanner(gameObjects.banner, orthoViewMatrix, orthoProjectionMatrix);
  }

}

// Called to update the display. You should call glutSwapBuffers after all of your
// rendering to display what you rendered.
void displayCallback() {
  GLbitfield mask = GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT;

  glClear(mask);

  drawWindowContents();

  glutSwapBuffers();
}

// Called whenever the window is resized. The new window size is given, in pixels.
// This is an opportunity to call glViewport or glScissor to keep up with the change in size.
void reshapeCallback(int newWidth, int newHeight) {

  gameState.windowWidth = newWidth;
  gameState.windowHeight = newHeight;

  glViewport(0, 0, (GLsizei) newWidth, (GLsizei) newHeight);
}

bool checkSceneBounds(glm::vec3 pos) {
    if (pos.x > (gameObjects.water->wSize.x) || pos.x < (-gameObjects.water->wSize.x) ||
        pos.y >(gameObjects.water->wSize.y) || pos.y < (-gameObjects.water->wSize.y)){
        return false;
    }
    return true;
}

bool collisionDetected(glm::vec3 firstObjectCoordinate, float firstObjectSize, glm::vec3 secondObjectCoordinate, float secondObjectSize) {
    return (pow((firstObjectSize + secondObjectSize), 2) > (firstObjectCoordinate.y - secondObjectCoordinate.y) * (firstObjectCoordinate.y - secondObjectCoordinate.y) +
                                                            (firstObjectCoordinate.x - secondObjectCoordinate.x) * (firstObjectCoordinate.x - secondObjectCoordinate.x));
}

void updateDrone(float elapsedTime) {
    gameObjects.drone->currentTime = elapsedTime;
    float curveParamT = gameObjects.drone->speed * (gameObjects.drone->currentTime - gameObjects.drone->startTime);
    gameObjects.drone->position = gameObjects.drone->initPosition + evaluateCatmullRollClosedCurve(curveData, curveSize, curveParamT);
    gameObjects.drone->direction = glm::normalize(evaluateCatmullRollClosedCurve_1stDerivative(curveData, curveSize, curveParamT));

    gameObjects.drone2->currentTime = elapsedTime;
    float curve2ParamT = gameObjects.drone2->speed * (gameObjects.drone2->currentTime - gameObjects.drone2->startTime);
    gameObjects.drone2->position = gameObjects.drone2->initPosition + evaluateCatmullRollClosedCurve(curve2Data, curve2Size, curve2ParamT);
    gameObjects.drone2->direction = glm::normalize(evaluateCatmullRollClosedCurve_1stDerivative(curve2Data, curve2Size, curve2ParamT));
}

void updateBoat(float elapsedTime) {
    float timeDelta = (elapsedTime - gameObjects.secondBoat->startTime)/5;
    gameObjects.secondBoat->position.x = gameObjects.secondBoat->initPosition.x + 5 * cos((timeDelta));
    gameObjects.secondBoat->position.y = gameObjects.secondBoat->initPosition.y + 5 * sin((timeDelta));
    gameObjects.secondBoat->viewAngle += 0.4f;
}

void updateObjects(float elapsedTime) {
    float timeDelta = elapsedTime - gameObjects.boat->currentTime;
    gameObjects.boat->currentTime = elapsedTime;
    glm::vec3 newPosition = gameObjects.boat->position + timeDelta * gameObjects.boat->speed * gameObjects.boat->direction;

    if (!checkSceneBounds(newPosition)) {
        gameObjects.boat->speed = 0;
    }

    if (collisionDetected(newPosition, gameState.configData[20], gameObjects.island->position, gameState.configData[15] - 0.5)) {
        gameObjects.boat->speed = 0;
    }
    else {
        gameObjects.boat->position += timeDelta * gameObjects.boat->speed * gameObjects.boat->direction;
    }

    updateDrone(elapsedTime);
    

    if (gameObjects.secondBoat->explode) {
        gameObjects.secondBoat->position.z -= 0.001f;
    }
    else {
        updateBoat(gameState.elapsedTime);
    }

    // UPDATE CAMERA POSITION
    gameObjects.camera->currentTime = elapsedTime;
    if (gameState.keyMap[KEY_SHIFT] && gameState.keyMap[KEY_UP_ARROW] || gameState.keyMap[KEY_SHIFT] && gameState.keyMap[KEY_DOWN_ARROW]) {
        gameObjects.camera->position += timeDelta * gameObjects.camera->speed*2 * gameObjects.camera->direction;
    }
    else {
        gameObjects.camera->position += timeDelta * gameObjects.camera->speed * gameObjects.camera->direction;
    }

    GameObjectsList::iterator each_pic = gameObjects.explosions.begin();
    while (each_pic != gameObjects.explosions.end())
    {
        ExplosionObject* explosion = static_cast<ExplosionObject*>(*each_pic);

        // update explosion
        explosion->currentTime = elapsedTime;

        if (explosion->currentTime > explosion->startTime + explosion->textureFrames * explosion->frameDuration) {
            explosion->finished = true;
        }
        if (explosion->finished){
            each_pic = gameObjects.explosions.erase(each_pic);
        } else {
            ++each_pic;
        }
    }

}

// Callback responsible for the scene update
void timerCallback(int) {

  // update scene time
  gameState.elapsedTime = 0.001f * (float)glutGet(GLUT_ELAPSED_TIME); // milliseconds => seconds

  // call appropriate actions according to the currently pressed keys in key map
  // (combinations of keys are supported but not used in this implementation)

  if (gameState.keyMap[KEY_UP_ARROW] && gameState.keyMap[KEY_SHIFT]) {
      cout << "hajo" << endl;
      moveForwardCameraFaster();
  }

  if (gameState.keyMap[KEY_DOWN_ARROW] && gameState.keyMap[KEY_SHIFT]) {
      cout << "bajo" << endl;
      moveBackwardCameraFaster();
  }

  if(gameState.keyMap[KEY_RIGHT_ARROW] == true)
    turnCameraRight(gameState.configData[1]);

  if(gameState.keyMap[KEY_LEFT_ARROW] == true)
    turnCameraLeft(gameState.configData[1]);

  if(gameState.keyMap[KEY_UP_ARROW] == true)
    increaseCameraSpeed();

  if(gameState.keyMap[KEY_DOWN_ARROW] == true)
    decreaseCameraSpeed();

  

  // update objects in the scene
  updateObjects(gameState.elapsedTime);

  if ((gameState.bannerDisplay == true) && (gameObjects.banner != NULL)) {
      gameObjects.banner->currentTime = gameState.elapsedTime;
  }

  if (gameState.bannerDisplay == true) {
      if (gameObjects.banner == NULL) {
          cout << "If not created, create banner" << endl;
          createBanner();
      }
  }

  // set timeCallback next invocation
  glutTimerFunc(33, timerCallback, 0);

  

  glutPostRedisplay();
}

// Called when mouse is moving while no mouse buttons are pressed.
void passiveMouseMotionCallback(int mouseX, int mouseY) {

  if(mouseY != gameState.windowHeight/2) {

    float cameraElevationAngleDelta = 0.5f * (mouseY - gameState.windowHeight/2);

    if(fabs(gameState.cameraElevationAngle+cameraElevationAngleDelta) < gameState.configData[13])
      gameState.cameraElevationAngle += cameraElevationAngleDelta;

      // set mouse pointer to the window center
      glutWarpPointer(gameState.windowWidth/2, gameState.windowHeight/2);

      glutPostRedisplay();
    }
}

// Called whenever a key on the keyboard was pressed. The key is given by the "keyPressed"
// parameter, which is in ASCII. It's often a good idea to have the escape key (ASCII value 27)
// to call glutLeaveMainLoop() to exit the program.
void keyboardCallback(unsigned char keyPressed, int mouseX, int mouseY) {
    switch (keyPressed) {
    case 'w':
        increaseBoatSpeed();
        break;
    case 's':
        decreaseBoatSpeed();
        break;
    case 'a':
        turnBoatLeft(gameState.configData[0]);
        break;
    case 'd':
        turnBoatRight(gameState.configData[0]);
        break;
    case 27: // escape
#ifndef __APPLE__
        glutLeaveMainLoop();
#else
        exit(0);
#endif
        break;
    case 'r': // restart game
        restartGame();
        break;
    case 'h':
        //sideCam();
        glutPassiveMotionFunc(NULL);
    case 'f': // teleport space ship
        gameState.fog = !gameState.fog;
        break;
    case 'g':
        gameState.dayDirectionalLight = !gameState.dayDirectionalLight;
    case 'c': // switch camera
        gameState.boatCamera = false;
        gameState.droneCamera = false;
        gameState.drone2Camera = false;
        gameObjects.camera->position = glm::vec3(-0.2f, 0.0f, -0.8f);
        gameObjects.camera->viewAngle = 90.0f; // degrees
        gameObjects.camera->direction = glm::vec3(cos(glm::radians(gameObjects.camera->viewAngle)), sin(glm::radians(gameObjects.camera->viewAngle)), 0.0f);
        gameObjects.camera->speed = 0.0f;
        gameObjects.camera->startTime = gameState.elapsedTime;
        gameObjects.camera->currentTime = gameObjects.camera->startTime;
        gameState.cameraSetup = true;
        gameState.freeCameraMode = true;
        glutPassiveMotionFunc(passiveMouseMotionCallback);
        break;

    case 'm':
        if (gameState.defaultSpotLightPosition < 0.6f) {
            gameState.defaultSpotLightPosition += 0.1f;
        }
        break;
    case 'n':
        if (gameState.defaultSpotLightPosition > -0.9f) {
            gameState.defaultSpotLightPosition -= 0.1f;
        }
        break;
    default:
        ; // printf("Unrecognized key pressed\n");
    }
}

  

void keyboardUpCallback(unsigned char keyReleased, int mouseX, int mouseY) {

  switch(keyReleased) {
    case ' ':
      gameState.keyMap[KEY_SPACE] = false;
      break;

    default:
      ; // printf("Unrecognized key released\n");
  }
}

void specialKeyboardCallback(int specKeyPressed, int mouseX, int mouseY) {

  if(gameState.gameOver == true)
    return;

  switch (specKeyPressed) {
    case GLUT_KEY_SHIFT_L:
      gameState.keyMap[KEY_SHIFT] = true;
      break;
    case GLUT_KEY_RIGHT:
      gameState.keyMap[KEY_RIGHT_ARROW] = true;
      break;
    case GLUT_KEY_LEFT:
      gameState.keyMap[KEY_LEFT_ARROW] = true;
      break;
    case GLUT_KEY_UP:
      gameState.keyMap[KEY_UP_ARROW] = true;
      break;
    case GLUT_KEY_DOWN:
      gameState.keyMap[KEY_DOWN_ARROW] = true;
      break;
    case GLUT_KEY_F1:
        gameState.cameraSetup = true;
        gameState.freeCameraMode = true;
        gameState.boatCamera = false;
        gameState.drone2Camera = false;
        gameState.droneCamera = true;
        break;
    case GLUT_KEY_F2:
        gameState.cameraSetup = true;
        gameState.freeCameraMode = true;
        gameState.boatCamera = false;
        gameState.droneCamera = false;
        gameState.drone2Camera = true;
        break;
    default:
      ;
  }
}

void specialKeyboardUpCallback(int specKeyReleased, int mouseX, int mouseY) {

  if(gameState.gameOver == true)
    return;

  switch (specKeyReleased) {
    case GLUT_KEY_SHIFT_L:

      gameState.keyMap[KEY_SHIFT] = false;
      break;
	case GLUT_KEY_RIGHT:
      gameState.keyMap[KEY_RIGHT_ARROW] = false;
      break;
    case GLUT_KEY_LEFT:
      gameState.keyMap[KEY_LEFT_ARROW] = false;
      break;
    case GLUT_KEY_UP:
      gameState.keyMap[KEY_UP_ARROW] = false;
      break;
    case GLUT_KEY_DOWN:
      gameState.keyMap[KEY_DOWN_ARROW] = false;
      break;
		default:
      ; // printf("Unrecognized special key released\n");
  }
}

void mouseCallback(int buttonPressed, int buttonState, int mouseX, int mouseY) {
    cout << "mouse x: " << mouseX << " , mouse y: " << mouseY << endl;

    if (((buttonPressed == GLUT_LEFT_BUTTON) && (buttonState == GLUT_DOWN)))
    {
        unsigned char charObjectID = 0;
        glReadPixels(mouseX, WINDOW_HEIGHT - mouseY - 1, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_BYTE, &charObjectID);

        int objectID = static_cast<int>(charObjectID);
        
        if (objectID == 3) {
            cout << "cone touched" << endl;
            gameObjects.cone->size += 0.1;

        }

        for (int i = 36; i < 106; i++) {
            if (i == objectID) {
                gameState.deletePalm[i-36] = true;
            }
        }

        for (int i = 4; i < 20; i++) {
            if (i == objectID) {
                cout << "umbrella touched" << endl;
            }
        }

        for (int i = 20; i < 36; i++) {
            if (i == objectID) {
                cout << "lehatko touched" << endl;
                gameState.move = true;
            }
        }

        if (objectID == 108) {
            gameObjects.secondBoat->explode = true;
            createExplosion();
        }

        if (objectID == 107) {
            cout << "Touched drone" << endl;
            gameState.changeElipse = !gameState.changeElipse;
        }
    }
}


void sceneSettings(int choice) {
    switch (choice) {
    case 1: // Static 1
        gameState.boatCamera = false;
        gameState.droneCamera = false;
        gameState.drone2Camera = false;
        gameObjects.camera->position = glm::vec3(0.4f, +2.8f, -0.7f);
        gameObjects.camera->viewAngle = -90.0; // degrees
        gameObjects.camera->direction = glm::vec3(cos(glm::radians(gameObjects.camera->viewAngle)), sin(glm::radians(gameObjects.camera->viewAngle)), 0.0f);
        gameObjects.camera->speed = 0.0f;
        gameObjects.camera->startTime = gameState.elapsedTime;
        gameObjects.camera->currentTime = gameObjects.camera->startTime;
        gameState.cameraSetup = true;
        gameState.freeCameraMode = false;
        break;
    case 2: // Static 2
        gameState.boatCamera = false;
        gameState.droneCamera = false;
        gameState.drone2Camera = false;
        gameObjects.camera->position = glm::vec3(0.0f, +1.8f, +0.7f);
        gameObjects.camera->viewAngle = -90.0; // degrees
        gameObjects.camera->direction = glm::vec3(cos(glm::radians(gameObjects.camera->viewAngle)), sin(glm::radians(gameObjects.camera->viewAngle)), -3.0f);
        gameObjects.camera->speed = 0.0f;
        gameObjects.camera->startTime = gameState.elapsedTime;
        gameObjects.camera->currentTime = gameObjects.camera->startTime;
        gameState.cameraSetup = true;
        gameState.freeCameraMode = false;
        break;

    case 3: // Static 3
        gameState.boatCamera = false;
        gameState.droneCamera = false;
        gameObjects.camera->position = glm::vec3(0.0f, -3.0f, +3.5f);
        gameObjects.camera->viewAngle = +90.0; // degrees
        gameObjects.camera->direction = glm::vec3(cos(glm::radians(gameObjects.camera->viewAngle)), sin(glm::radians(gameObjects.camera->viewAngle)), -3.0f);
        gameObjects.camera->speed = 0.0f;
        gameObjects.camera->startTime = gameState.elapsedTime;
        gameObjects.camera->currentTime = gameObjects.camera->startTime;
        gameState.cameraSetup = true;
        gameState.freeCameraMode = false;
        break;
    case 4: // Free
        gameState.boatCamera = false;
        gameState.droneCamera = false;
        gameState.drone2Camera = false;
        gameObjects.camera->position = glm::vec3(-0.2f, 0.0f, -0.8f);
        gameObjects.camera->viewAngle = 90.0f; // degrees
        gameObjects.camera->direction = glm::vec3(cos(glm::radians(gameObjects.camera->viewAngle)), sin(glm::radians(gameObjects.camera->viewAngle)), 0.0f);
        gameObjects.camera->speed = 0.0f;
        gameObjects.camera->startTime = gameState.elapsedTime;
        gameObjects.camera->currentTime = gameObjects.camera->startTime;
        gameState.cameraSetup = true;
        gameState.freeCameraMode = true;
        glutPassiveMotionFunc(passiveMouseMotionCallback);
        //glutWarpPointer(gameState.windowWidth / 2, gameState.windowHeight / 2);
        break;
    case 5:
        gameState.fog = true;
        break;
    case 6:
        gameState.fog = false;
        break;
    case 7:
        gameState.dayDirectionalLight = true;
        break;
    case 8:
        gameState.dayDirectionalLight = false;
        break;
    case 9:
        gameState.lighthouseSpotLight = true;
        break;
    case 10:
        gameState.lighthouseSpotLight = false;
        break;
    case 11:
        restartGame();
        break;
    case 12:
        exit(0);
    case 13:
        gameState.bannerDisplay = true;
        break;
    case 14:
        gameState.bannerDisplay = false;
        break;
    case 15:
        gameState.lampPointLight = true;
        break;
    case 16:
        gameState.lampPointLight = false;
        break;
    case 17:
        gameState.cameraSetup = true;
        gameState.freeCameraMode = true;
        gameState.droneCamera = false;
        gameState.boatCamera = true;
        break;
    case 18:
        gameState.cameraSetup = true;
        gameState.freeCameraMode = true;
        gameState.boatCamera = false;
        gameState.drone2Camera = false;
        gameState.droneCamera = true;
        break;
    case 19:
        gameState.cameraSetup = true;
        gameState.freeCameraMode = true;
        gameState.boatCamera = false;
        gameState.droneCamera = false;
        gameState.drone2Camera = true;
        break;
    }

    


}

 
void menu(void){
    int subCam = glutCreateMenu(sceneSettings);
    glutAddMenuEntry("STATIC CAMERA SIDE", 1);
    glutAddMenuEntry("STATIC CAMERA SIDE 2", 2);
    glutAddMenuEntry("STATIC CAMERA TOP", 3);
    glutAddMenuEntry("BOAT CAMEREA", 17);
    glutAddMenuEntry("FREE CAMERA", 4);
    glutAddMenuEntry("DRONE CAMERA", 18);
    glutAddMenuEntry("DRONE CAMERA", 19);

    int fogToggler = glutCreateMenu(sceneSettings);
    glutAddMenuEntry("FOG ENABLE", 5);
    glutAddMenuEntry("FOG DISABLE", 6);

    int sunToggler = glutCreateMenu(sceneSettings);
    glutAddMenuEntry("SUN ENABLE", 7);
    glutAddMenuEntry("SUN DISABLE", 8);

    int flashToggler = glutCreateMenu(sceneSettings);
    glutAddMenuEntry("LIGHTHOUSE LIGHT ENABLE", 9);
    glutAddMenuEntry("LIGHTHOUSE LIGHT DISABLE", 10);

    int bannerToggler = glutCreateMenu(sceneSettings);
    glutAddMenuEntry("BANNER RUN", 13);
    glutAddMenuEntry("BANNER HIDE", 14);

    int ptLightToggler = glutCreateMenu(sceneSettings);
    glutAddMenuEntry("LAMP LIGHT ENABLE", 15);
    glutAddMenuEntry("LAMP LIGHT DISABLE", 16);


    glutCreateMenu(sceneSettings);
    glutAddSubMenu("CAMERA", subCam);
    glutAddSubMenu("FOG", fogToggler);
    glutAddSubMenu("SUN", sunToggler);
    glutAddSubMenu("LIGHTHOUSE LIGHT", flashToggler);
    glutAddSubMenu("BANNER", bannerToggler);
    glutAddSubMenu("LAMP LIGHT", ptLightToggler);
    glutAddMenuEntry("RESTART", 11);
    glutAddMenuEntry("EXIT", 12);


    glutAttachMenu(GLUT_RIGHT_BUTTON);
}



// Called after the window and OpenGL are initialized. Called exactly once, before the main loop.
void initializeApplication() {

  // initialize random seed
  srand ((unsigned int)time(NULL));

  // initialize OpenGL
  glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
  glEnable(GL_DEPTH_TEST);

  useLighting = true;

  

  

  // initialize shaders
  initializeShaderPrograms();
  // create geometry for all models used
  initializeModels();



  restartGame();
}

void finalizeApplication(void) {

  cleanUpObjects();

  //delete gameObjects.spaceShip;
  //gameObjects.spaceShip = NULL;

  // delete buffers - space ship, asteroid, missile, ufo, banner, and explosion
  cleanupModels();

  // delete shaders
  cleanupShaderPrograms();
}

int main(int argc, char** argv) {

  // initialize windowing system
  glutInit(&argc, argv);
  glutInitContextVersion(pgr::OGL_VER_MAJOR, pgr::OGL_VER_MINOR);
  glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH | GLUT_STENCIL);

  // initial window size
  glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
  glutCreateWindow(WINDOW_TITLE);

  glutDisplayFunc(displayCallback);
  // register callback for change of window size
  glutReshapeFunc(reshapeCallback);
  // register callbacks for keyboard
  glutKeyboardFunc(keyboardCallback);
  glutKeyboardUpFunc(keyboardUpCallback);
  glutSpecialFunc(specialKeyboardCallback);     // key pressed
  glutSpecialUpFunc(specialKeyboardUpCallback); // key released

  glutMouseFunc(mouseCallback);

  glutTimerFunc(33, timerCallback, 0);

  // zavola funkci menu
  menu();

  // initialize PGR framework (GL, DevIl, etc.)
  if(!pgr::initialize(pgr::OGL_VER_MAJOR, pgr::OGL_VER_MINOR))
    pgr::dieWithError("pgr init failed, required OpenGL not supported?");

  initializeApplication();

#ifndef __APPLE__
  glutCloseFunc(finalizeApplication);
#else
  glutWMCloseFunc(finalizeApplication);
#endif

  glutMainLoop();

  return 0;
}
