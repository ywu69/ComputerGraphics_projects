//
//  main.cpp
//  finalProject
//
//  Created by Yuefeng Wu on 4/10/14.
//  Copyright (c) 2014 Yuefeng Wu. All rights reserved.
//

#include <GLUT/glut.h>
#include <stdlib.h>
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
char text[] = "/Users/Wilfred/Desktop/finalProject/finalProject/elephant.off";
GLint pathLength = 53;

GLUI *glui;
GLUI_Panel *Thresholds;
int main_window;

GLdouble eyeX = 30;
GLdouble eyeY = 0;
GLdouble eyeZ = 0;
GLdouble v_vector[400000][3];
GLdouble w_vector[400000][3];
GLdouble dot_product[400000];
GLdouble contours_vertex[200000][3];
GLint contours_num = 0;
GLint vertex_neighbors[400000][20];
GLint vertex_neighbors_num[400000];

GLdouble normal_curvature[400000][20];
GLdouble k1[400000];
GLint k1_index[400000];
GLdouble k2[400000];
GLdouble kr[400000];
GLdouble suggestive_contours_vertex[200000][3];
GLint suggestive_contours_num = 0;
//GLdouble DwKr[200000];
GLdouble c_threshold = 0.05;
GLdouble s_threshold = 0.00005;

enum ContoursMode {draw_contours,draw_suggestive_contours,draw_both};
ContoursMode cm = draw_contours;

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
    if (strlen(text)==pathLength+8) {
        c_threshold = 0.05;
        s_threshold = 0.00005;
        eyeX = 30;
        eyeY = 0;
        eyeZ = 0;
    }
    if (strlen(text)==pathLength+6) {
        c_threshold = 0.00001;
        s_threshold = 0.00001;
        eyeX = 2;
        eyeY = 0;
        eyeZ = 0;
    }
    if (strlen(text)==pathLength+3) {
        c_threshold = 0.00025;
        s_threshold = 0.0008;
        eyeX = 0;
        eyeY = 0;
        eyeZ = 2;
    }
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

void contours(){
    for (int i = 0; i < vertex_num; i++) {
        contours_vertex[i][0] = 0;
        contours_vertex[i][1] = 0;
        contours_vertex[i][2] = 0;
    }
    contours_num = 0;
    
    for (int i = 0; i < vertex_num; i++) {
        v_vector[i][0] = eyeX - vertex[i][0];
        v_vector[i][1] = eyeY - vertex[i][1];
        v_vector[i][2] = eyeZ - vertex[i][2];
        
        dot_product[i] = v_vector[i][0]*vertexNoraml[i][0] + v_vector[i][1]*vertexNoraml[i][1] + v_vector[i][2]*vertexNoraml[i][2];
        
        if (dot_product[i] > -c_threshold && dot_product[i] < c_threshold) {
            contours_vertex[contours_num][0] = vertex[i][0];
            contours_vertex[contours_num][1] = vertex[i][1];
            contours_vertex[contours_num][2] = vertex[i][2];

            contours_num++;
        }
    }
}

void calW(){
    for (int i =0; i < vertex_num; i++) {
        w_vector[i][0] = v_vector[i][0] - dot_product[i]*vertexNoraml[i][0];
        w_vector[i][1] = v_vector[i][1] - dot_product[i]*vertexNoraml[i][1];
        w_vector[i][2] = v_vector[i][2] - dot_product[i]*vertexNoraml[i][2];
    }
}

