#include "ComplexPlane.h"

///map from pixels to complex plane
double mapRange(double n, double fromLow, double fromHigh, double toLow, double toHigh)
{
    return ((n - fromLow) / (fromHigh - fromLow)) * (toHigh - toLow) + toLow;
}
///write rgb values into one dimensional FLTK output buffer
void writePixel(unsigned char* buf, int xPixels, int row, int col, unsigned char r, unsigned char g, unsigned char b)   
{   
    buf[(row * xPixels + col) * 3] = r;         
    buf[(row * xPixels + col) * 3 + 1] = g;
    buf[(row * xPixels + col) * 3 + 2] = b;
}
///count the number of Mandelbrot iterations for a given point on the complex plane, used to determine pixel color
int countIterations(double re, double im, int maxIterations)
{
    complex<double> c(re,im);   // construct a complex number with real and imag values passed in
    complex<double> z(0,0);     // construct a complex number at (0,0)
    int count = 0;              // var to keep track of count

    // repeatedly calculate z = z*z + c, until abs(z) is greater than 2.0 or count has exceeded maxIterations
    while (count < maxIterations && abs(z) < 2.0)   
    {
        z = z*z + c;            
        count++;
    }

    return count;           
}

void ComplexPlane::draw_lines() const
{
    fl_draw_image(buf,10,y_pixel_offset,xPixels,yPixels);
}

void ComplexPlane::createBuffer()
{
    unsigned char r,g,b;    // create r,g,b variables for the color

    for (int y = 0; y < yPixels; y++)
    {
        for (int x = 0; x < xPixels; x++) 
        {
            double re = mapRange(x, 0, xPixels, center.real() - (reRange/2.0*zoomLevel), center.real() + (reRange/2.0*zoomLevel));  // map xpixel to real complex plane value
            double im = mapRange(y, yPixels, 0, center.imag() - (imRange/2.0*zoomLevel), center.imag() + (imRange/2.0*zoomLevel));  // map ypixel to imag complex plane value
            int iterations = countIterations(re,im,maxIterations);  // store the number returned from countIterations to determine color for given pixel
            Fl::get_color(maxIterations - iterations, r, g, b);     // call FL::get_color  to assign r,g,b variables to the correct color
            writePixel(buf, xPixels, y, x, r, g, b);                // call writePixel and pass in buf, current pixel (x,y) and r,g,b values to output color to buf
        }
    }
}