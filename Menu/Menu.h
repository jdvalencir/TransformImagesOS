#ifndef MENU_H
#define MENU_H

#include <vector>
#include <Structs/Pixel.h>

using namespace std;

void printMenu();
int receiveOptionByUser();
vector<vector<Pixel>> executeOption(char option);

#endif