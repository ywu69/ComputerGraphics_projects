//
//  main.cpp
//  boundingBox
//
//  Created by 吴 岳峰 on 14-2-27.
//  Copyright (c) 2014年 吴 岳峰. All rights reserved.
//

#include <GLUT/glut.h>
#include <stdlib.h>
#include <string>
#include <math.h>
#include <stdio.h>
#include <GLUI/glui.h>

int winWidth = 1000, winHeight = 800;
float viewWidth = 300;
int buttonPressed;
int oldX, oldY;
GLint vertex_num = 0;
GLint face_num = 0;
GLint edge_num = 0;
GLdouble vertex[400000][3];
GLint face[600000][3];
GLdouble faceNormal[600000][3];
GLdouble vertexNoraml[400000][3];
GLint vertex_face_index[400000][20];
GLint vertex_face_num[400000];
GLdouble sum[400000][3];
GLint drawMode = 0;
char format[3];

GLdouble x_min;
GLdouble x_max;
GLdouble y_min;
GLdouble y_max;
GLdouble z_min;
GLdouble z_max;
GLdouble boundingbox_vertex[8][3];

GLUI *glui;
int main_window;
char text[] = "/Users/Wilfred/Desktop/boundingBox/boundingBox/elephant.off";
GLint kk = 10;

void file(){
    FILE *fp=fopen(text,"r");
    if(!fp)
    {
        printf("can't open file\n");
    }
    fscanf(fp,"%c %c %c %d %d %d", &format[0], &format[1], &format[2], &vertex_num, &face_num, &edge_num);
    for (int i = 0; i<vertex_num; i++) {
            fscanf(fp,"%lf %lf %lf", &vertex[i][0], &vertex[i][1], &vertex[i][2]);
    }
    for (int i = 0; i<face_num; i++) {
        fscanf(fp, "%d %d %d %d", &drawMode, &face[i][0], &face[i][1], &face[i][2]);
    }
    fclose(fp);
}

void expandMesh(){
    GLdouble e = 1;
    e = kk/fabs(vertex[2][0]);
    for (int i =0; i<vertex_num; i++) {
        vertex[i][0] *= e;
        vertex[i][1] *= e;
        vertex[i][2] *= e;
    }
}

void boxBound(){
    x_min = vertex[0][0];
    x_max = vertex[0][0];
    y_min = vertex[0][1];
    y_max = vertex[0][1];
    z_min = vertex[0][2];
    z_max = vertex[0][2];

    for (int i = 0; i<vertex_num; i++) {
        if (vertex[i][0]<x_min) {
            x_min = vertex[i][0];
        }
        if (vertex[i][0]>x_max) {
            x_max = vertex[i][0];
        }
        if (vertex[i][1]<y_min) {
            y_min = vertex[i][1];
        }
        if (vertex[i][1]>y_max) {
            y_max = vertex[i][1];
        }
        if (vertex[i][2]<z_min) {
            z_min = vertex[i][2];
        }
        if (vertex[i][2]>z_max) {
            z_max = vertex[i][2];
        }
    }
    boundingbox_vertex[0][0] = x_min; boundingbox_vertex[0][1] = y_max; boundingbox_vertex[0][2] = z_min;
    boundingbox_vertex[1][0] = x_max; boundingbox_vertex[1][1] = y_max; boundingbox_vertex[1][2] = z_min;
    boundingbox_vertex[2][0] = x_min; boundingbox_vertex[2][1] = y_min; boundingbox_vertex[2][2] = z_min;
    boundingbox_vertex[3][0] = x_max; boundingbox_vertex[3][1] = y_min; boundingbox_vertex[3][2] = z_min;
    boundingbox_vertex[4][0] = x_min; boundingbox_vertex[4][1] = y_max; boundingbox_vertex[4][2] = z_max;
    boundingbox_vertex[5][0] = x_max; boundingbox_vertex[5][1] = y_max; boundingbox_vertex[5][2] = z_max;
    boundingbox_vertex[6][0] = x_min; boundingbox_vertex[6][1] = y_min; boundingbox_vertex[6][2] = z_max;
    boundingbox_vertex[7][0] = x_max; boundingbox_vertex[7][1] = y_min; boundingbox_vertex[7][2] = z_max;
}

GLdouble crossProduct_x(GLdouble a[3],GLdouble b[3],GLdouble c[3]){
    GLdouble e1[3];
    GLdouble e2[3];
    GLdouble x;
    
    e1[0] = b[0]-a[0];
    e1[1] = b[1]-a[1];
    e1[2] = b[2]-a[2];
    
    e2[0] = c[0]-a[0];
    e2[1] = c[1]-a[1];
    e2[2] = c[2]-a[2];
    
    x = e1[1]*e2[2] - e1[2]*e2[1];
    
    return x;
}

