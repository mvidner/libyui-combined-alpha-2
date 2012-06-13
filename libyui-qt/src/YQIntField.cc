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

  File:	      YQIntField.cc

  Author:     Stefan Hundhammer <sh@suse.de>

/-*/


#include <qspinbox.h>

#define YUILogComponent "qt-ui"
#include "YUILog.h"

#include "utf8.h"
#include "YQUI.h"
#include "YEvent.h"
#include "YQIntField.h"
#include "YQSignalBlocker.h"
#include "YQWidgetCaption.h"
#include <QVBoxLayout>

YQIntField::YQIntField( YWidget *	parent,
			const std::string &	label,
			int 		minValue,
			int 		maxValue,
			int 		initialValue )
    : QFrame( (QWidget *) parent->widgetRep() )
    , YIntField( parent, label, minValue, maxValue )
{
    QVBoxLayout* layout = new QVBoxLayout( this );
    setLayout( layout );

    setWidgetRep( this );

    layout->setSpacing( YQWidgetSpacing );
    layout->setMargin( YQWidgetMargin );

    _caption    = new YQWidgetCaption( this, label );
    YUI_CHECK_NEW( _caption );
    layout->addWidget( _caption );

    _qt_spinBox = new QSpinBox(this);
    _qt_spinBox->setMinimum(minValue);
    _qt_spinBox->setMaximum(maxValue);
    _qt_spinBox->setSingleStep(1);

    YUI_CHECK_NEW( _qt_spinBox );
    layout->addWidget( _qt_spinBox );

    _qt_spinBox->setValue( initialValue );

    _caption->setBuddy( _qt_spinBox );

    setValue( initialValue );

    connect( _qt_spinBox, SIGNAL( valueChanged    ( int ) ),
	     this,  	  SLOT  ( valueChangedSlot( int ) ) );
}


YQIntField::~YQIntField()
{
    // NOP
}


int
YQIntField::value()
{
    return _qt_spinBox->value();
}


void
YQIntField::setValueInternal( int newValue )
{
    YQSignalBlocker sigBlocker( _qt_spinBox );
    _qt_spinBox->setValue( newValue );
}


void
YQIntField::valueChangedSlot( int newValue )
{
    if ( notify() )
	YQUI::ui()->sendEvent( new YWidgetEvent( this, YEvent::ValueChanged ) );
    emit valueChanged( newValue );
}


void
YQIntField::setLabel( const std::string & newLabel )
{
    YIntField::setLabel( newLabel );
    _caption->setText( newLabel );
}


void
YQIntField::setEnabled( bool enabled )
{
    _caption->setEnabled  ( enabled );
    _qt_spinBox->setEnabled( enabled );
    YWidget::setEnabled( enabled );
}


int
YQIntField::preferredWidth()
{
    return sizeHint().width();
}


int
YQIntField::preferredHeight()
{
    return sizeHint().height();
}


void
YQIntField::setSize( int newWidth, int newHeight )
{
    resize( newWidth, newHeight );
}


bool
YQIntField::setKeyboardFocus()
{
    _qt_spinBox->setFocus();

    return true;
}


#include "YQIntField.moc"
