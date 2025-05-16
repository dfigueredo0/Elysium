#pragma once

#include <iostream>
#include <vector>

/*
* a = height / width -- aspect ratio
* f = 1 / tan(theta / 2) -- fov (theta = 60 or 90) typically
* n: (zfar - zfar*znear) / (zfar - znear) -- normalize z
* m: zfar / zfar - znear
* b: -zfar*znear/ zfar - znear
* 
* | x | convert   |     afx     |
* | y | --------> |      fy     |
* | z | to screen | nz - nznear |
* 
* math:
*  4x4 matrix
* | af 0 0 0 |   |  x   |   | afx         |
* | 0  f 0 0 | * |  y   | = | fy          |
* | 0  0 m b |   |  z   |   | nz - nznear |
* | 0  0 1 0 |   | 1(w) |   | z           |
*/

std::vector<std::vector<float>> perspective(float fov, float aspect, float znear, float zfar) {
	std::vector<std::vector<float>> m(4, std::vector<float>(4));
	m[0][0] = aspect * (1 / tan(fov / 2));
	m[1][1] = 1 / tan(fov / 2);
	m[2][2] = zfar / (zfar - znear);
	m[3][2] = (-zfar * znear) / (zfar - znear);
	m[2][3] = 1.0;
	return m;
}

std::vector<std::vector<float>> projection(std::vector<std::vector<float>> mat4, std::vector<std::vector<float>> v4) {
	std::vector<std::vector<float>> result = mat4 * v4;

	if (result[0][4] != 0.0) {
		result[0][1] /= result[0][4];
		result[0][2] /= result[0][4];
		result[0][3] /= result[0][4];
	}
	return result;
}