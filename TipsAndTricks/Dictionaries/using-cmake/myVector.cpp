#include "myParticle.hpp"
#include <TFile.h>
#include <TRandom3.h>
#include <TSystem.h>
#include <TTree.h>
#include <ctype.h>
#include <vector>

using namespace std;

void myVector() {

  gSystem->Load("libmyParticle.so");
  constexpr size_t N = 10;       // Number of Particles
  constexpr size_t nEvents = 10; // Number of events
  TFile *f =
      TFile::Open("particle_vector.root", "RECREATE"); // Creating a root file
  vector<myParticle> vmP; // std::vector containing myParticles
  TTree *t =
      new TTree("tvec", "Tree with vectors of myParticles"); // Create a TTree
  t->Branch("vmP", &vmP);                                    // Create a branch

  auto rng = TRandom3();
  double px, py, pz;
  for (size_t event = 0; event < nEvents; event++) {
    vmP.clear();
    for (int id = 0; id < N; id++) {
      px = rng.Gaus();
      py = rng.Gaus();
      pz = rng.Gaus();
      vmP.push_back({id, px, py, pz});
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
