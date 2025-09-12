#include <stdio.h>
#include <stdlib.h>

int main() {
    const int LENGTH = 500;
    const int MAX_COLOR_VALUE;

    char header[54] = { 
        0x42, 0x4D,                         // BM signature (magic number)
        0xE6, 0x71, 0x0B, 0x00,            // File size: 750,566 bytes
        0x00, 0x00,                         // Reserved field 1 (unused)
        0x00, 0x00,                         // Reserved field 2 (unused)
        0x36, 0x00, 0x00, 0x00,            // Pixel data offset: 54 bytes
        0x28, 0x00, 0x00, 0x00,            // DIB header size: 40 bytes (BITMAPINFOHEADER)
        0xF4, 0x01, 0x00, 0x00,            // Image width: 500 pixels
        0xF4, 0x01, 0x00, 0x00,            // Image height: 500 pixels
        0x01, 0x00,                         // Color planes: 1
        0x18, 0x00,                         // Bits per pixel: 24 (RGB)
        0x00, 0x00, 0x00, 0x00,            // Compression method: 0 (none)
        0xB0, 0x71, 0x0B, 0x00,            // Image data size: 750,000 bytes
        0xC4, 0x0E, 0x00, 0x00,            // Horizontal resolution: 3,780 pixels/meter
        0xC4, 0x0E, 0x00, 0x00,            // Vertical resolution: 3,780 pixels/meter
        0x00, 0x00, 0x00, 0x00,            // Colors in palette: 0 (not used for 24-bit)
        0x00, 0x00, 0x00, 0x00             // Important colors: 0 (all colors important)
    };
    FILE *fp;
    fp = fopen("test.bmp", "w+");
    for(int i = 0; i < 54; i++) {
        fputc(header[i], fp);
    }

    const int colors[] = {LENGTH, LENGTH/2, 0};
    const int R = 500, G = 250, B = 0;
    for(int i = 0, pos = 0; i < (LENGTH * LENGTH); i++){

        pos = abs((i % LENGTH) - (i / LENGTH));

        for(int j = 0; j < 3; j++){
            fputc((double)(abs(colors[j] - pos) - LENGTH) / 1.9607843137, fp);
        }
        // fputc(abs(B - pos) - LENGTH, fp);
        // fputc(abs(G - pos) - LENGTH, fp);
        // fputc(abs(R - pos) - LENGTH, fp);
    }
}
