#include <iostream>
#include "../Menu/Menu.h"
#include "../Mapping/Secuencial/Mapping.h"
#include "../BMPReadWrite/BMPReadWrite.h"

using namespace std;

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m" 

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
    switch (option) {
    case 1:
        double X, Y;
        cout << YELLOW << "Enter X: " << endl;
        cin >> X;
        cout << YELLOW << "Enter Y: " << endl;
        cin >> Y;
        resultMatrix = translationImage(matrix, X, Y);
        break;
    case 2:
        double W, H;
        cout << YELLOW << "Enter W: " << endl;
        cin >> W;
        cout << YELLOW << "Enter H: " << endl;
        cin >> H;
        resultMatrix = scaleImage(matrix, W, H);
        break;
    case 3: 
        cout << YELLOW << "Enter the angle: " << endl;
        cin >> angle;
        resultMatrix = rotateImage(matrix, angle);
        break;
    case 4: 
        cout << YELLOW << "Enter the angle: " << endl;
        cin >> angle;
        resultMatrix = skewImageX(matrix, angle);
        break;
    case 5: 
        cout << YELLOW << "Enter the angle: " << endl;
        cin >> angle;
        resultMatrix = skewImageY(matrix, angle);
        break;
    case 6: 
        resultMatrix = reflectionImageOrigin(matrix);
        break;
    case 7: 
        resultMatrix = reflectionImageX(matrix);
        break;
    case 8: 
        resultMatrix = reflectionImageY(matrix);
        break;
    default:
        cout << RED << "We do not have this option, sorry!" << endl;
        break;
    }
    return resultMatrix;
}