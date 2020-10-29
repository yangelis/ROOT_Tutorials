#ifndef __LINKDEF_H_
#define __LINKDEF_H_

#include <vector>
#include "myParticle.hpp"
#if defined(__MAKECINT__) || defined(__ROOTCLING__)
#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;
#pragma link C++ struct myParticle+;
#pragma link C++ class std::vector<myParticle>+;
#endif


#endif // __LINKDEF_H_
