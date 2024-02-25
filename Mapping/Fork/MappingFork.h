#ifndef MAPPINGFORK_H
#define MAPPINGFORK_H

#include <vector>
#include "../../Structs/Pixel.h"
#include "../../Structs/Point.h"

std::vector<std::vector<Pixel>> translationImage(const std::vector<std::vector<Pixel>>& matrix, double X, double Y);
std::vector<std::vector<Pixel>> scaleImage(const std::vector<std::vector<Pixel>>& image, double W, double H);
std::vector<std::vector<Pixel>> mapMatrixToRotateMatrix(const std::vector<std::vector<Pixel>>& matrix, float angle);
std::vector<std::vector<Pixel>> rotateImage(const std::vector<std::vector<Pixel>>& matrix, double angle);
std::vector<std::vector<Pixel>> skewImageX(const std::vector<std::vector<Pixel>>& matrix, float angle);
std::vector<std::vector<Pixel>> skewImageY(const std::vector<std::vector<Pixel>>& matrix, float angle);
std::vector<std::vector<Pixel>> reflectionImageOrigin(const std::vector<std::vector<Pixel>>& matrix);
std::vector<std::vector<Pixel>> reflectionImageX(const std::vector<std::vector<Pixel>>& matrix);
std::vector<std::vector<Pixel>> reflectionImageY(const std::vector<std::vector<Pixel>>& matrix);

#endif