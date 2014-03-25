#ifndef _texture_H
#define _texture_H
#include <vector>
#include <iostream>
using namespace std;
#include <GL/glew.h>

#include <gl\gl.h>
#include "glext.h"
#include "gl/glaux.h"
#pragma comment (lib,"glaux.lib")


class CTextureManager{
private:
	vector<GLuint> textureList;//存储纹理
public:
	CTextureManager(){
	}
	~CTextureManager(){
		destroy();

	}
	static CTextureManager*sharedTextureManager();
	int getTexCount()const{
		return (int)textureList.size();
	}
	void destroy(){
		//删除纹理
		int ntex=textureList.size();
		for(int i=0;i<ntex;i++){
			if(textureList[i]!=0)glDeleteTextures(1,&textureList[i]);
		}
		//列表清空
		textureList.clear();


	}
	void printTextureList(){
		cout<<"textureList: ";
		for(int i=0;i<(int)textureList.size();i++){
			cout<<textureList[i]<<" ";
		}cout<<endl;
	}
	GLuint getLastTex(){
		return textureList[(int)textureList.size()-1];
	}
	GLuint genTexture(){//获得一个纹理句柄，所有纹理句柄都必须通过此函数获得，以保证被记录到manager中
		GLuint texture=0;
		glGenTextures(1, &texture);
		if(texture==0){
			cout<<"glGenTextures失败!"<<endl;
			system("pause");
		}
		textureList.push_back(texture);
		return texture;
	}
	GLuint CreateTexture(char*filename,
		GLint fliterMIN=GL_NEAREST_MIPMAP_NEAREST,
		GLint fliterMAG=GL_LINEAR)
		//创建纹理
		//如果创建成功，就将纹理加到textureList，否则不加入
		//前端返回创建好的纹理句柄
	{
		//--------------------------------------------------------
		//首先将filename加载到内存的TextureImage中,
		//然后将TextureImage拷贝到GPU缓冲区texture中
		//--------------------------------------------------------
		//加载位图，指针存入TextureImage
		AUX_RGBImageRec *TextureImage=LoadBMP(filename);
		if (TextureImage!=NULL)
		{
			//获得1个纹理句柄存入texture
			GLuint texture=genTexture();//texture已加入到textureList
			//将texture用作当前2d纹理
			glBindTexture(GL_TEXTURE_2D, texture);
			glPixelStorei(GL_UNPACK_ALIGNMENT,1);//此函数使得bmp图片不是4的整数倍也能正常显示
			//为当前纹理创建（用*TextureImage）
			gluBuild2DMipmaps(GL_TEXTURE_2D, 3, TextureImage->sizeX, TextureImage->sizeY, GL_RGB, GL_UNSIGNED_BYTE, TextureImage->data);
			//对所创建的纹理图进行滤波
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,fliterMIN);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,fliterMAG);
			//销毁TextureImage（下面销毁代码摘自nehe教程，应较保险）
			if (TextureImage)									// If Texture Exists
			{
				if (TextureImage->data)							// If Texture Image Exists
				{
					free(TextureImage->data);					// Free The Texture Image Memory
				}
				
				free(TextureImage);								// Free The Image Structure
			}
			return texture;
			
		}else{
			cout<<"texture failed: "<<filename<<endl;
			return 0;
		}
	}
private:
	AUX_RGBImageRec *LoadBMP(char* Filename){     // Loads A Bitmap Image
		FILE *File=NULL;          // File Handle
		if (!Filename){           // Make Sure A Filename Was Given
			return NULL;          // If Not Return NULL
		}
		errno_t eno=fopen_s(&File,Filename,"r");        // Check To See If The File Exists
		if (eno!=0){//不成功
			return NULL;           // If Load Failed Return NULL
		}else{//成功
			fclose(File);          // Close The Handle
			//将Filename(char*)转为LPCWSTR
			WCHAR Filename_wcstr[MAX_PATH];
			MultiByteToWideChar(0,0,Filename,-1,Filename_wcstr,MAX_PATH);
			return auxDIBImageLoad(Filename_wcstr);     // Load The Bitmap And Return A Pointer
		}
		
	}
	
	
};

#endif