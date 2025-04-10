#include "TonysSPGRAM.h"
#include "WavFile.h"
#include "TonysFFT.h"
#include "CmplxNum.h"
#include "TGraph.h"

#include "iostream"
#include "matplot/matplot.h"
#include "chrono"

int main() {
	TonysFFT fft;
	WavFile wav;
	TonysSPGRAM spectogram;
    TGraph graph;

	using namespace std;
	using namespace matplot;

	string fileName = "vowel_a2-46967.wav";

	wav.load(fileName);
	
	vector<int16_t> audioData = wav.getAudioData();

	spectogram.GenerateSpectogram(audioData, 1024);

    vector<vector<CmplxNum>> ComplexSpectogramData = spectogram.GetSpectogramMatrix();

	vector<vector<int16_t>> SpectogramData = spectogram.GetMagnitudeSpectogramMatrix();


    //
    //
    // Spectogram
    //
    //


    //range

	vector<int> Frequencies = spectogram.GetFreuqencies();

    //domain

    vector<double> indicies = spectogram.GetTime();

    //depth/colour

    vector<vector<int16_t>> normalisedData = graph.normaliseData(SpectogramData);


    auto h = imagesc(normalisedData);
    colorbar();
    xlabel("Frequency Bins");
    ylabel("Time Bins");
    title("Normalised Spectogram");
    show();









    //for (size_t i = 0; i < SpectogramData.size(); i++)
    //{
    //    vector<int16_t> range = SpectogramData[i];

    //    // Create a figure
    //    matplot::figure();

    //    // Plot the data
    //    matplot::plot(Frequencies, range);

    //    // Set axis labels
    //    matplot::xlabel("Domain (Indices)");
    //    matplot::ylabel("Range (SpectogramData[1])");

    //    // Display the plot
    //    matplot::show();

    //    // Wait for user to press Enter before proceeding to the next plot
    //    cout << "Press Enter to continue to the next plot...";
    //    cin.get();  // Waits for the user to press Enter
    //}
}