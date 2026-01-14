#ifndef MATH_UTILS_H
#define MATH_UTILS_H

#define PI 3.14159265358979323846f

static inline float ClampFloat(float value, float min, float max) {
    if (value < min) return min;
    if (value > max) return max;
    return value;
}

static inline int ClampInt(int value, int min, int max) {
    if (value < min) return min;
    if (value > max) return max;
    return value;
}

static inline float LerpFloat(float a, float b, float t) {
    return a + t * (b - a);
}

static inline int LerpInt(int a, int b, float t) {
    return a + (int)(t * (b - a));
}

static inline float DegreesToRadians(float degrees) {
    return degrees * PI / 180.0f;
}

static inline float RadiansToDegrees(float radians) {
    return radians * 180.0f / PI;
}

static inline float MapFloat(float x, float in_min, float in_max, float out_min, float out_max) {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

#endif