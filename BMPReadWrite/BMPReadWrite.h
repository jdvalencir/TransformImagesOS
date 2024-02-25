#ifndef  BMPREADWRITE_H
#define BMPREADWRITE_H

#include <vector>
#include "../Structs/Pixel.h"
using namespace std;

vector<vector<Pixel>> readBMPFile(const char* fileName);
void saveBPMImage(const char* FileName, vector<vector<Pixel>>);

#endif
