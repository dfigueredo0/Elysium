#pragma once

#include <limits>

namespace Math {
	inline constexpr double SQRT2 =		1.4142135623730950488016887242;
	inline constexpr double SQRT3 =		1.7320508075688772935274463415059;
	inline constexpr double SQRT12 =	0.7071067811865475244008443621048490;
	inline constexpr double SQRT13 =	0.57735026918962576450914878050196;
	inline constexpr double LN2 =		0.6931471805599453094172321215;
	inline constexpr double TAU =		6.2831853071795864769252867666;
	inline constexpr double PI =		3.1415926535897932384626433833;
	inline constexpr double TWO_PI =	6.2831853071795862319959269371;
	inline constexpr double HALF_PI =	1.5707963267948965579989817343;
	inline constexpr double E =			2.7182818284590452353602874714;
	inline constexpr double EPSILON =	0.0000001192092896;
	inline constexpr double DEG2RAD =	PI / 180.f;
	inline constexpr double RAD2DEG =	180.f / PI;
	inline constexpr double INF =		std::numeric_limits<double>::infinity();
	inline constexpr double NaN =		std::numeric_limits<double>::quiet_NaN();

	inline constexpr double S1 =		-1.66666666666666324348e-01;
	inline constexpr double S2 =		8.33333333332248946124e-03;
	inline constexpr double S3 =		-1.98412698298579493134e-04;
	inline constexpr double S4 =		2.75573137070700676789e-06;
	inline constexpr double S5 =		-2.50507602534068634195e-08;
	inline constexpr double S6 =		1.58969099521155010221e-10;
	inline constexpr double S7 =		-1.60590438368216145994e-12;
	inline constexpr double S8 =		7.64716373181981647590e-15;

	inline constexpr double C1 =		-0.5;                            
	inline constexpr double C2 =		4.16666666666666019037e-02;      
	inline constexpr double C3 =		-1.38888888888741095749e-03;     
	inline constexpr double C4 =		2.48015872894767294178e-05;      
	inline constexpr double C5 =		-2.75573143513906633035e-07;     
	inline constexpr double C6 =		2.08757232129817482790e-09;      
	inline constexpr double C7 =		-1.13596475577881948265e-11;     
	inline constexpr double C8 =		4.77947733238738529744e-14;

	inline constexpr double A1 =		-0.3333333333333293;
	inline constexpr double A2 =		0.1999999999997816;
	inline constexpr double A3 =		-0.1428571427250347;
	inline constexpr double A4 =		0.1111111040546236;
	inline constexpr double A5 =		-0.0909088716976841;
	inline constexpr double A6 =		0.0769187620504483;
	inline constexpr double A7 =		-0.0666107313738753;
	inline constexpr double A8 =		0.0583357013379057;
}
