/*---------------------------------------------------------------------\
|                                                                      |
|                      __   __    ____ _____ ____                      |
|                      \ \ / /_ _/ ___|_   _|___ \                     |
|                       \ V / _` \___ \ | |   __) |                    |
|                        | | (_| |___) || |  / __/                     |
|                        |_|\__,_|____/ |_| |_____|                    |
|                                                                      |
|                               core system                            |
|                                                        (C) SuSE GmbH |
\----------------------------------------------------------------------/

   File:       NCtypes.cc

   Author:     Michael Andres <ma@suse.de>
   Maintainer: Michael Andres <ma@suse.de>

/-*/

#include "Y2Log.h"
#include "NCtypes.h"

/******************************************************************
**
**
**	FUNCTION NAME : operator<<
**	FUNCTION TYPE : ostream &
**
**	DESCRIPTION :
*/
ostream & operator<<( ostream & str, NC::ADJUST obj )
{
#define PRT(a) case NC::a: return str << #a
  switch ( obj ) {
    PRT( CENTER );
    PRT( TOP );
    PRT( BOTTOM );
    PRT( LEFT );
    PRT( RIGHT );
    PRT( TOPLEFT );
    PRT( TOPRIGHT );
    PRT( BOTTOMLEFT );
    PRT( BOTTOMRIGHT );
  }
  return str << "NC::ADJUST";
#undef PRT
}

/******************************************************************
**
**
**	FUNCTION NAME : operator<<
**	FUNCTION TYPE : ostream &
**
**	DESCRIPTION :
*/
ostream & operator<<( ostream & str, NC::WState obj )
{
#define PRT(a) case NC::a: return str << #a
  switch ( obj ) {
    PRT( WSdumb );
    PRT( WSnormal );
    PRT( WSactive );
    PRT( WSdisabeled );
  }
  return str << "NC::WState";
#undef PRT
}

