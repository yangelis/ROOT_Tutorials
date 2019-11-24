#include <TH1D.h>
#include <TCanvas.h>
#include <TApplication.h>
#include <ROOT/RDataFrame.hxx>
#include <iostream>

using namespace std;
using RDF = ROOT::RDataFrame;

int main(int argc, char **argv)
{
    TApplication theApp("App", &argc, argv);

    // declaring a variable for the dataframe
    RDF df("TreeS", "../Data/higgs_small.root");

    // Let's print the names of the branches:
    for (const auto column : df.GetColumnNames())
    {
        cout << column << '\n';
    }

    // We can draw a histogram for a branch like:
    auto hist_lep_pt = df.Histo1D("lepton_pT");
    hist_lep_pt->Draw();

    cout << "To exit, quit ROOT from the File menu of the plot" << '\n';
    theApp.Run(true);
    return 0;
}