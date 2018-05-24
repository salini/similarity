#ifndef _SIMILARITY_VERSION_H_
#define _SIMILARITY_VERSION_H_

/////////////////////////////////////////////////////////////////////////////////////
// WARNING: This file have been generated automatically, it should not be modified //
// If needed, better to change the Version.h.in file in the source code            //
//                                                                                 //
// This file is greatly inspired from the OpenSceneGraph osg/Version.in file       //
// http://www.openscenegraph.org/                                                  //
/////////////////////////////////////////////////////////////////////////////////////


#define SIMILARITY_VERSION_MAJOR    0
#define SIMILARITY_VERSION_MINOR    1
#define SIMILARITY_VERSION_PATCH    0


#define SIMILARITY_MIN_VERSION_REQUIRED    (MAJOR, MINOR, PATCH)     ((SIMILARITY_VERSION_MAJOR>MAJOR) || (SIMILARITY_VERSION_MAJOR==MAJOR && (SIMILARITY_VERSION_MINOR>MINOR || (SIMILARITY_VERSION_MINOR==MINOR && SIMILARITY_VERSION_PATCH>=PATCH))))
#define SIMILARITY_VERSION_LESS_THAN       (MAJOR, MINOR, PATCH)     ((SIMILARITY_VERSION_MAJOR<MAJOR) || (SIMILARITY_VERSION_MAJOR==MAJOR && (SIMILARITY_VERSION_MINOR<MINOR || (SIMILARITY_VERSION_MINOR==MINOR && SIMILARITY_VERSION_PATCH< PATCH))))
#define SIMILARITY_VERSION_LESS_OR_EQUAL   (MAJOR, MINOR, PATCH)     ((SIMILARITY_VERSION_MAJOR<MAJOR) || (SIMILARITY_VERSION_MAJOR==MAJOR && (SIMILARITY_VERSION_MINOR<MINOR || (SIMILARITY_VERSION_MINOR==MINOR && SIMILARITY_VERSION_PATCH<=PATCH))))
#define SIMILARITY_VERSION_GREATER_THAN    (MAJOR, MINOR, PATCH)     ((SIMILARITY_VERSION_MAJOR>MAJOR) || (SIMILARITY_VERSION_MAJOR==MAJOR && (SIMILARITY_VERSION_MINOR>MINOR || (SIMILARITY_VERSION_MINOR==MINOR && SIMILARITY_VERSION_PATCH> PATCH))))
#define SIMILARITY_VERSION_GREATER_OR_EQUAL(MAJOR, MINOR, PATCH)     ((SIMILARITY_VERSION_MAJOR>MAJOR) || (SIMILARITY_VERSION_MAJOR==MAJOR && (SIMILARITY_VERSION_MINOR>MINOR || (SIMILARITY_VERSION_MINOR==MINOR && SIMILARITY_VERSION_PATCH>=PATCH))))



std::string getVersion() {
    char _version[128];
    sprintf(_version,"%d.%d.%d",SIMILARITY_VERSION_MAJOR, SIMILARITY_VERSION_MINOR, SIMILARITY_VERSION_PATCH);
    return _version;
}


#endif
