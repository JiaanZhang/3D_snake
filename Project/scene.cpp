

#ifdef __APPLE__
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
#else
#  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/freeglut.h>
#endif

//#include <GL/glut.h>
#include <iostream>
#include <vector>
#include <sstream>
#include <cmath>
#include <array>
#include "scene.h"


body::body(){}

body::body(float x, float y, float z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

void body::changeY(float amount) {
	this->y += amount;
}

void body::changeX(float amount) {
	this->x += amount;

}

void body::changeZ(float amount) {
	this->z += amount;

}

void body::reY(float amount) {
    this->y = amount;
}

void body::reX(float amount) {
    this->x = amount;
    
}

void body::reZ(float amount) {
    this->z = amount;
    
}


float body::getY() {
	return this->y;
}

float body::getX() {
	return this->x;
}

float body::getZ() {
	return this->z;
}


void body::draw() {
	glPushMatrix();
	glTranslatef(this->x, this->y, this->z);
   // glTranslatef(12, 12, 12);
	glutSolidCube(1);

	glPopMatrix();
}

void body::get_food(int num){
    this->food_plane = num;
    sphere = gluNewQuadric();
    gluQuadricDrawStyle(sphere, GLU_FILL);
    gluQuadricTexture(sphere, true);
    gluQuadricNormals(sphere, GLU_SMOOTH);
    //Making a display list
    mysphereID = glGenLists(1);
    glNewList(mysphereID, GL_COMPILE);
    gluSphere(sphere, 0.75, 5, 5);
    glEndList();
    gluDeleteQuadric(sphere);
}

void body::dele_food(){
    glDeleteLists(mysphereID, 1);
    
}

void body::draw_food(){
    
    switch(food_plane){
        case 1:
              glTranslatef(0,0.5,0);
            break;
        case 2:
            glTranslatef(0,0,0.5);
            break;
        case 3:
            glTranslatef(0.5,0,0);
            break;
        case 4:
            glTranslatef(-0.5,0,0);
            break;
        case 5:
            glTranslatef(0,0,-0.5);
            break;
        case 6:
            glTranslatef(0,-0.5,0);
            break;
            
    
    }
    
    
    glTranslatef(this->x, this->y, this->z);
    glCallList(mysphereID);
}


Snake::Snake() {
    
    body b1 = body(4, 12, 4);
    body b2 = body(5, 12, 4);
    body b3 = body(6, 12, 4);
    body b4 = body(7, 12, 4);
    
    body_list.push_back(b1);
    body_list.push_back(b2);
    body_list.push_back(b3);
    body_list.push_back(b4);
    
    
}

void Snake::move(int mode){
    
    
    float tx, ty, tz,t1,t2,t3;
    tx = body_list[0].getX();
    ty = body_list[0].getY();
    tz = body_list[0].getZ();
    
    if (!this->get_move()){
        if (food_col) {
            switch (mode) {
                case 1:
                    tx += 1;
                    break;
                case 2:
                    tx -= 1;
                    break;
                case 3:
                    ty += 1;
                    break;
                case 4:
                    ty -= 1;
                    break;
                case 5:
                    tz += 1;
                    break;
                case 6:
                    tz -= 1;
                    break;
                    
            }
            
            body grow = body(tx, ty, tz);
            body_list.insert(body_list.begin(), grow);
            food_col = false;
            
        }
        else {
            for (int i = 1; i < body_list.size(); i++) {
                t1 = body_list[i].getX();
                t2 = body_list[i].getY();
                t3 = body_list[i].getZ();
                body_list[i].reX(tx);
                body_list[i].reY(ty);
                body_list[i].reZ(tz);
                tx = t1;
                ty = t2;
                tz = t3;
            }
            
            switch (mode)
            {
                case 1:
                    body_list[0].changeX(1);
                    break;
                case 2:
                    body_list[0].changeX(-1);
                    break;
                case 3:
                    body_list[0].changeY(1);
                    break;
                case 4:
                    body_list[0].changeY(-1);
                    break;
                case 5:
                    body_list[0].changeZ(1);
                    break;
                case 6:
                    body_list[0].changeZ(-1);
                    break;
            }
        }
    }
    
    else{
        return;
    }
}



std::array<float,3> Snake::position() {
    std::array<float, 3> list;
    list[0] = body_list[0].getX();
    list[1] = body_list[0].getY();
    list[2] = body_list[0].getZ();
    return list;
}


std::array<float,3> Snake::vposition(int index) {
    std::array<float, 3> list;
    list[0] = body_list[index].getX();
    list[1] = body_list[index].getY();
    list[2] = body_list[index].getZ();
    return list;
}

int Snake::snake_size(){
    
    return body_list.size();
}

void Snake::stop_move(){
    float x1,y1,z1,x2,y2,z2;
    for (int i = 0; i < body_list.size(); i++) {
        
        x1 = body_list[i].getX();
        y1 = body_list[i].getY();
        z1 = body_list[i].getZ();
        for (int j = 0; j < body_list.size(); j++) {
            x2 = body_list[j].getX();
            y2 = body_list[j].getY();
            z2 = body_list[j].getZ();
            
            if (j != i){
                if (x1 == x2 && y1 == y2 && z1 == z2){
                    this->stop = true;
                }}}
    }
}


bool Snake::get_move(){
    return this->stop;
}


void Snake::draw() {

    for (vector<body>::iterator it = body_list.begin(); it != body_list.end(); ++it) {
        body o3 = *it;
        
        o3.draw();
    }
}

void Snake::col_food() {
    food_col = true;
}
