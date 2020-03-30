/**
 * @file filler.h
 * Defintion of a filler namespace.
 *
 */
#ifndef _FILLER_H_
#define _FILLER_H_

#include <iostream>

#include "cs221util/PNG.h"

#include "animation.h"
#include "center.h"
#include "colorPicker.h"
#include "point.h"
#include "queue.h"
#include "stack.h"

using namespace std;
using namespace cs221util;

/**
 * filler namespace: specifies a set of functions for performing flood
 * fills on images.
 *
 */
namespace filler
{

class pixelLoc {
    public:
     
    int x;
    int y;
        
    /**
     * Constructor for pixelLoc, takes a point
     * 
     * @param p The point the pixel is at.
     */
    pixelLoc(point p);

    /**
     * Less-than comparison operator. Returns true if p1.x < p2.x  or p1.x == p2.x and p1.y < p2.y.
     * 
     * @param p1 First pixel to compare.
     * @param p2 Second pixel to compare.
     */
    bool operator< (const pixelLoc &p1) const;
};

/**
 * Struct to store configuration variables for filler function.
 * The length of the vectors `centers` and `pickers` should match.
 * We don't check this but you will likely get a segfault or other bugs if the lengths differ.
 * Each entry in `centers` is the seed location used for the flood fill by
 * the colorPicker at the corresponding location in `pickers`.
 */
struct FillerConfig
{
    int frameFreq;                  // Frequency with which to save frames to GIF animation.
    float tolerance;                // Tolerance used to determine if pixel is in fill region.
    PNG img;                        // Image to perform the fill on.
    vector<center> centers;         // Seed locations where the fill will begin.
    vector<colorPicker *> pickers;  // colorPickers used to fill the regions.
    std::set<pixelLoc> processed;   // set of pixels that have been processed.
    animation ani;
};

/**
 * Performs a multi-point flood fill using breadth first search.
 *
 * @param config      FillerConfig struct to setup the fill.
 * @return animation  Object illustrating progression of flood fill algorithm.
 */
animation fillBFS(FillerConfig &config);

/**
 * Performs a multi-point flood fill using depth first search.
 *
 * @param config      FillerConfig struct to setup the fill.
 * @return animation  Object illustrating progression of flood fill algorithm.
 */
animation fillDFS(FillerConfig &config);

/**
 * Run a multi-point flood fill on an image.
 *
 * @param  config     FillerConfig struct with data for flood fill of image.
 * @return animation  Object illustrating progression of flood fill algorithm.
 */
template <template <class T> class OrderingStructure> animation fill(FillerConfig &config);

/**
 * Add a frame to the animation if necessary
 * 
 * @param step      How many pixels have been filled in.
 * @param config    FillerConfig struct with data for flood fill of image.
 */
void aniCheck(int step, FillerConfig &config);

/**
 * Sets the value of the pixel at point p according to config.
 * 
 * @param p         The location of the pixel to be changed.
 * @param step      The number of pixels filled.
 * @param i         Which picker is being used.
 * @param config    FillerConfig struct with data for flood fill of image.
 */
void setPixel(point p, int &step, int i, FillerConfig &config);

/**
 * Helper function for fill, add eligible neighbors of the point to the ordering struct
 * 
 * @param p         The point being checked.
 * @param step      The number of pixels filled.
 * @param i         The current iteration, which picker to use.
 * @param os        Ordering struct to add neighbors to.
 * @param config    FillerConfig struct with data for flood fill of image.
 */
template <class OrderingStructure>
void addNeighbors(point p, int &step, int iter, OrderingStructure &os, FillerConfig &config);

} // namespace filler

#include "filler.cpp"

#endif
