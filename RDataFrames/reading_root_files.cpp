#include <ROOT/RDataFrame.hxx>
#include <TApplication.h>
#include <TCanvas.h>
#include <iostream>

using namespace std;

void reading_root_files()
{
  // declaring a variable for the dataframe
  ROOT::RDataFrame df("TreeS", "../Data/higgs_small.root");

  // Let's print the names of the branches:
  cout << "Branches in file: \n";
  for (const auto& column : df.GetColumnNames()) {
    cout << column << '\n';
  }

  // We can draw a histogram for a branch like:
  auto hist_lep_pt = df.Histo1D("lepton_pT");
  auto* c          = new TCanvas("c", "Pt histogram", 1366, 768);
  // use DrawClone because hist_lep_pt will be deleted after this scope
  hist_lep_pt->DrawClone();
  c->Draw();
}

int main(int argc, char** argv)
{
  TApplication theApp("App", &argc, argv);
  reading_root_files();
  cout << "To exit, quit ROOT from the File menu of the plot" << '\n';
  theApp.Run(true);
  return 0;
}
