//----------------------------------------------------------------------------------------
/**
 * \file    render_stuff.cpp
 * \author  Joran Jiri, Jaroslav Sloup, Tomas Barak, Petr Felkel
 * \date    2021
 * \brief   Rendering stuff - drawing functions for models, etc..
 */
//----------------------------------------------------------------------------------------

#include <iostream>
#include "pgr.h"
#include "render_stuff.h"
#include "data.h"
#include "spline.h"
#include "cone.h"

MeshGeometry* cameraGeometry = NULL;
MeshGeometry* islandGeometry = NULL;
MeshGeometry* beachUmbreallaGeometry = NULL;
MeshGeometry* chairGeometry = NULL;
MeshGeometry* coneGeometry = NULL;
MeshGeometry* boatGeometry = NULL;
MeshGeometry* skyboxGeometry = NULL;
MeshGeometry* palmGeometry = NULL;
MeshGeometry* waterGeometry = NULL;
MeshGeometry* droneGeometry = NULL;
MeshGeometry* drone2Geometry = NULL;
MeshGeometry* secondBoatGeometry = NULL;
MeshGeometry* lighthouseGeometry = NULL;
MeshGeometry* fireGeometry = NULL;
MeshGeometry* explosionGeometry = NULL;
MeshGeometry* lampGeometry = NULL;
MeshGeometry* bannerGeometry = NULL;

const char* ISLAND_MODEL_NAME = "data//ostrov/islandDoneV2.obj";
const char* BEACH_UMBRELLA_MODEL_NAME = "data/umbrella/12984_beach_umbrella_v1_L2.obj";
const char* SKYBOX_CUBE_TEXTURE_FILE_PREFIX = "data/skybox";
const char* PALM_MODEL_NAME = "data/palm/10446_Palm_Tree_v1_max2010_iteration-2.obj";
const char* WATER_MODEL_NAME = "data//water/wasser.obj";
const char* CHAIR_MODEL_NAME = "data/chair/12982_Deck_chair_v1_L3.obj";
const char* BOAT_MODEL_NAME = "data/boat/firstBoat.obj";
const char* DRONE_MODEL_NAME = "data/drone/drone.obj";
const char* SECOND_BOAT_MODEL_NAME = "data/boat/second.obj";
const char* LIGHTHOUSE_MODEL_NAME = "data/lighthouse/brickRound.obj";
const char* LAMP_MODEL_NAME = "data/lamp/Obj/Streetlight_LowRes.obj";

const char* BANNER_TEXTURE_NAME = "data/bannerNoBackground.png";
const char* EXPLOSION_TEXTURE_NAME = "data/explosion.png";


SCommonShaderProgram shaderProgram;
SkyboxFarPlaneShaderProgram skyboxProgram;
ExplosionShaderProgram explosionProgram;
BannerShaderProgram bannerProgram;

bool useLighting = false;

void setTransformUniforms(const glm::mat4 &modelMatrix, const glm::mat4 &viewMatrix, const glm::mat4 &projectionMatrix) {

  glm::mat4 PVM = projectionMatrix * viewMatrix * modelMatrix;
  glUniformMatrix4fv(shaderProgram.PVMmatrixLocation, 1, GL_FALSE, glm::value_ptr(PVM));

  glUniformMatrix4fv(shaderProgram.VmatrixLocation, 1, GL_FALSE, glm::value_ptr(viewMatrix));
  glUniformMatrix4fv(shaderProgram.MmatrixLocation, 1, GL_FALSE, glm::value_ptr(modelMatrix));

  // just take 3x3 rotation part of the modelMatrix
  // we presume the last row contains 0,0,0,1
  const glm::mat4 modelRotationMatrix = glm::mat4(
    modelMatrix[0],
    modelMatrix[1],
    modelMatrix[2],
    glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)
  );
  glm::mat4 normalMatrix = glm::transpose(glm::inverse(modelRotationMatrix));

  //or an alternative single-line method: 
  //glm::mat4 normalMatrix = glm::transpose(glm::inverse(glm::mat4(glm::mat3(modelRotationMatrix))));

  glUniformMatrix4fv(shaderProgram.normalMatrixLocation, 1, GL_FALSE, glm::value_ptr(normalMatrix));  // correct matrix for non-rigid transform
}

void setMaterialUniforms(const glm::vec3 &ambient, const glm::vec3 &diffuse, const glm::vec3 &specular, float shininess, GLuint texture) {

  glUniform3fv(shaderProgram.diffuseLocation,  1, glm::value_ptr(diffuse));  // 2nd parameter must be 1 - it declares number of vectors in the vector array
  glUniform3fv(shaderProgram.ambientLocation,  1, glm::value_ptr(ambient));
  glUniform3fv(shaderProgram.specularLocation, 1, glm::value_ptr(specular));
  glUniform1f(shaderProgram.shininessLocation,    shininess);

  if(texture != 0) {
    glUniform1i(shaderProgram.useTextureLocation, 1);  // do texture sampling
    glUniform1i(shaderProgram.texSamplerLocation, 0);  // texturing unit 0 -> samplerID   [for the GPU linker]
    glActiveTexture(GL_TEXTURE0 + 0);                  // texturing unit 0 -> to be bound [for OpenGL BindTexture]
    glBindTexture(GL_TEXTURE_2D, texture);
  }
  else {
    glUniform1i(shaderProgram.useTextureLocation, 0);  // do not sample the texture
  }
}

void drawSkybox(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix, float elapsedTime) {

    glUseProgram(skyboxProgram.program);

    // compose transformations
    glm::mat4 matrix = projectionMatrix * viewMatrix;

    // create view rotation matrix by using view matrix with cleared translation
    glm::mat4 viewRotation = viewMatrix;
    viewRotation[3] = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

    // vertex shader will translate screen space coordinates (NDC) using inverse PV matrix
    glm::mat4 inversePVmatrix = glm::inverse(projectionMatrix * viewRotation);

    glUniformMatrix4fv(skyboxProgram.inversePVmatrixLocation, 1, GL_FALSE, glm::value_ptr(inversePVmatrix));
    glUniform1i(skyboxProgram.skyboxSamplerLocation, 0);

    // draw "skybox" rendering 2 triangles covering the far plane
    glBindVertexArray(skyboxGeometry->vertexArrayObject);
    glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxGeometry->texture);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, skyboxGeometry->numTriangles + 2);

    glBindVertexArray(0);
    glUseProgram(0);
}


