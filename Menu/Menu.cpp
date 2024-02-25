#include <iostream>
#include <chrono>
#include <functional>
#include "../Menu/Menu.h"
#include "../Mapping/Secuencial/Mapping.h"
#include "../Mapping/OpenMp/MappingOpenMP.h"
#include "../BMPReadWrite/BMPReadWrite.h"

using namespace std;
using namespace chrono;

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m" 

template<typename F, typename... Args>
auto timedFunction(F func, Args&&... args) -> decltype(func(args...)) {
    auto start_time = high_resolution_clock::now();
    
    // Call the passed function with its arguments
    auto result = func(forward<Args>(args)...);
    
    auto end_time = high_resolution_clock::now();
    auto elapsed_time = duration_cast<milliseconds>(end_time - start_time);
    
    cout << "Time: " << elapsed_time.count() << " ms\n";
    
    return result;
}

void printMenu(){
    cout << GREEN << "----------- MENU -------------" << endl;
    cout << BLUE << "1- Translate image" << endl;
    cout << BLUE << "2- Scale image" << endl;
    cout << BLUE << "3- Rotate image" << endl;
    cout << BLUE << "4- Skew image X" << endl;
    cout << BLUE << "5- Skew image Y" << endl;
    cout << BLUE << "6- Reflection image Origin" << endl;
    cout << BLUE << "7- Reflection image X" << endl;
    cout << BLUE << "8- Reflection image Y" << endl;
    cout << RED  << "9- Finish program" << endl;
    cout << GREEN << "----------------------------" << endl;
}

int receiveOptionByUser(){
    char option; 
    cout << YELLOW << "Enter your option: " << endl;
    cin >> option;
    if(option >= 49 && option <= 57) return option - 48;
    return 0;
}

string getFileName() {
    string fileName;
    cout << YELLOW << "Enter the name of the file: " << endl;
    cin >> fileName;
    return fileName;
}

string getImageName(){
    string saveFileName;
    cout << YELLOW << "Enter the name of the file to save: " << endl;
    cin >> saveFileName;
    return saveFileName;
}

vector<vector<Pixel>> convertImageToMatrix(const char* fileName){
    vector<vector<Pixel>> readImageMatrix = readBMPFile(fileName);
    return readImageMatrix;
}

void saveImage(const vector<vector<Pixel>>& resultMatrix) {
    string saveFileName = getImageName();
    const char* saveFileNameChar = saveFileName.c_str();
    saveBPMImage(saveFileNameChar, resultMatrix);
}

vector<vector<Pixel>> executeOption(const vector<vector<Pixel>>& matrix, int option){
    vector<vector<Pixel>> resultMatrix; 
    double angle;
    int executionChoice;
    
    cout << "Enter your option: 1-Secuencial 2-Parallel with OpenMP" << endl; 
    cin >> executionChoice;

    switch (option) {
    case 1: {
        double X, Y;
        cout << YELLOW << "Enter X: " << endl;
        cin >> X;
        cout << YELLOW << "Enter Y: " << endl;
        cin >> Y;
        if(executionChoice == 1) resultMatrix = timedFunction(translationImage, matrix, X, Y);
        else resultMatrix = timedFunction(translationImageOpenMP, matrix, X, Y);
        break;
    }
    case 2: {
        double W, H;
        cout << YELLOW << "Enter W: " << endl;
        cin >> W;
        cout << YELLOW << "Enter H: " << endl;
        cin >> H;
        if(executionChoice == 1) resultMatrix = resultMatrix = timedFunction(scaleImage, matrix, W, H);
        else resultMatrix = resultMatrix = timedFunction(scaleImageOpenMP, matrix, W, H);
        break;
    }
    case 3: {
        cout << YELLOW << "Enter the angle: " << endl;
        cin >> angle;
        if(executionChoice == 1) resultMatrix = timedFunction(rotateImage, matrix, angle);
        else resultMatrix = timedFunction(rotateImageOpenMP, matrix, angle);
        break;
    }
    case 4: {
        cout << YELLOW << "Enter the angle: " << endl;
        cin >> angle;
        if(executionChoice == 1) resultMatrix = timedFunction(skewImageX, matrix, angle);
        else resultMatrix = timedFunction(skewImageXOpenMP, matrix, angle);
        break;
    }
    case 5: { 
        cout << YELLOW << "Enter the angle: " << endl;
        cin >> angle;
        if(executionChoice == 1) resultMatrix = timedFunction(skewImageY, matrix, angle);
        else resultMatrix = timedFunction(skewImageYOpenMP, matrix, angle);
        break;
    }
    case 6: {
        if(executionChoice == 1) resultMatrix = timedFunction(reflectionImageOrigin, matrix);
        else resultMatrix = timedFunction(reflectionImageOriginOpenMP, matrix);
        break;
    }
    case 7: {
        if(executionChoice == 1) resultMatrix = timedFunction(reflectionImageX, matrix);
        else resultMatrix = timedFunction(reflectionImageXOpenMP, matrix);
        break;
    }
    case 8: {
        if(executionChoice == 1) resultMatrix = timedFunction(reflectionImageY, matrix);
        else resultMatrix = timedFunction(reflectionImageYOpenMP, matrix);
        break;
    }
    default:
        cout << RED << "We do not have this option, sorry!" << endl;
        break;
    }
    return resultMatrix;
}