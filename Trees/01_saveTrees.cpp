#include <TFile.h>
#include <TTree.h>
#include <TRandom3.h>

using namespace std;

TTree *makeTTree(const int n_points)
{

    TTree *tree = new TTree("tree", "tree");
    double px, py;
    int *xx = new int;
    tree->Branch("px", &px);
    tree->Branch("py", &py);
    tree->Branch("xx", xx);
    for (int i = 0; i < n_points; ++i)
    {
        px = gRandom->Gaus(0, 3);
        py = gRandom->Uniform() * 30 - 15;
        *xx = gRandom->Poisson(10);
        tree->Fill();
    }
    return tree;
};

int main(int argc, char **argv)
{
    TFile hfile("myfile.root", "RECREATE");
    auto myTree = makeTTree(100);
    myTree->Write();
    hfile.Write();
    hfile.Close();
    return 0;
}