void drawIsland(IslandObject* island, const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) {
    glUseProgram(shaderProgram.program);
    // prepare modelling transform matrix
    glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), island->position);
    modelMatrix = glm::rotate(modelMatrix, glm::radians(90.0f), glm::vec3(1, 0, 0));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(island->size, island->size, island->size));
    // send matrices to the vertex & fragment shader
    setTransformUniforms(modelMatrix, viewMatrix, projectionMatrix);
    setMaterialUniforms(
        islandGeometry->ambient,
        islandGeometry->diffuse,
        islandGeometry->specular,
        islandGeometry->shininess,
        islandGeometry->texture
    );
    // draw geometry
    glBindVertexArray(islandGeometry->vertexArrayObject);
    glDrawElements(GL_TRIANGLES, islandGeometry->numTriangles * 3, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    glUseProgram(0);
    return;
}

void drawWater(WaterObject* water, const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix, float elapsedTime) {
    glUseProgram(shaderProgram.program);
    // prepare modelling transform matrix


    glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0), water->position);
    modelMatrix = glm::rotate(modelMatrix, glm::radians(90.0f), glm::vec3(elapsedTime, 0, 0));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(water->wSize.x, water->wSize.y, water->wSize.z));

    // send matrices to the vertex & fragment shader
    setTransformUniforms(modelMatrix, viewMatrix, projectionMatrix);

    setMaterialUniforms(
        waterGeometry->ambient,
        waterGeometry->diffuse,
        waterGeometry->specular,
        waterGeometry->shininess,
        waterGeometry->texture
        );
    // draw geometry
    glBindTexture(GL_TEXTURE_CUBE_MAP, waterGeometry->texture);
    glBindVertexArray(waterGeometry->vertexArrayObject);
    glDrawElements(GL_TRIANGLES, waterGeometry->numTriangles * 3, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    glUseProgram(0);
    return;
}

void drawBeachUmbrella(BeachUmbrellaObject* beachUmbrella, const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) {
    glUseProgram(shaderProgram.program);
    // prepare modelling transform matrix
    glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), beachUmbrella->position);
    modelMatrix = glm::rotate(modelMatrix, glm::radians(0.0f), glm::vec3(1, 0, 0));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(beachUmbrella->size, beachUmbrella->size, beachUmbrella->size));
    // send matrices to the vertex & fragment shader
    setTransformUniforms(modelMatrix, viewMatrix, projectionMatrix);

    setMaterialUniforms(
        beachUmbreallaGeometry->ambient,
        beachUmbreallaGeometry->diffuse,
        beachUmbreallaGeometry->specular,
        beachUmbreallaGeometry->shininess,
        beachUmbreallaGeometry->texture
    );
    // draw geometry
    glBindVertexArray(beachUmbreallaGeometry->vertexArrayObject);
    glDrawElements(GL_TRIANGLES, beachUmbreallaGeometry->numTriangles * 3, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    glUseProgram(0);
    return;
}

void drawLamp(LampObject* lamp, const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) {
    glUseProgram(shaderProgram.program);
    // prepare modelling transform matrix
    glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), lamp->position);
    modelMatrix = glm::rotate(modelMatrix, glm::radians(90.0f), glm::vec3(1, 0, 0));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(lamp->size, lamp->size, lamp->size));
    // send matrices to the vertex & fragment shader
    setTransformUniforms(modelMatrix, viewMatrix, projectionMatrix);

    setMaterialUniforms(
        lampGeometry->ambient,
        lampGeometry->diffuse,
        lampGeometry->specular,
        lampGeometry->shininess,
        lampGeometry->texture
        );
    // draw geometry
    glBindVertexArray(lampGeometry->vertexArrayObject);
    glDrawElements(GL_TRIANGLES, lampGeometry->numTriangles * 3, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    glUseProgram(0);
    return;
}

void drawBoat(BoatObject* boat, const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) {
    glUseProgram(shaderProgram.program);
    // prepare modelling transform matrix
    glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), boat->position);
    modelMatrix = glm::rotate(modelMatrix, glm::radians(boat->viewAngle), glm::vec3(0, 0, 1));
    modelMatrix = glm::rotate(modelMatrix, glm::radians(270.0f), glm::vec3(0, 0, 1));
    modelMatrix = glm::rotate(modelMatrix, glm::radians(90.0f), glm::vec3(1, 0, 0));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(boat->size, boat->size, boat->size));
    // send matrices to the vertex & fragment shader
    setTransformUniforms(modelMatrix, viewMatrix, projectionMatrix);

    setMaterialUniforms(
        boatGeometry->ambient,
        boatGeometry->diffuse,
        boatGeometry->specular,
        boatGeometry->shininess,
        boatGeometry->texture
        );
    // draw geometry
    glBindVertexArray(boatGeometry->vertexArrayObject);
    glDrawElements(GL_TRIANGLES, boatGeometry->numTriangles * 3, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    glUseProgram(0);
    return;
}

