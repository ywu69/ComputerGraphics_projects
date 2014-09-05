//
//  main.c
//  Navigation
//
//  Created by 吴 岳峰 on 14-3-16.
//  Copyright (c) 2014年 吴 岳峰. All rights reserved.
//

#include <GLUT/glut.h>
#include <stdlib.h>
#include <string>
#include <math.h>
#include <stdio.h>

int winWidth = 1000, winHeight = 800;
float viewWidth = 300;
int buttonPressed;
int oldX, oldY;

GLint dragon_vertex_num = 0;
GLint dragon_face_num = 0;
GLint dragon_edge_num = 0;
GLdouble dragon_vertex[50000][3];
GLint dragon_face[100000][3];
GLdouble dragon_faceNormal[100000][3];
GLdouble dragon_vertexNoraml[50000][3];
GLint dragon_vertex_face_index[50000][20];
GLint dragon_vertex_face_num[50000];
GLdouble dragon_sum[50000][3];

GLint turtle_vertex_num = 0;
GLint turtle_face_num = 0;
GLint turtle_edge_num = 0;
GLdouble turtle_vertex[150000][3];
GLint turtle_face[300000][3];
GLdouble turtle_faceNormal[300000][3];
GLdouble turtle_vertexNoraml[150000][3];
GLint turtle_vertex_face_index[150000][20];
GLint turtle_vertex_face_num[150000];
GLdouble turtle_sum[150000][3];

GLint hand_vertex_num = 0;
GLint hand_face_num = 0;
GLint hand_edge_num = 0;
GLdouble hand_vertex[40000][3];
GLint hand_face[80000][3];
GLdouble hand_faceNormal[80000][3];
GLdouble hand_vertexNoraml[40000][3];
GLint hand_vertex_face_index[40000][20];
GLint hand_vertex_face_num[40000];
GLdouble hand_sum[40000][3];

GLint teapot_vertex_num = 0;
GLint teapot_face_num = 0;
GLint teapot_edge_num = 0;
GLdouble teapot_vertex[1000][3];
GLint teapot_face[2000][3];
GLdouble teapot_faceNormal[2000][3];
GLdouble teapot_vertexNoraml[1000][3];
GLint teapot_vertex_face_index[1000][20];
GLint teapot_vertex_face_num[1000];
GLdouble teapot_sum[1000][3];

GLint drawMode;
char format[3];

GLdouble dragon_1_x_min;
GLdouble dragon_1_x_max;
GLdouble dragon_1_y_min;
GLdouble dragon_1_y_max;
GLdouble dragon_1_z_min;
GLdouble dragon_1_z_max;
GLdouble dragon_1_boundingbox_vertex[8][3];

GLdouble dragon_2_x_min;
GLdouble dragon_2_x_max;
GLdouble dragon_2_y_min;
GLdouble dragon_2_y_max;
GLdouble dragon_2_z_min;
GLdouble dragon_2_z_max;
GLdouble dragon_2_boundingbox_vertex[8][3];

GLdouble turtle_1_x_min;
GLdouble turtle_1_x_max;
GLdouble turtle_1_y_min;
GLdouble turtle_1_y_max;
GLdouble turtle_1_z_min;
GLdouble turtle_1_z_max;
GLdouble turtle_1_boundingbox_vertex[8][3];

GLdouble turtle_2_x_min;
GLdouble turtle_2_x_max;
GLdouble turtle_2_y_min;
GLdouble turtle_2_y_max;
GLdouble turtle_2_z_min;
GLdouble turtle_2_z_max;
GLdouble turtle_2_boundingbox_vertex[8][3];

GLdouble hand_1_x_min;
GLdouble hand_1_x_max;
GLdouble hand_1_y_min;
GLdouble hand_1_y_max;
GLdouble hand_1_z_min;
GLdouble hand_1_z_max;
GLdouble hand_1_boundingbox_vertex[8][3];

GLdouble hand_2_x_min;
GLdouble hand_2_x_max;
GLdouble hand_2_y_min;
GLdouble hand_2_y_max;
GLdouble hand_2_z_min;
GLdouble hand_2_z_max;
GLdouble hand_2_boundingbox_vertex[8][3];

GLdouble teapot_1_x_min;
GLdouble teapot_1_x_max;
GLdouble teapot_1_y_min;
GLdouble teapot_1_y_max;
GLdouble teapot_1_z_min;
GLdouble teapot_1_z_max;
GLdouble teapot_1_boundingbox_vertex[8][3];

GLdouble teapot_2_x_min;
GLdouble teapot_2_x_max;
GLdouble teapot_2_y_min;
GLdouble teapot_2_y_max;
GLdouble teapot_2_z_min;
GLdouble teapot_2_z_max;
GLdouble teapot_2_boundingbox_vertex[8][3];

char text_dragon[] = "/Users/Wilfred/Desktop/boundingBox/boundingBox/dragon.off";
char text_turtle[] = "/Users/Wilfred/Desktop/boundingBox/boundingBox/turtle.off";
char text_hand[] = "/Users/Wilfred/Desktop/boundingBox/boundingBox/hand.off";
char text_teapot[] = "/Users/Wilfred/Desktop/boundingBox/boundingBox/teapot.off";
GLint kk = 3;

GLdouble navigation_x = 0.0;
GLdouble navigation_y = 0.0;
GLdouble navigation_z = 450;

GLint view_type = 1;

char transform_1_1;
char transform_1_2;
char transform_2_1;
char transform_2_2;
char transform_3_1;
char transform_3_2;
char transform_4_1;
char transform_4_2;
char transform_5_1;
char transform_5_2;
char transform_6_1;
char transform_6_2;
char transform_7_1;
char transform_7_2;
char transform_8_1;
char transform_8_2;

int transform_value_1_1[3];
int transform_value_2_1[3];
int transform_value_2_2[4];
int transform_value_3_1[3];
int transform_value_3_2[4];
int transform_value_4_1[3];
int transform_value_4_2[4];
int transform_value_5_1[3];
int transform_value_5_2[4];
int transform_value_6_1[3];
int transform_value_6_2[4];
int transform_value_7_1[3];
int transform_value_8_1[3];
int transform_value_8_2[4];

char mesh_1[10];
char mesh_2[10];
char mesh_3[10];
char mesh_4[10];
char mesh_5[10];
char mesh_6[10];
char mesh_7[10];
char mesh_8[10];

GLint drawBox = 1;
GLint dragon_1_drag = 1;GLint dragon_2_drag = 1;GLint turtle_1_drag = 1;GLint turtle_2_drag = 1;
GLint hand_1_drag = 1;GLint hand_2_drag = 1;GLint teapot_1_drag = 1;GLint teapot_2_drag = 1;
GLint currentX;
GLint currentY;
GLint dragon_1_dragX=0;
GLint dragon_1_dragY=0;
GLint dragon_2_dragX=0;
GLint dragon_2_dragY=0;
GLint turtle_1_dragX=0;
GLint turtle_1_dragY=0;
GLint turtle_2_dragX=0;
GLint turtle_2_dragY=0;
GLint hand_1_dragX=0;
GLint hand_1_dragY=0;
GLint hand_2_dragX=0;
GLint hand_2_dragY=0;
GLint teapot_1_dragX=0;
GLint teapot_1_dragY=0;
GLint teapot_2_dragX=0;
GLint teapot_2_dragY=0;

void file(){
    
    // Scene File
    FILE *fp_scene=fopen("/Users/Wilfred/Desktop/Navigation/Navigation/scenefile.txt","r");
    if(!fp_scene)
    {
        printf("can't open file\n");
    }
    
    fscanf(fp_scene,"%c %d %d %d %s %c %d %d %d %c %d %d %d %d %s %c %d %d %d %c %d %d %d %d %s %c %d %d %d %c %d %d %d %d %s %c %d %d %d %c %d %d %d %d %s %c %d %d %d %c %d %d %d %d %s %c %d %d %d %s %c %d %d %d %c %d %d %d %d %s", &transform_1_1, &transform_value_1_1[0], &transform_value_1_1[1], &transform_value_1_1[2],mesh_1,&transform_2_1, &transform_value_2_1[0], &transform_value_2_1[1], &transform_value_2_1[2],&transform_2_2, &transform_value_2_2[0], &transform_value_2_2[1], &transform_value_2_2[2],&transform_value_2_2[3],mesh_2,&transform_3_1, &transform_value_3_1[0], &transform_value_3_1[1], &transform_value_3_1[2],&transform_3_2, &transform_value_3_2[0], &transform_value_3_2[1], &transform_value_3_2[2],&transform_value_3_2[3],mesh_3,&transform_4_1, &transform_value_4_1[0], &transform_value_4_1[1], &transform_value_4_1[2],&transform_4_2, &transform_value_4_2[0], &transform_value_4_2[1], &transform_value_4_2[2],&transform_value_4_2[3],mesh_4, &transform_5_1, &transform_value_5_1[0], &transform_value_5_1[1], &transform_value_5_1[2],&transform_5_2, &transform_value_5_2[0], &transform_value_5_2[1], &transform_value_5_2[2],&transform_value_5_2[3], mesh_5, &transform_6_1, &transform_value_6_1[0], &transform_value_6_1[1], &transform_value_6_1[2],&transform_6_2, &transform_value_6_2[0], &transform_value_6_2[1], &transform_value_6_2[2],
           &transform_value_6_2[3],mesh_6,&transform_7_1, &transform_value_7_1[0], &transform_value_7_1[1], &transform_value_7_1[2],mesh_7,&transform_8_1, &transform_value_8_1[0], &transform_value_8_1[1], &transform_value_8_1[2],&transform_8_2, &transform_value_8_2[0], &transform_value_8_2[1], &transform_value_8_2[2],
           &transform_value_8_2[3],mesh_8);
    fclose(fp_scene);
    
    // Meshes Files
    FILE *fp_dragon=fopen(text_dragon,"r");
    if(!fp_dragon)
    {
        printf("can't open file\n");
    }
    fscanf(fp_dragon,"%c %c %c %d %d %d", &format[0], &format[1], &format[2], &dragon_vertex_num, &dragon_face_num, &dragon_edge_num);
    for (int i = 0; i<dragon_vertex_num; i++) {
        fscanf(fp_dragon,"%lf %lf %lf", &dragon_vertex[i][0], &dragon_vertex[i][1], &dragon_vertex[i][2]);
    }
    for (int i = 0; i<dragon_face_num; i++) {
        fscanf(fp_dragon, "%d %d %d %d", &drawMode, &dragon_face[i][0], &dragon_face[i][1], &dragon_face[i][2]);
    }
    fclose(fp_dragon);
    
    FILE *fp_turtle=fopen(text_turtle,"r");
    if(!fp_turtle)
    {
        printf("can't open file\n");
    }
    fscanf(fp_turtle,"%c %c %c %d %d %d", &format[0], &format[1], &format[2], &turtle_vertex_num, &turtle_face_num, &turtle_edge_num);
    for (int i = 0; i<turtle_vertex_num; i++) {
        fscanf(fp_turtle,"%lf %lf %lf", &turtle_vertex[i][0], &turtle_vertex[i][1], &turtle_vertex[i][2]);
    }
    for (int i = 0; i<turtle_face_num; i++) {
        fscanf(fp_turtle, "%d %d %d %d", &drawMode, &turtle_face[i][0], &turtle_face[i][1], &turtle_face[i][2]);
    }
    fclose(fp_turtle);
    
    FILE *fp_hand=fopen(text_hand,"r");
    if(!fp_hand)
    {
        printf("can't open file\n");
    }
    fscanf(fp_hand,"%c %c %c %d %d %d", &format[0], &format[1], &format[2], &hand_vertex_num, &hand_face_num, &hand_edge_num);
    for (int i = 0; i<hand_vertex_num; i++) {
        fscanf(fp_hand,"%lf %lf %lf", &hand_vertex[i][0], &hand_vertex[i][1], &hand_vertex[i][2]);
    }
    for (int i = 0; i<hand_face_num; i++) {
        fscanf(fp_hand, "%d %d %d %d", &drawMode, &hand_face[i][0], &hand_face[i][1], &hand_face[i][2]);
    }
    fclose(fp_hand);
    
    FILE *fp_teapot=fopen(text_teapot,"r");
    if(!fp_teapot)
    {
        printf("can't open file\n");
    }
    fscanf(fp_teapot,"%c %c %c %d %d %d", &format[0], &format[1], &format[2], &teapot_vertex_num, &teapot_face_num, &teapot_edge_num);
    for (int i = 0; i<teapot_vertex_num; i++) {
        fscanf(fp_teapot,"%lf %lf %lf", &teapot_vertex[i][0], &teapot_vertex[i][1], &teapot_vertex[i][2]);
    }
    for (int i = 0; i<teapot_face_num; i++) {
        fscanf(fp_teapot, "%d %d %d %d", &drawMode, &teapot_face[i][0], &teapot_face[i][1], &teapot_face[i][2]);
    }
    fclose(fp_teapot);
}

void expandMesh(){
    
    for (int i =0; i<dragon_vertex_num; i++) {
        dragon_vertex[i][0] *= 130;
        dragon_vertex[i][1] *= 130;
        dragon_vertex[i][2] *= 130;
    }
    
    for (int i =0; i<turtle_vertex_num; i++) {
        turtle_vertex[i][0] *= 0.6;
        turtle_vertex[i][1] *= 0.6;
        turtle_vertex[i][2] *= 0.6;
    }
    
    for (int i =0; i<hand_vertex_num; i++) {
        hand_vertex[i][0] *= 55;
        hand_vertex[i][1] *= 55;
        hand_vertex[i][2] *= 55;
    }
    
    for (int i =0; i<teapot_vertex_num; i++) {
        teapot_vertex[i][0] *= 16;
        teapot_vertex[i][1] *= 16;
        teapot_vertex[i][2] *= 16;
    }
}



