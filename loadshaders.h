#ifndef __loadshaders_h__
#define __loadshaders_h__

#ifndef __gl_h__
#define __gl_h__
#include <OpenGL/gl.h>
#endif

typedef struct {
  GLenum type;
  const char *filename;
  GLuint shader;
} ShaderInfo;

GLuint load_shaders(ShaderInfo *);

#endif
