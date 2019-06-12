#include <windows.h>
#include<GL/gl.h>
#include<GL/glut.h>
#include<math.h>
#define PI  3.141592653589793238
float add_r,add_g,add_b;
void circle(float x_value,float y_value, float radious_value)
{
    float x =x_value;
    float y =y_value;
    float radious = radious_value;
    float twicePI = 2.0f*PI;
    int racmax=50;
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x,y);
    for(int i=0; i<=racmax; i++)
    {
        glVertex2f(
            x+(radious*cos(i*twicePI/racmax)),
            y+(radious*sin(i*twicePI/racmax))
        );
    }
    glEnd();
}

//////Sun & Moon//////////
float sun_y_position =80;
float moon_y_position=400;
float sun_color_g=1.0;
bool night = false;
bool evening=false;
void Sun()
{
    float x =680;
    float y = 300;
    float radious = 100;
    float twicePI = 2.0f*PI;
    int racmax=50;
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(1.0f,sun_color_g,0.0f);
    glVertex2f(x,y);
    for(int i=0; i<=racmax; i++)
    {
        glVertex2f(
            x+(radious*cos(i*twicePI/racmax)),
            y+(radious*sin(i*twicePI/racmax))
        );
    }
    glEnd();
}



void Moon()
{
    float x =680;
    float y = 300;
    float radious = 100;
    float twicePI = 2.0f*PI;
    int racmax=50;
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(1.0f,1.0f,1.0f);
    glVertex2f(x,y);
    for(int i=0; i<=racmax; i++)
    {
        glVertex2f(
            x+(radious*cos(i*twicePI/racmax)),
            y+(radious*sin(i*twicePI/racmax))
        );
    }
    glEnd();
}
/////////Sky///////////
float sky_r=0.3019,sky_g=0.9568,sky_b=1.0;

void Sky()
{
    glBegin(GL_QUADS);
    if(night==true)
        glColor3f(0.282353,0.282353,0.941176);
    else
        glColor3f(sky_r,sky_g,sky_b);
    glVertex2f(0,50);
    if(night==true)
        glColor3f(0.282353,0.282353,0.941176);
    else
        glColor3f(sky_r,sky_g,sky_b);
    glVertex2f(1900,50);
    if (evening==true)
        glColor3f(0.980392,0.627451,0.137255);
    else
        glColor3f(sky_r,sky_g,sky_b);
    glVertex2f(1900,528);
    if (evening==true)
        glColor3f(0.980392,0.627451,0.137255);
    else
        glColor3f(sky_r,sky_g,sky_b);
    glVertex2f(0,528);
    glEnd();
}
///////////////////////////


////////Clouds/////////////
float Cloud_1_x_pos=0;
void Cloud_1()
{
    if(evening)
        glColor3f(1,0.843137,0.568627);
    else if(night)
        glColor3f(0.509804,0.564706,0.619608);
    else
        glColor3f(1,1,1);
    circle(200,200,40);
    circle(210,209,40);
    circle(230,200,40);
    circle(220,190,40);
    circle(250,230,40);
    circle(260,180,40);
    circle(220,200,40);
    circle(190,195,40);
    circle(280,200,40);
    circle(300,197,40);
}
float Cloud_1cpy_x_pos=0;
void Cloud_1cpy()
{
    if(evening)
        glColor3f(1,0.843137,0.568627);
    else if(night)
        glColor3f(0.509804,0.564706,0.619608);
    else
        glColor3f(1,1,1);
    circle(200,400,40);
    circle(210,409,40);
    circle(230,400,40);
    circle(220,390,40);
    circle(250,430,40);
    circle(260,380,40);
    circle(220,400,40);
    circle(190,395,40);
    circle(280,400,40);
    circle(300,397,40);
}
float Cloud_2_x_pos =0;
void Cloud_2()
{
    if(evening)
        glColor3f(1,0.843137,0.568627);
    else if(night)
        glColor3f(0.509804,0.564706,0.619608);
    else
        glColor3f(1,1,1);
    circle(400,300,40);
    circle(410,309,40);
    circle(430,300,40);
    circle(420,290,40);
    circle(450,330,40);
    circle(460,280,40);
    circle(420,300,40);
    circle(390,295,40);
    circle(480,300,40);
    circle(500,297,40);
    circle(380,300,40);
    circle(520,300,40);
    circle(515,310,40);
    circle(530,295,40);
    circle(360,310,40);
    circle(550,300,40);
    circle(581,315,40);
}
float Cloud_3_x_pos=0;
void Cloud_3()
{

    if(evening)
        glColor3f(1,0.843137,0.568627);
    else if(night)
        glColor3f(0.509804,0.564706,0.619608);
    else
        glColor3f(1,1,1);
    circle(100,430,40);
    circle(110,439,40);
    circle(130,420,40);
    circle(120,420,40);
    circle(150,460,40);
    circle(160,410,40);
    circle(120,430,40);
    circle(90,425,40);
    circle(180,420,40);
    circle(200,407,40);
    circle(80,420,40);
    circle(220,430,40);
    circle(215,440,40);
    circle(230,405,40);
    circle(60,450,40);
    circle(250,430,40);
    circle(281,425,40);
    circle(70,430,40);
}
void cloud_movement_timer(int)
{
    glutTimerFunc(1000/90,cloud_movement_timer,0);
    if(Cloud_1_x_pos<1600)
    {
        Cloud_1_x_pos+=0.6;///cloud_1speed
    }
    else if (Cloud_1_x_pos>=1600)
    {
        Cloud_1_x_pos=(0);
    }
    if (Cloud_1cpy_x_pos<1600)
        Cloud_1cpy_x_pos+=0.8;///speed
    else if(Cloud_1cpy_x_pos>=1600)
        Cloud_1cpy_x_pos=0;
    if (Cloud_2_x_pos<1600)
        Cloud_2_x_pos+=0.3;///speed
    else if (Cloud_2_x_pos>=1600)
        Cloud_2_x_pos=-100;
    if(Cloud_3_x_pos<1600)
        Cloud_3_x_pos+=0.25;///speed
    else if(Cloud_3_x_pos>=1600)
        Cloud_3_x_pos=0;
    glutPostRedisplay();
}
///////////////////////////

