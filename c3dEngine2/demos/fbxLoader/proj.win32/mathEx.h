#include<iostream>
using namespace std;
#include "myh.h"
#include <math.h>


void printv(float v[4]);

int rem(int a,int b);
void init4(float vec[4],float x,float y,float z,float w);
void init2(float v[2],float x,float y);

float getLen_2(const float v[4]);
void sub(const float (&v1)[4],const float (&v2)[4],float (&vrs)[4]);
void add(const float v1[4],const float v2[4],float vrs[4]);
void addadd(const float v1[4],const float v2[4],const float v3[4],float vrs[4]);
float dot(const float v1[4],const float v2[4]);
void mul(float k,const float v[4],float vrs[4]);
void mulAdd(const float k,const float v1[4],const float v2[4],float vrs[4]);
void mul_mat(float k,float mat[16]);

void add_mat(float a[16],float b[16],float rs[16]);
float normalize(float v[4]);
void matcopy( const float src[16],float tg[16]);
void veccopy(const float vec[4],float tgvec[4]);
void cross(float v1[4], float v2[4], float result[4]);
void makeE(float m[16]);

void prodv_wOne(const float matrix[16], const float in[4],float out[4]);



void neg(const float v[4],float vrs[4]);