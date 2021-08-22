//
//  main.cpp
//  wavFile
//
//  Created by Saleh Ahmad on 22/8/21.
//

#include <iostream>
#include "Wave.hpp"

int main(int argc, const char * argv[]) {
    Wave wv;
    wv.openFile((char*)"/Users/salehahmad/Desktop/SpeechMod/speechCompressor/resource/test1.wav");
    return 0;
}
