//WARNING: this file has been generated automatically through
//         the cmake configure_file macro. You should not modify
//         this file directly; change your cmake parameters instead.


#ifndef _SIMILI_DLLEXPORT_H_
#define _SIMILI_DLLEXPORT_H_

// DEFINE DLL EXPORT IF COMPILING DLL (DYNAMIC LIB) IN WINDOWS

#if defined (WIN32)  &&  defined(DYNAMIC_LIB)
    #if defined(simili_EXPORTS) // should have been defined by Cmake if needed
        #define  SIMILI_EXPORT __declspec(dllexport)
    #else
        #define  SIMILI_EXPORT __declspec(dllimport)
    #endif
#else  // if not WIN32
    #define SIMILI_EXPORT
#endif



#endif
