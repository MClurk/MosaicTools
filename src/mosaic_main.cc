/*
 * mosaic_main.cc
 */
#include "mosaic_onmouse.h"

using namespace cv;
int main(int argc, char** argv) {  //parameter: path of image
	if(argc < 2) {
		std::cout<<"no image!"<<std::endl;
		return -1;
	}
	//the parameters pass to onMouse function
	MouseParam mouse_param;
	Mat &origin_image = mouse_param.origin_image;
	Mat &paint_image = mouse_param.paint_image;
	Mat &stroke_image = mouse_param.stroke_image;
	//initialize the parameters
	origin_image = imread(argv[1]);
	if(origin_image.empty()) {
		std::cout<<"no image!";
		return -1;
	}
	paint_image = origin_image.clone();
	stroke_image.create(origin_image.rows, origin_image.cols, CV_8UC1);
	stroke_image = Scalar_<unsigned char>::all(0);
	mouse_param.mosaic_image = origin_image.clone();
	mouse_param.min_x = origin_image.cols - 1;
	mouse_param.min_y = origin_image.rows - 1;
	mouse_param.pre_pt = Point(0, 0);
	int &stroke_radius = mouse_param.stroke_radius;
	string &window_name = mouse_param.window_name;
	window_name = "mosaic >v< Shift to change mode, Ctrl to erase!";

	putText(paint_image, "mode: stroke", Point(10, 10),
							FONT_HERSHEY_PLAIN, 1, Scalar_<unsigned char>::all(255));
	imshow(window_name.c_str(), paint_image);
	setMouseCallback(window_name.c_str(), onMouseStroke, (void*)(&mouse_param));
	bool mode = true;
	  //don't forget waitKey() to stop window
	int c = 0;
	while( 27 != (c = waitKey()) ) {
		switch (c) {
		case 65505:  //Shift = 65505
			if (mode) {
				mouse_param.mosaic_image.copyTo(paint_image);
				putText(paint_image, "mode: rectangle", Point(10, 10),
						FONT_HERSHEY_PLAIN, 1, Scalar_<unsigned char>::all(255));
				imshow(window_name.c_str(), paint_image);
				setMouseCallback(window_name.c_str(), onMouseRect, (void*)(&mouse_param));
				mode = false;
			}
			else {
				mouse_param.mosaic_image.copyTo(paint_image);  //reset the text
				putText(paint_image, "mode: stroke", Point(10, 10),
						FONT_HERSHEY_PLAIN, 1, Scalar_<unsigned char>::all(255));
				imshow(window_name.c_str(), paint_image);
				setMouseCallback(window_name.c_str(), onMouseStroke, (void*)(&mouse_param));
				mode = true;
			}
			break;
		case 65507:  //ctrl = 65507
		case 'e':
			mouse_param.mosaic_image.copyTo(paint_image);  //don't forget reset the text
			putText(paint_image, "mode: erase", Point(10, 10),
						FONT_HERSHEY_PLAIN, 1, Scalar_<unsigned char>::all(255));
			imshow(window_name.c_str(), paint_image);
			setMouseCallback(window_name.c_str(), onMouseEraser, (void*)(&mouse_param));
			break;
		case 'r':
			origin_image.copyTo(mouse_param.mosaic_image);
			origin_image.copyTo(paint_image);
			imshow(window_name.c_str(), paint_image);
			break;
		case 91:  //'['
			if (stroke_radius >= 3) {
				stroke_radius -= 3;
			}
			break;
		case 93:  //']'
			if (stroke_radius <= 200) {
				stroke_radius += 3;
			}
			break;
		}  //switch
	}  //while
	return 0;
}  //main
