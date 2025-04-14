#include "TonysSPGRAM.h"
#include "WavFile.h"
#include "TonysFFT.h"
#include "CmplxNum.h"
#include "TGraph.h"

#include "iostream"
#include "matplot/matplot.h"
#include "chrono"

int main() {
    WavFile wav;
    TonysSPGRAM spectogram;
    TGraph graph;

    using namespace std;
    using namespace matplot;

    string fileName = "Recording-_18_.wav";
    wav.load(fileName);
    vector<int16_t> audioData = wav.getAudioData();

    spectogram.GenerateSpectogramMatrix(audioData, 1024);

    auto MagnitudeMatrix = spectogram.GetMagnitudeSpectogramMatrix();

    //spectogram.ConvdB(MagnitudeMatrix);

    auto normalisedData = graph.normalizeTo255(MagnitudeMatrix);

    auto Frequencies = spectogram.GetFreuqencies();
    


    //// Some random fft from the spectogram
    //vector<int> range = normalisedData[100];

    //// Create a figure
    //matplot::figure();

    //// Plot the data
    //matplot::plot(Frequencies, range);

    //// Set axis labels
    //matplot::xlabel("Domain (Indices)");
    //matplot::ylabel("Range (SpectogramData[1])");

    //// Display the plot
    //matplot::show();

    //// Wait for user to press Enter before proceeding to the next plot
    //cout << "Press Enter to continue to the next plot...";
    //cin.get();  // Waits for the user to press Enter

     //Display spectrogram
    auto h = matplot::imagesc(normalisedData);
    colormap(palette::hot());
    colorbar();
    show();

    return 0;
}