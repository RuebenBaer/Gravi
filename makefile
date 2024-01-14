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
	$(OBJDIR)\partikel.o \
	$(OBJDIR)\PE_Dlg\ProgrammEinstellungenDlg.o \
	$(OBJDIR)\Dbl_Eingabe\Dbl_Eingabe.o \
	$(OBJDIR)\aru_events\aru_events.o \
	$(OBJDIR)\Kamera\Kamera_3D.o \
	$(OBJDIR)\Vektor\Vektor.o

.PHONEY: clean all

all: $(OBJ)
	$(CXX) $(CPPFLAGS) $(DEFS) -L$(WXLIBPATH) -o $(BIN) $(OBJ) -s $(LIBS)

$(OBJDIR)\base.o: $(SRCDIR)\base.cpp $(SRCDIR)\base.h
	if not exist $(OBJDIR) mkdir $(OBJDIR)
	$(CXX) $(CPPFLAGS) $(DEFS) $(INCLUDES) -c $< -o $@

$(OBJDIR)\partikel.o: $(SRCDIR)\partikel.cpp $(SRCDIR)\partikel.h
	if not exist $(OBJDIR) mkdir $(OBJDIR)
	$(CXX) $(CPPFLAGS) $(DEFS) $(INCLUDES) -c $< -o $@

$(OBJDIR)\PE_Dlg\ProgrammEinstellungenDlg.o: $(SRCDIR)\PE_Dlg\ProgrammEinstellungenDlg.cpp $(SRCDIR)\PE_Dlg\ProgrammEinstellungenDlg.h
	if not exist $(OBJDIR)\PE_Dlg mkdir $(OBJDIR)\PE_Dlg
	$(CXX) $(CPPFLAGS) $(DEFS) $(INCLUDES) -c $< -o $@

$(OBJDIR)\Dbl_Eingabe\Dbl_Eingabe.o: $(SRCDIR)\Dbl_Eingabe\Dbl_Eingabe.cpp $(SRCDIR)\Dbl_Eingabe\Dbl_Eingabe.h
	if not exist $(OBJDIR)\Dbl_Eingabe mkdir $(OBJDIR)\Dbl_Eingabe
	$(CXX) $(CPPFLAGS) $(DEFS) $(INCLUDES) -c $< -o $@

$(OBJDIR)\aru_events\aru_events.o: $(SRCDIR)\aru_events\aru_events.cpp $(SRCDIR)\aru_events\aru_events.h
	if not exist $(OBJDIR)\aru_events mkdir $(OBJDIR)\aru_events
	$(CXX) $(CPPFLAGS) $(DEFS) $(INCLUDES) -c $< -o $@

$(OBJDIR)\Kamera\Kamera_3D.o: $(SRCDIR)\Kamera\Kamera_3D.cpp $(SRCDIR)\Kamera\Kamera_3D.h
	if not exist $(OBJDIR)\Kamera mkdir $(OBJDIR)\Kamera
	$(CXX) $(CPPFLAGS) $(DEFS) $(INCLUDES) -c $< -o $@

$(OBJDIR)\Vektor\Vektor.o: $(SRCDIR)\Vektor\Vektor.cpp $(SRCDIR)\Vektor\Vektor.h
	if not exist $(OBJDIR)\Vektor mkdir $(OBJDIR)\Vektor
	$(CXX) $(CPPFLAGS) $(DEFS) $(INCLUDES) -c $< -o $@

clean:
	del /s /q $(OBJDIR)
	del /s /q $(BIN)