void drawSecondBoat(SecondBoatObject* secondBoat, const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) {
    glUseProgram(shaderProgram.program);
    // prepare modelling transform matrix
    glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), secondBoat->position);
    modelMatrix = glm::rotate(modelMatrix, glm::radians(secondBoat->viewAngle), glm::vec3(0, 0, 1));
    modelMatrix = glm::rotate(modelMatrix, glm::radians(270.0f), glm::vec3(0, 0, 1));
    modelMatrix = glm::rotate(modelMatrix, glm::radians(90.0f), glm::vec3(1, 0, 0));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(secondBoat->size, secondBoat->size, secondBoat->size));
    // send matrices to the vertex & fragment shader
    setTransformUniforms(modelMatrix, viewMatrix, projectionMatrix);

    setMaterialUniforms(
        secondBoatGeometry->ambient,
        secondBoatGeometry->diffuse,
        secondBoatGeometry->specular,
        secondBoatGeometry->shininess,
        secondBoatGeometry->texture
        );
    // draw geometry
    glBindVertexArray(secondBoatGeometry->vertexArrayObject);
    glDrawElements(GL_TRIANGLES, secondBoatGeometry->numTriangles * 3, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    glUseProgram(0);
    return;
}

void drawLighthouse(LighthouseObject* lighthouse, const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) {
    glUseProgram(shaderProgram.program);
    // prepare modelling transform matrix
    glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), lighthouse->position);
    modelMatrix = glm::rotate(modelMatrix, glm::radians(90.0f), glm::vec3(1, 0, 0));

    modelMatrix = glm::scale(modelMatrix, glm::vec3(lighthouse->size, lighthouse->size, lighthouse->size));
    // send matrices to the vertex & fragment shader
    setTransformUniforms(modelMatrix, viewMatrix, projectionMatrix);

    setMaterialUniforms(
        lighthouseGeometry->ambient,
        lighthouseGeometry->diffuse,
        lighthouseGeometry->specular,
        lighthouseGeometry->shininess,
        lighthouseGeometry->texture
        );
    // draw geometry
    glBindVertexArray(lighthouseGeometry->vertexArrayObject);
    glDrawElements(GL_TRIANGLES, lighthouseGeometry->numTriangles * 3, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    glUseProgram(0);
    return;
}

void drawExplosion(ExplosionObject* explosion, const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix)
{
    glEnable(GL_BLEND); // enable color blending
    glBlendFunc(GL_ONE, GL_ONE); // color of textury and color of background 1:1 -> black disapear

    glUseProgram(explosionProgram.program);

    glm::mat4 BillboardRotationMatrix = glm::mat4(viewMatrix[0], viewMatrix[1], viewMatrix[2], glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));

    glm::mat4 matrix = translate(glm::mat4(1.0f), explosion->position);
    matrix = scale(matrix, glm::vec3(explosion->size));

    glm::mat4 PVMmatrix = projectionMatrix * viewMatrix * matrix;
    glUniformMatrix4fv(explosionProgram.PVMmatrixLocation, 1, GL_FALSE, value_ptr(PVMmatrix));
    glUniformMatrix4fv(explosionProgram.VmatrixLocation, 1, GL_FALSE, value_ptr(viewMatrix)); // view
    glUniform1f(explosionProgram.timeLocation, explosion->currentTime - explosion->startTime);
    glUniform1i(explosionProgram.texSamplerLocation, 0);
    glUniform1f(explosionProgram.frameDurationLocation, explosion->frameDuration);

    glBindVertexArray(explosionGeometry->vertexArrayObject);
    glBindTexture(GL_TEXTURE_2D, explosionGeometry->texture);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, explosionGeometry->numTriangles);

    glBindVertexArray(0);
    glUseProgram(0);

    glDisable(GL_BLEND);
}

void drawDrone(DroneObject* drone, const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) {
    glUseProgram(shaderProgram.program);
    // prepare modelling transform matrix
    glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), drone->position);
    modelMatrix = glm::rotate(modelMatrix, glm::radians(drone->viewAngle), glm::vec3(0, 0, 1));
    modelMatrix = glm::rotate(modelMatrix, glm::radians(270.0f), glm::vec3(0, 0, 1));
    modelMatrix = glm::rotate(modelMatrix, glm::radians(90.0f), glm::vec3(1, 0, 0));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(drone->size, drone->size, drone->size));
    // send matrices to the vertex & fragment shader
    setTransformUniforms(modelMatrix, viewMatrix, projectionMatrix);

    setMaterialUniforms(
        droneGeometry->ambient,
        droneGeometry->diffuse,
        droneGeometry->specular,
        droneGeometry->shininess,
        droneGeometry->texture
        );
    // draw geometry
    glBindVertexArray(droneGeometry->vertexArrayObject);
    glDrawElements(GL_TRIANGLES, droneGeometry->numTriangles * 3, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    glUseProgram(0);
    return;
}

void drawDrone2(DroneObject* drone2, const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) {
    glUseProgram(shaderProgram.program);
    // prepare modelling transform matrix
    glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), drone2->position);
    modelMatrix = glm::rotate(modelMatrix, glm::radians(drone2->viewAngle), glm::vec3(0, 0, 1));
    modelMatrix = glm::rotate(modelMatrix, glm::radians(270.0f), glm::vec3(0, 0, 1));
    modelMatrix = glm::rotate(modelMatrix, glm::radians(90.0f), glm::vec3(1, 0, 0));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(drone2->size, drone2->size, drone2->size));
    // send matrices to the vertex & fragment shader
    setTransformUniforms(modelMatrix, viewMatrix, projectionMatrix);

    setMaterialUniforms(
        drone2Geometry->ambient,
        drone2Geometry->diffuse,
        drone2Geometry->specular,
        drone2Geometry->shininess,
        drone2Geometry->texture
    );
    // draw geometry
    glBindVertexArray(drone2Geometry->vertexArrayObject);
    glDrawElements(GL_TRIANGLES, drone2Geometry->numTriangles * 3, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    glUseProgram(0);
    return;
}

void drawPalm(PalmObject* palm, const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) {
    glUseProgram(shaderProgram.program);
    // prepare modelling transform matrix
    glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), palm->position);
    modelMatrix = glm::rotate(modelMatrix, glm::radians(0.0f), glm::vec3(1, 0, 0));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(palm->size, palm->size, palm->size));
    // send matrices to the vertex & fragment shader
    setTransformUniforms(modelMatrix, viewMatrix, projectionMatrix);
    setMaterialUniforms(
        palmGeometry->ambient,
        palmGeometry->diffuse,
        palmGeometry->specular,
        palmGeometry->shininess,
        palmGeometry->texture
        );
    // draw geometry
    glBindVertexArray(palmGeometry->vertexArrayObject);
    glDrawElements(GL_TRIANGLES, palmGeometry->numTriangles * 3, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    glUseProgram(0);
    return;
}

