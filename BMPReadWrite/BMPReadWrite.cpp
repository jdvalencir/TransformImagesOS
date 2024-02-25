#include <fstream>
#include <iostream>
#include "BMPReadWrite.h"
#include "../Structs/BMPHeader.h"

using namespace std;

void saveBPMImage(const char* fileName, vector<vector<Pixel>> matrix){
    ofstream file(fileName, ios::binary);
    if(!file){
        cerr << "No se pudo crear el file" << endl;
        exit(1);
    }
    BMPHeader header;
    header.signature[0] = 'B';
    header.signature[1] = 'M';
    header.fileSize = sizeof(BMPHeader) + matrix.size() * ((3 * matrix[0].size()) + (matrix[0].size() % 4)) + 2;
    header.reserved = 0;
    header.dataOffset = sizeof(BMPHeader);
    header.headerSize = 40;
    header.width = matrix[0].size();
    header.height = matrix.size();
    header.planes = 1;
    header.bitsPerPixel = 24;
    header.compression = 0;
    header.dataSize = matrix.size() * ((3 * matrix[0].size()) + (matrix[0].size() % 4)) + 2;
    header.horizontalResolution = 0;
    header.verticalResolution = 0;
    header.colors = 0;
    header.importantColors = 0;

    file.write(reinterpret_cast<char*>(&header), sizeof(BMPHeader));
    for(int i = 0; i < matrix.size(); i++){
        for(int j = 0; j < matrix[0].size(); j++){
            file.write(reinterpret_cast<const char*>(&matrix[i][j]), sizeof(Pixel));
        }   
        for (int k = 0; k < matrix[0].size() % 4; k++) {
            char paddingByte = 0;
            file.write(&paddingByte, 1);
        }
    }
    file.close();
}

#pragma pack(pop)
vector<vector<Pixel>> readBMPFile(const char *fileName){
    ifstream file(fileName, ios::binary);
    if (!file) {
        cerr << "No se pudo abrir el file BMP" << endl;
        exit(1);
    }
    BMPHeader header;
    file.read(reinterpret_cast<char *>(&header), sizeof(BMPHeader));
    std::cout << "Ancho: " << header.width << "  Alto: " << header.height << std::endl;
    if (header.bitsPerPixel != 24){
        cerr << "El file BMP debe tener 24 bits por píxel" << endl;
        exit(1);
    }
    // Mover el puntero al inicio de los datos de píxeles
    file.seekg(header.dataOffset, ios::beg);
    vector<vector<Pixel>> matrix(header.height, vector<Pixel>(header.width));
    for(int i = 0; i < header.height; ++i){
        for(int j = 0; j < header.width; ++j){
            file.read(reinterpret_cast<char *>(&matrix[i][j]), sizeof(Pixel));
        }
        file.seekg(header.width % 4, ios::cur);
    }
    file.close();
    return matrix;
}