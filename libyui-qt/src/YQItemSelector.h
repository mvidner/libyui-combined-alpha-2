/*
  Copyright (C) 2019 SUSE LLC
  This library is free software; you can redistribute it and/or modify
  it under the terms of the GNU Lesser General Public License as
  published by the Free Software Foundation; either version 2.1 of the
  License, or (at your option) version 3.0 of the License. This library
  is distributed in the hope that it will be useful, but WITHOUT ANY
  WARRANTY; without even the implied warranty of MERCHANTABILITY or
  FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public
  License for more details. You should have received a copy of the GNU
  Lesser General Public License along with this library; if not, write
  to the Free Software Foundation, Inc., 51 Franklin Street, Fifth
  Floor, Boston, MA 02110-1301 USA
*/


/*-/

  File:	      YQItemSelector.h

  Author:     Stefan Hundhammer <shundhammer@suse.de>

/-*/


#ifndef YQItemSelector_h
#define YQItemSelector_h

#include <QScrollArea>
#include <QMap>

#include <yui/YItemSelector.h>

class QScrollArea;
class QHBoxLayout;
class QVBoxLayout;
class QLabel;
class YQSelectorItemWidget;


class YQItemSelector: public QScrollArea, public YItemSelector
{
    Q_OBJECT

public:

    /**
     * Constructor.
     **/
    YQItemSelector( YWidget *	 parent,
		    bool	 enforceSingleSelection = true );

    /**
     * Destructor.
     **/
    virtual ~YQItemSelector();

    /**
     * Add an item.
     *
     * Reimplemented from YSelectionWidget.
     **/
    virtual void addItem( YItem * item );

    /**
     * Add multiple items.
     *
     * Reimplemented for efficiency from YSelectionWidget.
     **/
    virtual void addItems( const YItemCollection & itemCollection );

    /**
     * Select or deselect an item.
     *
     * Reimplemented from YSelectionWidget.
     **/
    virtual void selectItem( YItem * item, bool selected = true );

    /**
     * Deselect all items.
     *
     * Reimplemented from YSelectionWidget.
     **/
    virtual void deselectAllItems();

    /**
     * Delete all items.
     *
     * Reimplemented from YSelectionWidget.
     **/
    virtual void deleteAllItems();

    /**
     * Set enabled/disabled state.
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

    /**
     * Return the QWidget that will accept the item widgets.
     **/
    QWidget * itemContainer() { return _itemContainer; }

    /**
     * Add an item widget to the appropriate layout.
     * Not to confuse with addItem( YItem * ).
     **/
    void addItemWidget( YQSelectorItemWidget * itemWidget );


protected slots:

    /**
     * Notification that an item has been selected.
     * This is only relevant if `opt(`notify ) is set.
     **/
    void slotSelectionChanged( YQSelectorItemWidget *   itemWidget,
                               bool                     selected );



protected:

    /**
     * Deselect all items except 'selectedItem'.
     **/
    void deselectOtherItems( YItem * selectedItem );

    //
    // Data members
    //

    QWidget	* _itemContainer;
    QVBoxLayout * _itemLayout;

    QMap<YItem *, YQSelectorItemWidget *> _itemWidgets;

};	// class YQItemSelector



/**
 * Class for the widgets of one ItemSelector item
 **/
class YQSelectorItemWidget: public QFrame
{
    Q_OBJECT

public:

    /**
     * Constructor.
     **/
    YQSelectorItemWidget( YQItemSelector        * parent,
			  YItem			* item );
    /**
     * Destructor.
     **/
    virtual ~YQSelectorItemWidget();

    /**
     * Select the appropriate widget according to the parent's selection policy
     * (single or multi selection).
     **/
    void setSelected( bool sel = true );

    /**
     * Return 'true' if this item is selected, 'false' otherwise.
     **/
    bool selected() const;

    /**
     * Return 'true' if the parent YItemSelector has single selection (1-of-n).
     **/
    bool singleSelection() const;

    /**
     * Return 'true' if the parent YItemSelector has multi selection (n-of-m).
     **/
    bool multiSelection() const { return ! singleSelection(); }

    /**
     * Return the widget that handles the selection: Either a QRadioButton or a
     * QCheckBox. Both inherit QAbstractButton which has 'isChecked()' and
     * 'setChecked()'.
     **/
    QAbstractButton	* headingToggle()	const { return _headingToggle;		}

    //
    // Getters
    //

    YQItemSelector	* parent()		const { return _parent;			}
    QLabel		* descriptionLabel()	const { return _descriptionLabel;	}
    QLabel		* iconLabel()		const { return _iconLabel;		}
    YItem		* item()		const { return _item;			}

signals:

    void selectionChanged( YQSelectorItemWidget * itemWidget, bool selected );


protected slots:

    void slotSelectionChanged( bool selected );


protected:

    void createWidgets( const std::string	& label,
			const std::string	& description,
			const std::string	& iconName,
			bool			  selected = false );

    //
    // Data members
    //

    YQItemSelector	* _parent;
    YItem		* _item;

    QHBoxLayout		* _hBox;
    QVBoxLayout		*   _vBox;
    QAbstractButton	*     _headingToggle;
    QLabel		*     _descriptionLabel;
    QLabel		*   _iconLabel;

};	// class YQSelectorItem



#endif	// YQItemSelector_h
