#include <ROOT/RDataFrame.hxx>
#include <iostream>
#include <string>
#include <vector>

void writing_root_files()
{
  // declaring a variable for the dataframe
  ROOT::RDataFrame df("TreeS", "../Data/higgs_small.root");

  // Here we read a file and saving some of its branches to another file
  std::vector<std::string> columns = {"lepton_pT", "lepton_eta"};

  // Snapshot saves in a new root file in a new Tree
  df.Snapshot("myTree", "my_output.root", columns);
  // or we could use
  // df.Snapshot("myTree", "my_output.root", {"lepton_pT", "lepton_eta"});
}

int main()
{
  writing_root_files();

  return 0;
}
