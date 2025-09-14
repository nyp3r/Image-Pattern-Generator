#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void fillHeaderVal( int val,int placeHigh, unsigned char* header);

int Rainbow_Cornered(int length, int pixel, int color);
int Rainbow_Circle(int length, int pixel, int color);
int Reverse_Rainbow_Circle(int length, int pixel, int color);

int main() {
    const int LENGTH = 500;
    const int MAX_COLOR_VALUE;

    unsigned char header[54] = { 
        0x42, 0x4D, // "BM"
        0, 0, 0, 0, // image size with header
        0x00, 0x00,
        0x00, 0x00,
        0x36, 0x00, 0x00, 0x00,
        0x28, 0x00, 0x00, 0x00,
        0, 0, 0, 0, // width
        0, 0, 0, 0, // height
        0x01, 0x00,
        0x18, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0, 0, 0, 0, // image size excluding header

        0xC4, 0x0E, 0x00, 0x00,
        0xC4, 0x0E, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00
    };
    int bitmapSize = 3 * LENGTH * LENGTH;
    int fileSize = bitmapSize + 54;
    fillHeaderVal(fileSize, 5, header);
    fillHeaderVal(LENGTH, 21, header);      //width
    fillHeaderVal(LENGTH, 25, header);      //height
    fillHeaderVal(bitmapSize, 37, header);

    int padding = (4 -  ((3 * LENGTH)  % 4)); 
    if(padding == 4) {
        padding = 0;
    }

    FILE *fp;
    fp = fopen("pattern.bmp", "w+");
    for(int i = 0; i < 54; i++) {
        fputc(header[i], fp);
    }

    const int COLOR_COUNT = 3;
    const int COLORS[] = {LENGTH, LENGTH/2, 0};
    for(int i = 0, pos = 0; i < (LENGTH * LENGTH); i++){
        for(int j = 0; j < 3; j++){
            int color = Reverse_Rainbow_Circle(LENGTH, i, COLORS[j]);
            fputc(color, fp);
        }
        if(((i +1) % LENGTH == 0)   ) { // add padding when width is reached
            for( int j = 0; j < padding; j++) {
                    fputc(0, fp);
            }
        }
    }
}


int Rainbow_Cornered(int length, int pixel, int color){

    int pos = abs((pixel % length) + (pixel / length))/2;
    return (double)(length - abs(color - pos)) / 1.9607843137;
}

int Reverse_Rainbow_Circle(int length, int pixel, int color){

    const int WHITE = 255;
    const int X = (pixel % length) - length/2; // get x position but from center
    const int Y = (pixel / length) - length/2; // get y position but from center

    const int POS = (atan2(X, Y) + M_PI) * length / (2 * M_PI);

    const int CALCULATED_COLOR = (double)(length - abs(color - POS)) / 1.9607843137;

    if(POS > length) return WHITE; //make out of circle pixels white
    return CALCULATED_COLOR;
}


int Rainbow_Circle(int length, int pixel, int color){

    const int WHITE = 255;
    const int X = (pixel % length) - length/2; // get x position but from center
    const int Y = (pixel / length) - length/2; // get y position but from center

    const int POS = sqrt(pow(X, 2) + pow(Y, 2))*2; //euclidean distance zoomed out by 2

    const int CALCULATED_COLOR = (double)(length - abs(color - POS)) / 1.9607843137;

    if(POS > length) return WHITE; //make out of circle pixels white
    return CALCULATED_COLOR;
}


void fillHeaderVal( int val,int placeHigh, unsigned char* header) {
    // shift by hex bit count(2^4 = 16 = hex)
    // multiply by distance to least significant digit
    // since x86 is little endian we do
    header[placeHigh] = ((val & 0xFF000000) >> (6*4));
    header[placeHigh - 1] = ((val & 0x00FF0000) >> (4*4));
    header[placeHigh - 2] = ((val & 0x0000FF00) >> (2*4));
    header[placeHigh - 3] = (val & 0x000000FF);
}
