//
//  HistogramProc.cpp
//  loadBMP
//
//  Created by 欧长坤 on 15/4/23.
//  Copyright (c) 2015年 欧长坤. All rights reserved.
//

#include "HistogramProc.h"

double FindMax(double *list) {
    double temp = 0;
    for (int i = 0; i < 256; i++) {
        if (list[i] - temp > 10e-8)
            temp = list[i];
    }
    return temp;
}

void DrawHistRectange(Mat &img, int x, int hist_height, Color color) {
    int height = img.rows;
    //int width = img.cols;
    for (int i = height-1; i > height - hist_height - 1; i--) {
        unsigned char * line_ptr = (unsigned char *)(img.data + img.step*i);
        if (img.channels() == 1) {
            line_ptr[x] = 0;
        } else {
            if (color == red) {
                // BGR Color Space
                line_ptr[3*x+0] = 0;
                line_ptr[3*x+1] = 0;
                line_ptr[3*x+2] = 255;
            } else if (color == green) {
                // BGR Color Space
                line_ptr[3*x+0] = 0;
                line_ptr[3*x+1] = 255;
                line_ptr[3*x+2] = 0;
            } else if (color == blue) {
                // BGR Color Space
                line_ptr[3*x+0] = 255;
                line_ptr[3*x+1] = 0;
                line_ptr[3*x+2] = 0;
            } else {
                exit(-1);
            }
            
        }
    }
}

void GetHist(Mat &src, Mat &blueHist, Mat &greenHist, Mat &redHist) {
    assert(src.channels() == 3);
    int pHist_red[256] = {0};
    int pHist_green[256] = {0};
    int pHist_blue[256] = {0};
    
    int height = src.rows;
    int width = src.cols;
    for (int i = 0; i < height; i++) {
        unsigned char * line_ptr = (unsigned char *)(src.data + src.step*i);
        for (int j = 0; j < width; j++) {
            pHist_blue[line_ptr[3*j+0]]++;
            pHist_green[line_ptr[3*j+1]]++;
            pHist_red[line_ptr[3*j+2]]++;
        }
    }
    
    // normalizing
    double nor_pHist_blue[256] = {0};
    double nor_pHist_green[256] = {0};
    double nor_pHist_red[256] = {0};
    
    for (int i = 0; i<256; i++) {
        nor_pHist_blue[i] = double(pHist_blue[i])/(height*width);
        nor_pHist_green[i] = double(pHist_green[i])/(height*width);
        nor_pHist_red[i] = double(pHist_red[i])/(height*width);
    }
    double maxBlue = FindMax(nor_pHist_blue);
    double maxGreen = FindMax(nor_pHist_green);
    double maxRed = FindMax(nor_pHist_red);
    
    // width of every pillar
    int widthLen = 4;
    int histWidth = 256 * widthLen;
    int histHeight  = 400;
    
    // init histData
    redHist.create(histHeight, histWidth, CV_8UC3);
    greenHist.create(histHeight, histWidth, CV_8UC3);
    blueHist.create(histHeight, histWidth, CV_8UC3);
    
    for (int i = 0; i < histHeight; i++) {
        unsigned char * red_hist_line_ptr = (unsigned char *)(redHist.data + redHist.step*i);
        unsigned char * green_hist_line_ptr = (unsigned char *)(greenHist.data + greenHist.step*i);
        unsigned char * blue_hist_line_ptr = (unsigned char *)(blueHist.data + blueHist.step*i);
        for (int j = 0; j < histWidth; j++) {
            red_hist_line_ptr[3*j+0]   = red_hist_line_ptr[3*j+1]   = red_hist_line_ptr[3*j+2]   =
            green_hist_line_ptr[3*j+0] = green_hist_line_ptr[3*j+1] = green_hist_line_ptr[3*j+2] =
            blue_hist_line_ptr[3*j+0]  = blue_hist_line_ptr[3*j+1]  = blue_hist_line_ptr[3*j+2]  = 255;
        }
    }
    
    for (int i = 0; i < 256; i++) {
        for (int j = 0; j < widthLen; j++) {
            DrawHistRectange(redHist, widthLen*i+j, nor_pHist_red[i]*histHeight/maxRed, red);
            DrawHistRectange(greenHist, widthLen*i+j, nor_pHist_green[i]*histHeight/maxGreen, green);
            DrawHistRectange(blueHist, widthLen*i+j, nor_pHist_blue[i]*histHeight/maxBlue, blue);
        }
    }
}

void HistogramEqualizationRGB(Mat &src, Mat &dst) {
    assert(src.channels() == 3);
    int pHist_red[256] = {0};
    int pHist_green[256] = {0};
    int pHist_blue[256] = {0};
    
    int height = src.rows;
    int width = src.cols;
    for (int i = 0; i < height; i++) {
        unsigned char * line_ptr = (unsigned char *)(src.data + src.step*i);
        for (int j = 0; j < width; j++) {
            pHist_blue[line_ptr[3*j+0]]++;
            pHist_green[line_ptr[3*j+1]]++;
            pHist_red[line_ptr[3*j+2]]++;
        }
    }
    
    int cdf_red[256] = {0};
    int cdf_green[256] = {0};
    int cdf_blue[256] = {0};
    for (int i = 0; i < 256; i++) {
        for (int j = 0; j <= i; j++) {
            cdf_red[i] += pHist_red[j];
            cdf_green[i] += pHist_green[j];
            cdf_blue[i] += pHist_blue[j];
        }
    }
    dst.create(height, width, CV_8UC3);
    for (int i = 0; i < height; i++) {
        unsigned char * dst_line_ptr = (unsigned char *)(dst.data + dst.step*i);
        unsigned char * line_ptr = (unsigned char *)(src.data + src.step*i);
        for (int j = 0; j < width; j++) {
            dst_line_ptr[3*j+0] = int((cdf_blue[line_ptr[3*j+0]]-cdf_blue[0])*255/(height*width-cdf_blue[0]));
            dst_line_ptr[3*j+1] = int((cdf_green[line_ptr[3*j+1]]-cdf_green[0])*255/(height*width-cdf_green[0]));
            dst_line_ptr[3*j+2] = int((cdf_red[line_ptr[3*j+2]]-cdf_red[0])*255/(height*width-cdf_red[0]));
        }
    }
}
