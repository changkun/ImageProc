//
//  Segmentation.h
//  ImageProc
//
//  Created by 欧长坤 on 15/6/4.
//  Copyright (c) 2015年 欧长坤. All rights reserved.
//

#ifndef __ImageProc__Segmentation__
#define __ImageProc__Segmentation__

#include <opencv.hpp>
using namespace cv;

void IterateThreshold(Mat &src, Mat &dst, double threshold);
void NormalThreshold(Mat& src, Mat &dst, double threshold);

#endif /* defined(__ImageProc__Segmentation__) */
