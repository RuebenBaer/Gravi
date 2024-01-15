#include <wx/wxprec.h>
#ifndef WX_PRECOMP
   #include <wx/wx.h>
#endif

#include "base.h"
#include "Liste\Verkettete_Liste.h"

IMPLEMENT_APP(MainApp)

bool MainApp::OnInit()
{
   MainFrame *win = new MainFrame(_("Frame"), wxPoint (100, 100),
     wxSize(450, 340));
   win->Show(TRUE);
   SetTopWindow(win);

   return TRUE;
}

MainFrame::MainFrame(const wxString &title, const wxPoint &pos, const wxSize &size)
    : wxFrame((wxFrame *) NULL, -1, title, pos, size)
{
	Bind(aruEVT_DOUBLE, &MainFrame::OnAruDouble, this);
	Bind(aruEVT_COLOUR, &MainFrame::OnAruColour, this);
	Bind(wxEVT_MENU, &MainFrame::OnQuit, this, ID_MAINWIN_QUIT);
	Bind(wxEVT_MENU, &MainFrame::OnTimerStart, this, ID_TIMER_START);
	Bind(wxEVT_PAINT, &MainFrame::OnPaintIdle, this);
	Bind(wxEVT_MOUSEWHEEL, &MainFrame::OnMouseWheel, this);
	Bind(wxEVT_MOTION, &MainFrame::OnMouseMove, this);
	Bind(wxEVT_LEFT_DOWN, MainFrame::OnLeftClick, this);
	Bind(wxEVT_MENU, &MainFrame::EinstellungenOeffnen, this, ID_PE_DLG);
	Bind(wxEVT_TIMER, &MainFrame::OnTimer, this, ID_TIMER);
	Bind(wxEVT_KEY_DOWN, &MainFrame::OnKeyDown, this);
	Bind(wxEVT_KEY_UP, &MainFrame::OnKeyUp, this);
	
	wxMenu *FileMenu = new wxMenu;
    wxMenuBar *MenuBar = new wxMenuBar;

    FileMenu->Append(ID_MAINWIN_QUIT, _("&Quit"));
	m_menuTimer = new wxMenuItem(FileMenu, ID_TIMER_START, "Starte Timer");
	FileMenu->Append(m_menuTimer);
	FileMenu->Append(ID_PE_DLG, "Einstellungen");
	m_menuAnsicht = new wxMenuItem(FileMenu, ID_ANSICHT, "3D Kamera");
	FileMenu->Append(m_menuAnsicht);

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
		part_lst[i]->ort[0] = 200 + (double)(rand() % 2500) / 10.0;
		part_lst[i]->ort[1] = 200 + (double)(rand() % 2500) / 10.0;
		part_lst[i]->ort[2] = (double)(rand() % 2500) / 10.0;
		part_lst[i]->masse = (double)(rand() % 10) + 1.0;
		part_lst[i]->radius = part_lst[i]->masse; // 5;
	}
	
	timer.SetOwner(this, ID_TIMER);
	//timer.Start(timerTick);
	
	Vektor kStart(325, 325, 425);
	m_auge = new Kamera(kStart, -90, 0, 50, 10);
	
	Maximize(true);
}

MainFrame::~MainFrame()
{
	for(int i = 0; i < anzPartikel; i++)
	{
		delete part_lst[i];
	}
}

void MainFrame::OnQuit(wxCommandEvent & WXUNUSED(event))
{
	timer.Stop();

	delete peDlg;
    Close(TRUE);
}

void MainFrame::OnTimerStart(wxCommandEvent& event)
{
	if(timer.IsRunning())
	{
		m_menuTimer->SetItemLabel("Starte Timer");
		Unbind(wxEVT_PAINT, &MainFrame::OnPaint3D, this);
		Bind(wxEVT_PAINT, &MainFrame::OnPaintIdle, this);
		timer.Stop();
		Refresh();
		return;
	}
	timer.Start(timerTick);
	m_menuTimer->SetItemLabel("Timer anhalten");
	Unbind(wxEVT_PAINT, &MainFrame::OnPaintIdle, this);
	Bind(wxEVT_PAINT, &MainFrame::OnPaint3D, this);
	
	return;
}

