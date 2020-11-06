# Tips and Tricks

# Table of contents
- [Compiling C++ code using Cling](#compiling-c-code-using-cling)
- [Compiling C++ code using ROOT Libraries](#compiling-c-code-using-root-libraries)
- [Makefiles](#makefiles)
- [CMake](#cmake)
- [ROOT windows in compiled code](#root-windows-in-compiled-code)
- [Making Dictionaries](#making-dictionaries)
  - [Using Makefiles](#using-makefiles)
  - [Using CMake](#using-cmake)
  


## Compiling C++ code using Cling

The simplest and most painless way to compile some code using ROOT libraries is using the next line inside ROOT's prompt:
``` bash
.x mycode.cpp+(args)
```
where args will be the arguments, if any, that the function needs.

One problem of  that usage, is that the function that we want to run must have the same name as the file, without the extension part of course.

## Compiling C++ code using ROOT Libraries

In case we want to use ROOT libraries with our C++ code, we need to add the next bit to the compilation part
``` bash
g++ mycode.cpp -o mycode.exe `root-config --cflags --glibs --ldflags`
```
where the ```root-config --cflags``` will give the cflags that we need, like the c++ standard and the include directories of ROOT, ```root-config --ldflags``` are the linker flags, and ```root-config --glibs``` are the flags for linking with regular ROOT libraries with some GUI part. One can see the ```root-config --help``` for all the options.

For example, if we want to compile with RooFit and Minuit support we need the extra linking flags, because they are not included in the regular flags
``` bash
g++ mycode.cpp -o mycode.exe `root-config --cflags --glibs --ldflags` -lRooFit -lRooFitCore -lMinuit
```


## Makefiles

* **TODO**

## CMake
[https://root.cern/manual/integrate_root_into_my_cmake_project/](https://root.cern/manual/integrate_root_into_my_cmake_project/)

## ROOT windows in compiled code

One of the problems someone will face, is that GUI windows of ROOT won't appear in compiled code. For this to work we need to do an extra step, using the ```TApplication.h``` library of ROOT. Just befor the main function we can put the next line: 

```cpp 
TApplication theApp("AppName", &argc, argv);
// or TApplication theApp("AppName", nullptr, nullptr); 
```

After all our scientific code, we need to run that app:

```cpp 
theApp.Run(true);
```
Most of the times, the program will look like it hangs, but we just need to kill it by hand, or quit ROOT from a GUI window

A simple example would look like:

```cpp
// For actually seeing the canvases with compiled programs
#include <TApplication.h>
...
...
int main(int argc, char** argv){
    TApplication theApp("App", &argc, argv); // Declaring the app
    ...
    // scientific code 
    ...

    theApp.Run(true); // Running the app
}

```

## Making Dictionaries
[https://root.cern/manual/interacting_with_shared_libraries/#generating-dictionaries](https://root.cern/manual/interacting_with_shared_libraries/#generating-dictionaries)
### Using Makefiles
Let's say we have a struct for a particle object that we need for our code, and a particle is basically an id, maybe refering to PDG code, and its momenta. We can put that code in a *myParticle.h*:

```cpp
#include <TRoot.h>

struct myParticle {
  int id;
  double px, py, pz;
  myParticle() : id(0), px(0), py(0), pz(0){};
  myParticle(int i, double pX, double pY, double pZ)
      : id(i), px(pX), py(pY), pz(pZ){};
  // ClassDef(class-name, class-version-id)
  ClassDef(myParticle, 1);
};
```

Somehow in our code, we manage to generate some type of events consisting of a number of particles. We can imagine each event to be a ```std::vector<myParticle>```. We can save each event to a root file in that form, meaning that the branch will have type of ```std::vector<myParticle>```, but ROOT can do that in one step. That's when the notion of creating a `dictionary` for a custom struct/class comes in handy. 

After creating our custom struct/class, we need to create a header file, usually a name like `LinkDef.h`, where we say for which classes will need a dictionary. In this case we want a dictionary for *myParticle* struct and for the class *std::vector<myParticle>* :
```cpp
#include <vector>
#include "myParticle.h"
#if defined(__MAKECINT__) || defined(__ROOTCLING__)
#pragma link C++ struct myParticle+;
#pragma link C++ class std::vector<myParticle>+;
#endif
```


Τώρα, μέσω του *rootcling* και των δυο header files που φτιάξαμε πιο πριν, Θα φτιάξουμε ένα αρχείο ας πούμε *myDict.cxx*, από το οποίο μέσω του compiler μας, θα φτιάξουμε ένα shared library (.so file). 

``` sh
rootcling -f myDict.cxx  $(CXXFLAGS) myParticle.h Linkdef.h
```

Επόμενο βήμα, είναι να φτιάξουμε ένα shared library αρχείο, που θα το ονομάσουμε *libmyParticle.so*. 
```sh
g++ -shared -fPIC -o libmyParticle.so `root-config --ldflags --clfags` myDict.cxx
```

Είμαστε πλέον σε θέση να χρεισιμοποιήσουμε τα `myParticle` και `std::vector<myParticle>`. 
```sh 
g++ main.cpp libmyParticle.so -o main `root-config --cflags --glibs --ldflags`
```

### Using CMake


```cmake
# Minimum Version of CMake to be used
cmake_minimum_required(VERSION 3.16)

# Project name, and in what programming language
project(RootDictExample LANGUAGES CXX)

# tell the compiler to use c++XX standard
set(CMAKE_CXX_STANDARD XX)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# This line finds a specific file in ROOT's directory
# with functionality to compile code using ROOT
find_package(ROOT CONFIG REQUIRED)

# root_generate_dictionary(dictionary_name header_file LINKDEF appropriate_linkdef_header)
root_generate_dictionary(G__myParticle myParticle.hpp LINKDEF LinkDef.h)

# This line will create a myParticle.so file, which depends on myParticle.hpp header file 
# and the dictionary_name.cxx which was generated by the previous line
add_library(myParticle SHARED myParticle.hpp G__myParticle.cxx)

# specifie which folders to be inlcuded
target_include_directories(myParticle PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

# create executable name myVector, depending on myVector.cpp
add_executable(myVector myVector.cpp)

# link approprietly with TTree, RDataFrame and our myParticle libs
target_link_libraries(myVector PUBLIC ROOT::ROOTDataFrame
                                      ROOT::Tree myParticle)
```



