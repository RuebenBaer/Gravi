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
	$(OBJDIR)\Matrix\Matrix.o \
	$(OBJDIR)\Vektor\Vektor.o \
	$(OBJDIR)\aruZeichner\aruZeichnerR.o \
	$(OBJDIR)\aruZeichner\aruZeichnerGB.o \
	$(OBJDIR)\aruZeichner\px_font.o \
	$(OBJDIR)\resource.res
	

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

$(OBJDIR)\Matrix\Matrix.o: $(SRCDIR)\Matrix\Matrix.cpp $(SRCDIR)\Matrix\Matrix.h
	if not exist $(OBJDIR)\Matrix mkdir $(OBJDIR)\Matrix
	$(CXX) $(CPPFLAGS) $(DEFS) $(INCLUDES) -c $< -o $@

$(OBJDIR)\Vektor\Vektor.o: $(SRCDIR)\Vektor\Vektor.cpp $(SRCDIR)\Vektor\Vektor.h
	if not exist $(OBJDIR)\Vektor mkdir $(OBJDIR)\Vektor
	$(CXX) $(CPPFLAGS) $(DEFS) $(INCLUDES) -c $< -o $@

$(OBJDIR)\aruZeichner\aruZeichnerR.o: $(SRCDIR)\aruZeichner\aruZeichnerR.cpp $(SRCDIR)\aruZeichner\aruZeichnerR.h
	if not exist $(OBJDIR)\aruZeichner mkdir $(OBJDIR)\aruZeichner
	$(CXX) $(CPPFLAGS) $(DEFS) $(INCLUDES) -c $< -o $@

$(OBJDIR)\aruZeichner\aruZeichnerGB.o: $(SRCDIR)\aruZeichner\aruZeichnerGB.cpp $(SRCDIR)\aruZeichner\aruZeichnerGB.h
	if not exist $(OBJDIR)\aruZeichner mkdir $(OBJDIR)\aruZeichner
	$(CXX) $(CPPFLAGS) $(DEFS) $(INCLUDES) -c $< -o $@

$(OBJDIR)\aruZeichner\px_font.o: $(SRCDIR)\aruZeichner\px_font.cpp $(SRCDIR)\aruZeichner\px_font.h
	if not exist $(OBJDIR)\aruZeichner mkdir $(OBJDIR)\aruZeichner
	$(CXX) $(CPPFLAGS) $(DEFS) $(INCLUDES) -c $< -o $@

$(OBJDIR)\resource.res: $(SRCDIR)\resource.rc
	if not exist $(OBJDIR) mkdir $(OBJDIR)
	windres.exe $(INCLUDES) -J rc -O coff -i $(SRCDIR)\resource.rc -o $(OBJDIR)\resource.res

clean:
	del /s /q $(OBJDIR)
	del /s /q $(BIN)