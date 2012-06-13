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

  File:	      QY2ComboTabWidget.h

  Author:     Stefan Hundhammer <sh@suse.de>

  This is a pure Qt widget - it can be used independently of YaST2.

/-*/


#ifndef QY2ComboTabWidget_h
#define QY2ComboTabWidget_h

#include <QString>
#include <QHash>

class QComboBox;
class QLabel;
class QStackedWidget;
class QWidget;


/**
 * This widget is very much like a QTabWidget, but it uses a combo box above
 * the tab pages rather than a ( scrolled ) one-line row of tabs.
 **/
class QY2ComboTabWidget : public QWidget
{
    Q_OBJECT

public:

    /**
     * Constructor. 'combo_box_label' is the user-visible label of the combo
     * box that is used to switch between the different tab pages.
     **/
    QY2ComboTabWidget( const QString &	combo_box_label,
		       QWidget *	parent = 0,
		       const char *	name   = 0 );

    /**
     * Destructor.
     **/
    virtual ~QY2ComboTabWidget();

    /**
     * Add a page. 'page_label' will be the user-visible combo box entry for
     * that page.
     **/
    void addPage( const QString & page_label, QWidget * page );


signals:

    /**
     * Emitted when the current page changes.
     * NOT emitted initially for the very first page that is shown.
     **/
    void currentChanged( QWidget * newCurrentPage );


public slots:

    /**
     * Show a page. Updates the combo box contents accordingly.
     * This is an expensive operation: All combo box items are searched for the
     * item that corresponds to this page.
     **/
    void showPage( QWidget * page );


protected slots:

    /**
     * Show a page identified by its index. Does NOT update the combo box
     * contents.
     **/
    void showPageIndex( int index );


protected:

    QComboBox		* combo_box;
    QLabel		* combo_label;
    QStackedWidget 	* widget_stack;
    QHash<int, QWidget *>	  pages;
};

#endif // QY2ComboTabWidget_h
