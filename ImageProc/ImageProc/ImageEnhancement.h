//
//  ImageEnhancement.h
//  ImageProc
//
//  Created by 欧长坤 on 15/5/24.
//  Copyright (c) 2015年 欧长坤. All rights reserved.
//

#ifndef __ImageProc__ImageEnhancement__
#define __ImageProc__ImageEnhancement__

#include <opencv.hpp>

using namespace cv;

enum ProductTemplate {
    CONV_TEMP3X3,
    GAUSS_TEMP3X3,
    GAUSS_TEMP5X5,
    BOX_TEMP3X3,
    MIDDL_TEMP,
    SOBEL_TEMP3x3,
    LAPLACIAN_TEMP_3x3_1,
    LAPLACIAN_TEMP_3x3_2,
    LAPLACIAN_TEMP_3x3_3
};

static const int temp_size = 3;
static const double conv_temp_arr[] = {
    0, -1, 0,
    -1,  0, 1,
    0,  1, 0
};
static const double gauss_temp_arr[] = {
    1, 2, 1,
    2, 4, 2,
    1, 2, 1
};
static const double box_temp_arr[] = {
    1, 1, 1,
    1, 1, 1,
    1, 1, 1
};
static const double middl_temp_arr[] = {
    0, -1, 0,
    -1,  0, 1,
    0,  1, 0
};

// cannot use
static const double gauss_temp_arr_5x5[] = {
    1,4,7,4,1,
    4,16,26,16,4,
    7,26,41,26,7,
    4,16,26,16,4,
    1,4,7,4,1
};

static const double sobel_temp_arr_3x32[] = {
    -1, 0, 1,
    -2, 0, 2,
    -1, 0, 1
};
static const double sobel_temp_arr_3x3[] = {
    -1, -2, -1,
    0, 0, 0,
    1, 2, 1
};

static const double laplacian_temp_arr_3x3_1[] = {
    0, -1, 0,
    -1, 4, -1,
    0, -1, 0
};
static const double laplacian_temp_arr_3x3_2[] = {
    -1, -1, -1,
    -1, 8, -1,
    -1, -1, -1
};
static const double laplacian_temp_arr_3x3_3[] = {
    1, -2, 1,
    -2, 4, -2,
    1, -2, 1
};
Vec3b TempCompute(Vec3b * pixel_array,  ProductTemplate temp);
void SetPixelArray(Mat &src, int x, int y, Vec3b *pixel_array);
void Enhancement(Mat &src, Mat &dst, ProductTemplate temp);
#endif /* defined(__ImageProc__ImageEnhancement__) */
