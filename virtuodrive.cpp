#include "virtuodrive.h"
#include <math.h>
#include <iostream>
#include <cstdlib>
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
    in = std::min(std::max(in,(double)-1),.5);
    return in;
}

float virtuodrive::forSample(float in)
{
    in *= m_gain;
    in = (1+k) * in / (1+k * fabs(in));
    in = std::min(std::max(in,(float)-1),(float).5);
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

