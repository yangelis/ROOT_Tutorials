import sys
from ROOT import TFile, TTree, std, AddressOf
import numpy as np
from array import array

def main(filename, which_tree, method="arr"):
    inputFile = TFile.Open(filename)

    if which_tree == "tree":
        tree = inputFile.Get("tree")
        nEntries = tree.GetEntries()
        if method == "arr":
            px = array('d', [0.])
            py = array('d', [0.])
            xx = array('i', [0])
            tree.SetBranchAddress("px", px)
            tree.SetBranchAddress("py", py)
            tree.SetBranchAddress("xx", xx)

            for i in range(0, nEntries):
                tree.GetEntry(i)
                # Scientific code here...
                print(px[0], py[0], xx[0])
        elif method == "numpy":
            px = np.array([0,], dtype=np.float)
            py = np.array([0.], dtype=np.float)
            xx = np.array([0], dtype=np.int)
            tree.SetBranchAddress("px", px)
            tree.SetBranchAddress("py", py)
            tree.SetBranchAddress("xx", xx)

            for i in range(0, nEntries):
                tree.GetEntry(i)
                # Scientific code here...
                print(px[0], py[0], xx[0])

    elif which_tree == "vectree":
        vectree = inputFile.Get("vectree")
        nEntries = vectree.GetEntries()

        if method == "arr":
            for _, event in enumerate(vectree):
                px = [a for a in event.px]
                py = [a for a in event.py]
                xx = [a for a in event.xx]
                # Scientific code here...


        elif method == "numpy":
            px = np.empty([nEntries, 10])
            py = np.empty([nEntries, 10])
            xx = np.empty([nEntries, 10])

            for i, event in enumerate(vectree):
                px[i] = [a for a in event.px]
                py[i] = [a for a in event.py]
                xx[i] = [a for a in event.xx]
                # Scientific code here...

        elif method == "std":
            px = std.vector("double")()
            py = std.vector("double")()
            xx = std.vector("int")()
            vectree.SetBranchAddress("px", px)
            vectree.SetBranchAddress("py", py)
            vectree.SetBranchAddress("xx", xx)

            for i in range(0, nEntries):
                vectree.GetEntry(i)
                # Scientific code here...
                # print(px, py, xx)

    inputFile.Close()

if __name__ == "__main__":
    main(sys.argv[1], sys.argv[2], sys.argv[3])
