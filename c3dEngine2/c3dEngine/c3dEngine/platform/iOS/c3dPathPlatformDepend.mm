//
//  c3dPathPlatformDepend.cpp
//  HelloOpenGL
//
//  Created by wantnon (yang chao) on 14-3-9.
//
//

#include "c3dPathPlatformDepend.h"
//note: the getFullPath_plat function require the folderNames not contain dot character!
string getFullPath_plat(const string&filePath){
    string fileName;//文件名
    string ext;//后缀
    vector<string> rs=splitStrInTwoByLastDot(filePath);
    fileName=rs[0];
    ext=rs[1];
    NSString *fileName_NS=[[[NSString alloc] initWithUTF8String:fileName.c_str()] autorelease];
    NSString *ext_NS=[[[NSString alloc] initWithUTF8String:ext.c_str()] autorelease];
    NSString* fullPath_NS;
    if((int)ext.size()==0){
        fullPath_NS= [[NSBundle mainBundle] pathForResource:fileName_NS ofType:nil];
    }else{
        fullPath_NS= [[NSBundle mainBundle] pathForResource:fileName_NS ofType:ext_NS];
    }
    if(fullPath_NS==nil){
        cout<<"error: got nil fullPath, the path may be out of bundle. is it in ios Documents?"<<endl;
        assert(false);
    }
    string fullPath=[fullPath_NS cStringUsingEncoding:NSASCIIStringEncoding];
    return fullPath;
}
bool isFileExistsAtPath_plat(const string&path){
    NSString *path_NS=[[[NSString alloc] initWithUTF8String:path.c_str()] autorelease];
    bool isExist =  [[NSFileManager defaultManager] fileExistsAtPath:path_NS];
    return isExist;
}
