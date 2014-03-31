/*
 * mosaic_onmouse.h
 */

#ifndef MOSAIC_ONMOUSE_H_
#define MOSAIC_ONMOUSE_H_

#include "mosaic_totalheader.h"
void onMouseStroke( int event, int x, int y, int flags, void* mouse_param);
void onMouseRect( int event, int x, int y, int flags, void* mouse_param);
void onMouseEraser( int event, int x, int y, int flags, void* mouse_param);

#endif  //MOSAIC_ONMOUSE_H_
