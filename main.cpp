#include "tgaimage.h"

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red   = TGAColor(255, 0,   0,   255);

void line(int,int,int,int,TGAImage&, TGAColor);

int main(int argc, char** argv) {
    TGAImage image(100, 100, TGAImage::RGB);

    // Try out line func
    line(13, 20, 80, 40, image, white);
    line(10, 0, 11, 80, image, red);

    image.flip_vertically(); // make origin left corner 
    image.write_tga_file("line.tga");
    return 0;
}



void line(int x0, int y0, int x1 ,int y1, TGAImage &image, TGAColor color) {
    
    // if dy > dx, then swap axis now, and transpose when drawing
    bool steep = false;
    if (std::abs(y0-x1) > std::abs(x0-x1)) {
        steep = true;
        std::swap(x0, y0);
        std::swap(x1, y1);
    }

    // swap points to make x0, y0 the leftmost point
    if (x0 > x1) {
        std::swap(x0, x1);
        std::swap(y0, y1);
    }

    for (int x = x0; x <= x1; x++) {
        float t = (x-x0) / (float)(x1-x0);
        int y = y0*(1.-t) + y1*t;
        if (!steep)
            image.set(x, y, color);
        else
            image.set(y, x, color);  // untranspose the steep line
    }
}
