/*
 * mosaic_totalheader.h
 */

#ifndef MOSAIC_TOTALHEADER_H_
#define MOSAIC_TOTALHEADER_H_

#include<cv.h>
#include<highgui.h>
#include<cxcore.h>

struct MouseParam {  //the struct of parameters
	cv::Mat origin_image;  //source of image
	cv::Mat paint_image;  //image to show on the window
	cv::Mat stroke_image;  //use in Stroke only, be the binary mask, type is 8UC1
	cv::Mat mosaic_image;  //add mosaic on it
	int min_x, max_x;
	int min_y, max_y;
	cv::Point pre_pt;
	std::string window_name;
	int stroke_radius;
	MouseParam(): min_x(0), max_x(0), min_y(0), max_y(0), stroke_radius(30) {}
};

#endif /* MOSAIC_TOTALHEADER_H_ */
