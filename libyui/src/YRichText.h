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

  File:		YRichText.h

  Author:	Stefan Hundhammer <sh@suse.de>

/-*/

#ifndef YRichText_h
#define YRichText_h

#include <string>
#include "YWidget.h"
#include "ImplPtr.h"

using std::string;

class YRichTextPrivate;


class YRichText : public YWidget
{
public:

    /**
     * Constructor.
     *
     * 'plainTextMode' indicates that the text should be treated as plain text,
     * i.e. any HTML-like tags in the text should not be interpreted in any
     * way.
     **/
    YRichText( YWidget * 	parent,
	       const string & 	text,
	       bool 		plainTextMode = false );

    /**
     * Destructor.
     **/
    virtual ~YRichText();

    /**
     * Returns a descriptive name of this widget class for logging,
     * debugging etc.
     **/
    virtual const char * widgetClass() const { return "YRichText"; }

    /**
     * Change the text content of the RichText widget.
     *
     * Derived classes should overwrite this function, but call this base class
     * function in the new function.
     **/
    virtual void setValue( const string & newValue );

    /**
     * Return the text content of the RichText widget.
     **/
    string value() const;

    /**
     * Alias for setValue().
     **/
    void setText( const string & newText ) { setValue( newText ); }

    /**
     * Alias for value().
     **/
    string text() const { return value(); }

    /**
     * Return 'true' if this RichText widget is in "plain text" mode, i.e. does
     * not try to interpret RichText/HTML tags.
     **/
    bool plainTextMode() const;

    /**
     * Set this RichText widget's "plain text" mode on or off.
     *
     * Derived classes may want to reimplement this, but they should call this
     * base class function in the new function.
     **/
    virtual void setPlainTextMode( bool on = true );

    /**
     * Return 'true' if this RichText widget should automatically scroll down
     * when the text content is changed. This is useful for progress displays
     * and log files.
     **/
    bool autoScrollDown() const;

    /**
     * Set this RichText widget's "auto scroll down" mode on or off.
     *
     * Derived classes may want to reimplement this, but they should call this
     * base class function in the new function.
     **/
    virtual void setAutoScrollDown( bool on = true );

    /**
     * Returns 'true' if this widget is "shrinkable", i.e. it should be very
     * small by default.
     **/
    bool shrinkable() const;

    /**
     * Make this widget shrinkable, i.e. very small in layouts.
     *
     * This method is intentionally not virtual because it doesn't have any
     * immediate effect; it is only needed in preferredWidth() /
     * preferredHeight().
     **/
    void setShrinkable( bool shrinkable = true );

    /**
     * Set a property.
     * Reimplemented from YWidget.
     *
     * This function may throw YUIPropertyExceptions.
     *
     * This function returns 'true' if the value was successfully set and
     * 'false' if that value requires special handling (not in error cases:
     * those are covered by exceptions).
     **/
    virtual bool setProperty( const string & propertyName,
			      const YPropertyValue & val );

    /**
     * Get a property.
     * Reimplemented from YWidget.
     *
     * This method may throw YUIPropertyExceptions.
     **/
    virtual YPropertyValue getProperty( const string & propertyName );

    /**
     * Return this class's property set.
     * This also initializes the property upon the first call.
     *
     * Reimplemented from YWidget.
     **/
    virtual const YPropertySet & propertySet();


protected:

    ImplPtr<YRichTextPrivate> priv;
};


#endif // YRichText_h
