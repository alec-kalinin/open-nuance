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

#ifndef UTIMER_H
#define UTIMER_H

#include <windows.h>

/*!
 * User timer for benchmark puproses
 */
class UTimer
{
// Methods
public:
    UTimer();
    ~UTimer();

    void start();
    void stop();
    double ms() const;

// Data members
private:
    LARGE_INTEGER m_startTime, m_endTime, m_elapsed, m_freq;
};



#endif // UTIMER_H
