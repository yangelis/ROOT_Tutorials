import ROOT

canvas = ROOT.TCanvas()
zPoints = [93.4, 89.3, 94.9, 90.7, 89.9, 89.3, 90.9, 93.8, 91.3, 92.9, 91.4, 87.8, 91.5, 89.9, 94.4, 91.3, 88.3, 91.9,
           95.4, 91.1, 92.1, 91.7, 94.3, 92.0, 89.9, 90.6, 91.7, 90.4, 92.6, 93.8, 90.9, 90.4, 89.3,
           94.6, 90.6, 94.1, 89.7, 90.0, 92.8, 93.8, 93.8, 91.7, 88.2, 92.9, 86.6, 90.6, 89.9, 95.3, 92.5, 96.5]

zmass_5bins = ROOT.TH1D("zmass_5bins", "Binned LH Gauss Fit", 20, 80, 100)
for p in zPoints:
    zmass_5bins.Fill(p)

x = ROOT.RooRealVar("x_b5", "m_{Z} (GeV)", 80, 100)
mean = ROOT.RooRealVar("mean", "mean Z mass", 90, 85, 100)
sigma = ROOT.RooRealVar("sigma", "mass sigma", 2, 1, 5)
gauss = ROOT.RooGaussian("gauss", "Gaussian PDF", x, mean, sigma)
dh = ROOT.RooDataHist("dh", "data", ROOT.RooArgList(x), zmass_5bins)


result = gauss.fitTo(dh, ROOT.RooFit.PrintLevel(0))

mean.Print()
sigma.Print()

xframe = x.frame()
dh.plotOn(xframe, ROOT.RooLinkedList())
gauss.plotOn(xframe)
xframe.Draw()
zmass_5bins.Draw("SAME")
canvas.Draw()




input('Press enter to close.')