void boxBound(){
    dragon_1_x_min=0;dragon_1_x_max=0;dragon_1_y_min=0;dragon_1_y_max=0;dragon_1_z_min=0;dragon_1_z_max=0;
    dragon_2_x_min=0;dragon_2_x_max=0;dragon_2_y_min=0;dragon_2_y_max=0;dragon_2_z_min=0;dragon_2_z_max=0;
    turtle_1_x_min=0;turtle_1_x_max=0;turtle_1_y_min=0;turtle_1_y_max=0;turtle_1_z_min=0;turtle_1_z_max=0;
    turtle_2_x_min=0;turtle_2_x_max=0;turtle_2_y_min=0;turtle_2_y_max=0;turtle_2_z_min=0;turtle_2_z_max=0;
    hand_1_x_min=0;hand_1_x_max=0;hand_1_y_min=0;hand_1_y_max=0;hand_1_z_min=0;hand_1_z_max=0;
    hand_2_x_min=0;hand_2_x_max=0;hand_2_y_min=0;hand_2_y_max=0;hand_2_z_min=0;hand_2_z_max=0;
    teapot_1_x_min=0;teapot_1_x_max=0;teapot_1_y_min=0;teapot_1_y_max=0;teapot_1_z_min=0;teapot_1_z_max=0;
    teapot_2_x_min=0;teapot_2_x_max=0;teapot_2_y_min=0;teapot_2_y_max=0;teapot_2_z_min=0;teapot_2_z_max=0;
    // turtle Mesh 1
    dragon_1_x_min = dragon_vertex[0][0];
    dragon_1_x_max = dragon_vertex[0][0];
    dragon_1_y_min = dragon_vertex[0][1];
    dragon_1_y_max = dragon_vertex[0][1];
    dragon_1_z_min = dragon_vertex[0][2];
    dragon_1_z_max = dragon_vertex[0][2];
    
    for (int i = 0; i<dragon_vertex_num; i++) {
        if (dragon_vertex[i][0]<dragon_1_x_min) {
            dragon_1_x_min = dragon_vertex[i][0];
        }
        if (dragon_vertex[i][0]>dragon_1_x_max) {
            dragon_1_x_max = dragon_vertex[i][0];
        }
        if (dragon_vertex[i][1]<dragon_1_y_min) {
            dragon_1_y_min = dragon_vertex[i][1];
        }
        if (dragon_vertex[i][1]>dragon_1_y_max) {
            dragon_1_y_max = dragon_vertex[i][1];
        }
        if (dragon_vertex[i][2]<dragon_1_z_min) {
            dragon_1_z_min = dragon_vertex[i][2];
        }
        if (dragon_vertex[i][2]>dragon_1_z_max) {
            dragon_1_z_max = dragon_vertex[i][2];
        }
    }
    
    double x_1_min = dragon_1_x_min;
    double x_1_max = dragon_1_x_max;
    double y_1_min = dragon_1_y_min;
    double y_1_max = dragon_1_y_max;
    double z_1_min = dragon_1_z_min;
    double z_1_max = dragon_1_z_max;
    
    dragon_1_x_min += transform_value_1_1[0];dragon_1_x_max +=transform_value_1_1[0];dragon_1_z_min += transform_value_1_1[2];dragon_1_z_max +=transform_value_1_1[2];
    dragon_1_x_min += dragon_1_dragX;dragon_1_x_max += dragon_1_dragX;dragon_1_y_min += dragon_1_dragY;dragon_1_y_max += dragon_1_dragY;
    
    dragon_1_boundingbox_vertex[0][0] = dragon_1_x_min; dragon_1_boundingbox_vertex[0][1] = dragon_1_y_max; dragon_1_boundingbox_vertex[0][2] = dragon_1_z_min;
    dragon_1_boundingbox_vertex[1][0] = dragon_1_x_max; dragon_1_boundingbox_vertex[1][1] = dragon_1_y_max; dragon_1_boundingbox_vertex[1][2] = dragon_1_z_min;
    dragon_1_boundingbox_vertex[2][0] = dragon_1_x_min; dragon_1_boundingbox_vertex[2][1] = dragon_1_y_min; dragon_1_boundingbox_vertex[2][2] = dragon_1_z_min;
    dragon_1_boundingbox_vertex[3][0] = dragon_1_x_max; dragon_1_boundingbox_vertex[3][1] = dragon_1_y_min; dragon_1_boundingbox_vertex[3][2] = dragon_1_z_min;
    dragon_1_boundingbox_vertex[4][0] = dragon_1_x_min; dragon_1_boundingbox_vertex[4][1] = dragon_1_y_max; dragon_1_boundingbox_vertex[4][2] = dragon_1_z_max;
    dragon_1_boundingbox_vertex[5][0] = dragon_1_x_max; dragon_1_boundingbox_vertex[5][1] = dragon_1_y_max; dragon_1_boundingbox_vertex[5][2] = dragon_1_z_max;
    dragon_1_boundingbox_vertex[6][0] = dragon_1_x_min; dragon_1_boundingbox_vertex[6][1] = dragon_1_y_min; dragon_1_boundingbox_vertex[6][2] = dragon_1_z_max;
    dragon_1_boundingbox_vertex[7][0] = dragon_1_x_max; dragon_1_boundingbox_vertex[7][1] = dragon_1_y_min; dragon_1_boundingbox_vertex[7][2] = dragon_1_z_max;
    
    // dragon Mesh 2
    dragon_2_x_min = -z_1_max;dragon_2_x_max = -z_1_min;dragon_2_y_min = y_1_min;dragon_2_y_max = y_1_max;dragon_2_z_min = x_1_min;dragon_2_z_max = x_1_max;
    
    dragon_2_x_min += transform_value_2_1[0];dragon_2_x_max += transform_value_2_1[0];dragon_2_z_min += transform_value_2_1[2]; dragon_2_z_max += transform_value_2_1[2];
    dragon_2_x_min += dragon_2_dragX;dragon_2_x_max += dragon_2_dragX;dragon_2_y_min += dragon_2_dragY;dragon_2_y_max += dragon_2_dragY;
    
    dragon_2_boundingbox_vertex[0][0] = dragon_2_x_min; dragon_2_boundingbox_vertex[0][1] = dragon_2_y_max; dragon_2_boundingbox_vertex[0][2] = dragon_2_z_min;
    dragon_2_boundingbox_vertex[1][0] = dragon_2_x_max; dragon_2_boundingbox_vertex[1][1] = dragon_2_y_max; dragon_2_boundingbox_vertex[1][2] = dragon_2_z_min;
    dragon_2_boundingbox_vertex[2][0] = dragon_2_x_min; dragon_2_boundingbox_vertex[2][1] = dragon_2_y_min; dragon_2_boundingbox_vertex[2][2] = dragon_2_z_min;
    dragon_2_boundingbox_vertex[3][0] = dragon_2_x_max; dragon_2_boundingbox_vertex[3][1] = dragon_2_y_min; dragon_2_boundingbox_vertex[3][2] = dragon_2_z_min;
    dragon_2_boundingbox_vertex[4][0] = dragon_2_x_min; dragon_2_boundingbox_vertex[4][1] = dragon_2_y_max; dragon_2_boundingbox_vertex[4][2] = dragon_2_z_max;
    dragon_2_boundingbox_vertex[5][0] = dragon_2_x_max; dragon_2_boundingbox_vertex[5][1] = dragon_2_y_max; dragon_2_boundingbox_vertex[5][2] = dragon_2_z_max;
    dragon_2_boundingbox_vertex[6][0] = dragon_2_x_min; dragon_2_boundingbox_vertex[6][1] = dragon_2_y_min; dragon_2_boundingbox_vertex[6][2] = dragon_2_z_max;
    dragon_2_boundingbox_vertex[7][0] = dragon_2_x_max; dragon_2_boundingbox_vertex[7][1] = dragon_2_y_min; dragon_2_boundingbox_vertex[7][2] = dragon_2_z_max;
    
    // Turtle Mesh 1
    turtle_1_x_min = turtle_vertex[0][0];
    turtle_1_x_max = turtle_vertex[0][0];
    turtle_1_y_min = turtle_vertex[0][1];
    turtle_1_y_max = turtle_vertex[0][1];
    turtle_1_z_min = turtle_vertex[0][2];
    turtle_1_z_max = turtle_vertex[0][2];
    
    for (int i = 0; i<turtle_vertex_num; i++) {
        if (turtle_vertex[i][0]<turtle_1_x_min) {
            turtle_1_x_min = turtle_vertex[i][0];
        }
        if (turtle_vertex[i][0]>turtle_1_x_max) {
            turtle_1_x_max = turtle_vertex[i][0];
        }
        if (turtle_vertex[i][1]<turtle_1_y_min) {
            turtle_1_y_min = turtle_vertex[i][1];
        }
        if (turtle_vertex[i][1]>turtle_1_y_max) {
            turtle_1_y_max = turtle_vertex[i][1];
        }
        if (turtle_vertex[i][2]<turtle_1_z_min) {
            turtle_1_z_min = turtle_vertex[i][2];
        }
        if (turtle_vertex[i][2]>turtle_1_z_max) {
            turtle_1_z_max = turtle_vertex[i][2];
        }
    }
    
    double x_2_min = turtle_1_x_min;
    double x_2_max = turtle_1_x_max;
    double y_2_min = turtle_1_y_min;
    double y_2_max = turtle_1_y_max;
    double z_2_min = turtle_1_z_min;
    double z_2_max = turtle_1_z_max;
    
    turtle_1_x_min = -x_2_max;turtle_1_x_max = -x_2_min;turtle_1_z_min = -z_2_max;turtle_1_z_max = -z_2_min;
    
    turtle_1_x_min += transform_value_3_1[0];turtle_1_x_max += transform_value_3_1[0];turtle_1_y_min += transform_value_3_1[1];turtle_1_y_max += transform_value_3_1[1];turtle_1_z_min += transform_value_3_1[2];turtle_1_z_max += transform_value_3_1[2];
    turtle_1_x_min += turtle_1_dragX;turtle_1_x_max += turtle_1_dragX;turtle_1_y_min += turtle_1_dragY;turtle_1_y_max += turtle_1_dragY;
    
    turtle_1_boundingbox_vertex[0][0] = turtle_1_x_min; turtle_1_boundingbox_vertex[0][1] = turtle_1_y_max; turtle_1_boundingbox_vertex[0][2] = turtle_1_z_min;
    turtle_1_boundingbox_vertex[1][0] = turtle_1_x_max; turtle_1_boundingbox_vertex[1][1] = turtle_1_y_max; turtle_1_boundingbox_vertex[1][2] = turtle_1_z_min;
    turtle_1_boundingbox_vertex[2][0] = turtle_1_x_min; turtle_1_boundingbox_vertex[2][1] = turtle_1_y_min; turtle_1_boundingbox_vertex[2][2] = turtle_1_z_min;
    turtle_1_boundingbox_vertex[3][0] = turtle_1_x_max; turtle_1_boundingbox_vertex[3][1] = turtle_1_y_min; turtle_1_boundingbox_vertex[3][2] = turtle_1_z_min;
    turtle_1_boundingbox_vertex[4][0] = turtle_1_x_min; turtle_1_boundingbox_vertex[4][1] = turtle_1_y_max; turtle_1_boundingbox_vertex[4][2] = turtle_1_z_max;
    turtle_1_boundingbox_vertex[5][0] = turtle_1_x_max; turtle_1_boundingbox_vertex[5][1] = turtle_1_y_max; turtle_1_boundingbox_vertex[5][2] = turtle_1_z_max;
    turtle_1_boundingbox_vertex[6][0] = turtle_1_x_min; turtle_1_boundingbox_vertex[6][1] = turtle_1_y_min; turtle_1_boundingbox_vertex[6][2] = turtle_1_z_max;
    turtle_1_boundingbox_vertex[7][0] = turtle_1_x_max; turtle_1_boundingbox_vertex[7][1] = turtle_1_y_min; turtle_1_boundingbox_vertex[7][2] = turtle_1_z_max;
    
    // Turtle Mesh 2
    turtle_2_x_min = x_2_min;
    turtle_2_x_max = x_2_max;
    turtle_2_y_min = y_2_min;
    turtle_2_y_max = y_2_max;
    turtle_2_z_min = z_2_min;
    turtle_2_z_max = z_2_max;
    
    turtle_2_x_min = z_2_min;
    turtle_2_x_max = z_2_max;
    turtle_2_z_min = -x_2_max;
    turtle_2_z_max = -x_1_min;
    
    turtle_2_x_min += transform_value_4_1[0];
    turtle_2_x_max += transform_value_4_1[0];
    turtle_2_y_min += transform_value_4_1[1];
    turtle_2_y_max += transform_value_4_1[1];
    turtle_2_z_min += transform_value_4_1[2];
    turtle_2_z_max += transform_value_4_1[2];
    turtle_2_x_min += turtle_2_dragX;turtle_2_x_max += turtle_2_dragX;turtle_2_y_min += turtle_2_dragY;turtle_2_y_max += turtle_2_dragY;
    
    turtle_2_boundingbox_vertex[0][0] = turtle_2_x_min; turtle_2_boundingbox_vertex[0][1] = turtle_2_y_max; turtle_2_boundingbox_vertex[0][2] = turtle_2_z_min;
    turtle_2_boundingbox_vertex[1][0] = turtle_2_x_max; turtle_2_boundingbox_vertex[1][1] = turtle_2_y_max; turtle_2_boundingbox_vertex[1][2] = turtle_2_z_min;
    turtle_2_boundingbox_vertex[2][0] = turtle_2_x_min; turtle_2_boundingbox_vertex[2][1] = turtle_2_y_min; turtle_2_boundingbox_vertex[2][2] = turtle_2_z_min;
    turtle_2_boundingbox_vertex[3][0] = turtle_2_x_max; turtle_2_boundingbox_vertex[3][1] = turtle_2_y_min; turtle_2_boundingbox_vertex[3][2] = turtle_2_z_min;
    turtle_2_boundingbox_vertex[4][0] = turtle_2_x_min; turtle_2_boundingbox_vertex[4][1] = turtle_2_y_max; turtle_2_boundingbox_vertex[4][2] = turtle_2_z_max;
    turtle_2_boundingbox_vertex[5][0] = turtle_2_x_max; turtle_2_boundingbox_vertex[5][1] = turtle_2_y_max; turtle_2_boundingbox_vertex[5][2] = turtle_2_z_max;
    turtle_2_boundingbox_vertex[6][0] = turtle_2_x_min; turtle_2_boundingbox_vertex[6][1] = turtle_2_y_min; turtle_2_boundingbox_vertex[6][2] = turtle_2_z_max;
    turtle_2_boundingbox_vertex[7][0] = turtle_2_x_max; turtle_2_boundingbox_vertex[7][1] = turtle_2_y_min; turtle_2_boundingbox_vertex[7][2] = turtle_2_z_max;
    
    // Hand Mesh 1
    hand_1_x_min = hand_vertex[0][0];
    hand_1_x_max = hand_vertex[0][0];
    hand_1_y_min = hand_vertex[0][1];
    hand_1_y_max = hand_vertex[0][1];
    hand_1_z_min = hand_vertex[0][2];
    hand_1_z_max = hand_vertex[0][2];
    
    for (int i = 0; i<hand_vertex_num; i++) {
        if (hand_vertex[i][0]<hand_1_x_min) {
            hand_1_x_min = hand_vertex[i][0];
        }
        if (hand_vertex[i][0]>hand_1_x_max) {
            hand_1_x_max = hand_vertex[i][0];
        }
        if (hand_vertex[i][1]<hand_1_y_min) {
            hand_1_y_min = hand_vertex[i][1];
        }
        if (hand_vertex[i][1]>hand_1_y_max) {
            hand_1_y_max = hand_vertex[i][1];
        }
        if (hand_vertex[i][2]<hand_1_z_min) {
            hand_1_z_min = hand_vertex[i][2];
        }
        if (hand_vertex[i][2]>hand_1_z_max) {
            hand_1_z_max = hand_vertex[i][2];
        }
    }
    
    double x_3_min = hand_1_x_min;
    double x_3_max = hand_1_x_max;
    double y_3_min = hand_1_y_min;
    double y_3_max = hand_1_y_max;
    double z_3_min = hand_1_z_min;
    double z_3_max = hand_1_z_max;
    
    hand_1_x_min = z_3_min + transform_value_5_1[0];
    hand_1_x_max = z_3_max + transform_value_5_1[0];
    hand_1_z_min = -x_3_max + transform_value_5_1[2];
    hand_1_z_max = -x_3_min + transform_value_5_1[2];
    hand_1_x_min += hand_1_dragX;hand_1_x_max += hand_1_dragX;hand_1_y_min += hand_1_dragY;hand_1_y_max += hand_1_dragY;
    
    hand_1_boundingbox_vertex[0][0] = hand_1_x_min; hand_1_boundingbox_vertex[0][1] = hand_1_y_max; hand_1_boundingbox_vertex[0][2] = hand_1_z_min;
    hand_1_boundingbox_vertex[1][0] = hand_1_x_max; hand_1_boundingbox_vertex[1][1] = hand_1_y_max; hand_1_boundingbox_vertex[1][2] = hand_1_z_min;
    hand_1_boundingbox_vertex[2][0] = hand_1_x_min; hand_1_boundingbox_vertex[2][1] = hand_1_y_min; hand_1_boundingbox_vertex[2][2] = hand_1_z_min;
    hand_1_boundingbox_vertex[3][0] = hand_1_x_max; hand_1_boundingbox_vertex[3][1] = hand_1_y_min; hand_1_boundingbox_vertex[3][2] = hand_1_z_min;
    hand_1_boundingbox_vertex[4][0] = hand_1_x_min; hand_1_boundingbox_vertex[4][1] = hand_1_y_max; hand_1_boundingbox_vertex[4][2] = hand_1_z_max;
    hand_1_boundingbox_vertex[5][0] = hand_1_x_max; hand_1_boundingbox_vertex[5][1] = hand_1_y_max; hand_1_boundingbox_vertex[5][2] = hand_1_z_max;
    hand_1_boundingbox_vertex[6][0] = hand_1_x_min; hand_1_boundingbox_vertex[6][1] = hand_1_y_min; hand_1_boundingbox_vertex[6][2] = hand_1_z_max;
    hand_1_boundingbox_vertex[7][0] = hand_1_x_max; hand_1_boundingbox_vertex[7][1] = hand_1_y_min; hand_1_boundingbox_vertex[7][2] = hand_1_z_max;
    
    // Hand Mesh 2
    hand_2_x_min = x_3_min;
    hand_2_x_max = x_3_max;
    hand_2_y_min = y_3_min;
    hand_2_y_max = y_3_max;
    hand_2_z_min = z_3_min;
    hand_2_z_max = z_3_max;
    
    hand_2_x_min = -z_3_max + transform_value_6_1[0];
    hand_2_x_max = -z_3_min + transform_value_6_1[0];
    hand_2_z_min = x_3_min + transform_value_6_1[2];
    hand_2_z_max = x_3_max + transform_value_6_1[2];
    hand_2_x_min += hand_2_dragX;hand_2_x_max += hand_2_dragX;hand_2_y_min += hand_2_dragY;hand_2_y_max += hand_2_dragY;
    
    hand_2_boundingbox_vertex[0][0] = hand_2_x_min; hand_2_boundingbox_vertex[0][1] = hand_2_y_max; hand_2_boundingbox_vertex[0][2] = hand_2_z_min;
    hand_2_boundingbox_vertex[1][0] = hand_2_x_max; hand_2_boundingbox_vertex[1][1] = hand_2_y_max; hand_2_boundingbox_vertex[1][2] = hand_2_z_min;
    hand_2_boundingbox_vertex[2][0] = hand_2_x_min; hand_2_boundingbox_vertex[2][1] = hand_2_y_min; hand_2_boundingbox_vertex[2][2] = hand_2_z_min;
    hand_2_boundingbox_vertex[3][0] = hand_2_x_max; hand_2_boundingbox_vertex[3][1] = hand_2_y_min; hand_2_boundingbox_vertex[3][2] = hand_2_z_min;
    hand_2_boundingbox_vertex[4][0] = hand_2_x_min; hand_2_boundingbox_vertex[4][1] = hand_2_y_max; hand_2_boundingbox_vertex[4][2] = hand_2_z_max;
    hand_2_boundingbox_vertex[5][0] = hand_2_x_max; hand_2_boundingbox_vertex[5][1] = hand_2_y_max; hand_2_boundingbox_vertex[5][2] = hand_2_z_max;
    hand_2_boundingbox_vertex[6][0] = hand_2_x_min; hand_2_boundingbox_vertex[6][1] = hand_2_y_min; hand_2_boundingbox_vertex[6][2] = hand_2_z_max;
    hand_2_boundingbox_vertex[7][0] = hand_2_x_max; hand_2_boundingbox_vertex[7][1] = hand_2_y_min; hand_2_boundingbox_vertex[7][2] = hand_2_z_max;
    
    // Teapot Mesh 1
    teapot_1_x_min = teapot_vertex[0][0];
    teapot_1_x_max = teapot_vertex[0][0];
    teapot_1_y_min = teapot_vertex[0][1];
    teapot_1_y_max = teapot_vertex[0][1];
    teapot_1_z_min = teapot_vertex[0][2];
    teapot_1_z_max = teapot_vertex[0][2];
    
    for (int i = 0; i<teapot_vertex_num; i++) {
        if (teapot_vertex[i][0]<teapot_1_x_min) {
            teapot_1_x_min = teapot_vertex[i][0];
        }
        if (teapot_vertex[i][0]>teapot_1_x_max) {
            teapot_1_x_max = teapot_vertex[i][0];
        }
        if (teapot_vertex[i][1]<teapot_1_y_min) {
            teapot_1_y_min = teapot_vertex[i][1];
        }
        if (teapot_vertex[i][1]>teapot_1_y_max) {
            teapot_1_y_max = teapot_vertex[i][1];
        }
        if (teapot_vertex[i][2]<teapot_1_z_min) {
            teapot_1_z_min = teapot_vertex[i][2];
        }
        if (teapot_vertex[i][2]>teapot_1_z_max) {
            teapot_1_z_max = teapot_vertex[i][2];
        }
    }
    
    double x_4_min = teapot_1_x_min;
    double x_4_max = teapot_1_x_max;
    double y_4_min = teapot_1_y_min;
    double y_4_max = teapot_1_y_max;
    double z_4_min = teapot_1_z_min;
    double z_4_max = teapot_1_z_max;
    
    teapot_1_x_min += transform_value_7_1[0];
    teapot_1_x_max += transform_value_7_1[0];
    teapot_1_z_min += transform_value_7_1[2];
    teapot_1_z_max += transform_value_7_1[2];
    teapot_1_x_min += teapot_1_dragX;teapot_1_x_max += teapot_1_dragX;teapot_1_y_min += teapot_1_dragY;teapot_1_y_max += teapot_1_dragY;
    
    teapot_1_boundingbox_vertex[0][0] = teapot_1_x_min; teapot_1_boundingbox_vertex[0][1] = teapot_1_y_max; teapot_1_boundingbox_vertex[0][2] = teapot_1_z_min;
    teapot_1_boundingbox_vertex[1][0] = teapot_1_x_max; teapot_1_boundingbox_vertex[1][1] = teapot_1_y_max; teapot_1_boundingbox_vertex[1][2] = teapot_1_z_min;
    teapot_1_boundingbox_vertex[2][0] = teapot_1_x_min; teapot_1_boundingbox_vertex[2][1] = teapot_1_y_min; teapot_1_boundingbox_vertex[2][2] = teapot_1_z_min;
    teapot_1_boundingbox_vertex[3][0] = teapot_1_x_max; teapot_1_boundingbox_vertex[3][1] = teapot_1_y_min; teapot_1_boundingbox_vertex[3][2] = teapot_1_z_min;
    teapot_1_boundingbox_vertex[4][0] = teapot_1_x_min; teapot_1_boundingbox_vertex[4][1] = teapot_1_y_max; teapot_1_boundingbox_vertex[4][2] = teapot_1_z_max;
    teapot_1_boundingbox_vertex[5][0] = teapot_1_x_max; teapot_1_boundingbox_vertex[5][1] = teapot_1_y_max; teapot_1_boundingbox_vertex[5][2] = teapot_1_z_max;
    teapot_1_boundingbox_vertex[6][0] = teapot_1_x_min; teapot_1_boundingbox_vertex[6][1] = teapot_1_y_min; teapot_1_boundingbox_vertex[6][2] = teapot_1_z_max;
    teapot_1_boundingbox_vertex[7][0] = teapot_1_x_max; teapot_1_boundingbox_vertex[7][1] = teapot_1_y_min; teapot_1_boundingbox_vertex[7][2] = teapot_1_z_max;
    
    // Teapot Mesh 2
    teapot_2_x_min = x_4_min;
    teapot_2_x_max = x_4_max;
    teapot_2_y_min = y_4_min;
    teapot_2_y_max = y_4_max;
    teapot_2_z_min = z_4_min;
    teapot_2_z_max = z_4_max;
    
    teapot_2_x_min = -x_4_max + transform_value_8_1[0];
    teapot_2_x_max = -x_4_min + transform_value_8_1[0];
    teapot_2_z_min = -z_4_max + transform_value_8_1[2];
    teapot_2_z_max = -z_4_min + transform_value_8_1[2];
    teapot_2_x_min += teapot_2_dragX;teapot_2_x_max += teapot_2_dragX;teapot_2_y_min += teapot_2_dragY;teapot_2_y_max += teapot_2_dragY;
    
    teapot_2_boundingbox_vertex[0][0] = teapot_2_x_min; teapot_2_boundingbox_vertex[0][1] = teapot_2_y_max; teapot_2_boundingbox_vertex[0][2] = teapot_2_z_min;
    teapot_2_boundingbox_vertex[1][0] = teapot_2_x_max; teapot_2_boundingbox_vertex[1][1] = teapot_2_y_max; teapot_2_boundingbox_vertex[1][2] = teapot_2_z_min;
    teapot_2_boundingbox_vertex[2][0] = teapot_2_x_min; teapot_2_boundingbox_vertex[2][1] = teapot_2_y_min; teapot_2_boundingbox_vertex[2][2] = teapot_2_z_min;
    teapot_2_boundingbox_vertex[3][0] = teapot_2_x_max; teapot_2_boundingbox_vertex[3][1] = teapot_2_y_min; teapot_2_boundingbox_vertex[3][2] = teapot_2_z_min;
    teapot_2_boundingbox_vertex[4][0] = teapot_2_x_min; teapot_2_boundingbox_vertex[4][1] = teapot_2_y_max; teapot_2_boundingbox_vertex[4][2] = teapot_2_z_max;
    teapot_2_boundingbox_vertex[5][0] = teapot_2_x_max; teapot_2_boundingbox_vertex[5][1] = teapot_2_y_max; teapot_2_boundingbox_vertex[5][2] = teapot_2_z_max;
    teapot_2_boundingbox_vertex[6][0] = teapot_2_x_min; teapot_2_boundingbox_vertex[6][1] = teapot_2_y_min; teapot_2_boundingbox_vertex[6][2] = teapot_2_z_max;
    teapot_2_boundingbox_vertex[7][0] = teapot_2_x_max; teapot_2_boundingbox_vertex[7][1] = teapot_2_y_min; teapot_2_boundingbox_vertex[7][2] = teapot_2_z_max;
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
    for (int i = 0; i<dragon_face_num; i++) {
       dragon_faceNormal[i][0] = crossProduct_x(dragon_vertex[dragon_face[i][0]], dragon_vertex[dragon_face[i][1]], dragon_vertex[dragon_face[i][2]]);
       dragon_faceNormal[i][1] = crossProduct_y(dragon_vertex[dragon_face[i][0]], dragon_vertex[dragon_face[i][1]], dragon_vertex[dragon_face[i][2]]);
       dragon_faceNormal[i][2] = crossProduct_z(dragon_vertex[dragon_face[i][0]], dragon_vertex[dragon_face[i][1]], dragon_vertex[dragon_face[i][2]]);
    }
    
    for (int i = 0; i<turtle_face_num; i++) {
        turtle_faceNormal[i][0] = crossProduct_x(turtle_vertex[turtle_face[i][0]], turtle_vertex[turtle_face[i][1]], turtle_vertex[turtle_face[i][2]]);
        turtle_faceNormal[i][1] = crossProduct_y(turtle_vertex[turtle_face[i][0]], turtle_vertex[turtle_face[i][1]], turtle_vertex[turtle_face[i][2]]);
        turtle_faceNormal[i][2] = crossProduct_z(turtle_vertex[turtle_face[i][0]], turtle_vertex[turtle_face[i][1]], turtle_vertex[turtle_face[i][2]]);
    }
    
    for (int i = 0; i<hand_face_num; i++) {
        hand_faceNormal[i][0] = crossProduct_x(hand_vertex[hand_face[i][0]], hand_vertex[hand_face[i][1]], hand_vertex[hand_face[i][2]]);
        hand_faceNormal[i][1] = crossProduct_y(hand_vertex[hand_face[i][0]], hand_vertex[hand_face[i][1]], hand_vertex[hand_face[i][2]]);
        hand_faceNormal[i][2] = crossProduct_z(hand_vertex[hand_face[i][0]], hand_vertex[hand_face[i][1]], hand_vertex[hand_face[i][2]]);
    }
    
    for (int i = 0; i<teapot_face_num; i++) {
        teapot_faceNormal[i][0] = crossProduct_x(teapot_vertex[teapot_face[i][0]], teapot_vertex[teapot_face[i][1]], teapot_vertex[teapot_face[i][2]]);
        teapot_faceNormal[i][1] = crossProduct_y(teapot_vertex[teapot_face[i][0]], teapot_vertex[teapot_face[i][1]], teapot_vertex[teapot_face[i][2]]);
        teapot_faceNormal[i][2] = crossProduct_z(teapot_vertex[teapot_face[i][0]], teapot_vertex[teapot_face[i][1]], teapot_vertex[teapot_face[i][2]]);
    }
}

