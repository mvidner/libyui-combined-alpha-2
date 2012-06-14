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

  File:	      YQCheckBoxFrame.h

  Author:     Stefan Hundhammer <sh@suse.de>

/-*/


#ifndef YQCheckBoxFrame_h
#define YQCheckBoxFrame_h

#include <qgroupbox.h>
#include "YCheckBoxFrame.h"


class QWidget;
class QCheckBox;

class YQCheckBoxFrame : public QGroupBox, public YCheckBoxFrame
{
    Q_OBJECT

public:

    /**
     * Constructor.
     **/
    YQCheckBoxFrame( YWidget * 		parent,
		     const std::string &	label,
		     bool 		checked );

    /**
     * Change the label text on the CheckBoxFrame.
     *
     * Reimplemented from YCheckBoxFrame.
     **/
    virtual void setLabel( const std::string & label );

    /**
     * Check or uncheck the CheckBoxFrame's check box.
     *
     * Reimplemented from YCheckBoxFrame.
     **/
    virtual void setValue( bool isChecked );

    /**
     * Get the status of the CheckBoxFrame's check box.
     *
     * Reimplemented from YCheckBoxFrame.
     **/
    virtual bool value();

    /**
     * Set enabled / disabled state.
     *
     * Reimplemented from YWidget.
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


private slots:

    /**
     * Triggered when the on/off status is changed
     **/
    void stateChanged( bool newState );


protected:

    /**
     * Reimplemented from QGroupBox to prevent QGroupBox from disabling
     * children according to the check box status as the children are inserted.
     **/
    virtual void childEvent( QChildEvent * );

    virtual bool event(QEvent *e);
};


#endif // YQCheckBoxFrame_h
