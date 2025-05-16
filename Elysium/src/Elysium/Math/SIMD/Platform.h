#pragma once

#if defined(__AVX512F__)
#define SIMD_LEVEL_AVX512 1
#elif defined(__AVX2__)
#define SIMD_LEVEL_AVX2 1
#elif defined(__AVX__)
#define SIMD_LEVEL_AVX 1
#elif defined(__SSE4_1__)
#define SIMD_LEVEL_SSE41 1
#else
#define SIMD_LEVEL_SCALAR 1
#endif


/*
* #if GLM_ARCH & GLM_ARCH_AVX2_BIT
#	include <immintrin.h>
#elif GLM_ARCH & GLM_ARCH_AVX_BIT
#	include <immintrin.h>
#elif GLM_ARCH & GLM_ARCH_SSE42_BIT
#	if GLM_COMPILER & GLM_COMPILER_CLANG
#		include <popcntintrin.h>
#	endif
#	include <nmmintrin.h>
#elif GLM_ARCH & GLM_ARCH_SSE41_BIT
#	include <smmintrin.h>
#elif GLM_ARCH & GLM_ARCH_SSSE3_BIT
#	include <tmmintrin.h>
#elif GLM_ARCH & GLM_ARCH_SSE3_BIT
#	include <pmmintrin.h>
#elif GLM_ARCH & GLM_ARCH_SSE2_BIT
#	include <emmintrin.h>
#elif GLM_ARCH & GLM_ARCH_NEON_BIT
#	include "neon.h"
#endif//GLM_ARCH

#if GLM_ARCH & GLM_ARCH_SSE2_BIT
	typedef __m128			glm_f32vec4;
	typedef __m128i			glm_i32vec4;
	typedef __m128i			glm_u32vec4;
	typedef __m128d			glm_f64vec2;
	typedef __m128i			glm_i64vec2;
	typedef __m128i			glm_u64vec2;

	typedef glm_f32vec4		glm_vec4;
	typedef glm_i32vec4		glm_ivec4;
	typedef glm_u32vec4		glm_uvec4;
	typedef glm_f64vec2		glm_dvec2;
#endif

#if GLM_ARCH & GLM_ARCH_AVX_BIT
	typedef __m256d			glm_f64vec4;
	typedef glm_f64vec4		glm_dvec4;
#endif

#if GLM_ARCH & GLM_ARCH_AVX2_BIT
	typedef __m256i			glm_i64vec4;
	typedef __m256i			glm_u64vec4;
#endif

#if GLM_ARCH & GLM_ARCH_NEON_BIT
	typedef float32x4_t			glm_f32vec4;
	typedef int32x4_t			glm_i32vec4;
	typedef uint32x4_t			glm_u32vec4;
#endif

*/