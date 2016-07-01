# exstr
Expanded Strings. This library provides basic to advanced string functionality for C. Most functions have been implemented in other languages, but this library attempts to aggregate the best features of all libraries.

## Goals
The general goal of this project is to create a lightweight but extremely powerful string library for use with C.

### Usability
The library is also intended to be useful in as many scenarios as possible, therefore considerations to parallel programming and reentrancy are important. In fact, this library was concieved in the process of building a multi-threaded HTTP web server.

### Extensible Architecture
This project should be planned and executed with future development in mind. As such, the architecture of the project should be flexible and extensible.

### Cross Platform
This project should work on, at the very least, all major operating systems. Future goals may also inlcude embedded development and support for use on any platform that supports the standard C library. Efficiency on major operating systems takes priority over minor operating system compatibility.
