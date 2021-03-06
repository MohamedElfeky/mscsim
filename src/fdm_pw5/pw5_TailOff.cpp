﻿/****************************************************************************//*
 * Copyright (C) 2020 Marek M. Cel
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

#include <fdm_pw5/pw5_TailOff.h>

#include <fdm/main/fdm_Aerodynamics.h>
#include <fdm/xml/fdm_XmlUtils.h>

////////////////////////////////////////////////////////////////////////////////

using namespace fdm;

////////////////////////////////////////////////////////////////////////////////

PW5_TailOff::PW5_TailOff() :
    _ailerons  ( 0.0 ),
    _airbrakes ( 0.0 ),

    _dcl_dailerons ( 0.0 ),

    _dcx_dairbrake ( 0.0 ),
    _dcz_dairbrake ( 0.0 ),
    _dcm_dairbrake ( 0.0 )
{}

////////////////////////////////////////////////////////////////////////////////

PW5_TailOff::~PW5_TailOff() {}

////////////////////////////////////////////////////////////////////////////////

void PW5_TailOff::readData( XmlNode &dataNode )
{
    //////////////////////////////
    TailOff::readData( dataNode );
    //////////////////////////////

    if ( dataNode.isValid() )
    {
        int result = FDM_SUCCESS;

        if ( result == FDM_SUCCESS ) result = XmlUtils::read( dataNode, _dcl_dailerons, "dcl_dailerons" );

        if ( result == FDM_SUCCESS ) result = XmlUtils::read( dataNode, _dcx_dairbrake, "dcx_dairbrake" );
        if ( result == FDM_SUCCESS ) result = XmlUtils::read( dataNode, _dcz_dairbrake, "dcz_dairbrake" );
        if ( result == FDM_SUCCESS ) result = XmlUtils::read( dataNode, _dcm_dairbrake, "dcm_dairbrake" );

        if ( result != FDM_SUCCESS ) XmlUtils::throwError( __FILE__, __LINE__, dataNode );
    }
    else
    {
        XmlUtils::throwError( __FILE__, __LINE__, dataNode );
    }
}

////////////////////////////////////////////////////////////////////////////////

void PW5_TailOff::computeForceAndMoment( const Vector3 &vel_air_bas,
                                         const Vector3 &omg_air_bas,
                                         double airDensity,
                                         double ailerons,
                                         double airbrakes )
{
    _ailerons  = ailerons;
    _airbrakes = airbrakes;

    ///////////////////////////////////////////////////////////////////////
    TailOff::computeForceAndMoment( vel_air_bas, omg_air_bas, airDensity );
    ///////////////////////////////////////////////////////////////////////
}

////////////////////////////////////////////////////////////////////////////////

void PW5_TailOff::update( const Vector3 &vel_air_bas, const Vector3 &omg_air_bas )
{
    ////////////////////////////////////////////
    TailOff::update( vel_air_bas, omg_air_bas );
    ////////////////////////////////////////////

    Table1 cz_total = _cz;

    _aoa_critical_neg = cz_total.getKeyOfValueMin();
    _aoa_critical_pos = cz_total.getKeyOfValueMax();
}

////////////////////////////////////////////////////////////////////////////////

double PW5_TailOff::getCx( double angleOfAttack ) const
{
    return TailOff::getCx( angleOfAttack )
            + _airbrakes * _dcx_dairbrake;
}

////////////////////////////////////////////////////////////////////////////////

double PW5_TailOff::getCy( double sideslipAngle ) const
{
    return TailOff::getCy( sideslipAngle );
}

////////////////////////////////////////////////////////////////////////////////

double PW5_TailOff::getCz( double angleOfAttack ) const
{
    return TailOff::getCz( angleOfAttack )
            + _airbrakes * _dcz_dairbrake;
}

////////////////////////////////////////////////////////////////////////////////

double PW5_TailOff::getCl( double sideslipAngle ) const
{
    return TailOff::getCl( sideslipAngle ) + _ailerons * _dcl_dailerons;
}

////////////////////////////////////////////////////////////////////////////////

double PW5_TailOff::getCm( double angleOfAttack ) const
{
    return TailOff::getCm( angleOfAttack )
            + _airbrakes * _dcm_dairbrake;
}

////////////////////////////////////////////////////////////////////////////////

double PW5_TailOff::getCn( double sideslipAngle ) const
{
    return TailOff::getCn( sideslipAngle );
}
