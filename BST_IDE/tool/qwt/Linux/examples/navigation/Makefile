#############################################################################
# Makefile for building: ../../examples/bin/navigation
# Generated by qmake (2.01a) (Qt 4.8.2) on: ?? 10? 12 10:00:50 2013
# Project:  navigation.pro
# Template: app
# Command: /opt/qt_4.8.2_es1/bin/qmake -o Makefile navigation.pro
#############################################################################

####### Compiler, tools and options

CC            = @echo compiling $< && arm-arago-linux-gnueabi-gcc
CXX           = @echo compiling $< && arm-arago-linux-gnueabi-g++
DEFINES       = -DQT_NO_DEBUG -DQT_NO_KEYWORDS -DQT_SVG_LIB -DQT_GUI_LIB -DQT_NETWORK_LIB -DQT_CORE_LIB -DQT_SHARED
CFLAGS        = -pipe -O2 -Wall -W -D_REENTRANT $(DEFINES)
CXXFLAGS      = -pipe -O2 -Wall -W -D_REENTRANT $(DEFINES)
INCPATH       = -I/opt/qt_4.8.2_es1/mkspecs/qws/linux-TIarmv7-sgx-g++ -I. -I/opt/qt_4.8.2_es1/include/QtCore -I/opt/qt_4.8.2_es1/include/QtNetwork -I/opt/qt_4.8.2_es1/include/QtGui -I/opt/qt_4.8.2_es1/include/QtSvg -I/opt/qt_4.8.2_es1/include -I../../src -Imoc
LINK          = @echo linking $@ && arm-arago-linux-gnueabi-g++
LFLAGS        = -Wl,-O1 -Wl,-rpath,/opt/qt_4.8.2_es1/lib
LIBS          = $(SUBLIBS)  -L/opt/qt_4.8.2_es1/lib -L../../lib -lqwt -lQtSvg -L/opt/qt_4.8.2_es1/lib -L/AM335X/SDK/gfx_dbg_es8.x -lQtGui -lQtNetwork -lQtCore -lEGL -lGLES_CM -lIMGegl -lsrv_um -lusc -lpthread 
AR            = arm-arago-linux-gnueabi-ar cqs
RANLIB        = 
QMAKE         = /opt/qt_4.8.2_es1/bin/qmake
TAR           = tar -cf
COMPRESS      = gzip -9f
COPY          = cp -f
SED           = sed
COPY_FILE     = $(COPY)
COPY_DIR      = $(COPY) -r
STRIP         = arm-arago-linux-gnueabi-strip
INSTALL_FILE  = install -m 644 -p
INSTALL_DIR   = $(COPY_DIR)
INSTALL_PROGRAM = install -m 755 -p
DEL_FILE      = rm -f
SYMLINK       = ln -f -s
DEL_DIR       = rmdir
MOVE          = mv -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p

####### Output directory

OBJECTS_DIR   = obj/

####### Files

SOURCES       = mainwindow.cpp \
		plot.cpp \
		main.cpp moc/moc_mainwindow.cpp \
		moc/moc_plot.cpp
OBJECTS       = obj/mainwindow.o \
		obj/plot.o \
		obj/main.o \
		obj/moc_mainwindow.o \
		obj/moc_plot.o
DIST          = /opt/qt_4.8.2_es1/mkspecs/common/unix.conf \
		/opt/qt_4.8.2_es1/mkspecs/common/linux.conf \
		/opt/qt_4.8.2_es1/mkspecs/common/gcc-base.conf \
		/opt/qt_4.8.2_es1/mkspecs/common/gcc-base-unix.conf \
		/opt/qt_4.8.2_es1/mkspecs/common/g++-base.conf \
		/opt/qt_4.8.2_es1/mkspecs/common/g++-unix.conf \
		/opt/qt_4.8.2_es1/mkspecs/common/qws.conf \
		/opt/qt_4.8.2_es1/mkspecs/qconfig.pri \
		/opt/qt_4.8.2_es1/mkspecs/modules/qt_webkit_version.pri \
		/opt/qt_4.8.2_es1/mkspecs/features/qt_functions.prf \
		/opt/qt_4.8.2_es1/mkspecs/features/qt_config.prf \
		/opt/qt_4.8.2_es1/mkspecs/features/exclusive_builds.prf \
		/opt/qt_4.8.2_es1/mkspecs/features/default_pre.prf \
		../../qwtconfig.pri \
		../../qwtbuild.pri \
		../examples.pri \
		/opt/qt_4.8.2_es1/mkspecs/features/release.prf \
		/opt/qt_4.8.2_es1/mkspecs/features/default_post.prf \
		/opt/qt_4.8.2_es1/mkspecs/features/silent.prf \
		/opt/qt_4.8.2_es1/mkspecs/features/warn_on.prf \
		/opt/qt_4.8.2_es1/mkspecs/features/qt.prf \
		/opt/qt_4.8.2_es1/mkspecs/features/unix/thread.prf \
		/opt/qt_4.8.2_es1/mkspecs/features/moc.prf \
		/opt/qt_4.8.2_es1/mkspecs/features/resources.prf \
		/opt/qt_4.8.2_es1/mkspecs/features/uic.prf \
		/opt/qt_4.8.2_es1/mkspecs/features/yacc.prf \
		/opt/qt_4.8.2_es1/mkspecs/features/lex.prf \
		/opt/qt_4.8.2_es1/mkspecs/features/include_source_dir.prf \
		navigation.pro
