#include <GL/gl.h>
#include <GL/glut.h>
#include <math.h>
#include <bits/stdc++.h>

#define PI 3.14159
const int n = 10000;
const float R = 0.28f;
const float R2 = 0.18f;
const float R3 = 0.08f;

GLfloat step=0.0f;
GLfloat color = 0.0f;
int m = 0;
float duck[3]={1.0, 1.0, 0.0};

void time(int value)
{
    m++;
    if(m%2 == 0){
        color = 0.5f;
    }
    else if(m%2 == 1){
        color = 0.0f;
    }
    glutPostRedisplay();
    glutTimerFunc(600,time,1);
}
void display(void)
{
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      glPolygonMode(GL_BACK,GL_FILL);
      glPushMatrix();
      glColor3f(duck[0], duck[1], duck[2]);
      glBegin(GL_POLYGON);
          glVertex3f(-0.75f, 0.10f, 0.0f);glVertex3f(-0.76f, 0.22f, 0.0f);
          glVertex3f(-0.76f, 0.22f, 0.0f);glVertex3f(-0.72f, 0.31f, 0.0f);
          glVertex3f(-0.72f, 0.31f, 0.0f);glVertex3f(-0.65f, 0.39f, 0.0f);
          glVertex3f(-0.65f, 0.39f, 0.0f);glVertex3f(-0.63f, 0.44f, 0.0f);
          glVertex3f(-0.63f, 0.44f, 0.0f);glVertex3f(-0.56f, 0.50f, 0.0f);
          glVertex3f(-0.56f, 0.50f, 0.0f);glVertex3f(-0.50f, 0.55f, 0.0f);
          glVertex3f(-0.50f, 0.55f, 0.0f);glVertex3f(-0.44f, 0.58f, 0.0f);
          glVertex3f(-0.44f, 0.58f, 0.0f);glVertex3f(-0.37f, 0.63f, 0.0f);
          glVertex3f(-0.37f, 0.63f, 0.0f);glVertex3f(-0.34f, 0.64f, 0.0f);
          glVertex3f(-0.34f, 0.64f, 0.0f);glVertex3f(-0.09f, 0.69f, 0.0f);
          glVertex3f(-0.09f, 0.69f, 0.0f);glVertex3f(-0.08f, 0.88f, 0.0f);
          glVertex3f(-0.08f, 0.88f, 0.0f);glVertex3f(-0.04f, 0.90f, 0.0f);
          glVertex3f(-0.04f, 0.90f, 0.0f);glVertex3f(-0.03f, 0.92f, 0.0f);
          glVertex3f(-0.03f, 0.92f, 0.0f);glVertex3f(0.01f, 0.92f, 0.0f);
          glVertex3f(0.01f, 0.92f, 0.0f);glVertex3f(0.04f, 0.89f, 0.0f);
          glVertex3f(0.04f, 0.89f, 0.0f);glVertex3f(0.05f, 0.86f, 0.0f);
          glVertex3f(0.05f, 0.86f, 0.0f);glVertex3f(0.04f, 0.77f, 0.0f);
          glVertex3f(0.04f, 0.77f, 0.0f);glVertex3f(0.12f, 0.83f, 0.0f);
          glVertex3f(0.12f, 0.83f, 0.0f);glVertex3f(0.22f, 0.84f, 0.0f);
          glVertex3f(0.22f, 0.84f, 0.0f);glVertex3f(0.27f, 0.82f, 0.0f);
          glVertex3f(0.27f, 0.82f, 0.0f);glVertex3f(0.24f, 0.77f, 0.0f);
          glVertex3f(0.24f, 0.77f, 0.0f);glVertex3f(0.16f, 0.75f, 0.0f);
          glVertex3f(0.16f, 0.75f, 0.0f);glVertex3f(0.12f, 0.68f, 0.0f);
          glVertex3f(0.12f, 0.68f, 0.0f);glVertex3f(0.23f, 0.67f, 0.0f);
          glVertex3f(0.23f, 0.67f, 0.0f);glVertex3f(0.32f, 0.61f, 0.0f);
          glVertex3f(0.32f, 0.61f, 0.0f);glVertex3f(0.37f, 0.56f, 0.0f);
          glVertex3f(0.37f, 0.56f, 0.0f);glVertex3f(0.41f, 0.50f, 0.0f);
          glVertex3f(0.41f, 0.50f, 0.0f);glVertex3f(0.55f, 0.35f, 0.0f);
          glVertex3f(0.55f, 0.35f, 0.0f);glVertex3f(0.58f, 0.27f, 0.0f);
          glVertex3f(0.58f, 0.27f, 0.0f);glVertex3f(0.61f, 0.26f, 0.0f);
          glVertex3f(0.61f, 0.26f, 0.0f);glVertex3f(0.68f, 0.17f, 0.0f);
          glVertex3f(0.68f, 0.17f, 0.0f);glVertex3f(0.69f, 0.09f, 0.0f);
          glVertex3f(0.69f, 0.09f, 0.0f);glVertex3f(0.74f, 0.03f, 0.0f);
          glVertex3f(0.74f, 0.03f, 0.0f);glVertex3f(0.73f, -0.08f, 0.0f);
          glVertex3f(0.73f, -0.08f, 0.0f);glVertex3f(0.71f, -0.17f, 0.0f);
          glVertex3f(0.71f, -0.17f, 0.0f);glVertex3f(0.67f, -0.29f, 0.0f);
          glVertex3f(0.67f, -0.29f, 0.0f);glVertex3f(0.63f, -0.37f, 0.0f);
          glVertex3f(0.63f, -0.37f, 0.0f);glVertex3f(0.57f, -0.44f, 0.0f);
          glVertex3f(0.57f, -0.44f, 0.0f);glVertex3f(0.53f, -0.47f, 0.0f);
          glVertex3f(0.53f, -0.47f, 0.0f);glVertex3f(0.46f, -0.50f, 0.0f);
          glVertex3f(0.46f, -0.50f, 0.0f);glVertex3f(0.43f, -0.56f, 0.0f);
          glVertex3f(0.43f, -0.56f, 0.0f);glVertex3f(0.40f, -0.58f, 0.0f);
          glVertex3f(0.40f, -0.58f, 0.0f);glVertex3f(0.37f, -0.63f, 0.0f);
          glVertex3f(0.37f, -0.63f, 0.0f);glVertex3f(0.45f, -0.73f, 0.0f);
          glVertex3f(0.45f, -0.73f, 0.0f);glVertex3f(0.49f, -0.85f, 0.0f);
          glVertex3f(0.49f, -0.85f, 0.0f);glVertex3f(0.52f, -1.00f, 0.0f);
          glVertex3f(0.52f, -1.00f, 0.0f);glVertex3f(-0.47f, -1.00f, 0.0f);
          glVertex3f(-0.47f, -1.00f, 0.0f);glVertex3f(-0.43f, -0.76f, 0.0f);
          glVertex3f(-0.43f, -0.76f, 0.0f);glVertex3f(-0.48f, -1.00f, 0.0f);
          glVertex3f(-0.48f, -1.00f, 0.0f);glVertex3f(-0.70f, -1.00f, 0.0f);
          glVertex3f(-0.70f, -1.00f, 0.0f);glVertex3f(-0.72f, -0.84f, 0.0f);
          glVertex3f(-0.72f, -0.84f, 0.0f);glVertex3f(-0.68f, -0.75f, 0.0f);
          glVertex3f(-0.68f, -0.75f, 0.0f);glVertex3f(-0.64f, -0.69f, 0.0f);
          glVertex3f(-0.64f, -0.69f, 0.0f);glVertex3f(-0.59f, -0.63f, 0.0f);
          glVertex3f(-0.59f, -0.63f, 0.0f);glVertex3f(-0.47f, -0.55f, 0.0f);
          glVertex3f(-0.47f, -0.55f, 0.0f);glVertex3f(-0.62f, -0.43f, 0.0f);
          glVertex3f(-0.62f, -0.43f, 0.0f);glVertex3f(-0.71f, -0.36f, 0.0f);
          glVertex3f(-0.71f, -0.36f, 0.0f);glVertex3f(-0.76f, -0.27f, 0.0f);
          glVertex3f(-0.76f, -0.27f, 0.0f);glVertex3f(-0.79f, -0.15f, 0.0f);
          glVertex3f(-0.79f, -0.15f, 0.0f);glVertex3f(-0.77f, -0.03f, 0.0f);
          glVertex3f(-0.77f, -0.03f, 0.0f);glVertex3f(-0.80f, 0.01f, 0.0f);
          glVertex3f(-0.80f, 0.01f, 0.0f);glVertex3f(-0.75f, 0.10f, 0.0f);
      glEnd();

      glColor3f(duck[0], duck[1], duck[2]);
      glBegin(GL_POLYGON);
          glVertex3f(0.43f, -0.56f, 0.0f);glVertex3f(0.40f, -0.58f, 0.0f);
          glVertex3f(0.40f, -0.58f, 0.0f);glVertex3f(0.37f, -0.63f, 0.0f);
          glVertex3f(0.37f, -0.63f, 0.0f);glVertex3f(0.45f, -0.73f, 0.0f);
          glVertex3f(0.45f, -0.73f, 0.0f);glVertex3f(0.49f, -0.85f, 0.0f);
          glVertex3f(0.49f, -0.85f, 0.0f);glVertex3f(0.52f, -1.00f, 0.0f);
          glVertex3f(0.52f, -1.00f, 0.0f);glVertex3f(0.66f, -1.00f, 0.0f);
          glVertex3f(0.66f, -1.00f, 0.0f);glVertex3f(0.65f, -0.82f, 0.0f);
          glVertex3f(0.65f, -0.82f, 0.0f);glVertex3f(0.60f, -0.76f, 0.0f);
          glVertex3f(0.60f, -0.76f, 0.0f);glVertex3f(0.43f, -0.56f, 0.0f);
      glEnd();

      glColor3f(1.0, 1.0, 1.0);
      glBegin(GL_POLYGON);
          glVertex3f(-0.72f, -0.84f, 0.0f);glVertex3f(-0.68f, -0.75f, 0.0f);
          glVertex3f(-0.68f, -0.75f, 0.0f);glVertex3f(-0.64f, -0.69f, 0.0f);
          glVertex3f(-0.64f, -0.69f, 0.0f);glVertex3f(-0.59f, -0.63f, 0.0f);
          glVertex3f(-0.59f, -0.63f, 0.0f);glVertex3f(-0.47f, -0.55f, 0.0f);
          glVertex3f(-0.47f, -0.55f, 0.0f);glVertex3f(-0.62f, -0.43f, 0.0f);
          glVertex3f(-0.62f, -0.43f, 0.0f);glVertex3f(-0.71f, -0.36f, 0.0f);
          glVertex3f(-0.71f, -0.36f, 0.0f);glVertex3f(-0.76f, -0.27f, 0.0f);
          glVertex3f(-0.76f, -0.27f, 0.0f);glVertex3f(-0.72f, -0.84f, 0.0f);
      glEnd();

      glColor3f(duck[0], duck[1], duck[2]);
      glBegin(GL_POLYGON);
          glVertex3f(-0.72f, -0.84f, 0.0f);glVertex3f(-0.68f, -0.75f, 0.0f);
          glVertex3f(-0.68f, -0.75f, 0.0f);glVertex3f(-0.64f, -0.69f, 0.0f);
          glVertex3f(-0.64f, -0.69f, 0.0f);glVertex3f(-0.59f, -0.63f, 0.0f);
          glVertex3f(-0.59f, -0.63f, 0.0f);glVertex3f(-0.47f, -0.55f, 0.0f);
          glVertex3f(-0.47f, -0.55f, 0.0f);glVertex3f(-0.72f, -0.84f, 0.0f);
      glEnd();

      glColor3f(1.0, 1.0, 1.0);
      glBegin(GL_POLYGON);
          glVertex3f(-0.34f, 0.64f, 0.0f);glVertex3f(-0.09f, 0.69f, 0.0f);
          glVertex3f(-0.09f, 0.69f, 0.0f);glVertex3f(-0.08f, 0.88f, 0.0f);
          glVertex3f(-0.08f, 0.88f, 0.0f);glVertex3f(-0.34f, 0.64f, 0.0f);
      glEnd();

      glColor3f(1.0, 1.0, 1.0);
      glBegin(GL_POLYGON);
          glVertex3f(0.24f, 0.77f, 0.0f);glVertex3f(0.16f, 0.75f, 0.0f);
          glVertex3f(0.16f, 0.75f, 0.0f);glVertex3f(0.12f, 0.68f, 0.0f);
          glVertex3f(0.12f, 0.68f, 0.0f);glVertex3f(0.24f, 0.77f, 0.0f);
      glEnd();

      glLineWidth(1.0f);
      glColor3f(0.0, 0.0, 0.0);
      glBegin(GL_LINE_STRIP);
          glVertex3f(-0.75f, 0.10f, 0.0f);glVertex3f(-0.76f, 0.22f, 0.0f);
          glVertex3f(-0.76f, 0.22f, 0.0f);glVertex3f(-0.72f, 0.31f, 0.0f);
          glVertex3f(-0.72f, 0.31f, 0.0f);glVertex3f(-0.65f, 0.39f, 0.0f);
          glVertex3f(-0.65f, 0.39f, 0.0f);glVertex3f(-0.63f, 0.44f, 0.0f);
          glVertex3f(-0.63f, 0.44f, 0.0f);glVertex3f(-0.56f, 0.50f, 0.0f);
          glVertex3f(-0.56f, 0.50f, 0.0f);glVertex3f(-0.50f, 0.55f, 0.0f);
          glVertex3f(-0.50f, 0.55f, 0.0f);glVertex3f(-0.44f, 0.58f, 0.0f);
          glVertex3f(-0.44f, 0.58f, 0.0f);glVertex3f(-0.37f, 0.63f, 0.0f);
          glVertex3f(-0.37f, 0.63f, 0.0f);glVertex3f(-0.34f, 0.64f, 0.0f);
          glVertex3f(-0.34f, 0.64f, 0.0f);glVertex3f(-0.09f, 0.69f, 0.0f);
          glVertex3f(-0.09f, 0.69f, 0.0f);glVertex3f(-0.08f, 0.88f, 0.0f);
          glVertex3f(-0.08f, 0.88f, 0.0f);glVertex3f(-0.04f, 0.90f, 0.0f);
          glVertex3f(-0.04f, 0.90f, 0.0f);glVertex3f(-0.03f, 0.92f, 0.0f);
          glVertex3f(-0.03f, 0.92f, 0.0f);glVertex3f(0.01f, 0.92f, 0.0f);
          glVertex3f(0.01f, 0.92f, 0.0f);glVertex3f(0.04f, 0.89f, 0.0f);
          glVertex3f(0.04f, 0.89f, 0.0f);glVertex3f(0.05f, 0.86f, 0.0f);
          glVertex3f(0.05f, 0.86f, 0.0f);glVertex3f(0.04f, 0.77f, 0.0f);
          glVertex3f(0.04f, 0.77f, 0.0f);glVertex3f(0.12f, 0.83f, 0.0f);
          glVertex3f(0.12f, 0.83f, 0.0f);glVertex3f(0.22f, 0.84f, 0.0f);
          glVertex3f(0.22f, 0.84f, 0.0f);glVertex3f(0.27f, 0.82f, 0.0f);
          glVertex3f(0.27f, 0.82f, 0.0f);glVertex3f(0.24f, 0.77f, 0.0f);
          glVertex3f(0.24f, 0.77f, 0.0f);glVertex3f(0.16f, 0.75f, 0.0f);
          glVertex3f(0.16f, 0.75f, 0.0f);glVertex3f(0.12f, 0.68f, 0.0f);
          glVertex3f(0.12f, 0.68f, 0.0f);glVertex3f(0.23f, 0.67f, 0.0f);
          glVertex3f(0.23f, 0.67f, 0.0f);glVertex3f(0.32f, 0.61f, 0.0f);
          glVertex3f(0.32f, 0.61f, 0.0f);glVertex3f(0.37f, 0.56f, 0.0f);
          glVertex3f(0.37f, 0.56f, 0.0f);glVertex3f(0.41f, 0.50f, 0.0f);
          glVertex3f(0.41f, 0.50f, 0.0f);glVertex3f(0.55f, 0.35f, 0.0f);
          glVertex3f(0.55f, 0.35f, 0.0f);glVertex3f(0.58f, 0.27f, 0.0f);
          glVertex3f(0.58f, 0.27f, 0.0f);glVertex3f(0.61f, 0.26f, 0.0f);
          glVertex3f(0.61f, 0.26f, 0.0f);glVertex3f(0.68f, 0.17f, 0.0f);
          glVertex3f(0.68f, 0.17f, 0.0f);glVertex3f(0.69f, 0.09f, 0.0f);
          glVertex3f(0.69f, 0.09f, 0.0f);glVertex3f(0.74f, 0.03f, 0.0f);
          glVertex3f(0.74f, 0.03f, 0.0f);glVertex3f(0.73f, -0.08f, 0.0f);
          glVertex3f(0.73f, -0.08f, 0.0f);glVertex3f(0.71f, -0.17f, 0.0f);
          glVertex3f(0.71f, -0.17f, 0.0f);glVertex3f(0.67f, -0.29f, 0.0f);
          glVertex3f(0.67f, -0.29f, 0.0f);glVertex3f(0.63f, -0.37f, 0.0f);
          glVertex3f(0.63f, -0.37f, 0.0f);glVertex3f(0.57f, -0.44f, 0.0f);
          glVertex3f(0.57f, -0.44f, 0.0f);glVertex3f(0.53f, -0.47f, 0.0f);
          glVertex3f(0.53f, -0.47f, 0.0f);glVertex3f(0.46f, -0.50f, 0.0f);
          glVertex3f(0.46f, -0.50f, 0.0f);glVertex3f(0.43f, -0.56f, 0.0f);
          glVertex3f(0.43f, -0.56f, 0.0f);glVertex3f(0.40f, -0.58f, 0.0f);
          glVertex3f(0.40f, -0.58f, 0.0f);glVertex3f(0.37f, -0.63f, 0.0f);
          glVertex3f(0.37f, -0.63f, 0.0f);glVertex3f(0.45f, -0.73f, 0.0f);
          glVertex3f(0.45f, -0.73f, 0.0f);glVertex3f(0.49f, -0.85f, 0.0f);
          glVertex3f(0.49f, -0.85f, 0.0f);glVertex3f(0.52f, -1.00f, 0.0f);
          glVertex3f(0.52f, -1.00f, 0.0f);glVertex3f(-0.47f, -1.00f, 0.0f);
          glVertex3f(-0.47f, -1.00f, 0.0f);glVertex3f(-0.43f, -0.76f, 0.0f);
          glVertex3f(-0.43f, -0.76f, 0.0f);glVertex3f(-0.48f, -1.00f, 0.0f);
          glVertex3f(-0.48f, -1.00f, 0.0f);glVertex3f(-0.70f, -1.00f, 0.0f);
          glVertex3f(-0.70f, -1.00f, 0.0f);glVertex3f(-0.72f, -0.84f, 0.0f);
          glVertex3f(-0.72f, -0.84f, 0.0f);glVertex3f(-0.68f, -0.75f, 0.0f);
          glVertex3f(-0.68f, -0.75f, 0.0f);glVertex3f(-0.64f, -0.69f, 0.0f);
          glVertex3f(-0.64f, -0.69f, 0.0f);glVertex3f(-0.59f, -0.63f, 0.0f);
          glVertex3f(-0.59f, -0.63f, 0.0f);glVertex3f(-0.47f, -0.55f, 0.0f);
          glVertex3f(-0.47f, -0.55f, 0.0f);glVertex3f(-0.62f, -0.43f, 0.0f);
          glVertex3f(-0.62f, -0.43f, 0.0f);glVertex3f(-0.71f, -0.36f, 0.0f);
          glVertex3f(-0.71f, -0.36f, 0.0f);glVertex3f(-0.76f, -0.27f, 0.0f);
          glVertex3f(-0.76f, -0.27f, 0.0f);glVertex3f(-0.79f, -0.15f, 0.0f);
          glVertex3f(-0.79f, -0.15f, 0.0f);glVertex3f(-0.77f, -0.03f, 0.0f);
          glVertex3f(-0.77f, -0.03f, 0.0f);glVertex3f(-0.80f, 0.01f, 0.0f);
          glVertex3f(-0.80f, 0.01f, 0.0f);glVertex3f(-0.75f, 0.10f, 0.0f);
      glEnd();

      //右手
      glBegin(GL_LINES);
          glVertex3f(0.43f, -0.56f, 0.0f);glVertex3f(0.40f, -0.58f, 0.0f);
          glVertex3f(0.40f, -0.58f, 0.0f);glVertex3f(0.37f, -0.63f, 0.0f);
          glVertex3f(0.37f, -0.63f, 0.0f);glVertex3f(0.45f, -0.73f, 0.0f);
          glVertex3f(0.45f, -0.73f, 0.0f);glVertex3f(0.49f, -0.85f, 0.0f);
          glVertex3f(0.49f, -0.85f, 0.0f);glVertex3f(0.52f, -1.00f, 0.0f);
          glVertex3f(0.52f, -1.00f, 0.0f);glVertex3f(0.66f, -1.00f, 0.0f);
          glVertex3f(0.66f, -1.00f, 0.0f);glVertex3f(0.65f, -0.82f, 0.0f);
          glVertex3f(0.65f, -0.82f, 0.0f);glVertex3f(0.60f, -0.76f, 0.0f);
          glVertex3f(0.60f, -0.76f, 0.0f);glVertex3f(0.43f, -0.56f, 0.0f);
      glEnd();
      glPopMatrix();

      //右眼
      glPushMatrix();
      glTranslated(0.15, 0.33, 0);
      glColor3f(1, 1, 1);
      glBegin(GL_POLYGON);
          for(int i=0;i<n;i++){
             glVertex2f(R*cos(2*PI/n*i)+0.1, R*sin(2*PI/n*i)-0.1);
          }
      glEnd();
      glPopMatrix();

      //右眼线条
      glPushMatrix();
      glColor3f(0, 0, 0);
      glTranslated(0.15, 0.33, 0);
      glBegin(GL_LINE_STRIP);
          for(int i=0;i<n;i++){
             glVertex2f(R*cos(2*PI/n*i)+0.1, R*sin(2*PI/n*i)-0.1);
          }
      glEnd();
      glPopMatrix();

      //右眼珠
      glPushMatrix();
      glTranslated(0.27, 0.24, 0);
      glRotated(step, 0.0f, 0.0f, 1.0f);
      glTranslated(-0.10, 0.10, 0);

      glColor3f(0, 0, 0);
      glBegin(GL_POLYGON);
          for(int i=0;i<n;i++){
             glVertex2f(R3*cos(2*PI/n*i)-0.1, R3*sin(2*PI/n*i)-0.1);
          }
      glEnd();
      glPopMatrix();
      //左眼
      glPushMatrix();
      glTranslated(-0.17, 0.33, 0);
      glColor3f(1, 1, 1);
      glBegin(GL_POLYGON);
          for(int i=0;i<n;i++){
             glVertex2f(R*cos(2*PI/n*i)-0.1, R*sin(2*PI/n*i)-0.1);
          }
      glEnd();
      glPopMatrix();

      //左眼线条
      glPushMatrix();
      glTranslated(-0.17, 0.33, 0);
      glColor3f(0, 0, 0);
      glBegin(GL_LINE_STRIP);
          for(int i=0;i<n;i++){
             glVertex2f(R*cos(2*PI/n*i)-0.1, R*sin(2*PI/n*i)-0.1);
          }
      glEnd();
      glPopMatrix();

      //左腮红
      glPushMatrix();
      glTranslated(-0.40, -0.12, 0);
      glColor3f(1, color, 0);
      glBegin(GL_POLYGON);
          for(int i=0;i<n;i++){
             glVertex2f(R2*cos(2*PI/n*i)-0.1, R2*sin(2*PI/n*i)-0.1);
          }
      glEnd();
      glPopMatrix();

      //嘴巴
      glPushMatrix();
      glTranslated(-0.23, 0.02, 0);
      glColor3f(1.00, 0.50, 0.0);
      glBegin(GL_POLYGON);
          glVertex3f(0.22f, 0.04f, 0.0f);glVertex3f(0.11f, 0.0f, 0.0f);
          glVertex3f(0.11f, 0.0f, 0.0f);glVertex3f(0.03f, -0.06f, 0.0f);
          glVertex3f(0.03f, -0.06f, 0.0f);glVertex3f(-0.07f, -0.16f, 0.0f);
          glVertex3f(-0.07f, -0.16f, 0.0f);glVertex3f(0.07f, -0.29f, 0.0f);
          glVertex3f(0.07f, -0.29f, 0.0f);glVertex3f(0.19f, -0.36f, 0.0f);
          glVertex3f(0.19f, -0.36f, 0.0f);glVertex3f(0.28f, -0.36f, 0.0f);
          glVertex3f(0.28f, -0.36f, 0.0f);glVertex3f(0.42f, -0.28f, 0.0f);
          glVertex3f(0.42f, -0.28f, 0.0f);glVertex3f(0.53f, -0.15f, 0.0f);
          glVertex3f(0.53f, -0.15f, 0.0f);glVertex3f(0.38f, -0.04f, 0.0f);
          glVertex3f(0.38f, -0.04f, 0.0f);glVertex3f(0.23f, 0.05f, 0.0f);
      glEnd();

      glColor3f(0.0, 0.0, 0.0);
      glBegin(GL_LINES);
          glVertex3f(0.22f, 0.04f, 0.0f);glVertex3f(0.11f, 0.0f, 0.0f);
          glVertex3f(0.11f, 0.0f, 0.0f);glVertex3f(0.03f, -0.06f, 0.0f);
          glVertex3f(0.03f, -0.06f, 0.0f);glVertex3f(-0.07f, -0.16f, 0.0f);
          glVertex3f(-0.07f, -0.16f, 0.0f);glVertex3f(0.07f, -0.29f, 0.0f);
          glVertex3f(0.07f, -0.29f, 0.0f);glVertex3f(0.19f, -0.36f, 0.0f);
          glVertex3f(0.19f, -0.36f, 0.0f);glVertex3f(0.28f, -0.36f, 0.0f);
          glVertex3f(0.28f, -0.36f, 0.0f);glVertex3f(0.42f, -0.28f, 0.0f);
          glVertex3f(0.42f, -0.28f, 0.0f);glVertex3f(0.53f, -0.15f, 0.0f);
          glVertex3f(0.53f, -0.15f, 0.0f);glVertex3f(0.38f, -0.04f, 0.0f);
          glVertex3f(0.38f, -0.04f, 0.0f);glVertex3f(0.23f, 0.05f, 0.0f);
      glEnd();

      glColor3f(0.0, 0.0, 0.0);
      glBegin(GL_LINES);
          glVertex3f(-0.07f, -0.16f, 0.0f);glVertex3f(0.24f, -0.23f, 0.0f);
          glVertex3f(0.24f, -0.23f, 0.0f);glVertex3f(0.53f, -0.15f, 0.0f);
      glEnd();
      glPopMatrix();

      //右腮红
      glPushMatrix();
      glColor3f(1, color, 0);
      glTranslated(0.60, -0.08, 0);
      glBegin(GL_POLYGON);
          for(int i=0;i<n;i++){
             glVertex2f(R2*cos(2*PI/n*i)-0.1, R2*sin(2*PI/n*i)-0.1);
          }
      glEnd();
      glPopMatrix();

      //左眼珠
      glPushMatrix();
      glTranslated(-0.28, 0.25, 0);
      glRotated(step, 0.0f, 0.0f, 1.0f);
      glTranslated(-0.10, 0.10, 0);
      glColor3f(0, 0, 0);
      glBegin(GL_POLYGON);
          for(int i=0;i<n;i++){
             glVertex2f(R3*cos(2*PI/n*i)-0.1, R3*sin(2*PI/n*i)-0.1);
          }
      glEnd();
      glPopMatrix();
      glutSwapBuffers();
}

