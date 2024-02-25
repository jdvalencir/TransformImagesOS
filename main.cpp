#include <iostream>
#include <vector>
#include "./Menu/Menu.h"

using namespace std;

int main(int argc, char *argv[]) {
    string readFileName;
    vector<vector<Pixel>> resultMatrix;
    
    while(true){
        printMenu();
        readFileName = getFileName();
        
        int option = receiveOptionByUser();    
        if(option == 9) break; 
        
        vector<vector<Pixel>> ReadMatrix = convertImageToMatrix(readFileName.c_str());

        
        resultMatrix = executeOption(ReadMatrix, option);
        
        saveImage(resultMatrix);
    }
    return 0;
}