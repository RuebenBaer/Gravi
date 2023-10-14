CXX = g++
CPPFLAGS =  \
	-Wall \
	-Werror \
	-Wpedantic \
	-pipe \
	-mthreads \
	-O3 \
	-std=gnu++11

INCLUDES =  \
	-I$(WXINCLUDE) \
	-I$(WXINCLUDESETUP)

DEFS =  \
	-D__WXMSW__ \
	-DwxUSE_UNICODE

LIBS = \
	-lkernel32 \
	-luser32 \
	-lgdi32 \
	-lcomdlg32 \
	-lwinspool \
	-lwinmm \
	-lshell32 \
	-lshlwapi \
	-lcomctl32 \
	-lole32 \
	-loleaut32 \
	-luuid \
	-lrpcrt4 \
	-ladvapi32 \
	-lversion \
	-lws2_32 \
	-lwininet \
	-loleacc \
	-luxtheme

include wxLib.lst

OBJDIR = obj
SRCDIR = src
BINDIR = bin
BIN = $(BINDIR)\gravi.exe
OBJ = \
	$(OBJDIR)\base.o \
	$(OBJDIR)\partikel.o

.PHONEY: clean all

all: $(OBJ)
	$(CXX) $(CPPFLAGS) $(DEFS) -L$(WXLIBPATH) -o $(BIN) $(OBJ) -s $(LIBS)

$(OBJDIR)\base.o: $(SRCDIR)\base.cpp
	if not exist $(OBJDIR) mkdir $(OBJDIR)
	$(CXX) $(CPPFLAGS) $(DEFS) $(INCLUDES) -c $< -o $@

$(OBJDIR)\partikel.o: $(SRCDIR)\partikel.cpp
	if not exist $(OBJDIR) mkdir $(OBJDIR)
	$(CXX) $(CPPFLAGS) $(DEFS) $(INCLUDES) -c $< -o $@

clean:
	del /q $(OBJDIR)
	del /q $(BIN)