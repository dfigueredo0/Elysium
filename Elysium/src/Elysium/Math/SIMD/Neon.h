#pragma once

#if defined(__ARM_NEON) || defined(__ARM_NEON__)
#include <arm_neon.h>


inline float32x4_t dupq_lane(float32x4_t v, int lane) {
#if defined(__aarch64__)
    return vdupq_laneq_f32(v, lane);
#else
    return vdupq_n_f32(vgetq_lane_f32(v, lane));
#endif
}

// Dup to 2-lane float32x2_t
inline float32x2_t dup_lane(float32x4_t v, int lane) {
#if defined(__aarch64__)
    return vdup_laneq_f32(v, lane);
#else
    return vdup_n_f32(vgetq_lane_f32(v, lane));
#endif
}

// Set a specific lane in a vector
inline float32x4_t set_lane(float32x4_t vdst, int dlane, float value) {
    return vsetq_lane_f32(value, vdst, dlane);
}

// Copy a lane from vsrc to vdst
inline float32x4_t copy_lane(float32x4_t vdst, int dlane, float32x4_t vsrc, int slane) {
    return set_lane(vdst, dlane, vgetq_lane_f32(vsrc, slane));
}

// Multiply by lane
inline float32x4_t mul_lane(float32x4_t v, float32x4_t vlane, int lane) {
#if defined(__aarch64__)
    return vmulq_laneq_f32(v, vlane, lane);
#else
    return vmulq_f32(v, dupq_lane(vlane, lane));
#endif
}

// Multiply-add by lane
inline float32x4_t madd_lane(float32x4_t acc, float32x4_t v, float32x4_t vlane, int lane) {
#if defined(__aarch64__)
    return vmlaq_laneq_f32(acc, v, vlane, lane);
#else
    return vaddq_f32(acc, vmulq_f32(v, dupq_lane(vlane, lane)));
#endif
}
#endif