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
- <mr/algo> - A few helper classes for specific cases in algorithmic problems
- <mr/common> - better asserts, constants, wrapped methods for std random header
- <mr/qt> - some Qt helper methods
- <mr/timer> - Timer class
- <mr/version> - Version class (also see gitversion.pri)

## License
For know this code will be under the MIT License, but when I have time I will switch to an similar license with a "non-military use only" clause. This code should not be used for any kind of violence.

The MIT License (MIT)

Copyright (c) 2015 Marvin Ritter

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.