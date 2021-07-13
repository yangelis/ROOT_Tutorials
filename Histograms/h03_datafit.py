"""
In this example, we gonna create some random data using two distributions
and save them on a csv file. Then, we will read that data, put them in a histogram
using the same range as they created with and fit some functions on them using ROOT
"""

import ROOT
from ROOT import TFile, TF1, TH1D, TCanvas
import numpy as np


"""
This function just creates the sample data
"""


def create_data():
    import scipy.stats as stats

    x = np.linspace(10, 20, 1000)
    y1 = stats.expon.pdf(x) * 10 + 0.0005 * stats.cauchy.pdf(x, loc=14)
    y2 = stats.expon.pdf(x) * 20 + 0.01 * stats.cauchy.pdf(x, loc=12)
    y3 = stats.expon.pdf(x) * 100 + 0.041 * stats.cauchy.pdf(x, loc=16)
    np.savetxt("../Data/fit_test.csv", [y1, y2, y3], delimiter=",", fmt="%f")


"""
Read the file using numpy's genfromtxt, in orded to generate
numpy arrays with the data. You must use the delimeter that the data have.
"""
try:
    data = np.genfromtxt("../Data/fit_test.csv", delimiter=",")
except:
    # Run the function if you need the data file
    create_data()
    data = np.genfromtxt("../Data/fit_test.csv", delimiter=",")

# We will use just the first row
y = data[0]

""" Declare a ROOT histogram for the data.
The range was choosen in order to match the "real" x
and the number of bins correspond to the number of columns.
"""
hist = TH1D("hist", "My histo", 1000, 10, 20)


# We fill each bin in this range with the data we read
for i in range(y.size):
    hist.SetBinContent(i + 1, y[i])


"""
Now in order to fit the data, we need 2 functions.
Here, we show the most weird, complicated and powerful
way to do it!

First we write C++ functions for the exponential and cauchy
distributions. Then, another function calls these two.
The total fit uses that function to fin the data.
"""

# C++ code declaring the exponential distribution
expo = """
double expon(double *x, double *par)
{
  return par[0] * TMath::Exp(-1.0 * x[0]);
};
"""

# With this way we can use that function through ROOT
ROOT.gInterpreter.Declare(expo)


# C++ code declaring the cauchy distribution
cauchy = """
double chy(double *x, double *par)
{
  return par[0]/(TMath::Pi()*( 1 + pow( x[0] - par[1], 2 ) ) ) ;
};
"""

# Same as before
ROOT.gInterpreter.Declare(cauchy)


# The function of the total fit
fitfunc = """
double fitf(double *x, double *par)
{
  return expon(x,par) + chy(x,&par[1]) ;
};
"""
# And again
ROOT.gInterpreter.Declare(fitfunc)

# Now we declare a TF1 function for the total fit, using the function we declared above
fitf = TF1("fit", ROOT.fitf, 10, 20, 3)

# Making easier the fit setting the cauchy parameter at the peak
fitf.SetParameter(2, 14)
# Setting the line style
fitf.SetLineStyle(1)

# Fitting the data, using the "R" we tell it to use the range
# used in the TF1 declaration
canvas = TCanvas("c1", "Fiting histogram", 1366, 768)
hist.Fit(fitf, "R")
hist.DrawClone()
canvas.Draw()

input("Press enter to close.")

