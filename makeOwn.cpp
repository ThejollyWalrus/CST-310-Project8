// Mason Hamilton
// CST-310-1:55
// 4/6/20
// Professor Citro
// Project 8 Demo Scene

//All the libaries included
#include <GL/glut.h>
#include <cmath>
#include <cstdlib>
#include <string>
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

//To use namespace
using namespace std;

//Global values used over mutiple functions
float angle = 5.0f;
float angle2 = 4.0f;
float xaxis = 0.0f;
float zaxis = 0.0f;
float adder = 0.0f;
float lx = 0.0f, lz=1.0f;
float x = 2.0f, z = 0.0f;
bool spin = true;
int num = 0;
int balls = 0;
bool spiner = false;
bool slide = true;
bool mover = true;
bool spin2 = true;
bool dropped = true;
GLfloat hold;
int wave_count = 0, on = 0, off = 0, p = 0;
double pi = acos(-1);
bool mover2 = true;
double points[45][45][3], r = 1.85, s = 0.00681817;
float inOut = 20.0f;
// Define a 2 x 2 red and yellow checkered pattern using RGB colors.
#define red {0xff, 0x00, 0x00}
#define yellow {0xff, 0xff, 0x00}
#define magenta {0xff, 0, 0xff}
#define PI 3.1415927
GLubyte texture[][3] = {
    red, yellow,
    yellow, red,
};

// Initializes GLUT and enters the main loop.
// This program is a flyby around the RGB color cube.  One intersting note
// is that because the cube is a convex polyhedron and it is the only thing
// in the scene, we can render it using backface culling only. i.e., there
// is no need for a depth buffer.

//This sphere is used for the moving golf ball
void sphere(){
glTranslated(-25,0,0);
  glPushMatrix();
  glColor3d(.9,.9,.9);
  glTranslatef(angle2, xaxis*3,zaxis);
  glTranslated(0.0, -15 , -6);
  glutSolidSphere(1.0, 16, 16);
  glColor3d(.8,.8,.8);
  glutWireSphere(1.0, 16, 16);
  glEnd();
  glPopMatrix();

}
//This sphere function is used to make the pile of golf balls
//I had a different version so the moving ball isn't affecting
void sphere2(){
  glPushMatrix();
  glColor3d(.9,.9,.9);
  glutSolidSphere(.5, 12, 12);
  glColor3d(.8,.8,.8);
  glutWireSphere(.5, 12, 12);
  glEnd();
  glPopMatrix();


}
//This draws the grass plane
void draw2(){

glColor3f(.7, 0, .1);


glColor3f(0, .99, 0);
glBegin(GL_QUADS);
	glVertex3f(-15,-15,-8);
	glVertex3f(15,-15,-8);
	glVertex3f(15,15,-8);
	glVertex3f(-15,15,-8);
glEnd();



}

//This section is used to move the sphere towards the flag
//It has 3 different case's via switch statment
void sphereCreate(){
sphere();

switch (num){
//case 0 moves in a straight line
 case 0:	 
	if(mover2 == true){
	if(spin ==true)
	angle2 += 0.04f;
	}	    
	else{
	 if(mover2 == false)
 	 xaxis -= 0.1f; 
	 zaxis -= 0.175f;   
	 }
	if(angle2 > 33){
	   mover2 = false;
	   dropped = true;
	   
	}
	if(xaxis < -25){
	 angle2 = 4.0f;
	 xaxis = 0.0f;
	 zaxis = 0.0f;
	 num +=1 ;
	 balls++;
	 mover2 = true;
	}
	break;

//case 1 moves in a zig zag pattern and a little faster 
 case 1:
	if(mover2 == true){
		 if(spin ==true){
	 	  angle2 += 0.06f;
		  xaxis += adder;
		}
		  			
		if (xaxis <= -1)
		slide = true;
 		if(xaxis >= 1)
		  slide = false;	 
		if (slide == true)
		  adder = 0.01;			
		if(slide == false)
		  adder = - 0.02;
		
	}	
	
	   
	else{
	if(mover2 == false)
 	xaxis -= 0.1f;    
	zaxis -= 0.1f;
	}
	
	if(angle2 > 33){
	  adder = 0.0;
	   mover2 = false;
	   dropped = true;
	   
	}
	if(xaxis < -25){
	angle2 = 4.0f;
	xaxis = 0.0f;
	zaxis = 0.0f;
	num += 1;
	balls++;
	mover2 = true;
	}
	break;
//case 2 bounces towards the hole 
case 2:

	if(mover2 == true){
	if(spin ==true){
	angle2 += 0.02f;
	zaxis += adder;}
		
		  			
		if (zaxis <= 0)
		slide = true;
 		if(zaxis >= 6)
		slide = false;	 
		if (slide == true)
		  adder = 0.05;
		 			
						
		if(slide == false)
		  adder = - 0.07;
	}    
	else{
	if(mover2 == false)
 	xaxis -= 0.1f;
	zaxis -= 0.1f;    
	}
	if(angle2 > 33){
	   adder = 0.0;
	   mover2 = false;
	   dropped = true;
	   
		}
	if(xaxis < -25){
	angle2 = 4.0f;
	xaxis = 0.0f;	
	zaxis = 0.0f;
	num = 0;
	balls++;
	mover2 = true;
	}	
	break;


}


}