///////Buildings///////////
void Building_1()
{
    glColor3f(0.054902,0.105882,0.141176);
    glBegin(GL_POLYGON);
    glVertex2f(435,528);
    glVertex2f(450,528);
    glVertex2f(450,-150);
    glVertex2f(435,-150);
    glEnd();

    glColor3f(0.627451+add_r,0.921569+add_g,0.980392+add_b);
    glBegin(GL_POLYGON);
    glVertex2f(365,528);
    glVertex2f(390,528);
    glVertex2f(390,500);
    glVertex2f(365,500);
    glEnd();
    float glass_y=45;
    for(int i = 0; i<14; i++)
    {
        if(night==true &&(i==1||i==3||i==4||i==5||i==10))
            glColor3f(0.984314,1,0);
        else
            glColor3f(0.627451+add_r,0.921569+add_g,0.980392+add_b);
        glBegin(GL_POLYGON);
        glVertex2f(365,528-glass_y);
        glVertex2f(390,528-glass_y);
        glVertex2f(390,500-glass_y);
        glVertex2f(365,500-glass_y);
        glEnd();
        glass_y+=45;
    }
    glColor3f(0.2+add_r,0.054902+add_g,0.145098+add_b);
    glBegin(GL_POLYGON);
    glVertex2f(355,528);
    glVertex2f(400,528);
    glVertex2f(400,-150);
    glVertex2f(355,-150);
    glEnd();

    glColor3f(0.054902+add_r,0.105882+add_g,0.141176+add_b);
    glBegin(GL_POLYGON);
    glVertex2f(305,528);
    glVertex2f(355,528);
    glVertex2f(355,-150);
    glVertex2f(305,-150);
    glEnd();

    glColor3f(0.631373+add_r,0.486275+add_g,0.384314+add_b);
    glBegin(GL_POLYGON);
    glVertex2f(205,528);
    glVertex2f(305,528);
    glVertex2f(305,450);
    glVertex2f(205,450);
    glEnd();

    glColor3f(0.054902+add_r,0.105882+add_g,0.141176+add_b);
    glBegin(GL_POLYGON);
    glVertex2f(195,528);
    glVertex2f(205,528);
    glVertex2f(205,-150);
    glVertex2f(195,-150);
    glEnd();

    glColor3f(0.054902+add_r,0.105882+add_g,0.141176+add_b);
    glBegin(GL_POLYGON);
    glVertex2f(155,528);
    glVertex2f(195,528);
    glVertex2f(195,508);
    glVertex2f(155,508);
    glEnd();
    float yx = 40;
    for (int i = 0; i<16; i++)
    {
        glBegin(GL_POLYGON);
        glVertex2f(155,528-yx);
        glVertex2f(195,528-yx);
        glVertex2f(195,508-yx);
        glVertex2f(155,508-yx);
        glEnd();
        yx=yx+40;
    }


    glColor3f(0.631373+add_r,0.486275+add_g,0.384314+add_b);
    glBegin(GL_POLYGON);
    glVertex2f(110,528);
    glVertex2f(150,528);
    glVertex2f(150,450);
    glVertex2f(110,450);
    glEnd();

    glColor3f(0.054902+add_r,0.105882+add_g,0.141176+add_b);
    glBegin(GL_POLYGON);
    glVertex2f(90,528);
    glVertex2f(105,528);
    glVertex2f(105,-150);
    glVertex2f(90,-150);
    glEnd();

    glColor3f(0.631373+add_r,0.486275+add_g,0.384314+add_b);
    glBegin(GL_POLYGON);
    glVertex2f(22,528);
    glVertex2f(85,528);
    glVertex2f(85,450);
    glVertex2f(22,450);
    glEnd();

    glColor3f(0.631373+add_r,0.486275+add_g,0.384314+add_b);
    glBegin(GL_POLYGON);
    glVertex2f(0,528);
    glVertex2f(20,528);
    glVertex2f(20,-150);
    glVertex2f(0,-150);
    glEnd();

    glColor3f(0.929412+add_r,0.611765+add_g,0.380392+add_b);
    glBegin(GL_POLYGON);
    glVertex2f(0,528);
    glVertex2f(450,528);
    glVertex2f(450,-150);
    glVertex2f(0,-150);
    glEnd();

}

