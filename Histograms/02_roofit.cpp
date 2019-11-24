// This is an example program using RooFit with binned ML fit
// using some random data acting like the Z mass.

#include <TH1D.h>
#include <TCanvas.h>
#include <TApplication.h>
#include <RooRealVar.h>
#include <RooDataHist.h>
#include <RooGaussian.h>
#include <RooPlot.h>

#include <vector>

using namespace std;
using namespace RooFit;

int main(int argc, char **argv)
{
    TApplication theApp("App", &argc, argv);
    auto canvas = new TCanvas();
    canvas->SetBorderMode(0);
    const vector<double> zPoints = {93.4, 89.3, 94.9, 90.7, 89.9, 89.3, 90.9, 93.8, 91.3, 92.9,
                                    91.4, 87.8, 91.5, 89.9, 94.4, 91.3, 88.3, 91.9, 95.4, 91.1,
                                    92.1, 91.7, 94.3, 92.0, 89.9, 90.6, 91.7, 90.4, 92.6, 93.8,
                                    90.9, 90.4, 89.3, 94.6, 90.6, 94.1, 89.7, 90.0, 92.8, 93.8,
                                    93.8, 91.7, 88.2, 92.9, 86.6, 90.6, 89.9, 95.3, 92.5, 96.5};

    auto zmass_5bins = new TH1D("zmass_5bins", "Binned LH Gauss Fit", 20, 80, 100);

    for (const auto &point : zPoints)
    {
        zmass_5bins->Fill(point);
    }
    RooRealVar x("x", "m_{Z}", 80, 100);
    RooRealVar mean("mean", "mean Z mass", 90, 85, 100);
    RooRealVar sigma("sigma", "mass sigma", 2, 1, 5);
    RooGaussian gauss("gauss", "pd", x, mean, sigma);
    RooDataHist dh("dh", "data", RooArgList(x), zmass_5bins);

    auto result_b5 = gauss.fitTo(dh, PrintLevel(0));

    auto xframe = x.frame();
    dh.plotOn(xframe);
    gauss.plotOn(xframe);
    xframe->Draw();
    zmass_5bins->Draw("SAME");
    canvas->Draw();

    mean.Print();
    sigma.Print();

    cout << "To exit, quit ROOT from the File menu of the plot" << endl;
    theApp.Run(true);
    canvas->Close();

    delete canvas;
    delete zmass_5bins;
    return 0;
}