void neighborVertex(){
    for (int i = 0; i < vertex_num; i++) {
        for (int j = 0; j < 10; j++) {
            vertex_neighbors[i][j] = 0;
        }
    }
    for (int i = 0; i < vertex_num; i++) {
        vertex_neighbors_num[i] = 0;
        for (int j = 0; j < vertex_face_num[i]; j++) {
            GLint nb1 = face[vertex_face_index[i][j]][0];
            GLint nb2 = face[vertex_face_index[i][j]][1];
            GLint nb3 = face[vertex_face_index[i][j]][2];

            if (vertex_neighbors_num[i] > 0 && vertex_neighbors_num[i] < vertex_face_num[i]) {
                if (nb1==i) {
                    GLboolean bl = 0;
                    for (int k = 0; k < vertex_neighbors_num[i]; k++) {
                        if (vertex_neighbors[i][k]==nb2) {
                            bl = 1;
                        }
                    }
                    if (bl==1) {
                        vertex_neighbors[i][vertex_neighbors_num[i]] = nb3;
                        vertex_neighbors_num[i] = vertex_neighbors_num[i] + 1;
                    }
                    if (bl==0) {
                        vertex_neighbors[i][vertex_neighbors_num[i]] = nb2;
                        vertex_neighbors_num[i] = vertex_neighbors_num[i] + 1;
                    }
                }
                if (nb2==i) {
                    GLboolean bl = 0;
                    for (int k = 0; k < vertex_neighbors_num[i]; k++) {
                        if (vertex_neighbors[i][k]==nb1) {
                            bl = 1;
                        }
                    }
                    if (bl==1) {
                        vertex_neighbors[i][vertex_neighbors_num[i]] = nb3;
                        vertex_neighbors_num[i] = vertex_neighbors_num[i] + 1;
                    }
                    if (bl==0) {
                        vertex_neighbors[i][vertex_neighbors_num[i]] = nb1;
                        vertex_neighbors_num[i] = vertex_neighbors_num[i] + 1;
                    }
                }
                if (nb3==i) {
                    GLboolean bl = 0;
                    for (int k = 0; k < vertex_neighbors_num[i]; k++) {
                        if (vertex_neighbors[i][k]==nb2) {
                            bl = 1;
                        }
                    }
                    if (bl==1) {
                        vertex_neighbors[i][vertex_neighbors_num[i]] = nb1;
                        vertex_neighbors_num[i] = vertex_neighbors_num[i] + 1;
                    }
                    if (bl==0) {
                        vertex_neighbors[i][vertex_neighbors_num[i]] = nb2;
                        vertex_neighbors_num[i] = vertex_neighbors_num[i] + 1;
                    }
                }
            }
            
            if (vertex_neighbors_num[i]==0) {
                if (nb1==i) {
                    vertex_neighbors[i][vertex_neighbors_num[i]] = nb2;
                    vertex_neighbors[i][vertex_neighbors_num[i]+1] = nb3;
                    vertex_neighbors_num[i] = vertex_neighbors_num[i] + 2;
                }
                if (nb2==i) {
                    vertex_neighbors[i][vertex_neighbors_num[i]] = nb1;
                    vertex_neighbors[i][vertex_neighbors_num[i]+1] = nb3;
                    vertex_neighbors_num[i] = vertex_neighbors_num[i] + 2;
                }
                if (nb3==i) {
                    vertex_neighbors[i][vertex_neighbors_num[i]] = nb1;
                    vertex_neighbors[i][vertex_neighbors_num[i]+1] = nb2;
                    vertex_neighbors_num[i] = vertex_neighbors_num[i] + 2;
                }
            }
        }
    }
//    int yyy = vertex_face_num[0];
//    int xxxxxx = vertex_neighbors[100][3];
}

void normalCurvature(){
    for (int i = 0; i < vertex_num; i++) {
        k1[i]=0;
        k2[i]=0;
        for (int j = 0; j < 10; j++) {
            normal_curvature[i][j] = 0;
        }
    }
    for (int i = 0; i < vertex_num; i++) {
        for (int j = 0; j < vertex_neighbors_num[i]; j++) {
            normal_curvature[i][j] = 2*(vertexNoraml[i][0]*(vertex[i][0]-vertex[vertex_neighbors[i][j]][0])+vertexNoraml[i][1]*(vertex[i][1]-vertex[vertex_neighbors[i][j]][1])+vertexNoraml[i][2]*(vertex[i][2]-vertex[vertex_neighbors[i][j]][2]))
            / (pow(vertex[i][0] - vertex[vertex_neighbors[i][j]][0],2) + pow(vertex[i][1] - vertex[vertex_neighbors[i][j]][1],2)
               + pow(vertex[i][2] - vertex[vertex_neighbors[i][j]][2],2));
        }
    }
    
    for (int i = 0; i < vertex_num; i++) {
        k1[i] = normal_curvature[i][0];
        k2[i] = normal_curvature[i][0];
        k1_index[i] = vertex_neighbors[i][0];
        for (int j = 0; j < vertex_neighbors_num[i]; j++) {
            if (k1[i]<normal_curvature[i][j]) {
                k1[i] = normal_curvature[i][j];
                k1_index[i] = vertex_neighbors[i][j];
            }
            if (k2[i]>normal_curvature[i][j]) {
                k2[i] = normal_curvature[i][j];
            }
        }
    }
//    float zzz = k1[0];

}



