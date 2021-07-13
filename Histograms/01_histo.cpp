/* In order to compile the program run:
g++ 01_histo.cpp -o 01_histo.exe `root-config --cflags --glibs`
*/

/// Including ROOT libradies:
#include <TApplication.h> // For actually seeing the canvases with compiled programs
#include <TCanvas.h>      // For the Canvas where plot are being drawed
#include <TH1D.h>         // TH1D for 1D histogram with doubles
#include <TRandom3.h>     // Random number generators
/// C++ includes
#include <iostream>

using namespace std;

int main(int argc, char** argv)
{
  TApplication theApp("App", &argc, argv); // Declaring the app
  auto canvas     = new TCanvas();         // Creating a new canvas
  auto h1         = new TH1D("h1", "A simple histogram", 100, -5,
                     5); // A new histogram with 100 bins, from -5 to 5
  constexpr int N = 10000;
  /// We fill the histogram in the loop using the Fill method
  for (Int_t i = 0; i < N; ++i) {
    h1->Fill(gRandom->Gaus());
  }
  h1->Draw(); // Drawing the histo
  cout << "To exit, quit ROOT from the File menu of the plot" << endl;
  theApp.Run(true); // Running the app
  canvas->Close();  // Closing the canvas after done
  /// Deleting objects declared with 'new'
  delete canvas;
  delete h1;
  return 0;
}
