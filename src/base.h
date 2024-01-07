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
		~MainFrame();
		void OnQuit(wxCommandEvent &event);
		
	private:
		partikel *part_lst[10];
		int anzPartikel = 10;
		double gravKonst = 1.0;
		wxTimer timer;
		int timerTick = 50;
		
		wxPoint alteMousePosition;
		
		Programm_Einstellungen_Dialog* peDlg;
		
		double m_wertFkt, m_skalierung;
		double dc_Offset[2];
		
		void OnPaint(wxPaintEvent& event);
		void OnPaintIdle(wxPaintEvent& event);
		void OnTimer(wxTimerEvent& event);
		void OnTimerStart(wxCommandEvent& event);
		void OnMouseWheel(wxMouseEvent& event);
		void OnMouseMove(wxMouseEvent& event);
		void OnLeftClick(wxMouseEvent& event);
		
		void OnAruDouble(aruDblEvent& event);
		void OnAruColour(aruColourEvent& event);
		
		void EinstellungenOeffnen(wxCommandEvent& event);
		//DECLARE_EVENT_TABLE()
};

enum
{
   ID_MAINWIN_QUIT = wxID_HIGHEST+1, ID_TIMER, ID_TIMER_START, ID_PE_DLG
};


#endif
