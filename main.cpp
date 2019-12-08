#include <iostream>
#include "debug.h"
#include "glutils.h"
#include "Heightmap.h"
#include <SFML/Graphics.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cmath>

#define PI ((float)M_PI)

using std::cout;
using std::endl;
using namespace glm;

void draw();

namespace sf
{
	sf::Glsl::Mat4 toMat(const mat4& m)
	{
		return sf::Glsl::Mat4(value_ptr(m));
	}
}

int main()
{
    //Perlin3D().run();

	const int w(800), h(800);
	const bool fullscreen(true);
    sf::RenderWindow window(sf::VideoMode(w, h), "SFML works!", fullscreen ? sf::Style::Fullscreen : sf::Style::Default, sf::ContextSettings(24 /* important sinon bugs graphiques */, 0, 0, 4, 6)); // verifiéer que ça retire les bugs la 4.6 de SFML inutilisable
	sf::Shader shader;
    Heightmap map;
	mat4 model(1.0f);
	mat4 camera(1.0f);
	mat4 projection(1.0f);
	bool pause(false);
	bool wireframe(false);
	const GLfloat dspace(.1f);
	
	window.setMouseCursorVisible(false);
	glInitGlew();
    glVersion();
	//glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glCullFace(GL_BACK);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	
	shader.loadFromFile("3d.vert", "3d.frag");
    map.loadFromFile("heightmap_unity.png");

	projection = glm::perspective(70.0f, (float)(w) / h, 0.1f, 10000.0f);
	camera = translate(camera, -11.f * vec3(0, 1, 0));
	camera = rotate(mat4(1.0f), PI / -8.0f, vec3(-1, 0, 0)) * camera;

    while (window.isOpen())
    {
		if(!pause)
		{
			//camera = rotate(camera, 0.001f, vec3(-1, 0, 0));
			//camera = rotate(camera, 0.001f, vec);
		}
     
		sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

			if(event.type == sf::Event::KeyPressed)
			{
				if(event.key.code == sf::Keyboard::Space)
				{
					pause = !pause;
				}
				else if(event.key.code == sf::Keyboard::F)
				{
					GLint params[2], &front(params[0]), &back(params[1]);
					GLint mode;
					glGetIntegerv(GL_POLYGON_MODE, params);

					if(front == GL_POINT) mode = GL_LINE;
					else if(front == GL_LINE) mode = GL_FILL;
					else mode = GL_POINT;
					
					glPolygonMode(GL_FRONT_AND_BACK, mode);
				}
        	}
		} 

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
		{
			camera = translate(mat4(1.0f), -dspace * vec3(0, 0, -1)) * camera;
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			camera = translate(mat4(1.0f), -dspace * vec3(0, 0, 1)) * camera;
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			camera = rotate(mat4(1.0f), PI / 300.0f, vec3(0, 1, 0)) * camera;
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			camera = rotate(mat4(1.0f), PI / 300.0f, vec3(0, -1, 0)) * camera;
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			camera = rotate(mat4(1.0f), PI / -300.0f, vec3(1, 0, 0)) * camera;
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			camera = rotate(mat4(1.0f), PI / -300.0f, vec3(-1, 0, 0)) * camera;
		}
			
		sf::Shader::bind(&shader);
		shader.setUniform("modelview", sf::toMat(projection * camera * model));
	
        //window.clear();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		map.draw();
        window.display();
    }

    return 0;
}
