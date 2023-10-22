#ifndef __BASE_H
#define __BASE_H

#include "partikel.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>
#include "aru_events\aru_events.h"
#include "PE_Dlg\ProgrammEinstellungenDlg.h"

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
		partikel *part_lst[3];
		int anzPartikel = 3;
		double gravKonst = 1.0;
		wxTimer timer;
		int timerTick = 50;
		
		Programm_Einstellungen_Dialog* peDlg;
		
		double m_wertFkt, m_skalierung;
		int dc_Offset[2];
		
		void OnPaint(wxPaintEvent& event);
		void OnTimer(wxTimerEvent& event);
		void OnMouseWheel(wxMouseEvent& event);
		
		void OnAruDouble(aruDblEvent& event);
		void OnAruColour(aruColourEvent& event);
		
		void EinstellungenOeffnen(wxCommandEvent& event);
		//DECLARE_EVENT_TABLE()
};

enum
{
   ID_MAINWIN_QUIT = wxID_HIGHEST+1, ID_TIMER, ID_PE_DLG
};


#endif