void MainFrame::OnAnsichtWechsel(wxCommandEvent& event)
{
	
	return;
}

void MainFrame::OnPaint(wxPaintEvent &event)
{
	wxPaintDC dc(this);
	dc.SetPen(wxPen(wxColor(0, 0, 0)));
	for(int i = 0; i < anzPartikel; i++)
	{
		int malRadius = part_lst[i]->radius * m_skalierung;
		if(malRadius < 1)malRadius = 1;
		dc.DrawCircle((part_lst[i]->ort[0] + dc_Offset[0]) * m_skalierung,
						(part_lst[i]->ort[1] + dc_Offset[1]) * m_skalierung,
						malRadius);
	}
	return;
}

void MainFrame::OnPaint3D(wxPaintEvent &event)
{
	wxPaintDC dc(this);
	dc.SetPen(wxPen(wxColor(0, 0, 0)));
	if(m_auge == NULL)
	{
		dc.DrawText("Keine Kamera\nvorhanden", dc.GetSize().GetWidth() / 2, dc.GetSize().GetHeight() / 2);
	}
	
	Vektor tempOrt;
	Vektor Ansicht, KameraStandpunkt;
	double entfernung, msEntfernung;
	Liste<PartikelBild> partBilder;
	PartikelBild *pB;
	
	KameraStandpunkt = m_auge->HoleOrt();
	msEntfernung = m_auge->HoleAbstand();
	for(int i = 0; i < anzPartikel; i++)
	{
		tempOrt = Vektor(part_lst[i]->ort);
		Ansicht = m_auge->Aufnahme(tempOrt);
		Ansicht += Vektor(dc_Offset[0] - 200, dc_Offset[1], 0);
		entfernung = (KameraStandpunkt - tempOrt).Laenge();
		
		int malRadius = part_lst[i]->radius * msEntfernung / entfernung;
		if(malRadius < 1)malRadius = 1;
		pB = new struct PartikelBild;
		pB->ort = Ansicht;
		pB->radius = malRadius;
		
		partBilder.Hinzufuegen(pB, false);
		partBilder.GetErstesListenelement()->Wert(-entfernung);
	}
	m_auge->Verschieben(-50, 0, 0);
	
	KameraStandpunkt = m_auge->HoleOrt();
	msEntfernung = m_auge->HoleAbstand();
	for(int i = 0; i < anzPartikel; i++)
	{
		tempOrt = Vektor(part_lst[i]->ort);
		Ansicht = m_auge->Aufnahme(tempOrt);
		Ansicht += Vektor(dc_Offset[0] + 200, dc_Offset[1], 0);
		entfernung = (KameraStandpunkt - tempOrt).Laenge();
		
		int malRadius = part_lst[i]->radius * msEntfernung / entfernung;
		if(malRadius < 1)malRadius = 1;
		pB = new struct PartikelBild;
		pB->ort = Ansicht;
		pB->radius = malRadius;
		
		partBilder.Hinzufuegen(pB, false);
		partBilder.GetErstesListenelement()->Wert(-entfernung);
	}
	m_auge->Verschieben(50, 0, 0);
	
	partBilder.ListeNachWertSortieren();
	
	for(PartikelBild* aktPB = partBilder.GetErstesElement(); aktPB != NULL; aktPB = partBilder.GetNaechstesElement())
	{
		dc.DrawCircle(aktPB->ort.x(), aktPB->ort.y(), aktPB->radius);
	}
	return;
}

