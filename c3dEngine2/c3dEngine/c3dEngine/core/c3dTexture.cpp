//
//  c3dTexture.cpp
//  HelloOpenGL
//
//  Created by wantnon (yang chao) on 14-2-20.
//
//

#include "core/c3dTexture.h"
#if (C3D_TARGET_PLATFORM == C3D_PLATFORM_WIN32)
#include "platform/win32/c3dTexturePlatformDepend.h"
#else
#include "platform/iOS/c3dTexturePlatformDepend.h"
#endif
bool Cc3dTexture::initDepthTexture(int width,int height,int wrapS,int wrapT,GLint minFilter,GLint magFilter)
//note, if used as target of render to texture, then wrapS and wrapT should be GL_CLAMP_TO_EDGE
{
    assert(m_texture==0);
    m_width=width;
    m_height=height;
    glGenTextures(1, &m_texture);
    glBindTexture(GL_TEXTURE_2D, m_texture);
    //GL_NEAREST,GL_LINEAR
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);
    //
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,wrapS);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,wrapT);
    //note, for depth texture
    //            1, use GL_DEPTH_COMPONENT, not GL_DEPTH_COMPONENT16
    //            2, use GL_UNSIGNED_INT, not GL_UNSIGNED_BYTE
    glTexImage2D( GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT,m_width, m_height, 0,
                 GL_DEPTH_COMPONENT,GL_UNSIGNED_INT, NULL);
    glBindTexture(GL_TEXTURE_2D, 0);
    
    C3DCHECK_GL_ERROR_DEBUG();
    return true;
}

bool Cc3dTexture::initColorTexture(int width,int height,int wrapS,int wrapT,GLint minFilter,GLint magFilter)
//note, if used as target of render to texture, then wrapS and wrapT should be GL_CLAMP_TO_EDGE
{
    assert(m_texture==0);
    m_width=width;
    m_height=height;
    glGenTextures(1, &m_texture);
    glBindTexture(GL_TEXTURE_2D, m_texture);
    //GL_NEAREST或GL_LINEAR
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);
    //
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapS);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapT);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    glBindTexture(GL_TEXTURE_2D, 0);
    C3DCHECK_GL_ERROR_DEBUG();
    return true;
}

bool Cc3dTexture::init(const string&filePath,int wrapS,int wrapT,GLint minFilter,GLint magFilter)
{
    GLuint texture;
	
    float width,height;
    texture=createGLTexture_plat(filePath,wrapS,wrapT,minFilter,magFilter,width,height);
	//cout<<"texture ID:"<<texture<<endl;
    //
    m_texture=texture;
    m_width=width;
    m_height=height;
    m_filePath=filePath;
    
    return true;

}