#include <wx/wxprec.h>
#ifndef WX_PRECOMP
   #include <wx/wx.h>
#endif

#include "base.h"

IMPLEMENT_APP(MainApp)

bool MainApp::OnInit()
{
   MainFrame *win = new MainFrame(_("Frame"), wxPoint (100, 100),
     wxSize(450, 340));
   win->Show(TRUE);
   SetTopWindow(win);

   return TRUE;
}


/*BEGIN_EVENT_TABLE(MainFrame, wxFrame)
   EVT_MENU(ID_MAINWIN_QUIT, MainFrame::OnQuit)
   EVT_PAINT(MainFrame::OnPaint)
   EVT_MOUSEWHEEL(MainFrame::OnMouseWheel)
   EVT_MENU(ID_PE_DLG, MainFrame::EinstellungenOeffnen)
   EVT_TIMER(ID_TIMER, MainFrame::OnTimer)
END_EVENT_TABLE()*/

MainFrame::MainFrame(const wxString &title, const wxPoint &pos, const wxSize &size)
    : wxFrame((wxFrame *) NULL, -1, title, pos, size)
{
	Bind(aruEVT_DOUBLE, &MainFrame::OnAruDouble, this);
	Bind(aruEVT_COLOUR, &MainFrame::OnAruColour, this);
	Bind(wxEVT_MENU, &MainFrame::OnQuit, this, ID_MAINWIN_QUIT);
	Bind(wxEVT_PAINT, &MainFrame::OnPaint, this);
	Bind(wxEVT_MOUSEWHEEL, &MainFrame::OnMouseWheel, this);
	Bind(wxEVT_MENU, &MainFrame::EinstellungenOeffnen, this, ID_PE_DLG);
	Bind(wxEVT_TIMER, &MainFrame::OnTimer, this, ID_TIMER);
	
	wxMenu *FileMenu = new wxMenu;
    wxMenuBar *MenuBar = new wxMenuBar;

    FileMenu->Append(ID_MAINWIN_QUIT, _("&Quit"));
	FileMenu->Append(ID_PE_DLG, "Einstellungen");

    MenuBar->Append(FileMenu, _("&File"));
    SetMenuBar(MenuBar);	

    CreateStatusBar(2);
    SetStatusText(_("Gravitationssimulator"));
	
	m_wertFkt = 1.0;
	m_skalierung = 1.0;
	dc_Offset[0] = dc_Offset[1] = 200;
	
	peDlg = new Programm_Einstellungen_Dialog(this);
	
	srand (time(NULL));
	for(int i = 0; i < anzPartikel; i++)
	{
		part_lst[i] = new partikel;
		part_lst[i]->ort[0] = 200 + (double)(rand() % 2500) / 100.0;
		part_lst[i]->ort[1] = 200 + (double)(rand() % 2500) / 100.0;
		part_lst[i]->masse = (double)(rand() % 10) + 1.0;
		part_lst[i]->radius = part_lst[i]->masse / 5;
		part_lst[i]->ort[2] = 0.0;
	}
	
	timer.SetOwner(this, ID_TIMER);
	timer.Start(timerTick);
	
	Maximize(true);
}

void MainFrame::OnQuit(wxCommandEvent & WXUNUSED(event))
{
	timer.Stop();
	for(int i = 0; i < anzPartikel; i++)
	{
		delete part_lst[i];
	}
	
	delete peDlg;
    Close(TRUE);
}

void MainFrame::OnPaint(wxPaintEvent &event)
{
	wxPaintDC dc(this);
	dc.SetPen(wxPen(wxColor(0, 0, 0)));
	for(int i = 0; i < anzPartikel; i++)
	{
		dc.DrawCircle((part_lst[i]->ort[0] + dc_Offset[0]) * m_skalierung,
						(part_lst[i]->ort[1] + dc_Offset[1]) * m_skalierung,
						part_lst[i]->radius * m_skalierung);
	}
	return;
}

void MainFrame::OnTimer(wxTimerEvent& event)
{
	double deltaT = timerTick/1000.0;
	//std::cout<<"Tick: "<<deltaT<<"\n";
	for(int i = 0; i < anzPartikel; i++)
	{
		for(int k = i + 1; k < anzPartikel; k++)
		{
			Wechselwirkung(*part_lst[i], *part_lst[k], gravKonst);
		}
		Bewegen(deltaT, *part_lst[i]);
	}
	Refresh();
	return;
}

void MainFrame::OnMouseWheel(wxMouseEvent& event)
{
    wxClientDC dc(this);
    wxPoint MousePosition = event.GetLogicalPosition(dc);
    double alteSkalierung = m_skalierung;
    
	if(event.GetWheelRotation() < 0)
	{
		m_skalierung = m_skalierung / (1 + 0.1 * m_wertFkt);
	}
	if(event.GetWheelRotation() > 0)
	{
		m_skalierung = m_skalierung * (1 + 0.1 * m_wertFkt);
	}

	dc_Offset[0] -= MousePosition.x * ((1/alteSkalierung)-(1/m_skalierung));
	dc_Offset[1] -= MousePosition.y * ((1/alteSkalierung)-(1/m_skalierung));
	SetStatusText(wxString::Format("Offset: %d - %d / Skalierung: %5.5f", dc_Offset[0], dc_Offset[1], m_skalierung), 1);

    Refresh();
    event.Skip();
    return;
}

void MainFrame::EinstellungenOeffnen(wxCommandEvent& event)
{
	peDlg->ShowModal();
	return;
}

void MainFrame::OnAruDouble(aruDblEvent& event)
{
	int tempID = event.GetId();
    double Wert = event.HoleWert();
	
	SetStatusText (wxString::Format("Wert = %.2f; ID = %d", Wert, tempID), 0);
	Refresh();
	event.Skip();
	return;
}

void MainFrame::OnAruColour(aruColourEvent& event)
{
	SetStatusText(wxString::Format("Farbe = %d %d %d; ID = %d", event.HoleWert().Red(),
					event.HoleWert().Green(), event.HoleWert().Blue(), event.GetId()), 0);
	event.Skip();
	return;
}