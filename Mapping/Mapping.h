#ifndef MAPPING_H
#define MAPPING_H

#include <vector>
#include "../Structs/Pixel.h"
#include "../Structs/Point.h"

using namespace std;

vector<vector<Pixel>> translationImage(const vector<vector<Pixel>>& matrix, double X, double Y);
vector<vector<Pixel>> scaleImage(const vector<vector<Pixel>>& image, double W, double H);
vector<vector<Pixel>> mapMatrixToRotateMatrix(const vector<vector<Pixel>>& matrix, float angle);
vector<vector<Pixel>> rotateImage(const vector<vector<Pixel>>& matrix, double angle);
vector<vector<Pixel>> skewImageX(const vector<vector<Pixel>>& matrix, float angle);
vector<vector<Pixel>> skewImageY(const vector<vector<Pixel>>& matrix, float angle);
vector<vector<Pixel>> reflectionImageOrigin(const vector<vector<Pixel>>& matrix); 
vector<vector<Pixel>> reflectionImageX(const vector<vector<Pixel>>& matrix);
vector<vector<Pixel>> reflectionImageY(const vector<vector<Pixel>>& matrix);

#endif