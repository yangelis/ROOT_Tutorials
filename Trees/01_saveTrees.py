from ROOT import TFile, TTree, TRandom3, gRandom, std
import numpy as np
from array import array


"""
This function demonstrates a way to write data to a TTree,
with each set of px,py,xx being 1 entry.
It uses python arrays of size 1 in order to
declare double and integer variables.
The same can be done with numpy arrays.
"""

def makeTTree(n_points, tp="arr"):
    tree = TTree("pytree", "A simple tree")

    if tp == "arr":
        px = array("d", [0])
        py = array("d", [0])
        xx = array("i", [0])
    elif tp == "np":
        px = np.array([0], dtype=np.float)
        py = np.array([0], dtype=np.float)
        xx = np.array([0], dtype=np.int)

    tree.Branch("px", px, "px/D")
    tree.Branch("py", py, "py/D")
    tree.Branch("xx", xx, "xx/I")
    for _ in range(n_points):
        px[0] = gRandom.Gaus(0.3)
        py[0] = gRandom.Uniform() * 30 - 15
        xx[0] = gRandom.Poisson(10)
        tree.Fill()
    return tree


"""
This function saves data to a TTree, using C++ std::vector through ROOT,
or python arrays or even numpy arrays.
Now we can do more complicated things, like having more instances per entry.
"""


def makeTTree_vector(n_events=10, n_points=10, ar_type="std"):
    tree = TTree("vectree", "a tree from vectors")

    if ar_type == "python":
        px = array("d", n_points * [0])
        py = array("d", n_points * [0])
        xx = array("i", n_points * [0])
        tree.Branch("px", px, f"px[{n_points}]/D")
        tree.Branch("py", py, f"py[{n_points}]/D")
        tree.Branch("xx", xx, f"xx[{n_points}]/I")
    elif ar_type == "numpy":
        px = np.array(n_points * [0], dtype=np.float)
        py = np.array(n_points * [0], dtype=np.float)
        xx = np.array(n_points * [0], dtype=np.int)
        tree.Branch("px", px, f"px[{n_points}]/D")
        tree.Branch("py", py, f"py[{n_points}]/D")
        tree.Branch("xx", xx, f"xx[{n_points}]/I")
    elif ar_type == "std":
        px = std.vector("double")(n_points)
        py = std.vector("double")(n_points)
        xx = std.vector("int")(n_points)
        tree.Branch("px", px)
        tree.Branch("py", py)
        tree.Branch("xx", xx)

    for j in range(n_events):
        for i in range(n_points):
            px[i] = gRandom.Gaus(0.3)
            py[i] = gRandom.Uniform() * 30 - 15
            xx[i] = gRandom.Poisson(10)
        tree.Fill()
    return tree


hfile = TFile("myfile.root", "RECREATE")
myTree = makeTTree(100)
myTree.Write()
myTree = makeTTree_vector(10, 10, "numpy")
myTree.Write()
hfile.Close()
