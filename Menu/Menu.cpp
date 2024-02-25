#include <Menu/Menu.h>
#include <iostream>
#include <Mapping/Mapping.h>

using namespace std;

#define BLUE 0x001F      
#define GREEN 0x07E0     
#define RED 0xF800      
#define ORANGE 0xFD20 

void printMenu(){
    cout << GREEN <<"----------- MENU -------------" << endl;
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
    cout << ORANGE << "Enter your option: " << endl;
    cin >> option;
    if(option >= 49 && opcion <= 57) return opcion - 48;
    return 0;
}

vector<vector<Pixel>> executeOption(vector<vector<Pixel>> matrix, char option){
    vector<vector<Pixel>> resultMatrix; 
    switch (opcion) {
    case 1:
        double X, Y;
        cout << ORANGE << "Enter X: " << endl;
        cin >> X;
        cout << ORANGE << "Enter Y: " << endl;
        cint >> Y;
        resultMatrix = translationImage(matrix, x, y);
        break;
    case 2:
        double W, H;
        cout << ORANGE << "Enter W: " << endl;
        cin >> W;
        cout << ORANGE << "Enter H: " << endl;
        cin >> H;
        resultMatrix = scaleImage(matrix, W, H);
        break;
    case 3: 
        float angle;
        cout << ORANGE << "Enter the angle: " << endl;
        cin >> angle;
        resultMatrix = rotateImage(matrix, angle);
        break;
    case 4: 
        float angle; 
        cout << ORANGE << "Enter the angle: " << endl;
        cin >> angle;
        resultMatrix = skewImageX(matrix, angle);
        break;
    case 5: 
        float angle; 
        cout << ORANGE << "Enter the angle: " << endl;
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
        resultMatrix = reflectionImagey(matrix);
        break;
    default:
        cout << RED << "We do not have this option, sorry!" << endl;
        break;
    }
    return resultMatrix;
}