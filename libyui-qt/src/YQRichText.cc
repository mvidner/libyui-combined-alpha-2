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

  File:	      YQRichText.cc

  Author:     Stefan Hundhammer <sh@suse.de>

/-*/

#define YUILogComponent "qt-ui"
#include "YUILog.h"

#include <QColorGroup>
#include <QScrollBar>
#include <QRegExp>
#include <QDebug>
#include <QKeyEvent>
#include <QVBoxLayout>

#include "YApplication.h"
#include "YEvent.h"
#include "utf8.h"
#include "QY2Styler.h"
#include "YQUI.h"
#include "YQDialog.h"
#include "YQRichText.h"

static const char *colors[] = { "red", "blue", "green", 0};

YQRichText::YQRichText( YWidget * parent, const string & text, bool plainTextMode )
    : QFrame( (QWidget *) parent->widgetRep() )
    , YRichText( parent, text, plainTextMode )
    , _colors_specified( 0 )
{
    QVBoxLayout* layout = new QVBoxLayout( this );
    layout->setSpacing( 0 );
    setLayout( layout );

    setWidgetRep( this );

    layout->setMargin( YQWidgetMargin );

    _textBrowser = new YQTextBrowser( this );
    YUI_CHECK_NEW( _textBrowser );
    layout->addWidget( _textBrowser );

    _textBrowser->installEventFilter( this );

    if ( plainTextMode )
    {
        _textBrowser->setWordWrapMode( QTextOption::NoWrap );
    }
    else
    {
        QString style = "\n" + QY2Styler::styler()->textStyle();
        size_t ccolors = sizeof( colors ) / sizeof( char* ) - 1;
        _colors_specified = new bool[ccolors];
        for ( size_t i = 0; i < ccolors; ++i )
        {
            _colors_specified[i] = false;
            char buffer[20];
            sprintf( buffer, "\n.%s ", colors[i] );
            if ( style.contains( buffer ) )
                _colors_specified[i] = true;
        }
        _textBrowser->document()->setDefaultStyleSheet( style );
    }

    setValue( text );

    // Propagate clicks on hyperlinks

    connect( _textBrowser, SIGNAL( anchorClicked( const QUrl & ) ),
	     this,	   SLOT  ( linkClicked  ( const QUrl & ) ) );
}


YQRichText::~YQRichText()
{
    // NOP
}


void YQRichText::setValue( const string & newText )
{
    if ( _textBrowser->horizontalScrollBar() )
	_textBrowser->horizontalScrollBar()->setValue(0);

    if ( ! autoScrollDown() && _textBrowser->verticalScrollBar() )
	_textBrowser->verticalScrollBar()->setValue(0);

    QString text = fromUTF8( newText );

    if ( ! plainTextMode() )
    {
        for ( int counter = 0; colors[counter]; counter++ )
        {
            if ( !_colors_specified[counter] ) continue;
            text.replace( QString( "color=%1" ).arg( colors[counter] ), QString( "class=\"%1\"" ).arg( colors[counter] ) );
            text.replace( QString( "color=\"%1\"" ).arg( colors[counter] ), QString( "class=\"%1\"" ).arg( colors[counter] ));
        }
        text.replace( "&product;", fromUTF8( YUI::app()->productName() ) );
        _textBrowser->setHtml( text );
    }
    else
    {
          _textBrowser->setPlainText( text );
    }
    YRichText::setValue( newText );

    if ( autoScrollDown() && _textBrowser->verticalScrollBar() )
	_textBrowser->verticalScrollBar()->setValue( _textBrowser->verticalScrollBar()->maximum() );
}


void YQRichText::setPlainTextMode( bool newPlainTextMode )
{
    YRichText::setPlainTextMode( newPlainTextMode );

    if ( plainTextMode() )
    {
      _textBrowser->setWordWrapMode( QTextOption::NoWrap );
    }
}


void YQRichText::setAutoScrollDown( bool newAutoScrollDown )
{
    YRichText::setAutoScrollDown( newAutoScrollDown );

    if ( autoScrollDown() && _textBrowser->verticalScrollBar() )
	_textBrowser->verticalScrollBar()->setValue( _textBrowser->verticalScrollBar()->maximum() );
}


void YQRichText::linkClicked( const QUrl & url )
{
    // yuiDebug() << "Selected hyperlink \"" << url.toString() << "\" << endl;
    YQUI::ui()->sendEvent( new YMenuEvent( url.toString().toUtf8()) );
}


bool YQRichText::eventFilter( QObject * obj, QEvent * ev )
{
    if ( ev->type() == QEvent::KeyPress )
    {
	QKeyEvent * event = ( QKeyEvent * ) ev;

	if ( ( event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter ) &&
	     ( event->modifiers() & Qt::NoModifier || event->modifiers() & Qt::KeypadModifier ) &&
	     ! haveHyperLinks() )
	{
	    YQDialog * dia = (YQDialog *) findDialog();

	    if ( dia )
	    {
		( void ) dia->activateDefaultButton();
		return true;
	    }
	}
    }

    return QWidget::eventFilter( obj, ev );
}


bool YQRichText::haveHyperLinks()
{
    if ( plainTextMode() )
	return false;

    return ( _textBrowser->document()->toPlainText().contains( QRegExp( "<a\\s+href\\s*=", Qt::CaseInsensitive ) ) > 0 );
}


int YQRichText::preferredWidth()
{
    return shrinkable() ? 10 : 100;
}


int YQRichText::preferredHeight()
{
    return shrinkable() ? 10 : 100;
}


void YQRichText::setSize( int newWidth, int newHeight )
{
    resize( newWidth, newHeight );
}


void YQRichText::setEnabled( bool enabled )
{
    _textBrowser->setEnabled( enabled );
    YWidget::setEnabled( enabled );
}


bool YQRichText::setKeyboardFocus()
{
    _textBrowser->setFocus();

    return true;
}



#include "YQRichText.moc"