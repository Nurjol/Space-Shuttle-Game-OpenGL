//
//  15th week.cpp
//  space shuttle
//
//  Created by Nurjol Badyelkhan on 2021/12/03.
//

#include<GL/glew.h>
#include <GL/glut.h>
#include <GL/freeglut.h>
#include <stdlib.h>
#include <math.h>
#include<stdio.h>
#include<string.h>
#include<vector>
#include<execution>
#include "bmpfuncs.h"
#include "objet.hpp"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

#define PI 3.14159265
double theta =45;
double phi =  45;
int radius =30;
double upVector = cos(phi*PI/180);

double objx=3,objy=-5,objz=3;



int direction=0; //direction

double eyex,eyey,eyez;

//environment mapping set variable
GLuint g_nCubeTex;

GLuint* texMoon = new GLuint();
GLuint* texEarth = new GLuint();
GLuint texDock;

GLUquadricObj* qobj = gluNewQuadric();
GLUquadricObj* moon = gluNewQuadric();
GLUquadricObj* dock = gluNewQuadric();

unsigned char selector =4;

//function definitions:
void init(void);
void resize(int,int);
void draw(void);
void draw_earth(void);
void draw_moon(void);
void draw_skyBox(void);
void draw_string(void*, const char*,float,float,float,float,float);

void drawShuttle(void);
void drawDock(void);

void mouse(int,int,int,int);
void mouseWheel(int but,int dir,int x, int y);
void keyboard(unsigned char, int ,int);
void specialkeyboard(int,int,int);
void idle(void);

void printInstruction(void);
void light_default(void);
void setDefault(void);

void sphereTextureMapping(void);
void moonTextureMapping(void);
void earthTextureMapping(void);
void environmentMapSetting(void);
    void dockTextureMapping(void);

typedef unsigned char uchar;



int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(WINDOW_WIDTH,WINDOW_HEIGHT);
    glutInitWindowPosition(WINDOW_WIDTH/2,WINDOW_HEIGHT/2);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("mighty nurjol");
    init();
    
    gluQuadricDrawStyle(qobj, GLU_FILL);
    gluQuadricNormals(qobj, GLU_SMOOTH);
    gluQuadricDrawStyle(moon, GLU_FILL);
    gluQuadricNormals(moon, GLU_SMOOTH);
    
    glutIdleFunc(idle);
    glutDisplayFunc(draw);
    
    glutKeyboardFunc(keyboard);
    glutSpecialFunc( specialkeyboard);
    glutMouseFunc(mouse);
   // glutMouseWheelFunc(mouseWheel);
    
    glutMainLoop();
    return 0;
}
void init(void)
{
    printf("init func called\n");
    glClearColor(0.0f,0.0f,0.0f,0.0f);
    glColor3f(1.0f,1.0f,1.0f);
    glutReshapeFunc(resize);
    
    light_default();
    
    gluQuadricTexture(dock, GL_TRUE);
    dockTextureMapping();
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glEnable(GL_TEXTURE_2D);
  
    
    gluQuadricTexture(moon, GL_TRUE);
    moonTextureMapping();
    earthTextureMapping();
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glEnable(GL_TEXTURE_2D);

  
    
    gluQuadricTexture(qobj, GL_TRUE);
    environmentMapSetting();
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glEnable(GL_TEXTURE_2D);
    
    glFrontFace(GL_CCW);
    glEnable(GL_DEPTH_TEST);
    
}


void setDefault(){
    radius = 18;
    theta = 45.0;
    phi = 45.0;

    selector = 4;
}
void idle(void){
    float sum = 0.5;
    if(direction ==1){
        objx-=sum;
        objz-=sum;
    }
    else if(direction==2){
        objx+=sum;
        objz-=sum;
        
    }
    else if(direction==3){
        
            objx+=sum;
            objz+=sum;
    }
    else if(direction==4){
        objx-=sum;
        objz+=sum;
        
        
    }
    glutPostRedisplay();
    
}


void draw(void)
{
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glEnable(GL_DEPTH_TEST);
    eyex = radius *sin(theta*PI/180)*cos(phi*PI/180);
    eyey = radius *sin(phi*PI/180);
    eyez = radius *cos(theta*PI/180)*sin(phi*PI/180);
    upVector = cos(phi*PI/180);
    gluLookAt( eyex,eyey,eyez,0,0,0,0,upVector,0);
   
   
//    glDisable(GL_LIGHT1);
  
   
        glPushMatrix();
        glTranslatef(objx, objy,objz);
        drawShuttle();
        glPopMatrix();
    glPushMatrix();
    glTranslatef(-10, 2, -10);
    draw_earth();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(-10, 4, 4);
    draw_moon();
    glPopMatrix();
    glPushMatrix();

    glTranslatef(10, -6.5, 10);
        glRotatef(90, 1, 0, 0);
    drawDock();
    
    glPopMatrix();
    glPushMatrix();
    draw_skyBox();
    glPopMatrix();
  

    glutSwapBuffers();
}