GLdouble crossProduct_y(GLdouble a[3],GLdouble b[3],GLdouble c[3]){
    GLdouble e1[3];
    GLdouble e2[3];
    GLdouble y;
    
    e1[0] = b[0]-a[0];
    e1[1] = b[1]-a[1];
    e1[2] = b[2]-a[2];
    
    e2[0] = c[0]-a[0];
    e2[1] = c[1]-a[1];
    e2[2] = c[2]-a[2];
    
    y = e1[2]*e2[0] - e1[0]*e2[2];
    
    return y;
}

GLdouble crossProduct_z(GLdouble a[3],GLdouble b[3],GLdouble c[3]){
    GLdouble e1[3];
    GLdouble e2[3];
    GLdouble z;
    
    e1[0] = b[0]-a[0];
    e1[1] = b[1]-a[1];
    e1[2] = b[2]-a[2];
    
    e2[0] = c[0]-a[0];
    e2[1] = c[1]-a[1];
    e2[2] = c[2]-a[2];
    
    z = e1[0]*e2[1] - e1[1]*e2[0];
    
    return z;
}

void calfaceNormal(){
    for (int i = 0; i<face_num; i++) {
        faceNormal[i][0] = crossProduct_x(vertex[face[i][0]], vertex[face[i][1]], vertex[face[i][2]]);
        faceNormal[i][1] = crossProduct_y(vertex[face[i][0]], vertex[face[i][1]], vertex[face[i][2]]);
        faceNormal[i][2] = crossProduct_z(vertex[face[i][0]], vertex[face[i][1]], vertex[face[i][2]]);
    }
}

void calvertexNormal(){
    
    for (int i =0; i<face_num; i++) {
         vertex_face_num[i] = 0;
    }
    
    for (int i = 0; i<vertex_num; i++) {
        sum[i][0] = 0;
        sum[i][1] = 0;
        sum[i][2] = 0;
    }
    
    for (int i =0; i<face_num; i++) {
        vertex_face_num[face[i][0]]++;
        vertex_face_num[face[i][1]]++;
        vertex_face_num[face[i][2]]++;
        vertex_face_index[face[i][0]][vertex_face_num[face[i][0]]-1] = i;
        vertex_face_index[face[i][1]][vertex_face_num[face[i][1]]-1] = i;
        vertex_face_index[face[i][2]][vertex_face_num[face[i][2]]-1] = i;
    }
    
    for (int i = 0; i<vertex_num; i++) {
        for (int j = 0; j<vertex_face_num[i]; j++) {
            sum[i][0] += faceNormal[vertex_face_index[i][j]][0];
            sum[i][1] += faceNormal[vertex_face_index[i][j]][1];
            sum[i][2] += faceNormal[vertex_face_index[i][j]][2];
        }
        vertexNoraml[i][0] = sum[i][0]/vertex_face_num[i];
        vertexNoraml[i][1] = sum[i][1]/vertex_face_num[i];
        vertexNoraml[i][2] = sum[i][2]/vertex_face_num[i];
    }
}

void prejob(){
    file();
    expandMesh();
    boxBound();
    calfaceNormal();
    calvertexNormal();
}

