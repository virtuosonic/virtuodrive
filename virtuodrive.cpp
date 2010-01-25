#include "virtuodrive.h"
#include <math.h>
#include <iostream>
#define cDenorm pow(10,-30)


double Min(double x,double y)
{
    if (x < y)
    	return x;
    else
    	return y;
}

double Max(double x,double y)
{
    if (x > y)
    	return x;
    else
    	return y;
}

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

