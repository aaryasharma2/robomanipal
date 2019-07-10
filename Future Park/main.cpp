/*
 * GLUT Shapes Demo
 *
 * Written by Nigel Stewart November 2003
 *
 * This program is test harness for the sphere, cone
 * and torus shapes in GLUT.
 *
 * Spinning wireframe and smooth shaded shapes are
 * displayed until the ESC or q key is pressed.  The
 * number of geometry stacks and slices can be adjusted
 * using the + and - keys.
 */
#include <windows.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>

static int slices = 16;
static int stacks = 60;
static double topbot=0;
static double leftright=0;
static double inout=0;

//car whips
static bool whipeFlag=false;
static double whipe=0;
static bool whipeMax = false;

//car front light;
static bool carFrontLight= false;
static bool carStrongFrontLight= false;

//car stop rear light
static bool carStopLight=false;

static bool carBackLight=false;

//car wheels
static int wheelx=10;
static int wheely=10;
static int wheelz=5;


/* GLUT callback Handlers */

static void resize(int width, int height)
{
    const float ar = (float) width / (float) height;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;
}

static void display(void)
{
    const double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
    const double a = t*90.0;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3d(1,0,0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-100,100,-100,100,-100,100);

    //car matrix
    glPushMatrix();
        glScaled(0.5,0.5,0.5);
        //glRotated(0,1,0,0);
        glRotated(slices-16,0,1,0);
        glTranslated(0,-50,70);
        //glRotated(stacks,1,0,0);

        //goto whipees;

        //wheels
        glColor3d(0,0,0);
        glPushMatrix();
            glColor3d(0,0,0);
            glTranslated(leftright,topbot,inout+5);
            glRotated(-leftright,0,0,1);
            glScaled(wheelx,wheely,wheelz);
            glutSolidTorus(1,0,500,500);
        glPopMatrix();

        glPushMatrix();
            glColor3d(0,0,0);
            glTranslated(leftright-50,topbot,inout+5);
            glRotated(-leftright,0,0,1);
            glScaled(wheelx,wheely,wheelz);
            glutSolidTorus(1,0,500,500);
        glPopMatrix();


        glPushMatrix();
            glTranslated(leftright+30,topbot,inout+5);
            glRotated(-leftright,0,0,1);
            glScaled(wheelx,wheely,wheelz);
            glutSolidTorus(1,0,500,500);
        glPopMatrix();

        glPushMatrix();
            glRotated(180,1,0,0);
            glTranslated(leftright,-topbot,-(inout-45));
            glRotated(leftright,0,0,1);
            glScaled(wheelx,wheely,wheelz);
            glutSolidTorus(1,0,500,500);
        glPopMatrix();

        glPushMatrix();
            glRotated(180,1,0,0);
            glTranslated(leftright-50,-topbot,-(inout-45));
            glRotated(leftright,0,0,1);
            glScaled(wheelx,wheely,wheelz);
            glutSolidTorus(1,0,500,500);
        glPopMatrix();

        glPushMatrix();
            glRotated(180,1,0,0);
            glTranslated(leftright+30,-topbot,-(inout-45));
            glRotated(leftright,0,0,1);
            glScaled(wheelx,wheely,wheelz);
            glutSolidTorus(1,0,500,500);
        glPopMatrix();
//wheel wires
        glColor3d(0.9,0.9,0.9);
        glPushMatrix();
            glTranslated(leftright,topbot,inout+9);
            glRotated(-leftright,0,0,1);
            glScaled(7,7,1);
            glutWireSphere(1,10,10);
        glPopMatrix();

        glPushMatrix();
            glTranslated(leftright+30,topbot,inout+9);
            glRotated(-leftright,0,0,1);
            glScaled(7,7,1);
            glutWireSphere(1,10,10);
        glPopMatrix();

        glPushMatrix();
            glTranslated(leftright-50,topbot,inout+9);
            glRotated(-leftright,0,0,1);
            glScaled(7,7,1);
            glutWireSphere(1,10,10);
        glPopMatrix();

        glPushMatrix();
            glRotated(180,1,0,0);
            glTranslated(leftright,-topbot,-(inout-49));
            glRotated(leftright,0,0,1);
            glScaled(7,7,1);
            glutWireSphere(1,10,10);
        glPopMatrix();

        glPushMatrix();
            glRotated(180,1,0,0);
            glTranslated(leftright+30,-topbot,-(inout-49));
            glRotated(leftright,0,0,1);
            glScaled(7,7,1);
            glutWireSphere(1,10,10);
        glPopMatrix();

        glPushMatrix();
            glRotated(180,1,0,0);
            glTranslated(leftright-50,-topbot,-(inout-49));
            glRotated(leftright,0,0,1);
            glScaled(7,7,1);
            glutWireSphere(1,10,10);
        glPopMatrix();



    carbody:
        //car body
        glColor3d(0.5,0,0);

        glPushMatrix();
            glTranslated(leftright-25,topbot+30,inout-20);
            glRotated(90,0,1,0);
            glScaled(50,50,80);
            glutSolidCube(1);
        glPopMatrix();

        glColor3d(0.8,0.8,0.8);
        glPushMatrix();
            glTranslated(leftright+30,topbot+25,inout-20);
            glRotated(90,0,1,0);
            glScaled(50,40,20);
            glutSolidCube(1);
        glPopMatrix();
turt:
        glPushMatrix();
            glTranslated(leftright+25,topbot+50,inout-5);
            glRotated(90,1,0,0);
            glScaled(0.5,0.5,20);
            glutSolidTorus(0.5,1,500,500);
        glPopMatrix();

        glPushMatrix();
            glTranslated(leftright+25,topbot+50,inout-35);
            glRotated(90,1,0,0);
            glScaled(0.5,0.5,20);
            glutSolidTorus(0.5,1,500,500);
        glPopMatrix();

        glPushMatrix();
            glTranslated(leftright+20,topbot+10,inout-20);
            glScaled(10,10,10);
            glutSolidCube(1);
        glPopMatrix();

//glass
//front
    glass:
        glPushMatrix();
            glColor3d(0.4,0.4,0.4);
            glTranslated(leftright,topbot+45,inout+5);
            glScaled(10,5,1);
            glutSolidCube(1);
        glPopMatrix();

        glPushMatrix();
            glColor3d(0.4,0.4,0.4);
            glTranslated(leftright-25,topbot+45,inout+5);
            glScaled(10,5,1);
            glutSolidCube(1);
        glPopMatrix();

        glPushMatrix();
            glColor3d(0.4,0.4,0.4);
            glTranslated(leftright-50,topbot+45,inout+5);
            glScaled(10,5,1);
            glutSolidCube(1);
        glPopMatrix();
//rear glass
        glPushMatrix();
            glRotated(180,1,0,0);
            glColor3d(0.4,0.4,0.4);
            glTranslated(leftright,-topbot-45,-(inout-45));
            glScaled(10,5,1);
            glutSolidCube(1);
        glPopMatrix();

        glPushMatrix();
            glRotated(180,1,0,0);
            glColor3d(0.4,0.4,0.4);
            glTranslated(leftright-25,-topbot-45,-(inout-45));
            glScaled(10,5,1);
            glutSolidCube(1);
        glPopMatrix();

        glPushMatrix();
            glRotated(180,1,0,0);
            glColor3d(0.4,0.4,0.4);
            glTranslated(leftright-50,-topbot-45,-(inout-45));
            glScaled(10,5,1);
            glutSolidCube(1);
        glPopMatrix();

driverglass:

        glPushMatrix();
            glColor3d(0.4,0.4,0.4);
            glTranslated(leftright+30,topbot+35,inout+5);
            glScaled(10,10,1);
            glutSolidCube(1);
        glPopMatrix();

        glPushMatrix();
            glRotated(180,1,0,0);
            glColor3d(0.4,0.4,0.4);
            glTranslated(leftright+30,-(topbot+35),-(inout-45));
            glScaled(10,10,1);
            glutSolidCube(1);
        glPopMatrix();

        glPushMatrix();
            glColor3d(0.6,0.6,0.6);
            glTranslated(leftright+40,topbot+30,inout-20);
            glScaled(1,20,40);
            glutSolidCube(1);
        glPopMatrix();

whipees:
        if(whipeFlag){
            if(whipeMax){
                whipe-=3;
            }
            else{
                whipe+=3;
            }
            if(whipe>=90){
                whipeMax= true;
            }
            else if(whipe<=0){
                whipeMax = false;
            }
        }
        glPushMatrix();
                glColor3d(0,0,0);
                glTranslated(leftright+41,topbot+20+whipe/20,inout-12);
                glRotated(whipe,1,0,0);
                glScaled(1,1,20);
                glutSolidCube(1);
        glPopMatrix();

        glPushMatrix();
                glColor3d(0,0,0);
                glTranslated(leftright+41,topbot+20+whipe/20,inout-27);
                glRotated(whipe,1,0,0);
                glScaled(1,1,20);
                glutSolidCube(1);
        glPopMatrix();

//front light
        if(carFrontLight && carStrongFrontLight)
            glColor3d(1,1,1);
        else if(carFrontLight)
            glColor3d(0.7,0.7,0.7);
        else
            glColor3d(0.3,0.3,0.3);

        glPushMatrix();
                glTranslated(leftright+40,topbot+10,inout-5);
                glScaled(1,5,10);
                glutSolidCube(1);
        glPopMatrix();

        glPushMatrix();
                glTranslated(leftright+40,topbot+10,inout-35);
                glScaled(1,5,10);
                glutSolidCube(1);
        glPopMatrix();

        if(carFrontLight && !carStopLight  && !carBackLight)
            glColor3d(0.7,0,0);
        else if(carStopLight)
            glColor3d(1,0,0);
        else if(carBackLight)
            glColor3d(1,1,1);
        else
            glColor3d(0.2,0,0);

//light rear
        carBackLight=false;
        carStopLight=false;


        glPushMatrix();
                glTranslated(leftright-65,topbot+10,inout-5);
                glScaled(1,5,10);
                glutSolidCube(1);
        glPopMatrix();

        glPushMatrix();
                glTranslated(leftright-65,topbot+10,inout-35);
                glScaled(1,5,10);
                glutSolidCube(1);
        glPopMatrix();
// rear decor
        glPushMatrix();
                glColor3d(0,0,0);
                glTranslated(leftright-65,topbot+30,inout-20);
                glScaled(1,50,1);
                glutSolidCube(1);
        glPopMatrix();

        glPushMatrix();
                glColor3d(0,0,0);
                glTranslated(leftright-65,topbot+30,inout-25);
                glScaled(1,1,5);
                glutSolidCube(1);
        glPopMatrix();

        glPushMatrix();
                glColor3d(0,0,0);
                glTranslated(leftright-65,topbot+30,inout-15);
                glScaled(1,1,5);
                glutSolidCube(1);
        glPopMatrix();
//front doors
        glPushMatrix();
                glColor3d(0,0,0);
                glTranslated(leftright+27,topbot+25,inout+5);
                glScaled(4,1,1);
                glutSolidCube(1);
        glPopMatrix();

        glPushMatrix();
                glColor3d(0,0,0);
                glTranslated(leftright+27,topbot+25,inout-45);
                glScaled(4,1,1);
                glutSolidCube(1);
        glPopMatrix();

    glPopMatrix();

//street
    glPushMatrix();
        glColor3d(0,0,0);
        glTranslated(0,-50,0);
        glScaled(200,100,1);
        glutSolidCube(1);

    glPopMatrix();
//white marks
    glPushMatrix();
        glColor3d(0.5,0.5,0.5);
        glTranslated(-70,-50,1);
        glScaled(50,5,40);
        glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
        glColor3d(0.5,0.5,0.5);
        glTranslated(0,-50,1);
        glScaled(50,5,40);
        glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
        glColor3d(0.5,0.5,0.5);
        glTranslated(70,-50,1);
        glScaled(50,5,1);
        glutSolidCube(1);
    glPopMatrix();

//moon
    glPushMatrix();
        glColor3d(0.62,0.824,1);
        glTranslated(70,70,-50);
        glScaled(15,15,15);
        glutSolidSphere(1,500,500);
    glPopMatrix();


    glutSwapBuffers();
}


