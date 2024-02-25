#ifndef MAPPINGTHREADS_H
#define MAPPINGTHREADS_H

#include <vector>
#include "../Structs/Pixel.h"

void translatePart(const std::vector<std::vector<Pixel>>& matrix, std::vector<std::vector<Pixel>>& translatedMatrix, double X, double Y,
                   int startY, int endY, int newWidth, int newHeight);
std::vector<std::vector<Pixel>> translationImageThreads(const std::vector<std::vector<Pixel>>& matrix, double X, double Y); 

void scalePart(const std::vector<std::vector<Pixel>>& image, std::vector<std::vector<Pixel>>& scaledMatrix, double scaleX, double scaleY,
               int startY, int endY, int newWidth, int newHeight, int cols, int rows);

std::vector<std::vector<Pixel>> scaleImageThreads(const std::vector<std::vector<Pixel>>& image, double W, double H);



#endif