//This version is used for the stick part of the golf club
void draw_cylinder(GLfloat radius, GLfloat height, GLubyte R, GLubyte G, GLubyte B)
{
    GLfloat x              = 0.0;
    GLfloat y              = 0.0;
    GLfloat angle          = 0.0;
    GLfloat angle_stepsize = 0.1;
    glTranslated(7,0,0);
    glRotatef(-30, 0, 1, 0);
    /** Draw the tube */
    glColor3ub(R-40,G-40,B-40);
    glColor3f(0.752941 ,0.752941 ,0.752941);
    glBegin(GL_QUAD_STRIP);
    angle = 0.0;
        while( angle < 2*PI ) {
            x = radius * cos(angle);
            y = radius * sin(angle);
            glVertex3f(x, y , height);
            glVertex3f(x, y , 0.0);
            angle = angle + angle_stepsize;
        }
        glVertex3f(radius, 0.0, height);
        glVertex3f(radius, 0.0, 0.0);
    glEnd();
    /** Draw the circle on top of cylinder */
    glColor3ub(R,G,B);
    glBegin(GL_POLYGON);
    angle = 0.0;
        while( angle < 2*PI ) {
            x = radius * cos(angle);
            y = radius * sin(angle);
            glVertex3f(x, y , height);
            angle = angle + angle_stepsize;
        }
        glVertex3f(radius, 0.0, height);
    glEnd();
}

//2nd version of the cylinder this version is used for the flag pole
void draw_cylinder2(GLfloat radius,
                   GLfloat height,
                   GLubyte R,
                   GLubyte G,
                   GLubyte B)
{
    GLfloat x              = 0.0;
    GLfloat y              = 0.0;
    GLfloat angle          = 0.0;
    GLfloat angle_stepsize = 0.1;
    glTranslated(25.5,1,0);

    /** Draw the tube */
    glColor3ub(R-40,G-40,B-40);
    glColor3f(1 ,1 ,0);
    glBegin(GL_QUAD_STRIP);
    angle = 0.0;
        while( angle < 2*PI ) {
            x = radius * cos(angle);
            y = radius * sin(angle);
            glVertex3f(x, y , height);
            glVertex3f(x, y , 0.0);
            angle = angle + angle_stepsize;
        }
        glVertex3f(radius, 0.0, height);
        glVertex3f(radius, 0.0, 0.0);
    glEnd();

    /** Draw the circle on top of cylinder */
    glColor3ub(R,G,B);
    glBegin(GL_POLYGON);
    angle = 0.0;
        while( angle < 2*PI ) {
            x = radius * cos(angle);
            y = radius * sin(angle);
            glVertex3f(x, y , height);
            angle = angle + angle_stepsize;
        }
        glVertex3f(radius, 0.0, height);
    glEnd();
}
//This fucntion was used to create the hole for where the golf ball falls into
void circ(){
float theta;
 glTranslatef(11.0,-0.5,-8.0);
glBegin(GL_POLYGON);
      glColor3f(0.09, 0.9f, 0.90f);
     
   for(int i = 0; i < 360; i++){
   
	theta = i * 3.1415/180;
	glVertex2f(0.4 + 1.75*cos(theta), 0.825 + 1.75*sin(theta)); 
   }
  
   glEnd();

}
//This fucntion is used to create the club or bottom part of the golf club
void circ2(){
float theta;
 glTranslatef(0,-1, 0);
glBegin(GL_POLYGON);
      glColor3f(0, 0.0f, 0.0f);
     //used 390 instead of 360 to give it more of an oval shape
   for(int i = 0; i < 390; i++){
   
	theta = i * 3.1415/90;
	glVertex2f(0.4 + 1*cos(theta), 0.825 + 1*sin(theta)); 
   }
  
   glEnd();

}

