#include <ROOT/RDataFrame.hxx>
#include <iostream>
#include <vector>
#include <string>

using namespace std;
using RDF = ROOT::RDataFrame;

int main(int argc, char **argv)
{

    // declaring a variable for the dataframe
    RDF df("TreeS", "../Data/higgs_small.root");

    // Sometimes when choosing the branch name
    // python string dont work, so we are using
    // a ROOT vector of string, with the desired
    // branches
    // Let's print the names of the branches:

    vector<string> columns = {"lepton_pT", "lepton_eta"};

    // Snapshot saves in a new root file in a new Tree
    df.Snapshot("myTree", "my_output.root", columns);

    return 0;
}