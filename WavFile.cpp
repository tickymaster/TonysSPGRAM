#include "WavFile.h"
#include <iostream>
#include <fstream>
#include <cstring>

bool WavFile::load(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return false;
    }

    // Read the RIFF header
    file.read(reinterpret_cast<char*>(&wavHeader), sizeof(WavHeader));
    if (std::strncmp(wavHeader.chunkID, "RIFF", 4) != 0 || std::strncmp(wavHeader.format, "WAVE", 4) != 0) {
        std::cerr << "Invalid WAV file: " << filename << std::endl;
        return false;
    }

    // Read chunks until the "fmt " chunk is found
    while (file) {
        file.read(reinterpret_cast<char*>(&fmtSubchunk), sizeof(FmtSubchunk));
        if (std::strncmp(fmtSubchunk.subchunk1ID, "fmt ", 4) == 0) {
            break;
        }
        // Skip the chunk if it's not "fmt "
        file.seekg(fmtSubchunk.subchunk1Size, std::ios::cur);
    }

    if (fmtSubchunk.audioFormat != 1) {
        std::cerr << "Unsupported audio format: " << fmtSubchunk.audioFormat << std::endl;
        return false;
    }

    // Read chunks until the "data" chunk is found
    char dataHeader[4];
    uint32_t dataSize;
    while (file) {
        file.read(dataHeader, 4);
        file.read(reinterpret_cast<char*>(&dataSize), sizeof(uint32_t));
        if (std::strncmp(dataHeader, "data", 4) == 0) {
            break;
        }
        // Skip the chunk if it's not "data"
        file.seekg(dataSize, std::ios::cur);
    }

    // Read the audio data
    audioData.resize(dataSize / sizeof(int16_t));
    file.read(reinterpret_cast<char*>(audioData.data()), dataSize);

    return true;
}

void WavFile::printHeaderInfo() const {
    std::cout << "Audio Format: " << fmtSubchunk.audioFormat << std::endl;
    std::cout << "Number of Channels: " << fmtSubchunk.numChannels << std::endl;
    std::cout << "Sample Rate: " << fmtSubchunk.sampleRate << " Hz" << std::endl;
    std::cout << "Byte Rate: " << fmtSubchunk.byteRate << std::endl;
    std::cout << "Block Align: " << fmtSubchunk.blockAlign << std::endl;
    std::cout << "Bits per Sample: " << fmtSubchunk.bitsPerSample << std::endl;
}

const std::vector<int16_t>& WavFile::getAudioData() const {
    return audioData;
}
