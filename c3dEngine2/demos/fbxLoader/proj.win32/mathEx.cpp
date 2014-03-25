#include "mathEx.h"


void printv(float v[4]){
	cout<<v[X]<<" "<<v[Y]<<" "<<v[Z]<<endl;
}

int rem(int a,int b){//比"%"更合逻辑的取余运算
	int r=a%b;
	if(r<0)return r+b;
	else return r;
}
void init4(float vec[4],float x,float y,float z,float w){
	vec[0]=x;
	vec[1]=y;
	vec[2]=z;
	vec[3]=w;
}
void init2(float v[2],float x,float y){
	v[0]=x;
	v[1]=y;
}

float getLen_2(const float v[4]){//返回模的平方
	return v[0]*v[0]+v[1]*v[1]+v[2]*v[2];
}
void sub(const float (&v1)[4],const float (&v2)[4],float (&vrs)[4]){
	vrs[0]=v1[0]-v2[0];
	vrs[1]=v1[1]-v2[1];
	vrs[2]=v1[2]-v2[2];
	vrs[3]=v1[3]-v2[3];
}
void add(const float v1[4],const float v2[4],float vrs[4]){
	vrs[0]=v1[0]+v2[0];
	vrs[1]=v1[1]+v2[1];
	vrs[2]=v1[2]+v2[2];
	vrs[3]=v1[3]+v2[3];

}
void addadd(const float v1[4],const float v2[4],const float v3[4],float vrs[4]){
	vrs[0]=v1[0]+v2[0]+v3[0];
	vrs[1]=v1[1]+v2[1]+v3[1];
	vrs[2]=v1[2]+v2[2]+v3[2];
	vrs[3]=v1[3]+v2[3]+v3[3];
}
float dot(const float v1[4],const float v2[4]){
	return v1[X]*v2[X]+v1[Y]*v2[Y]+v1[Z]*v2[Z];

}
void mul(float k,const float v[4],float vrs[4]){
	vrs[0]=v[0]*k;
	vrs[1]=v[1]*k;
	vrs[2]=v[2]*k;
	vrs[3]=v[3]*k;
}
void mulAdd(const float k,const float v1[4],const float v2[4],float vrs[4])
//vrs=k*v1+v2
//此函数很有意义，适应现代cpu能将乘和加合并成一条指令的特点
//等以后有机会将以前没有使用此函数的部分逐渐改成使用此函数
{
	vrs[0]=k*v1[0]+v2[0];
	vrs[1]=k*v1[1]+v2[1];
	vrs[2]=k*v1[2]+v2[2];
	vrs[3]=k*v1[3]+v2[3];

}
void mul_mat(float k,float mat[16]){
	for(int i=0;i<=15;i++){
	mat[i]*=k;
	}
}

void add_mat(float a[16],float b[16],float rs[16]){
	for(int i=0;i<=15;i++){
		rs[i]=a[i]+b[i];
	}

}
float normalize(float v[4]){//精确单位化

    float r2=v[0]*v[0] + v[1]*v[1] + v[2]*v[2];
	if(r2==0.0)return 0;
	float r=sqrt(r2);
    v[0] /=r;
    v[1] /=r;
    v[2] /=r;
	return r;

}
void matcopy( const float src[16],float tg[16])
{
	memcpy(tg,src,sizeof(float)*16);	
}
void veccopy(const float vec[4],float tgvec[4]){
	tgvec[X]=vec[X];
	tgvec[Y]=vec[Y];
	tgvec[Z]=vec[Z];
	tgvec[W]=vec[W];
	//如果用memcpy，则会报warning: warning C4789: destination of memory copy is too small
	//因此或许对于此种规模较小的情况用直接逐个赋值更快
}
void cross(float v1[4], float v2[4], float result[4])
{
    result[0] = v1[1]*v2[2] - v1[2]*v2[1];
    result[1] = v1[2]*v2[0] - v1[0]*v2[2];
    result[2] = v1[0]*v2[1] - v1[1]*v2[0];
	result[3] = 0;//因为叉乘结果必是向量，所以第四维为0
}
void makeE(float m[16])
{
	m[0] = 1; m[4] = 0; m[8] = 0; m[12] = 0;
    m[1] = 0; m[5] = 1; m[9] = 0; m[13] = 0;
    m[2] = 0; m[6] = 0; m[10] = 1; m[14] = 0;
    m[3] = 0; m[7] = 0; m[11] = 0; m[15] = 1;
}


void prodv_wOne(const float matrix[16], const float in[4],
		      float out[4]){//in和out可以是同一数组
	float _out[4];//临时中转
	_out[0]=in[0]*matrix[0]+in[1]*matrix[4]+in[2]*matrix[8]+matrix[12];
	_out[1]=in[0]*matrix[1]+in[1]*matrix[5]+in[2]*matrix[9]+matrix[13];
	_out[2]=in[0]*matrix[2]+in[1]*matrix[6]+in[2]*matrix[10]+matrix[14];
	_out[3]=in[0]*matrix[3]+in[1]*matrix[7]+in[2]*matrix[11]+matrix[15];
	out[0]=_out[0];
	out[1]=_out[1];
	out[2]=_out[2];
	out[3]=_out[3];
}

int inv_general(const float src[16], float inverse[16])
//一般4*4矩阵求逆
//两者可为同一矩阵
{
    int i, j, k, swap;
    float t;
    float temp[4][4];

    for (i=0; i<4; i++) {
	for (j=0; j<4; j++) {
	    temp[i][j] = src[i*4+j];
	}
    }
    makeE(inverse);

    for (i = 0; i < 4; i++) {
	/*
	** Look for largest element in column
	*/
	swap = i;
	for (j = i + 1; j < 4; j++) {
	    if (fabs(temp[j][i]) > fabs(temp[i][i])) {
		swap = j;
	    }
	}

	if (swap != i) {
	    /*
	    ** Swap rows.
	    */
	    for (k = 0; k < 4; k++) {
		t = temp[i][k];
		temp[i][k] = temp[swap][k];
		temp[swap][k] = t;

		t = inverse[i*4+k];
		inverse[i*4+k] = inverse[swap*4+k];
		inverse[swap*4+k] = t;
	    }
	}

	if (temp[i][i] == 0) {
	    /*
	    ** No non-zero pivot.  The matrix is singular, which shouldn't
	    ** happen.  This means the user gave us a bad matrix.
	    */
	    return GL_FALSE;
	}

	t = temp[i][i];
	for (k = 0; k < 4; k++) {
	    temp[i][k] /= t;
	    inverse[i*4+k] /= t;
	}
	for (j = 0; j < 4; j++) {
	    if (j != i) {
		t = temp[j][i];
		for (k = 0; k < 4; k++) {
		    temp[j][k] -= temp[i][k]*t;
		    inverse[j*4+k] -= inverse[i*4+k]*t;
		}
	    }
	}
    }
    return GL_TRUE;
}


void neg(const float v[4],float vrs[4]){
	vrs[0]=-v[0];
	vrs[1]=-v[1];
	vrs[2]=-v[2];
	vrs[3]=-v[3];
}