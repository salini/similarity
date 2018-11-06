
FILE(GLOB H_FILES      *.h)
FILE(GLOB CPP_FILES    *.cpp)

SETUP_LIBRARY(simili_algorithm   H_FILES   CPP_FILES)

TARGET_LINK_LIBRARIES(simili_algorithm  # a DllExport.h file will be created automatically
    ${Boost_LIBRARIES}
)
