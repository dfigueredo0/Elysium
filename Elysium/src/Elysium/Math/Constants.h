#pragma once

#include <limits>

namespace Math {
	template<typename T>
	struct MathTraits;

	template<>
	struct MathTraits<float> {
		static constexpr float PI = 3.1415927f;
		static constexpr float TWO_PI = 6.2831853f;
		static constexpr float HALF_PI = 1.5707964f;
		static constexpr float E = 2.7182818f;
		static constexpr float LN2 = 0.6931471f;
		static constexpr float LOG2_E = 1.4426951f;
		static constexpr float LOG10_E = 0.4342945f;
		static constexpr float DEG2RAD = PI / 180.0f;
		static constexpr float RAD2DEG = 180.0f / PI;
		static constexpr float EPSILON = 1.1920929e-07f;

		static constexpr float S1 = -1.6666666e-01f;
		static constexpr float S2 = 8.3333332e-03f;
		static constexpr float S3 = -1.9841269e-04f;
		static constexpr float S4 = 2.7557314e-06f;
		static constexpr float S5 = -2.5050760e-08f;
		static constexpr float S6 = 1.5896910e-10f;
		static constexpr float S7 = -1.6059044e-12f;
		static constexpr float S8 = 7.6471638e-15f;

		static constexpr float C1 = -0.5;
		static constexpr float C2 = 4.1666667e-02f;
		static constexpr float C3 = -1.3888889e-03f;
		static constexpr float C4 = 2.4801587e-05f;
		static constexpr float C5 = -2.7557314e-07f;
		static constexpr float C6 = 2.0875723e-09f;
		static constexpr float C7 = -1.1359648e-11f;
		static constexpr float C8 = 4.7794773e-14f;

		static constexpr float A1 = -0.3333333f;
		static constexpr float A2 = 0.19999999f;
		static constexpr float A3 = -0.1428571f;
		static constexpr float A4 = 0.1111111f;
		static constexpr float A5 = -0.0909089f;
		static constexpr float A6 = 0.0769188f;
		static constexpr float A7 = -0.0666107f;
		static constexpr float A8 = 0.0583357f;

		static constexpr float NaN = std::numeric_limits<float>::quiet_NaN();
		static constexpr float INF = std::numeric_limits<float>::infinity();
	};

	template<>
	struct MathTraits<double> {
		static constexpr double PI = 3.14159265358979323846;
		static constexpr double TWO_PI = 6.28318530717958647692;
		static constexpr double HALF_PI = 1.57079632679489661923;
		static constexpr double E = 2.71828182845904523536;
		static constexpr double LN2 = 0.6931471805599453;
		static constexpr double LOG2_E = 1.442695040888963;
		static constexpr double LOG10_E = 0.4342944819;
		static constexpr double DEG2RAD = PI / 180.0;
		static constexpr double RAD2DEG = 180.0 / PI;
		static constexpr double EPSILON = 2.2204460492503131e-16;

		static constexpr double S1 = -1.66666666666666324348e-01;
		static constexpr double S2 = 8.33333333332248946124e-03;
		static constexpr double S3 = -1.98412698298579493134e-04;
		static constexpr double S4 = 2.75573137070700676789e-06;
		static constexpr double S5 = -2.50507602534068634195e-08;
		static constexpr double S6 = 1.58969099521155010221e-10;
		static constexpr double S7 = -1.60590438368216145994e-12;
		static constexpr double S8 = 7.64716373181981647590e-15;

		static constexpr double C1 = -0.5;
		static constexpr double C2 = 4.16666666666666019037e-02;
		static constexpr double C3 = -1.38888888888741095749e-03;
		static constexpr double C4 = 2.48015872894767294178e-05;
		static constexpr double C5 = -2.75573143513906633035e-07;
		static constexpr double C6 = 2.08757232129817482790e-09;
		static constexpr double C7 = -1.13596475577881948265e-11;
		static constexpr double C8 = 4.77947733238738529744e-14;

		static constexpr double A1 = -0.3333333333333293;
		static constexpr double A2 = 0.1999999999997816;
		static constexpr double A3 = -0.1428571427250347;
		static constexpr double A4 = 0.1111111040546236;
		static constexpr double A5 = -0.0909088716976841;
		static constexpr double A6 = 0.0769187620504483;
		static constexpr double A7 = -0.0666107313738753;
		static constexpr double A8 = 0.0583357013379057;

		static constexpr double NaN = std::numeric_limits<double>::quiet_NaN();
		static constexpr double INF = std::numeric_limits<double>::infinity();
	};
}
