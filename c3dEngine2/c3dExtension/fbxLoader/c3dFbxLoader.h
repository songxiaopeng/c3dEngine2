#ifndef _c3dFbxLoader__
#define _c3dFbxLoader__
#include <string>
using namespace std;
#include "c3dSkinActor.h"
#include "c3dFbxOneLoad.h"

class Cc3dFbxLoader{
public:
	static Cc3dFbxLoader*sharedFbxLoader();
	Cc3dSkinActor*load(string fbxFilePath);
};
#endif