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

  File:	      YQRadioButton.cc

  Author:     Stefan Hundhammer <sh@suse.de>

/-*/

#include <qradiobutton.h>
#include <QMouseEvent>
#include <QBoxLayout>

#define YUILogComponent "qt-ui"
#include "YUILog.h"

#include "utf8.h"
#include "YQUI.h"
#include "YQApplication.h"
#include "YEvent.h"
#include "YQRadioButton.h"
#include "YRadioButtonGroup.h"
#include "YQSignalBlocker.h"

using std::string;

#define SPACING 8

// +----+----------------------------------+----+
// |	|(o) RadioButtonlabel		   |	|
// +----+----------------------------------+----+
// <----> SPACING			   <---->



YQRadioButton::YQRadioButton( YWidget * 	parent,
			      const std::string & 	label,
			      bool 		checked )
    : QRadioButton( fromUTF8( label ), ( QWidget *) (parent->widgetRep() ) )
    , YRadioButton( parent, label )
{
    setWidgetRep( this );

    // QRadioButton uses its own logic by default to make sure that only one
    // button of a radio box is checked at any time, but this interferes with
    // YRadioButtonGroup. Let YRadioButtonGroup and YQRadioButton::changed()
    // handle this.
    setAutoExclusive( false );

    setChecked( checked );

    installEventFilter(this);

    connect ( this,     SIGNAL( toggled ( bool ) ),
	      this,	SLOT  ( changed ( bool ) ) );
}


void
YQRadioButton::setUseBoldFont( bool useBold )
{
    setFont( useBold ?
             YQUI::yqApp()->boldFont() :
             YQUI::yqApp()->currentFont() );

    YRadioButton::setUseBoldFont( useBold );
}


int YQRadioButton::preferredWidth()
{
    return sizeHint().width();
}


int YQRadioButton::preferredHeight()
{
    return sizeHint().height();
}


void YQRadioButton::setSize( int newWidth, int newHeight )
{
    resize( newWidth, newHeight );
}


bool YQRadioButton::value()
{
    return isChecked();
}


void YQRadioButton::setValue( bool newValue )
{
    YQSignalBlocker sigBlocker( this );

    // yuiDebug() << "Setting " << this << (newValue ? " on" : " off") << std::endl;
    setChecked( newValue );

    if ( newValue )
    {
	YRadioButtonGroup * group = buttonGroup();

	if ( group )
	    group->uncheckOtherButtons( this );
    }
}


void YQRadioButton::setLabel( const std::string & label )
{
    setText( fromUTF8( label ) );
    YRadioButton::setLabel( label );
}


void YQRadioButton::setEnabled( bool enabled )
{
    QRadioButton::setEnabled( enabled );
    YWidget::setEnabled( enabled );
}


bool YQRadioButton::setKeyboardFocus()
{
    setFocus();

    return true;
}


void YQRadioButton::changed( bool newState )
{
    if ( newState )
    {
	yuiDebug() << "User set " << this << ( newState ? " on" : " off" ) << std::endl;
	YRadioButtonGroup * group = buttonGroup();

	if ( group )
	    group->uncheckOtherButtons( this );

	if ( notify() )
	    YQUI::ui()->sendEvent( new YWidgetEvent( this, YEvent::ValueChanged ) );
    }
    else
    {
        // prevent that the user deselects all items
        setChecked( true );
    }
}


bool YQRadioButton::eventFilter( QObject * obj, QEvent * event )
{
    if ( event && event->type() == QEvent::MouseButtonRelease )
    {
        QMouseEvent * mouseEvent = dynamic_cast<QMouseEvent *> (event);

        if ( mouseEvent && mouseEvent->button() == Qt::RightButton )
        {
	    yuiMilestone() << "Right click on button detected" << std::endl;
	    YQUI::yqApp()->maybeLeftHandedUser();
        }
    }

    return QObject::eventFilter( obj, event );
}


#include "YQRadioButton.moc"
