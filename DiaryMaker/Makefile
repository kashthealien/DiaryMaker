#############################################################################
# Makefile for building: DiaryMaker
# Generated by qmake (2.01a) (Qt 4.5.2) on: Sun Mar 13 18:12:46 2011
# Project:  DiaryMaker.pro
# Template: app
# Command: /usr/bin/qmake-qt4 -spec /usr/share/qt4/mkspecs/linux-g++ -unix CONFIG+=debug -o Makefile DiaryMaker.pro
#############################################################################

####### Compiler, tools and options

CC            = gcc
CXX           = g++
DEFINES       = -DQT_SQL_LIB -DQT_GUI_LIB -DQT_CORE_LIB -DQT_SHARED
CFLAGS        = -pipe -g -Wall -W -D_REENTRANT $(DEFINES)
CXXFLAGS      = -pipe -g -Wall -W -D_REENTRANT $(DEFINES)
INCPATH       = -I/usr/share/qt4/mkspecs/linux-g++ -I. -I/usr/include/qt4/QtCore -I/usr/include/qt4/QtGui -I/usr/include/qt4/QtSql -I/usr/include/qt4 -I/usr/include/qwt-qt4 -I. -I.
LINK          = g++
LFLAGS        = 
LIBS          = $(SUBLIBS)  -L/usr/lib -lqwt-qt4 -lQtSql -lQtGui -lQtCore -lpthread
AR            = ar cqs
RANLIB        = 
QMAKE         = /usr/bin/qmake-qt4
TAR           = tar -cf
COMPRESS      = gzip -9f
COPY          = cp -f
SED           = sed
COPY_FILE     = $(COPY)
COPY_DIR      = $(COPY) -r
INSTALL_FILE  = install -m 644 -p
INSTALL_DIR   = $(COPY_DIR)
INSTALL_PROGRAM = install -m 755 -p
DEL_FILE      = rm -f
SYMLINK       = ln -sf
DEL_DIR       = rmdir
MOVE          = mv -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p

####### Output directory

OBJECTS_DIR   = ./

####### Files

SOURCES       = diary.cpp \
		chatbrowser.cpp \
		fileparsers.cpp \
		indexer.cpp \
		main.cpp \
		plotter.cpp \
		searcher.cpp \
		sentimentanalyser.cpp \
		sqlitehandler.cpp \
		statextractor.cpp \
		utils.cpp \
		tutorial.cpp moc_diary.cpp \
		moc_fileparsers.cpp \
		moc_tutorial.cpp
OBJECTS       = diary.o \
		chatbrowser.o \
		fileparsers.o \
		indexer.o \
		main.o \
		plotter.o \
		searcher.o \
		sentimentanalyser.o \
		sqlitehandler.o \
		statextractor.o \
		utils.o \
		tutorial.o \
		moc_diary.o \
		moc_fileparsers.o \
		moc_tutorial.o
DIST          = /usr/share/qt4/mkspecs/common/g++.conf \
		/usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/debug.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		/usr/share/qt4/mkspecs/features/include_source_dir.prf \
		DiaryMaker.pro
QMAKE_TARGET  = DiaryMaker
DESTDIR       = 
TARGET        = DiaryMaker

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

$(TARGET): ui_diary.h ui_tutorial.h $(OBJECTS)  
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)

Makefile: DiaryMaker.pro  /usr/share/qt4/mkspecs/linux-g++/qmake.conf /usr/share/qt4/mkspecs/common/g++.conf \
		/usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/debug.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		/usr/share/qt4/mkspecs/features/include_source_dir.prf \
		/usr/lib/libQtSql.prl \
		/usr/lib/libQtGui.prl \
		/usr/lib/libQtCore.prl
	$(QMAKE) -spec /usr/share/qt4/mkspecs/linux-g++ -unix CONFIG+=debug -o Makefile DiaryMaker.pro
/usr/share/qt4/mkspecs/common/g++.conf:
/usr/share/qt4/mkspecs/common/unix.conf:
/usr/share/qt4/mkspecs/common/linux.conf:
/usr/share/qt4/mkspecs/qconfig.pri:
/usr/share/qt4/mkspecs/features/qt_functions.prf:
/usr/share/qt4/mkspecs/features/qt_config.prf:
/usr/share/qt4/mkspecs/features/exclusive_builds.prf:
/usr/share/qt4/mkspecs/features/default_pre.prf:
/usr/share/qt4/mkspecs/features/debug.prf:
/usr/share/qt4/mkspecs/features/default_post.prf:
/usr/share/qt4/mkspecs/features/warn_on.prf:
/usr/share/qt4/mkspecs/features/qt.prf:
/usr/share/qt4/mkspecs/features/unix/thread.prf:
/usr/share/qt4/mkspecs/features/moc.prf:
/usr/share/qt4/mkspecs/features/resources.prf:
/usr/share/qt4/mkspecs/features/uic.prf:
/usr/share/qt4/mkspecs/features/yacc.prf:
/usr/share/qt4/mkspecs/features/lex.prf:
/usr/share/qt4/mkspecs/features/include_source_dir.prf:
/usr/lib/libQtSql.prl:
/usr/lib/libQtGui.prl:
/usr/lib/libQtCore.prl:
qmake:  FORCE
	@$(QMAKE) -spec /usr/share/qt4/mkspecs/linux-g++ -unix CONFIG+=debug -o Makefile DiaryMaker.pro

