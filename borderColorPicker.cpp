#include "borderColorPicker.h"

borderColorPicker::borderColorPicker(unsigned int borderSize, HSLAPixel fillColor, PNG &img, double tolerance) {
    /* your code here */
    this->borderSize = borderSize;
    this->fillColor = fillColor;
    this->img = img;
    this->tolerance = tolerance;
}

HSLAPixel borderColorPicker::operator()(point p) {
    /**
     * Picks the color for pixel (x, y). If the x or y coordinate is a
     * multiple of the spacing, it will be filled with the fillColor.
     * otherwise, it will be filled with white.
     *
     * @param p   The point for which you're picking a color
     * @return    The color chosen for (p).
     */
    /* your code here */
    if (p.x < borderSize || p.x >= img.width() - borderSize || p.y < borderSize || p.y >= img.height() - borderSize) {
        return fillColor;
    } 
    else {
        for (size_t i = p.x-borderSize-1; i < p.x + borderSize+1; i++) { // iterate through pixels
            for (size_t j = p.y-borderSize-1; j < p.y+borderSize+1; j++) {
                double tol = img.getPixel(i, j)->dist(p.c.color);
                bool tolgreater = tol >= tolerance;
                // if not center pixel and within radius bordersize and tol is greater
                if (((i-p.x) != 0 || (j-p.y != 0)) && (((i-p.x)*(i-p.x) + (j-p.y)*(j-p.y)) <= (borderSize*borderSize)) && tolgreater) {
                    return fillColor;
                }
            }
        }
    }
    return *img.getPixel(p.x,p.y);
}
