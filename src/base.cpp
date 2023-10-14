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


BEGIN_EVENT_TABLE(MainFrame, wxFrame)
   EVT_MENU(ID_MAINWIN_QUIT, MainFrame::OnQuit)
   EVT_PAINT(MainFrame::OnPaint)
   EVT_TIMER(ID_TIMER, MainFrame::OnTimer)
END_EVENT_TABLE()

MainFrame::MainFrame(const wxString &title, const wxPoint &pos, const wxSize &size)
    : wxFrame((wxFrame *) NULL, -1, title, pos, size)
{
    wxMenu *FileMenu = new wxMenu;
    wxMenuBar *MenuBar = new wxMenuBar;

    FileMenu->Append(ID_MAINWIN_QUIT, _("&Quit"));

    MenuBar->Append(FileMenu, _("&File"));
    SetMenuBar(MenuBar);	

    CreateStatusBar(2);
    SetStatusText(_("Hello World!"));
	
	srand (time(NULL));
	for(int i = 0; i < anzPartikel; i++)
	{
		part_lst[i] = new partikel;
		part_lst[i]->ort[0] = 200 + (double)(rand() % 10000) / 100.0;
		part_lst[i]->ort[1] = 200 + (double)(rand() % 10000) / 100.0;
		part_lst[i]->masse = (double)(rand() % 10) + 1.0;
		part_lst[i]->radius = part_lst[i]->masse / 5;
		part_lst[i]->ort[2] = 0.0;
	}
	
	timer.SetOwner(this, ID_TIMER);
	timer.Start(timerTick);
}

void MainFrame::OnQuit(wxCommandEvent & WXUNUSED(event))
{
	timer.Stop();
	for(int i = 0; i < anzPartikel; i++)
	{
		delete part_lst[i];
	}
    Close(TRUE);
}

void MainFrame::OnPaint(wxPaintEvent &event)
{
	wxPaintDC dc(this);
	dc.SetPen(wxPen(wxColor(0, 0, 0)));
	for(int i = 0; i < anzPartikel; i++)
	{
		dc.DrawCircle(part_lst[i]->ort[0], part_lst[i]->ort[1], part_lst[i]->radius);
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