dist: 
	@$(CHK_DIR_EXISTS) .tmp/DiaryMaker1.0.0 || $(MKDIR) .tmp/DiaryMaker1.0.0 
	$(COPY_FILE) --parents $(SOURCES) $(DIST) .tmp/DiaryMaker1.0.0/ && $(COPY_FILE) --parents diary.h chatbrowser.h fileparsers.h indexer.h plotter.h searcher.h sentimentanalyser.h sqlitehandler.h statextractor.h structs.h tutorial.h utils.h ui_diary.h ui_tutorial.h .tmp/DiaryMaker1.0.0/ && $(COPY_FILE) --parents diary.cpp chatbrowser.cpp fileparsers.cpp indexer.cpp main.cpp plotter.cpp searcher.cpp sentimentanalyser.cpp sqlitehandler.cpp statextractor.cpp utils.cpp tutorial.cpp .tmp/DiaryMaker1.0.0/ && $(COPY_FILE) --parents diary.ui tutorial.ui .tmp/DiaryMaker1.0.0/ && (cd `dirname .tmp/DiaryMaker1.0.0` && $(TAR) DiaryMaker1.0.0.tar DiaryMaker1.0.0 && $(COMPRESS) DiaryMaker1.0.0.tar) && $(MOVE) `dirname .tmp/DiaryMaker1.0.0`/DiaryMaker1.0.0.tar.gz . && $(DEL_FILE) -r .tmp/DiaryMaker1.0.0


clean:compiler_clean 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core


####### Sub-libraries

distclean: clean
	-$(DEL_FILE) $(TARGET) 
	-$(DEL_FILE) Makefile


mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all

compiler_moc_header_make_all: moc_diary.cpp moc_fileparsers.cpp moc_tutorial.cpp
compiler_moc_header_clean:
	-$(DEL_FILE) moc_diary.cpp moc_fileparsers.cpp moc_tutorial.cpp
moc_diary.cpp: structs.h \
		indexer.h \
		statextractor.h \
		sentimentanalyser.h \
		sqlitehandler.h \
		chatbrowser.h \
		tutorial.h \
		plotter.h \
		utils.h \
		fileparsers.h \
		diary.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) diary.h -o moc_diary.cpp

moc_fileparsers.cpp: structs.h \
		fileparsers.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) fileparsers.h -o moc_fileparsers.cpp

moc_tutorial.cpp: structs.h \
		tutorial.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) tutorial.h -o moc_tutorial.cpp

compiler_rcc_make_all:
compiler_rcc_clean:
compiler_image_collection_make_all: qmake_image_collection.cpp
compiler_image_collection_clean:
	-$(DEL_FILE) qmake_image_collection.cpp
compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_uic_make_all: ui_diary.h ui_tutorial.h
compiler_uic_clean:
	-$(DEL_FILE) ui_diary.h ui_tutorial.h
ui_diary.h: diary.ui
	/usr/bin/uic-qt4 diary.ui -o ui_diary.h

ui_tutorial.h: tutorial.ui
	/usr/bin/uic-qt4 tutorial.ui -o ui_tutorial.h

compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: compiler_moc_header_clean compiler_uic_clean 

####### Compile

diary.o: diary.cpp diary.h \
		structs.h \
		indexer.h \
		statextractor.h \
		sentimentanalyser.h \
		sqlitehandler.h \
		chatbrowser.h \
		tutorial.h \
		plotter.h \
		utils.h \
		fileparsers.h \
		ui_diary.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o diary.o diary.cpp

chatbrowser.o: chatbrowser.cpp chatbrowser.h \
		sqlitehandler.h \
		structs.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o chatbrowser.o chatbrowser.cpp

fileparsers.o: fileparsers.cpp fileparsers.h \
		structs.h \
		utils.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o fileparsers.o fileparsers.cpp

indexer.o: indexer.cpp indexer.h \
		statextractor.h \
		sentimentanalyser.h \
		structs.h \
		sqlitehandler.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o indexer.o indexer.cpp

main.o: main.cpp diary.h \
		structs.h \
		indexer.h \
		statextractor.h \
		sentimentanalyser.h \
		sqlitehandler.h \
		chatbrowser.h \
		tutorial.h \
		plotter.h \
		utils.h \
		fileparsers.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o main.o main.cpp

plotter.o: plotter.cpp plotter.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o plotter.o plotter.cpp

searcher.o: searcher.cpp searcher.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o searcher.o searcher.cpp

sentimentanalyser.o: sentimentanalyser.cpp sentimentanalyser.h \
		structs.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o sentimentanalyser.o sentimentanalyser.cpp

sqlitehandler.o: sqlitehandler.cpp sqlitehandler.h \
		structs.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o sqlitehandler.o sqlitehandler.cpp

statextractor.o: statextractor.cpp statextractor.h \
		sentimentanalyser.h \
		structs.h \
		sqlitehandler.h \
		utils.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o statextractor.o statextractor.cpp

utils.o: utils.cpp utils.h \
		structs.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o utils.o utils.cpp

tutorial.o: tutorial.cpp tutorial.h \
		structs.h \
		ui_tutorial.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o tutorial.o tutorial.cpp

moc_diary.o: moc_diary.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_diary.o moc_diary.cpp

moc_fileparsers.o: moc_fileparsers.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_fileparsers.o moc_fileparsers.cpp

moc_tutorial.o: moc_tutorial.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_tutorial.o moc_tutorial.cpp

####### Install

install:   FORCE

uninstall:   FORCE

FORCE:

