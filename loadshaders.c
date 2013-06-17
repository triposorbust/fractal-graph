#ifndef __LOADSHADERS_H__
#include "loadshaders.h"
#endif

#ifndef __STDLIB_H__
#define __STDLIB_H__
#include <stdlib.h>
#endif

#ifndef __STDIO_H__
#define __STDIO_H__
#include <stdio.h>
#endif

static const GLchar *read_shader(const char *filename)
{
  FILE *infile = fopen(filename, "rb");
  if (!infile) {
    printf("Unable to read file: %s\n", filename);
    exit(1);
  }

  fseek(infile, 0, SEEK_END);
  int len = ftell(infile);
  fseek(infile, 0, SEEK_SET);

  GLchar *source = (GLchar *) malloc((len+1) * sizeof(GLchar *));
  source[len] = 0;

  fread(source, 1, len, infile);
  fclose(infile);

  return (const GLchar *)(source);
}

GLuint load_shaders(ShaderInfo *shaders)
{

  if (shaders == NULL) return 0;
  GLuint program = glCreateProgram();

  ShaderInfo *entry = shaders;
  while (entry->type != GL_NONE) {
    GLuint shader = glCreateShader(entry->type);

    entry->shader = shader;

    const GLchar* source = read_shader(entry->filename);
    if (source == NULL) {
      for (entry=shaders; entry->type != GL_NONE; ++entry) {
        glDeleteShader(entry->shader);
        entry->shader = 0;
      }
      exit(1);
    }

    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);
    free((GLchar *)source);

    GLint compiled;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
    if (!compiled) {
      GLsizei len;
      glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);
      GLchar *log = (GLchar *) malloc((len+1) * sizeof(GLchar));
      glGetShaderInfoLog(shader, len, &len, log);
      printf("Shader compilation failed: %s\n", log);
      free(log);
      exit(1);
    }

    glAttachShader(program, shader);
    entry++;
  }

  glLinkProgram(program);
  GLint linked;
  glGetProgramiv(program, GL_LINK_STATUS, &linked);
  if (!linked) {
    GLsizei len;
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &len);
    GLchar *log = (GLchar *) malloc((len+1) * sizeof(GLchar));
    glGetProgramInfoLog(program, len, &len, log);
    printf("Shader linking failed: %s\n", log);
    free(log);

    for (entry=shaders; entry->type != GL_NONE; ++entry) {
      glDeleteShader(entry->shader);
      entry->shader = 0;
    }

    exit(1);
  }

  return program;

}
