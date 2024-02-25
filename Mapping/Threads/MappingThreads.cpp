#include <thread>
#include "./MappingThreads.h"
#include "../Structs/Point.h"
#include "../Transformations/Transformations.h"
#include <cmath>

using namespace std;

void translatePart(const vector<vector<Pixel>>& matrix, vector<vector<Pixel>>& translatedMatrix, double X, double Y,
                   int startY, int endY, int newWidth, int newHeight) {
    for (int y = startY; y < endY; ++y) {
        for (int x = 0; x < newWidth; ++x) {
            Point translatedPoint;
            translatedPoint.y = y;
            translatedPoint.x = x;
            translatedPoint = translatePoint(translatedPoint, X, Y); 
            if (translatedPoint.y < newHeight && translatedPoint.x < newWidth) {
                translatedMatrix[translatedPoint.y][translatedPoint.x] = matrix[y][x];
            }
        }
    }
}

vector<vector<Pixel>> translationImageThreads(const vector<vector<Pixel>>& matrix, double X, double Y) {
    int rows = matrix.size();
    int cols = matrix[0].size();
    int newWidth = static_cast<int>(cols + X);
    int newHeight = static_cast<int>(rows + Y); 

    vector<vector<Pixel>> translatedMatrix(newHeight, vector<Pixel>(newWidth));

    const int numThreads = thread::hardware_concurrency();
    vector<thread> threads(numThreads);

    int rowsPerThread = newHeight / numThreads;
    int startY = 0;
    int endY = 0;

    for (int i = 0; i < numThreads; ++i) {
        endY = startY + rowsPerThread;
        if (i == numThreads - 1) endY = newHeight; 
        threads[i] = std::thread(translatePart, cref(matrix), ref(translatedMatrix), X, Y, startY, endY, newWidth, newHeight);
        startY = endY;
    }

    // Esperar a que todos los hilos terminen
    for (auto& thread : threads) {
        thread.join();
    }

    return translatedMatrix;
}

void scalePart(const std::vector<std::vector<Pixel>>& image, std::vector<std::vector<Pixel>>& scaledMatrix, double scaleX, double scaleY,
               int startY, int endY, int newWidth, int newHeight, int cols, int rows) {
    for (int y = startY; y < endY; ++y) {
        for (int x = 0; x < newWidth; ++x) {
            Point scaledPoint;
            scaledPoint.y = y * scaleY;
            scaledPoint.x = x * scaleX;
            
            int nearestX = static_cast<int>(round(scaledPoint.x));
            int nearestY = static_cast<int>(round(scaledPoint.y));
            
            // Make sure the nearest point is within the original image bounds
            nearestX = std::max(0, std::min(cols - 1, nearestX));
            nearestY = std::max(0, std::min(rows - 1, nearestY));
            
            scaledMatrix[y][x] = image[nearestY][nearestX];
        }
    }
}

std::vector<std::vector<Pixel>> scaleImageThreads(const std::vector<std::vector<Pixel>>& image, double W, double H) {
    int cols = image[0].size();
    int rows = image.size();
    int newWidth = static_cast<int>(cols * W);
    int newHeight = static_cast<int>(rows * H);
    
    std::vector<std::vector<Pixel>> scaledMatrix(newHeight, std::vector<Pixel>(newWidth));

    const int numThreads = std::thread::hardware_concurrency(); // Obtener el número de hilos soportados
    std::vector<std::thread> threads(numThreads);

    int rowsPerThread = newHeight / numThreads;
    int startY = 0;
    int endY = 0;

    for (int i = 0; i < numThreads; ++i) {
        endY = startY + rowsPerThread;
        if (i == numThreads - 1) {
            endY = newHeight; // Asegurar que el último hilo maneje cualquier fila restante
        }
        threads[i] = std::thread(scalePart, std::cref(image), std::ref(scaledMatrix),
                                 1.0 / W, 1.0 / H, startY, endY, newWidth, newHeight, cols, rows);
        startY = endY;
    }

    // Esperar a que todos los hilos terminen
    for (auto& thread : threads) {
        thread.join();
    }

    return scaledMatrix;
}