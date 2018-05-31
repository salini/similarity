
ADD_VERSION_HEADER_FILE()  # this will add a Version.h file based on the cmake inputs. Should be done once in the source tree folder

FILE(GLOB H_FILES       *.h)
FILE(GLOB CPP_FILES     *.cpp )
FILE(GLOB UI_FILES      *.ui )


SETUP_QT_LIBRARY(simili   H_FILES   CPP_FILES   UI_FILES)



TARGET_LINK_LIBRARIES( simili
    Qt5::Widgets
    Qt5::Core
)

