CXXFLAGS= -Wall -pthread -O0 -g $(INCLUDE_DIRS)
CFLAGS= -Wall -pthread -O0 -g $(INCLUDE_DIRS)
INCLUDE_DIRS=-I./include -I../include

CC=gcc
CXX=g++

#CXXFLAGS+=-O0 -fprofile-arcs -ftest-coverage
#CXXFLAGS+=-O0 --coverage

# change to reflect path to the CppUnit-Framework
CPPUNIT_PATH=/usr/include/cppunit

SLIBC_NAME=slibc

SLIBC_LIB=lib$(SLIBC_NAME).a

SLIBC_LIB_SH=lib$(SLIBC_NAME).so

SLIBC_LIB_SO=lib$(SLIBC_NAME).so.$(VER_MAJOR).$(VER_MINOR).$(VER_RELEASE)

SLIBC_LIB_SONAME=lib$(SLIBC_NAME).so

libdir.x86_64 = /usr/lib64
libdir.i686   = /usr/lib

MACHINE := $(shell uname -m)
SYSTEM := $(shell ./checkdistro.sh)

ifneq ($(SYSTEM),debian)
libdir = $(libdir.$(MACHINE))
else
libdir = $(libdir.i686)
endif
includedir = /usr/include/
mandir = /usr/share/man/
