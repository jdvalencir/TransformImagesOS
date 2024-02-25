#ifndef MAPPINGOPENMP_H
#define MAPPINGOPENMP_H

#include <vector>
#include "../../Structs/Pixel.h"
#include "../../Structs/Point.h"

std::vector<std::vector<Pixel>> translationImageOpenMP(const std::vector<std::vector<Pixel>>& matrix, double X, double Y);
std::vector<std::vector<Pixel>> scaleImageOpenMP(const std::vector<std::vector<Pixel>>& image, double W, double H);
std::vector<std::vector<Pixel>> mapMatrixToRotateMatrixOpenMP(const std::vector<std::vector<Pixel>>& matrix, float angle);
std::vector<std::vector<Pixel>> rotateImageOpenMP(const std::vector<std::vector<Pixel>>& matrix, double angle);
std::vector<std::vector<Pixel>> skewImageXOpenMP(const std::vector<std::vector<Pixel>>& matrix, float angle);
std::vector<std::vector<Pixel>> skewImageYOpenMP(const std::vector<std::vector<Pixel>>& matrix, float angle);
std::vector<std::vector<Pixel>> reflectionImageOriginOpenMP(const std::vector<std::vector<Pixel>>& matrix); 
std::vector<std::vector<Pixel>> reflectionImageXOpenMP(const std::vector<std::vector<Pixel>>& matrix);
std::vector<std::vector<Pixel>> reflectionImageYOpenMP(const std::vector<std::vector<Pixel>>& matrix);

#endif