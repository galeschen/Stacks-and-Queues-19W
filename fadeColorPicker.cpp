#include "fadeColorPicker.h"

fadeColorPicker::fadeColorPicker(double fade) {
    /* your code here */
    fadeFactor = fade;
}

HSLAPixel fadeColorPicker::operator()(point p) {
    /* your code here */
    int dist = sqrt(pow(((int)p.x - (int)p.c.x), 2) + pow(((int)p.y - (int)p.c.y), 2));
    double lum = p.c.color.l * pow(fadeFactor, dist);
    return HSLAPixel(p.c.color.h, p.c.color.s, lum);
}
