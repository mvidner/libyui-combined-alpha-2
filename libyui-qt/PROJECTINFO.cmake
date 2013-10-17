##### PROJECTINFO for CMake

SET( BASELIB		"yui" )		# don't change this

##### MAKE ALL NEEDED CHANGES HERE #####

SET( SUBDIRS		src )	        # set the subdirs where your code is located.
SET( PLUGINNAME		"qt" )		# define the your plugin's name, e.g. {gtk, ncurses-pkg, qt-graph}
SET( LIB_DEPS		Qt5Widgets)		# define the plugin's dependecies CMake should look for separated with spaces; libyui-internal deps go in the next line
# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)
SET( INTERNAL_DEPS	Libyui )	# include libyui or it's plugins (if needed), too!
SET( LIB_LINKER		Qt5Core Qt5Gui Qt5Widgets Qt5Svg X11 fontconfig dl pthread )	# define the libs to link against with their -l name for separated with spaces, e.g. pthread dl; include libyui or it's plugins (if needed), too!
SET( EXTRA_INCLUDES	/usr/include/qt5 /usr/include/qt5/QtCore /usr/include/qt5/QtGui /usr/include/qt5/QtWidgets /usr/include/qt5/QtSvg)		# set include-dir which are not picked by CMake automagically here.
SET( PROGSUBDIR		"" )		# define your programm's name if the plugin is made for it, only. e.g. "YaST2" for {gtk,ncurses,qt}-pkg.
SET( URL                "http://github.com/libyui/" )
SET( SUMMARY            "Libyui - Qt User Interface" )
SET( DESCRIPTION        "This package contains the Qt user interface\ncomponent for libYUI.\n" )


## Things to cleanup; probably too yast2 related

SET( YUIQT_THEMEDIR		"${CMAKE_INSTALL_PREFIX}/share/YaST2/theme" )
SET( YUIQT_ICONDIR		"${CMAKE_INSTALL_PREFIX}/share/YaST2/theme/current" )
SET( YUIQT_LOCALEDIR		"${CMAKE_INSTALL_PREFIX}/share/YaST2/locale" )
SET( YUIQT_LANG_FONTS_FILE	"${CMAKE_INSTALL_PREFIX}/share/YaST2/data/lang_fonts" )
