/**************************************************************************
Copyright (C) 2000 - 2010 Novell, Inc.
All Rights Reserved.

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License along
with this program; if not, write to the Free Software Foundation, Inc.,
51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

**************************************************************************/


/*---------------------------------------------------------------------\
|								       |
|		       __   __	  ____ _____ ____		       |
|		       \ \ / /_ _/ ___|_   _|___ \		       |
|			\ V / _` \___ \ | |   __) |		       |
|			 | | (_| |___) || |  / __/		       |
|			 |_|\__,_|____/ |_| |_____|		       |
|								       |
|				core system			       |
|							 (C) SuSE GmbH |
\----------------------------------------------------------------------/

  File:		YBusyIndicator.h

  Author:	Thomas Goettlicher <tgoettlicher@suse.de>

/-*/

#ifndef YBusyIndicator_h
#define YBusyIndicator_h

#include "YWidget.h"

class YBusyIndicatorPrivate;


class YBusyIndicator : public YWidget
{
protected:
    /**
     * Constructor.
     **/
    YBusyIndicator( YWidget * 		parent,
		  const string &	label,
		  int			timeout = 1000,
		  bool 			alive = true );

public:
    /**
     * Destructor.
     **/
    virtual ~YBusyIndicator();
    
    /**
     * Returns a descriptive name of this widget class for logging,
     * debugging etc.
     **/
    virtual const char * widgetClass() const { return "YBusyIndicator"; }

    /**
     * Get the label (the caption above the progress bar).
     **/
    string label();

    /**
     * Set the label (the caption above the progress bar).
     *
     * Derived classes are free to reimplement this, but they should call this
     * base class method at the end of the overloaded function.
     **/
    virtual void setLabel( const string & label );

    /**
     * Return the current timeout in milliseconds.
     **/
    int timeout() const;

    /**
     * Set the timeout in milliseconds after that the widget shows 'stalled'
     * when no new tick is received.
     *
     * Derived classes should reimplement this, but they should call this
     * base class method at the end of the overloaded function.
     **/
    virtual void setTimeout( int newTimeout );

    /**
     * Return whether busy indicator is alive or in stalled stated.
     **/
    bool alive() const;


    /**
     * Send a keep alive message to prevent BusyIndicator from changing
     * to 'stalled' state. 
     *
     * Derived classes should reimplement this, but they should call this
     * base class method at the end of the overloaded function.
     **/
    virtual void setAlive( bool newAlive );


    /**
     * Set a property.
     * Reimplemented from YWidget.
     *
     * This function may throw YUIPropertyExceptions.
     *
     * This function returns 'true' if the value was successfully set and
     * 'false' if that value requires special handling (not in error cases:
     * those are covered by exceptions).
     **/
    virtual bool setProperty( const string & propertyName,
			      const YPropertyValue & val );

    /**
     * Get a property.
     * Reimplemented from YWidget.
     *
     * This method may throw YUIPropertyExceptions.
     **/
    virtual YPropertyValue getProperty( const string & propertyName );

    /**
     * Return this class's property set.
     * This also initializes the property upon the first call.
     *
     * Reimplemented from YWidget.
     **/
    virtual const YPropertySet & propertySet();


private:

    ImplPtr<YBusyIndicatorPrivate> priv;
};


#endif // YBusyIndicator_h
