#ifndef ZOOMWINDOW_H_INCLUDED
#define ZOOMWINDOW_H_INCLUDED

#include "ComplexPlane.h"
#include "Simple_window.h"

const int PLANE_Y_OFFSET = 20;

struct ZoomWindow : Simple_window
{
    ZoomWindow(Point xy, int w, int h, const string& title);

    double getCenter_r() const;
    double getCenter_i() const;
    double getZoom() const;
    bool wait_for_button();

    private:

        ComplexPlane plane;

        // Widgets:
        In_box next_i;
        In_box next_r;
        In_box next_zoom;
};


#endif // ZOOMWINDOW_H_INCLUDED
