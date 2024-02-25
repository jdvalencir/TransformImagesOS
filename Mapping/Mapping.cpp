#include <cmath>
#include "../Mapping/Mapping.h"
#include "../Transformations/Transformations.h"

vector<vector<Pixel>> translationImage(const vector<vector<Pixel>>& matrix, double X, double Y){
    int rows = matrix.size();
    int cols = matrix[0].size();
    int newWidth = static_cast<int>(cols + X);
    int newHeight = static_cast<int>(rows + Y); 

    vector<vector<Pixel>> translatedMatrix(newHeight, vector<Pixel>(newWidth));

    for(int y = 0; y < newHeight; y++){
        for(int x = 0; x < newWidth; x++){
            Point translatedPoint;
            translatedPoint.y = y;
            translatedPoint.x = x;
            translatedPoint = translatePoint(translatedPoint, X, Y); 
            if(translatedPoint.y < newHeight && translatedPoint.x < newWidth){
                translatedMatrix[translatedPoint.y][translatedPoint.x] = matrix[y][x];
            }
        }
    }
    return translatedMatrix;    
}

vector<vector<Pixel>> scaleImage(const vector<vector<Pixel>>& image, double W, double H) {
    int cols = image[0].size();
    int rows = image.size();
    int newWidth = static_cast<int>(cols * W);
    int newHeight = static_cast<int>(rows * H);
    
    vector<vector<Pixel>> scaledMatrix(newHeight, vector<Pixel>(newWidth));

    for (int y = 0; y < rows; y++) {
        for (int x = 0; x < cols; x++) {
            Point scaledPoint;
            scaledPoint.y = y;
            scaledPoint.x = x;
            scaledPoint = scalePoint(scaledPoint, W, H);
            if (scaledPoint.x < newWidth && scaledPoint.y < newHeight) {
                scaledMatrix[scaledPoint.y][scaledPoint.x] = image[y][x];
            }
        }
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

    for(int y = 0; y < rows; y++){
        for(int x = 0; x < cols; x++){
            mapImgMatrix[y + (rotateImageWidth / 2) - (rows / 2)][x + (rotateImageHeight / 2) - (cols / 2)] = matrix[y][x];
        }
    }
    return  mapImgMatrix;
}

vector<vector<Pixel>> rotateImage(const vector<vector<Pixel>>& matrix, double angle){
    int rowsHeight = matrix.size();
    int colsWidth = matrix[0].size();
    float angleRad = angle * M_PI / 180;

    vector<vector<Pixel>> mapImage = mapMatrixToRotateMatrix(matrix, angleRad);
    
    double centerX = mapImage.size() / 2.0;
    double centerY = mapImage[0].size() / 2.0;
    
    vector<vector<Pixel>> rotateImage(mapImage.size(), vector<Pixel>(mapImage[0].size()));
    
    int rotateHeight = rotateImage.size();
    int rotateWidth = rotateImage[0].size();
    
    for(int y = 0; y < rotateHeight; y++){ 
        for(int x = 0; x < rotateWidth; x++){
            Point rotatedPoint;
            rotatedPoint.x = x - centerX; 
            rotatedPoint.y = y - centerY;
            rotatedPoint = rotatePoint(rotatedPoint, angleRad);
            int rorig = rotatedPoint.y + centerY;
            int corig = rotatedPoint.x + centerX;

            if((rorig >= 0 && rorig < rotateHeight) && (corig >= 0 && corig < rotateWidth)){
                rotateImage[y][x] = mapImage[rorig][corig];
            }
        }
    }
    return rotateImage;
}

vector<vector<Pixel>> skewImageX(const vector<vector<Pixel>>& matrix, float angle) {   
    int rows = matrix.size();
    int cols = matrix[0].size();
    
    float angleRad = angle * M_PI / 180;
    float oppositiveLeg = tan(angleRad) * rows;

    float skewImageHeight = rows; 
    float skewImageWidth = cols + oppositiveLeg;

    vector<vector<Pixel>> skewedMatrix(skewImageHeight, vector<Pixel>(skewImageWidth));

    int skewMatrixHeight = skewedMatrix.size();
    int skewMatrixWidth = skewedMatrix[0].size();
    
    for(int y = 0; y < rows; y++){
        for(int x = 0; x < cols; x++){
            Point skewedPoint;
            skewedPoint.x = x; 
            skewedPoint.y = y;
            skewedPoint = skewPointX(skewedPoint, angleRad);
            
            if((skewedPoint.y >= 0 && skewedPoint.y < skewMatrixHeight) && (skewedPoint.x >= 0 && skewedPoint.x < skewMatrixWidth)){
                skewedMatrix[skewedPoint.y][skewedPoint.x] = matrix[y][x];
            }          
        }
    }
    return skewedMatrix;
}

vector<vector<Pixel>> skewImageY(const vector<vector<Pixel>>& matrix, float angle){
    int rows = matrix.size();
    int cols = matrix[0].size();
    
    float angleRad = angle * M_PI / 180;
    float catetoOpuesto = tan(angleRad) * cols;

    float skewImageHeight = rows + catetoOpuesto; 
    float skewImageWidth = cols;

    vector<vector<Pixel>> skewedMatrix(skewImageHeight, vector<Pixel>(skewImageWidth));

    int skewMatrixHeight = skewedMatrix.size();
    int skewMatrixWidth = skewedMatrix[0].size();
    
    for(int y = 0; y < rows; y++){
        for(int x = 0; x < cols; x++){
            Point skewedPoint;
            skewedPoint.y = y;
            skewedPoint.x = x; 
            skewedPoint = skewPointY(skewedPoint, angleRad);
            
            if((skewedPoint.y >= 0 && skewedPoint.y < skewMatrixHeight) && (skewedPoint.x >= 0 && skewedPoint.x < skewMatrixWidth)){
                skewedMatrix[skewedPoint.y][skewedPoint.x] = matrix[y][x];
            }          
        }
    }
    return skewedMatrix;
}

vector<vector<Pixel>> reflectionImageOrigin(const vector<vector<Pixel>>& matrix){
    int rows = matrix.size();
    int cols = matrix[0].size();
    
    vector<vector<Pixel>> reflectedOriginMatrix(rows * 2, vector<Pixel>(cols * 2)); 
    int centerX = reflectedOriginMatrix[0].size() / 2;
    int centerY = reflectedOriginMatrix.size() / 2;


    for(int y = 0; y < rows; y++){
        for(int x = 0; x < cols; x++){
            Point reflectedOriginPoint;
            reflectedOriginPoint.y = y;
            reflectedOriginPoint.x = x;
            reflectedOriginPoint = reflectPointOrigin(reflectedOriginPoint);
            if(reflectedOriginPoint.y < rows && reflectedOriginPoint.x < cols){
                reflectedOriginMatrix[abs(reflectedOriginPoint.y + centerY)][abs(reflectedOriginPoint.x + centerX)] = matrix[y][x];
            }
        }
    }
    return reflectedOriginMatrix;
}


vector<vector<Pixel>> reflectionImageX(const vector<vector<Pixel>>& matrix){
    int rows = matrix.size();
    int cols = matrix[0].size();

    vector<vector<Pixel>> reflectedXMatrix(rows * 2, vector<Pixel>(cols)); 
    int centerX = reflectedXMatrix[0].size() / 2;
    int centerY = reflectedXMatrix.size() / 2;

    for(int y = 0; y < rows; y++){
        for(int x = 0; x < cols; x++){
            Point reflectedXPoint;
            reflectedXPoint.y = y;
            reflectedXPoint.x = x;
            reflectedXPoint = reflectPointX(reflectedXPoint);
            if(reflectedXPoint.y < rows && reflectedXPoint.x < cols){
                reflectedXMatrix[abs(reflectedXPoint.y + centerY)][abs(reflectedXPoint.x) ] = matrix[y][x];
            }
        }
    }
    return reflectedXMatrix;
}

vector<vector<Pixel>> reflectionImageY(const vector<vector<Pixel>>& matrix){
    int rows = matrix.size();
    int cols = matrix[0].size();

    vector<vector<Pixel>> reflectedYMatrix(rows , vector<Pixel>(cols * 2 )); 
    int centerX = reflectedYMatrix[0].size() / 2;
    int centerY = reflectedYMatrix.size() / 2;

    for(int y = 0; y < rows; y++){
        for(int x = 0; x < cols; x++){
            Point reflectedYPoint; 
            reflectedYPoint.y = y;
            reflectedYPoint.x = x; 
            reflectedYPoint = reflectPointY(reflectedYPoint);
            if(reflectedYPoint.y < rows && reflectedYPoint.x < cols){
                reflectedYMatrix[abs(reflectedYPoint.y )][abs(reflectedYPoint.x + centerX)] = matrix[y][x];
            }
        }
    }
    return reflectedYMatrix;
}