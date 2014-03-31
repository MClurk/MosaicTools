/*
 * mosaic_functions.cc
 */
#include "mosaic_totalheader.h"
using namespace cv;

void addEraser(const Mat &origin_image,
					 Mat &stroke_image,
					 Mat &mosaic_image,
					 int &min_x,  //& because I want to change their value
					 int &max_x,
					 int &min_y,
					 int &max_y) {
	if (min_x > max_x || min_y > max_y)
		return;  //attention!
	Mat roi_origin(origin_image, Range(min_y, max_y + 1), Range(min_x, max_x + 1));
	Mat roi_stroke(stroke_image, Range(min_y, max_y + 1), Range(min_x, max_x + 1));
	Mat roi_mosaic(mosaic_image, Range(min_y, max_y + 1), Range(min_x, max_x + 1));
	int height = roi_origin.rows;
	int width = roi_origin.cols;
	for(int y = 0; y < height; ++y) {
		const unsigned char* ptr_origin_data = roi_origin.ptr(y);
		const unsigned char* ptr_stroke_data = roi_stroke.ptr(y);
		unsigned char* ptr_mosaic_data = roi_mosaic.ptr(y);
		for(int x = 0; x < width; ++x) {
			if(255 == ptr_stroke_data[x]) {
				for(int c = 0; c < 3; ++c) {
					ptr_mosaic_data[3 * x + c] = ptr_origin_data[3 * x + c];
				}
			}
		}
	}
	  //reset
	min_x = origin_image.cols - 1;
	max_x = 0;
	min_y = origin_image.rows - 1;
	max_y = 0;
	stroke_image = Scalar_<unsigned char>::all(0);
	return;
}
void addMosaic(const Mat &origin_image,
					 Mat &stroke_image,
					 Mat &mosaic_image,
					 int &min_x,  //& because I want to change their value
					 int &max_x,
					 int &min_y,
					 int &max_y) {
	if (min_x > max_x || min_y > max_y)
		return;  //attention!
	const int mosaic_size = 15;
	int height_cell = (int)( (max_y - min_y + 1 - 1) / mosaic_size ) + 1;  //be attention of -1
	int width_cell = (int)( (max_x - min_x + 1 - 1) / mosaic_size ) + 1;
	vector< vector<int> > vec_numbers( height_cell, vector<int>(width_cell, 0) );
	vector< vector< vector<int> > > vec3D_colors(
			height_cell, vector< vector<int> >(width_cell, vector<int>(3, 0)));

	Mat roi_image(origin_image, Range(min_y, max_y + 1), Range(min_x, max_x + 1));
	for(int y = 0; y < roi_image.rows; ++y) {
		const unsigned char* ptr_data = roi_image.ptr(y);

		int yy = (int)(y / mosaic_size);
		for(int x = 0; x < roi_image.cols; ++x) {
			int xx = (int)(x / mosaic_size);
			vec_numbers[yy][xx] += 1;
			for(int c = 0; c < 3; ++c) {
				vec3D_colors[yy][xx][c] += ptr_data[3 * x + c];
			}
		}
	}
	for(int y = 0; y < height_cell; ++y) {
		for(int x = 0; x < width_cell; ++x) {
			if(0 == vec_numbers[y][x])
				continue;
			for(int c = 0; c < 3; ++c)
				vec3D_colors[y][x][c] = vec3D_colors[y][x][c] / vec_numbers[y][x];  //no need to be double type
		}
	}
	Mat roi_mosaic(mosaic_image, Range(min_y, max_y + 1), Range(min_x, max_x + 1));
	Mat roi_stroke(stroke_image, Range(min_y, max_y + 1), Range(min_x, max_x + 1));
	for(int y = 0; y < roi_mosaic.rows; ++y) {
		unsigned char* ptr_mosaic_data = roi_mosaic.ptr(y);
		const unsigned char* ptr_stroke_data = roi_stroke.ptr(y);

		int yy = (int)(y / mosaic_size);
		for(int x = 0; x < roi_mosaic.cols; ++x) {
			if (0 == ptr_stroke_data[x])
				continue;
			int xx = (int)(x / mosaic_size);
			for (int c = 0; c < 3; ++c)
				ptr_mosaic_data[3 * x + c] = (unsigned char)vec3D_colors[yy][xx][c];
		}
	}
	  //reset
	min_x = origin_image.cols - 1;
	max_x = 0;
	min_y = origin_image.rows - 1;
	max_y = 0;
	stroke_image = Scalar_<unsigned char>::all(0);
	return;
}

void addColor(const Mat &origin_image,
			  const Mat &stroke_image,
			  Mat &paint_image,
			  int min_x,
			  int max_x,
			  int min_y,
			  int max_y) {
	if (min_x > max_x || min_y > max_y)
		return;  //attention!
	Mat roi_origin(origin_image, Range(min_y, max_y + 1), Range(min_x, max_x + 1));
	Mat roi_stroke(stroke_image, Range(min_y, max_y + 1), Range(min_x, max_x + 1));
	Mat roi_paint(paint_image, Range(min_y, max_y + 1), Range(min_x, max_x + 1));
	int height = roi_origin.rows;
	int width = roi_origin.cols;
	for(int y = 0; y < height; ++y) {
		unsigned char* ptr_origin_data = roi_origin.ptr(y);
		unsigned char* ptr_stroke_data = roi_stroke.ptr(y);
		unsigned char* ptr_paint_data = roi_paint.ptr(y);
		for (int x = 0; x < width; ++x) {
			if (255 == ptr_stroke_data[x]) {
				ptr_paint_data[3 * x + 0] = ptr_origin_data[3 * x + 0] * 0.7 + 255 * 0.3;
				ptr_paint_data[3 * x + 1] = ptr_origin_data[3 * x + 1] * 0.7 + 0 * 0.3;
				ptr_paint_data[3 * x + 2] = ptr_origin_data[3 * x + 2] * 0.7 + 128 * 0.3;
			}
		}
	}
	return;
}