void display(){
    
    glShadeModel(GL_SMOOTH);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // Draw mesh
    glBegin(GL_TRIANGLES);
    glColor4d(0.78, 0.62, 0.14, 0.00);
    for (int i = 0; i<face_num; i++) {
        glNormal3d(vertexNoraml[face[i][0]][0], vertexNoraml[face[i][0]][1], vertexNoraml[face[i][0]][2]);
        glVertex3d(vertex[face[i][0]][0], vertex[face[i][0]][1], vertex[face[i][0]][2]);
        glNormal3d(vertexNoraml[face[i][1]][0], vertexNoraml[face[i][1]][1], vertexNoraml[face[i][1]][2]);
        glVertex3d(vertex[face[i][1]][0], vertex[face[i][1]][1], vertex[face[i][1]][2]);
        glNormal3d(vertexNoraml[face[i][2]][0], vertexNoraml[face[i][2]][1], vertexNoraml[face[i][2]][2]);
        glVertex3d(vertex[face[i][2]][0], vertex[face[i][2]][1], vertex[face[i][2]][2]);
    }
    glEnd();
    
    //Draw boundingBox
    if (drawMode == 1) {
        glColor4d(1.00, 0.00, 0.00, 0.9);
        glBegin(GL_LINE_LOOP);
        glVertex3d(boundingbox_vertex[0][0], boundingbox_vertex[0][1], boundingbox_vertex[0][2]);
        glVertex3d(boundingbox_vertex[1][0], boundingbox_vertex[1][1], boundingbox_vertex[1][2]);
        glVertex3d(boundingbox_vertex[3][0], boundingbox_vertex[3][1], boundingbox_vertex[3][2]);
        glVertex3d(boundingbox_vertex[2][0], boundingbox_vertex[2][1], boundingbox_vertex[2][2]);
        glEnd();
        
        glBegin(GL_LINE_LOOP);
        glVertex3d(boundingbox_vertex[4][0], boundingbox_vertex[4][1], boundingbox_vertex[4][2]);
        glVertex3d(boundingbox_vertex[5][0], boundingbox_vertex[5][1], boundingbox_vertex[5][2]);
        glVertex3d(boundingbox_vertex[7][0], boundingbox_vertex[7][1], boundingbox_vertex[7][2]);
        glVertex3d(boundingbox_vertex[6][0], boundingbox_vertex[6][1], boundingbox_vertex[6][2]);
        glEnd();
        
        glBegin(GL_LINE_LOOP);
        glVertex3d(boundingbox_vertex[4][0], boundingbox_vertex[4][1], boundingbox_vertex[4][2]);
        glVertex3d(boundingbox_vertex[6][0], boundingbox_vertex[6][1], boundingbox_vertex[6][2]);
        glVertex3d(boundingbox_vertex[2][0], boundingbox_vertex[2][1], boundingbox_vertex[2][2]);
        glVertex3d(boundingbox_vertex[0][0], boundingbox_vertex[0][1], boundingbox_vertex[0][2]);
        glEnd();
        
        glBegin(GL_LINE_LOOP);
        glVertex3d(boundingbox_vertex[5][0], boundingbox_vertex[5][1], boundingbox_vertex[5][2]);
        glVertex3d(boundingbox_vertex[7][0], boundingbox_vertex[7][1], boundingbox_vertex[7][2]);
        glVertex3d(boundingbox_vertex[3][0], boundingbox_vertex[3][1], boundingbox_vertex[3][2]);
        glVertex3d(boundingbox_vertex[1][0], boundingbox_vertex[1][1], boundingbox_vertex[1][2]);
        glEnd();
        
        glBegin(GL_LINE_LOOP);
        glVertex3d(boundingbox_vertex[0][0], boundingbox_vertex[0][1], boundingbox_vertex[0][2]);
        glVertex3d(boundingbox_vertex[1][0], boundingbox_vertex[1][1], boundingbox_vertex[1][2]);
        glVertex3d(boundingbox_vertex[5][0], boundingbox_vertex[5][1], boundingbox_vertex[5][2]);
        glVertex3d(boundingbox_vertex[4][0], boundingbox_vertex[4][1], boundingbox_vertex[4][2]);
        glEnd();
        
        glBegin(GL_LINE_LOOP);
        glVertex3d(boundingbox_vertex[6][0], boundingbox_vertex[6][1], boundingbox_vertex[6][2]);
        glVertex3d(boundingbox_vertex[7][0], boundingbox_vertex[7][1], boundingbox_vertex[7][2]);
        glVertex3d(boundingbox_vertex[3][0], boundingbox_vertex[3][1], boundingbox_vertex[3][2]);
        glVertex3d(boundingbox_vertex[2][0], boundingbox_vertex[2][1], boundingbox_vertex[2][2]);
        glEnd();
    }
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
        case 'b':
            drawMode = 1;
            break;
        case 'q':
            drawMode = 0;
            break;
        case 27:  /*  Escape key  */
            exit(0);
            break;
    }
    glutPostRedisplay();
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

void change_file_function() {
    if(strlen(text)> 0) {
        prejob();
        glutPostRedisplay();
    }
}

void change_size_function() {
    prejob();
    glutPostRedisplay();
}

void initGLUT(int *argcp, char *argv[])
{
    glutInit(argcp, argv);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(winWidth, winHeight);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    main_window = glutCreateWindow(argv[0]);
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
    
    glui = GLUI_Master.create_glui_subwindow(main_window,GLUI_SUBWINDOW_BOTTOM);
    glui->add_spinner("Zoom", GLUI_SPINNER_INT, &kk, 1, (GLUI_Update_CB)change_size_function)
    ->set_int_limits(1, 50);
    glui->add_edittext("OFF File:", GLUI_EDITTEXT_TEXT, text)
    ->set_w(450);
    glui->add_button("Change", 2, (GLUI_Update_CB)change_file_function);
    new GLUI_Button( glui, "Quit", 0,(GLUI_Update_CB)exit );
    glui->set_main_gfx_window( main_window );
    
    prejob();

    glutMainLoop();
    return 0;
}