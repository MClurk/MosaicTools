/*
 * mosaic_onmouse.cc
 */
#include "mosaic_functions.h"
using namespace cv;

void onMouseStroke( int event, int x, int y, int flags, void* mouse_param ) {
	MouseParam* ptr_mouse_param = (MouseParam*)mouse_param;
	const Mat &origin_image = ptr_mouse_param->origin_image;
	Mat &paint_image = ptr_mouse_param->paint_image;
	Mat &stroke_image = ptr_mouse_param->stroke_image;
	Mat &mosaic_image = ptr_mouse_param->mosaic_image;  //never clean it
	int &min_x = ptr_mouse_param->min_x;
	int &max_x = ptr_mouse_param->max_x;
	int &min_y = ptr_mouse_param->min_y;
	int &max_y = ptr_mouse_param->max_y;
	Point &pre_pt = ptr_mouse_param->pre_pt;
	string window_name = ptr_mouse_param->window_name;
	const int &stroke_radius = ptr_mouse_param->stroke_radius;

	if (EVENT_LBUTTONDOWN != event &&
	    flags != EVENT_FLAG_LBUTTON &&
	    flags != EVENT_FLAG_RBUTTON) {
		circle(paint_image, Point(x, y), stroke_radius / 2, Scalar_<unsigned char>::all(255));
		imshow(window_name.c_str(), paint_image);
		mosaic_image.copyTo(paint_image);
	}  //when not drawing

	else if(EVENT_LBUTTONDOWN == event) {
		pre_pt = Point(x,y);
	}  //start drawing

	else if(EVENT_LBUTTONUP == event) {
		addMosaic(origin_image, stroke_image, mosaic_image, min_x, max_x, min_y, max_y);
		mosaic_image.copyTo(paint_image);
		imshow(window_name.c_str(), paint_image);
	}  //when stop draw, add the mosaics
	else if( event == EVENT_MOUSEMOVE &&
			 flags == EVENT_FLAG_LBUTTON ) {
		Point pt(x,y);
		line(stroke_image, pre_pt, pt, Scalar_<unsigned char>::all(255), stroke_radius);  //make the mask
		  //draw a transparent line
		int stroke_min_x = max(min(x, pre_pt.x) - stroke_radius / 2, 0);
		int stroke_max_x = min(max(x, pre_pt.x) + stroke_radius / 2, origin_image.cols - 1);
		int stroke_min_y = max(min(y, pre_pt.y) - stroke_radius / 2, 0);
		int stroke_max_y = min(max(y, pre_pt.y) + stroke_radius / 2, origin_image.rows - 1);
		addColor(origin_image, stroke_image, paint_image, stroke_min_x, stroke_max_x, stroke_min_y, stroke_max_y);
		  //focus on a rectangle that include the stroke
		min_x = max(min(min_x, x - stroke_radius / 2), 0);  //attention!
		max_x = min(max(max_x, x + stroke_radius / 2), origin_image.cols - 1);
		min_y = max(min(min_y, y - stroke_radius / 2), 0);
		max_y = min(max(max_y, y + stroke_radius / 2), origin_image.rows - 1);

		circle(paint_image, pt, stroke_radius / 2, Scalar_<unsigned char>::all(255));
		  //here, also use the stroke_image
		pre_pt = pt;
		imshow(window_name.c_str(), paint_image);
		}  //when drawing stroke
}