void s_contours(){
    for (int i = 0; i < vertex_num; i++) {
        suggestive_contours_vertex[i][0] = 0;
        suggestive_contours_vertex[i][1] = 0;
        suggestive_contours_vertex[i][2] = 0;
    }
    suggestive_contours_num = 0;
    for (int i = 0; i < vertex_num; i++) {
        GLdouble a = (vertex[i][0]-vertex[k1_index[i]][0])*w_vector[i][0]+
                     (vertex[i][1]-vertex[k1_index[i]][1])*w_vector[i][1]+
                     (vertex[i][2]-vertex[k1_index[i]][2])*w_vector[i][2];
        GLdouble b = sqrt(pow(vertex[i][0]-vertex[k1_index[i]][0], 2)+pow(vertex[i][1]-vertex[k1_index[i]][1], 2)+pow(vertex[i][2]-vertex[k1_index[i]][2], 2))*sqrt(pow(w_vector[i][0], 2)+pow(w_vector[i][1], 2)+pow(w_vector[i][2], 2));
        GLdouble cos2 = pow(a/b,2.0);
        GLdouble sin2 = 1.0 - cos2;
        
        kr[i] = k1[i] * cos2 + k2[i] * sin2;
        if (kr[i] > -s_threshold && kr[i] < s_threshold ) {
//        if(kr[i] < abs(s_threshold)) {
            suggestive_contours_vertex[suggestive_contours_num][0] = vertex[i][0];
            suggestive_contours_vertex[suggestive_contours_num][1] = vertex[i][1];
            suggestive_contours_vertex[suggestive_contours_num][2] = vertex[i][2];
            suggestive_contours_num++;
        }
    }
//    cout << "Vertex 0's DwKr " << DwKr[1000] << endl;
}

void prejob(){
    file();
    calfaceNormal();
    calvertexNormal();
    contours();
    calW();
    neighborVertex();
    normalCurvature();
    s_contours();
}