void drawChair(ChairObject* chair, const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) {
    glUseProgram(shaderProgram.program);
    // prepare modelling transform matrix
    glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), chair->position);
    modelMatrix = glm::rotate(modelMatrix, glm::radians(180.0f), glm::vec3(0, 0, 1));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(chair->size, chair->size, chair->size));
    // send matrices to the vertex & fragment shader
    setTransformUniforms(modelMatrix, viewMatrix, projectionMatrix);
    setMaterialUniforms(
        chairGeometry->ambient,
        chairGeometry->diffuse,
        chairGeometry->specular,
        chairGeometry->shininess,
        chairGeometry->texture
    );
    // draw geometry
    glBindVertexArray(chairGeometry->vertexArrayObject);
    glDrawElements(GL_TRIANGLES, chairGeometry->numTriangles * 3, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    glUseProgram(0);
    return;
}

void drawCone(ConeObject* cone, const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) {

    glUseProgram(shaderProgram.program);

    // prepare modelling transform matrix
    glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), cone->position);
    modelMatrix = glm::rotate(modelMatrix, glm::radians(0.0f), glm::vec3(1, 0, 0));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(cone->size, cone->size, cone->size));

    // send matrices to the vertex & fragment shader
    setTransformUniforms(modelMatrix, viewMatrix, projectionMatrix);

    setMaterialUniforms(
        coneGeometry->ambient,
        coneGeometry->diffuse,
        coneGeometry->specular,
        coneGeometry->shininess,
        coneGeometry->texture
    );


    // draw geometry
    glBindVertexArray(coneGeometry->vertexArrayObject);
    glDrawElements(GL_TRIANGLES, coneGeometry->numTriangles * 3, GL_UNSIGNED_INT, 0);
    //glUniform1i(shaderProgram.useTextureLocation, 0);

    glBindVertexArray(0);
    glUseProgram(0);

    return;
}

void drawBanner(BannerObject* banner, const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) {

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glDisable(GL_DEPTH_TEST);

    glUseProgram(bannerProgram.program);

    glm::mat4 matrix = glm::translate(glm::mat4(1.0f), banner->position);
    matrix = glm::scale(matrix, glm::vec3(banner->size));

    glm::mat4 PVMmatrix = projectionMatrix * viewMatrix * matrix;
    glUniformMatrix4fv(bannerProgram.PVMmatrixLocation, 1, GL_FALSE, glm::value_ptr(PVMmatrix));        // model-view-projection
    glUniform1f(bannerProgram.timeLocation, banner->currentTime - banner->startTime);
    glUniform1i(bannerProgram.texSamplerLocation, 0);

    glBindTexture(GL_TEXTURE_2D, bannerGeometry->texture);
    glBindVertexArray(bannerGeometry->vertexArrayObject);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, bannerGeometry->numTriangles);

    CHECK_GL_ERROR();

    glBindVertexArray(0);
    glUseProgram(0);

    glEnable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);

    return;
}

void cleanupShaderPrograms(void) {

  pgr::deleteProgramAndShaders(shaderProgram.program);
  pgr::deleteProgramAndShaders(bannerProgram.program);
  pgr::deleteProgramAndShaders(explosionProgram.program);

}