void resize(int width, int height)
{
   const float ar = (float) width / (float) height;
   glViewport(0, 0, width, height);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluPerspective(45,ar,1,500);
   
   glMatrixMode(GL_MODELVIEW);
   
}
void mouse(int button,int state, int x,int y){
}

void mouseWheel(int but,int dir, int x,int y){
    if(dir>0)
    {
        if(radius>2){radius--;}
    }
    else{
        if(radius<100){radius++;}
    }
    glutPostRedisplay();
}

void light_default(){
    glClearColor(0, 0, 0, 0.0f);
    
    
    GLfloat ambientLight[] = {0.2f, 0.2f, 0.2f, 1.0f};
    GLfloat diffuseLight[] = {0.7f, 0.7f, 0.7f, 1.0f};
    GLfloat specularLight[] = {1.0f, 1.0f, 1.0f, 1.0f};
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
    
    
    GLfloat ambientMaterial[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    GLfloat diffuseMaterial[] = { 1.0f, 0.0f, 0.0f, 1.0f };
    GLfloat specularMaterial[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambientMaterial);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseMaterial);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specularMaterial);
    glMaterialf(GL_FRONT,GL_SHININESS,60);
    
     glEnable(GL_COLOR_MATERIAL);
     glColorMaterial(GL_FRONT,GL_AMBIENT_AND_DIFFUSE);
    
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

}


void keyboard(unsigned char key, int x, int y){
    
    switch (key) {
        case 'z':
            if(radius>2){radius--;}
            printf("z preesed\n");
            break;
        case 'w':
            printf("up key pressed\ntheta:%d phi: %d\n",theta,phi);
            phi +=5;
            if(abs((int)phi)%360 ==0) phi=0.0;
            break;
        case 's':
            printf("down key pressed\ntheta:%d phi: %d\n",theta,phi);
            phi -=5;
            if(abs((int)phi)%360 ==0) phi=0.0;
            break;
        case 'a':
       
            printf("left key pressed\ntheta:%d phi: %d\n",theta,phi);
            theta +=2;
            if(theta >= 360) theta =0;
            break;
        case 'd':
            printf("right key pressed\ntheta:%d phi: %d\n",theta,phi);
            theta -=2;
            if(theta <=-360) theta =0;
            break;
        case 'x':
            if(radius<100){radius++;}
            printf("x preesed\n");
            break;
        default:
            printf("%c pressed\n",key);
            break;
    }
    glutPostRedisplay();
}


    
void specialkeyboard(int key, int x1, int y1){
 
    if(key == GLUT_KEY_RIGHT){
        direction = 2;
    }
    else if(key == GLUT_KEY_LEFT){
        direction = 4;
       
    }
    else if(key == GLUT_KEY_UP){
        direction = 1;
    
    }
    else if(key == GLUT_KEY_DOWN){
        direction = 3;
    }
    glutPostRedisplay();
}
void main_menu_function(int option){
    if(option == 1){
        setDefault();
        draw();
       
    }
    else if (option == 999){
        printf("you selected quit\n");
        exit(0);
    }
    printf("main menu selected\n");
}


//void sub_menu_function(int option){
//    //glClear(GL_COLOR_BUFFER_BIT);
//    if(option == 1){
//        lightMode = 0;
//        selector = 1;
//    }
//    else if(option == 2){
//        lightMode = 0;
//        selector = 2;
//    }
//    else if(option == 3){
//        lightMode = 0;
//        selector = 3;
//    }
//    else if (option ==4){
//        lightMode = 0;
//        selector = 4;
//    }
//    printf("sub menu %d has selected\n",option);
//    glutPostRedisplay();
//}



void draw_string(void* font, const char* str,float x_position,float y_position,float red,float green ,float blue){
    glPushAttrib(GL_LIGHTING_BIT);
    glDisable(GL_LIGHTING);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(-10, 10, -10, 10);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glColor3f(red, green, blue);
    glRasterPos3f(x_position, y_position, 0);
    for(unsigned int i=0;i<strlen(str);i++){
        glutBitmapCharacter(font, str[i]);
    }
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopAttrib();
    
}


void draw_earth(){
    glDisable(GL_TEXTURE_GEN_S);
    glDisable(GL_TEXTURE_GEN_T);
    glDisable(GL_TEXTURE_GEN_R);
    glDisable(GL_TEXTURE_CUBE_MAP);

    glColor3f(1.0,1.0,1.0);
    glBindTexture(GL_TEXTURE_2D, *texEarth);
    gluSphere(moon, 1.5, 50, 50);
    
}

