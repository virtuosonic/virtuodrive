#include "virtuodrive.h"
#include "VirtuosonicHelperFunctions.h"
#include <math.h>
#define cDenorm pow(10,-30)

virtuodrive::virtuodrive()
{
}

virtuodrive::~virtuodrive()
{
}

double virtuodrive::forSample(double in)
{
    in = (in) * m_gain;
    in = (1+k) * in / (1+k * fabs(in));
    in = Min(Max(in,-1),.5);
    return in;
}

float virtuodrive::forSample(float in)
{
    in *= m_gain;
    in = (1+k) * in / (1+k * fabs(in));
    in = Min(Max(in,-1),.5);
    return in;
}

void virtuodrive::SetAmount(double amount)
{
    m_amount=amount;
    k = 2 * amount / (1 - amount);
}

void virtuodrive::SetGain(double gain)
{
    m_gain=gain;
}

