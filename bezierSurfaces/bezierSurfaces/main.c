//
//  main.cpp
//  Bezier Surfaces
//
//  Created by 吴 岳峰 on 14-2-19.
//  Copyright (c) 2014年 吴 岳峰. All rights reserved.
//

#include <GLUT/glut.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int winWidth = 1000, winHeight = 800;
float viewWidth = 300;
GLdouble maxheight = 0.00;
GLint k = 30;
int buttonPressed;
int oldX, oldY;

int typeMode = 2;

GLint inter_point_num = 0;
GLint patch_index_row = 0;
GLint patch_index_column = 0;
GLdouble patch_index_points[35][35];
GLint control_row = 0;
GLint control_column = 0;
GLdouble patch_mid_points[70][70][4];
GLdouble patch_points[150][150][16];
GLdouble inter_points[400][400][10201][3];
GLdouble vertexNormal[400][400][100][3];
char filename[100];

void file(){
    
    if (typeMode == 1) {
        strcpy(filename,"/Users/Wilfred/Desktop/bezierSurfaces/bezierSurfaces/hump.hf");
    }
    if (typeMode == 2) {
        strcpy(filename,"/Users/Wilfred/Desktop/bezierSurfaces/bezierSurfaces/turb.hf");
    }
    if (typeMode == 3) {
        strcpy(filename,"/Users/Wilfred/Desktop/bezierSurfaces/bezierSurfaces/turb2.hf");
    }
    if (typeMode == 4) {
        strcpy(filename,"/Users/Wilfred/Desktop/bezierSurfaces/bezierSurfaces/smile.hf");
    }
    
    FILE *fp=fopen(filename,"r");
    if(!fp)
    {
        printf("can't open file\n");
    }
    fscanf(fp,"%d %d", &patch_index_row, &patch_index_column);
    for (int i = 0; i<patch_index_row; i++) {
        for (int j = 0; j<patch_index_column; j++) {
            fscanf(fp,"%lf", &patch_index_points[i][j]);
        }
    }
    fclose(fp);
}

// calculate bezier surface points

void bspoints(){

    double s = 0.00;
    double t = 0.00;
    
    if (typeMode == 1) {
        k = 60;
    }
    
    if (typeMode == 2) {
        k = 20;
    }
    
    if (typeMode == 3) {
        k = 13;
    }
    
    if (typeMode == 4) {
        k = 22;
    }
    
    for (int i=0;i<patch_index_row-1; i++) {
        for (int j=0; j<patch_index_column-1; j++) {
            patch_mid_points[i][j][0] = patch_index_points[i][j];
            patch_mid_points[i][j][1] = patch_index_points[i][j+1];
            patch_mid_points[i][j][2] = patch_index_points[i+1][j];
            patch_mid_points[i][j][3] = patch_index_points[i+1][j+1];
        }
    }
    
    for (int i=0;i<patch_index_row-1; i++) {
        for (int j=0; j<patch_index_column-1; j++) {
            patch_points[i][j][0]=patch_points[i][j][1]=patch_points[i][j][4]=patch_points[i][j][5]=patch_mid_points[i][j][0];
            patch_points[i][j][2]=patch_points[i][j][3]=patch_points[i][j][6]=patch_points[i][j][7]=patch_mid_points[i][j][1];
            patch_points[i][j][8]=patch_points[i][j][9]=patch_points[i][j][12]=patch_points[i][j][13]=patch_mid_points[i][j][2];
            patch_points[i][j][10]=patch_points[i][j][11]=patch_points[i][j][14]=patch_points[i][j][15]=patch_mid_points[i][j][3];
        }
    }
    
    for (int i=0;i<patch_index_row-1; i++) {
        for (int j=0; j<patch_index_column-1; j++) {
            patch_points[i][j][0]=patch_points[i][j][1]=patch_points[i][j][4]=patch_points[i][j][5]=patch_mid_points[i][j][0];
            patch_points[i][j][2]=patch_points[i][j][3]=patch_points[i][j][6]=patch_points[i][j][7]=patch_mid_points[i][j][1];
            patch_points[i][j][8]=patch_points[i][j][9]=patch_points[i][j][12]=patch_points[i][j][13]=patch_mid_points[i][j][2];
            patch_points[i][j][10]=patch_points[i][j][11]=patch_points[i][j][14]=patch_points[i][j][15]=patch_mid_points[i][j][3];
        }
    }

    for (int i=0;i<patch_index_row-1; i++) {
        for (int j=0; j<patch_index_column-1; j++) {
            for (s=0.00; s<1.01; s+=0.01) {
                for (t=0.00; t<1.01; t+=0.01) {
            
                    GLdouble s1 = -pow(s, 3)+3*pow(s, 2)-3*s+1;
                    GLdouble s2 = 3*pow(s, 3)-6*pow(s, 2)+3*s;
                    GLdouble s3 = -3*pow(s, 3)+3*pow(s, 2);
                    GLdouble s4 = pow(s, 3);
            
                    GLdouble t1 = -pow(t, 3)+3*pow(t, 2)-3*t+1;
                    GLdouble t2 = 3*pow(t, 3)-6*pow(t, 2)+3*t;
                    GLdouble t3 = -3*pow(t, 3)+3*pow(t, 2);
                    GLdouble t4 = pow(t, 3);
                    
                    GLdouble x = k*s+k*j-(patch_index_row-1)*k/2;
            
                    GLdouble y = 12*(t1*(s1*patch_points[i][j][0]+s2*patch_points[i][j][1]+s3*patch_points[i][j][2]+s4*patch_points[i][j][3])
                                +t2*(s1*patch_points[i][j][4]+s2*patch_points[i][j][5]+s3*patch_points[i][j][6]+s4*patch_points[i][j][7])
                                +t3*(s1*patch_points[i][j][8]+s2*patch_points[i][j][9]+s3*patch_points[i][j][10]+s4*patch_points[i][j][11])
                                +t4*(s1*patch_points[i][j][12]+s2*patch_points[i][j][13]+s3*patch_points[i][j][14]+s4*patch_points[i][j][15]));
            
                    GLdouble z = k*t+k*i-(patch_index_column-1)*k/2;
            
                    inter_points[i][j][inter_point_num][0] = x;
                    inter_points[i][j][inter_point_num][1] = y;
                    inter_points[i][j][inter_point_num][2] = z;
            
            
                    inter_point_num++;
                }
            }
            inter_point_num = 0;
        }
    }
}

