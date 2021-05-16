#pragma once

//small_glload.hpp
// (C) 2019-2020 Arthur Brainville (Ybalrid)
//
//License: The Unlicense
//
//small, like, really, really small, nasty, bad, non-exhaustive OpenGL function loader.
//
// Intended for some demo making experiments.
//
// Usage:
// -----
//  Include all the files, alongside the GL and KHR directories to your project.
//
//  Then: get the functions and definitions here
//  #include "small_glload.hpp"
//
//  To load functions call this:
//
//  small_glload_init();
//
//  If it failed, it returns false.
//
//
// How it works:
// -------------
//
//  Manually define the OpenGL function pointer we are going to use by doing the following
//
//   1. define a "GLAPI PFN+GLNAMEOFFUNC+PROC glNameOFunc;" symbol here
//   2. in small_glload.cpp, define it as "PFN+GLNAMEOFFUNC+PROC glNameOfFunc = nullptr;"
//   3. add to small_glload_init() a call to small_glloader_get_proc_address like all the
//      other ones
//
//  It could be extended to other platform just by providing a function pointer to
//  small_glloader_get_proc_address into any function that take a string and return a void*

//Hopefully a small 64k demo should be able to be made without the need to go use super
//complex OpenGL, right? ;-)

#if defined(DEBUG) || defined (_DEBUG)
#ifndef SMALL_DEBUG
#define SMALL_DEBUG
#endif
#endif

//Operating system API
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

//MS Windows OpenGL 1.1 API. Thanks Microsoft... :cry:
#include <GL/GL.h>

//Khronos Registry headers for API and extensions
//They contains the function pointer types, and all the
//missing "#defines GL_MAGIC_NUMBER and "typedf GLtype"
#include "gl/glext.h"
#ifdef _WIN32
#include "gl/wglext.h"
#endif

//All functions will be loaded through that function, you can change
//this pointer if you so desire
GLAPI void* (APIENTRY *small_glloader_get_proc_address)(const char*);

///Load OpenGL functions defined here
bool small_glload_init();

#ifdef _WIN32
//Better Win32 context creation utilities
GLAPI PFNWGLCHOOSEPIXELFORMATARBPROC wglChoosePixelFormatARB;
GLAPI PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB;
GLAPI PFNWGLSWAPINTERVALEXTPROC wglSwapIntervalEXT;
#endif
#if defined(DEBUG) || defined(_DEBUG)
GLAPI PFNGLDEBUGMESSAGECALLBACKPROC glDebugMessageCallback;
GLAPI PFNGLDEBUGMESSAGECONTROLPROC glDebugMessageControl;
#endif

//Buffer management
GLAPI PFNGLGENBUFFERSPROC glGenBuffers;
GLAPI PFNGLGENVERTEXARRAYSPROC glGenVertexArrays;
GLAPI PFNGLBINDBUFFERPROC glBindBuffer;
GLAPI PFNGLBUFFERDATAPROC glBufferData;
GLAPI PFNGLBINDVERTEXARRAYPROC glBindVertexArray;
GLAPI PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer;
GLAPI PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray;

//Shader management
GLAPI PFNGLCREATESHADERPROC glCreateShader;
GLAPI PFNGLCREATEPROGRAMPROC glCreateProgram;
GLAPI PFNGLSHADERSOURCEPROC glShaderSource;
GLAPI PFNGLCOMPILESHADERPROC glCompileShader;
GLAPI PFNGLATTACHSHADERPROC glAttachShader;
GLAPI PFNGLLINKPROGRAMPROC glLinkProgram;
GLAPI PFNGLUSEPROGRAMPROC glUseProgram;
GLAPI PFNGLDELETESHADERPROC glDeleteShader;

//Shader info retrieval
#if defined(DEBUG) || defined(_DEBUG)
GLAPI PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog;
GLAPI PFNGLGETSHADERIVPROC glGetShaderiv;
GLAPI PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog;
GLAPI PFNGLGETPROGRAMIVPROC glGetProgramiv;
#endif


GLAPI PFNGLACTIVETEXTUREPROC glActiveTexture;
GLAPI PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation;
//TODO Add more shader uniforms functions... Yeah, there's a lot of them :sadface:
GLAPI PFNGLUNIFORMMATRIX4FVPROC glUniformMatrix4fv;
GLAPI PFNGLUNIFORM1FPROC glUniform1f;
GLAPI PFNGLUNIFORM1IPROC glUniform1i;
GLAPI PFNGLUNIFORM3FPROC glUniform3f;

//Frambuffer management
GLAPI PFNGLGENFRAMEBUFFERSPROC glGenFramebuffers;
GLAPI PFNGLBINDFRAMEBUFFERPROC glBindFramebuffer;
GLAPI PFNGLFRAMEBUFFERTEXTURE2DPROC glFramebufferTexture2D;
GLAPI PFNGLTEXIMAGE2DMULTISAMPLEPROC glTexImage2DMultisample;
GLAPI PFNGLBLITFRAMEBUFFERPROC glBlitFramebuffer;

GLAPI PFNGLGENERATEMIPMAPPROC glGenerateMipmap;