void initializeShaderPrograms(void) {

  std::vector<GLuint> shaderList;

  if (useLighting == true) {
      // load and compile shader for lighting (lights & materials)

      // push vertex shader and fragment shader
      shaderList.push_back(pgr::createShaderFromFile(GL_VERTEX_SHADER, "perVertex.vert"));
      shaderList.push_back(pgr::createShaderFromFile(GL_FRAGMENT_SHADER, "perVertex.frag"));

      // create the shader program with two shaders
      shaderProgram.program = pgr::createProgram(shaderList);

      // get vertex attributes locations, if the shader does not have this uniform -> return -1
      shaderProgram.posLocation = glGetAttribLocation(shaderProgram.program, "position");
      shaderProgram.normalLocation = glGetAttribLocation(shaderProgram.program, "normal");
      shaderProgram.texCoordLocation = glGetAttribLocation(shaderProgram.program, "texCoord");
      // get uniforms locations
      shaderProgram.PVMmatrixLocation = glGetUniformLocation(shaderProgram.program, "PVMmatrix");
      shaderProgram.VmatrixLocation = glGetUniformLocation(shaderProgram.program, "Vmatrix");
      shaderProgram.MmatrixLocation = glGetUniformLocation(shaderProgram.program, "Mmatrix");
      shaderProgram.normalMatrixLocation = glGetUniformLocation(shaderProgram.program, "normalMatrix");
      shaderProgram.timeLocation = glGetUniformLocation(shaderProgram.program, "time");
      // material
      shaderProgram.ambientLocation = glGetUniformLocation(shaderProgram.program, "material.ambient");
      shaderProgram.diffuseLocation = glGetUniformLocation(shaderProgram.program, "material.diffuse");
      shaderProgram.specularLocation = glGetUniformLocation(shaderProgram.program, "material.specular");
      shaderProgram.shininessLocation = glGetUniformLocation(shaderProgram.program, "material.shininess");
      // texture
      shaderProgram.texSamplerLocation = glGetUniformLocation(shaderProgram.program, "texSampler");
      shaderProgram.useTextureLocation = glGetUniformLocation(shaderProgram.program, "material.useTexture");
      // reflector
      shaderProgram.spotlightPosition = glGetUniformLocation(shaderProgram.program, "spotlightPosition");
      shaderProgram.spotlightDirection = glGetUniformLocation(shaderProgram.program, "spotlightDirection");

      shaderProgram.flashLoc = glGetUniformLocation(shaderProgram.program, "lighthouseSpotLight");

      shaderProgram.sunAngle = glGetUniformLocation(shaderProgram.program, "sunAngle");
      shaderProgram.sunLoc = glGetUniformLocation(shaderProgram.program, "dayDirectionalLight");

      

      //shaderList.clear();

      shaderProgram.ptLightOnLoc = glGetUniformLocation(shaderProgram.program, "lampLight");

      shaderProgram.fogLoc = glGetUniformLocation(shaderProgram.program, "fog");
      shaderList.clear();
  }
  else {
    // load and compile simple shader (colors only, no lights at all)

    // push vertex shader and fragment shader
    shaderList.push_back(pgr::createShaderFromSource(GL_VERTEX_SHADER, colorVertexShaderSrc));
    shaderList.push_back(pgr::createShaderFromSource(GL_FRAGMENT_SHADER, colorFragmentShaderSrc));

    // create the program with two shaders (fragment and vertex)
    shaderProgram.program = pgr::createProgram(shaderList);
    // get position and color attributes locations
    shaderProgram.posLocation   = glGetAttribLocation(shaderProgram.program, "position");
    shaderProgram.colorLocation = glGetAttribLocation(shaderProgram.program, "color");
    // get uniforms locations
    shaderProgram.PVMmatrixLocation = glGetUniformLocation(shaderProgram.program, "PVMmatrix");
  }

  // load and compile shader for skybox (cube map)
  shaderList.clear();

  // push vertex shader and fragment shader
  shaderList.push_back(pgr::createShaderFromFile(GL_VERTEX_SHADER, "skybox.vert"));
  shaderList.push_back(pgr::createShaderFromFile(GL_FRAGMENT_SHADER, "skybox.frag"));

  // create the program with two shaders
  skyboxProgram.program = pgr::createProgram(shaderList);
  // handles to vertex attributes locations
  skyboxProgram.screenCoordLocation = glGetAttribLocation(skyboxProgram.program, "screenCoord");
  // get uniforms locations
  skyboxProgram.skyboxSamplerLocation = glGetUniformLocation(skyboxProgram.program, "skyboxSampler");
  skyboxProgram.inversePVmatrixLocation = glGetUniformLocation(skyboxProgram.program, "inversePVmatrix");
  skyboxProgram.intensity = glGetUniformLocation(skyboxProgram.program, "intensity");

  shaderList.clear();

  // push vertex shader and fragment shader
  shaderList.push_back(pgr::createShaderFromFile(GL_VERTEX_SHADER, "explosion.vert"));
  shaderList.push_back(pgr::createShaderFromFile(GL_FRAGMENT_SHADER, "explosion.frag"));

  // create the program with two shaders
  explosionProgram.program = pgr::createProgram(shaderList);

  // get position and texture coordinates attributes locations
  explosionProgram.posLocation = glGetAttribLocation(explosionProgram.program, "position");
  explosionProgram.texCoordLocation = glGetAttribLocation(explosionProgram.program, "texCoord");
  shaderProgram.texLocation = glGetAttribLocation(explosionProgram.program, "texCoord");

  // get uniforms locations
  explosionProgram.PVMmatrixLocation = glGetUniformLocation(explosionProgram.program, "PVMmatrix");
  explosionProgram.VmatrixLocation = glGetUniformLocation(explosionProgram.program, "Vmatrix");
  explosionProgram.timeLocation = glGetUniformLocation(explosionProgram.program, "time");
  explosionProgram.texSamplerLocation = glGetUniformLocation(explosionProgram.program, "texSampler");
  explosionProgram.frameDurationLocation = glGetUniformLocation(explosionProgram.program, "frameDuration");

  shaderList.clear();

  // push vertex shader and fragment shader
  shaderList.push_back(pgr::createShaderFromFile(GL_VERTEX_SHADER, "banner.vert"));
  shaderList.push_back(pgr::createShaderFromFile(GL_FRAGMENT_SHADER, "banner.frag"));

  // Create the program with two shaders
  bannerProgram.program = pgr::createProgram(shaderList);

  // get position and color attributes locations
  bannerProgram.posLocation = glGetAttribLocation(bannerProgram.program, "position");
  bannerProgram.texCoordLocation = glGetAttribLocation(bannerProgram.program, "texCoord");
  // get uniforms locations
  bannerProgram.PVMmatrixLocation = glGetUniformLocation(bannerProgram.program, "PVMmatrix");
  bannerProgram.timeLocation = glGetUniformLocation(bannerProgram.program, "time");
  bannerProgram.texSamplerLocation = glGetUniformLocation(bannerProgram.program, "texSampler");

  shaderList.clear();
}

