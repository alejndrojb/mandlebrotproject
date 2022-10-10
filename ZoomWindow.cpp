#include "ZoomWindow.h"

ZoomWindow::ZoomWindow(Point xy, int w, int h, const string& title) :
    // initialize new simple window, construct plane, and initialize in_box members
    Simple_window{xy,w,h,title},                                            
    plane{PLANE_Y_OFFSET,complex<double> {0,0}, 1.0, w, h-PLANE_Y_OFFSET},  
    next_i{Point{x_max()-130,0}, 50, 20, "Center i:"},                     
    next_r{Point{x_max()-250,0}, 50, 20, "Center r:"},
    next_zoom{Point{x_max()-370,0}, 50, 20, "Zoom Level:"}
{
    // attach plane and in_box members
    attach(plane);
    attach(next_i);
    attach(next_r);
    attach(next_zoom);
    plane.createBuffer();      // call createBuffer on plane constructed
}

double ZoomWindow::getCenter_r() const
{
    return plane.getCenter().real();    
}

double ZoomWindow::getCenter_i() const
{
    return plane.getCenter().imag();
}

double ZoomWindow::getZoom() const
{
    return plane.getZoomLevel();
}

bool ZoomWindow::wait_for_button()
{
    Simple_window::wait_for_button();

    string stream = next_r.get_string() + " " + next_i.get_string() + " " + next_zoom.get_string();     // create string with in_boxes values
    istringstream iss(stream);  // store stream in iss

    double center_r, center_i, zoom_level;
    iss >> center_r >> center_i >> zoom_level;  // extract in_box values from iss and assign them to their correct variables
    iss.clear();                                // clear iss in between reads to clear EOF state 

    complex<double>center(center_r,center_i);   // construct a complex number with extracted center values
    plane.setCenter(center);                    // set plane center with the complex number constucted
    plane.setZoomLevel(zoom_level);             // set plane zoom level 
    plane.createBuffer();                       // call createBuffer on plane
}
