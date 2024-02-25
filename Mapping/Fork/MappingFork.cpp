#include <unistd.h>
#include <sys/wait.h>
#include <cmath>
#include <iostream>
#include "MappingFork.h"
#include "../Transformations/Transformations.h"

using namespace std;

vector<vector<Pixel>> translationImage(const vector<vector<Pixel>>& matrix, double X, double Y){
    int rows = matrix.size();
    int cols = matrix[0].size();
    int newWidth = static_cast<int>(cols + X);
    int newHeight = static_cast<int>(rows + Y); 

    vector<vector<Pixel>> translatedMatrix(newHeight, vector<Pixel>(newWidth));
    
    pid_t pids[newHeight];
    int processCount = 0;

    for(int y = 0; y < newHeight; y++){
        pids[y] = fork();
        if(pids[y] == 0) { // Child process
            for(int x = 0; x < newWidth; x++){
                Point translatedPoint;
                translatedPoint.y = y;
                translatedPoint.x = x;
                translatedPoint = translatePoint(translatedPoint, X, Y); 
                if(translatedPoint.y < newHeight && translatedPoint.x < newWidth){
                    translatedMatrix[translatedPoint.y][translatedPoint.x] = matrix[y][x];
                }
            }
            exit(0); // Terminate the child process
        } else if (pids[y] > 0) { // Parent process
            processCount++;
        } else {
            cerr << "Fork failed" << endl;
            exit(1); // Fork failed
        }
    }

    // Wait for all child processes to complete
    while (processCount > 0) {
        wait(NULL);
        processCount--;
    }

    return translatedMatrix;    
}

vector<vector<Pixel>> scaleImage(const vector<vector<Pixel>>& image, double W, double H) {
    int cols = image[0].size();
    int rows = image.size();
    int newWidth = static_cast<int>(cols * W);
    int newHeight = static_cast<int>(rows * H);
    
    vector<vector<Pixel>> scaledMatrix(newHeight, vector<Pixel>(newWidth));

    pid_t pids[newHeight];
    int processCount = 0;

    for (int y = 0; y < newHeight; y++) {
        pids[y] = fork();
        if(pids[y] == 0) { // Child process
            for (int x = 0; x < newWidth; x++) {
                    Point scaledPoint;
                    scaledPoint.y = y;
                    scaledPoint.x = x;
                    scaledPoint = scalePoint(scaledPoint, 1.0 / W, 1.0 / H);
                                            
                    int nearestX = static_cast<int>(round(scaledPoint.x));
                    int nearestY = static_cast<int>(round(scaledPoint.y));
                    
                    // Make sure the nearest point is within the original image bounds
                    nearestX = max(0, min(cols - 1, nearestX));
                    nearestY = max(0, min(rows - 1, nearestY));
                    
                    scaledMatrix[y][x] = image[nearestY][nearestX];
            }
            exit(0); // Terminate the child process
        } else if(pids[y] > 0){
            processCount++;
        } else {
            cerr << "Fork failed" << endl;
            exit(1); // Fork failed
        }
    }

     // Wait for all child processes to complete
    while (processCount > 0) {
        wait(NULL);
        processCount--;
    }

    return scaledMatrix;
}

vector<vector<Pixel>> mapMatrixToRotateMatrix(const vector<vector<Pixel>>& matrix, float angle) {   
    int rows = matrix.size();
    int cols = matrix[0].size();

    float rotateImageHeight = 0; 
    float rotateImageWidth = 0;

    if(rows != cols){ 
        float sizeOfImg = sqrt((pow(rows, 2) + pow(cols, 2)));
        rotateImageHeight = sizeOfImg;
        rotateImageWidth = sizeOfImg;
    } else {
        rotateImageHeight = (abs(cols * sin(angle)) + abs(rows * cos(angle)));
        rotateImageWidth = (abs(cols * cos(angle)) + abs(rows * sin(angle)));
    }
 
    vector<vector<Pixel>> mapImgMatrix(rotateImageHeight, vector<Pixel>(rotateImageWidth));

    pid_t pids[static_cast<int>(rotateImageHeight)];
    int processCount = 0;

    for(int y = 0; y < rows; y++){
        pids[y] = fork();
        if (pids[y] == 0) { // Child process
            for(int x = 0; x < cols; x++){
                mapImgMatrix[y + (rotateImageWidth / 2) - (rows / 2)][x + (rotateImageHeight / 2) - (cols / 2)] = matrix[y][x];
            }
            exit(0); // Terminate the child process
        } else if (pids[y] > 0) { // Parent process
            processCount++;
        } else {
            cerr << "Fork failed" << endl;
            exit(1); // Fork failed
        }
    }

     // Wait for all child processes to complete
    while (processCount > 0) {
        wait(NULL);
        processCount--;
    }
    return  mapImgMatrix;
}