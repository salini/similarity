# similarity

## dependencies

### Ubuntu (18.04)

```sh
sudo apt install  cmake  qt5-default  libopencv-dev  libboost-system-dev  libboost-filesystem-dev  libboost-program_options-dev  libboost-iostreams-dev
```

### Windows

* [CMake](https://cmake.org/files/v3.12/cmake-3.12.4-win64-x64.msi)

using vs2015 x64:

* [Qt5](http://download.qt.io/official_releases/online_installers/qt-unified-windows-x86-online.exe)
* [OpenCV](https://downloads.sourceforge.net/project/opencvlibrary/opencv-win/3.4.1/opencv-3.4.1-vc14_vc15.exe?r=https%3A%2F%2Fsourceforge.net%2Fprojects%2Fopencvlibrary%2Ffiles%2Fopencv-win%2F3.4.1%2Fopencv-3.4.1-vc14_vc15.exe%2Fdownload&ts=1541544039)
* [Boost](https://downloads.sourceforge.net/project/boost/boost-binaries/1.68.0/boost_1_68_0-msvc-14.0-64.exe?r=https%3A%2F%2Fsourceforge.net%2Fprojects%2Fboost%2Ffiles%2Fboost-binaries%2F1.68.0%2Fboost_1_68_0-msvc-14.0-64.exe%2Fdownload&ts=1541544164)

set environment variables:

* `Qt5_DIR` (e.g. `Qt5_DIR=D:/Qt/5.11.2/msvc2015_64/lib/cmake/Qt5`)
* `OpenCV_DIR` (e.g. `OpenCV_DIR=D:\opencv\build`)
* `BOOST_INCLUDEDIR` (e.g. `BOOST_INCLUDEDIR=d:\boost_1_68_0`)
* `BOOST_LIBRARYDIR` (e.g. `BOOST_LIBRARYDIR=d:\boost_1_68_0\lib64-msvc-14.0`)

add to path:

* `D:\Qt\5.11.2\msvc2015_64\bin`
* `%OpenCV_DIR%\x64\vc14\bin`
* `%BOOST_LIBRARYDIR%`


# Possible issues

if you get a message:
```sh
This application failed to start because it could not find or load the Qt platform plugin "windows"
```
check that another Qt5 dll (e.g. Qt5Core.dll) are no present in another location in the PATH.