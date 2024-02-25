#include <fstream>
#include <vector>
#include <cmath>
#include <Structs/BMPHeader.h>
#include <Structs/Pixel.h>
#include <Structs/Point.h>
#include <BmpReadWrite/BmpReadWrite.h>
#include <Menu/Menu.h>

using namespace std;

int main(int argc, char *argv[]) {
    const char* readFileName;
    const char* saveFileName;
    vector<vector<Pixel>> resultMatrix;
    
    while(true){
        cout << ORANGE << "Enter the name of the file: " << endl;
        cin >> readFileName;
        vector<vector<Pixel>> ReadMatrix = readBMPFile(readFileName);
        
        printMenu();
        
        int option = receiveOptionByUser();    
        if(option == 9) break; 
        resultMatrix = executeOption(ReadMatrix, option);

        cout << ORANGE << "Enter the name of the file to save: " << endl;
        cin >> saveFileName;
        saveBPMImage(saveFileName, resultMatrix);
    }
    return 0;
}