bool loadSingleMesh(const std::string &fileName, SCommonShaderProgram& shader, MeshGeometry** geometry) {
  Assimp::Importer importer;

  // Unitize object in size (scale the model to fit into (-1..1)^3)
  importer.SetPropertyInteger(AI_CONFIG_PP_PTV_NORMALIZE, 1);

  // Load asset from the file - you can play with various processing steps
  const aiScene * scn = importer.ReadFile(fileName.c_str(), 0
      | aiProcess_Triangulate             // Triangulate polygons (if any).
      | aiProcess_PreTransformVertices    // Transforms scene hierarchy into one root with geometry-leafs only. For more see Doc.
      | aiProcess_GenSmoothNormals        // Calculate normals per vertex.
      | aiProcess_JoinIdenticalVertices);

  // abort if the loader fails
  if(scn == NULL) {
    std::cerr << "assimp error: " << importer.GetErrorString() << std::endl;
    *geometry = NULL;
    return false;
  }

  // some formats store whole scene (multiple meshes and materials, lights, cameras, ...) in one file, we cannot handle that in our simplified example
  if(scn->mNumMeshes != 1) {
    std::cerr << "this simplified loader can only process files with only one mesh" << std::endl;
    *geometry = NULL;
    return false;
  }

  // in this phase we know we have one mesh in our loaded scene, we can directly copy its data to OpenGL ...
  const aiMesh * mesh = scn->mMeshes[0];

  *geometry = new MeshGeometry;

  // vertex buffer object, store all vertex positions and normals
  glGenBuffers(1, &((*geometry)->vertexBufferObject));
  glBindBuffer(GL_ARRAY_BUFFER, (*geometry)->vertexBufferObject);
  glBufferData(GL_ARRAY_BUFFER, 8*sizeof(float)*mesh->mNumVertices, 0, GL_STATIC_DRAW); // allocate memory for vertices, normals, and texture coordinates
  // first store all vertices
  glBufferSubData(GL_ARRAY_BUFFER, 0, 3*sizeof(float)*mesh->mNumVertices, mesh->mVertices);
  // then store all normals
  glBufferSubData(GL_ARRAY_BUFFER, 3*sizeof(float)*mesh->mNumVertices, 3*sizeof(float)*mesh->mNumVertices, mesh->mNormals);
  
  // just texture 0 for now
  float *textureCoords = new float[2 * mesh->mNumVertices];  // 2 floats per vertex
  float *currentTextureCoord = textureCoords;

  // copy texture coordinates
  aiVector3D vect;
    
  if(mesh->HasTextureCoords(0) ) {
    // we use 2D textures with 2 coordinates and ignore the third coordinate
    for(unsigned int idx=0; idx<mesh->mNumVertices; idx++) {
      vect = (mesh->mTextureCoords[0])[idx];
      *currentTextureCoord++ = vect.x;
      *currentTextureCoord++ = vect.y;
    }
  }
    
  // finally store all texture coordinates
  glBufferSubData(GL_ARRAY_BUFFER, 6*sizeof(float)*mesh->mNumVertices, 2*sizeof(float)*mesh->mNumVertices, textureCoords);

  // copy all mesh faces into one big array (assimp supports faces with ordinary number of vertices, we use only 3 -> triangles)
  unsigned int *indices = new unsigned int[mesh->mNumFaces * 3];
  for(unsigned int f = 0; f < mesh->mNumFaces; ++f) {
    indices[f*3 + 0] = mesh->mFaces[f].mIndices[0];
    indices[f*3 + 1] = mesh->mFaces[f].mIndices[1];
    indices[f*3 + 2] = mesh->mFaces[f].mIndices[2];
  }

  // copy our temporary index array to OpenGL and free the array
  glGenBuffers(1, &((*geometry)->elementBufferObject));
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, (*geometry)->elementBufferObject);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3 * sizeof(unsigned) * mesh->mNumFaces, indices, GL_STATIC_DRAW);

  delete [] indices;

  // copy the material info to MeshGeometry structure
  const aiMaterial *mat  = scn->mMaterials[mesh->mMaterialIndex];
  aiColor4D color;
  aiString name;
  aiReturn retValue = AI_SUCCESS;

  // Get returns: aiReturn_SUCCESS 0 | aiReturn_FAILURE -1 | aiReturn_OUTOFMEMORY -3
  mat->Get(AI_MATKEY_NAME, name); // may be "" after the input mesh processing. Must be aiString type!

  if((retValue = aiGetMaterialColor(mat, AI_MATKEY_COLOR_DIFFUSE, &color)) != AI_SUCCESS)
    color = aiColor4D(0.0f, 0.0f, 0.0f, 0.0f);

  (*geometry)->diffuse = glm::vec3(color.r, color.g, color.b);

  if ((retValue = aiGetMaterialColor(mat, AI_MATKEY_COLOR_AMBIENT, &color)) != AI_SUCCESS)
    color = aiColor4D(0.0f, 0.0f, 0.0f, 0.0f);
  (*geometry)->ambient = glm::vec3(color.r, color.g, color.b);

  if ((retValue = aiGetMaterialColor(mat, AI_MATKEY_COLOR_SPECULAR, &color)) != AI_SUCCESS)
    color = aiColor4D(0.0f, 0.0f, 0.0f, 0.0f);
  (*geometry)->specular = glm::vec3(color.r, color.g, color.b);

  ai_real shininess, strength;
  unsigned int max;	// changed: to unsigned

  max = 1;	
  if ((retValue = aiGetMaterialFloatArray(mat, AI_MATKEY_SHININESS, &shininess, &max)) != AI_SUCCESS)
    shininess = 1.0f;
  max = 1;
  if((retValue = aiGetMaterialFloatArray(mat, AI_MATKEY_SHININESS_STRENGTH, &strength, &max)) != AI_SUCCESS)
    strength = 1.0f;
  (*geometry)->shininess = shininess * strength;

  (*geometry)->texture = 0;

  // load texture image
  if (mat->GetTextureCount(aiTextureType_DIFFUSE) > 0) {
    // get texture name 
    aiString path; // filename

    aiReturn texFound = mat->GetTexture(aiTextureType_DIFFUSE, 0, &path);
    std::string textureName = path.data;

    size_t found = fileName.find_last_of("/\\");
    // insert correct texture file path 
    if(found != std::string::npos) { // not found
      //subMesh_p->textureName.insert(0, "/");
      textureName.insert(0, fileName.substr(0, found+1));
    }

    std::cout << "Loading texture file: " << textureName << std::endl;
    (*geometry)->texture = pgr::createTexture(textureName);
  }
  CHECK_GL_ERROR();

  glGenVertexArrays(1, &((*geometry)->vertexArrayObject));
  glBindVertexArray((*geometry)->vertexArrayObject);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, (*geometry)->elementBufferObject); // bind our element array buffer (indices) to vao
  glBindBuffer(GL_ARRAY_BUFFER, (*geometry)->vertexBufferObject);

  glEnableVertexAttribArray(shader.posLocation);
  glVertexAttribPointer(shader.posLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);

  if(useLighting == true) {
    glEnableVertexAttribArray(shader.normalLocation);
    glVertexAttribPointer(shader.normalLocation, 3, GL_FLOAT, GL_FALSE, 0, (void*)(3 * sizeof(float) * mesh->mNumVertices));
  }
  else {
	  glDisableVertexAttribArray(shader.colorLocation);
	  // following line is problematic on AMD/ATI graphic cards
	  // -> if you see black screen (no objects at all) than try to set color manually in vertex shader to see at least something
    glVertexAttrib3f(shader.colorLocation, color.r, color.g, color.b);
  }

  glEnableVertexAttribArray(shader.texCoordLocation);
  glVertexAttribPointer(shader.texCoordLocation, 2, GL_FLOAT, GL_FALSE, 0, (void*)(6 * sizeof(float) * mesh->mNumVertices));
  CHECK_GL_ERROR();

  glBindVertexArray(0);

  (*geometry)->numTriangles = mesh->mNumFaces;

  return true;
}