void Building_2()
{
    glColor3f(0.627451+add_r,0.921569+add_g,0.980392+add_b);
    glBegin(GL_POLYGON);
    glVertex2f(460,330);
    glVertex2f(528,330);
    glVertex2f(528,280);
    glVertex2f(460,280);
    glEnd();

    glPushMatrix();
    float glass_y=70;
    for(int i=0; i<5; i++)
    {
        if(night==true &&(i==0||i==1||i==3||i==4))
            glColor3f(0.984314,1,0);
        else
            glColor3f(0.627451+add_r,0.921569+add_g,0.980392+add_b);
        glTranslatef(0,-glass_y,0);
        glBegin(GL_POLYGON);
        glVertex2f(460,330);
        glVertex2f(528,330);
        glVertex2f(528,280);
        glVertex2f(460,280);
        glEnd();
    }
    glPopMatrix();

    glColor3f(0.211765+add_r,0.321569+add_g,0.490196+add_b);
    glBegin(GL_POLYGON);
    glVertex2f(450,358);
    glVertex2f(538,358);
    glVertex2f(538,-80);
    glVertex2f(450,-80);
    glEnd();

    glColor3f(0.498039+add_r,0.654902+add_g,0.890196+add_b);
    glBegin(GL_POLYGON);
    glVertex2f(450,428);
    glVertex2f(550,428);
    glVertex2f(550,438);
    glVertex2f(450,438);
    glEnd();

    glColor3f(0.498039+add_r,0.654902+add_g,0.890196+add_b);
    glBegin(GL_POLYGON);
    glVertex2f(450,378);
    glVertex2f(550,378);
    glVertex2f(550,388);
    glVertex2f(450,388);
    glEnd();

    glColor3f(0.309804+add_r,0.490196+add_g,0.760784+add_b);
    glBegin(GL_POLYGON);
    glVertex2f(450,428);
    glVertex2f(550,428);
    glVertex2f(550,-80);
    glVertex2f(450,-80);
    glEnd();
}
void Building_3()
{
    float x_div=0,y_div=0;
    glColor3f(0.501961+add_r,0.415686+add_g,0.27451+add_b);
    for (int i=0; i<8; i++)
    {
        for(int j=0; j<7; j++)
        {
            glBegin(GL_POLYGON);
            glVertex2f(1000+x_div,20-y_div);
            glVertex2f(1040+x_div,20-y_div);
            glVertex2f(1040+x_div,17-y_div);
            glVertex2f(1000+x_div,17-y_div);
            glEnd();
            y_div+=30;
        }
        y_div=0;
        x_div+=50;
    }


    glColor3f(0.054902,0.0509804,0.14902);
    glBegin(GL_POLYGON);
    glVertex2f(1000,50);
    glVertex2f(1040,50);
    glVertex2f(1040,-200);
    glVertex2f(1000,-200);
    glEnd();
    float x_pos=50;
    for(int i=0; i<7; i++)
    {
        glBegin(GL_POLYGON);
        glVertex2f(1000+x_pos,50);
        glVertex2f(1040+x_pos,50);
        glVertex2f(1040+x_pos,-200);
        glVertex2f(1000+x_pos,-200);
        glEnd();
        x_pos+=50;
    }

    glColor3f(1,0.819608,0.6);
    glBegin(GL_POLYGON);
    glVertex2f(1030,60);
    glVertex2f(1370,60);
    glVertex2f(1370,95);
    glVertex2f(1030,95);
    glEnd();

    glColor3f(0.929412,0.733333,0.494118);
    glBegin(GL_POLYGON);
    glVertex2f(1000,-200);
    glVertex2f(1400,-200);
    glVertex2f(1400,50);
    glVertex2f(1000,50);
    glEnd();
}

void Building_4()
{

    float y_pos=0,y_pos_1=0;

    glPushMatrix();
    glTranslatef(110,0,0);
    for(int i=0; i<13; i++)
    {
        if(night==true && (i==1||i==10||i==7||i==6||i==3))
            glColor3f(0.984314,1,0);
        else
            glColor3f(0.266667+add_r,0.345098+add_g,0.580392+add_b);
        glBegin(GL_POLYGON);
        glVertex2f(962,528-y_pos_1);
        glVertex2f(999,528-y_pos_1);
        glVertex2f(999,483-y_pos_1);
        glVertex2f(962,483-y_pos_1);
        glEnd();
        glBegin(GL_POLYGON);
        glVertex2f(1048,528-y_pos_1);
        glVertex2f(1011,528-y_pos_1);
        glVertex2f(1011,483-y_pos_1);
        glVertex2f(1048,483-y_pos_1);
        glEnd();
        y_pos_1+=52;
    }
    glPopMatrix();

    for(int i=0; i<13; i++)
    {
        if(night==true && (i==2||i==11||i==4||i==8||i==7))
            glColor3f(0.984314,1,0);
        else
            glColor3f(0.266667+add_r,0.345098+add_g,0.580392+add_b);
        glBegin(GL_POLYGON);
        glVertex2f(962,528-y_pos);
        glVertex2f(999,528-y_pos);
        glVertex2f(999,483-y_pos);
        glVertex2f(962,483-y_pos);
        glEnd();
        glBegin(GL_POLYGON);
        glVertex2f(1048,528-y_pos);
        glVertex2f(1011,528-y_pos);
        glVertex2f(1011,483-y_pos);
        glVertex2f(1048,483-y_pos);
        glEnd();
        y_pos+=52.00;
    }
    glColor3f(0.929412,0.733333,0.494118);
    glBegin(GL_POLYGON);
    glVertex2f(1200,528);
    glVertex2f(1180,528);
    glVertex2f(1180,-150);
    glVertex2f(1200,-150);
    glEnd();

    glColor3f(0.0156863,0.054902,0.168627);
    glBegin(GL_POLYGON);
    glVertex2f(900,528);
    glVertex2f(950,528);
    glVertex2f(950,-150);
    glVertex2f(900,-150);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(955,528);
    glVertex2f(1055,528);
    glVertex2f(1055,-150);
    glVertex2f(955,-150);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(1065,528);
    glVertex2f(1165,528);
    glVertex2f(1165,-150);
    glVertex2f(1065,-150);
    glEnd();


    glColor3f(0.862745,0.886275,0.960784);
    glBegin(GL_POLYGON);
    glVertex2f(900,528);
    glVertex2f(1200,528);
    glVertex2f(1200,-150);
    glVertex2f(900,-150);
    glEnd();
}

