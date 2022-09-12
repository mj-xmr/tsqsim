#
# Example project that uses QCustomPlot as a shared library
#
# The compiled shared library file(s) must be in the project directory.
# On Unix, set LD_LIBRARY_PATH to "." before launching the compiled application
# unless the library files are installed in one of the library locations (e.g. /usr/lib)
#
# Note that the qcustomplot.h header should not be added to the project file in the
# HEADERS variable, but only included in your source files with #include.
#

QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

greaterThan(QT_MAJOR_VERSION, 4): CONFIG += c++11
lessThan(QT_MAJOR_VERSION, 5): QMAKE_CXXFLAGS += -std=c++11

TARGET = sharedlib-usage
TEMPLATE = app

# Tell the qcustomplot header that it will be used as library:
DEFINES += QCUSTOMPLOT_USE_LIBRARY

# Link with debug version of qcustomplot if compiling in debug mode, else with release library:
CONFIG(debug, release|debug) {
  win32:QCPLIB = qcustomplotd2
  else: QCPLIB = qcustomplotd
} else {
  win32:QCPLIB = qcustomplot2
  else: QCPLIB = qcustomplot
}
LIBS += -L./ -l$$QCPLIB

SOURCES += main.cpp
