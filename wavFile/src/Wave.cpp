//
//  Wave.cpp
//  speechCompressor
//
//  Created by Saleh Ahmad on 10/8/21.
//
#include "Wave.hpp"

using namespace std;

bool Wave::openFile(char* filepath){
    rf.open(filepath, ios::out | ios::binary);
    if (rf.is_open()){
        rf.read((char *) &header, sizeof(header));
        while(header.data_chunk_header[0] != 'd' && header.data_chunk_header[0] != 'a' &&
              header.data_chunk_header[0] != 't' && header.data_chunk_header[0] != 'a'){
            char ignore[header.data_size];
            rf.read(ignore, header.data_size);
            rf.read((char*)&header.data_chunk_header, 4);
            rf.read((char*)&header.data_size, 4);
            if (rf.eof())
                return false;
        }
        return true;
    }
    return false;
}

void Wave::read(char* buf, int len){
    rf.read(buf, len);
}

uint32_t Wave::readSamples(char* buf, uint32_t len){
    long size_of_each_sample = (header.channels * header.bits_per_sample) / 8;
    if (len<size_of_each_sample){
        return 0;
    }
    rf.read(buf, (len/size_of_each_sample)*size_of_each_sample);
    if (rf.eof())
        return 0;
    return len;
}

void Wave::closeFile(){
    rf.close();
}

bool Wave::exportSmallFile(char* filepath, struct HEADER *fileHeader, char* data, uint32_t len){
    ofstream outdata;
    outdata.open(filepath);
    if( !outdata ) { // file couldn't be opened
        return false;
    }
    header.data_size=len;
    header.overall_size=44+len;
    char* head = (char*)fileHeader;
    for (uint32_t i=0; i<sizeof(struct HEADER); ++i){
        outdata<<head[i];
    }
    for (uint32_t i=0; i<len; ++i){
          outdata << data[i];
    }
    outdata.close();
    
    return true;
}

ofstream fileWriter;
uint32_t dataLen;
struct HEADER *wfileHeader;
string wfilepath;
bool Wave::exportBigFileStart(char* filepath, struct HEADER *fileHeader){
    dataLen=0;
    wfileHeader=fileHeader;
    fileWriter.open(filepath);
    wfilepath=filepath;
    if( !fileWriter ) { // file couldn't be opened
        return false;
    }
    char* head = (char*)fileHeader;
    for (uint32_t i=0; i<sizeof(struct HEADER); ++i){
        fileWriter<<head[i];
    }
    return true;
}

bool Wave::exportBigFileChunk(char* data, uint32_t len){
    if( !fileWriter ) {
        return false;
    }
    for (uint32_t i=0; i<len; ++i){
        fileWriter << data[i];
    }
    dataLen+=len;
    return true;
}

bool Wave::exportBigFileFinish(){
    if( !fileWriter ) {
        return false;
    }
    
//    //update data size and overall size
//    fileWriter.seekp(40, ios::beg);//seek to data size
//    fileWriter.write((char*)&dataLen, 4);
//    fileWriter.seekp(4, ios::beg);//seek to overall size
//    dataLen+=44;
//    fileWriter.write((char*)&dataLen, 4);
    fileWriter.close();
    wfileHeader->data_size=dataLen;
    wfileHeader->overall_size=44+dataLen;
    fileWriter.open(wfilepath, std::ios_base::app);
    if( !fileWriter ) { // file couldn't be opened
        return false;
    }
    char* head = (char*)wfileHeader;
    for (uint32_t i=0; i<sizeof(struct HEADER); ++i){
        fileWriter<<head[i];
    }
    fileWriter.close();
    return true;
}
