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

		static constexpr float NaN = std::numeric_limits<float>::quiet_NaN();
		static constexpr float INF = std::numeric_limits<float>::infinity();
	};

	template<>
	struct MathTraits<double> {
		static constexpr double PI = 3.14159265358979323846;
		static constexpr double TWO_PI = 6.28318530717958647692;
		static constexpr double HALF_PI = 1.57079632679489661923;
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

		static constexpr double NaN = std::numeric_limits<double>::quiet_NaN();
		static constexpr double INF = std::numeric_limits<double>::infinity();
	};
}
