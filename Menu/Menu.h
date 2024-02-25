#ifndef MENU_H
#define MENU_H

#include <vector>
#include "../Structs/Pixel.h"
using namespace std;

void printMenu();
int receiveOptionByUser();
string getFileName(); 
string getImageName();
vector<vector<Pixel>> convertImageToMatrix(const char* fileName);
vector<vector<Pixel>> executeOption(const vector<vector<Pixel>>& matrix, int option);
void saveImage(const vector<vector<Pixel>>& resultMatrix);

#endif