void Building_5()
{
    float y_pos=0;

    for (int i=0; i<10; i++)
    {
        if(night==true&&(i==0||i==3||i==5||i==6||i==9))
            glColor3f(0.984314,1,0);
        else
            glColor3f(0.266667+add_r,0.345098+add_g,0.580392+add_b);
        glBegin(GL_POLYGON);
        glVertex2f(830,325-y_pos);
        glVertex2f(950,325-y_pos);
        glVertex2f(950,290-y_pos);
        glVertex2f(830,290-y_pos);
        glEnd();
        y_pos+=40;
    }

    glColor3f(0.0156863,0.054902,0.168627);
    glBegin(GL_POLYGON);
    glVertex2f(820,328);
    glVertex2f(1000,328);
    glVertex2f(1000,348);
    glVertex2f(820,348);
    glEnd();

    glColor3f(0.941176,0.435294,0.282353);
    glBegin(GL_POLYGON);
    glVertex2f(820,328);
    glVertex2f(1000,328);
    glVertex2f(1000,-100);
    glVertex2f(820,-100);
    glEnd();
}
void Building_6()
{

    glColor3f(0.309804+add_r,0.490196+add_g,0.760784+add_b);
    glBegin(GL_POLYGON);
    glVertex2f(1280,428);
    glVertex2f(1360,428);
    glVertex2f(1360,490);
    glVertex2f(1280,490);
    glEnd();

    float x_pos=0;
    glColor3f(0.541176+add_r,0.705882+add_g,0.831373+add_b);
    for(int i=0; i<9; i++)
    {
        glBegin(GL_POLYGON);
        glVertex2f(1285+x_pos,328);
        glVertex2f(1290+x_pos,328);
        glVertex2f(1290+x_pos,400);
        glVertex2f(1285+x_pos,400);
        glEnd();
        x_pos+=10;
    }

    glColor3f(0.156863+add_r,0.345098+add_g,0.490196+add_b);
    glBegin(GL_POLYGON);
    glVertex2f(1280,328);
    glVertex2f(1375,328);
    glVertex2f(1375,400);
    glVertex2f(1280,400);
    glEnd();
    float y_pos=0;
    //glass
    for (int i=0; i<6; i++)
    {
        if(night==true)
            glColor3f(0.984314,1,0);
        else
            glColor3f(0.337255+add_r,0.662745+add_g,0.909804+add_b);
        glBegin(GL_POLYGON);
        glVertex2f(1210,318-y_pos);
        glVertex2f(1270,318-y_pos);
        glVertex2f(1270,278-y_pos);
        glVertex2f(1210,278-y_pos);
        glEnd();
        y_pos+=50;
    }
    glColor3f(0.156863+add_r,0.345098+add_g,0.490196+add_b);
    glBegin(GL_POLYGON);
    glVertex2f(1000,328);
    glVertex2f(1280,328);
    glVertex2f(1280,-100);
    glVertex2f(1000,-100);
    glEnd();

    float y_pos_1=0;
    //glass
    for(int i=0; i<6; i++)
    {
        if(night==true&&(i==2||i==4||i==5))
            glColor3f(0.984314,1,0);
        else
            glColor3f(0.490196+add_r,0.627451+add_g,0.729412+add_b);
        glBegin(GL_POLYGON);
        glVertex2f(1285,318-y_pos_1);
        glVertex2f(1370,318-y_pos_1);
        glVertex2f(1370,278-y_pos_1);
        glVertex2f(1285,278-y_pos_1);
        glEnd();
        y_pos_1+=50;
    }
    glColor3f(0.109804+add_r,0.223529+add_g,0.309804+add_b);
    glBegin(GL_POLYGON);
    glVertex2f(1280,328);
    glVertex2f(1375,328);
    glVertex2f(1375,-100);
    glVertex2f(1280,-100);
    glEnd();

    glColor3f(0.309804+add_r,0.490196+add_g,0.760784+add_b);
    glBegin(GL_POLYGON);
    glVertex2f(1000,428);
    glVertex2f(1380,428);
    glVertex2f(1380,-100);
    glVertex2f(1000,-100);
    glEnd();
}
void Building_7()
{

    float x_pos=0,y_pos=0;
    for(int y =0; y<16; y++)
    {
        for(int x=0; x<5; x++)
        {
            if(night==true&&((y==2&&(x==3||x==2))||(y==4&&(x==1||x==4))||(y==5&&x==0)||(y==1&&(x==0||x==2))||(y==6&&x==2)||(y==7&&(x==0||x==4))
                             ||(y==8&&(x==0||x==4))||(y==11)||y==13||(y==15&&(x==0||x==2))))
                glColor3f(0.984314,1,0);
            else
                glColor3f(0.568627+add_r,0.180392+add_g,0.121569+add_b);
            glBegin(GL_POLYGON);
            glVertex2f(1710+x_pos,528-y_pos);
            glVertex2f(1742+x_pos,528-y_pos);
            glVertex2f(1742+x_pos,498-y_pos);
            glVertex2f(1710+x_pos,498-y_pos);
            glEnd();
            x_pos+=40;
        }
        x_pos=0;
        y_pos+=40;
    }

    glColor3f(0.580392+add_r,0.545098+add_g,0.282353+add_b);
    glBegin(GL_POLYGON);
    glVertex2f(1700,-130);
    glVertex2f(1900,-130);
    glVertex2f(1900,528);
    glVertex2f(1700,528);
    glEnd();
}

