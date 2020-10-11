# Tips and Tricks

# Table of contents
- [Compiling C++ code using Cling](#Compiling-C-code-using-Cling)
- [Compiling C++ code using ROOT Libraries](#compiling-c-code-using-root-libraries)
- [Makefiles](#Makefiles)

## Compiling C++ code using Cling [](#){name=cling}

Ο ποιος απλός τρόπος να κάνουμε compile έαν κώδικα που περιέχει βιβλιοθήκες της ROOT, είναι χρησιμοποιώντας την εξής εντολή στην ROOT:

``` bash
.x mycode.cpp+(args)
```
όπου στην παρένθεση βάζουμε τις παραμέτρους που περιμένει το πρόγραμμα, αν περιμένει.


Το "πρόβλημα" με αυτόν τον τρόπο είναι ότι η συνάρτηση που θέλουμε να τρέξουμε θα πρέπει να έχει το ίδιο όνομα με το αρχείο μας.






## Compiling C++ code using ROOT Libraries

Στην περίπτωση που θέλουμε να προσθέσουμε βιβλιοθήκες της ROOT στον κώδικά μας, μπορούμε πολύ εύκολα να κάνουμε το εξής:

``` bash
g++ mycode.cpp -o mycode.exe `root-config --cflags --glibs --ldflags`
```

Αναλόγως, ποιες βιβλιοθήκες χρησιμοποιούμε, θα πρέπει να προστέσουμε για επιπλεόν options. Για παράδειγμα, αν θέλουμε να χρησιμοποιήσουμε την RooFit χρειαζόμαστε επιπλέον:

``` bash
g++ mycode.cpp -o mycode.exe `root-config --cflags --glibs --ldflags` -lRooFit -lRooFitCore -lMinuit
```

Tο ```--cflags``` κάνει setup τα include paths και το ```--glibs``` τα library paths και κάποιες βιβλιοθήκες που χρησιμοποιούνται συχνά.


**Σημείωση** : όλα τα παραδείγματα σε C++, είναι φτιαγμένα για να τρέχουν με αυτόν τον τρόπο, είτε με τα Makefiles που βρίσκονται στον εκάστοτε φάκελο.


## Makefiles

* **TODO**

## ROOT windows in compiled code

Στην περίπτωση που θέλουμε να έχουμε ένα executable, για να εμφανιστούν τα παράθυρα της ROOT (πχ histo->Draw()), θα πρέπει να προσθέσουμε την βιβλιοθήκη ```TApplication.h```. Έπειτα, στην αρχή του προγράμματος προσθέτουμε την σειρά:

```cpp 
TApplication theApp("App", &argc, argv);
```

Και αφού έχουμε τελειώσει την επεξεργασία μας, στο τέλος πρέπει να τρέξουμε αυτό το ```App```:

```cpp 
theApp.Run(true);
```
Υπάρχουν περιπτώσεις που το πρόγραμμα δε θα κλείσει μόνο του, οπότε μπορει να χρειαστεί να το σταματήσουμε με ```^C``` (Ctrl+C).

Οπότε ο κώδικας, θα μοιάζει σε γενικές γραμμές:

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
### Using Makefiles
Ας υποθέσουμε ότι έχουμε ένα struct για να εκφράσουμε ένα σωματίδιο, όπου θέλουμε ένα id του σωματιδίου, ώστε να ξέρουμε ποιο είναι, και 3 double μεταβλητές για την ορμή του. Φτιάχνουμε ένα αρχείο *myParticle.h*, όπου θα περιέχει:

```cpp
struct myParticle {
  int id;
  double px, py, pz;
  myParticle() : id(0), px(0), py(0), pz(0){};
  myParticle(int i, double pX, double pY, double pZ)
      : id(i), px(pX), py(pY), pz(pZ){};
};
```

Έστω ότι γενάμε με κάποιο τρόπο γεγονότα, όπου το καθένα έχει ένα αριθμό σωματιδίων. Θα χρησιμοποιήσουμε ένα ```std::vector<myParticle>```  σαν ένα container για τα σωματίδια που υπάρχουν για ένα γεγονός. Αυτό σημαίνει ότι στο root file μας, θα αποθηκεύσουμε ```std::vector<myParticle>```. Αλλά η ROOT δεν ξέρει πώς να το κάνει αυτό.
Οπότε η λύση είναι να φτιάξουμε ένα dictionary που να λέει στην ROOT πώς να το χρησιμοποιήσει. 

Για αρχή θα φτιάξουμε ένα header file, με όνομα *Linkdef.h*, που θα ορίσουμε ποιες καινούριες 'δομές' θα χρησιμοποιήσουμε. Αυτό το αρχείο θα περιέχει τα εξής:

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



