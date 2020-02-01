#include "small_glload.hpp"

#ifdef _WIN32
PFNWGLCHOOSEPIXELFORMATARBPROC wglChoosePixelFormatARB = nullptr;
PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB = nullptr;
PFNWGLSWAPINTERVALEXTPROC wglSwapIntervalEXT  = nullptr;
#endif 

void* (APIENTRY* small_glloader_get_proc_address)(const char*) = nullptr;

#if defined(SMALL_DEBUG)
PFNGLDEBUGMESSAGECALLBACKPROC glDebugMessageCallback = nullptr;
PFNGLDEBUGMESSAGECONTROLPROC glDebugMessageControl = nullptr;
#endif

PFNGLGENBUFFERSPROC glGenBuffers = nullptr;
PFNGLGENVERTEXARRAYSPROC glGenVertexArrays = nullptr;
PFNGLBINDBUFFERPROC glBindBuffer = nullptr;
PFNGLBUFFERDATAPROC glBufferData = nullptr;
PFNGLBINDVERTEXARRAYPROC glBindVertexArray = nullptr;
PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer = nullptr;
PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray = nullptr;

PFNGLCREATESHADERPROC glCreateShader = nullptr;
PFNGLCREATEPROGRAMPROC glCreateProgram = nullptr;
PFNGLSHADERSOURCEPROC glShaderSource = nullptr;
PFNGLCOMPILESHADERPROC glCompileShader = nullptr;
PFNGLATTACHSHADERPROC glAttachShader = nullptr;
PFNGLLINKPROGRAMPROC glLinkProgram = nullptr;
PFNGLUSEPROGRAMPROC glUseProgram = nullptr;
PFNGLDELETESHADERPROC glDeleteShader = nullptr;

#if defined(SMALL_DEBUG)
PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog = nullptr;
PFNGLGETSHADERIVPROC glGetShaderiv = nullptr;
PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog = nullptr;
PFNGLGETPROGRAMIVPROC glGetProgramiv = nullptr;
#endif

//TODO uniforms
PFNGLACTIVETEXTUREPROC glActiveTexture = nullptr;
PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation = nullptr;
PFNGLUNIFORMMATRIX4FVPROC glUniformMatrix4fv = nullptr;
PFNGLUNIFORM1FPROC glUniform1f = nullptr;
PFNGLUNIFORM1IPROC glUniform1i = nullptr;
PFNGLUNIFORM3FPROC glUniform3f = nullptr;

PFNGLGENFRAMEBUFFERSPROC glGenFramebuffers = nullptr;
PFNGLBINDFRAMEBUFFERPROC glBindFramebuffer = nullptr;
PFNGLFRAMEBUFFERTEXTURE2DPROC glFramebufferTexture2D = nullptr;
PFNGLTEXIMAGE2DMULTISAMPLEPROC glTexImage2DMultisample  = nullptr;
PFNGLBLITFRAMEBUFFERPROC glBlitFramebuffer = nullptr;


