//
//  GrayTransfer.h
//  loadBMP
//
//  Created by 欧长坤 on 15/4/23.
//  Copyright (c) 2015年 欧长坤. All rights reserved.
//

#ifndef __loadBMP__GrayTransfer__
#define __loadBMP__GrayTransfer__

#include <opencv.hpp>
using namespace cv;

// An implimentation of gray tranfer image
// (x0,y0) (x1,y1) means two points on the transfer curv.
unsigned char transfer_function(unsigned char *pixel, int x0, int y0, int x1, int y1);

void GrayTransfer(Mat &src, Mat &dst);

#endif /* defined(__loadBMP__GrayTransfer__) */
