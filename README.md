# small_glload

Small, like, really, really small, nasty, bad, non-exhaustive OpenGL function loader.

Intended for some demo making experiments.

Only tested on Win32, and it loads just a handful of functions.

Usage:
-----
 Include all the files, alongside the GL and KHR directories to your project.

 Then: get the functions and definitions here
 #include "small_glload.hpp"

 To load functions call this:

 small_glload_init();

 If it failed, it returns false.


How it works:
-------------

 Manually define the OpenGL function pointer we are going to use by doing the following

  1. define a "GLAPI PFN+GLNAMEOFFUNC+PROC glNameOFunc;" symbol here
  2. in small_glload.cpp, define it as "PFN+GLNAMEOFFUNC+PROC glNameOfFunc = nullptr;"
  3. add to small_glload_init() a call to small_glloader_get_proc_address like all the
     other ones

 It could be extended to other platform just by providing a function pointer to
 small_glloader_get_proc_address into any function that take a string and return a void*

