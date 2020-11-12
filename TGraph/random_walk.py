from ROOT import TRandom3, TCanvas, TGraph, TGraph2D, gROOT

def random_walk2d(N = 1000):
    rng = TRandom3()
    xy_scatter = TGraph()
    xy_scatter.SetTitle(";x;y")
    x = 0; y = 0
    for i in range(0, N):
        xy_scatter.SetPoint(i, x, y)
        x += (rng.Uniform() - 0.5) / 2.0;
        y += (rng.Uniform() - 0.5) / 2.0;

    c = TCanvas("2d")
    xy_scatter.Draw()
    c.Draw()
    input('Press Enter to close')

def random_walk3d(N = 1000):
    rng = TRandom3()
    xyz_scatter = TGraph2D()
    xyz_scatter.SetTitle(";x;y;z")
    x = 0.0; y = 0.0; z = 0.0
    for i in range(0, N):
        xyz_scatter.SetPoint(i, x, y, z)
        x += (rng.Uniform() - 0.5) / 2.0;
        y += (rng.Uniform() - 0.5) / 2.0;
        z += (rng.Uniform() - 0.5) / 2.0;

    c = TCanvas("3d")
    xyz_scatter.Draw("LINE")
    c.Draw()
    input('Press Enter to close')


def main():
    gROOT.SetBatch(False)
    random_walk2d()
    random_walk3d()

if __name__ == "__main__":
    main()
