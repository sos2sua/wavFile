//
//  Wave.hpp
//  speechCompressor
//
//  Created by Saleh Ahmad on 10/8/21.
//

#ifndef Wave_hpp
#define Wave_hpp

#include <iostream>
#include <fstream>

using namespace std;

struct HEADER {
    unsigned char riff[4];                        // RIFF string
    uint32_t overall_size;                // overall size of file in bytes
    unsigned char wave[4];                        // WAVE string
    unsigned char fmt_chunk_marker[4];            // fmt string with trailing null char
    uint32_t length_of_fmt;                    // length of the format data
    uint16_t format_type;                    // format type. 1-PCM, 3- IEEE float, 6 - 8bit A law, 7 - 8bit mu law
    uint16_t channels;                        // no.of channels
    uint32_t sample_rate;                    // sampling rate (blocks per second)
    uint32_t byterate;                        // SampleRate * NumChannels * BitsPerSample/8
    uint16_t block_align;                    // NumChannels * BitsPerSample/8
    uint16_t bits_per_sample;                // bits per sample, 8- 8bits, 16- 16 bits etc
    unsigned char data_chunk_header [4];        // DATA string or FLLR string
    uint32_t data_size;                        // NumSamples * NumChannels * BitsPerSample/8 - size of the next chunk that will be read
};
class Wave{
private:
    ifstream rf;
    
public:
    struct HEADER header;
    bool openFile(char* filepath);
    void read(char* buf, int len);
    uint32_t readSamples(char* buf, uint32_t len);
    void closeFile();
    bool exportSmallFile(char* filepath, struct HEADER *fileHeader,char* data, uint32_t len);
    bool exportBigFileStart(char* filepath, struct HEADER *fileHeader);
    bool exportBigFileChunk(char* data, uint32_t len);
    bool exportBigFileFinish();
};

#endif /* Wave_hpp */
