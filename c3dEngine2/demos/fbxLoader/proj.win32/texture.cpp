#include "texture.h"

static CTextureManager*s_textureManager=NULL;
CTextureManager* CTextureManager::sharedTextureManager(){
	if(s_textureManager==NULL){
		s_textureManager=new CTextureManager();
	}
	return s_textureManager;
}