void Building_8()
{
    float y_pos=0;
    for(int x=0; x<10; x++)
    {
        glColor3f(0.74902+add_r,0.588235+add_g,0.427451+add_b);
        glBegin(GL_POLYGON);
        glVertex2f(1643,420-y_pos);
        glVertex2f(1700,420-y_pos);
        glVertex2f(1700,427-y_pos);
        glVertex2f(1643,427-y_pos);
        glEnd();
        glColor3f(0.431373+add_r,0.364706+add_g,0.329412+add_b);
        glBegin(GL_POLYGON);
        glVertex2f(1643,420-y_pos);
        glVertex2f(1700,420-y_pos);
        glVertex2f(1700,417-y_pos);
        glVertex2f(1643,417-y_pos);
        glEnd();

        y_pos+=50;
    }

    glColor3f(0.0509804+add_r,0,0.219608+add_b);
    glBegin(GL_POLYGON);
    glVertex2f(1635,-80);
    glVertex2f(1645,-80);
    glVertex2f(1645,420);
    glVertex2f(1635,420);
    glEnd();

    glColor3f(0.568627+add_r,0.247059+add_g,0.0980392+add_b);
    glBegin(GL_POLYGON);
    glVertex2f(1600,-80);
    glVertex2f(1635,-80);
    glVertex2f(1635,420);
    glVertex2f(1600,420);
    glEnd();


    glColor3f(0.811765+add_r,0.333333+add_g,0.113725+add_b);
    glBegin(GL_POLYGON);
    glVertex2f(1600,-80);
    glVertex2f(1700,-80);
    glVertex2f(1700,420);
    glVertex2f(1600,420);
    glEnd();

}
void Building_9()
{
    if(night||evening)
    {
        float point_x=0;
        glPointSize(4);
        glColor3f(0.152941,0.729412,0.768627);
        glBegin(GL_POINTS);
        for(int i=0; i<11; i++)
        {
            glVertex2f(660+point_x,30);
            point_x+=6;
        }
        glVertex2f(560,140);
        glVertex2f(590,120);
        glVertex2f(575,100);
        glVertex2f(560,80);
        glVertex2f(670,180);
        glVertex2f(680,180);
        glVertex2f(690,180);
        glVertex2f(700,160);
        glVertex2f(710,160);
        glVertex2f(720,160);
        glVertex2f(730,160);
        glVertex2f(700,140);
        glVertex2f(690,140);
        glVertex2f(670,120);
        glVertex2f(730,100);
        glVertex2f(670,80);
        glVertex2f(710,80);
        glVertex2f(720,80);
        glVertex2f(730,80);
        glVertex2f(570,80);
        glVertex2f(610,80);
        glVertex2f(570,60);
        glVertex2f(580,60);
        glVertex2f(590,60);
        glVertex2f(600,60);
        glVertex2f(610,60);
        glVertex2f(740,100);
        glVertex2f(780,100);
        glVertex2f(740,150);
        glVertex2f(780,50);
        glVertex2f(790,50);
        glVertex2f(800,50);
        glVertex2f(800,150);
        glVertex2f(820,200);
        glVertex2f(810,200);
        glVertex2f(800,200);
        glVertex2f(810,250);
        glVertex2f(1500,200);
        glVertex2f(1450,200);
        glVertex2f(1400,200);
        glVertex2f(1390,200);
        glVertex2f(1410,200);
        glVertex2f(1420,200);
        glVertex2f(1400,250);
        glVertex2f(1390,300);
        glVertex2f(1530,250);
        glVertex2f(1520,250);
        glVertex2f(1510,250);
        glVertex2f(1500,250);
        glVertex2f(1450,250);
        glVertex2f(1440,250);
        glVertex2f(1500,230);
        glVertex2f(1480,230);
        glVertex2f(1480,210);
        glVertex2f(1490,210);
        glVertex2f(1470,210);
        glVertex2f(1430,180);
        glVertex2f(1440,180);
        glVertex2f(1380,180);
        glVertex2f(1470,180);
        glVertex2f(1460,180);
        glVertex2f(1530,180);
        glVertex2f(1510,180);
        glVertex2f(1430,160);
        glVertex2f(1440,160);
        glVertex2f(1450,160);
        glVertex2f(1460,160);
        glVertex2f(1530,140);
        glVertex2f(1520,140);
        glVertex2f(1510,140);
        glVertex2f(1500,140);
        glVertex2f(1430,140);
        glVertex2f(1420,140);
        glVertex2f(1390,100);
        glVertex2f(1490,100);
        glVertex2f(1480,100);
        glVertex2f(1470,100);
        glVertex2f(1460,100);
        glVertex2f(1410,60);
        glVertex2f(1420,60);
        glVertex2f(1430,60);
        glVertex2f(1510,60);
        glVertex2f(1440,30);
        glVertex2f(1450,30);
        glVertex2f(1460,30);


        glEnd();

    }



    if(evening)
        glColor3f(0.00784314,0.25098,0.639216);
    else if(night)
        glColor3f(0,0,0.529412);
    else
        glColor3f(0.454902,0.686275,0.94902);
    glBegin(GL_POLYGON);
    glVertex2f(550,150);
    glVertex2f(600,150);
    glVertex2f(600,-10);
    glVertex2f(550,-10);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(600,100);
    glVertex2f(650,100);
    glVertex2f(650,-10);
    glVertex2f(600,-10);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(650,180);
    glVertex2f(655,180);
    glVertex2f(655,-10);
    glVertex2f(650,-10);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(655,190);
    glVertex2f(670,190);
    glVertex2f(670,-10);
    glVertex2f(655,-10);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(670,250);
    glVertex2f(700,250);
    glVertex2f(700,-10);
    glVertex2f(670,-10);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(700,200);
    glVertex2f(750,200);
    glVertex2f(750,-10);
    glVertex2f(700,-10);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(750,170);
    glVertex2f(780,170);
    glVertex2f(780,-10);
    glVertex2f(750,-10);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(780,280);
    glVertex2f(820,280);
    glVertex2f(820,-10);
    glVertex2f(780,-10);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(1350,320);
    glVertex2f(1410,320);
    glVertex2f(1410,-10);
    glVertex2f(1350,-10);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(1350,320);
    glVertex2f(1410,320);
    glVertex2f(1410,-10);
    glVertex2f(1350,-10);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(1410,260);
    glVertex2f(1470,260);
    glVertex2f(1470,-10);
    glVertex2f(1410,-10);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(1470,290);
    glVertex2f(1510,290);
    glVertex2f(1510,-10);
    glVertex2f(1470,-10);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(1510,320);
    glVertex2f(1550,320);
    glVertex2f(1550,-10);
    glVertex2f(1510,-10);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(1550,380);
    glVertex2f(1650,380);
    glVertex2f(1650,-10);
    glVertex2f(1550,-10);
    glEnd();
}
//////////////////////////
////////Slab//////////////
void slab_1()
{
    glColor3f(0.309804+add_r,0.368627+add_g,0.333333+add_b);
    glBegin(GL_POLYGON);
    glVertex2f(0,50);
    glVertex2f(650,50);
    glVertex2f(540,-250);
    glVertex2f(0,-250);
    glEnd();
}
void slab_2()
{
    glColor3f(0.309804+add_r,0.368627+add_g,0.333333+add_b);
    glBegin(GL_QUADS);
    glVertex2f(730,50);
    glVertex2f(1100,50);
    glVertex2f(1590,-250);
    glVertex2f(850,-250);
    glEnd();
}
void slab_3()
{
    glColor3f(0.309804+add_r,0.368627+add_g,0.333333+add_b);
    glBegin(GL_QUADS);
    glVertex2f(1300,50);
    glVertex2f(1900,50);
    glVertex2f(1900,-250);
    glVertex2f(1900,-250);
    glEnd();
}
///////road//////
void road()
{
    glColor3f(1,1,1);
    float x_r_p=0,y_r_p=0;
    for(int i=0; i<6; i++)
    {
        glBegin(GL_POLYGON);
        glVertex2f(0+x_r_p,-346);
        glVertex2f(250+x_r_p,-346);
        glVertex2f(250+x_r_p,-352);
        glVertex2f(0+x_r_p,-352);
        glEnd();
        x_r_p+=350;
    }
    for(int i=0; i<2; i++)
    {
        glBegin(GL_POLYGON);
        glVertex2f(685,-250+y_r_p);
        glVertex2f(691,-250+y_r_p);
        glVertex2f(691,-100+y_r_p);
        glVertex2f(685,-100+y_r_p);
        glEnd();
        y_r_p+=180;
    }

    glColor3f(0.258824,0.258824,0.258824);
    glBegin(GL_POLYGON);
    glVertex2f(0,-10);
    glVertex2f(1900,-10);
    glVertex2f(1900,-528);
    glVertex2f(0,-528);
    glEnd();
}
////tree///
void tree()
{
    glColor3f(0.337255,0.54902,0.152941);
    glBegin(GL_TRIANGLES);
    glVertex2f(50,-40);
    glVertex2f(25,-160);
    glVertex2f(50,-170);
    glEnd();
    glColor3f(0.188235,0.329412,0.0627451);
    glBegin(GL_TRIANGLES);
    glVertex2f(50,-40);
    glVertex2f(75,-160);
    glVertex2f(50,-170);
    glEnd();
    glColor3f(0.180392,0.0627451,0.0627451);
    glBegin(GL_POLYGON);
    glVertex2f(46,-167);
    glVertex2f(56,-167);
    glVertex2f(56,-180);
    glVertex2f(46,-180);
    glEnd();
}
void tree_1()
{
    glColor3f(0.403922,0.541176,0.227451);
    glBegin(GL_POLYGON);
    glVertex2f(840,-40);
    glVertex2f(910,-40);
    glVertex2f(910,-100);
    glVertex2f(840,-100);
    glEnd();

    glColor3f(0.231373,0.341176,0.0862745);
    glBegin(GL_POLYGON);
    glVertex2f(800,-70);
    glVertex2f(860,-70);
    glVertex2f(860,-120);
    glVertex2f(800,-120);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(890,-70);
    glVertex2f(950,-70);
    glVertex2f(950,-120);
    glVertex2f(890,-120);
    glEnd();

    glColor3f(0.501961,0.278431,0.0980392);
    glBegin(GL_POLYGON);
    glVertex2f(870,-180);
    glVertex2f(880,-180);
    glVertex2f(880,-100);
    glVertex2f(870,-100);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(840,-100);
    glVertex2f(850,-100);
    glVertex2f(870,-140);
    glVertex2f(880,-140);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(900,-100);
    glVertex2f(910,-100);
    glVertex2f(870,-137);
    glVertex2f(880,-137);
    glEnd();
}
////////car///////
float car_1_xpos=0;

