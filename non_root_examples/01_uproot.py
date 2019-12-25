"""
An example of reading a root file using uproot
and using the data as numpy arrays.

"""
import uproot
import numpy as np
import matplotlib.pyplot as plt

path = "../Data/"
filename = path + "higgs_small.root"

rt_file = uproot.open(filename)
