# Space-Shuttle-Game-OpenGL
Using OpenGL C++ making space shuttle game( 50% done) on Visual Stduio Community. Main idea of the game is avoid obstacles and successfully go to Earth. By passing obstacles speed will increase.  
Currently I made 5 object:
  -Earth (drawn and wrapped with texture) 
  -Moon (drawn and wrapped with texture) 
  -Environment stars (drawn and wrapped with texture) 
  -Dock (drawn and wrapped with texture) 
  -Space ship (created by blender and imported .obj file) + texture mapped 
  
  
For the future: 
  - animate environment (shuttle going forward effect)
  - make obstacles to avoid (meteors, different planets, etc...)
  - make point system.
  
  
  example screenshot:
![shuttle](https://user-images.githubusercontent.com/65017142/223376404-e436bee6-e3a9-45eb-9cd5-0eedb7b2b48a.png)

Requirements:
  -install freeglut
  -install glew (add and link library to VSC)
  -set x64 and set Solution Configuration Debug-> Release 
  -Check loading file paths are correct
  -if there are errors prevent from loading please write #define _CRT_SECURE_NO_WARNINGS 
