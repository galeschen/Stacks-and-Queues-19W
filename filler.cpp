/**
 * @file filler.cpp
 * Implementation of functions in the filler namespace.
 *
 */

/**
 * Constructor for pixelLoc, takes a point
 * 
 * @param p The point the pixel is at.
 */
filler::pixelLoc::pixelLoc(point p) {
    /* your code here */
    x = p.x;
    y = p.y;
}

/**
 * Less-than comparison operator. Returns true if p1.x < p2.x  or p1.x == p2.x and p1.y < p2.y.
 * 
 * @param p1 Pixel to compare this against.
 */
bool filler::pixelLoc::operator< (const pixelLoc &p1) const {
    /* your code here */
    if (this->x < p1.x || (this->x == p1.x && this->y < p1.y)) {
        return true;
    }
    return false;
}

/**
 * Performs a multi-point flood fill using breadth first search.
 *
 * @param config      FillerConfig struct to setup the fill
 * @return animation  object illustrating progression of flood fill algorithm
 */
animation filler::fillBFS(FillerConfig &config) {
    /* your code here */
    return fill<Queue>(config);
}

/**
 * Performs a multi-point flood fill using depth first search.
 *
 * @param config      FillerConfig struct to setup the fill
 * @return animation  object illustrating progression of flood fill algorithm
 */
animation filler::fillDFS(FillerConfig &config) {
    /* your code here */
    return fill<Stack>(config);
}

/**
 * Run a multi-point flood fill on an image
 *
 * @param  config     FillerConfig struct with data for flood fill of image
 * @return animation  object illustrating progression of flood fill algorithm
 */
template <template <class T> class OrderingStructure>
animation filler::fill(FillerConfig &config) {   
    /* your code here */
    config.ani = animation();
    int iterations = min(config.centers.size(), config.pickers.size());
    int step = 0;

    for (int i = 0; i < iterations; i++) {
        config.processed = set<pixelLoc>();
        OrderingStructure<point> os = OrderingStructure<point>();

        config.ani.addFrame(config.img);
        point p1 = point(config.centers[i]);
        setPixel(p1, step, i, config);
        os.add(p1);
        while (!os.isEmpty()) {
            point workingPoint = os.peek();
            os.remove();
            addNeighbors(workingPoint, step, i, os, config);
        }
    }
    config.ani.addFrame(config.img);
    return config.ani;
    /**
     * @todo You need to implement this function!
     *
     * This is the basic description of a flood-fill algorithm: Every fill
     * algorithm requires an ordering structure, which is passed to this
     * function via its template parameter. For a breadth-first-search
     * fill, that structure is a Queue, for a depth-first-search, that
     * structure is a Stack. To begin the algorithm, you simply place the
     * given point in the ordering structure, marking it processed
     * (the way you mark it is a design decision you'll make yourself).
     * We have a choice to either change the color, if appropriate, when we
     * add the point to the OS, or when we take it off. In our test cases,
     * we have assumed that you will change the color when a point is added
     * to the structure.
     * Until the structure is empty, you do the following:
     *
     * 1.     Remove a point from the ordering structure, and then...
     *
     *        1.    add its unprocessed neighbors whose color values are
     *              within (or equal to) tolerance distance from the center,
     *              to the ordering structure, and
     *              mark them as processed.
     *        2.    if it is an appropriate frame, send the current PNG to the
     *              animation (as described below).
     *
     * 2.     When implementing your breadth-first-search and
     *        depth-first-search fills, you will need to explore neighboring
     *        pixels in some order.
     *
     *        While the order in which you examine neighbors does not matter
     *        for a proper fill, you must use the same order as we do for
     *        your animations to come out like ours! The order you should put
     *        neighboring pixels **ONTO** the queue or stack is as follows:
     *        ** LEFT(-x), DOWN(+y), RIGHT(+x), UP(-y). IMPORTANT NOTE: *UP*
     *        here means towards the top of the image, so since an image has
     *        smaller y coordinates at the top, this is in the *negative y*
     *        direction. Similarly, *DOWN* means in the *positive y*
     *        direction.** To reiterate, when you are exploring (filling out)
     *        from a given pixel, you must first try to fill the pixel to
     *        it's LEFT, then the one DOWN from it, then to the RIGHT and
     *        finally UP. If you do them in a different order, your fill may
     *        still work correctly, but your animations will be different
     *        from the grading scripts!
     *
     *        Because we are doing a multi-point flood fill you will repeat the flood
     *        fill from several locations stored in the `centers` variable of FillerConfig
     *        struct. Initial fill points should be visited in the order they stored in the
     *        `centers` vector. If a pixel lies in the fill region of multiple start points,
     *        it should only be updated by the first fill. To repeat, pixels should only
     *        be modified the first time they are visited by the filler algorithm.
     *
     * 3.     For every k pixels filled, **starting at the kth pixel**, you
     *        must add a frame to the animation, where k = frameFreq.
     *
     *        For example, if frameFreq is 4, then after the 4th pixel has
     *        been filled you should add a frame to the animation, then again
     *        after the 8th pixel, etc.  You must only add frames for the
     *        number of pixels that have been filled, not the number that
     *        have been checked. So if frameFreq is set to 1, a pixel should
     *        be filled every frame.
     *
     * 4.     Finally, as you leave the function, send one last frame to the
     *        animation. This frame will be the final result of the fill, and
     *        it will be the one we test against.
     *
     */
}

