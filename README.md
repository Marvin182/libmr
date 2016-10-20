# libmr

This is my personal C++ library. It's not more than a bunch of more or less useful C++ classes and methods - so far very low level stuff. In future I might add data structures and algorithms.

## Build
```
mkdir build
cd build
cmake .. <OPTIONS>
make
```

Options:

- `-DBUILD_WITH_QT=OFF` Don't build parts based on Qt5
- `-DCMAKE_PREFIX_PATH=<PATH>` Point CMake to Qt5 directory
- `-DCMAKE_BUILD_TYPE=Debug` Build with debug flags


## Usage
TODO: Describe usage (build, add include directory to project and link to the created binary files)

## Headers
- *mr/algo* - A few helper classes for specific cases in algorithmic problems
- *mr/common* - better asserts, constants, wrapped methods for std random header
- *mr/qt* - some Qt helper methods
- *mr/timer* - Timer class

## License
For know this code will be under the MIT License, but when I have time I will switch to an similar license with a "non-military use only" clause. This code should not be used for any kind of violence.