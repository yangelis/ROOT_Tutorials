"""
An example of reading a root file using uproot
and using the data as numpy arrays.

"""
import uproot
import numpy as np
import matplotlib.pyplot as plt

path = "../Data/"
filename = path + "higgs_small.root"

rt_file = uproot.open(filename, )
print(rt_file.keys())  # printing the available trees of the file


# Now lets assign a variable to the signal tree
# and see what branches it contains
signal_tree = rt_file['TreeS']
signal_tree.show()
print(20*'#')
# we can also obtain easily the total number of entries
print(f'Number of entries: {signal_tree.numentries}')


# Lets convert one branch into an array and plot it
m_bb = signal_tree.array('m_bb')
# m_bb will be a numpy array with the same type as the branch eg 8-byte floating
# which means a 64-bit floating-point number
print(m_bb.dtype)
# Double checking the size of the array:
print(m_bb.shape)
# We can even make a histogram with matplotlib
plt.hist(m_bb, bins=20)
plt.xlabel('m_bb')
plt.title('Histogram from a branch')
plt.show()


# we can even extract some of the branches into a python dict
# containing numpy arrays for each branch
lepton_info = signal_tree.arrays(['lepton_*'])
print(lepton_info.keys())
