#pragma once

struct myParticle {
  int id;
  double px, py, pz;
  myParticle() : id(0), px(0), py(0), pz(0){};
  myParticle(int i, double pX, double pY, double pZ)
      : id(i), px(pX), py(pY), pz(pZ){};
};
