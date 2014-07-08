//
//  c3dTexturePlatformDepend.h
//  HelloOpenGL
//
//  Created by wantnon (yang chao) on 14-3-9.
//
//

#ifndef __HelloOpenGL__c3dTexturePlatformDepend__
#define __HelloOpenGL__c3dTexturePlatformDepend__

#include <iostream>
using namespace std;
#include "core/c3dGLdebug.h"

typedef enum {

    //! 32-bit texture: RGBA8888
    kCCTexture2DPixelFormat_RGBA8888,
    //! 24-bit texture: RGBA888
    kCCTexture2DPixelFormat_RGB888,
    //! 16-bit texture without Alpha channel
    kCCTexture2DPixelFormat_RGB565,
    //! 8-bit textures used as masks
    kCCTexture2DPixelFormat_A8,
    //! 8-bit intensity texture
    kCCTexture2DPixelFormat_I8,
    //! 16-bit textures used as masks
    kCCTexture2DPixelFormat_AI88,
    //! 16-bit textures: RGBA4444
    kCCTexture2DPixelFormat_RGBA4444,
    //! 16-bit textures: RGB5A1
    kCCTexture2DPixelFormat_RGB5A1,    
    //! 4-bit PVRTC-compressed texture: PVRTC4
    kCCTexture2DPixelFormat_PVRTC4,
    //! 2-bit PVRTC-compressed texture: PVRTC2
    kCCTexture2DPixelFormat_PVRTC2,


    //! Default texture format: RGBA8888
    kCCTexture2DPixelFormat_Default = kCCTexture2DPixelFormat_RGBA8888,

    // backward compatibility stuff
    kTexture2DPixelFormat_RGBA8888 = kCCTexture2DPixelFormat_RGBA8888,
    kTexture2DPixelFormat_RGB888 = kCCTexture2DPixelFormat_RGB888,
    kTexture2DPixelFormat_RGB565 = kCCTexture2DPixelFormat_RGB565,
    kTexture2DPixelFormat_A8 = kCCTexture2DPixelFormat_A8,
    kTexture2DPixelFormat_RGBA4444 = kCCTexture2DPixelFormat_RGBA4444,
    kTexture2DPixelFormat_RGB5A1 = kCCTexture2DPixelFormat_RGB5A1,
    kTexture2DPixelFormat_Default = kCCTexture2DPixelFormat_Default

} CCTexture2DPixelFormat;

GLuint createGLTexture_plat(const string&filePath,int wrapS,int wrapT,GLint minFilter,GLint magFilter,
                           float&textureWidth,float&textureHeight);
unsigned char*  getImageData_plat(const string&filePath,CCTexture2DPixelFormat&_pixelFormat,float&_imageWidth,float&_imageHeight);
#endif /* defined(__HelloOpenGL__c3dTexturePlatformDepend__) */