void initBannerGeometry(GLuint shader, MeshGeometry** geometry) {

    *geometry = new MeshGeometry;

    (*geometry)->texture = pgr::createTexture(BANNER_TEXTURE_NAME);
    glBindTexture(GL_TEXTURE_2D, (*geometry)->texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);

    glGenVertexArrays(1, &((*geometry)->vertexArrayObject));
    glBindVertexArray((*geometry)->vertexArrayObject);

    glGenBuffers(1, &((*geometry)->vertexBufferObject));
    glBindBuffer(GL_ARRAY_BUFFER, (*geometry)->vertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, sizeof(bannerVertexData), bannerVertexData, GL_STATIC_DRAW);

    glEnableVertexAttribArray(bannerProgram.posLocation);
    glEnableVertexAttribArray(bannerProgram.texCoordLocation);
    // vertices of triangles - start at the beginning of the interlaced array
    glVertexAttribPointer(bannerProgram.posLocation, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);
    // texture coordinates of each vertices are stored just after its position
    glVertexAttribPointer(bannerProgram.texCoordLocation, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));

    glBindVertexArray(0);

    (*geometry)->numTriangles = bannerNumQuadVertices;
}

void initExplosionGeometry(GLuint shader, MeshGeometry** geometry)
{
    *geometry = new MeshGeometry;

    (*geometry)->texture = pgr::createTexture(EXPLOSION_TEXTURE_NAME);

    glGenVertexArrays(1, &((*geometry)->vertexArrayObject));
    glBindVertexArray((*geometry)->vertexArrayObject);

    glGenBuffers(1, &((*geometry)->vertexBufferObject));
    glBindBuffer(GL_ARRAY_BUFFER, (*geometry)->vertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, sizeof(explosionVertexData), explosionVertexData, GL_STATIC_DRAW);

    glEnableVertexAttribArray(explosionProgram.posLocation);
    // vertices of triangles - start at the beginning of the array (interlaced array)
    glVertexAttribPointer(explosionProgram.posLocation, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), nullptr);

    glEnableVertexAttribArray(explosionProgram.texCoordLocation);
    // texture coordinates are placed just after the position of each vertex (interlaced array)
    glVertexAttribPointer(explosionProgram.texCoordLocation, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
        (void*)(3 * sizeof(float)));

    glBindVertexArray(0);

    (*geometry)->ambient = glm::vec3(0.2f, 0.2f, 0.2f);
    (*geometry)->diffuse = glm::vec3(0.2f, 0.2f, 0.2f);
    (*geometry)->specular = glm::vec3(0.2f, 0.2f, 0.2f);
    (*geometry)->shininess = 2.0f;
    (*geometry)->numTriangles = explosionNumQuadVertices;
}


void initConeGeometry(SCommonShaderProgram& shader, MeshGeometry** geometry) {

    *geometry = new MeshGeometry;

    glGenVertexArrays(1, &((*geometry)->vertexArrayObject));
    glBindVertexArray((*geometry)->vertexArrayObject);

    glGenBuffers(1, &((*geometry)->vertexBufferObject));
    glBindBuffer(GL_ARRAY_BUFFER, (*geometry)->vertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, coneNVertices * coneNAttribsPerVertex * sizeof(float), coneVertices, GL_STATIC_DRAW);
    CHECK_GL_ERROR();

    glGenBuffers(1, &((*geometry)->elementBufferObject));
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, (*geometry)->elementBufferObject);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, coneNTriangles * 3 * sizeof(unsigned int), coneTriangles, GL_STATIC_DRAW);
    CHECK_GL_ERROR();
     
    glEnableVertexAttribArray(shader.posLocation);
    // vertices of triangles - start at the beginning of the array
    glVertexAttribPointer(shader.posLocation, 3, GL_FLOAT, GL_FALSE, coneNAttribsPerVertex * sizeof(float), 0);

    //if(useLighting == false) {
    glEnableVertexAttribArray(shader.texCoordLocation);
    // colors of vertices start after the positions
    glVertexAttribPointer(shader.texCoordLocation, 2, GL_FLOAT, GL_FALSE, coneNAttribsPerVertex * sizeof(float), (void*)(3 * sizeof(float)));
    //}
    //else {
    glEnableVertexAttribArray(shader.normalLocation);
    // normals of vertices start after the colors
    glVertexAttribPointer(shader.normalLocation, 3, GL_FLOAT, GL_FALSE, coneNAttribsPerVertex * sizeof(float), (void*)(2 * 3 * sizeof(float)));
    //}
    
    // Hardcodove nastaveni barvy
    (*geometry)->ambient = glm::vec3(2.0f, 5.0f, 6.0f);
    (*geometry)->diffuse = glm::vec3(12.0f, 52.0f, 62.0f);
    (*geometry)->specular = glm::vec3(25.0f, 222.0f, 124.0f);
    (*geometry)->shininess = 5.0f;
    (*geometry)->texture = pgr::createTexture("data/cone/coneTexture.png");


    glBindVertexArray(0);

    (*geometry)->numTriangles = coneNTriangles;
}