QMAKE_TARGET  = navigation
DESTDIR       = ../../examples/bin/
TARGET        = ../../examples/bin/navigation

first: all
####### Implicit rules

.SUFFIXES: .o .c .cpp .cc .cxx .C

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.C.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o "$@" "$<"

####### Build rules

all: Makefile $(TARGET)

$(TARGET):  $(OBJECTS)  
	@$(CHK_DIR_EXISTS) ../../examples/bin/ || $(MKDIR) ../../examples/bin/ 
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)

Makefile: navigation.pro  /opt/qt_4.8.2_es1/mkspecs/qws/linux-TIarmv7-sgx-g++/qmake.conf /opt/qt_4.8.2_es1/mkspecs/common/unix.conf \
		/opt/qt_4.8.2_es1/mkspecs/common/linux.conf \
		/opt/qt_4.8.2_es1/mkspecs/common/gcc-base.conf \
		/opt/qt_4.8.2_es1/mkspecs/common/gcc-base-unix.conf \
		/opt/qt_4.8.2_es1/mkspecs/common/g++-base.conf \
		/opt/qt_4.8.2_es1/mkspecs/common/g++-unix.conf \
		/opt/qt_4.8.2_es1/mkspecs/common/qws.conf \
		/opt/qt_4.8.2_es1/mkspecs/qconfig.pri \
		/opt/qt_4.8.2_es1/mkspecs/modules/qt_webkit_version.pri \
		/opt/qt_4.8.2_es1/mkspecs/features/qt_functions.prf \
		/opt/qt_4.8.2_es1/mkspecs/features/qt_config.prf \
		/opt/qt_4.8.2_es1/mkspecs/features/exclusive_builds.prf \
		/opt/qt_4.8.2_es1/mkspecs/features/default_pre.prf \
		../../qwtconfig.pri \
		../../qwtbuild.pri \
		../examples.pri \
		/opt/qt_4.8.2_es1/mkspecs/features/release.prf \
		/opt/qt_4.8.2_es1/mkspecs/features/default_post.prf \
		/opt/qt_4.8.2_es1/mkspecs/features/silent.prf \
		/opt/qt_4.8.2_es1/mkspecs/features/warn_on.prf \
		/opt/qt_4.8.2_es1/mkspecs/features/qt.prf \
		/opt/qt_4.8.2_es1/mkspecs/features/unix/thread.prf \
		/opt/qt_4.8.2_es1/mkspecs/features/moc.prf \
		/opt/qt_4.8.2_es1/mkspecs/features/resources.prf \
		/opt/qt_4.8.2_es1/mkspecs/features/uic.prf \
		/opt/qt_4.8.2_es1/mkspecs/features/yacc.prf \
		/opt/qt_4.8.2_es1/mkspecs/features/lex.prf \
		/opt/qt_4.8.2_es1/mkspecs/features/include_source_dir.prf \
		/opt/qt_4.8.2_es1/lib/libQtSvg.prl \
		/opt/qt_4.8.2_es1/lib/libQtGui.prl \
		/opt/qt_4.8.2_es1/lib/libQtNetwork.prl \
		/opt/qt_4.8.2_es1/lib/libQtCore.prl
	$(QMAKE) -o Makefile navigation.pro
/opt/qt_4.8.2_es1/mkspecs/common/unix.conf:
/opt/qt_4.8.2_es1/mkspecs/common/linux.conf:
/opt/qt_4.8.2_es1/mkspecs/common/gcc-base.conf:
/opt/qt_4.8.2_es1/mkspecs/common/gcc-base-unix.conf:
/opt/qt_4.8.2_es1/mkspecs/common/g++-base.conf:
/opt/qt_4.8.2_es1/mkspecs/common/g++-unix.conf:
/opt/qt_4.8.2_es1/mkspecs/common/qws.conf:
/opt/qt_4.8.2_es1/mkspecs/qconfig.pri:
/opt/qt_4.8.2_es1/mkspecs/modules/qt_webkit_version.pri:
/opt/qt_4.8.2_es1/mkspecs/features/qt_functions.prf:
/opt/qt_4.8.2_es1/mkspecs/features/qt_config.prf:
/opt/qt_4.8.2_es1/mkspecs/features/exclusive_builds.prf:
/opt/qt_4.8.2_es1/mkspecs/features/default_pre.prf:
../../qwtconfig.pri:
../../qwtbuild.pri:
../examples.pri:
/opt/qt_4.8.2_es1/mkspecs/features/release.prf:
/opt/qt_4.8.2_es1/mkspecs/features/default_post.prf:
/opt/qt_4.8.2_es1/mkspecs/features/silent.prf:
/opt/qt_4.8.2_es1/mkspecs/features/warn_on.prf:
/opt/qt_4.8.2_es1/mkspecs/features/qt.prf:
/opt/qt_4.8.2_es1/mkspecs/features/unix/thread.prf:
/opt/qt_4.8.2_es1/mkspecs/features/moc.prf:
/opt/qt_4.8.2_es1/mkspecs/features/resources.prf:
/opt/qt_4.8.2_es1/mkspecs/features/uic.prf:
/opt/qt_4.8.2_es1/mkspecs/features/yacc.prf:
/opt/qt_4.8.2_es1/mkspecs/features/lex.prf:
/opt/qt_4.8.2_es1/mkspecs/features/include_source_dir.prf:
/opt/qt_4.8.2_es1/lib/libQtSvg.prl:
/opt/qt_4.8.2_es1/lib/libQtGui.prl:
/opt/qt_4.8.2_es1/lib/libQtNetwork.prl:
/opt/qt_4.8.2_es1/lib/libQtCore.prl:
qmake:  FORCE
	@$(QMAKE) -o Makefile navigation.pro

