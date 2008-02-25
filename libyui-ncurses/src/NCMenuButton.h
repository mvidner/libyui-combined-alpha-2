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

   File:       NCMenuButton.h

   Author:     Michael Andres <ma@suse.de>
   Maintainer: Michael Andres <ma@suse.de>

/-*/
#ifndef NCMenuButton_h
#define NCMenuButton_h

#include <iosfwd>

#include "YMenuButton.h"
#include "NCWidget.h"

class NCMenuButton;

///////////////////////////////////////////////////////////////////
//
//	CLASS NAME : NCMenuButton
//
//	DESCRIPTION :
//
class NCMenuButton : public YMenuButton, public NCWidget {

  friend std::ostream & operator<<( std::ostream & STREAM, const NCMenuButton & OBJ );

  NCMenuButton & operator=( const NCMenuButton & );
  NCMenuButton            ( const NCMenuButton & );

  private:

    NClabel label;

  protected:

    virtual const char * location() const { return "NCMenuButton"; }

    virtual void wRedraw();

    NCursesEvent postMenu();

  public:

    NCMenuButton( YWidget * parent,
		  string label );
    virtual ~NCMenuButton();

    virtual int preferredWidth();
    virtual int preferredHeight();

    virtual void rebuildMenuTree();
    
    /**
     * Set the new size of the widget.
     *
     * Reimplemented from YWidget.
     **/
    virtual void setSize( int newWidth, int newHeight );

    virtual NCursesEvent wHandleInput( wint_t key );

    virtual void setLabel( const string & nlabel );

    virtual void setEnabled( bool do_bv );

    YMenuItem * findItem( int selection ) { return findMenuItem( selection ); }

    virtual bool setKeyboardFocus() {
      if ( !grabFocus() )
        return YWidget::setKeyboardFocus();
      return true;
    }
};

///////////////////////////////////////////////////////////////////

#endif // NCMenuButton_h