void initSkyboxGeometry(GLuint shader, MeshGeometry** geometry) {
    *geometry = new MeshGeometry;
    // 2D coordinates of 2 triangles covering the whole screen (NDC), draw using triangle strip
    static const float screenCoords[] = {
        -1.0f, -1.0f,
        1.0f, -1.0f,
        -1.0f, 1.0f,
        1.0f, 1.0f
    };
    glGenVertexArrays(1, &((*geometry)->vertexArrayObject));
    glBindVertexArray((*geometry)->vertexArrayObject);
    // buffer for far plane rendering
    glGenBuffers(1, &((*geometry)->vertexBufferObject)); \
        glBindBuffer(GL_ARRAY_BUFFER, (*geometry)->vertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, sizeof(screenCoords), screenCoords, GL_STATIC_DRAW);
    glEnableVertexAttribArray(skyboxProgram.screenCoordLocation);
    glVertexAttribPointer(skyboxProgram.screenCoordLocation, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glBindVertexArray(0);
    glUseProgram(0);
    CHECK_GL_ERROR();
    (*geometry)->numTriangles = 2;
    glActiveTexture(GL_TEXTURE0);
    glGenTextures(1, &((*geometry)->texture));
    glBindTexture(GL_TEXTURE_CUBE_MAP, (*geometry)->texture);
    const char* suffixes[] = { "right", "left", "up", "down", "front", "back" };
    GLuint targets[] = {
        GL_TEXTURE_CUBE_MAP_POSITIVE_X, GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
        GL_TEXTURE_CUBE_MAP_POSITIVE_Y, GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
        GL_TEXTURE_CUBE_MAP_POSITIVE_Z, GL_TEXTURE_CUBE_MAP_NEGATIVE_Z
    };
    for (int i = 0; i < 6; i++) {
        std::string texName = std::string(SKYBOX_CUBE_TEXTURE_FILE_PREFIX) + "/" + suffixes[i] + ".jpg";
        std::cout << "Loading cube map texture: " << texName << std::endl;
        if (!pgr::loadTexImage2D(texName, targets[i])) {
            std::cout << std::endl;
            std::cout << texName << '\n';
            std::cout << std::endl;
            pgr::dieWithError("Skybox cube map loading failed!");
        }
    }
    glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
    // unbind the texture (just in case someone will mess up with texture calls later)
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
    CHECK_GL_ERROR();
}


/** Initialize vertex buffers and vertex arrays for all objects. 
 */
void initializeModels() {

  // load asteroid model from external file
    initConeGeometry(shaderProgram, &coneGeometry);
    initExplosionGeometry(explosionProgram.program, &explosionGeometry);
    initBannerGeometry(bannerProgram.program, &bannerGeometry);
    initSkyboxGeometry(skyboxProgram.program, &skyboxGeometry);

  CHECK_GL_ERROR();
  
  if (loadSingleMesh(ISLAND_MODEL_NAME, shaderProgram, &islandGeometry) != true) {
      std::cerr << "Island model loading failed." << std::endl;
  }
  CHECK_GL_ERROR();

  if (loadSingleMesh(WATER_MODEL_NAME, shaderProgram, &waterGeometry) != true) {
      std::cerr << "Water model loading failed." << std::endl;
  }
  CHECK_GL_ERROR();

  if (loadSingleMesh(CHAIR_MODEL_NAME, shaderProgram, &chairGeometry) != true) {
      std::cerr << "Chair model loading failed." << std::endl;
  }
  CHECK_GL_ERROR();
  
  if (loadSingleMesh(BEACH_UMBRELLA_MODEL_NAME, shaderProgram, &beachUmbreallaGeometry) != true) {
      std::cerr << "Beach umbrella model loading failed." << std::endl;
  }
  CHECK_GL_ERROR();

  if (loadSingleMesh(BOAT_MODEL_NAME, shaderProgram, &boatGeometry) != true) {
      std::cerr << "Boat model loading failed." << std::endl;
  }
  CHECK_GL_ERROR();

  if (loadSingleMesh(LAMP_MODEL_NAME, shaderProgram, &lampGeometry) != true) {
      std::cerr << "Lamp model loading failed." << std::endl;
  }
  CHECK_GL_ERROR();

  if (loadSingleMesh(PALM_MODEL_NAME, shaderProgram, &palmGeometry) != true) {
      std::cerr << "Palm model loading failed." << std::endl;
  }
  CHECK_GL_ERROR();

  if (loadSingleMesh(DRONE_MODEL_NAME, shaderProgram, &droneGeometry) != true) {
      std::cerr << "Drone model loading failed." << std::endl;
  }
  CHECK_GL_ERROR();

  if (loadSingleMesh(DRONE_MODEL_NAME, shaderProgram, &drone2Geometry) != true) {
      std::cerr << "Drone2 model loading failed." << std::endl;
  }
  CHECK_GL_ERROR();

  if (loadSingleMesh(SECOND_BOAT_MODEL_NAME, shaderProgram, &secondBoatGeometry) != true) {
      std::cerr << "Second boat model loading failed." << std::endl;
  }
  CHECK_GL_ERROR();

  if (loadSingleMesh(LIGHTHOUSE_MODEL_NAME, shaderProgram, &lighthouseGeometry) != true) {
      std::cerr << "Lighthouse model loading failed." << std::endl;
  }
  CHECK_GL_ERROR();


}

void cleanupGeometry(MeshGeometry *geometry) {

  glDeleteVertexArrays(1, &(geometry->vertexArrayObject));
  glDeleteBuffers(1, &(geometry->elementBufferObject));
  glDeleteBuffers(1, &(geometry->vertexBufferObject));

  if(geometry->texture != 0)
    glDeleteTextures(1, &(geometry->texture));
}

void cleanupModels() {
  cleanupGeometry(coneGeometry);
  cleanupGeometry(skyboxGeometry);
  cleanupGeometry(palmGeometry);
  cleanupGeometry(waterGeometry);
  cleanupGeometry(droneGeometry);
  cleanupGeometry(secondBoatGeometry);
  cleanupGeometry(lighthouseGeometry);
  cleanupGeometry(explosionGeometry);
  cleanupGeometry(lampGeometry);
  cleanupGeometry(bannerGeometry);
}