void Car_1()
{
    if(night==true)
        glColor3f(0.984314,1,0);
    else
        glColor3f(0.537255,0.537255,0.533333);
     glBegin(GL_QUADS);
    glVertex2f(450,-250);
    glVertex2f(440,-250);
    glVertex2f(440,-230);
    glVertex2f(450,-230);
    glEnd();

   glColor3f(0.686275+add_r,0.839216+add_g,0.509804+add_b);
   circle(200,-180,60);
    glColor3f(0.129412+add_r,0.129412+add_g,0.129412+add_b);
    glBegin(GL_QUADS);
    glVertex2f(450,-270);
    glVertex2f(440,-270);
    glVertex2f(440,-260);
    glVertex2f(450,-260);
    glEnd();

    glColor3f(0.129412+add_r,0.129412+add_g,0.129412+add_b);
    circle(170,-280,35);
    glColor3f(0.129412,0.129412,0.129412);
    circle(400,-280,35);
    glColor3f(0.2,0.2,0.2);
    glBegin(GL_POLYGON);
    glVertex2f(100,-270);
    glVertex2f(130,-280);
    glVertex2f(420,-280);
    glVertex2f(450,-270);
    glEnd();
    glColor3f(0.34902+add_r,0.431373+add_g,0.431373+add_b);
    glLineWidth(5);
    glBegin(GL_LINES);
    glVertex2f(300,-270);
    glVertex2f(300,-100);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(300,-100);
    glVertex2f(100,-100);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(100,-100);
    glVertex2f(100,-270);
    glEnd();

    glColor3f(0.603922+add_r,0.721569+add_g,0.705882+add_b);
    glBegin(GL_POLYGON);
    glVertex2f(300,-270);
    glVertex2f(300,-100);
    glVertex2f(100,-100);
    glVertex2f(100,-270);
    glEnd();

    glColor3f(0.227451+add_r,0.231373+add_g,0.231373+add_b);
    glBegin(GL_POLYGON);
    glVertex2f(305,-155);
    glVertex2f(345,-155);
    glVertex2f(395,-205);
    glVertex2f(305,-205);
    glEnd();

    glColor3f(0.603922+add_r,0.721569+add_g,0.705882+add_b);
    glBegin(GL_POLYGON);
    glVertex2f(300,-150);
    glVertex2f(350,-150);
    glVertex2f(400,-200);
    glVertex2f(450,-230);
    glVertex2f(450,-270);
    glVertex2f(300,-270);
    glEnd();

    glColor3f(0.34902+add_r,0.431373+add_g,0.431373+add_b);
    circle(310,-150,36);
}
void Car_1_move(int)
{
    glutTimerFunc(1000/90,Car_1_move,1);
    if(car_1_xpos<=1950)
        car_1_xpos+=3;
    else
        car_1_xpos=-450;
    glutPostRedisplay();
}

