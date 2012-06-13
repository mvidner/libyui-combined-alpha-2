/*
  |****************************************************************************
  |
  | Copyright (c) 2000 - 2012 Novell, Inc.
  | All Rights Reserved.
  |
  | This program is free software; you can redistribute it and/or
  | modify it under the terms of version 2 of the GNU General Public License as
  | published by the Free Software Foundation.
  |
  | This program is distributed in the hope that it will be useful,
  | but WITHOUT ANY WARRANTY; without even the implied warranty of
  | MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.   See the
  | GNU General Public License for more details.
  |
  | You should have received a copy of the GNU General Public License
  | along with this program; if not, contact Novell, Inc.
  |
  | To contact Novell about this file by physical or electronic mail,
  | you may find current contact information at www.novell.com
  |
  |****************************************************************************
*/



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
 ////                                        ***  Qt4 plugin  ***                                         ////
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

  File:	      YQIntField.h

  Author:     Stefan Hundhammer <sh@suse.de>

/-*/


#ifndef YQIntField_h
#define YQIntField_h

#include <qlabel.h>
#include <QFrame>

#include "YIntField.h"


class YQWidgetCaption;
class QSpinBox;


class YQIntField : public QFrame, public YIntField
{
    Q_OBJECT

public:

    /**
     * Constructor.
     **/
    YQIntField( YWidget *	parent,
		const std::string &	label,
		int 		minValue,
		int 		maxValue,
		int 		initialValue );

    /**
     * Destructor.
     **/
    virtual ~YQIntField();

    /**
     * Get the current value (the number entered by the user or set from the
     * outside) of this IntField.
     *
     * Implemented from YIntField.
     **/
    virtual int value();

protected:

    /**
     * Set the current value (the number entered by the user or set from the
     * outside) of this IntField. 'val' is guaranteed to be between minValue
     * and maxValue; no further checks are required.
     *
     * Implemented from YIntField.
     **/
    virtual void setValueInternal( int val );

public:

    /**
     * Set the label (the caption above the input field).
     *
     * Reimplemented from YIntField.
     **/
    virtual void setLabel( const std::string & label );

    /**
     * Sets the widget's enabled state.
     *
     * Inherited from YWidget.
     **/
    virtual void setEnabled( bool enabled );

    /**
     * Preferred width of the widget.
     *
     * Reimplemented from YWidget.
     **/
    virtual int preferredWidth();

    /**
     * Preferred height of the widget.
     *
     * Reimplemented from YWidget.
     **/
    virtual int preferredHeight();

    /**
     * Set the new size of the widget.
     *
     * Reimplemented from YWidget.
     **/
    virtual void setSize( int newWidth, int newHeight );

    /**
     * Accept the keyboard focus.
     *
     * Reimplemented from YWidget.
     **/
    virtual bool setKeyboardFocus();


signals:

    /**
     * Emitted when the value changes (regardless of the notify flag).
     **/
    void valueChanged( int newValue );


protected slots:

    /**
     * Slot for "value changed". This will send a ValueChanged event if
     * 'notify' is set.
     **/
    void valueChangedSlot( int newValue );


protected:

    YQWidgetCaption *	_caption;
    QSpinBox *		_qt_spinBox;
};


#endif // YQIntField_h
