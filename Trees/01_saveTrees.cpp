#include <TFile.h>
#include <TRandom3.h>
#include <TTree.h>
#include <memory>
#include <vector>

using namespace std;

shared_ptr<TTree> makeTTree(const size_t nPoints) {

  shared_ptr<TTree> tree = make_shared<TTree>("tree", "A simple tree");
  double px, py;
  int *xx = new int;
  tree->Branch("px", &px);
  tree->Branch("py", &py);
  tree->Branch("xx", xx);
  for (size_t i = 0; i < nPoints; ++i) {
    px = gRandom->Gaus(0, 3);
    py = gRandom->Uniform() * 30 - 15;
    *xx = gRandom->Poisson(10);
    tree->Fill();
  }
  return tree;
};

shared_ptr<TTree> makeTTree_vectors(const size_t nEvents,
                                    const size_t nPoints) {

  shared_ptr<TTree> tree = make_shared<TTree>("vectree", "tree of vectors");
  vector<double> px, py;
  vector<int> *xx = new vector<int>;
  tree->Branch("px", &px);
  tree->Branch("py", &py);
  tree->Branch("xx", &xx);
  for (size_t j = 0; j < nEvents; ++j) {
    px.clear();
    py.clear();
    xx->clear();
    for (size_t i = 0; i < nPoints; ++i) {
      px.push_back(gRandom->Gaus(0, 3));
      py.push_back(gRandom->Uniform() * 30 - 15);
      xx->push_back(gRandom->Poisson(10));
    }
    tree->Fill();
  }
  return tree;
};

int main(int argc, char **argv) {
  TFile hfile("myfile.root", "RECREATE");
  auto myTree = makeTTree(100);
  myTree->Write();
  auto myVecTree = makeTTree_vectors(10, 10);
  myVecTree->Write();
  hfile.Close();
  return 0;
}
