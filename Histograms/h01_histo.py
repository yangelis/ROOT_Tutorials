# Importing ROOT functions
from ROOT import TH1D, TCanvas, TRandom3

N = 10000
canvas = TCanvas()
h1 = TH1D('h1', 'A simple histogram', 100, -5, 5)
h1.FillRandom('gaus', N)
h1.Draw()
canvas.Update()

input('Press Enter to close')
