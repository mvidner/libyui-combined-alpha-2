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

  File:	      YQSpacing.cc

  Author:     Stefan Hundhammer <sh@suse.de>

/-*/


#include "YQSpacing.h"


YQSpacing::YQSpacing( YWidget *		parent,
		      YUIDimension 	dim,
		      bool 		stretchable,
		      YLayoutSize_t 	layoutUnits )
    : QWidget( (QWidget *) parent->widgetRep() )
    , YSpacing( parent, dim, stretchable, layoutUnits )
{
    setWidgetRep( this );
}


YQSpacing::~YQSpacing()
{
    // NOP
}


void YQSpacing::setSize( int newWidth, int newHeight )
{
    resize( newWidth, newHeight );
}



#include "YQSpacing.moc"
