#include <string>
#include "Heightmap.h"
#include "debug.h"
#include <glm/gtc/noise.hpp>
#include "modules/noise3d.hpp"

// PRIVATE UTILS //////////////////////////////////////////////////////

struct Index
{
	Index(GLfloat *d, const sf::Image& s) : data(d), currentIndex(0), scale(0.1f), src(s) {}
	GLfloat *const data;
	GLfloat scale;
	int currentIndex;
	const sf::Image& src;

	void operator()(GLfloat x, GLfloat y)
	{
		// On lit le rouge, ça n'a pas d'importance car le fichier est censé être en nuance de gris
		GLfloat z = src.getPixel(x, y).r / 255.0f;
		x -= 300;
		//y += 100;

		data[currentIndex++] = x * scale;
		data[currentIndex++] = z * 700.4f;
		data[currentIndex++] = -y * scale;
	}
};

///////////////////////////////////////////////////////////////////////

Heightmap::Heightmap():
    sizeX(1), sizeY(1), vao(0), vbo(0), dtaSize(0)
{
}

Heightmap::~Heightmap()
{
}
#include <iostream>
bool Heightmap::loadFromFile(const char* file)
{
	if(!src.loadFromFile(file))
	{
		return false;
	}

	Perlin3D p;
	const int S = 1024;
	src.create(S, S);

	for(int i = 0; i < S; i++)
	{
		for(int j = 0; j < S; j++)
		{
			unsigned char r = (unsigned char)(255.0f * ((p.getNoise(i, j, 0))));
			src.setPixel(i, j, sf::Color(r, r, r));
		}
	}

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    const int nbCoords(3), nbVertex(3), nbTriangles(2);
    const int sideX(src.getSize().x - 1), sideY(src.getSize().y - 1);
	dtaSize = nbCoords * nbVertex * nbTriangles * sideX * sideY;
    GLfloat *dta = new GLfloat[dtaSize];
	Index put_coord(dta, src);

	debug("heightmap %ix%i\n", sideX, sideY);

    for(int y = 0; y < sideY; ++y)
    {
		for(int x = 0; x < sideX; ++x)
		{
			//Even triangle
			put_coord(x, y);
			put_coord(x+1, y);
			put_coord(x, y+1);

			//Odd triangle
			put_coord(x+1, y);
			put_coord(x+1, y+1);
			put_coord(x, y+1);
		}
    }

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, dtaSize * sizeof(GLfloat), dta, GL_STATIC_DRAW);
    delete[] dta;

	return true;
}

void Heightmap::draw()
{
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glDrawArrays(GL_TRIANGLES, 0, dtaSize);
    glDisableVertexAttribArray(0);
}

void Heightmap::setSize(float x, float y)
{
    sizeX = x;
    sizeY = y;
}
