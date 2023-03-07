//
//  objet.cpp
//  space shuttle
//
//  Created by Nurjol Badyelkhan on 2021/12/16.
//

#include "objet.hpp"
#include "bmpfuncs.h"

GLuint* texShuttle = new GLuint();
void shuttleTextureMapping(void){
    glGenTextures(3, texShuttle);

    glBindTexture(GL_TEXTURE_2D, *texShuttle);
    int width,height,channels;
    unsigned char* img=readImageData("/Users/bmbi/Desktop/spaceship/env/shuttletex.bmp",&width,&height,&channels);
        

    glTexImage2D(GL_TEXTURE_2D,0,3,width,height,0,GL_RGB,GL_UNSIGNED_BYTE,img);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
}
void myObject :: loadObj()
{
    std::ifstream fp;
    fp.open (nomdufichier, std::ifstream::in);
    std::string line;
    GLfloat x, y, z;
    Triplet stockv; //triplet à push_back dans le vecteur
    Paire stockt; //paire à push_back dans le vecteur
    int ilim; //taille du vertex
    GLuint elephant;
    elephant=glGenLists(1);
    if (!fp.is_open())
    {
        printf("can't open file \n");
        exit(1);
    }

    glNewList(elephant, GL_COMPILE);
    {
        glPushMatrix();
        while(!fp.eof())
        {
            getline (fp,line);
            if (line.substr(0,2) == "v ")
            {
                line[0] = ' ';
                sscanf(line.c_str(), "%f %f %f", &x, &y, &z);
                stockv.x = x;
                stockv.y = y;
                stockv.z = z;
                vertex.push_back(stockv);
                ilim = vertex.size();
//                printf("vertex[%d]: %f, %f, %f\n",ilim-1, vertex[ilim-1].x,vertex[ilim-1].y,vertex[ilim-1].z);
//                
            }

            if (line.substr(0,2) =="vn")
            {
                line[0] = ' ';
                line[1]=' ';
                sscanf(line.c_str(), "%f %f %f", &x, &y, &z);
                stockv.x = x;
                stockv.y = y;
                stockv.z = z;
                normales.push_back(stockv);
            }

            if (line.substr(0,2) =="vt")
            {
                line[0] = ' ';
                line[1] = ' ';
                sscanf(line.c_str(), "%f %f", &x, &y);
                stockt.x = x;
                stockt.y = y;
                vtextures.push_back(stockt);
            }
        }
        
    }
    glPopMatrix();
    glEndList();
    fp.close();
}
myObject :: myObject( std::string fname)
{
    nomdufichier=fname;

}

GLvoid myObject :: dispObj()
{
    std::ifstream fp;
    fp.open (nomdufichier, std::ifstream::in);
    std::string line;
    int po1,tex1,nor1,po2,tex2,nor2,po3,tex3,nor3;
    if (!fp.is_open())
    {
        printf("can't open file \n");
        exit(1);
    }
    shuttleTextureMapping();
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
     while(!fp.eof())
        {
            getline (fp,line);
            if (line.substr(0,2) == "f ")
            {
                line[0] = ' ';
                sscanf(line.c_str(), "%d/%d/%d%d/%d/%d%d/%d/%d", &po1,&tex1,&nor1,&po2,&tex2,&nor2,&po3,&tex3,&nor3);
                
//                printf("f %d/%d/%d%d/%d/%d%d/%d/%d\n", po1,tex1,nor1,po2,tex2,nor2,po3,tex3,nor3);
                po1--;
                tex1--;
                nor1--;
                po2--;
                tex2--;
                nor2--;
                po3--;
                tex3--;
                nor3--;
                

        
                
                
                glBegin(GL_TRIANGLES);
                {
                    
                   glTexCoord2d(vtextures[tex1].x,vtextures[tex1].y);
                    glVertex3f(vertex[po1].x,vertex[po1].y,vertex[po1].z);
                   
                    glNormal3f(normales[nor1].x,normales[nor1].y,normales[nor1].z);

                   glTexCoord2d(vtextures[tex2].x,vtextures[tex2].y);
                    glVertex3f(vertex[po2].x,vertex[po2].y,vertex[po2].z);
                   
                   glNormal3f(normales[nor2].x,normales[nor2].y,normales[nor2].z);

                   glTexCoord2d(vtextures[tex3].x,vtextures[tex3].y);
                    glVertex3f(vertex[po3].x,vertex[po3].y,vertex[po3].z);
                
                   glNormal3f(normales[nor3].x,normales[nor3].y,normales[nor3].z);
                }
                glEnd();
                
            }
            glFlush();
            
        }


    fp.close();
}
