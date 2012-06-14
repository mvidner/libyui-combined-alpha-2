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


/*-/

  File:	      YQContextMenu.cc

  Author:     Thomas Goettlicher <tgoettlicher@suse.de>

/-*/


#include <QMenu>
#include <qtimer.h>
#define YUILogComponent "qt-ui"
#include "YUILog.h"

#include "utf8.h"
#include "YQUI.h"
#include "YQContextMenu.h"
#include "YEvent.h"


YQContextMenu::YQContextMenu()
    : QObject ()
    , YContextMenu( )
    , _suppressCancelEvent(false )
{
     yuiWarning() << "YQContextMenu";

}

YQContextMenu::YQContextMenu( const QPoint position )
    : QObject ()
    , YContextMenu(  )
    , _position ( position )
{
    // NOP
}


YQContextMenu::~YQContextMenu()
{
    // NOP
}


void
YQContextMenu::rebuildMenuTree()
{
    QMenu * menu = new QMenu( 0 );
    YUI_CHECK_NEW( menu );
    menu->setProperty( "class", "ycontextmenu QMenu" );

    connect( menu,	SIGNAL( triggered         ( QAction * ) ),
	     this,	SLOT  ( menuEntryActivated( QAction * ) ) );

    connect( menu,	SIGNAL( aboutToHide      () ),
	     this,	SLOT  ( slotMenuHidden   () ) );
    //
    // Recursively add Qt menu items from the YMenuItems
    //

    rebuildMenuTree( menu, itemsBegin(), itemsEnd() );
    menu->popup( _position );
}


void
YQContextMenu::rebuildMenuTree( QMenu * parentMenu, YItemIterator begin, YItemIterator end )
{
    for ( YItemIterator it = begin; it != end; ++it )
    {
	YItem * item = *it;
	QPixmap icon;

	if ( item->hasIconName() )
	{
	    std::string iconName = iconFullPath( item );
	    icon = QPixmap( iconName.c_str() );

	    if ( icon.isNull() )
		yuiWarning() << "Can't load icon " << iconName << std::endl;
	}

	if ( item->hasChildren() )
	{
	    QMenu * subMenu;

	    if ( icon.isNull() )
		subMenu = parentMenu->addMenu( fromUTF8( item->label() ));
	    else
		subMenu = parentMenu->addMenu( QIcon( icon ), fromUTF8( item->label() ));

	    connect( subMenu,	SIGNAL( triggered         ( QAction * ) ),
		     this,	SLOT  ( menuEntryActivated( QAction * ) ) );

	    rebuildMenuTree( subMenu, item->childrenBegin(), item->childrenEnd() );
	}
	else // No children - leaf entry
	{
	    // item->index() is guaranteed to be unique within this YContextMenu's items,
	    // so it can easily be used as unique ID in all Q3PopupMenus that belong
	    // to this YQContextMenu.

            QAction *act;

	    if ( icon.isNull() )
		act = parentMenu->addAction( fromUTF8( item->label() ) );
	    else
		act = parentMenu->addAction( QIcon( icon ), fromUTF8( item->label() ) );

            _serials[act] = item->index();
	}
    }
}

void
YQContextMenu::slotMenuHidden()
{
	// dirty hack
	// see menuEntryActivated() for details
	QTimer::singleShot( 150, this, SLOT( slotReturnMenuHidden() ) );
}


void
YQContextMenu::slotReturnMenuHidden()
{
    if ( ! _suppressCancelEvent )
        YQUI::ui()->sendEvent( new YCancelEvent() );

    _suppressCancelEvent = false;
}


void
YQContextMenu::menuEntryActivated( QAction* action )
{
    int serialNo = -1;
    if ( _serials.contains( action ) )
        serialNo = _serials[action];

    // yuiDebug() << "Selected menu entry #" << menu_item_index << std::endl;
    _selectedItem = findMenuItem( serialNo );

    if ( _selectedItem )
    {
	/*
	 * Defer the real returnNow() until all popup related events have been
	 * processed. This took me some hours to figure out; obviously
	 * exit_loop() doesn't have any effect as long as there are still
	 * popups open. So be it - use a zero timer to perform the real
	 * returnNow() later.
	 */

	/*
	 * the 100 delay is a ugly dirty workaround
	 */
	_suppressCancelEvent = true;
	QTimer::singleShot( 100, this, SLOT( returnNow() ) );
    }
    else
    {
	yuiError() << "No menu item with serial no. " << serialNo << std::endl;
    }
}


void
YQContextMenu::returnNow()
{
    if ( _selectedItem )
    {
	YQUI::ui()->sendEvent( new YMenuEvent( _selectedItem ) );
	_selectedItem = 0;
    }
}


int YQContextMenu::preferredWidth()
{
        return 42;
}


int YQContextMenu::preferredHeight()
{
        return 42;
}


void
YQContextMenu::setSize( int newWidth, int newHeight )
{

}


#include "YQContextMenu.moc"
