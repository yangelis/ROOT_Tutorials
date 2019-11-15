import ROOT
from ROOT import RDataFrame
# declaring a variable for the dataframe
df = RDataFrame('TreeS','../Data/higgs_small.root')

# Let's print the names of the branches:
for column in df.GetColumnNames():
    print(column)


# We can draw a histogram for a branch like:

hist_lep_pt = df.Histo1D('lepton_pT')
hist_lep_pt.Draw()



input('Press enter to close.')