void display(){
    
    glShadeModel(GL_SMOOTH);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable( GL_POINT_SMOOTH );
//    glEnable( GL_BLEND );
//    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
//    glPointSize( 2.0 );
    /* adjust region of 3D space projected into this window */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //    glOrtho(-xMax, xMax,		/* x extents */
    //            -yMax, yMax,		/* y extents */
    //            -10*xMax, 10*xMax);		/* z extents */
    gluPerspective(90, (GLfloat) winWidth /(GLfloat) winHeight, .1, 100);
    /* switch back to "normal" transformation mode */
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(eyeX, eyeY, eyeZ, 1.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    
    // Draw contours
    if (cm==draw_contours) {
        glBegin(GL_POINTS);
        //    glBegin(GL_LINE_STRIP);
        glColor4f(1.0, 0.0, 0.0, 1.0);
        for (int i = 0; i<contours_num; i++) {
            glVertex3d(contours_vertex[i][0], contours_vertex[i][1], contours_vertex[i][2]);
        }
        glEnd();
    }
    
    // Draw suggestive contours
    if (cm==draw_suggestive_contours) {
        glBegin(GL_POINTS);
        glColor4f(0.0, 1.0, 0.0, 1.0);
        for (int i = 0; i<suggestive_contours_num; i++) {
            glVertex3d(suggestive_contours_vertex[i][0],suggestive_contours_vertex[i][1],suggestive_contours_vertex[i][2]);
        }
        glEnd();
    }
    
    // Draw both contours and suggestive contours
    if (cm==draw_both) {
        glBegin(GL_POINTS);
        //    glBegin(GL_LINE_STRIP);
        glColor4f(1.0, 0.0, 0.0, 1.0);
        for (int i = 0; i<contours_num; i++) {
            glVertex3d(contours_vertex[i][0], contours_vertex[i][1], contours_vertex[i][2]);
        }
        glColor4f(0.0, 1.0, 0.0, 1.0);
        
        for (int i = 0; i<suggestive_contours_num; i++) {
            glVertex3d(suggestive_contours_vertex[i][0],suggestive_contours_vertex[i][1],suggestive_contours_vertex[i][2]);
        }
        glEnd();
    }
    
    glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y){
    switch (key) {
        case 'w':
            eyeZ -= 1;
            contours();
            calW();
            neighborVertex();
            normalCurvature();
            s_contours();
            break;
        case 's':
            eyeZ += 1;
            contours();
            calW();
            neighborVertex();
            normalCurvature();
            s_contours();
            break;
        case 'a':
            eyeX -= 1;
            contours();
            calW();
            neighborVertex();
            normalCurvature();
            s_contours();
            break;
        case 'd':
            eyeX += 1;
            contours();
            calW();
            neighborVertex();
            normalCurvature();
            s_contours();
            break;
        case 'o':
            c_threshold *= 0.5;
            contours();
            calW();
            neighborVertex();
            normalCurvature();
            s_contours();
            break;
        case 'p':
            c_threshold /= 0.5;
            contours();
            calW();
            neighborVertex();
            normalCurvature();
            s_contours();
            break;
        case 'k':
            s_threshold *= 0.5;
            contours();
            calW();
            neighborVertex();
            normalCurvature();
            s_contours();
            break;
        case 'l':
            s_threshold /= 0.5;
            contours();
            calW();
            neighborVertex();
            normalCurvature();
            s_contours();
            break;
        case 'c':
            cm = draw_contours;
            break;
        case 'v':
            cm = draw_suggestive_contours;
            break;
        case 'b':
            cm = draw_both;
            break;
        case 27:  /*  Escape key  */
            exit(0);
            break;
    }
    glutPostRedisplay();
}

//void reshape(int width, int height)
//{
//    /* distance in grid coordinates from edge to the center of the window */
//    float xMax = viewWidth/2;
//    float yMax = xMax * height / width;
//    
//    /* copy width and height into global variables so other callback
//     functions can access them */
//    winWidth = width;
//    winHeight = height;
//    
//    /* this viewport makes a 1 to 1 mapping of physical pixels to GL
//     "logical" pixels */
//    glViewport(0, 0, (GLint) width, (GLint) height);
//    
//    /* adjust region of 3D space projected into this window */
//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
////    glOrtho(-xMax, xMax,		/* x extents */
////            -yMax, yMax,		/* y extents */
////            -10*xMax, 10*xMax);		/* z extents */
//    gluPerspective(90, (GLfloat) winWidth /(GLfloat) winHeight, .1, 100);
//    /* switch back to "normal" transformation mode */
//    glMatrixMode(GL_MODELVIEW);
//    glLoadIdentity();
//    gluLookAt(eyeX, eyeY, eyeZ, 1.0, 0.0, 0.0, 0.0, 1.0, 0.0);
//}

void change_file_function() {
    if(strlen(text)> 0) {
        prejob();
        glutPostRedisplay();
    }
}

int main(int argc, char ** argv)
{
    glutInit(&argc, argv);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(winWidth, winHeight);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    main_window = glutCreateWindow(argv[0]);
    glutDisplayFunc(display);
//    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    
    glui = GLUI_Master.create_glui_subwindow(main_window,GLUI_SUBWINDOW_BOTTOM);
    glui->add_edittext("OFF File:", GLUI_EDITTEXT_TEXT, text)
    ->set_w(450);
//    Thresholds = new GLUI_Rollout(glui, "Thresholds", true );
//    (new GLUI_Spinner( Thresholds, "C_threshold:", &c_threshold ))
//    ->set_float_limits(0.000000001, 0.1);
//    (new GLUI_Spinner( Thresholds, "S_threhold:", &s_threshold ))
//    ->set_float_limits(0.00000001, 0.1);
    glui->add_button("Change", 2, (GLUI_Update_CB)change_file_function);
    new GLUI_Button( glui, "Quit", 0,(GLUI_Update_CB)exit );
    glui->set_main_gfx_window( main_window );

    prejob();
    
    glutMainLoop();
    return 0;
}

