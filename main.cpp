#include <iostream>
#include <string>
#include "CImg.h"

using namespace cimg_library;

int main(int argc,char **argv){

    CImgDisplay main_window(200,200,"Braun Fighters",0);

    while(!main_window.is_closed()){
        CImg<> img(main_window.window_width(),main_window.window_height(),1,3);
        img.rand(0,255); // Fill image with noise
        if(main_window.is_resized()) main_window.resize(CImg<>(main_window.window_width(),main_window.window_height(),1,3));
        main_window.display(img);
    }

    return 0;
}