void MainFrame::OnPaintIdle(wxPaintEvent& event)
{
	wxPaintDC dc(this);
	dc.SetPen(wxPen(wxColor(0, 0, 0)));
	for(int i = 0; i < anzPartikel; i++)
	{
		int malRadius = part_lst[i]->radius * m_skalierung;
		if(malRadius < 1)malRadius = 1;
		dc.DrawCircle((part_lst[i]->ort[0] + dc_Offset[0]) * m_skalierung,
						(part_lst[i]->ort[1] + dc_Offset[1]) * m_skalierung,
						malRadius);
	}
	dc.DrawText("PAUSE", dc.GetSize().GetWidth() / 2, dc.GetSize().GetHeight() / 2);
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
    //wxPoint MousePosition = event.GetLogicalPosition(dc);
    //double alteSkalierung = m_skalierung;
	
	m_wertFkt = 1;
	if(m_shift)m_wertFkt = 10;
    
	if(event.GetWheelRotation() < 0)
	{
		if(m_ctrl)
		{
			m_auge->InkrAbstand(1.0 * m_wertFkt);
		}else{
			m_auge->Verschieben(0, 0, 1.0 * m_wertFkt);
		}
		//m_skalierung = m_skalierung / (1 + 0.1 * m_wertFkt);
	}
	if(event.GetWheelRotation() > 0)
	{
		if(m_ctrl)
		{
			m_auge->InkrAbstand(-1.0 * m_wertFkt);
		}else{
			m_auge->Verschieben(0, 0, -1.0 * m_wertFkt);
		}
		//m_skalierung = m_skalierung * (1 + 0.1 * m_wertFkt);
	}

	//dc_Offset[0] -= MousePosition.x * ((1/alteSkalierung)-(1/m_skalierung));
	//dc_Offset[1] -= MousePosition.y * ((1/alteSkalierung)-(1/m_skalierung));
	//SetStatusText(wxString::Format("Offset: %.0f - %.0f / Skalierung: %5.5f", dc_Offset[0], dc_Offset[1], m_skalierung), 1);
	SetStatusText(wxString::Format("Kamera: %.5f / Mattscheibe: %.5f", m_auge->HoleOrt().z(), m_auge->HoleAbstand()), 1);

    Refresh();
    event.Skip();
    return;
}

void MainFrame::OnMouseMove(wxMouseEvent& event)
{
	if(event.Dragging())
	{
		wxClientDC dc(this);
		wxPoint MousePosition = event.GetLogicalPosition(dc);
		dc_Offset[0] += ((MousePosition.x - alteMousePosition.x) / m_skalierung);
		dc_Offset[1] += ((MousePosition.y - alteMousePosition.y) / m_skalierung);
		alteMousePosition = MousePosition;
		if(!timer.IsRunning())
		{
			Refresh();
		}
	}
    event.Skip();
    return;
}

void MainFrame::OnLeftClick(wxMouseEvent& event)
{
	wxClientDC dc(this);
	alteMousePosition = event.GetLogicalPosition(dc);
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
	switch(tempID)
	{
		case Programm_Einstellungen_Dialog::IDwGraviKonst:
			gravKonst = event.HoleWert();
			break;
		case Programm_Einstellungen_Dialog::IDwTimerTick:
			timerTick = event.HoleWert();
			if(timer.IsRunning())
			{
				timer.Stop();
				timer.Start(timerTick);
			}
			break;
	}

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

void MainFrame::OnKeyDown(wxKeyEvent& event)
{
	if(event.GetKeyCode() == WXK_SHIFT)
	{
		m_shift = true;
	}
	if(event.GetKeyCode() == WXK_CONTROL)
	{
		m_ctrl = true;
	}
}

void MainFrame::OnKeyUp(wxKeyEvent& event)
{
	if(event.GetKeyCode() == WXK_SHIFT)
	{
		m_shift = false;
	}
	if(event.GetKeyCode() == WXK_CONTROL)
	{
		m_ctrl = false;
	}
}