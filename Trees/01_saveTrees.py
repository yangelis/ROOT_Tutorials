from ROOT import TFile, TTree, TRandom3, gRandom, std
import numpy as np
from array import array


"""
This function demonstrates a way to write data to a TTree. 
It uses python arrays of size 1 in order to 
declare double and integer variables.
The same can be done with numpy arrays.
"""


def makeTTree_array(n_points):
    tree = TTree("pytree", "my tree")

    tp = "arr"
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
    for i in range(n_points):
        px[0] = gRandom.Gaus(0.3)
        py[0] = gRandom.Uniform() * 30 - 15
        xx[0] = gRandom.Poisson(10)
        tree.Fill()
    return tree


"""
This function saves data to a TTree, using C++ std::vector,
with the same way of declaring arrays of size 1.
"""


def makeTTree_vector_v1(n_points):
    tree = TTree("vec_tree1", "my tree")

    px = std.vector("double")(1)
    py = std.vector("double")(1)
    xx = std.vector("int")(1)

    tree.Branch("px", px)
    tree.Branch("py", py)
    tree.Branch("xx", xx)
    for i in range(n_points):
        px[0] = gRandom.Gaus(0.3)
        py[0] = gRandom.Uniform() * 30 - 15
        xx[0] = gRandom.Poisson(10)
        tree.Fill()
    return tree


"""
This function saves data to a TTree, using C++ std::vector.
BUT, with this method we can save all this data to 
correspond to the same row. 
"""


def makeTTree_vector_v2(n_points):
    tree = TTree("vec_tree2", "my tree")

    px = std.vector("double")(n_points)
    py = std.vector("double")(n_points)
    xx = std.vector("int")(n_points)

    tree.Branch("px", px)
    tree.Branch("py", py)
    tree.Branch("xx", xx)
    for i in range(n_points):
        px[i] = gRandom.Gaus(0.3)
        py[i] = gRandom.Uniform() * 30 - 15
        xx[i] = gRandom.Poisson(10)
    tree.Fill()
    return tree


hfile = TFile("myfile.root", "RECREATE")
myTree = makeTTree_array(100)
myTree.Write()
myTree = makeTTree_vector_v1(100)
myTree.Write()
myTree = makeTTree_vector_v2(100)
myTree.Write()
hfile.Close()
