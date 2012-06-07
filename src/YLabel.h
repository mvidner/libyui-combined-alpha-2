/*************************************************************************************************************

 Copyright (C) 2000 - 2010 Novell, Inc.   All Rights Reserved.

 This program is free software; you can redistribute it and/or modify it under the terms of the GNU General
 Public License as published by the Free Software Foundation; either version 2 of the License, or (at your
 option) any later version.

 This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the
 implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 for more details.

 You should have received a copy of the GNU General Public License along with this program; if not, write to
 the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

*************************************************************************************************************/



 /////////////////////////////////////////////////////////////////////////////////////////////////////////////
 /////////////////////////////////////////////////////////////////////////////////////////////////////////////
 ////                                                                                                     ////
 ////                                                                                                     ////
 ////                                                                                                     ////
 ////   __/\\\\\\_____________/\\\__________/\\\________/\\\___/\\\________/\\\___/\\\\\\\\\\\_           ////
 ////    _\////\\\____________\/\\\_________\///\\\____/\\\/___\/\\\_______\/\\\__\/////\\\///__          ////
 ////     ____\/\\\______/\\\__\/\\\___________\///\\\/\\\/_____\/\\\_______\/\\\______\/\\\_____         ////
 ////      ____\/\\\_____\///___\/\\\_____________\///\\\/_______\/\\\_______\/\\\______\/\\\_____        ////
 ////       ____\/\\\______/\\\__\/\\\\\\\\\_________\/\\\________\/\\\_______\/\\\______\/\\\_____       ////
 ////        ____\/\\\_____\/\\\__\/\\\////\\\________\/\\\________\/\\\_______\/\\\______\/\\\_____      ////
 ////         ____\/\\\_____\/\\\__\/\\\__\/\\\________\/\\\________\//\\\______/\\\_______\/\\\_____     ////
 ////          __/\\\\\\\\\__\/\\\__\/\\\\\\\\\_________\/\\\_________\///\\\\\\\\\/_____/\\\\\\\\\\\_    ////
 ////           _\/////////___\///___\/////////__________\///____________\/////////______\///////////__   ////
 ////                                                                                                     ////
 ////                                                                                                     ////
 ////                 widget abstraction library providing Qt, GTK and ncurses frontends                  ////
 ////                                                                                                     ////
 ////                                   3 UIs for the price of one code                                   ////
 ////                                                                                                     ////
 ////                                       ***  core library  ***                                        ////
 ////                                                                                                     ////
 ////                                                                                                     ////
 ////                                                                                                     ////
 ////                                                                              (C) SUSE Linux GmbH    ////
 ////                                                                                                     ////
 ////                                                              libYUI-AsciiArt (C) 2012 Björn Esser   ////
 ////                                                                                                     ////
 /////////////////////////////////////////////////////////////////////////////////////////////////////////////
 /////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*-/

  File:		YLabel.h

  Author:	Stefan Hundhammer <sh@suse.de>

/-*/

#ifndef YLabel_h
#define YLabel_h

#include "YWidget.h"
#include <string>
#include "ImplPtr.h"

using std::string;

class YLabelPrivate;

/**
 * Implementation of the Label, Heading and OutputField widgets
 **/
class YLabel : public YWidget
{
public:

    /**
     * Constructor.
     *
     * 'isHeading' indicates if this should be displayed as a Heading widget,
     * i.e. with a bold and/or larger font.
     * This cannot be changed after creating the widget.
     *
     * 'isOutputField' indicates if this should be displayed as an OutputField
     * widget, i.e. similar to an InputField the user can't change.
     * This cannot be changed after creating the widget.
     **/
    YLabel( YWidget * 		parent,
	    const string &	text,
	    bool 		isHeading	= false,
	    bool 		isOutputField	= false );

    /**
     * Destructor.
     **/
    virtual ~YLabel();

    /**
     * Returns a descriptive name of this widget class for logging,
     * debugging etc.
     *
     * Reimplemented from YWidget.
     **/
    virtual const char * widgetClass() const;

    /**
     * Return the text the widget displays.
     **/
    string text() const;

    /**
     * Aliases for text().
     **/
    string value() const { return text(); }
    string label() const { return text(); }

    /**
     * Set the text the widget displays.
     *
     * Derived classes should overwrite this, but call this base class function
     * in the overwritten function.
     **/
    virtual void setText( const string & newText );

    /**
     * Aliases for setText().
     **/
    void setValue( const string & newValue ) { setText( newValue ); }
    void setLabel( const string & newLabel ) { setText( newLabel ); }

    /**
     * Return 'true' if this is a Heading widget, i.e., it should display its
     * text in a bold and/or larger font.
     *
     * This cannot be changed after creating the widget.
     **/
    bool isHeading() const;

    /**
     * Return 'true' if this is an OutputField widget, i.e., it should display
     * its text similar to an InputField the user can't change.
     *
     * This cannot be changed after creating the widget.
     **/
    bool isOutputField() const;

    /**
     * Return 'true' if a bold font should be used.
     **/
    bool useBoldFont() const;

    /**
     * Switch bold font on or off.
     *
     * Derived classes should overwrite this, but call this base class function
     * in the overwritten function.
     **/
    virtual void setUseBoldFont( bool bold = true );

    /**
     * Set a property.
     * Reimplemented from YWidget.
     *
     * This method may throw exceptions, for example
     *   - if there is no property with that name
     *   - if the expected type and the type mismatch
     *   - if the value is out of range
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
     * This method may throw exceptions, for example
     *   - if there is no property with that name
     **/
    virtual YPropertyValue getProperty( const std::string & propertyName );

    /**
     * Return this class's property set.
     * This also initializes the property set upon the first call.
     *
     * Reimplemented from YWidget.
     **/
    virtual const YPropertySet & propertySet();

    /**
     * Returns a descriptive label of this widget instance for debugging.
     *
     * Reimplemented from YWidget since a YLabel doesn't have a shortcut
     * property.
     **/
    virtual string debugLabel() const;

private:

    ImplPtr<YLabelPrivate> priv;
};


typedef	YLabel	YHeading;
typedef	YLabel	YOutputField;


#endif // YLabel_h