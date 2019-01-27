/**
 * @file
 * @author  Mamadou Babaei <info@babaei.net>
 * @version 0.1.0
 *
 * @section LICENSE
 *
 * (The MIT License)
 *
 * Copyright (c) 2018 - 2019 Mamadou Babaei
 * Copyright (c) 2018 - 2019 Seditious Games Studio
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * @section DESCRIPTION
 *
 * A generic stopwatch implementation.
 */


#pragma once

#include <chrono>

template<typename CLOCK_TYPE = std::chrono::high_resolution_clock,
         typename UNIT_TYPE = std::chrono::microseconds,
         typename DURATION_TYPE = double>
class GStopwatch
{
private:
    typedef std::chrono::time_point<CLOCK_TYPE> TimePoint;

private:
    TimePoint StartPoint;
    TimePoint EndPoint;

public:
    GStopwatch()
    {
        Start();
    }

    virtual ~GStopwatch() = default;

public:
    void Start()
    {
        StartPoint = CLOCK_TYPE::now();
        EndPoint = StartPoint;
    }

    DURATION_TYPE Stop()
    {
        EndPoint = CLOCK_TYPE::now();
        return Elapsed();
    }

    DURATION_TYPE Elapsed()
    {
        auto Delta = std::chrono::duration_cast<UNIT_TYPE>(EndPoint - StartPoint);
        return Delta.count();
    }
};
