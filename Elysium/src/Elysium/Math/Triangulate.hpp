#pragma once

/*
* 
* 
* 
* High lvl overview
* typedef struct { float x, y } vec2;
* 
* Bounding box with all candidate pixels
* x_min of all vertices
* x_max of all vertices
* y_min of all vertices
* y_max of all vertices
* 
* constant delta's for horizontal and vertical steps
* delta_w0_col = (v1.y - v2.y)
* delta_w0_row = (v2.x - v1.x)
* 
* For z-fighting top-left rule for triangles 
* bias = top_left(v1, v2)
* 
* p0 = { x_min, y_min } //top-left most point
* w0 = edgeCross(&v1, &v2, &p) + bias0
* w1 = edgeCross(&v2, &v0, &p) + bias1
* w2 = edgeCross(&v0, &v1, &p) + bias2
* 
* for (int y = y_min; y <= y_max; y++) {
*	for (int x = x_min; x <= x_max; x++) {

*		if (p in triangle) 
*			put pixel(x, y, color)
*		w0 += delta_0_col
*		w1 += delta_1_col
*		w2 += delta_2_col
*	}
*	w0 += delta_0_row
*	w1 += delta_1_row
*	w2 += delta_2_row
* }
* 
* 
* barycentric coordinates:
* p = (alpha, beta, gamma) how close to each verticy a + b + c = 1
* 
* alpha = cross product (v1v2, v1p)/ cross product (v0v1, v0,v2) = w0 / cross product (v0v1, v0,v2)
* beta = cross product (v2v0, v2p)/ cross product (v0v1, v0,v2) = w1 / cross product (v0v1, v0,v2)
* gamma = cross product (v0v1, v1p)/ cross product (v0v1, v0,v2) = w2 / cross product (v0v1, v0,v2)
* 
* area = edgeCross(&v0, &v1, &v2)
* 
* alpa = w0 / area
* beta = w1 / area
* gamma = w2 / area
* 
* TODO: Interpolate using alpah * v0 + beta * v1 + gamma * v2
*/