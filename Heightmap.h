#ifndef HEIGHTMAP
#define HEIGHTMAP

#include "glutils.h"
#include <SFML/Graphics.hpp>

class Heightmap
{
public:
	Heightmap();
	~Heightmap();

	bool loadFromFile(const char* file);
	void draw();
	void setSize(float x, float y);

private:
	sf::Image src;
	float sizeX;
	float sizeY;
	size_t dtaSize;
	GLuint vao;
	GLuint vbo;
};

#endif /* HEIGHTMAP */
