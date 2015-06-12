//
//  Segmentation.cpp
//  ImageProc
//
//  Created by 欧长坤 on 15/6/4.
//  Copyright (c) 2015年 欧长坤. All rights reserved.
//

#include "Segmentation.h"
#include <cstdio>

void NormalThreshold(Mat& src, Mat &dst, double threshold) {
    int height = src.rows;
    int width = src.cols;
    for (int i = 0; i < height; i++) {
        dst.create(height, width, CV_8UC3);
        unsigned char * src_line_ptr = (unsigned char *)(src.data + src.step*i);
        unsigned char * dst_line_ptr = (unsigned char *)(dst.data + dst.step*i);
        for (int j = 0; j < width; j++) {
            int avg = (src_line_ptr[3*j+0]+src_line_ptr[3*j+1]+src_line_ptr[3*j+2])/3.0;
            if (avg < threshold) {
                dst_line_ptr[3*j+0] = dst_line_ptr[3*j+1] = dst_line_ptr[3*j+2] = 255;
            } else {
                dst_line_ptr[3*j+0] = dst_line_ptr[3*j+1] = dst_line_ptr[3*j+2] = 0;
            }
        }
    }
}

void IterateThreshold(Mat &src, Mat &dst, double threshold) {
    int height = src.rows;
    int width = src.cols;
    
    int sum_channel_a = 0;
    int sum_channel_b = 0;
    int count_channel_a = 0;
    int count_channel_b = 0;
    for (int i = 0; i < height; i++) {
        unsigned char * line_ptr = (unsigned char *)(src.data + src.step*i);
        for (int j = 0; j < width; j++) {
            int avg = (line_ptr[3*j+0]+line_ptr[3*j+1]+line_ptr[3*j+2])/3.0;
            if (avg < threshold) {
                sum_channel_a += avg;
                count_channel_a++;
            } else {
                sum_channel_b += avg;
                count_channel_b++;
            }
        }
    }
    double mu_channel_a = sum_channel_a/count_channel_a;
    double mu_channel_b = sum_channel_a/count_channel_b;
    double new_threshold = (mu_channel_a+mu_channel_b)/2.0;
    if (fabs(new_threshold-threshold) == 0) {
        IterateThreshold(src, dst, new_threshold);
    } else {
        for (int i = 0; i < height; i++) {
            dst.create(height, width, CV_8UC3);
            unsigned char * src_line_ptr = (unsigned char *)(src.data + src.step*i);
            unsigned char * dst_line_ptr = (unsigned char *)(dst.data + dst.step*i);
            for (int j = 0; j < width; j++) {
                int avg = (src_line_ptr[3*j+0]+src_line_ptr[3*j+1]+src_line_ptr[3*j+2])/3.0;
                if (avg < new_threshold) {
                    dst_line_ptr[3*j+0] = dst_line_ptr[3*j+1] = dst_line_ptr[3*j+2] = 255;
                } else {
                    dst_line_ptr[3*j+0] = dst_line_ptr[3*j+1] = dst_line_ptr[3*j+2] = 0;
                }
            }
        }
    }
}