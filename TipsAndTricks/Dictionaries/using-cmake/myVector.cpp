#include "myParticle.hpp"
#include <ROOT/RDataFrame.hxx>
#include <ROOT/RSnapshotOptions.hxx>
#include <TFile.h>
#include <TRandom3.h>
#include <TSystem.h>
#include <TTree.h>
#include <ctype.h>
#include <vector>

using RDF = ROOT::RDataFrame;
using namespace std;

void myVector() {

  // No real need to load because we link with it in CMakeLists
  // gSystem->Load("libmyParticle.so");
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

void rdf_example() {
  // No real need to load because we link with it in CMakeLists
  // gSystem->Load("libmyParticle.so");
  constexpr size_t N = 10;       // Number of Particles
  constexpr size_t nEvents = 10; // Number of events

  RDF df(nEvents);

  auto rng = TRandom3();
  auto df_vec = df.Define("particles", [&rng]() {
                    return myParticle(
                        {(int)rng.Gaus(), rng.Gaus(), rng.Gaus(), rng.Gaus()});
                  }).Define("part_vec", [&rng]() {
    vector<myParticle> vmP;
    for (int id = 0; id < N; id++) {
      vmP.push_back({id, rng.Gaus(), rng.Gaus(), rng.Gaus()});
    }
    return vmP;
  });

  ROOT::RDF::RSnapshotOptions opts;
  opts.fMode = "UPDATE";
  df_vec.Snapshot("parts", "testfile.root", {"particles"});
  df_vec.Snapshot("vec", "testfile.root", {"part_vec"}, opts);
}

int main() {
  myVector();
  rdf_example();
  return 0;
}
