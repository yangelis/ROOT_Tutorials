# Let's read the same file and tree as before
# but now just pick two branches and save the
# in a different file.

import ROOT
from ROOT import RDataFrame
df = RDataFrame('TreeS','../Data/higgs_small.root')

# Sometimes when choosing the branch name 
# python string dont work, so we are using
# a ROOT vector of string, with the desired
# branches.
columns = ROOT.vector('string')() 
columns.push_back('lepton_pT')
columns.push_back('lepton_eta')
# Snapshot saves in a new root file in a new Tree 
df.Snapshot('myTree','my_output.root',columns)
