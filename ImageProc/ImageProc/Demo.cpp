//
//  Demo.cpp
//  ImageProc
//
//  Created by 欧长坤 on 15/6/4.
//  Copyright (c) 2015年 欧长坤. All rights reserved.
//

#include "Demo.h"
#include "GrayTransfer.h"
#include "HistogramProc.h"
#include "ImageEnhancement.h"
#include "Segmentation.h"
#include "DiscreteFourierTransform.h"

void GrayTransferProc(Mat &image) {
    // show an image by processing gray transfer
    Mat gray_transfer_img = Mat(image.size(), image.type());
    GrayTransfer(image, gray_transfer_img);
    imshow("image", image);
    imshow("gray", gray_transfer_img);
}

void HistogramProc(Mat &image) {
    // show an image histogram
    Mat histRed = Mat();
    Mat histGreen = Mat();
    Mat histBlue = Mat();
    GetHist(image, histBlue, histGreen, histRed);
    
    imshow("redHist", histRed);
    imshow("greenHist", histGreen);
    imshow("blueHist", histBlue);
}

void HistogramEualProc(Mat &image) {
    // show an image by processing histogram equalization rgb
    Mat histEual = Mat();
    HistogramEqualizationRGB(image, histEual);
    
    // show the image by using opencv api cv::imshow()
    imshow("histEual", histEual);
    
}

void ImageEnhancement(Mat &image) {
    Mat dst = Mat();
    // show the image by using opencv api cv::imshow()
    Enhancement(image, dst, BOX_TEMP3X3);
    imshow("ImageEnhancement - src", image);
    imshow("ImageEnhancement - dst", dst);
}

void ImageSegmentation(Mat &image) {
    Mat dst_iter = Mat();
    Mat dst_norm = Mat();
    double threshold = 100.0;
    IterateThreshold(image, dst_iter, threshold);
    NormalThreshold(image, dst_norm, threshold);
    imshow("ImageSegmentation - src", image);
    imshow("ImageSegmentation - Iterate", dst_iter);
    imshow("ImageSegmentation - Normal", dst_norm);
}

void DiscreteFourierTransformImage(const char * imagepath) {
    DFTImage(imagepath);
}