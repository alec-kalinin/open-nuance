/******************************************************************************
 * Open NUANCE:                                                               *
 *     NUmerical Algorithms for Noninvasive Cardiac Electrophysiology         *
 *                                                                            *
 * Authors:                                                                   *
 *     Alexander V. Kalinin <alec.kalinin@gmail.com>, 2012 -- 2014            *
 *                                                                            *
 * License:                                                                   *
 *     Redistribution and use of the source code with or without modification *
 *     are permitted for any scientific, research and educational purposes.   *
 ******************************************************************************/

#include "UTimer.h"

using namespace std;

UTimer::UTimer()
{
    QueryPerformanceFrequency(&m_freq);
}

UTimer::~UTimer()
{

}

void UTimer::start()
{
    QueryPerformanceCounter(&m_startTime);
}

void UTimer::stop()
{
    QueryPerformanceCounter(&m_endTime);

    m_elapsed.QuadPart = m_endTime.QuadPart - m_startTime.QuadPart;

}

double UTimer::ms() const
{
    return (double)(m_elapsed.QuadPart * 1000 / m_freq.QuadPart);
}
