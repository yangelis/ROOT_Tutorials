#include <TApplication.h>
#include <TCanvas.h>
#include <TGraph.h>
#include <TGraph2D.h>
#include <TRandom3.h>
#include <vector>

using namespace std;

void random_walk2d(const size_t N = 10000)
{

  TRandom3 rng{};
  auto xy_scatter = new TGraph();
  xy_scatter->SetTitle(";x;y");
  double x = 0, y = 0;
  for (size_t i = 0; i < N; ++i) {
    xy_scatter->SetPoint(i, x, y);
    x += (rng.Uniform() - 0.5) / 2.0;
    y += (rng.Uniform() - 0.5) / 2.0;
  }

  auto c = new TCanvas("2d");
  xy_scatter->Draw();
  c->Draw();
}

void random_walk3d(const size_t N = 10000)
{

  TRandom3 rng{};

  vector<double> x(N), y(N), z(N);
  x[0] = y[0] = z[0] = 0.0;
  for (size_t i = 0; i < N; ++i) {
    x[i] = x[i - 1] + (rng.Uniform() - 0.5) / 2.0;
    y[i] = y[i - 1] + (rng.Uniform() - 0.5) / 2.0;
    z[i] = z[i - 1] + (rng.Uniform() - 0.5) / 2.0;
  }

  auto xyz_scatter = new TGraph2D(N, x.data(), y.data(), z.data());
  xyz_scatter->SetTitle(";x;y;z");

  auto c = new TCanvas("3d");
  xyz_scatter->Draw("LINE");
  c->Draw();
}

int main(int agrc, char* argv[])
{
  TApplication app("Random walk", nullptr, nullptr);

  random_walk2d();
  random_walk3d();
  app.Run();

  return 0;
}
