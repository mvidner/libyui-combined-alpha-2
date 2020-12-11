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

  File:	      YQLayoutBox.h

  Author:     Stefan Hundhammer <sh@suse.de>

/-*/


#ifndef YQLayoutBox_h
#define YQLayoutBox_h

#include <qwidget.h>

#include "YLayoutBox.h"


class YQLayoutBox : public QWidget, public YLayoutBox
{
    Q_OBJECT

public:

    /**
     * Constructor.
     *
     * Creates a VBox for dim == YD_VERT or a HBox for YD_HORIZ.
     **/
    YQLayoutBox( YWidget * parent, YUIDimension dim );

    /**
     * Destructor.
     **/
    virtual ~YQLayoutBox();

    /**
     * Set enabled/disabled state.
     *
     * Reimplemented from YWidget.
     **/
    virtual void setEnabled( bool enabled );

    /**
     * Set the new size of the widget.
     *
     * Reimplemented from YWidget.
     **/
    virtual void setSize( int newWidth, int newHeight );

    /**
     * Move a child widget to a new position.
     *
     * Reimplemented from YLayoutBox.
     **/
    virtual void moveChild( YWidget * child, int newX, int newY );
};


typedef YQLayoutBox	YQVBox;
typedef YQLayoutBox	YQHBox;


#endif // YQLayoutBox_h
