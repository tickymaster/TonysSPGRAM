#ifndef WAVFILE_H
#define WAVFILE_H

#include <string>
#include <vector>
#include <cstdint>

#pragma pack(push, 1)
struct WavHeader {
    char chunkID[4];       // "RIFF"
    uint32_t chunkSize;    // File size - 8
    char format[4];        // "WAVE"
};
#pragma pack(pop)

#pragma pack(push, 1)
struct FmtSubchunk {
    char subchunk1ID[4];   // "fmt "
    uint32_t subchunk1Size;// 16 for PCM
    uint16_t audioFormat;  // PCM = 1
    uint16_t numChannels;  // Mono = 1, Stereo = 2
    uint32_t sampleRate;   // 44100, 48000, etc.
    uint32_t byteRate;     // SampleRate * NumChannels * BitsPerSample/8
    uint16_t blockAlign;   // NumChannels * BitsPerSample/8
    uint16_t bitsPerSample;// 8, 16, 24, 32
};
#pragma pack(pop)

class WavFile {
public:
    // Loads a WAV file and parses its header and audio data
    bool load(const std::string& filename);

    // Prints the header information of the WAV file
    void printHeaderInfo() const;

    // Returns the raw audio data
    const std::vector<int16_t>& getAudioData() const;

private:
    WavHeader wavHeader;          // WAV file header
    FmtSubchunk fmtSubchunk;      // Format subchunk
    std::vector<int16_t> audioData; // Audio data
};

#endif // WAVFILE_H
