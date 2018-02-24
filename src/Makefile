include ../VERSION
include ../Makefile.inc

CFLAGS += -fPIC -fexceptions
CXXFLAGS += -fPIC

.PHONY: all clean

all: $(SLIBC_LIB_SO)

SLIBC_OBJS=slibc.o stdio_fmt_s.o string_s.o stdio_s.o stdlib_s.o \
	time_s.o stdio_ext_s.o \
	gnu_qsort_s.o gnu_bsearch_s.o gnu_strtok_s.o gnu_vfscanf_s.o 

# static libraries
# $(SLIBC_LIB): $(SLIBC_OBJS)
# 	ar rcs $(SLIBC_LIB) $(SLIBC_OBJS)

$(SLIBC_LIB_SO): $(SLIBC_OBJS)
	$(CC) -shared -Wl,-soname,$(SLIBC_LIB_SONAME) -o $(SLIBC_LIB_SO) $(SLIBC_OBJS)

%_cpp.o: %.c
	$(CXX) $(CXXFLAGS) -c -o $@ $<
%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

prepare_test:
	ln -s $(SLIBC_LIB_SO) $(SLIBC_LIB_SONAME)

clean: 
	rm -f *.o *.gcda *.gcno *.gcov $(SLIBC_LIB) \
	$(SLIBC_LIB_SO) $(SLIBC_LIB_SONAME) lib$(SLIBC_NAME).so 
