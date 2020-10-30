#include <TFile.h>
#include <TTree.h>
#include <memory>
#include <vector>

using namespace std;

int main(int argc, char **argv) {
  if (argc == 1) {
    fprintf(stderr, "No file provided. Please run 01_saveTrees first\n");
    exit(1);
  }

  TFile *hfile = TFile::Open(argv[1], "READ");
  // or
  // TFile hfile(argv[1], "READ");

  // check that the file exist
  if (!hfile) {
    fprintf(stderr, "No file provided. Please run 01_saveTrees first\n");
    exit(1);
  }

  // Reading from the simple tree
  TTree *tree = nullptr;
  double px, py;
  int xx;

  hfile->GetObject("tree", tree);
  tree->SetBranchAddress("px", &px);
  tree->SetBranchAddress("py", &py);
  tree->SetBranchAddress("xx", &xx);
  size_t nEntries = (size_t)tree->GetEntries();

  for (size_t i = 0; i < nEntries; ++i) {
    tree->GetEntry(i);
    // Scientific code here ...
    // printf("%f, %f\n", px, py);
  }

  // Reading from the tree containing vectors
  TTree *vectree = nullptr;
  vector<double> *vec_px = nullptr;
  vector<double> *vec_py = nullptr;
  vector<int> *vec_xx = nullptr;
  hfile->GetObject("vectree", vectree);
  vectree->SetBranchAddress("px", &vec_px);
  vectree->SetBranchAddress("py", &vec_py);
  vectree->SetBranchAddress("xx", &vec_xx);
  nEntries = (size_t)vectree->GetEntries(); // just reusing the variable

  for (size_t i = 0; i < nEntries; ++i) {
    vectree->GetEntry(i);
    // More scientific code here ...
  }

  delete tree;
  delete vectree;
  delete hfile;
  return 0;
}
