#ifndef GLUTILS_H
#define GLUTILS_H

#define GLEW_STATIC
#include <GL/glew.h>

inline void glVersion()
{
	const GLubyte *ver = glGetString(GL_VERSION);
	const GLubyte *sha = glGetString(GL_SHADING_LANGUAGE_VERSION);
	
	printf("GL_VERSION = %s\nGLSL_VERSION = %s\n", ver, sha);
}

inline void glInitGlew()
{
	GLenum err = glewInit();
	if(err != GLEW_OK)
	{
		printf("%s\n", glewGetErrorString(err));
		exit(1);
	}
}

#endif /* GLUTILS_H */
