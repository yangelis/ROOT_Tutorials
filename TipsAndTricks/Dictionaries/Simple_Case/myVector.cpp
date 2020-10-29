#include "myParticle.h"
#include <ROOT/RDataFrame.hxx>
#include <ROOT/RSnapshotOptions.hxx>
#include <TFile.h>
#include <TRandom3.h>
#include <TSystem.h>
#include <TTree.h>
#include <ctype.h>
#include <vector>

using RDF = ROOT::RDataFrame;
using std::vector;

void myVector() {

  // gSystem->Load("libmyParticle.so");
  constexpr size_t N = 10;       // Number of Particles
  constexpr size_t nEvents = 10; // Number of events
  TFile *f =
      TFile::Open("vector_particles.root", "RECREATE"); // Creating a root file
  vector<myParticle> particles; // std::vector containing myParticles
  TTree *t =
      new TTree("tvec", "Tree with vectors of myParticles"); // Create a TTree
  t->Branch("particles", &particles);                        // Create a branch

  auto rng = TRandom3();
  double px, py, pz;
  for (size_t event = 0; event < nEvents; event++) {
    particles.clear();
    for (int id = 0; id < N; id++) {
      px = rng.Gaus();
      py = rng.Gaus();
      pz = rng.Gaus();
      particles.push_back({id, px, py, pz});
    }
    t->Fill();
  }
  f->Write();
  delete f;
}

void rdf_example() {
  // gSystem->Load("libmyParticle.so");
  constexpr size_t N = 10;       // Number of Particles
  constexpr size_t nEvents = 10; // Number of events

  RDF df(nEvents);

  auto rng = TRandom3();
  auto df_vec = df.Define("particles", [&rng]() {
                    return myParticle(
                        {(int)rng.Gaus(), rng.Gaus(), rng.Gaus(), rng.Gaus()});
                  }).Define("part_vec", [&rng]() {
    vector<myParticle> particles;
    for (int id = 0; id < N; id++) {
      particles.push_back({id, rng.Gaus(), rng.Gaus(), rng.Gaus()});
    }
    return particles;
  });

  ROOT::RDF::RSnapshotOptions opts;
  // NOTE: we need the Snapshot Options in order to save to
  // the same file, because the default is  "RECREATE"
  opts.fMode = "UPDATE";
  df_vec.Snapshot("particles", "testfile.root", {"particles"});
  df_vec.Snapshot("vectors", "testfile.root", {"part_vec"}, opts);
}

int main() {
  myVector();
  rdf_example();
  return 0;
}