void resize(GLsizei w,GLsizei h)
{
	GLfloat ratio=(GLfloat)w/(GLfloat)h;
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if(w<=h)//保持形状不变
		gluOrtho2D(-1.0,1.0,-1.0/ratio,1.0/ratio);
	else
		gluOrtho2D(-1.0*ratio,1.0*ratio,-1.0,1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void menuFunc(int value)
{
    //绿鸭子
    if(value == 1){
        duck[0] = 0.0;
        duck[1] = 1.0;
        duck[2] = 0.0;
    }//蓝鸭子
    if(value == 2){
        duck[0] = 0.0;
        duck[1] = 0.0;
        duck[2] = 1.0;
    }//红鸭子
    if(value == 3){
        duck[0] = 1.0;
        duck[1] = 0.0;
        duck[2] = 0.0;
    }//黄鸭子
    if(value == 4){
        duck[0] = 1.0;
        duck[1] = 1.0;
        duck[2] = 0.0;
    }
    glutPostRedisplay();
}

void NormalKeys(unsigned char key, int x, int y)
{
    int mod = glutGetModifiers();
    if(mod == GLUT_ACTIVE_ALT){
        if(key == '1'){
            step -= 60.0f;
        }
        if(key == '2'){
            step += 60.0f;
        }
        step = (GLfloat)((int)step%360);
        glutPostRedisplay();
    }
}

int main(int argc, char *argv[])
{
   int MainManuHandle;
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
   glutInitWindowPosition(100, 100);
   glutInitWindowSize(400, 400);
   glutCreateWindow("Duck Duck!");
   MainManuHandle = glutCreateMenu(menuFunc);
   glutAddMenuEntry("green duck", 1);
   glutAddMenuEntry("blue duck", 2);
   glutAddMenuEntry("red duck", 3);
   glutAddMenuEntry("yellow duck", 4);
   glutAttachMenu(GLUT_RIGHT_BUTTON);
   glutKeyboardFunc(NormalKeys);
   glutTimerFunc(50,time,1);
   glutDisplayFunc(display);
   glutReshapeFunc(resize);
   glClearColor(1, 1, 1, 1);
   glutMainLoop();
 return 0;
}