bool small_glload_init()
{
	if (!small_glloader_get_proc_address) 
#ifdef _WIN32
		small_glloader_get_proc_address 
			= reinterpret_cast<decltype(small_glloader_get_proc_address)>
				(&wglGetProcAddress);
#else
	//TODO define other platform default "get proc address" function
	{}
#endif
	//This pointer should be null, if it's not null, it means the programmer that called this function made an *oopsie"
	//At this point, the OpenGL loading is probably messed up beyond repair. We will then ask the currently running
	//WIN32 process to kindly commit suicide after yelling at the programmer. Because obviously.
	if (glGenBuffers)
	{
#if defined(SMALL_DEBUG) && defined (WIN32)
		MessageBoxA(nullptr, "Did you attempt to load OpenGL functions TWICE?", "Are you kidding me?", MB_ICONERROR);
#endif
		TerminateProcess(GetCurrentProcess(), 0xDEADDEAD);
	}

#if defined(SMALL_DEBUG)
	glDebugMessageCallback = reinterpret_cast<PFNGLDEBUGMESSAGECALLBACKPROC>
		(small_glloader_get_proc_address("glDebugMessageCallback"));
	if (!glDebugMessageCallback)
		return false;

	glDebugMessageControl = reinterpret_cast<PFNGLDEBUGMESSAGECONTROLPROC>
		(small_glloader_get_proc_address("glDebugMessageControl"));
	if (!glDebugMessageControl)
		return false;
#endif

#ifdef _WIN32
	wglChoosePixelFormatARB = reinterpret_cast<PFNWGLCHOOSEPIXELFORMATARBPROC>
		(small_glloader_get_proc_address("wglChoosePixelFormatARB"));
#if defined(SMALL_DEBUG)
	if (!wglChoosePixelFormatARB)
		return false;
#endif

	wglCreateContextAttribsARB = reinterpret_cast<PFNWGLCREATECONTEXTATTRIBSARBPROC>
		(small_glloader_get_proc_address("wglCreateContextAttribsARB"));
#if defined(SMALL_DEBUG)
	if (!wglCreateContextAttribsARB)
		return false;
#endif

	wglSwapIntervalEXT  = reinterpret_cast<PFNWGLSWAPINTERVALEXTPROC>
		(small_glloader_get_proc_address("wglSwapIntervalEXT"));
#if defined(SMALL_DEBUG)
	if (!wglSwapIntervalEXT)
		return false;
#endif

#endif //WIN32

	glGenBuffers = reinterpret_cast<PFNGLGENBUFFERSPROC>
		(small_glloader_get_proc_address("glGenBuffers"));
#if defined(SMALL_DEBUG)
	if (!glGenBuffers)
		return false;
#endif

	glGenVertexArrays = reinterpret_cast<PFNGLGENVERTEXARRAYSPROC>
		(small_glloader_get_proc_address("glGenVertexArrays"));
#if defined(SMALL_DEBUG)
	if (!glGenVertexArrays)
		return false;
#endif

	glBindBuffer = reinterpret_cast<PFNGLBINDBUFFERPROC>
		(small_glloader_get_proc_address("glBindBuffer"));
#if defined(SMALL_DEBUG)
	if (!glBindBuffer)
		return false;
#endif

	glBufferData = reinterpret_cast<PFNGLBUFFERDATAPROC>
		(small_glloader_get_proc_address("glBufferData"));
#if defined(SMALL_DEBUG)
	if (!glBufferData)
		return false;
#endif

	glBindVertexArray = reinterpret_cast<PFNGLBINDVERTEXARRAYPROC>
		(small_glloader_get_proc_address("glBindVertexArray"));
#if defined(SMALL_DEBUG)
	if (!glBindVertexArray)
		return false;
#endif

	glVertexAttribPointer = reinterpret_cast<PFNGLVERTEXATTRIBPOINTERPROC>
		(small_glloader_get_proc_address("glVertexAttribPointer"));
#if defined(SMALL_DEBUG)
	if (!glVertexAttribPointer)
		return false;
#endif

	glEnableVertexAttribArray = reinterpret_cast<PFNGLENABLEVERTEXATTRIBARRAYPROC>
		(small_glloader_get_proc_address("glEnableVertexAttribArray"));
#if defined(SMALL_DEBUG)
	if (!glEnableVertexAttribArray)
		return false;
#endif

	glCreateShader = reinterpret_cast<PFNGLCREATESHADERPROC>
		(small_glloader_get_proc_address("glCreateShader"));
#if defined(SMALL_DEBUG)
	if (!glCreateShader)
		return false;
#endif

	glCreateProgram = reinterpret_cast<PFNGLCREATEPROGRAMPROC>
		(small_glloader_get_proc_address("glCreateProgram"));
#if defined(SMALL_DEBUG)
	if (!glCreateProgram)
		return false;
#endif

	glShaderSource = reinterpret_cast<PFNGLSHADERSOURCEPROC>
		(small_glloader_get_proc_address("glShaderSource"));
#if defined(SMALL_DEBUG)
	if (!glShaderSource)
		return false;
#endif
	glCompileShader = reinterpret_cast<PFNGLCOMPILESHADERPROC>
		(small_glloader_get_proc_address("glCompileShader"));
#if defined(SMALL_DEBUG)
	if (!glCompileShader)
		return false;
#endif

	glAttachShader = reinterpret_cast<PFNGLATTACHSHADERPROC>
		(small_glloader_get_proc_address("glAttachShader"));
#if defined(SMALL_DEBUG)
	if (!glAttachShader)
		return false;
#endif

	glLinkProgram = reinterpret_cast<PFNGLLINKPROGRAMPROC>
		(small_glloader_get_proc_address("glLinkProgram"));
#if defined(SMALL_DEBUG)
	if (!glLinkProgram)
		return false;
#endif

	glUseProgram = reinterpret_cast<PFNGLUSEPROGRAMPROC>
		(small_glloader_get_proc_address("glUseProgram"));
#if defined(SMALL_DEBUG)
	if (!glUseProgram)
		return false;
#endif

	glDeleteShader = reinterpret_cast<PFNGLDELETESHADERPROC>
		(small_glloader_get_proc_address("glDeleteShader"));
#if defined(SMALL_DEBUG)
	if (!glDeleteShader)
		return false;
#endif


#if defined(SMALL_DEBUG)
	//Relase build doesn't check **anything** at runtime to save codesize
	glGetShaderInfoLog = reinterpret_cast<PFNGLGETSHADERINFOLOGPROC>
		(small_glloader_get_proc_address("glGetShaderInfoLog"));
	if (!glGetShaderInfoLog)
		return false;

	glGetShaderiv = reinterpret_cast<PFNGLGETSHADERIVPROC>
		(small_glloader_get_proc_address("glGetShaderiv"));
	if (!glGetShaderiv)
		return false;

	glGetProgramInfoLog = reinterpret_cast<PFNGLGETPROGRAMINFOLOGPROC>
		(small_glloader_get_proc_address("glGetProgramInfoLog"));
	if (!glGetProgramInfoLog)
		return false;

	glGetProgramiv = reinterpret_cast<PFNGLGETPROGRAMIVPROC>
		(small_glloader_get_proc_address("glGetProgramiv"));
	if (!glGetProgramiv)
		return false;
#endif

	glActiveTexture = reinterpret_cast<PFNGLACTIVETEXTUREPROC>
	(small_glloader_get_proc_address("glActiveTexture"));
#if defined(SMALL_DEBUG)
	if(!glActiveTexture)
		return false;
#endif

	glGetUniformLocation = reinterpret_cast<PFNGLGETUNIFORMLOCATIONPROC>
	(small_glloader_get_proc_address("glGetUniformLocation"));
#if defined(SMALL_DEBUG)
	if (!glGetUniformLocation)
		return false;
#endif

	glUniformMatrix4fv = reinterpret_cast<PFNGLUNIFORMMATRIX4FVPROC>
	(small_glloader_get_proc_address("glUniformMatrix4fv"));
#if defined(SMALL_DEBUG)
	if (!glUniformMatrix4fv)
		return false;
#endif
	
	glUniform1f = reinterpret_cast<PFNGLUNIFORM1FPROC>
	(small_glloader_get_proc_address("glUniform1f"));
#if defined(SMALL_DEBUG)
	if (!glUniform1f)
		return false;
#endif

	glUniform1i = reinterpret_cast<PFNGLUNIFORM1IPROC>
	(small_glloader_get_proc_address("glUniform1i"));
#if defined(SMALL_DEBUG)
	if (!glUniform1i)
		return false;
#endif

	glUniform3f = reinterpret_cast<PFNGLUNIFORM3FPROC>
	(small_glloader_get_proc_address("glUniform3f"));
#if defined(SMALL_DEBUG)
	if (!glUniform3f)
		return false;
#endif

	//TODO here add more uniform functions

	glGenFramebuffers = reinterpret_cast<PFNGLGENFRAMEBUFFERSPROC>
		(small_glloader_get_proc_address("glGenFramebuffers"));
#if defined(SMALL_DEBUG)
	if (!glGenFramebuffers)
		return false;
#endif

	glBindFramebuffer = reinterpret_cast<PFNGLBINDFRAMEBUFFERPROC>
		(small_glloader_get_proc_address("glBindFramebuffer"));
#if defined(SMALL_DEBUG)
	if (!glBindFramebuffer)
		return false;
#endif

	glFramebufferTexture2D = reinterpret_cast<PFNGLFRAMEBUFFERTEXTURE2DPROC>
		(small_glloader_get_proc_address("glFramebufferTexture2D"));
#if defined(SMALL_DEBUG)
	if (!glFramebufferTexture2D)
		return false;
#endif

	glTexImage2DMultisample = reinterpret_cast<PFNGLTEXIMAGE2DMULTISAMPLEPROC>
	(small_glloader_get_proc_address("glTexImage2DMultisample"));
#if defined(SMALL_DEBUG)
	if (!glTexImage2DMultisample)
		return false;
#endif
	
	glBlitFramebuffer = reinterpret_cast<PFNGLBLITFRAMEBUFFERPROC>
	(small_glloader_get_proc_address("glBlitFramebuffer"));
#if defined(SMALL_DEBUG)
	if (!glBlitFramebuffer)
		return false;
#endif

	return true;
}
