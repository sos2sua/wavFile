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
    if (wv.openFile((char*)"[your path to file].wav")){
        cout<<"format type: "<<wv.header.format_type<<endl;
        cout<<"channels: "<<wv.header.channels<<endl;
        cout<<"sample_rate: "<<wv.header.sample_rate<<endl;
        cout<<"byterate: "<<wv.header.byterate<<endl;
        cout<<"bits_per_sample: "<<wv.header.bits_per_sample<<endl;
        wv.closeFile();
    }else{
        cout<<"Failed to open File"<<endl;
    }
    return 0;
}