static void key(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 27 :
        case 'q':
            exit(0);
            break;

        case '+':
            slices++;
            slices++;
            slices++;
            slices++;
            break;

        case '-':
                slices--;
                slices--;
                slices--;
                slices--;
            break;
        case '8':
            stacks++;
            stacks++;
            stacks++;
            stacks++;
            break;
        case '2':
            stacks--;
            stacks--;
            stacks--;
            stacks--;
            break;
        case 'W':
        case 'w':
            topbot++;
            topbot++;
            topbot++;
            break;
        case 'S':
        case 's':
            topbot--;
            topbot--;
            topbot--;
            break;
        case 'A':
        case 'a':
            leftright--;
            leftright--;
            leftright--;
            carBackLight=true;
            break;
        case 'D':
        case 'd':
            leftright++;
            leftright++;
            leftright++;
            break;
        case 'K':
        case 'k':
            whipeFlag=false;
            whipe=0;
            inout--;
            inout--;
            inout--;
            break;
        case 'L':
        case 'l':
            whipeFlag=false;
            whipe=0;
            inout++;
            inout++;
            inout++;
            break;
        case 'B':
        case 'b':
            if(whipeFlag)
                whipeFlag=false;
            else
                whipeFlag=true;
            break;
        case 'H':
        case 'h':
            if(carFrontLight && carStrongFrontLight){
                carFrontLight=false;
                carStrongFrontLight=false;
            }
            else if(carFrontLight)
                carStrongFrontLight=true;
            else
                carFrontLight=true;
            break;
        case ' ':
            carStopLight=true;
            break;
    }

    glutPostRedisplay();
}

static void idle(void)
{
    glutPostRedisplay();
}

const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };

/* Program entry point */

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("GLUT Shapes");

    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutIdleFunc(idle);

    glClearColor(0.0665,0.251,0.349,1);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);

    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);

    glutMainLoop();

    return EXIT_SUCCESS;
}
