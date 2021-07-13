#include <TApplication.h>
#include <TCanvas.h>
#include <TGraph.h>
#include <TMath.h>
#include <TMultiGraph.h>
#include <TRandom3.h>
#include <iostream>

using namespace std;

constexpr double R = 1.0;

struct Point {
  double x, y;

  double r() const { return sqrt(x * x + y * y); }
};

double pi_monte_carlo(const size_t n = 100000, const bool plot = true)
{
  TRandom3 rng(0);

  size_t p_inside_rect   = n;
  size_t p_inside_circle = 0;
  vector<Point> points_rect(n); // we know their size
  vector<Point> points_circle;
  points_circle.reserve(n); // pre-allocating a bigger size

  auto in_circle = [](const Point& p) {
    if (p.r() < R) {
      return true;
    }
    return false;
  };

  for (size_t i = 0; i < n; ++i) {
    points_rect[i] = {rng.Uniform(-1.0, 1.0), rng.Uniform(-1.0, 1.0)};
    if (in_circle(points_rect[i])) {
      points_circle.emplace_back(points_rect[i]);
      ++p_inside_circle;
    }
  }

  if (plot) {
    auto* mg     = new TMultiGraph();
    auto* rect   = new TGraph();
    auto* circle = new TGraph();
    for (size_t i = 0; i < n; ++i) {
      rect->SetPoint(static_cast<int>(i), points_rect[i].x, points_rect[i].y);
    }
    for (size_t i = 0; i < points_circle.size(); ++i) {
      circle->SetPoint(static_cast<int>(i), points_circle[i].x,
                       points_circle[i].y);
    }

    rect->SetMarkerStyle(20);
    circle->SetMarkerStyle(20);
    circle->SetMarkerColor(kRed);
    mg->Add(rect);
    mg->Add(circle);
    mg->Draw("ap");
  }
  return 4.0 * static_cast<double>(p_inside_circle) /
         static_cast<double>(p_inside_rect);
}

int main()
{
  TApplication app("pimc", nullptr, nullptr);

  constexpr size_t N = 10000;

  auto graph = new TGraph();
  graph->SetTitle(";N points;approx/#pi");
  int i = 0;
  for (size_t n = 10; n < N; n += 10) {
    graph->SetPoint(i++, static_cast<double>(n),
                    pi_monte_carlo(n, false) / TMath::Pi());
  }

  auto* c = new TCanvas();
  graph->Draw("AC");
  c->Draw();

  cout << "done\n";
  app.Run();
  return 0;
}
