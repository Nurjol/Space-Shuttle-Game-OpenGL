//
//  objet.hpp
//  space shuttle
//
//  Created by Nurjol Badyelkhan on 2021/12/16.
//

#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/freeglut.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include "bmpfuncs.hpp"


struct Triplet
{
        float x,y,z;
};

struct Paire
{
    float x,y;
};

class myObject {
private :
    std::vector<Triplet> vertex;
    std::vector<Triplet> normales;
    std::vector<Paire> vtextures;
    std::string nomdufichier;

public :
    myObject(std::string filename);
    GLvoid loadObj (); //charge les vecteurs de points normales et textures
    GLvoid dispObj ();//affiche les faces et textures
    

};
