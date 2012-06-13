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

  File:	      YQMultiLineEdit.cc

  Author:     Stefan Hundhammer <sh@suse.de>

/-*/


#include <QVBoxLayout>
#include <QTextEdit>
#include <qlabel.h>
#define YUILogComponent "qt-ui"
#include "YUILog.h"

using std::max;

#include "utf8.h"
#include "YQUI.h"
#include "YEvent.h"
#include "YQMultiLineEdit.h"
#include "YQSignalBlocker.h"
#include "YQWidgetCaption.h"


YQMultiLineEdit::YQMultiLineEdit( YWidget * parent, const std::string & label )
    : QFrame( (QWidget *) parent->widgetRep() )
    , YMultiLineEdit( parent, label )
{
    QVBoxLayout* layout = new QVBoxLayout( this );
    setLayout( layout );

    setWidgetRep( this );
    layout->setSpacing( YQWidgetSpacing );
    layout->setMargin ( YQWidgetMargin  );

    _caption = new YQWidgetCaption( this, label );
    YUI_CHECK_NEW( _caption );
    layout->addWidget( _caption );

    _qt_textEdit = new QTextEdit( this );
    YUI_CHECK_NEW( _qt_textEdit );
    layout->addWidget( _qt_textEdit );

    _qt_textEdit->setAcceptRichText( false );
    _qt_textEdit->setSizePolicy( QSizePolicy( QSizePolicy::Expanding, QSizePolicy::Expanding ) );

    _caption->setBuddy( _qt_textEdit );

    connect( _qt_textEdit,	SIGNAL( textChanged( void ) ),
	     this, 		SLOT  ( changed    ( void ) ) );
}


YQMultiLineEdit::~YQMultiLineEdit()
{
    // NOP
}


string YQMultiLineEdit::value()
{
    return toUTF8( _qt_textEdit->document()->toPlainText() );
}


void YQMultiLineEdit::setValue( const std::string & text )
{
    YQSignalBlocker sigBlocker( _qt_textEdit );

    _qt_textEdit->setText( fromUTF8( text ) );
}


void YQMultiLineEdit::setLabel( const std::string & label )
{
    _caption->setText( label );
    YMultiLineEdit::setLabel( label );
}


void YQMultiLineEdit::setInputMaxLength( int newMaxLength )
{
    YMultiLineEdit::setInputMaxLength( newMaxLength );

    QString text = _qt_textEdit->document()->toPlainText();

    if ( (int) text.length() > inputMaxLength() )
    {
	text.truncate( inputMaxLength() );
	_qt_textEdit->setText(text);
    }
}


void YQMultiLineEdit::enforceMaxInputLength()
{
    if ( inputMaxLength() >= 0 && _qt_textEdit->toPlainText().length() > inputMaxLength() )
        _qt_textEdit->undo();
}


void YQMultiLineEdit::changed()
{
    enforceMaxInputLength();

    if ( notify() )
	YQUI::ui()->sendEvent( new YWidgetEvent( this, YEvent::ValueChanged ) );
}


void YQMultiLineEdit::setEnabled( bool enabled )
{
    _caption->setEnabled( enabled );
    _qt_textEdit->setEnabled( enabled );
    YWidget::setEnabled( enabled );
}


int YQMultiLineEdit::preferredWidth()
{
    return max( 30, sizeHint().width() );
}


int YQMultiLineEdit::preferredHeight()
{
    int hintHeight 	 = defaultVisibleLines() * _qt_textEdit->fontMetrics().lineSpacing();
    hintHeight		+= _qt_textEdit->frameWidth() * 2 + YQWidgetMargin * 2;

    if ( !_caption->isHidden() )
	hintHeight += _caption->sizeHint().height() + YQWidgetSpacing;

    return max( 10, hintHeight );
}


void YQMultiLineEdit::setSize( int newWidth, int newHeight )
{
    resize( newWidth, newHeight );
}


bool YQMultiLineEdit::setKeyboardFocus()
{
    _qt_textEdit->setFocus();

    return true;
}


#include "YQMultiLineEdit.moc"

