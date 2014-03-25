//
//  userConfig.h
//  HelloOpenGL
//
//  Created by wantnon (yang chao) on 13-1-31.
//
//

#ifndef __HelloOpenGL__userConfig__
#define __HelloOpenGL__userConfig__

#include <iostream>
#include <string>
#include <vector>
using namespace std;
#include "c3dDocuments.h"
#include "c3dCommonFunc.h"

class CuserConfig//用户设置
{
public:
    static CuserConfig*sharedUserConfig();
    vector<bool> unLockList;//解锁列表
    vector<int> starNumberList;//星星数列表
    CuserConfig(){
        
    }
    int get_levelCount()const{
         return (int)unLockList.size();
     }
    bool getIsConfigFileExistInDocuments(const string&fileName);
    void copyConfigFileToDocuments(const string&filePath);
    void writeToConfigFileInDocuments(const string&filePath);
    void loadConfigFileFromDocuments(const string&fileNameWithExt);

};
#endif /* defined(__HelloOpenGL__userConfig__) */