void onMouseRect( int event, int x, int y, int flags, void* mouse_param ) {
	MouseParam* ptr_mouse_param = (MouseParam*)mouse_param;
	const Mat &origin_image = ptr_mouse_param->origin_image;
	Mat &paint_image = ptr_mouse_param->paint_image;
	Mat &stroke_image = ptr_mouse_param->stroke_image;
	Mat &mosaic_image = ptr_mouse_param->mosaic_image;
	int &min_x = ptr_mouse_param->min_x;
	int &max_x = ptr_mouse_param->max_x;
	int &min_y = ptr_mouse_param->min_y;
	int &max_y = ptr_mouse_param->max_y;
	Point &pre_pt = ptr_mouse_param->pre_pt;
	string &window_name = ptr_mouse_param->window_name;

	if (EVENT_LBUTTONDOWN != event &&
		flags != EVENT_FLAG_LBUTTON &&
		flags != EVENT_FLAG_RBUTTON) {}  //when not drawing, do nothing
	else if(EVENT_LBUTTONDOWN == event) {
		pre_pt = Point(x,y);
	}  //start drawing
	else if(EVENT_LBUTTONUP == event) {
		min_x = max(min(pre_pt.x, x), 0);  //attention!
		max_x = min(max(pre_pt.x, x), origin_image.cols - 1);
		min_y = max(min(pre_pt.y, y), 0);
		max_y = min(max(pre_pt.y, y), origin_image.rows - 1);
		rectangle(stroke_image, Point(min_x, min_y), Point(max_x, max_y), Scalar::all(255), CV_FILLED);
		addMosaic(origin_image, stroke_image, mosaic_image, min_x, max_x, min_y, max_y);
		stroke_image = Scalar_<unsigned char>::all(0);
		mosaic_image.copyTo(paint_image);
		imshow(window_name.c_str(), paint_image);
	}
	else if( event == EVENT_MOUSEMOVE &&
			 flags == EVENT_FLAG_LBUTTON) {
		rectangle(paint_image, pre_pt, Point(x, y), Scalar_<unsigned char>::all(255), 1, 8, 0);
		imshow(window_name.c_str(), paint_image);
		mosaic_image.copyTo(paint_image);
	}  //when drawing stroke
}

void onMouseEraser( int event, int x, int y, int flags, void* mouse_param ) {
	MouseParam* ptr_mouse_param = (MouseParam*)mouse_param;
	const Mat &origin_image = ptr_mouse_param->origin_image;
	Mat &paint_image = ptr_mouse_param->paint_image;
	Mat &stroke_image = ptr_mouse_param->stroke_image;
	Mat &mosaic_image = ptr_mouse_param->mosaic_image;  //never clean it
	int &min_x = ptr_mouse_param->min_x;
	int &max_x = ptr_mouse_param->max_x;
	int &min_y = ptr_mouse_param->min_y;
	int &max_y = ptr_mouse_param->max_y;
	Point &pre_pt = ptr_mouse_param->pre_pt;
	string &window_name = ptr_mouse_param->window_name;
	const int &stroke_radius = ptr_mouse_param->stroke_radius;

	if (EVENT_LBUTTONDOWN != event &&
		flags != EVENT_FLAG_LBUTTON &&
		flags != EVENT_FLAG_RBUTTON) {
		circle(paint_image, Point(x, y), stroke_radius / 2, Scalar_<unsigned char>(0, 0, 255)/*red*/);
		imshow(window_name.c_str(), paint_image);
		mosaic_image.copyTo(paint_image);
	}  //when not drawing
	else if(EVENT_LBUTTONDOWN == event) {
		pre_pt = Point(x,y);
	}  //start drawing
	else if( event == EVENT_MOUSEMOVE &&
		flags == EVENT_FLAG_LBUTTON ) {
		Point pt(x,y);
		  //focus on a rectangle that include the single stroke
		min_x = max(min(pre_pt.x, x) - stroke_radius / 2, 0);
		max_x = min(max(pre_pt.x, x) + stroke_radius / 2, origin_image.cols - 1);
		min_y = max(min(pre_pt.y, y) - stroke_radius / 2, 0);
		max_y = min(max(pre_pt.y, y) + stroke_radius / 2, origin_image.rows - 1);

		line(stroke_image, pre_pt, pt, Scalar_<unsigned char>::all(255), stroke_radius);
		addEraser(origin_image, stroke_image, mosaic_image, min_x, max_x, min_y, max_y);
		circle(paint_image, pt, stroke_radius / 2, Scalar_<unsigned char>(0, 0, 255));
		imshow(window_name.c_str(), paint_image);
		mosaic_image.copyTo(paint_image);
		pre_pt = pt;
	}  //when drawing stroke
}
