//
//  LoadBMP.cpp
//  loadBMP
//
//  Created by 欧长坤 on 15/4/23.
//  Copyright (c) 2015年 欧长坤. All rights reserved.
//

#include <iostream>
#include "LoadBMP.h"


using namespace std;

// self-implementation function to load a bmp image for extension opencv api cv::imread()
void loadBMPimage(const char *filename, Mat &image) {
    
    // load file head
    FILE* fp;
    fp = fopen(filename, "r");
    if (!fp) {
        cout << filename << " could not be opend!" << endl;
        fclose(fp);
        return;
    }
    char* headerField = new char[2];
    fread(headerField, 2, sizeof(char), fp);
    if (strcmp(headerField, "BM")) {
        delete [] headerField;
        cout << "File is not a bitmap" << endl;
        fclose(fp);
        // no data;
        return;
    }
    delete [] headerField;
    
    unsigned int bmpDataLocation;
    unsigned int bmpWidth;
    unsigned int bmpHeight;
    unsigned short numColorPlanes;
    unsigned short bitsPerPixel;
    unsigned int compressionMethod;
    unsigned int bmpDataSize;
    
    fseek(fp, 0x000a, SEEK_SET);
    fread(&bmpDataLocation, 1, sizeof(unsigned int), fp);
    
    fseek(fp, 0x0012, SEEK_SET);
    fread(&bmpWidth, 1, sizeof(unsigned int), fp);
    fread(&bmpHeight, 1, sizeof(unsigned int), fp);
    fread(&numColorPlanes, 1, sizeof(unsigned short), fp);
    fread(&bitsPerPixel, 1, sizeof(unsigned short), fp);
    fread(&compressionMethod, 1, sizeof(unsigned int), fp);
    fread(&bmpDataSize, 1, sizeof(unsigned int), fp);
    
    if (numColorPlanes != 1 || bitsPerPixel != 24 || compressionMethod != 0) {
        cout << "File Is Not Raw BMP24!" << endl;
        fclose(fp);
        // no data
        return;
    }
    
    // load data part
    unsigned char* bmpData = new unsigned char[bmpDataSize];
    fseek(fp, bmpDataLocation, SEEK_SET);
    fread(bmpData, bmpDataSize, sizeof(unsigned char), fp);
    
    // Get data and save it in a temp cv::Mat
    Mat tempImg = Mat((int)bmpHeight, (int)bmpWidth, CV_8UC3, (void *)bmpData);
    image.create(tempImg.size(), tempImg.type());
    
    // transfer data structure to cv::Mat
    for (int i = 0; i <= tempImg.rows; i++)
        for (int j = 0; j <= tempImg.cols; j++)
            // NOTE: it must be rows-i-1 are not rows-i, because rows-i will be rows that cause at() goes bounds get an error if i == 0
            image.at<Vec3b>(i, j) = tempImg.at<Vec3b>(tempImg.rows-i-1, j);
    
    // save image data to cv::Mat
    //image = Mat((int)bmpHeight, (int)bmpWidth, CV_8UC3, (void *)bmpData);
    fclose(fp);
}