void draw_moon(){
    glDisable(GL_TEXTURE_GEN_S);
    glDisable(GL_TEXTURE_GEN_T);
    glDisable(GL_TEXTURE_GEN_R);
    glDisable(GL_TEXTURE_CUBE_MAP);

    glRotatef(-90, 1, 0, 0);
    glColor3f(1.0,1.0,1.0);
    glBindTexture(GL_TEXTURE_2D, *texMoon);
    gluSphere(moon, 3, 50, 50);
    

    
}
void draw_skyBox(){
    glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
   //glDisable(GL_LIGHTING);
    glEnable(GL_TEXTURE_CUBE_MAP);
    glBindTexture(GL_TEXTURE_CUBE_MAP,g_nCubeTex);
    float g_nSkySize = 50.0f;
    
    glBegin(GL_QUADS);
    //px
    glTexCoord3d(1.0, -1.0, -1.0); glVertex3f(g_nSkySize, -g_nSkySize, -g_nSkySize);
    glTexCoord3d(1.0, -1.0, 1.0); glVertex3f(g_nSkySize, -g_nSkySize, g_nSkySize);
    glTexCoord3d(1.0, 1.0, 1.0); glVertex3f(g_nSkySize, g_nSkySize, g_nSkySize);
    glTexCoord3d(1.0, 1.0, -1.0); glVertex3f(g_nSkySize, g_nSkySize, -g_nSkySize);
    
    //nx
    glTexCoord3d(-1.0, -1.0, -1.0); glVertex3f(-g_nSkySize, -g_nSkySize, -g_nSkySize);
    glTexCoord3d(-1.0, -1.0, 1.0); glVertex3f(-g_nSkySize, -g_nSkySize, g_nSkySize);
    glTexCoord3d(-1.0, 1.0, 1.0); glVertex3f(-g_nSkySize, g_nSkySize, g_nSkySize);
    glTexCoord3d(-1.0, 1.0, -1.0); glVertex3f(-g_nSkySize, g_nSkySize, -g_nSkySize);
    
    
    //py
    glTexCoord3d(1.0, 1.0, 1.0); glVertex3f(g_nSkySize, g_nSkySize, g_nSkySize);
    glTexCoord3d(-1.0, 1.0, 1.0); glVertex3f(-g_nSkySize, g_nSkySize, g_nSkySize);
    glTexCoord3d(-1.0, 1.0, -1.0); glVertex3f(-g_nSkySize, g_nSkySize, -g_nSkySize);
    glTexCoord3d(1.0, 1.0, -1.0); glVertex3f(g_nSkySize, g_nSkySize, -g_nSkySize);
    
    //ny
    glTexCoord3d(1.0, -1.0, 1.0); glVertex3f(g_nSkySize, -g_nSkySize, g_nSkySize);
    glTexCoord3d(-1.0, -1.0, 1.0); glVertex3f(-g_nSkySize, -g_nSkySize, g_nSkySize);
    glTexCoord3d(-1.0, -1.0, -1.0); glVertex3f(-g_nSkySize, -g_nSkySize, -g_nSkySize);
    glTexCoord3d(1.0, -1.0, -1.0); glVertex3f(g_nSkySize, -g_nSkySize, -g_nSkySize);
    
    //pz
    glTexCoord3d(1.0, -1.0, 1.0); glVertex3f(g_nSkySize, -g_nSkySize, g_nSkySize);
    glTexCoord3d(-1.0, -1.0, 1.0); glVertex3f(-g_nSkySize, -g_nSkySize, g_nSkySize);
    glTexCoord3d(-1.0, 1.0, 1.0); glVertex3f(-g_nSkySize, g_nSkySize, g_nSkySize);
    glTexCoord3d(1.0, 1.0, 1.0); glVertex3f(g_nSkySize, g_nSkySize, g_nSkySize);
    
    //nz
    glTexCoord3d(1.0, -1.0, -1.0); glVertex3f(g_nSkySize, -g_nSkySize, -g_nSkySize);
    glTexCoord3d(-1.0, -1.0, -1.0); glVertex3f(-g_nSkySize, -g_nSkySize, -g_nSkySize);
    glTexCoord3d(-1.0, 1.0, -1.0); glVertex3f(-g_nSkySize, g_nSkySize, -g_nSkySize);
    glTexCoord3d(1.0, 1.0, -1.0); glVertex3f(g_nSkySize, g_nSkySize, -g_nSkySize);
    
    glEnd();
}
void environmentMapSetting(void){
    glGenTextures(1, &g_nCubeTex);
    int width,height,channels;

    
    uchar* img0 = readImageData("/Users/bmbi/Desktop/spaceship/env/envtex.bmp", &width, &height, &channels);
    uchar* img1 = readImageData("/Users/bmbi/Desktop/spaceship//env/envtex.bmp", &width, &height, &channels);
    uchar* img2 = readImageData("/Users/bmbi/Desktop/spaceship/env/envtex.bmp", &width, &height, &channels);
    uchar* img3 = readImageData("/Users/bmbi/Desktop/spaceship/env/envtex.bmp", &width, &height, &channels);
    uchar* img4 = readImageData("/Users/bmbi/Desktop/spaceship/env/envtex.bmp", &width, &height, &channels);
    uchar* img5 = readImageData("/Users/bmbi/Desktop/spaceship/env/envtex.bmp", &width, &height, &channels);

    
    glBindTexture(GL_TEXTURE_CUBE_MAP,g_nCubeTex);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X,0,GL_RGB,width,height,0,GL_RGB,GL_UNSIGNED_BYTE,img0);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X,0,GL_RGB,width,height,0,GL_RGB,GL_UNSIGNED_BYTE,img1);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y,0,GL_RGB,width,height,0,GL_RGB,GL_UNSIGNED_BYTE,img2);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,0,GL_RGB,width,height,0,GL_RGB,GL_UNSIGNED_BYTE,img3);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z,0,GL_RGB,width,height,0,GL_RGB,GL_UNSIGNED_BYTE,img4);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z,0,GL_RGB,width,height,0,GL_RGB,GL_UNSIGNED_BYTE,img5);
    
