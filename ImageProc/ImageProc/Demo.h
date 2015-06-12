//
//  Demo.h
//  ImageProc
//
//  Created by 欧长坤 on 15/6/4.
//  Copyright (c) 2015年 欧长坤. All rights reserved.
//

#ifndef __ImageProc__Demo__
#define __ImageProc__Demo__

#include <opencv.hpp>
using namespace cv;

void GrayTransferProc(Mat &image);
void HistogramProc(Mat &image);
void HistogramEualProc(Mat &image);
void ImageEnhancement(Mat &image);
void ImageSegmentation(Mat &image);
void DiscreteFourierTransformImage(const char *imagepath);

#endif /* defined(__ImageProc__Demo__) */