//This fucntion is used to create the moving flag
void rectangle(void)
{
    int x, y;
	double double_x, double_y, double_xb, double_yb;
	glColor3f(0.0, 0.4, 0.3);
	glTranslated(13.485, 7, 6);
	glRotatef(90, 1,0,0);
	//first create a base quad that is made up of different "points" for the location
	glBegin(GL_QUADS);
        for (x=0; x<7; x++) {
            for (y=0; y<7; y++) {
                double_x = double(x) / 44.0f;
                double_y = double(y) / 44.0f;
                double_xb = double(x + 1) / 44.0f;
                double_yb = double(y + 1) / 44.0f;

                glTexCoord2f(double_x, double_y);
                glVertex3f(points[x][y][0], points[x][y][1], points[x][y][2]);

                glTexCoord2f(double_x, double_yb);
                glVertex3f(points[x][y+1][0], points[x][y+1][1], points[x][y+1][2]);

                glTexCoord2f(double_xb, double_yb);
                glVertex3f(points[x+1][y+1][0], points[x+1][y+1][1], points[x+1][y+1][2]);

                glTexCoord2f(double_xb, double_y);
                glVertex3f(points[x+1][y][0], points[x+1][y][1], points[x+1][y][2]);
            }
        }
	glEnd();
	//Wave count is used to display how many ripples will be in the flag 
	//this also use "point"
	if (wave_count==5) {
		for (y=0; y<20; y++) {
			hold = points[0][y][2];

			for (x=0; x<20; x++) {
				points[x][y][2] = points[x+1][y][2];
			}

			points[20][y][2] = hold;
		}

		wave_count = 0;
	}

	wave_count++;
}
//Our main display fuction
//This calls all of our objects and puts them into the scene
void display() { 
  glMatrixMode(GL_MODELVIEW);
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
glPushMatrix();
glColor3f(.5, .8, 0);
glPopMatrix();
glLoadIdentity();
//Look at is used to move our camera to the right postion to see the project
 gluLookAt(x, inOut, z, x+lx, 0.0, z+lz, 0.0, 1, 0);

  glPushMatrix();
  glTranslatef(angle, 0,0);
  
  glPopMatrix();
  draw2();
  rectangle();
  glRotatef(-90, 1,0,0);
  glTranslated(-13.485, -7, -6);
   circ();
sphereCreate();
//All fo the (balls > i) are used to remove the golf balls after one is dropped into the hole
if(balls > 10)
  balls = 0;
cout << "ball: " << balls << endl;
glTranslated(10, -12, -2);
if(balls<10)
	sphere2();
glTranslated(-1, 0,0);
if(balls<9)
	sphere2();
glTranslated(-1,0,0);
if(balls<8)
sphere2();
glTranslated(-1,0,0);
if(balls<7)
sphere2();
glTranslated(3,0,0);
glTranslated(-.5,0,.9);
if(balls<6)
sphere2();
glTranslated(-1,0,0);
if(balls<5)
sphere2();
glTranslated(-1,0,0);
if(balls<4)
sphere2();
glTranslated(2.5,0,-.9);
glTranslated(-1,0,1.8);
if(balls<3)
sphere2();
glTranslated(-1, 0 ,0);
if(balls < 2)
	sphere2();
glTranslated(2,0,-1.8);
glTranslated(-1.5,0,2.7);
if(balls < 1)
	sphere2();
glTranslated(1.5,0,-2.7);
glTranslated(-10, 12, 2);
//I had to use translated to move the golf balls in place
//At the end of each statment i did the opposite translated
// i did that to not affect the other objects
  draw_cylinder2(0.3, 13.0, 255, 160, 100);
  glTranslated(-25.5, -1, 0);
//Below is the if statment i used to move the golf club back and fourth
if(mover == false){
	if(dropped==true)
	angle += 0.02f;
	}
    else{
	if(dropped ==false)
 	angle -= 0.03f;
	}
    if(angle > 1){
	   mover = true;
	   dropped = false;}
    else if(angle < -1)
	mover = false;
//Its moving the angle of y and z postion 
   glRotatef(angle*3, 0, 1, 1);
   glTranslated(1, 0, 1);
//This affect both the club and the stick
    draw_cylinder(0.3, 9.0, 255, 160, 100);
    glRotatef(35, 0, 1, 0);
   circ2();

  
  glFlush();
  glutSwapBuffers();
}
//Reshape method that loads the instructions for the display
//This gives us the right perspective of our project
void reshape(int w, int h) {
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60.0, GLfloat(w) / GLfloat(h), 0.5, 40.0);
  glMatrixMode(GL_MODELVIEW);
}

//A fucntion that lets you create moving points
//This lets us make the flag look like its moving
void init() {
  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);
for (int x=0; x<20; x++) {
        for (int y=0; y<20; y++) {
			points[x][y][0] = double((x / 3.0f) - 7.25f);
			points[x][y][1] = double((y / 5.0f) - 4.5f);
			points[x][y][2] = double(sin((((x / 5.0f) * 40.0f) / 360.0f) * pi * 2.0f));
		}
	}
}


// Special keyboard used input 
//Lets you stop and go 
//Also lets you zoom in and out
void onKeyboard(unsigned char keys, int x, int y) {
	switch(keys) {
		//Stop
		case 's' :
			spin = false;
			break;
		//Go
		case 'g' :
			spin = true;
			break;
		case '=': case '+':
			inOut -= .25;
			break;
		case '-': case '_':
			inOut += .25;
			break;

}

}

// The usual main for a GLUT application.
// This calls all the fucntions and instructions above
int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(900, 900);
  glutCreateWindow("Create My Own 3D");
  glutDisplayFunc(display); 
  glutReshapeFunc(reshape);
  glutIdleFunc(display);
  glutKeyboardFunc(onKeyboard);
  glEnable(GL_DEPTH_TEST);
  init();
  glutMainLoop();
  return 1;
}
  
