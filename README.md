c3dEngine2
==========  
  
![screenshot](http://git.oschina.net/wantnon2/c3dEngine2/raw/master/screenshot/logo.png)    
  
by wantnon (yang chao) 2014-4-1  
  
c3dEngine2 is a cocos2d-x-like simple 3d game engine. it is the upgrade version of c3dEngine.  
  
support platform: iOS, win32  
language: c++  
  
c3dEngine2 is the upgrade version of c3dEngine.(c3dEngine, see: http://git.oschina.net/wantnon2/c3dEngine-superSingleCell or https://github.com/wantnon2/superSingleCell-c3dEngine )   
  
as i think c3dEngine is not very good in some aspects, so i am trying to make a better one. i will write a series of small samples to show each feature of the engine, and at the same time, refine the engine.  
now, the project is just start, so there is very few samples. but i will add more later.        
  
document:  
you can temporarily refer to the old version document, main concepts are same:   
http://git.oschina.net/wantnon2/c3dEngine-superSingleCell/wikis/home  
  
How to run the project:  
for iOS project, open .xcodeproj with Xcode and run.  
for win32 project:  
1, install OpenAL: run OpenAL11CoreSDK.exe under OpenAL_install folder.  
2, open .sln with vs2010 and run (suggest to run under release mode).   
i mainly debug under release mode, so sometimes may forget to configure the debug mode --!  
  
possible issues and solution:  
assert failure on windows xp: http://git.oschina.net/wantnon2/c3dEngine2/issues/1  
  
i will update code to http://git.oschina.net/wantnon2/c3dEngine2.git and https://github.com/wantnon2/c3dEngine2, the former is the main site.     
  
qq group: 338565878  
  
screenshot:  
draw a simple box  
![screenshot](http://git.oschina.net/wantnon2/c3dEngine2/raw/master/screenshot/screenshot1.png)  
fbx skin animation and convert fbx to user-defined format  
![screenshot](http://git.oschina.net/wantnon2/c3dEngine2/raw/master/screenshot/screenshot2.png)  
quadtree LOD terrain   
![screenshot](http://git.oschina.net/wantnon2/c3dEngine2/raw/master/screenshot/screenshot3.png)  
bullet integration  
![screenshot](http://git.oschina.net/wantnon2/c3dEngine2/raw/master/screenshot/screenshot4.png)  
a whole game: super single cell  
![screenshot](http://git.oschina.net/wantnon2/c3dEngine2/raw/master/screenshot/screenshot5.png)  