void calvertexNormal(){
    
    for (int i =0; i<dragon_face_num; i++) {
        dragon_vertex_face_num[dragon_face[i][0]]++;
        dragon_vertex_face_num[dragon_face[i][1]]++;
        dragon_vertex_face_num[dragon_face[i][2]]++;
        dragon_vertex_face_index[dragon_face[i][0]][dragon_vertex_face_num[dragon_face[i][0]]-1] = i;
        dragon_vertex_face_index[dragon_face[i][1]][dragon_vertex_face_num[dragon_face[i][1]]-1] = i;
        dragon_vertex_face_index[dragon_face[i][2]][dragon_vertex_face_num[dragon_face[i][2]]-1] = i;
    }
    
    for (int i = 0; i<dragon_vertex_num; i++) {
        for (int j = 0; j<dragon_vertex_face_num[i]; j++) {
            dragon_sum[i][0] += dragon_faceNormal[dragon_vertex_face_index[i][j]][0];
            dragon_sum[i][1] += dragon_faceNormal[dragon_vertex_face_index[i][j]][1];
            dragon_sum[i][2] += dragon_faceNormal[dragon_vertex_face_index[i][j]][2];
        }
        dragon_vertexNoraml[i][0] = dragon_sum[i][0]/dragon_vertex_face_num[i];
        dragon_vertexNoraml[i][1] = dragon_sum[i][1]/dragon_vertex_face_num[i];
        dragon_vertexNoraml[i][2] = dragon_sum[i][2]/dragon_vertex_face_num[i];
    }
    
    for (int i =0; i<turtle_face_num; i++) {
        turtle_vertex_face_num[turtle_face[i][0]]++;
        turtle_vertex_face_num[turtle_face[i][1]]++;
        turtle_vertex_face_num[turtle_face[i][2]]++;
        turtle_vertex_face_index[turtle_face[i][0]][turtle_vertex_face_num[turtle_face[i][0]]-1] = i;
        turtle_vertex_face_index[turtle_face[i][1]][turtle_vertex_face_num[turtle_face[i][1]]-1] = i;
        turtle_vertex_face_index[turtle_face[i][2]][turtle_vertex_face_num[turtle_face[i][2]]-1] = i;
    }
    
    for (int i = 0; i<turtle_vertex_num; i++) {
        for (int j = 0; j<turtle_vertex_face_num[i]; j++) {
            turtle_sum[i][0] += turtle_faceNormal[turtle_vertex_face_index[i][j]][0];
            turtle_sum[i][1] += turtle_faceNormal[turtle_vertex_face_index[i][j]][1];
            turtle_sum[i][2] += turtle_faceNormal[turtle_vertex_face_index[i][j]][2];
        }
        turtle_vertexNoraml[i][0] = turtle_sum[i][0]/turtle_vertex_face_num[i];
        turtle_vertexNoraml[i][1] = turtle_sum[i][1]/turtle_vertex_face_num[i];
        turtle_vertexNoraml[i][2] = turtle_sum[i][2]/turtle_vertex_face_num[i];
    }
    
    for (int i =0; i<hand_face_num; i++) {
        hand_vertex_face_num[hand_face[i][0]]++;
        hand_vertex_face_num[hand_face[i][1]]++;
        hand_vertex_face_num[hand_face[i][2]]++;
        hand_vertex_face_index[hand_face[i][0]][hand_vertex_face_num[hand_face[i][0]]-1] = i;
        hand_vertex_face_index[hand_face[i][1]][hand_vertex_face_num[hand_face[i][1]]-1] = i;
        hand_vertex_face_index[hand_face[i][2]][hand_vertex_face_num[hand_face[i][2]]-1] = i;
    }
    
    for (int i = 0; i<hand_vertex_num; i++) {
        for (int j = 0; j<hand_vertex_face_num[i]; j++) {
            hand_sum[i][0] += hand_faceNormal[hand_vertex_face_index[i][j]][0];
            hand_sum[i][1] += hand_faceNormal[hand_vertex_face_index[i][j]][1];
            hand_sum[i][2] += hand_faceNormal[hand_vertex_face_index[i][j]][2];
        }
        hand_vertexNoraml[i][0] = hand_sum[i][0]/hand_vertex_face_num[i];
        hand_vertexNoraml[i][1] = hand_sum[i][1]/hand_vertex_face_num[i];
        hand_vertexNoraml[i][2] = hand_sum[i][2]/hand_vertex_face_num[i];
    }
    
    for (int i =0; i<teapot_face_num; i++) {
        teapot_vertex_face_num[teapot_face[i][0]]++;
        teapot_vertex_face_num[teapot_face[i][1]]++;
        teapot_vertex_face_num[teapot_face[i][2]]++;
        teapot_vertex_face_index[teapot_face[i][0]][teapot_vertex_face_num[teapot_face[i][0]]-1] = i;
        teapot_vertex_face_index[teapot_face[i][1]][teapot_vertex_face_num[teapot_face[i][1]]-1] = i;
        teapot_vertex_face_index[teapot_face[i][2]][teapot_vertex_face_num[teapot_face[i][2]]-1] = i;
    }
    
    for (int i = 0; i<teapot_vertex_num; i++) {
        for (int j = 0; j<teapot_vertex_face_num[i]; j++) {
            teapot_sum[i][0] += teapot_faceNormal[teapot_vertex_face_index[i][j]][0];
            teapot_sum[i][1] += teapot_faceNormal[teapot_vertex_face_index[i][j]][1];
            teapot_sum[i][2] += teapot_faceNormal[teapot_vertex_face_index[i][j]][2];
        }
        teapot_vertexNoraml[i][0] = teapot_sum[i][0]/teapot_vertex_face_num[i];
        teapot_vertexNoraml[i][1] = teapot_sum[i][1]/teapot_vertex_face_num[i];
        teapot_vertexNoraml[i][2] = teapot_sum[i][2]/teapot_vertex_face_num[i];
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
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (view_type == 2) {
        glOrtho(-350, 350, -320, 320, -750, 800);
    }
    if (view_type == 1) {
        gluPerspective(90, (GLfloat) winWidth /(GLfloat) winHeight, 10, 1850);
    }
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(navigation_x,navigation_y,navigation_z,0.0,0.0,-10000.0,0.0,1.0,0.0);
    
    // Draw Dragon
    glPushMatrix();
    glTranslated(dragon_1_dragX, dragon_1_dragY, 0);
    glTranslated(transform_value_1_1[0], transform_value_1_1[1], transform_value_1_1[2]);
    glBegin(GL_TRIANGLES);
    glColor4d(0.78, 0.62, 0.14, 0.00);
    for (int i = 0; i<dragon_face_num; i++) {
        glNormal3d(dragon_vertexNoraml[dragon_face[i][0]][0], dragon_vertexNoraml[dragon_face[i][0]][1], dragon_vertexNoraml[dragon_face[i][0]][2]);
        glVertex3d(dragon_vertex[dragon_face[i][0]][0], dragon_vertex[dragon_face[i][0]][1], dragon_vertex[dragon_face[i][0]][2]);
        glNormal3d(dragon_vertexNoraml[dragon_face[i][1]][0], dragon_vertexNoraml[dragon_face[i][1]][1], dragon_vertexNoraml[dragon_face[i][1]][2]);
        glVertex3d(dragon_vertex[dragon_face[i][1]][0], dragon_vertex[dragon_face[i][1]][1], dragon_vertex[dragon_face[i][1]][2]);
        glNormal3d(dragon_vertexNoraml[dragon_face[i][2]][0], dragon_vertexNoraml[dragon_face[i][2]][1], dragon_vertexNoraml[dragon_face[i][2]][2]);
        glVertex3d(dragon_vertex[dragon_face[i][2]][0], dragon_vertex[dragon_face[i][2]][1], dragon_vertex[dragon_face[i][2]][2]);
    }
    glEnd();
    glPopMatrix();
    
    glPushMatrix();
    glTranslated(dragon_2_dragX, dragon_2_dragY, 0);
    glTranslated(transform_value_2_1[0], transform_value_2_1[1], transform_value_2_1[2]);
    glRotated(transform_value_2_2[0], transform_value_2_2[1], transform_value_2_2[2], transform_value_2_2[3]);
    glBegin(GL_TRIANGLES);
    glColor4d(0.78, 0.62, 0.14, 0.00);
    for (int i = 0; i<dragon_face_num; i++) {
        glNormal3d(dragon_vertexNoraml[dragon_face[i][0]][0], dragon_vertexNoraml[dragon_face[i][0]][1], dragon_vertexNoraml[dragon_face[i][0]][2]);
        glVertex3d(dragon_vertex[dragon_face[i][0]][0], dragon_vertex[dragon_face[i][0]][1], dragon_vertex[dragon_face[i][0]][2]);
        glNormal3d(dragon_vertexNoraml[dragon_face[i][1]][0], dragon_vertexNoraml[dragon_face[i][1]][1], dragon_vertexNoraml[dragon_face[i][1]][2]);
        glVertex3d(dragon_vertex[dragon_face[i][1]][0], dragon_vertex[dragon_face[i][1]][1], dragon_vertex[dragon_face[i][1]][2]);
        glNormal3d(dragon_vertexNoraml[dragon_face[i][2]][0], dragon_vertexNoraml[dragon_face[i][2]][1], dragon_vertexNoraml[dragon_face[i][2]][2]);
        glVertex3d(dragon_vertex[dragon_face[i][2]][0], dragon_vertex[dragon_face[i][2]][1], dragon_vertex[dragon_face[i][2]][2]);
    }
    glEnd();
    glPopMatrix();
    
    // Draw Turtle
    glPushMatrix();
    glTranslated(turtle_1_dragX, turtle_1_dragY, 0);
    glTranslated(transform_value_3_1[0], transform_value_3_1[1], transform_value_3_1[2]);
    glRotated(transform_value_3_2[0], transform_value_3_2[1], transform_value_3_2[2], transform_value_3_2[3]);
    glBegin(GL_TRIANGLES);
    glColor4d(0.78, 0.62, 0.14, 0.00);
    for (int i = 0; i<turtle_face_num; i++) {
        glNormal3d(turtle_vertexNoraml[turtle_face[i][0]][0], turtle_vertexNoraml[turtle_face[i][0]][1], turtle_vertexNoraml[turtle_face[i][0]][2]);
        glVertex3d(turtle_vertex[turtle_face[i][0]][0], turtle_vertex[turtle_face[i][0]][1], turtle_vertex[turtle_face[i][0]][2]);
        glNormal3d(turtle_vertexNoraml[turtle_face[i][1]][0], turtle_vertexNoraml[turtle_face[i][1]][1], turtle_vertexNoraml[turtle_face[i][1]][2]);
        glVertex3d(turtle_vertex[turtle_face[i][1]][0], turtle_vertex[turtle_face[i][1]][1], turtle_vertex[turtle_face[i][1]][2]);
        glNormal3d(turtle_vertexNoraml[turtle_face[i][2]][0], turtle_vertexNoraml[turtle_face[i][2]][1], turtle_vertexNoraml[turtle_face[i][2]][2]);
        glVertex3d(turtle_vertex[turtle_face[i][2]][0], turtle_vertex[turtle_face[i][2]][1], turtle_vertex[turtle_face[i][2]][2]);
    }
    glEnd();
    glPopMatrix();
    
    glPushMatrix();
    glTranslated(turtle_2_dragX, turtle_2_dragY, 0);
    glTranslated(transform_value_4_1[0], transform_value_4_1[1], transform_value_4_1[2]);
    glRotated(transform_value_4_2[0], transform_value_4_2[1], transform_value_4_2[2], transform_value_4_2[3]);
    glBegin(GL_TRIANGLES);
    glColor4d(0.78, 0.62, 0.14, 0.00);
    for (int i = 0; i<turtle_face_num; i++) {
        glNormal3d(turtle_vertexNoraml[turtle_face[i][0]][0], turtle_vertexNoraml[turtle_face[i][0]][1], turtle_vertexNoraml[turtle_face[i][0]][2]);
        glVertex3d(turtle_vertex[turtle_face[i][0]][0], turtle_vertex[turtle_face[i][0]][1], turtle_vertex[turtle_face[i][0]][2]);
        glNormal3d(turtle_vertexNoraml[turtle_face[i][1]][0], turtle_vertexNoraml[turtle_face[i][1]][1], turtle_vertexNoraml[turtle_face[i][1]][2]);
        glVertex3d(turtle_vertex[turtle_face[i][1]][0], turtle_vertex[turtle_face[i][1]][1], turtle_vertex[turtle_face[i][1]][2]);
        glNormal3d(turtle_vertexNoraml[turtle_face[i][2]][0], turtle_vertexNoraml[turtle_face[i][2]][1], turtle_vertexNoraml[turtle_face[i][2]][2]);
        glVertex3d(turtle_vertex[turtle_face[i][2]][0], turtle_vertex[turtle_face[i][2]][1], turtle_vertex[turtle_face[i][2]][2]);
    }
    glEnd();
    glPopMatrix();

    // Draw Hand
    glPushMatrix();
    glTranslated(hand_1_dragX, hand_1_dragY, 0);
    glTranslated(transform_value_5_1[0], transform_value_5_1[1], transform_value_5_1[2]);
    glRotated(transform_value_5_2[0], transform_value_5_2[1], transform_value_5_2[2], transform_value_5_2[3]);
    glBegin(GL_TRIANGLES);
    glColor4d(0.78, 0.62, 0.14, 0.00);
    for (int i = 0; i<hand_face_num; i++) {
        glNormal3d(hand_vertexNoraml[hand_face[i][0]][0], hand_vertexNoraml[hand_face[i][0]][1], hand_vertexNoraml[hand_face[i][0]][2]);
        glVertex3d(hand_vertex[hand_face[i][0]][0], hand_vertex[hand_face[i][0]][1], hand_vertex[hand_face[i][0]][2]);
        glNormal3d(hand_vertexNoraml[hand_face[i][1]][0], hand_vertexNoraml[hand_face[i][1]][1], hand_vertexNoraml[hand_face[i][1]][2]);
        glVertex3d(hand_vertex[hand_face[i][1]][0], hand_vertex[hand_face[i][1]][1], hand_vertex[hand_face[i][1]][2]);
        glNormal3d(hand_vertexNoraml[hand_face[i][2]][0], hand_vertexNoraml[hand_face[i][2]][1], hand_vertexNoraml[hand_face[i][2]][2]);
        glVertex3d(hand_vertex[hand_face[i][2]][0], hand_vertex[hand_face[i][2]][1], hand_vertex[hand_face[i][2]][2]);
    }
    glEnd();
    glPopMatrix();
    
    glPushMatrix();
    glTranslated(hand_2_dragX, hand_2_dragY, 0);
    glTranslated(transform_value_6_1[0], transform_value_6_1[1], transform_value_6_1[2]);
    glRotated(transform_value_6_2[0], transform_value_6_2[1], transform_value_6_2[2], transform_value_6_2[3]);
    glBegin(GL_TRIANGLES);
    glColor4d(0.78, 0.62, 0.14, 0.00);
    for (int i = 0; i<hand_face_num; i++) {
        glNormal3d(hand_vertexNoraml[hand_face[i][0]][0], hand_vertexNoraml[hand_face[i][0]][1], hand_vertexNoraml[hand_face[i][0]][2]);
        glVertex3d(hand_vertex[hand_face[i][0]][0], hand_vertex[hand_face[i][0]][1], hand_vertex[hand_face[i][0]][2]);
        glNormal3d(hand_vertexNoraml[hand_face[i][1]][0], hand_vertexNoraml[hand_face[i][1]][1], hand_vertexNoraml[hand_face[i][1]][2]);
        glVertex3d(hand_vertex[hand_face[i][1]][0], hand_vertex[hand_face[i][1]][1], hand_vertex[hand_face[i][1]][2]);
        glNormal3d(hand_vertexNoraml[hand_face[i][2]][0], hand_vertexNoraml[hand_face[i][2]][1], hand_vertexNoraml[hand_face[i][2]][2]);
        glVertex3d(hand_vertex[hand_face[i][2]][0], hand_vertex[hand_face[i][2]][1], hand_vertex[hand_face[i][2]][2]);
    }
    glEnd();
    glPopMatrix();
    
    // Draw Teapot
    glPushMatrix();
    glTranslated(teapot_1_dragX, teapot_1_dragY, 0);
    glTranslated(transform_value_7_1[0], transform_value_7_1[1], transform_value_7_1[2]);
    glBegin(GL_TRIANGLES);
    glColor4d(0.78, 0.62, 0.14, 0.00);
    for (int i = 0; i<teapot_face_num; i++) {
        glNormal3d(teapot_vertexNoraml[teapot_face[i][0]][0], teapot_vertexNoraml[teapot_face[i][0]][1], teapot_vertexNoraml[teapot_face[i][0]][2]);
        glVertex3d(teapot_vertex[teapot_face[i][0]][0], teapot_vertex[teapot_face[i][0]][1], teapot_vertex[teapot_face[i][0]][2]);
        glNormal3d(teapot_vertexNoraml[teapot_face[i][1]][0], teapot_vertexNoraml[teapot_face[i][1]][1], teapot_vertexNoraml[teapot_face[i][1]][2]);
        glVertex3d(teapot_vertex[teapot_face[i][1]][0], teapot_vertex[teapot_face[i][1]][1], teapot_vertex[teapot_face[i][1]][2]);
        glNormal3d(teapot_vertexNoraml[teapot_face[i][2]][0], teapot_vertexNoraml[teapot_face[i][2]][1], teapot_vertexNoraml[teapot_face[i][2]][2]);
        glVertex3d(teapot_vertex[teapot_face[i][2]][0], teapot_vertex[teapot_face[i][2]][1], teapot_vertex[teapot_face[i][2]][2]);
    }
    glEnd();
    glPopMatrix();
    
    glPushMatrix();
    glTranslated(teapot_2_dragX, teapot_2_dragY, 0);
    glTranslated(transform_value_8_1[0], transform_value_8_1[1], transform_value_8_1[2]);
    glRotated(transform_value_8_2[0], transform_value_8_2[1], transform_value_8_2[2], transform_value_8_2[3]);
    glBegin(GL_TRIANGLES);
    glColor4d(0.78, 0.62, 0.14, 0.00);
    for (int i = 0; i<teapot_face_num; i++) {
        glNormal3d(teapot_vertexNoraml[teapot_face[i][0]][0], teapot_vertexNoraml[teapot_face[i][0]][1], teapot_vertexNoraml[teapot_face[i][0]][2]);
        glVertex3d(teapot_vertex[teapot_face[i][0]][0], teapot_vertex[teapot_face[i][0]][1], teapot_vertex[teapot_face[i][0]][2]);
        glNormal3d(teapot_vertexNoraml[teapot_face[i][1]][0], teapot_vertexNoraml[teapot_face[i][1]][1], teapot_vertexNoraml[teapot_face[i][1]][2]);
        glVertex3d(teapot_vertex[teapot_face[i][1]][0], teapot_vertex[teapot_face[i][1]][1], teapot_vertex[teapot_face[i][1]][2]);
        glNormal3d(teapot_vertexNoraml[teapot_face[i][2]][0], teapot_vertexNoraml[teapot_face[i][2]][1], teapot_vertexNoraml[teapot_face[i][2]][2]);
        glVertex3d(teapot_vertex[teapot_face[i][2]][0], teapot_vertex[teapot_face[i][2]][1], teapot_vertex[teapot_face[i][2]][2]);
    }
    glEnd();
    glPopMatrix();

    if (drawBox == 2) {
    // draw dragon 1 bounding box
    glColor4d(1.00, 0.00, 0.00, 0.9);
    glBegin(GL_LINE_LOOP);
    glVertex3d(dragon_1_boundingbox_vertex[0][0], dragon_1_boundingbox_vertex[0][1], dragon_1_boundingbox_vertex[0][2]);
    glVertex3d(dragon_1_boundingbox_vertex[1][0], dragon_1_boundingbox_vertex[1][1], dragon_1_boundingbox_vertex[1][2]);
    glVertex3d(dragon_1_boundingbox_vertex[3][0], dragon_1_boundingbox_vertex[3][1], dragon_1_boundingbox_vertex[3][2]);
    glVertex3d(dragon_1_boundingbox_vertex[2][0], dragon_1_boundingbox_vertex[2][1], dragon_1_boundingbox_vertex[2][2]);
    glEnd();
    
    glBegin(GL_LINE_LOOP);
    glVertex3d(dragon_1_boundingbox_vertex[4][0], dragon_1_boundingbox_vertex[4][1], dragon_1_boundingbox_vertex[4][2]);
    glVertex3d(dragon_1_boundingbox_vertex[5][0], dragon_1_boundingbox_vertex[5][1], dragon_1_boundingbox_vertex[5][2]);
    glVertex3d(dragon_1_boundingbox_vertex[7][0], dragon_1_boundingbox_vertex[7][1], dragon_1_boundingbox_vertex[7][2]);
    glVertex3d(dragon_1_boundingbox_vertex[6][0], dragon_1_boundingbox_vertex[6][1], dragon_1_boundingbox_vertex[6][2]);
    glEnd();
    
    glBegin(GL_LINE_LOOP);
    glVertex3d(dragon_1_boundingbox_vertex[4][0], dragon_1_boundingbox_vertex[4][1], dragon_1_boundingbox_vertex[4][2]);
    glVertex3d(dragon_1_boundingbox_vertex[6][0], dragon_1_boundingbox_vertex[6][1], dragon_1_boundingbox_vertex[6][2]);
    glVertex3d(dragon_1_boundingbox_vertex[2][0], dragon_1_boundingbox_vertex[2][1], dragon_1_boundingbox_vertex[2][2]);
    glVertex3d(dragon_1_boundingbox_vertex[0][0], dragon_1_boundingbox_vertex[0][1], dragon_1_boundingbox_vertex[0][2]);
    glEnd();
    
    glBegin(GL_LINE_LOOP);
    glVertex3d(dragon_1_boundingbox_vertex[5][0], dragon_1_boundingbox_vertex[5][1], dragon_1_boundingbox_vertex[5][2]);
    glVertex3d(dragon_1_boundingbox_vertex[7][0], dragon_1_boundingbox_vertex[7][1], dragon_1_boundingbox_vertex[7][2]);
    glVertex3d(dragon_1_boundingbox_vertex[3][0], dragon_1_boundingbox_vertex[3][1], dragon_1_boundingbox_vertex[3][2]);
    glVertex3d(dragon_1_boundingbox_vertex[1][0], dragon_1_boundingbox_vertex[1][1], dragon_1_boundingbox_vertex[1][2]);
    glEnd();
    
    glBegin(GL_LINE_LOOP);
    glVertex3d(dragon_1_boundingbox_vertex[0][0], dragon_1_boundingbox_vertex[0][1], dragon_1_boundingbox_vertex[0][2]);
    glVertex3d(dragon_1_boundingbox_vertex[1][0], dragon_1_boundingbox_vertex[1][1], dragon_1_boundingbox_vertex[1][2]);
    glVertex3d(dragon_1_boundingbox_vertex[5][0], dragon_1_boundingbox_vertex[5][1], dragon_1_boundingbox_vertex[5][2]);
    glVertex3d(dragon_1_boundingbox_vertex[4][0], dragon_1_boundingbox_vertex[4][1], dragon_1_boundingbox_vertex[4][2]);
    glEnd();
    
    glBegin(GL_LINE_LOOP);
    glVertex3d(dragon_1_boundingbox_vertex[6][0], dragon_1_boundingbox_vertex[6][1], dragon_1_boundingbox_vertex[6][2]);
    glVertex3d(dragon_1_boundingbox_vertex[7][0], dragon_1_boundingbox_vertex[7][1], dragon_1_boundingbox_vertex[7][2]);
    glVertex3d(dragon_1_boundingbox_vertex[3][0], dragon_1_boundingbox_vertex[3][1], dragon_1_boundingbox_vertex[3][2]);
    glVertex3d(dragon_1_boundingbox_vertex[2][0], dragon_1_boundingbox_vertex[2][1], dragon_1_boundingbox_vertex[2][2]);
    glEnd();
    
    // draw dragon 2 bounding box
    glColor4d(1.00, 0.00, 0.00, 0.9);
    glBegin(GL_LINE_LOOP);
    glVertex3d(dragon_2_boundingbox_vertex[0][0], dragon_2_boundingbox_vertex[0][1], dragon_2_boundingbox_vertex[0][2]);
    glVertex3d(dragon_2_boundingbox_vertex[1][0], dragon_2_boundingbox_vertex[1][1], dragon_2_boundingbox_vertex[1][2]);
    glVertex3d(dragon_2_boundingbox_vertex[3][0], dragon_2_boundingbox_vertex[3][1], dragon_2_boundingbox_vertex[3][2]);
    glVertex3d(dragon_2_boundingbox_vertex[2][0], dragon_2_boundingbox_vertex[2][1], dragon_2_boundingbox_vertex[2][2]);
    glEnd();
    
    glBegin(GL_LINE_LOOP);
    glVertex3d(dragon_2_boundingbox_vertex[4][0], dragon_2_boundingbox_vertex[4][1], dragon_2_boundingbox_vertex[4][2]);
    glVertex3d(dragon_2_boundingbox_vertex[5][0], dragon_2_boundingbox_vertex[5][1], dragon_2_boundingbox_vertex[5][2]);
    glVertex3d(dragon_2_boundingbox_vertex[7][0], dragon_2_boundingbox_vertex[7][1], dragon_2_boundingbox_vertex[7][2]);
    glVertex3d(dragon_2_boundingbox_vertex[6][0], dragon_2_boundingbox_vertex[6][1], dragon_2_boundingbox_vertex[6][2]);
    glEnd();
    
    glBegin(GL_LINE_LOOP);
    glVertex3d(dragon_2_boundingbox_vertex[4][0], dragon_2_boundingbox_vertex[4][1], dragon_2_boundingbox_vertex[4][2]);
    glVertex3d(dragon_2_boundingbox_vertex[6][0], dragon_2_boundingbox_vertex[6][1], dragon_2_boundingbox_vertex[6][2]);
    glVertex3d(dragon_2_boundingbox_vertex[2][0], dragon_2_boundingbox_vertex[2][1], dragon_2_boundingbox_vertex[2][2]);
    glVertex3d(dragon_2_boundingbox_vertex[0][0], dragon_2_boundingbox_vertex[0][1], dragon_2_boundingbox_vertex[0][2]);
    glEnd();
    
    glBegin(GL_LINE_LOOP);
    glVertex3d(dragon_2_boundingbox_vertex[5][0], dragon_2_boundingbox_vertex[5][1], dragon_2_boundingbox_vertex[5][2]);
    glVertex3d(dragon_2_boundingbox_vertex[7][0], dragon_2_boundingbox_vertex[7][1], dragon_2_boundingbox_vertex[7][2]);
    glVertex3d(dragon_2_boundingbox_vertex[3][0], dragon_2_boundingbox_vertex[3][1], dragon_2_boundingbox_vertex[3][2]);
    glVertex3d(dragon_2_boundingbox_vertex[1][0], dragon_2_boundingbox_vertex[1][1], dragon_2_boundingbox_vertex[1][2]);
    glEnd();
    
    glBegin(GL_LINE_LOOP);
    glVertex3d(dragon_2_boundingbox_vertex[0][0], dragon_2_boundingbox_vertex[0][1], dragon_2_boundingbox_vertex[0][2]);
    glVertex3d(dragon_2_boundingbox_vertex[1][0], dragon_2_boundingbox_vertex[1][1], dragon_2_boundingbox_vertex[1][2]);
    glVertex3d(dragon_2_boundingbox_vertex[5][0], dragon_2_boundingbox_vertex[5][1], dragon_2_boundingbox_vertex[5][2]);
    glVertex3d(dragon_2_boundingbox_vertex[4][0], dragon_2_boundingbox_vertex[4][1], dragon_2_boundingbox_vertex[4][2]);
    glEnd();
    
    glBegin(GL_LINE_LOOP);
    glVertex3d(dragon_2_boundingbox_vertex[6][0], dragon_2_boundingbox_vertex[6][1], dragon_2_boundingbox_vertex[6][2]);
    glVertex3d(dragon_2_boundingbox_vertex[7][0], dragon_2_boundingbox_vertex[7][1], dragon_2_boundingbox_vertex[7][2]);
    glVertex3d(dragon_2_boundingbox_vertex[3][0], dragon_2_boundingbox_vertex[3][1], dragon_2_boundingbox_vertex[3][2]);
    glVertex3d(dragon_2_boundingbox_vertex[2][0], dragon_2_boundingbox_vertex[2][1], dragon_2_boundingbox_vertex[2][2]);
    glEnd();
    
    // draw turtle 1 bounding box
    glColor4d(1.00, 0.00, 0.00, 0.9);
    glBegin(GL_LINE_LOOP);
    glVertex3d(turtle_1_boundingbox_vertex[0][0], turtle_1_boundingbox_vertex[0][1], turtle_1_boundingbox_vertex[0][2]);
    glVertex3d(turtle_1_boundingbox_vertex[1][0], turtle_1_boundingbox_vertex[1][1], turtle_1_boundingbox_vertex[1][2]);
    glVertex3d(turtle_1_boundingbox_vertex[3][0], turtle_1_boundingbox_vertex[3][1], turtle_1_boundingbox_vertex[3][2]);
    glVertex3d(turtle_1_boundingbox_vertex[2][0], turtle_1_boundingbox_vertex[2][1], turtle_1_boundingbox_vertex[2][2]);
    glEnd();
    
    glBegin(GL_LINE_LOOP);
    glVertex3d(turtle_1_boundingbox_vertex[4][0], turtle_1_boundingbox_vertex[4][1], turtle_1_boundingbox_vertex[4][2]);
    glVertex3d(turtle_1_boundingbox_vertex[5][0], turtle_1_boundingbox_vertex[5][1], turtle_1_boundingbox_vertex[5][2]);
    glVertex3d(turtle_1_boundingbox_vertex[7][0], turtle_1_boundingbox_vertex[7][1], turtle_1_boundingbox_vertex[7][2]);
    glVertex3d(turtle_1_boundingbox_vertex[6][0], turtle_1_boundingbox_vertex[6][1], turtle_1_boundingbox_vertex[6][2]);
    glEnd();
    
    glBegin(GL_LINE_LOOP);
    glVertex3d(turtle_1_boundingbox_vertex[4][0], turtle_1_boundingbox_vertex[4][1], turtle_1_boundingbox_vertex[4][2]);
    glVertex3d(turtle_1_boundingbox_vertex[6][0], turtle_1_boundingbox_vertex[6][1], turtle_1_boundingbox_vertex[6][2]);
    glVertex3d(turtle_1_boundingbox_vertex[2][0], turtle_1_boundingbox_vertex[2][1], turtle_1_boundingbox_vertex[2][2]);
    glVertex3d(turtle_1_boundingbox_vertex[0][0], turtle_1_boundingbox_vertex[0][1], turtle_1_boundingbox_vertex[0][2]);
    glEnd();
    
    glBegin(GL_LINE_LOOP);
    glVertex3d(turtle_1_boundingbox_vertex[5][0], turtle_1_boundingbox_vertex[5][1], turtle_1_boundingbox_vertex[5][2]);
    glVertex3d(turtle_1_boundingbox_vertex[7][0], turtle_1_boundingbox_vertex[7][1], turtle_1_boundingbox_vertex[7][2]);
    glVertex3d(turtle_1_boundingbox_vertex[3][0], turtle_1_boundingbox_vertex[3][1], turtle_1_boundingbox_vertex[3][2]);
    glVertex3d(turtle_1_boundingbox_vertex[1][0], turtle_1_boundingbox_vertex[1][1], turtle_1_boundingbox_vertex[1][2]);
    glEnd();
    
    glBegin(GL_LINE_LOOP);
    glVertex3d(turtle_1_boundingbox_vertex[0][0], turtle_1_boundingbox_vertex[0][1], turtle_1_boundingbox_vertex[0][2]);
    glVertex3d(turtle_1_boundingbox_vertex[1][0], turtle_1_boundingbox_vertex[1][1], turtle_1_boundingbox_vertex[1][2]);
    glVertex3d(turtle_1_boundingbox_vertex[5][0], turtle_1_boundingbox_vertex[5][1], turtle_1_boundingbox_vertex[5][2]);
    glVertex3d(turtle_1_boundingbox_vertex[4][0], turtle_1_boundingbox_vertex[4][1], turtle_1_boundingbox_vertex[4][2]);
    glEnd();
    
    glBegin(GL_LINE_LOOP);
    glVertex3d(turtle_1_boundingbox_vertex[6][0], turtle_1_boundingbox_vertex[6][1], turtle_1_boundingbox_vertex[6][2]);
    glVertex3d(turtle_1_boundingbox_vertex[7][0], turtle_1_boundingbox_vertex[7][1], turtle_1_boundingbox_vertex[7][2]);
    glVertex3d(turtle_1_boundingbox_vertex[3][0], turtle_1_boundingbox_vertex[3][1], turtle_1_boundingbox_vertex[3][2]);
    glVertex3d(turtle_1_boundingbox_vertex[2][0], turtle_1_boundingbox_vertex[2][1], turtle_1_boundingbox_vertex[2][2]);
    glEnd();
    
    // draw turtle 2 bounding box
    glColor4d(1.00, 0.00, 0.00, 0.9);
    glBegin(GL_LINE_LOOP);
    glVertex3d(turtle_2_boundingbox_vertex[0][0], turtle_2_boundingbox_vertex[0][1], turtle_2_boundingbox_vertex[0][2]);
    glVertex3d(turtle_2_boundingbox_vertex[1][0], turtle_2_boundingbox_vertex[1][1], turtle_2_boundingbox_vertex[1][2]);
    glVertex3d(turtle_2_boundingbox_vertex[3][0], turtle_2_boundingbox_vertex[3][1], turtle_2_boundingbox_vertex[3][2]);
    glVertex3d(turtle_2_boundingbox_vertex[2][0], turtle_2_boundingbox_vertex[2][1], turtle_2_boundingbox_vertex[2][2]);
    glEnd();
    
    glBegin(GL_LINE_LOOP);
    glVertex3d(turtle_2_boundingbox_vertex[4][0], turtle_2_boundingbox_vertex[4][1], turtle_2_boundingbox_vertex[4][2]);
    glVertex3d(turtle_2_boundingbox_vertex[5][0], turtle_2_boundingbox_vertex[5][1], turtle_2_boundingbox_vertex[5][2]);
    glVertex3d(turtle_2_boundingbox_vertex[7][0], turtle_2_boundingbox_vertex[7][1], turtle_2_boundingbox_vertex[7][2]);
    glVertex3d(turtle_2_boundingbox_vertex[6][0], turtle_2_boundingbox_vertex[6][1], turtle_2_boundingbox_vertex[6][2]);
    glEnd();
    
    glBegin(GL_LINE_LOOP);
    glVertex3d(turtle_2_boundingbox_vertex[4][0], turtle_2_boundingbox_vertex[4][1], turtle_2_boundingbox_vertex[4][2]);
    glVertex3d(turtle_2_boundingbox_vertex[6][0], turtle_2_boundingbox_vertex[6][1], turtle_2_boundingbox_vertex[6][2]);
    glVertex3d(turtle_2_boundingbox_vertex[2][0], turtle_2_boundingbox_vertex[2][1], turtle_2_boundingbox_vertex[2][2]);
    glVertex3d(turtle_2_boundingbox_vertex[0][0], turtle_2_boundingbox_vertex[0][1], turtle_2_boundingbox_vertex[0][2]);
    glEnd();
    
    glBegin(GL_LINE_LOOP);
    glVertex3d(turtle_2_boundingbox_vertex[5][0], turtle_2_boundingbox_vertex[5][1], turtle_2_boundingbox_vertex[5][2]);
    glVertex3d(turtle_2_boundingbox_vertex[7][0], turtle_2_boundingbox_vertex[7][1], turtle_2_boundingbox_vertex[7][2]);
    glVertex3d(turtle_2_boundingbox_vertex[3][0], turtle_2_boundingbox_vertex[3][1], turtle_2_boundingbox_vertex[3][2]);
    glVertex3d(turtle_2_boundingbox_vertex[1][0], turtle_2_boundingbox_vertex[1][1], turtle_2_boundingbox_vertex[1][2]);
    glEnd();
    
    glBegin(GL_LINE_LOOP);
    glVertex3d(turtle_2_boundingbox_vertex[0][0], turtle_2_boundingbox_vertex[0][1], turtle_2_boundingbox_vertex[0][2]);
    glVertex3d(turtle_2_boundingbox_vertex[1][0], turtle_2_boundingbox_vertex[1][1], turtle_2_boundingbox_vertex[1][2]);
    glVertex3d(turtle_2_boundingbox_vertex[5][0], turtle_2_boundingbox_vertex[5][1], turtle_2_boundingbox_vertex[5][2]);
    glVertex3d(turtle_2_boundingbox_vertex[4][0], turtle_2_boundingbox_vertex[4][1], turtle_2_boundingbox_vertex[4][2]);
    glEnd();
    
    glBegin(GL_LINE_LOOP);
    glVertex3d(turtle_2_boundingbox_vertex[6][0], turtle_2_boundingbox_vertex[6][1], turtle_2_boundingbox_vertex[6][2]);
    glVertex3d(turtle_2_boundingbox_vertex[7][0], turtle_2_boundingbox_vertex[7][1], turtle_2_boundingbox_vertex[7][2]);
    glVertex3d(turtle_2_boundingbox_vertex[3][0], turtle_2_boundingbox_vertex[3][1], turtle_2_boundingbox_vertex[3][2]);
    glVertex3d(turtle_2_boundingbox_vertex[2][0], turtle_2_boundingbox_vertex[2][1], turtle_2_boundingbox_vertex[2][2]);
    glEnd();
    
    // draw hand 1 bounding box
    glColor4d(1.00, 0.00, 0.00, 0.9);
    glBegin(GL_LINE_LOOP);
    glVertex3d(hand_1_boundingbox_vertex[0][0], hand_1_boundingbox_vertex[0][1], hand_1_boundingbox_vertex[0][2]);
    glVertex3d(hand_1_boundingbox_vertex[1][0], hand_1_boundingbox_vertex[1][1], hand_1_boundingbox_vertex[1][2]);
    glVertex3d(hand_1_boundingbox_vertex[3][0], hand_1_boundingbox_vertex[3][1], hand_1_boundingbox_vertex[3][2]);
    glVertex3d(hand_1_boundingbox_vertex[2][0], hand_1_boundingbox_vertex[2][1], hand_1_boundingbox_vertex[2][2]);
    glEnd();
    
    glBegin(GL_LINE_LOOP);
    glVertex3d(hand_1_boundingbox_vertex[4][0], hand_1_boundingbox_vertex[4][1], hand_1_boundingbox_vertex[4][2]);
    glVertex3d(hand_1_boundingbox_vertex[5][0], hand_1_boundingbox_vertex[5][1], hand_1_boundingbox_vertex[5][2]);
    glVertex3d(hand_1_boundingbox_vertex[7][0], hand_1_boundingbox_vertex[7][1], hand_1_boundingbox_vertex[7][2]);
    glVertex3d(hand_1_boundingbox_vertex[6][0], hand_1_boundingbox_vertex[6][1], hand_1_boundingbox_vertex[6][2]);
    glEnd();
    
    glBegin(GL_LINE_LOOP);
    glVertex3d(hand_1_boundingbox_vertex[4][0], hand_1_boundingbox_vertex[4][1], hand_1_boundingbox_vertex[4][2]);
    glVertex3d(hand_1_boundingbox_vertex[6][0], hand_1_boundingbox_vertex[6][1], hand_1_boundingbox_vertex[6][2]);
    glVertex3d(hand_1_boundingbox_vertex[2][0], hand_1_boundingbox_vertex[2][1], hand_1_boundingbox_vertex[2][2]);
    glVertex3d(hand_1_boundingbox_vertex[0][0], hand_1_boundingbox_vertex[0][1], hand_1_boundingbox_vertex[0][2]);
    glEnd();
    
    glBegin(GL_LINE_LOOP);
    glVertex3d(hand_1_boundingbox_vertex[5][0], hand_1_boundingbox_vertex[5][1], hand_1_boundingbox_vertex[5][2]);
    glVertex3d(hand_1_boundingbox_vertex[7][0], hand_1_boundingbox_vertex[7][1], hand_1_boundingbox_vertex[7][2]);
    glVertex3d(hand_1_boundingbox_vertex[3][0], hand_1_boundingbox_vertex[3][1], hand_1_boundingbox_vertex[3][2]);
    glVertex3d(hand_1_boundingbox_vertex[1][0], hand_1_boundingbox_vertex[1][1], hand_1_boundingbox_vertex[1][2]);
    glEnd();
    
    glBegin(GL_LINE_LOOP);
    glVertex3d(hand_1_boundingbox_vertex[0][0], hand_1_boundingbox_vertex[0][1], hand_1_boundingbox_vertex[0][2]);
    glVertex3d(hand_1_boundingbox_vertex[1][0], hand_1_boundingbox_vertex[1][1], hand_1_boundingbox_vertex[1][2]);
    glVertex3d(hand_1_boundingbox_vertex[5][0], hand_1_boundingbox_vertex[5][1], hand_1_boundingbox_vertex[5][2]);
    glVertex3d(hand_1_boundingbox_vertex[4][0], hand_1_boundingbox_vertex[4][1], hand_1_boundingbox_vertex[4][2]);
    glEnd();
    
    glBegin(GL_LINE_LOOP);
    glVertex3d(hand_1_boundingbox_vertex[6][0], hand_1_boundingbox_vertex[6][1], hand_1_boundingbox_vertex[6][2]);
    glVertex3d(hand_1_boundingbox_vertex[7][0], hand_1_boundingbox_vertex[7][1], hand_1_boundingbox_vertex[7][2]);
    glVertex3d(hand_1_boundingbox_vertex[3][0], hand_1_boundingbox_vertex[3][1], hand_1_boundingbox_vertex[3][2]);
    glVertex3d(hand_1_boundingbox_vertex[2][0], hand_1_boundingbox_vertex[2][1], hand_1_boundingbox_vertex[2][2]);
    glEnd();
    
    // draw hand 2 bounding box
    glColor4d(1.00, 0.00, 0.00, 0.9);
    glBegin(GL_LINE_LOOP);
    glVertex3d(hand_2_boundingbox_vertex[0][0], hand_2_boundingbox_vertex[0][1], hand_2_boundingbox_vertex[0][2]);
    glVertex3d(hand_2_boundingbox_vertex[1][0], hand_2_boundingbox_vertex[1][1], hand_2_boundingbox_vertex[1][2]);
    glVertex3d(hand_2_boundingbox_vertex[3][0], hand_2_boundingbox_vertex[3][1], hand_2_boundingbox_vertex[3][2]);
    glVertex3d(hand_2_boundingbox_vertex[2][0], hand_2_boundingbox_vertex[2][1], hand_2_boundingbox_vertex[2][2]);
    glEnd();
    
    glBegin(GL_LINE_LOOP);
    glVertex3d(hand_2_boundingbox_vertex[4][0], hand_2_boundingbox_vertex[4][1], hand_2_boundingbox_vertex[4][2]);
    glVertex3d(hand_2_boundingbox_vertex[5][0], hand_2_boundingbox_vertex[5][1], hand_2_boundingbox_vertex[5][2]);
    glVertex3d(hand_2_boundingbox_vertex[7][0], hand_2_boundingbox_vertex[7][1], hand_2_boundingbox_vertex[7][2]);
    glVertex3d(hand_2_boundingbox_vertex[6][0], hand_2_boundingbox_vertex[6][1], hand_2_boundingbox_vertex[6][2]);
    glEnd();
    
    glBegin(GL_LINE_LOOP);
    glVertex3d(hand_2_boundingbox_vertex[4][0], hand_2_boundingbox_vertex[4][1], hand_2_boundingbox_vertex[4][2]);
    glVertex3d(hand_2_boundingbox_vertex[6][0], hand_2_boundingbox_vertex[6][1], hand_2_boundingbox_vertex[6][2]);
    glVertex3d(hand_2_boundingbox_vertex[2][0], hand_2_boundingbox_vertex[2][1], hand_2_boundingbox_vertex[2][2]);
    glVertex3d(hand_2_boundingbox_vertex[0][0], hand_2_boundingbox_vertex[0][1], hand_2_boundingbox_vertex[0][2]);
    glEnd();
    
    glBegin(GL_LINE_LOOP);
    glVertex3d(hand_2_boundingbox_vertex[5][0], hand_2_boundingbox_vertex[5][1], hand_2_boundingbox_vertex[5][2]);
    glVertex3d(hand_2_boundingbox_vertex[7][0], hand_2_boundingbox_vertex[7][1], hand_2_boundingbox_vertex[7][2]);
    glVertex3d(hand_2_boundingbox_vertex[3][0], hand_2_boundingbox_vertex[3][1], hand_2_boundingbox_vertex[3][2]);
    glVertex3d(hand_2_boundingbox_vertex[1][0], hand_2_boundingbox_vertex[1][1], hand_2_boundingbox_vertex[1][2]);
    glEnd();
    
    glBegin(GL_LINE_LOOP);
    glVertex3d(hand_2_boundingbox_vertex[0][0], hand_2_boundingbox_vertex[0][1], hand_2_boundingbox_vertex[0][2]);
    glVertex3d(hand_2_boundingbox_vertex[1][0], hand_2_boundingbox_vertex[1][1], hand_2_boundingbox_vertex[1][2]);
    glVertex3d(hand_2_boundingbox_vertex[5][0], hand_2_boundingbox_vertex[5][1], hand_2_boundingbox_vertex[5][2]);
    glVertex3d(hand_2_boundingbox_vertex[4][0], hand_2_boundingbox_vertex[4][1], hand_2_boundingbox_vertex[4][2]);
    glEnd();
    
    glBegin(GL_LINE_LOOP);
    glVertex3d(hand_2_boundingbox_vertex[6][0], hand_2_boundingbox_vertex[6][1], hand_2_boundingbox_vertex[6][2]);
    glVertex3d(hand_2_boundingbox_vertex[7][0], hand_2_boundingbox_vertex[7][1], hand_2_boundingbox_vertex[7][2]);
    glVertex3d(hand_2_boundingbox_vertex[3][0], hand_2_boundingbox_vertex[3][1], hand_2_boundingbox_vertex[3][2]);
    glVertex3d(hand_2_boundingbox_vertex[2][0], hand_2_boundingbox_vertex[2][1], hand_2_boundingbox_vertex[2][2]);
    glEnd();
    
    // draw teapot 1 bounding box
    glColor4d(1.00, 0.00, 0.00, 0.9);
    glBegin(GL_LINE_LOOP);
    glVertex3d(teapot_1_boundingbox_vertex[0][0], teapot_1_boundingbox_vertex[0][1], teapot_1_boundingbox_vertex[0][2]);
    glVertex3d(teapot_1_boundingbox_vertex[1][0], teapot_1_boundingbox_vertex[1][1], teapot_1_boundingbox_vertex[1][2]);
    glVertex3d(teapot_1_boundingbox_vertex[3][0], teapot_1_boundingbox_vertex[3][1], teapot_1_boundingbox_vertex[3][2]);
    glVertex3d(teapot_1_boundingbox_vertex[2][0], teapot_1_boundingbox_vertex[2][1], teapot_1_boundingbox_vertex[2][2]);
    glEnd();
    
    glBegin(GL_LINE_LOOP);
    glVertex3d(teapot_1_boundingbox_vertex[4][0], teapot_1_boundingbox_vertex[4][1], teapot_1_boundingbox_vertex[4][2]);
    glVertex3d(teapot_1_boundingbox_vertex[5][0], teapot_1_boundingbox_vertex[5][1], teapot_1_boundingbox_vertex[5][2]);
    glVertex3d(teapot_1_boundingbox_vertex[7][0], teapot_1_boundingbox_vertex[7][1], teapot_1_boundingbox_vertex[7][2]);
    glVertex3d(teapot_1_boundingbox_vertex[6][0], teapot_1_boundingbox_vertex[6][1], teapot_1_boundingbox_vertex[6][2]);
    glEnd();
    
    glBegin(GL_LINE_LOOP);
    glVertex3d(teapot_1_boundingbox_vertex[4][0], teapot_1_boundingbox_vertex[4][1], teapot_1_boundingbox_vertex[4][2]);
    glVertex3d(teapot_1_boundingbox_vertex[6][0], teapot_1_boundingbox_vertex[6][1], teapot_1_boundingbox_vertex[6][2]);
    glVertex3d(teapot_1_boundingbox_vertex[2][0], teapot_1_boundingbox_vertex[2][1], teapot_1_boundingbox_vertex[2][2]);
    glVertex3d(teapot_1_boundingbox_vertex[0][0], teapot_1_boundingbox_vertex[0][1], teapot_1_boundingbox_vertex[0][2]);
    glEnd();
    
    glBegin(GL_LINE_LOOP);
    glVertex3d(teapot_1_boundingbox_vertex[5][0], teapot_1_boundingbox_vertex[5][1], teapot_1_boundingbox_vertex[5][2]);
    glVertex3d(teapot_1_boundingbox_vertex[7][0], teapot_1_boundingbox_vertex[7][1], teapot_1_boundingbox_vertex[7][2]);
    glVertex3d(teapot_1_boundingbox_vertex[3][0], teapot_1_boundingbox_vertex[3][1], teapot_1_boundingbox_vertex[3][2]);
    glVertex3d(teapot_1_boundingbox_vertex[1][0], teapot_1_boundingbox_vertex[1][1], teapot_1_boundingbox_vertex[1][2]);
    glEnd();
    
    glBegin(GL_LINE_LOOP);
    glVertex3d(teapot_1_boundingbox_vertex[0][0], teapot_1_boundingbox_vertex[0][1], teapot_1_boundingbox_vertex[0][2]);
    glVertex3d(teapot_1_boundingbox_vertex[1][0], teapot_1_boundingbox_vertex[1][1], teapot_1_boundingbox_vertex[1][2]);
    glVertex3d(teapot_1_boundingbox_vertex[5][0], teapot_1_boundingbox_vertex[5][1], teapot_1_boundingbox_vertex[5][2]);
    glVertex3d(teapot_1_boundingbox_vertex[4][0], teapot_1_boundingbox_vertex[4][1], teapot_1_boundingbox_vertex[4][2]);
    glEnd();
    
    glBegin(GL_LINE_LOOP);
    glVertex3d(teapot_1_boundingbox_vertex[6][0], teapot_1_boundingbox_vertex[6][1], teapot_1_boundingbox_vertex[6][2]);
    glVertex3d(teapot_1_boundingbox_vertex[7][0], teapot_1_boundingbox_vertex[7][1], teapot_1_boundingbox_vertex[7][2]);
    glVertex3d(teapot_1_boundingbox_vertex[3][0], teapot_1_boundingbox_vertex[3][1], teapot_1_boundingbox_vertex[3][2]);
    glVertex3d(teapot_1_boundingbox_vertex[2][0], teapot_1_boundingbox_vertex[2][1], teapot_1_boundingbox_vertex[2][2]);
    glEnd();
    
    // draw teapot 2 bounding box
    glColor4d(1.00, 0.00, 0.00, 0.9);
    glBegin(GL_LINE_LOOP);
    glVertex3d(teapot_2_boundingbox_vertex[0][0], teapot_2_boundingbox_vertex[0][1], teapot_2_boundingbox_vertex[0][2]);
    glVertex3d(teapot_2_boundingbox_vertex[1][0], teapot_2_boundingbox_vertex[1][1], teapot_2_boundingbox_vertex[1][2]);
    glVertex3d(teapot_2_boundingbox_vertex[3][0], teapot_2_boundingbox_vertex[3][1], teapot_2_boundingbox_vertex[3][2]);
    glVertex3d(teapot_2_boundingbox_vertex[2][0], teapot_2_boundingbox_vertex[2][1], teapot_2_boundingbox_vertex[2][2]);
    glEnd();
    
    glBegin(GL_LINE_LOOP);
    glVertex3d(teapot_2_boundingbox_vertex[4][0], teapot_2_boundingbox_vertex[4][1], teapot_2_boundingbox_vertex[4][2]);
    glVertex3d(teapot_2_boundingbox_vertex[5][0], teapot_2_boundingbox_vertex[5][1], teapot_2_boundingbox_vertex[5][2]);
    glVertex3d(teapot_2_boundingbox_vertex[7][0], teapot_2_boundingbox_vertex[7][1], teapot_2_boundingbox_vertex[7][2]);
    glVertex3d(teapot_2_boundingbox_vertex[6][0], teapot_2_boundingbox_vertex[6][1], teapot_2_boundingbox_vertex[6][2]);
    glEnd();
    
    glBegin(GL_LINE_LOOP);
    glVertex3d(teapot_2_boundingbox_vertex[4][0], teapot_2_boundingbox_vertex[4][1], teapot_2_boundingbox_vertex[4][2]);
    glVertex3d(teapot_2_boundingbox_vertex[6][0], teapot_2_boundingbox_vertex[6][1], teapot_2_boundingbox_vertex[6][2]);
    glVertex3d(teapot_2_boundingbox_vertex[2][0], teapot_2_boundingbox_vertex[2][1], teapot_2_boundingbox_vertex[2][2]);
    glVertex3d(teapot_2_boundingbox_vertex[0][0], teapot_2_boundingbox_vertex[0][1], teapot_2_boundingbox_vertex[0][2]);
    glEnd();
    
    glBegin(GL_LINE_LOOP);
    glVertex3d(teapot_2_boundingbox_vertex[5][0], teapot_2_boundingbox_vertex[5][1], teapot_2_boundingbox_vertex[5][2]);
    glVertex3d(teapot_2_boundingbox_vertex[7][0], teapot_2_boundingbox_vertex[7][1], teapot_2_boundingbox_vertex[7][2]);
    glVertex3d(teapot_2_boundingbox_vertex[3][0], teapot_2_boundingbox_vertex[3][1], teapot_2_boundingbox_vertex[3][2]);
    glVertex3d(teapot_2_boundingbox_vertex[1][0], teapot_2_boundingbox_vertex[1][1], teapot_2_boundingbox_vertex[1][2]);
    glEnd();
    
    glBegin(GL_LINE_LOOP);
    glVertex3d(teapot_2_boundingbox_vertex[0][0], teapot_2_boundingbox_vertex[0][1], teapot_2_boundingbox_vertex[0][2]);
    glVertex3d(teapot_2_boundingbox_vertex[1][0], teapot_2_boundingbox_vertex[1][1], teapot_2_boundingbox_vertex[1][2]);
    glVertex3d(teapot_2_boundingbox_vertex[5][0], teapot_2_boundingbox_vertex[5][1], teapot_2_boundingbox_vertex[5][2]);
    glVertex3d(teapot_2_boundingbox_vertex[4][0], teapot_2_boundingbox_vertex[4][1], teapot_2_boundingbox_vertex[4][2]);
    glEnd();
    
    glBegin(GL_LINE_LOOP);
    glVertex3d(teapot_2_boundingbox_vertex[6][0], teapot_2_boundingbox_vertex[6][1], teapot_2_boundingbox_vertex[6][2]);
    glVertex3d(teapot_2_boundingbox_vertex[7][0], teapot_2_boundingbox_vertex[7][1], teapot_2_boundingbox_vertex[7][2]);
    glVertex3d(teapot_2_boundingbox_vertex[3][0], teapot_2_boundingbox_vertex[3][1], teapot_2_boundingbox_vertex[3][2]);
    glVertex3d(teapot_2_boundingbox_vertex[2][0], teapot_2_boundingbox_vertex[2][1], teapot_2_boundingbox_vertex[2][2]);
    glEnd();
    }
    
    glutSwapBuffers();
}

void mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {

        GLint newX = x - winWidth/2;
        GLint newY = winHeight/2 - y;
    
        GLint moveX = newX - navigation_x;
        GLint moveY = newY - navigation_y;
    
        navigation_x += 0.5*moveX;
        navigation_z -= 0.5*moveY;
        if ((navigation_x<=dragon_1_x_max&&navigation_x>=dragon_1_x_min&&navigation_z<=dragon_1_z_max&&navigation_z>=dragon_1_z_min)
            ||(navigation_x<=dragon_2_x_max&&navigation_x>=dragon_2_x_min&&navigation_z<=dragon_2_z_max&&navigation_z>=dragon_2_z_min)
            ||(navigation_x<=turtle_1_x_max&&navigation_x>=turtle_1_x_min&&navigation_z<=turtle_1_z_max&&navigation_z>=turtle_1_z_min)
            ||(navigation_x<=turtle_2_x_max&&navigation_x>=turtle_2_x_min&&navigation_z<=turtle_2_z_max&&navigation_z>=turtle_2_z_min)
            ||(navigation_x<=hand_1_x_max&&navigation_x>=hand_1_x_min&&navigation_z<=hand_1_z_max&&navigation_z>=hand_1_z_min)
            ||(navigation_x<=hand_2_x_max&&navigation_x>=hand_2_x_min&&navigation_z<=hand_2_z_max&&navigation_z>=hand_2_z_min)
            ||(navigation_x<=teapot_1_x_max&&navigation_x>=teapot_1_x_min&&navigation_z<=teapot_1_z_max&&navigation_z>=teapot_1_z_min)
            ||(navigation_x<=teapot_2_x_max&&navigation_x>=teapot_2_x_min&&navigation_z<=teapot_2_z_max&&navigation_z>=teapot_2_z_min)) {
            navigation_x -= 0.5*moveX;
            navigation_z += 0.5*moveY;
        }
    }
    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
        if (x<=396+dragon_1_dragX&&x>=341+dragon_1_dragX&&y<=460+dragon_1_dragY&&y>=412+dragon_1_dragY) {
            dragon_1_drag=2;
        }
        if (x<=677&&x>=605&&y<=448&&y>=405) {
            dragon_2_drag=2;
        }
        if (x<=475&&x>=450&&y<=403&&y>=389) {
            turtle_1_drag=2;
        }
        if (x<=556&&x>=534&&y<=400&&y>=390) {
            turtle_2_drag=2;
        }
        if (x<=287&&x>=222&&y<=532&&y>=278) {
            hand_1_drag=2;
        }
        if (x<=755&&x>=698&&y<=525&&y>=288) {
            hand_2_drag=2;
        }
        if (x<=420&&x>=315&&y<=390&&y>=305) {
            teapot_1_drag=2;
        }
        if (x<=690&&x>=509&&y<=379&&y>=310) {
            teapot_2_drag=2;
        }
        currentX=x;
        currentY=winHeight/2-y;
    }
    if (button == GLUT_RIGHT_BUTTON && state == GLUT_UP) {
        dragon_1_drag=1;dragon_2_drag=1;turtle_1_drag=1;turtle_2_drag=1;hand_1_drag=1;hand_2_drag=1;teapot_1_drag=1;teapot_2_drag=1;
    }
    glutPostRedisplay();
}

