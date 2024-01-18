#include "pbPlots.hpp"
#include "supportLib.hpp"
#include <vector> // Include this for std::vector

using namespace std; // This allows you to use 'vector' instead of 'std::vector'

int main() {
    RGBABitmapImageReference* imageRef = CreateRGBABitmapImageReference();

    // Define your vectors
    vector<double> x = {-2, -1, 0, 1, 2};
    vector<double> y = {2, -1, -2, -1, 2};

    // Plot the scatter plot
    DrawScatterPlot(imageRef, 600, 400, &x, &y);

    // Convert to PNG and write to file
    vector<double> *pngData = ConvertToPNG(imageRef->image);
    WriteToFile(pngData, "plot.png");

    // Clean up
    DeleteImage(imageRef->image);
    delete pngData; // Don't forget to delete the dynamically allocated memory

    return 0;
}