void beauty(){
    for (int i=0;i<patch_index_row; i++) {
        for (int j=0; j<patch_index_column; j++) {
                if (maxheight<patch_index_points[i][j]) {
                    maxheight = patch_index_points[i][j];
            }
        }
    }
}

void display(){

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glBegin(GL_QUADS);

    for (int i=0;i<patch_index_row-1; i++) {
        for (int j=0; j<patch_index_column-1; j++) {
            for (int r = 0; r<100; r++) {
                for (int q = 0; q < 100; q++) {
                    GLdouble ratio = (inter_points[i][j][101*r+q][1]+inter_points[i][j][101*r+q+1][1]
                                      +inter_points[i][j][101*r+q+102][1]+inter_points[i][j][101*r+q+101][1])/(4*maxheight*12);
                    glColor3d(ratio*1.00, ratio*1.00, ratio*1.00);
                    glVertex3d(inter_points[i][j][101*r+q][0], inter_points[i][j][101*r+q][1], inter_points[i][j][101*r+q][2]);
                    glVertex3d(inter_points[i][j][101*r+q+1][0], inter_points[i][j][101*r+q+1][1], inter_points[i][j][101*r+q+1][2]);
                    glVertex3d(inter_points[i][j][101*r+q+102][0], inter_points[i][j][101*r+q+102][1], inter_points[i][j][101*r+q+102][2]);
                    glVertex3d(inter_points[i][j][101*r+q+101][0], inter_points[i][j][101*r+q+101][1], inter_points[i][j][101*r+q+101][2]);
                }
            }
        }
    }
    glEnd();
    glutSwapBuffers();
}

void mousePress(int b, int state, int x, int y)
{
    buttonPressed = b;
    oldX = x;
    oldY = y;
}

void mouseDrag(int x, int y)
{
    float dx = x - oldX;		/* record differences from last position */
    float dy = y - oldY;
    
    oldX = x;			/* update stored position */
    oldY = y;
    
    if (buttonPressed == GLUT_LEFT_BUTTON) {
        /* rotation angle, scaled so 1/2 window width = about 90 degrees */
        float angle = 180 * sqrt(dx*dx + dy*dy) / winWidth;
        
        /* save current rotation state */
        float matrix[16];
        glGetFloatv(GL_MODELVIEW_MATRIX, matrix);
        
        /*
         From the starting state, rotate around axis perpendicular to
         mouse motion, where the window x axis is aligned with the 3D
         view x axis, while the window y axis is aligned with the 3D
         view z axis. Find perpendicular using rule that (y,-x) is
         perpendicular to (x,y)
         */
        glLoadIdentity();
        glRotatef(angle, dy,dx,0);
        
        /* reapply other rotations so far */
        glMultMatrixf(matrix);
        
        /* tell GLUT that something has changed and we must redraw */
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

void reshape(int width, int height)
{
    /* distance in grid coordinates from edge to the center of the window */
    float xMax = viewWidth/2;
    float yMax = xMax * height / width;
    
    /* copy width and height into global variables so other callback
     functions can access them */
    winWidth = width;
    winHeight = height;
    
    /* this viewport makes a 1 to 1 mapping of physical pixels to GL
     "logical" pixels */
    glViewport(0, 0, (GLint) width, (GLint) height);
    
    /* adjust region of 3D space projected into this window */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-xMax, xMax,		/* x extents */
            -yMax, yMax,		/* y extents */
            -10*xMax, 10*xMax);		/* z extents */
    
    /* switch back to "normal" transformation mode */
    glMatrixMode(GL_MODELVIEW);
}

void initGLUT(int *argcp, char *argv[])
{
    file();
    beauty();
    bspoints();
    
    glutInit(argcp, argv);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(winWidth, winHeight);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    glutCreateWindow("Bezier Surfaces");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mousePress);
    glutMotionFunc(mouseDrag);
    glutKeyboardFunc(keyboard);
}

void initGL()
{
    float lightdir[4] = {1,1,2,0};	/* homogeneous light position: directional if w=0 */
    float white[4] = {1,1,1,1}; 		/* color for light: glLightfv needs 4 components!*/
    float dim[4] = {.2,.2,.2,1};

    glClearColor(0.0, 0.0, 1.0, 0.0);

    /* enable some GL features */
    glEnable(GL_DEPTH_TEST);		/* tell OpenGL to handle overlapping surfaces */
    glEnable(GL_COLOR_MATERIAL);		/* map glColor to surface colors used by lighting */
    glEnable(GL_NORMALIZE);		/* tell GL to normalize normals so we don't have to */

    /* set up one light for both directional and ambient */
    glLightfv(GL_LIGHT0, GL_AMBIENT, dim);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, white);
    glLightfv(GL_LIGHT0, GL_POSITION, lightdir);
    glEnable(GL_LIGHT0);			/* turn on this light */
    glEnable(GL_LIGHTING);		/* turn on use of lighting in general */
}

int main(int argc, char *argv[])
{
    initGLUT(&argc, argv);
    initGL();
    glutMainLoop();
    return 0;
}