void mouseMove(int x, int y)
{
	if (dragon_1_drag==2)
	{
        dragon_1_dragX = x - currentX;
        dragon_1_dragY = winHeight/2 - y - currentY;
        boxBound();
        glutPostRedisplay();
	}
    if (dragon_2_drag==2)
	{
        dragon_2_dragX = x - currentX;
        dragon_2_dragY = winHeight/2 - y - currentY;
        boxBound();
        glutPostRedisplay();
	}
    if (turtle_1_drag==2)
	{
        turtle_1_dragX = x - currentX;
        turtle_1_dragY = winHeight/2 - y - currentY;
        boxBound();
        glutPostRedisplay();
	}
    if (turtle_2_drag==2)
	{
        turtle_2_dragX = x - currentX;
        turtle_2_dragY = winHeight/2 - y - currentY;
        boxBound();
        glutPostRedisplay();
	}
    if (hand_1_drag==2)
	{
        hand_1_dragX = x - currentX;
        hand_1_dragY = winHeight/2 - y - currentY;
        boxBound();
        glutPostRedisplay();
	}
    if (hand_2_drag==2)
	{
        hand_2_dragX = x - currentX;
        hand_2_dragY = winHeight/2 - y - currentY;
        boxBound();
        glutPostRedisplay();
	}
    if (teapot_1_drag==2)
	{
        teapot_1_dragX = x - currentX;
        teapot_1_dragY = winHeight/2 - y - currentY;
        boxBound();
        glutPostRedisplay();
	}
    if (teapot_2_drag==2)
	{
        teapot_2_dragX = x - currentX;
        teapot_2_dragY = winHeight/2 - y - currentY;
        boxBound();
        glutPostRedisplay();
	}
}

