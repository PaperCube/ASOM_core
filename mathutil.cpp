#include "mathutil.h"

namespace mathutil
{
bool inCircularRange(long value, long leftSide, long rightSide, long cycle)
{
    long rangeLength = rightSide - leftSide;
    leftSide = remainderToPositive(leftSide, cycle);
    rightSide = leftSide + rangeLength;

    long valueRemaindered = remainderToPositive(value, cycle);

    return inRangeInclusive(valueRemaindered, leftSide, rightSide) ||
           inRangeInclusive(valueRemaindered + cycle, leftSide, rightSide);
}

bool inRangeInclusive(long v, const long l, const long r)
{
    return (v >= l) && (v <= r);
}

long remainderToPositive(long value, long remainder)
{
    long offset = value % remainder;
    return offset < 0 ? offset + remainder : offset;
}
}