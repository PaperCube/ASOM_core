#ifndef MATHUTIL_H
#define MATHUTIL_H

namespace mathutil
{
template <typename T>
T map(T value, T mapFromLower, T mapFromUpper, T mapToLower, T mapToUpper)
{
    T ratio = (value - mapFromLower) / (mapFromUpper - mapFromLower);
    return mapToLower + ratio * (mapToUpper - mapToLower);
}

template <typename T>
T mapWithinRange(T value, T mapFromLower, T mapFromUpper, T mapToLower, T mapToUpper)
{
    value = value < mapFromLower ? mapFromLower : (value > mapFromUpper ? mapFromUpper : value);
    return map(value, mapFromLower, mapFromUpper, mapToLower, mapToUpper);
}

template <typename T>
T maxOf(T v1, T v2, T v3)
{
    T &max = v1 > v2 ? v1 : v2;
    max = max > v3 ? max : v3;
    return max;
}

template <typename T>
T minOf(T v1, T v2, T v3)
{
    T &min = v1 < v2 ? v1 : v2;
    min = min < v3 ? min : v3;
    return min;
}

template <typename T>
T absOf(T x)
{
    return x > 0 ? x : -x;
}

bool inCircularRange(long, long, long, long);

bool inRangeInclusive(long, long, long);
}

#endif