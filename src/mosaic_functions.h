/*
 * mosaic_functions.h
 */
#ifndef MOSAIC_FUNCTIONS_H_
#define MOSAIC_FUNCTIONS_H_

#include "mosaic_totalheader.h"
void addEraser(const cv::Mat &origin_image,
					  cv::Mat &stroke_image,
					  cv::Mat &mosaic_image,
					  int &min_x,
					  int &max_x,
					  int &min_y,
					  int &max_y);
void addMosaic(const cv::Mat &origin_image,
					  cv::Mat &stroke_image,
					  cv::Mat &mosaic_image,
					  int &min_x,
					  int &max_x,
					  int &min_y,
					  int &max_y);
void addColor(const cv::Mat &origin_image,
			  const cv::Mat &stroke_image,
			  cv::Mat &paint_image,
			  int min_x,
			  int max_x,
			  int min_y,
			  int max_y);

#endif  //MOSAIC_FUNCTIONS_H_
