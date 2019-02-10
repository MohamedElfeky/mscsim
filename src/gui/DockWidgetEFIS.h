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
#ifndef DOCKWIDGETEFIS_H
#define DOCKWIDGETEFIS_H

////////////////////////////////////////////////////////////////////////////////

#include <QDockWidget>

#include "GraphicsEADI.h"
#include "GraphicsEHSI.h"

////////////////////////////////////////////////////////////////////////////////

namespace Ui
{
    class DockWidgetEFIS;
}

////////////////////////////////////////////////////////////////////////////////

/**
 * @brief EFIS dock widget class.
 */
class DockWidgetEFIS : public QDockWidget
{
    Q_OBJECT

public:

    /** Constructor. */
    explicit DockWidgetEFIS( QWidget *parent = 0 );

    /** Destructor. */
    virtual ~DockWidgetEFIS();

    /** @param roll angle [deg] */
    inline void setRoll( float roll )
    {
        m_graphicsEADI->setRoll( roll );
    }

    /** @param pitch angle [deg] */
    inline void setPitch( float pitch )
    {
        m_graphicsEADI->setPitch( pitch );
    }

    /** @param normalized slip or skid (range from -1.0 to 1.0) */
    inline void setSlipSkid( float slipSkid )
    {
        m_graphicsEADI->setSlipSkid( slipSkid );
    }

    /**
     * @param normalized turn rate (range from -1.0 to 1.0),
     * hash marks positions are set to be -0.5 and 0.5
     */
    inline void setTurnRate( float turnRate )
    {
        m_graphicsEADI->setTurnRate( turnRate );
    }

    /**
     * @param dotH [-] normalized horizontal deviation position (range from -1.0 to 1.0)
     * @param dotV [-] normalized vertical deviation position (range from -1.0 to 1.0)
     * @param visibleH deviation horizontal visibility
     * @param visibleV deviation vertical visibility */
    inline void setDots( float dotH, float dotV,
                         bool visibleH, bool visibleV )
    {
        m_graphicsEADI->setDots( dotH, dotV, visibleH, visibleV );
    }

    /**
     * @param FD roll angle [deg]
     * @param FD pitch angle [deg]
     * @param FD visibility */
    inline void setFD( float roll, float pitch, bool visible = true )
    {
        m_graphicsEADI->setFD( roll, pitch, visible );
    }

    /** @param stall flag */
    inline void setStall( bool stall )
    {
        m_graphicsEADI->setStall( stall );
    }

    /** @param altitude (dimensionless numeric value) */
    inline void setAltitude( float altitude )
    {
        m_graphicsEADI->setAltitude( altitude );
    }

    /** @param airspeed (dimensionless numeric value) */
    inline void setAirspeed( float airspeed )
    {
        m_graphicsEADI->setAirspeed( airspeed );
    }

    /** @param Mach number */
    inline void setMachNo( float machNo )
    {
        m_graphicsEADI->setMachNo( machNo );
    }

    /** @param heading [deg] */
    inline void setHeading( float heading )
    {
        m_graphicsEADI->setHeading( heading );
        m_graphicsEHSI->setHeading( heading );
    }

    /** @param climb rate (dimensionless numeric value)  */
    inline void setClimbRate( float climbRate )
    {
        m_graphicsEADI->setClimbRate( climbRate );
    }

    /**
     * setDistance
     * @param distance [nmi] distance
     * @param visible
     */
    inline void setDistance( float distance, bool visible )
    {
        m_graphicsEHSI->setDistance( distance, visible );
    }

    /**
     * setBearing
     * @param bearing [deg] bearing
     * @param visible
     */
    inline void setBearing( float bearing, bool visible )
    {
        m_graphicsEHSI->setBearing( bearing, visible );
    }

    /**
     * setDeviation
     * @param deviation [-]
     * @param visible
     */
    inline void setDeviation( float deviation, bool visible )
    {
        m_graphicsEHSI->setDeviation( deviation, visible );
    }

private:

    Ui::DockWidgetEFIS *m_ui;

    GraphicsEADI *m_graphicsEADI;
    GraphicsEHSI *m_graphicsEHSI;
};

////////////////////////////////////////////////////////////////////////////////

#endif // DOCKWIDGETEFIS_H