/**
 * Add a frame to the animation if necessary
 * 
 * @param step      How many pixels have been filled in.
 * @param config    FillerConfig struct with data for flood fill of image.
 */
void filler::aniCheck(int step, FillerConfig &config) {
    /* your code here */
    if (step%config.frameFreq == 0) {
        config.ani.addFrame(config.img);
    }
}

/**
 * Sets the value of the pixel at point p according to config.
 * 
 * @param p         The location of the pixel to be changed.
 * @param step      The number of pixels filled.
 * @param i         Which picker is being used.
 * @param config    FillerConfig struct with data for flood fill of image.
 */
void filler::setPixel(point p, int &step, int i, FillerConfig &config) {
    /* your code here */
    HSLAPixel newPixel = config.pickers[i]->operator()(p);
    HSLAPixel * oldPixel = config.img.getPixel(p.x, p.y);
        oldPixel->h = newPixel.h;
        oldPixel->s = newPixel.s;
        oldPixel->l = newPixel.l;
        oldPixel->a = newPixel.a;
        step++;
        aniCheck(step, config);
    config.processed.insert(p);
}

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
void filler::addNeighbors(point p, int &step, int iter, OrderingStructure &os, FillerConfig &config) {
    /* your code here */
    point pleft = point(p.x-1, p.y, p.c);
    if (p.x > 0
        && config.processed.count(pleft) == 0
        && (config.tolerance >= config.img.getPixel(pleft.x, pleft.y)->dist(p.c.color))) {
        setPixel(pleft, step, iter, config);
        os.add(pleft);
    }
    point pdown = point(p.x, p.y+1, p.c);
    if (p.y+1 < config.img.height()
        && config.processed.count(pdown) == 0
        && (config.tolerance >= config.img.getPixel(pdown.x, pdown.y)->dist(p.c.color))) {
        setPixel(pdown, step, iter, config);
        os.add(pdown);
    }
    point pright = point(p.x+1, p.y, p.c);
    if (p.x + 1 < config.img.width()
        && config.processed.count(pright) == 0
        && (config.tolerance >= config.img.getPixel(pright.x, pright.y)->dist(p.c.color))) {
        setPixel(pright, step, iter, config);
        os.add(pright);
    }
    point pup = point(p.x, p.y-1, p.c);
    if (p.y > 0
        && config.processed.count(pup) == 0
        && (config.tolerance >= config.img.getPixel(pup.x, pup.y)->dist(p.c.color))) {
        setPixel(pup, step, iter, config);
        os.add(pup);
    }
}