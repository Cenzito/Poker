#include "pbPlots.hpp"
#include "supportLib.hpp"
#include <vector>

using namespace std;

int main() {
    RGBABitmapImageReference* imageRef = CreateRGBABitmapImageReference();

    vector<double> x = {-2, -1, 0, 1, 2};
    vector<double> y = {2, -1, -2, -1, 2};

    StringReference *errorMessage = new StringReference();

    // Plot the scatter plot
    bool success = DrawScatterPlot(imageRef, 600, 400, &x, &y, errorMessage);

    if(success){
        // Convert to PNG and write to file
        vector<double> *pngData = ConvertToPNG(imageRef->image);
        WriteToFile(pngData, "plot.png");

        // Clean up
        DeleteImage(imageRef->image);
        delete pngData; // Free dynamically allocated memory
    } else {
        // Handle error
        cout << "Error: " << errorMessage->string << endl;
    }

    delete errorMessage; // Don't forget to delete the dynamically allocated memory

    return 0;
}