void keyboard(unsigned char key, int x, int y){
    switch (key) {
        case 'w':
            if (navigation_z-30<=dragon_1_z_max&&navigation_z-30>=dragon_1_z_min&&navigation_x-10<=dragon_1_x_max&&navigation_x-10>=dragon_1_x_min) {
                break;
            }
            if (navigation_z-30<=dragon_2_z_max&&navigation_z-30>=dragon_2_z_min&&navigation_x-10<=dragon_2_x_max&&navigation_x-10>=dragon_2_x_min) {
                break;
            }
            if (navigation_z-30<=turtle_1_z_max&&navigation_z-30>=turtle_1_z_min&&navigation_x-10<=turtle_1_x_max&&navigation_x-10>=turtle_1_x_min) {
                break;
            }
            if (navigation_z-30<=turtle_2_z_max&&navigation_z-30>=turtle_2_z_min&&navigation_x-10<=turtle_2_x_max&&navigation_x-10>=turtle_2_x_min) {
                break;
            }
            if (navigation_z-30<=hand_1_z_max&&navigation_z-30>=hand_1_z_min&&navigation_x-10<=hand_1_x_max&&navigation_x+10>=hand_1_x_min) {
                break;
            }
            if (navigation_z-30<=hand_2_z_max&&navigation_z-30>=hand_2_z_min&&navigation_x-10<=hand_2_x_max&&navigation_x-10>=hand_2_x_min) {
                break;
            }
            if (navigation_z-30<=teapot_1_z_max&&navigation_z-30>=teapot_1_z_min&&navigation_x-10<=teapot_1_x_max&&navigation_x-10>=teapot_1_x_min) {
                break;
            }
            if (navigation_z-30<=teapot_2_z_max&&navigation_z-30>=teapot_2_z_min&&navigation_x-10<=teapot_2_x_max&&navigation_x-10>=teapot_2_x_min) {
                break;
            }
            navigation_z -= 20;
            break;
        case 's':
            if (navigation_z+10>=dragon_1_z_min&&navigation_z+10<=dragon_1_z_max&&navigation_x-10<=dragon_1_x_max&&navigation_x-10>=dragon_1_x_min) {
                break;
            }
            if (navigation_z+10>=dragon_2_z_min&&navigation_z+10<=dragon_2_z_max&&navigation_x-10<=dragon_2_x_max&&navigation_x-10>=dragon_2_x_min) {
                break;
            }
            if (navigation_z+10>=turtle_1_z_min&&navigation_z+10<=turtle_1_z_max&&navigation_x-10<=turtle_1_x_max&&navigation_x-10>=turtle_1_x_min) {
                break;
            }
            if (navigation_z+10>=turtle_2_z_min&&navigation_z+10<=turtle_2_z_max&&navigation_x-10<=turtle_2_x_max&&navigation_x-10>=turtle_2_x_min) {
                break;
            }
            if (navigation_z+10>=hand_1_z_min&&navigation_z+10<=hand_1_z_max&&navigation_x-10<=hand_1_x_max&&navigation_x-10>=hand_1_x_min) {
                break;
            }
            if (navigation_z+10>=hand_2_z_min&&navigation_z+10<=hand_2_z_max&&navigation_x-10<=hand_2_x_max&&navigation_x-10>=hand_2_x_min) {
                break;
            }
            if (navigation_z+10>=teapot_1_z_min&&navigation_z+10<=teapot_1_z_max&&navigation_x-10<=teapot_1_x_max&&navigation_x-10>=teapot_1_x_min) {
                break;
            }
            if (navigation_z+10>=teapot_2_z_min&&navigation_z+10<=teapot_2_z_max&&navigation_x-10<=teapot_2_x_max&&navigation_x-10>=teapot_2_x_min) {
                break;
            }
            navigation_z += 20;
            break;
        case 'a':
            if (navigation_x-25<=dragon_1_x_max&&navigation_x-25>=dragon_1_x_min&&navigation_z-10<=dragon_1_z_max&&navigation_z-10>=dragon_1_z_min) {
                break;
            }
            if (navigation_x-25<=dragon_2_x_max&&navigation_x-25>=dragon_2_x_min&&navigation_z-10<=dragon_2_z_max&&navigation_z-10>=dragon_2_z_min) {
                break;
            }
            if (navigation_x-25<=turtle_1_x_max&&navigation_x-25>=turtle_1_x_min&&navigation_z-10<=turtle_1_z_max&&navigation_z-10>=turtle_1_z_min) {
                break;
            }
            if (navigation_x-25<=turtle_2_x_max&&navigation_x-25>=turtle_2_x_min&&navigation_z-10<=turtle_2_z_max&&navigation_z-10>=turtle_2_z_min) {
                break;
            }
            if (navigation_x-25<=hand_1_x_max&&navigation_x-25>=hand_1_x_min&&navigation_z-10<=hand_1_z_max&&navigation_z-10>=hand_1_z_min) {
                break;
            }
            if (navigation_x-25<=hand_2_x_max&&navigation_x-25>=hand_2_x_min&&navigation_z-10<=hand_2_z_max&&navigation_z-10>=hand_2_z_min) {
                break;
            }
            if (navigation_x-25<=teapot_1_x_max&&navigation_x-25>=teapot_1_x_min&&navigation_z-10<=teapot_1_z_max&&navigation_z-10>=teapot_1_z_min) {
                break;
            }
            if (navigation_x-25<=teapot_2_x_max&&navigation_x-25>=teapot_2_x_min&&navigation_z-10<=teapot_2_z_max&&navigation_z-10>=teapot_2_z_min) {
                break;
            }
            navigation_x -= 15;
            break;
        case 'd':
            if (navigation_x+25>=dragon_1_x_min&&navigation_x+25<=dragon_1_x_max&&navigation_z-10<=dragon_1_z_max&&navigation_z-10>=dragon_1_z_min) {
                break;
            }
            if (navigation_x+25>=dragon_2_x_min&&navigation_x+25<=dragon_2_x_max&&navigation_z-10<=dragon_2_z_max&&navigation_z-10>=dragon_2_z_min) {
                break;
            }
            if (navigation_x+25>=turtle_1_x_min&&navigation_x+25<=turtle_1_x_max&&navigation_z-10<=turtle_1_z_max&&navigation_z-10>=turtle_1_z_min) {
                break;
            }
            if (navigation_x+25>=turtle_2_x_min&&navigation_x+25<=turtle_2_x_max&&navigation_z-10<=turtle_2_z_max&&navigation_z-10>=turtle_2_z_min) {
                break;
            }
            if (navigation_x+25>=hand_1_x_min&&navigation_x+25<=hand_1_x_max&&navigation_z-10<=hand_1_z_max&&navigation_z-10>=hand_1_z_min) {
                break;
            }
            if (navigation_x+25>=hand_2_x_min&&navigation_x+25<=hand_2_x_max&&navigation_z-10<=hand_2_z_max&&navigation_z-10>=hand_2_z_min) {
                break;
            }
            if (navigation_x+25>=teapot_1_x_min&&navigation_x+25<=teapot_1_x_max&&navigation_z-10<=teapot_1_z_max&&navigation_z-10>=teapot_1_z_min) {
                break;
            }
            if (navigation_x+25>=teapot_2_x_min&&navigation_x+25<=teapot_2_x_max&&navigation_z-10<=teapot_2_z_max&&navigation_z-10>=teapot_2_z_min) {
                break;
            }
            navigation_x += 15;
            break;
        case 'p':
            view_type = 1;
            break;
        case 'o':
            view_type = 2;
            break;
        case 'b':
            drawBox = 2;
            break;
        case 'h':
            drawBox = 1;
            break;
        case 27:  /*  Escape key  */
            exit(0);
            break;
    }
    glutPostRedisplay();
}

void initGLUT(int *argcp, char *argv[])
{
    glutInit(argcp, argv);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(winWidth, winHeight);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    glutCreateWindow(argv[0]);
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(mouseMove);
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
    
    prejob();
    
    glutMainLoop();
    return 0;
}