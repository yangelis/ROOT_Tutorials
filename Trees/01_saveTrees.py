from ROOT import TFile, TTree, TRandom3, gRandom
from array import array


def makeTTree(n_points):
    tree = TTree('tree', 'tree')

    px = array('d', n_points*[0])
    py = array('d', n_points*[0])
    xx = array('i', n_points*[0])

    tree.Branch('px', px, 'px/D')
    tree.Branch('py', py, 'py/D')
    tree.Branch('xx', xx, 'xx/I')
    for i in range(n_points):
        px[0] = gRandom.Gaus(0.3)
        py[0] = gRandom.Uniform() * 30 - 15
        xx[0] = gRandom.Poisson(10)
        tree.Fill()
    return tree


hfile = TFile("myfile.root", "RECREATE")
myTree = makeTTree(100)
myTree.Write()
hfile.Write()
hfile.Close()