void Car_2()
{
    if(night==true)
        glColor3f(0.984314,1,0);
    else
        glColor3f(0.537255,0.537255,0.533333);
     glBegin(GL_QUADS);
    glVertex2f(450,-250);
    glVertex2f(440,-250);
    glVertex2f(440,-230);
    glVertex2f(450,-230);
    glEnd();

   glColor3f(0.686275+add_r,0.839216+add_g,0.509804+add_b);
   circle(200,-180,60);
    glColor3f(0.129412+add_r,0.129412+add_g,0.129412+add_b);
    glBegin(GL_QUADS);
    glVertex2f(450,-270);
    glVertex2f(440,-270);
    glVertex2f(440,-260);
    glVertex2f(450,-260);
    glEnd();

    glColor3f(0.129412+add_r,0.129412+add_g,0.129412+add_b);
    circle(170,-280,35);
    glColor3f(0.129412,0.129412,0.129412);
    circle(400,-280,35);
    glColor3f(0.2,0.2,0.2);
    glBegin(GL_POLYGON);
    glVertex2f(100,-270);
    glVertex2f(130,-280);
    glVertex2f(420,-280);
    glVertex2f(450,-270);
    glEnd();
    glColor3f(0.34902+add_r,0.431373+add_g,0.431373+add_b);
    glLineWidth(5);
    glBegin(GL_LINES);
    glVertex2f(300,-270);
    glVertex2f(300,-100);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(300,-100);
    glVertex2f(100,-100);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(100,-100);
    glVertex2f(100,-270);
    glEnd();

    glColor3f(0.878431+add_r,0.835294+add_g,0.00784314+add_b);
    glBegin(GL_POLYGON);
    glVertex2f(300,-270);
    glVertex2f(300,-100);
    glVertex2f(100,-100);
    glVertex2f(100,-270);
    glEnd();

    glColor3f(0.227451+add_r,0.231373+add_g,0.231373+add_b);
    glBegin(GL_POLYGON);
    glVertex2f(305,-155);
    glVertex2f(345,-155);
    glVertex2f(395,-205);
    glVertex2f(305,-205);
    glEnd();

    glColor3f(0.878431+add_r,0.835294+add_g,0.00784314+add_b);
    glBegin(GL_POLYGON);
    glVertex2f(300,-150);
    glVertex2f(350,-150);
    glVertex2f(400,-200);
    glVertex2f(450,-230);
    glVertex2f(450,-270);
    glVertex2f(300,-270);
    glEnd();

    glColor3f(0.34902+add_r,0.431373+add_g,0.431373+add_b);
    circle(310,-150,36);
}
float car_2_xpos=10;
void Car_2_perfectPlace()
{
    glPushMatrix();
    glTranslatef(0,-110,0);
    Car_2();
    glPopMatrix();
}
void car_2_move(int)
{
        glutTimerFunc(1000/90,car_2_move,1);
        if(car_2_xpos<=1950)
            car_2_xpos+=1.5;
        else
            car_2_xpos=-450;
        glutPostRedisplay();
}
void reshape(int w,int h)
{
    glViewport(0,0,(GLsizei)w,(GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,1900,-528,528);
    glMatrixMode(GL_MODELVIEW);
}

void init()
{
    glClearColor(0,0,0,1.0);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

}
void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'd':
    {
        night=false;
        evening=false;
        sun_y_position=80;
        sky_r=0.3019;
        sky_g=0.9538;
        sky_b=1.0;
        sun_color_g=1.0;
        add_r=0;
        add_g=0;
        add_b=0;
        glClear(GL_COLOR_BUFFER_BIT);
        glutPostRedisplay();
        break;
    }
    case 'e':
    {
        night=false;
        evening=true;
        sun_y_position=-100;
        sun_color_g=.9;
        add_r=-0.0588235;
        add_g=-0.0588235;
        add_b=-0.0588235;
        glutPostRedisplay();
        break;
    }
    case 'n':
    {
        night = true;
        evening=false;
        sky_r=0;
        sky_g=0.0823529;
        sky_b=0.278431;
        add_r=-0.117647;
        add_g=-0.117647;
        add_b=-0.117647;
        glutPostRedisplay();
        break;
    }
    }
}
void Display()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    ///car///
    glPushMatrix();
    glTranslatef(car_2_xpos,0,0);
    Car_2_perfectPlace();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(car_1_xpos,0,0);
    Car_1();
    glPopMatrix();
    ///buildings///
    glPushMatrix();
    glTranslatef(-350,0,0);
    tree_1();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-20,0,0);
    tree_1();
    glPopMatrix();
    float tree_1_x_pos=0;
    for(int i=0; i<6; i++)
    {
        glPushMatrix();
        glTranslatef(tree_1_x_pos,0,0);
        tree();
        glPopMatrix();
        tree_1_x_pos+=70;
    }
    tree_1_x_pos=0;
    glPushMatrix();
    glTranslatef(2000,0,0);
    glScalef(-.8,0.8,0);
    for(int i=0; i<5; i++)
    {
        glPushMatrix();
        glTranslatef(tree_1_x_pos,0,0);
        tree();
        glPopMatrix();
        tree_1_x_pos+=70;
    }
    glPopMatrix();

    Building_1();

    glPushMatrix();
    glScalef(0.8,0.8,0);
    glTranslatef(-180,40,0);
    tree_1();
    glPopMatrix();

    Building_2();

    glPushMatrix();
    glScalef(0.6,0.6,0);
    glTranslatef(90,90,0);
    tree_1();
    glPopMatrix();

    Building_3();
    Building_4();
    glPushMatrix();
    glScalef(0.8,0.8,0);
    glTranslatef(150,40,0);
    tree_1();
    glPopMatrix();
    Building_5();

    Building_6();
    glPushMatrix();
    glScalef(0.6,0.6,0);
    glTranslatef(450,90,0);
    tree_1();
    glPopMatrix();
    Building_7();
    Building_8();
    glPushMatrix();
    glTranslatef(720,50,0);
    Building_5();
    glPopMatrix();
    Building_9();
    ///Slabs//
    slab_1();
    slab_2();
    slab_3();
    ///road///
    road();
    ///Clouds//



    glPushMatrix();
    glTranslatef(Cloud_2_x_pos,0,0);
    Cloud_2();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(Cloud_1_x_pos,0,0);
    Cloud_1();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(Cloud_1cpy_x_pos,0,0);
    Cloud_1cpy();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(Cloud_3_x_pos,0,0);
    Cloud_3();
    glPopMatrix();

    ///Sun&Moon///
    if(night == false)
    {
        glPushMatrix();
        glTranslatef(0.0,sun_y_position,0.0);
        Sun();
        glPopMatrix();
    }
    else if(night = true)
    {
        glPushMatrix();
        glTranslatef(0.0,80,0.0);
        Moon();
        glPopMatrix();
    }


    ///Sky//
    Sky();
    glFlush();
    glutSwapBuffers();
}
void TimerHolder(int)
{
    cloud_movement_timer(0);
    Car_1_move(0);
    car_2_move(0);
}
int main(int argc,char ** argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE|GLUT_DEPTH);
    glutInitWindowSize(1900,1060);
    glutInitWindowPosition(0,0);
    glutCreateWindow("City view");
    glutReshapeFunc(reshape);
    glutDisplayFunc(Display);
    glutKeyboardFunc(keyboard);
    init();
    glutIdleFunc(Display);
    glutTimerFunc(0,TimerHolder,0);
    glutMainLoop();
}
