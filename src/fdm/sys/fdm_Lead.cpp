/****************************************************************************//*
 * Copyright (C) 2019 Marek M. Cel
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom
 * the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 ******************************************************************************/

#include <fdm/sys/fdm_Lead.h>

#include <math.h>

////////////////////////////////////////////////////////////////////////////////

using namespace fdm;

////////////////////////////////////////////////////////////////////////////////

Lead::Lead() :
    _tc( 1.0 ),
    _u ( 0.0 ),
    _y ( 0.0 )
{}

////////////////////////////////////////////////////////////////////////////////

Lead::Lead( double tc, double y ) :
    _tc ( tc ),
    _y ( y )
{}

////////////////////////////////////////////////////////////////////////////////

void Lead::setValue( double y )
{
    _y = y;
}

////////////////////////////////////////////////////////////////////////////////

void Lead::setTimeConstant( double tc )
{
    if ( tc > 0.0 )
    {
        _tc = tc;
    }
}

////////////////////////////////////////////////////////////////////////////////

void Lead::update( double u, double dt )
{
    if ( dt > 0.0 )
    {
        double du_dt = ( u - _u ) / dt;
        _y = _tc * du_dt + u;
        _u = u;
    }
}