dist: 
	@$(CHK_DIR_EXISTS) obj/navigation6.0.0 || $(MKDIR) obj/navigation6.0.0 
	$(COPY_FILE) --parents $(SOURCES) $(DIST) obj/navigation6.0.0/ && $(COPY_FILE) --parents mainwindow.h plot.h obj/navigation6.0.0/ && $(COPY_FILE) --parents mainwindow.cpp plot.cpp main.cpp obj/navigation6.0.0/ && (cd `dirname obj/navigation6.0.0` && $(TAR) navigation6.0.0.tar navigation6.0.0 && $(COMPRESS) navigation6.0.0.tar) && $(MOVE) `dirname obj/navigation6.0.0`/navigation6.0.0.tar.gz . && $(DEL_FILE) -r obj/navigation6.0.0


clean:compiler_clean 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core


####### Sub-libraries

distclean: clean
	-$(DEL_FILE) $(TARGET) 
	-$(DEL_FILE) Makefile


check: first

mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all

compiler_moc_header_make_all: moc/moc_mainwindow.cpp moc/moc_plot.cpp
compiler_moc_header_clean:
	-$(DEL_FILE) moc/moc_mainwindow.cpp moc/moc_plot.cpp
moc/moc_mainwindow.cpp: mainwindow.h
	@echo moc mainwindow.h && /opt/qt_4.8.2_es1/bin/moc $(DEFINES) $(INCPATH) mainwindow.h -o moc/moc_mainwindow.cpp

moc/moc_plot.cpp: ../../src/qwt_plot.h \
		../../src/qwt_global.h \
		../../src/qwt_text.h \
		../../src/qwt_plot_dict.h \
		../../src/qwt_plot_item.h \
		../../src/qwt_legend_itemmanager.h \
		../../src/qwt_scale_map.h \
		../../src/qwt_math.h \
		plot.h
	@echo moc plot.h && /opt/qt_4.8.2_es1/bin/moc $(DEFINES) $(INCPATH) plot.h -o moc/moc_plot.cpp

compiler_rcc_make_all:
compiler_rcc_clean:
compiler_image_collection_make_all: qmake_image_collection.cpp
compiler_image_collection_clean:
	-$(DEL_FILE) qmake_image_collection.cpp
compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_uic_make_all:
compiler_uic_clean:
compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: compiler_moc_header_clean 

####### Compile

obj/mainwindow.o: mainwindow.cpp ../../src/qwt_plot.h \
		../../src/qwt_global.h \
		../../src/qwt_text.h \
		../../src/qwt_plot_dict.h \
		../../src/qwt_plot_item.h \
		../../src/qwt_legend_itemmanager.h \
		../../src/qwt_scale_map.h \
		../../src/qwt_math.h \
		../../src/qwt_plot_rescaler.h \
		../../src/qwt_interval.h \
		../../src/qwt_scale_div.h \
		plot.h \
		mainwindow.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/mainwindow.o mainwindow.cpp

obj/plot.o: plot.cpp plot.h \
		../../src/qwt_plot.h \
		../../src/qwt_global.h \
		../../src/qwt_text.h \
		../../src/qwt_plot_dict.h \
		../../src/qwt_plot_item.h \
		../../src/qwt_legend_itemmanager.h \
		../../src/qwt_scale_map.h \
		../../src/qwt_math.h \
		../../src/qwt_plot_grid.h \
		../../src/qwt_scale_div.h \
		../../src/qwt_interval.h \
		../../src/qwt_plot_canvas.h \
		../../src/qwt_plot_layout.h \
		../../src/qwt_painter.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/plot.o plot.cpp

obj/main.o: main.cpp mainwindow.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/main.o main.cpp

obj/moc_mainwindow.o: moc/moc_mainwindow.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/moc_mainwindow.o moc/moc_mainwindow.cpp

obj/moc_plot.o: moc/moc_plot.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/moc_plot.o moc/moc_plot.cpp

####### Install

install:   FORCE

uninstall:   FORCE

FORCE:

