#include <TFile.h>
#include <TRandom3.h>
#include <TTree.h>
#include <ctype.h>
#include <vector>

using namespace std;

struct myParticle {
  int id;
  double px, py, pz;
  myParticle(int i, double pX, double pY, double pZ)
      : id(i), px(pX), py(pY), pz(pZ) {}
};

void myVector() {

  constexpr size_t N = 1000;     // Number of Particles
  constexpr size_t nEvents = 10; // Number of events
  TFile *f =
      TFile::Open("particle_vector.root", "RECREATE"); // Creating a root file
  vector<myParticle> vmP; // std::vector containing myParticles
  TTree *t =
      new TTree("tvec", "Tree with vectors of myParticles"); // Create a TTree
  t->Branch("vmP", &vmP);                                    // Create a branch

  auto rng = TRandom3();
  for (size_t event = 0; event < nEvents; event++) {
    vmP.clear();
    int id;
    double px, py, pz;
    for (size_t id = 0; id < N; id++) {
      id = rng.Poisson(10);
      px = rng.Gaus();
      py = rng.Gaus();
      pz = rng.Gaus();
      vmP.emplace_back(myParticle(id, px, py, pz));
    }
    t->Fill();
  }
  f->Write();
  delete f;
}

int main() {
  myVector();
  return 0;
}
