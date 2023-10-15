#ifndef __BASE_H
#define __BASE_H

#include "partikel.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h> 

class MainApp: public wxApp
{
  public:
      virtual bool OnInit();
};

class MainFrame: public wxFrame
{
	public:
		MainFrame(const wxString &title, const wxPoint &pos, const wxSize &size);
		void OnQuit(wxCommandEvent &event);
		
	private:
		partikel *part_lst[200];
		int anzPartikel = 200;
		double gravKonst = 0.00001;
		wxTimer timer;
		int timerTick = 50;
		void OnPaint(wxPaintEvent& event);
		void OnTimer(wxTimerEvent& event);
		DECLARE_EVENT_TABLE()
};

enum
{
   ID_MAINWIN_QUIT = wxID_HIGHEST+1, ID_TIMER
};


#endif
