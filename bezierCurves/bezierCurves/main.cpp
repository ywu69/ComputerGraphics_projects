//
//  main.cpp
//  bezierCurves
//
//  Created by 吴 岳峰 on 14-2-11.
//  Copyright (c) 2014年 吴 岳峰. All rights reserved.
//

#include <stdlib.h>
#include <stdio.h>
#include <GLUT/glut.h>
#include <math.h>

int ww = 800;
int wh = 700;
int move = - 1;
int pickSize = 10;
double points [100][2];
int points_num = 0;
int curves_amount = 1;


void init()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, ww, 0.0, wh);
}

void myDisplay(){

    glClear(GL_COLOR_BUFFER_BIT);

    //draw points
    glColor3f(1.0, 0.0, 0.0);
    glPointSize(8.0);
    glBegin(GL_POINTS);
    for (int i = 0; i < points_num; i++) {
        glVertex2f(points[i][0],points[i][1]);
    }
    glEnd();
    
    //draw lines
    glColor3f(1.0, 1.0, 1.0);
    glEnable(GL_LINE_STIPPLE);
    glLineWidth(1.0);
    glLineStipple(3, 0xcccc);
    glBegin(GL_LINES);
    for (int i=1; i<curves_amount; i++) {
        glVertex2f(points[3*i-3][0],points[3*i-3][1]);
        glVertex2f(points[3*i-2][0],points[3*i-2][1]);
        glVertex2f(points[3*i-1][0],points[3*i-1][1]);
        glVertex2f(points[3*i][0],points[3*i][1]);
    }
    glEnd();
    
    //draw bezierCurves
    glColor3f(0.0, 0.0, 1.0);
    glDisable(GL_LINE_STIPPLE);
    glLineWidth(2.0);
    glBegin(GL_LINE_STRIP);
    for (int i=1; i<curves_amount; i++) {
        for (double t = 0.00; t <= 1.00; t+=0.01) {
            
            double a1 = pow((1-t),3);
            double a2 = pow((1-t),2)*3*t;
            double a3 = 3*t*t*(1-t);
            double a4 = t*t*t;
            double x = a1*points[3*i-3][0]+a2*points[3*i-2][0]+a3*points[3*i-1][0]+a4*points[3*i][0];
            double y = a1*points[3*i-3][1]+a2*points[3*i-2][1]+a3*points[3*i-1][1]+a4*points[3*i][1];
            glVertex2f(x, y);
        }
    }
    glEnd();
    
    glFlush();
}

void mouse(int button, int state, int x, int y)
{
    GLuint newX = x;
    GLuint newY = wh - y;

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {

        for (int i = 0; i < points_num; i++)
        {
            if ((abs(points[i][0] - newX) <= pickSize) &&
                (abs(points[i][1] - newY) <= pickSize))
            {
                move = i;
            }
        }
        
        if (move < 0) {
            
            points[points_num][0] = newX;
            points[points_num][1] = newY;
            
            points_num++;
            
            if (curves_amount == (points_num - 1)/3 && curves_amount != 0) {
                curves_amount++;
            }
            
            
            //calculate auto-generate points
            if (points_num == 3*curves_amount - 1 && points_num != 2){
                points[3*curves_amount - 2][0] = 2*points[3*curves_amount - 3][0] - points[3*curves_amount - 4][0];
                points[3*curves_amount - 2][1] = 2*points[3*curves_amount - 3][1] - points[3*curves_amount - 4][1];
            }
        }
}

    if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
		move = -1;
	}
    
	glutPostRedisplay();
}

// mouse motion function
void mouseMove(int x, int y)
{
	if (move > -1)
	{
        GLuint newX = x;
        GLuint newY = wh - y;

        if (move < 2) {
            points[move][0] = newX;
            points[move][1] = newY;
        }
        for (int i = 1; i < curves_amount; i++) {
            
            if (move == 3*i - 1) {
                points[move][0] = newX;
                points[move][1] = newY;
                points[move+2][0] = 2*points[move+1][0] - points[move][0];
                points[move+2][1] = 2*points[move+1][1] - points[move][1];
            }
            
            if (move == 3*i) {
                double xc = newX - points[move][0];
                double yc = newY - points[move][1];
                points[move][0] = newX;
                points[move][1] = newY;
                points[move-1][0] += xc;
                points[move-1][1] += yc;
                points[move+1][0] += xc;
                points[move+1][1] += yc;
            }
            
            if (move == 3*i + 1) {
                points[move][0] = newX;
                points[move][1] = newY;
                points[move-2][0] = 2*points[move-1][0] - points[move][0];
                points[move-2][1] = 2*points[move-1][1] - points[move][1];
            }
        }
        
        glutPostRedisplay();
	}
}

void keyboard(unsigned char key, int x, int y){
    switch (key) {
        case 27:  /*  Escape key  */
            exit(0);
            break;
    }

}

int main(int argc, char * agrv[])
{
	glutInit(&argc, agrv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(ww, wh);
	glutInitWindowPosition(100, 150);
	glutCreateWindow("Bezier Curve");
	glutMouseFunc(mouse);
    glutMotionFunc(mouseMove);
	glutDisplayFunc(myDisplay);
    glutKeyboardFunc(keyboard);
	init();
	glutMainLoop();
	return 0;  
}