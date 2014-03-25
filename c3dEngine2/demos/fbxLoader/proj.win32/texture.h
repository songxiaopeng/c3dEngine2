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
	vector<GLuint> textureList;//�洢����
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
		//ɾ������
		int ntex=textureList.size();
		for(int i=0;i<ntex;i++){
			if(textureList[i]!=0)glDeleteTextures(1,&textureList[i]);
		}
		//�б����
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
	GLuint genTexture(){//���һ��������������������������ͨ���˺�����ã��Ա�֤����¼��manager��
		GLuint texture=0;
		glGenTextures(1, &texture);
		if(texture==0){
			cout<<"glGenTexturesʧ��!"<<endl;
			system("pause");
		}
		textureList.push_back(texture);
		return texture;
	}
	GLuint CreateTexture(char*filename,
		GLint fliterMIN=GL_NEAREST_MIPMAP_NEAREST,
		GLint fliterMAG=GL_LINEAR)
		//��������
		//��������ɹ����ͽ�����ӵ�textureList�����򲻼���
		//ǰ�˷��ش����õ�������
	{
		//--------------------------------------------------------
		//���Ƚ�filename���ص��ڴ��TextureImage��,
		//Ȼ��TextureImage������GPU������texture��
		//--------------------------------------------------------
		//����λͼ��ָ�����TextureImage
		AUX_RGBImageRec *TextureImage=LoadBMP(filename);
		if (TextureImage!=NULL)
		{
			//���1������������texture
			GLuint texture=genTexture();//texture�Ѽ��뵽textureList
			//��texture������ǰ2d����
			glBindTexture(GL_TEXTURE_2D, texture);
			glPixelStorei(GL_UNPACK_ALIGNMENT,1);//�˺���ʹ��bmpͼƬ����4��������Ҳ��������ʾ
			//Ϊ��ǰ����������*TextureImage��
			gluBuild2DMipmaps(GL_TEXTURE_2D, 3, TextureImage->sizeX, TextureImage->sizeY, GL_RGB, GL_UNSIGNED_BYTE, TextureImage->data);
			//��������������ͼ�����˲�
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,fliterMIN);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,fliterMAG);
			//����TextureImage���������ٴ���ժ��nehe�̳̣�Ӧ�ϱ��գ�
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
		if (eno!=0){//���ɹ�
			return NULL;           // If Load Failed Return NULL
		}else{//�ɹ�
			fclose(File);          // Close The Handle
			//��Filename(char*)תΪLPCWSTR
			WCHAR Filename_wcstr[MAX_PATH];
			MultiByteToWideChar(0,0,Filename,-1,Filename_wcstr,MAX_PATH);
			return auxDIBImageLoad(Filename_wcstr);     // Load The Bitmap And Return A Pointer
		}
		
	}
	
	
};

#endif