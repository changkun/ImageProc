//
//  GrayTransfer.cpp
//  loadBMP
//
//  Created by 欧长坤 on 15/4/23.
//  Copyright (c) 2015年 欧长坤. All rights reserved.
//

#include "GrayTransfer.h"

// An implimentation of gray tranfer image
// (x0,y0) (x1,y1) means two points on the transfer curv.
unsigned char transfer_function(unsigned char *pixel, int x0, int y0, int x1, int y1) {
    if ((int)*pixel < x0) {
        return *pixel;
    } else if ( (int)*pixel >= x0 && (int)*pixel < x1 ) {
        return (unsigned char)(((float)(y1-y0)/(x1-x0))*((float)*pixel - x0) + y0);
    } else if ( (int)*pixel >= x1 && (int)*pixel <= 255 ){
        if ((int)(((float)(256-y1)/(256-x1))*((float)(*pixel) - x1) + y1) > 255)
            return 255;
        else
            return (int)(((float)(256-y1)/(256-x1))*((float)(*pixel) - x1) + y1);
    } else {
        return *pixel;
    }
}
void GrayTransfer(Mat &src, Mat &dst) {
    int height = src.rows;
    int width  = src.cols;
    for (int i = 0; i < height; i++) {
        unsigned char * line_ptr = (unsigned char *)(src.data + src.step*i);
        unsigned char * dst_ptr = (unsigned char *)(dst.data + dst.step*i);
        for (int j = 0; j < width; j++) {
            if (src.channels() == 1) {
                dst_ptr[j] = transfer_function(&line_ptr[j], 30, 30, 100, 200);
            } else {
                dst_ptr[3*j+0] = transfer_function(&line_ptr[3*j+0], 30, 30, 100, 200);
                dst_ptr[3*j+1] = transfer_function(&line_ptr[3*j+1], 30, 30, 100, 200);
                dst_ptr[3*j+2] = transfer_function(&line_ptr[3*j+2], 30, 30, 100, 200);
            }
        }
    }
}
