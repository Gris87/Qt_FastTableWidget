#include "optimallist.h"

OptimalListSharedData::OptimalListSharedData()
{
    mBuffer=0;
    mBegin=0;
    mCount=0;
    mCapacity=0;
    mReserved=0;
    mReferences=1;
}