//    glBindTexture(GL_TEXTURE_CUBE_MAP,g_nCubeTex);
//    glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
//    glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
//    glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_WRAP_R,GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    
    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP);
    glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP);
    glTexGeni(GL_R, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP);
    
    glEnable(GL_TEXTURE_GEN_S);
    glEnable(GL_TEXTURE_GEN_T);
    glEnable(GL_TEXTURE_GEN_R);
    glEnable(GL_TEXTURE_CUBE_MAP);
    
}


void moonTextureMapping(void){
    glGenTextures(3, texMoon);
    
    glBindTexture(GL_TEXTURE_2D, *texMoon);
    int width,height,channels;
    unsigned char* img=readImageData("/Users/bmbi/Desktop/spaceship/env/moontex.bmp",&width,&height,&channels);
    
    glTexImage2D(GL_TEXTURE_2D,0,3,width,height,0,GL_RGB,GL_UNSIGNED_BYTE,img);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
}
void earthTextureMapping(void){
    glGenTextures(3, texEarth);
    
    glBindTexture(GL_TEXTURE_2D, *texEarth);
    int width,height,channels;
    unsigned char* img=readImageData("/Users/bmbi/Desktop/spaceship/env/earthtex.bmp",&width,&height,&channels);
    
    glTexImage2D(GL_TEXTURE_2D,0,3,width,height,0,GL_RGB,GL_UNSIGNED_BYTE,img);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
}

//void shuttleTextureMapping(void){
//    glGenTextures(3, texShuttle);
//    
//    glBindTexture(GL_TEXTURE_2D, *texShuttle);
//    int width,height,channels;
//    unsigned char* img=readImageData("/Users/bmbi/Desktop/spaceship/shuttle/texture.bmp",&width,&height,&channels);
//    
//    glTexImage2D(GL_TEXTURE_2D,0,3,width,height,0,GL_RGB,GL_UNSIGNED_BYTE,img);
//    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
//    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
//    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
//    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
//}

void drawShuttle(void){
    glDisable(GL_TEXTURE_GEN_S);
    glDisable(GL_TEXTURE_GEN_T);
    glDisable(GL_TEXTURE_GEN_R);
    glDisable(GL_TEXTURE_CUBE_MAP);
    glScalef(0.8, 0.8, 0.8);
    
    glRotatef(-135, 0, 1, 0);
    myObject teddy("/Users/bmbi/Desktop/spaceship/shuttle.obj");
    teddy.loadObj();
    teddy.dispObj();
}

void dockTextureMapping(void){
    int width,height,channels;
    glBindTexture(GL_TEXTURE_2D, texDock);
    unsigned char* img=readImageData("/Users/bmbi/Desktop/spaceship/env/dock.bmp",&width,&height,&channels);
        glTexImage2D(GL_TEXTURE_2D,0,/*input channel*/ 3,width,height,0,/*textel channel*/ GL_RGB,GL_UNSIGNED_BYTE,img);
      
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
}

void drawDock(void){
    
    glColor3f(1.0,1.0,1.0);
    
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    
    glBindTexture(GL_TEXTURE_2D, texDock);

    gluDisk(dock, 0, 20, 30, 3);
    
}
