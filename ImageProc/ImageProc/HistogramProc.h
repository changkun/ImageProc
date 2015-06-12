//
//  HistogramProc.h
//  loadBMP
//
//  Created by 欧长坤 on 15/4/23.
//  Copyright (c) 2015年 欧长坤. All rights reserved.
//

#ifndef __loadBMP__HistogramProc__
#define __loadBMP__HistogramProc__

#include <opencv.hpp>
using namespace cv;

enum Color {red, green, blue};

double FindMax(double *list);
void DrawHistRectange(Mat &img, int x, int hist_height, Color color);
void GetHist(Mat &src, Mat &blueHist, Mat &greenHist, Mat &redHist);
void HistogramEqualizationRGB(Mat &src, Mat &dst);

#endif /* defined(__loadBMP__HistogramProc__) */
