//----------------------------------------------------------------------------------------
/**
 * \file    render_stuff.h
 * \author  Jordan Jiri, Jaroslav Sloup, Tomas Barak, Petr Felkel
 * \date    2021
 * \brief   Rendering stuff - drawing functions for models, etc.
 */
//----------------------------------------------------------------------------------------

#ifndef __RENDER_STUFF_H
#define __RENDER_STUFF_H

#include "data.h"

// defines geometry of object in the scene (space ship, ufo, asteroid, etc.)
// geometry is shared among all instances of the same object type
typedef struct MeshGeometry {
  GLuint        vertexBufferObject;   // identifier for the vertex buffer object
  GLuint        elementBufferObject;  // identifier for the element buffer object
  GLuint        vertexArrayObject;    // identifier for the vertex array object
  unsigned int  numTriangles;         // number of triangles in the mesh
  // material
  glm::vec3     ambient;
  glm::vec3     diffuse;
  glm::vec3     specular;
  float         shininess;
  GLuint        texture;

} MeshGeometry;


// parameters of individual objects in the scene (e.g. position, size, speed, etc.)
typedef struct Object {
  glm::vec3 position;
  glm::vec3 direction;
  float     speed;
  float     size;

  bool destroyed;

  float startTime;
  float currentTime;

} Object;

typedef struct Camera : public Object {

	float viewAngle; // in degrees

} CameraObject;

typedef struct Palm : public Object {
} PalmObject;

typedef struct Island : public Object {
} IslandObject;

typedef struct Water : public Object {
    glm::vec3 wSize;
    float viewAngle;
} WaterObject;

typedef struct BeachUmbrella : public Object {
} BeachUmbrellaObject;

typedef struct Lamp : public Object {
} LampObject;

typedef struct Chair : public Object {
} ChairObject;

typedef struct Drone : public Object {
    glm::vec3 initPosition;
    float viewAngle;
} DroneObject;

typedef struct SecondBoat : public Object {
    bool explode;
    glm::vec3 initPosition;
    float viewAngle;
} SecondBoatObject;

typedef struct ConeObject : public Object {
} ConeObject;

typedef struct Boat : public Object {
    float viewAngle;
} BoatObject;

typedef struct Fire : public Object {
    int frames;
    float frameDuration;
} Fire;

typedef struct ExplosionObject : public Object
{
    int textureFrames;
    float frameDuration;
    bool finished;
} ExplosionObject;

typedef struct Lighthouse : public Object {
} LighthouseObject;

typedef struct BannerObject : public Object {
} BannerObject;

typedef struct SpaceShipObject : public Object {

  float viewAngle; // in degrees

} SpaceShipObject;

typedef struct AsteroidObject : public Object {

  float rotationSpeed;

} AsteroidObject;

typedef struct MissileObject : public Object {

} MissileObject;

typedef struct UfoObject : public Object {

  float     rotationSpeed;
  glm::vec3 initPosition;

} UfoObject;



typedef struct _commonShaderProgram {
  // identifier for the shader program
  GLuint program;          // = 0;
  // vertex attributes locations
  GLint posLocation;       // = -1;
  GLint colorLocation;     // = -1;
  GLint normalLocation;    // = -1;
  GLint texCoordLocation;  // = -1;
  // uniforms locations
  GLint PVMmatrixLocation;    // = -1;
  GLint VmatrixLocation;      // = -1;  view/camera matrix
  GLint MmatrixLocation;      // = -1;  modeling matrix
  GLint normalMatrixLocation; // = -1;  inverse transposed Mmatrix

  GLint timeLocation;         // = -1; elapsed time in seconds

  // material 
  GLint diffuseLocation;    // = -1;
  GLint ambientLocation;    // = -1;
  GLint specularLocation;   // = -1;
  GLint shininessLocation;  // = -1;
  // texture
  GLint useTextureLocation; // = -1; 
  GLint texSamplerLocation; // = -1;
  GLint texLocation;
  
  // reflector related uniforms
  GLint spotlightPosition;  // = -1; 
  GLint spotlightDirection; // = -1;
  //torch
  GLint ptLightOnLoc;

  GLfloat sunAngle;

  GLint sunLoc;
  GLint fogLoc;
  GLint flashLoc;

} SCommonShaderProgram;

typedef struct SkyboxFarPlaneShaderProgram {
    // identifier for the shader program
    GLuint program;                 // = 0;
    // vertex attributes locations
    GLint screenCoordLocation;      // = -1;
    // uniforms locations
    GLint inversePVmatrixLocation; // = -1;
    GLint skyboxSamplerLocation;    // = -1;
    GLfloat intensity;
} SkyboxFarPlaneShaderProgram;

typedef struct ExplosionShaderProgram
{
    // identifier for the shader program
    GLuint program; // = 0;
    // vertex attributes locations
    GLint posLocation; // = -1;
    GLint texCoordLocation; // = -1;
    // uniforms locations
    GLint PVMmatrixLocation; // = -1;
    GLint VmatrixLocation; // = -1;
    GLint timeLocation; // = -1;
    GLint texSamplerLocation; // = -1;
    GLint frameDurationLocation; // = -1;
} ExplosionShaderProgram;

typedef struct BannerShaderProgram {
    // identifier for the shader program
    GLuint program;           // = 0;
    // vertex attributes locations
    GLint posLocation;        // = -1;
    GLint texCoordLocation;   // = -1;
    // uniforms locations
    GLint PVMmatrixLocation;  // = -1;
    GLint timeLocation;       // = -1;
    GLint texSamplerLocation; // = -1;
} BannerShaderProgram;



void drawBanner(BannerObject* banner, const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix);
void drawSkybox(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix, float elapsedTime);
void drawIsland(IslandObject* island, const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix);
void drawWater(WaterObject* water, const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix, float elapsedTime);
void drawBeachUmbrella(BeachUmbrellaObject* beachUmbrella, const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix);
void drawLamp(LampObject* lamp, const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix);
void drawPalm(PalmObject* beachUmbrella, const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix);
void drawChair(ChairObject* chair, const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix);
void drawBoat(BoatObject* boat, const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix);
void drawDrone(DroneObject* drone, const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix);
void drawDrone2(DroneObject* drone2, const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix);
void drawSecondBoat(SecondBoatObject* secondBoat, const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix);
void drawCone(ConeObject* cone, const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix);
void initConeGeometry(SCommonShaderProgram& shader, MeshGeometry** geometry);
void drawLighthouse(LighthouseObject* lighthouse, const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix);
void drawFire(Fire* fire, const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix);
void initFireGeometry(SCommonShaderProgram& shader, MeshGeometry** geometry);
void drawExplosion(ExplosionObject* explosion, const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix);

void drawSpaceShip(SpaceShipObject* spaceShip, const glm::mat4 & viewMatrix, const glm::mat4 & projectionMatrix);
void drawAsteroid(AsteroidObject* asteroid, const glm::mat4 & viewMatrix, const glm::mat4 & projectionMatrix);
void drawMissile(MissileObject* missile, const glm::mat4 & viewMatrix, const glm::mat4 & projectionMatrix);
void drawUfo(UfoObject* ufo, const glm::mat4 & viewMatrix, const glm::mat4 & projectionMatrix);

void initializeShaderPrograms();
void cleanupShaderPrograms();

void initializeModels();
void cleanupModels();

#endif // __RENDER_STUFF_H
