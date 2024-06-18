#include <wx/wxprec.h>
#ifndef WX_PRECOMP
   #include <wx/wx.h>
#endif

#include "base.h"
#include "Liste\Verkettete_Liste.h"

IMPLEMENT_APP(MainApp)

bool MainApp::OnInit()
{
   MainFrame *win = new MainFrame(_("Gravitationssimulator"), wxPoint (100, 100),
     wxSize(450, 340));
   SetExitOnFrameDelete(TRUE);
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
	Bind(wxEVT_RIGHT_DOWN, MainFrame::OnRightClick, this);
	Bind(wxEVT_RIGHT_UP, MainFrame::OnRightUp, this);
	Bind(wxEVT_MENU, &MainFrame::EinstellungenOeffnen, this, ID_PE_DLG);
	Bind(wxEVT_MENU, &MainFrame::OnAnsichtWechsel, this, ID_ANSICHT);
	Bind(wxEVT_TIMER, &MainFrame::OnTimer, this, ID_TIMER);
	Bind(wxEVT_KEY_DOWN, &MainFrame::OnKeyDown, this);
	Bind(wxEVT_KEY_UP, &MainFrame::OnKeyUp, this);
	Bind(wxEVT_ERASE_BACKGROUND, &MainFrame::OnEraseBackground, this);
	AktPaint = &MainFrame::OnPaint3D;
	
	wxMenu *FileMenu = new wxMenu;
    wxMenuBar *MenuBar = new wxMenuBar;

    FileMenu->Append(ID_MAINWIN_QUIT, _("&Quit\tALT-F4"));
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
	Vektor vZentrum(0, 0, 0);
	for(int i = 0; i < anzPartikel; i++)
	{
		part_lst[i] = new partikel;
		part_lst[i]->ort[0] = (double)(rand() % 2500) / 10.0;
		part_lst[i]->ort[1] = (double)(rand() % 2500) / 10.0;
		part_lst[i]->ort[2] = (double)(rand() % 2500) / 10.0;
		part_lst[i]->masse = (double)(rand() % 30) + 1.0;
		part_lst[i]->radius = part_lst[i]->masse / 5;
		vZentrum += Vektor(part_lst[i]->ort[0], part_lst[i]->ort[1], part_lst[i]->ort[2]);
	}
	vZentrum /= anzPartikel;
	vZentrum += Vektor(-1000, 0, 0);
	m_auge_links = new Kamera(vZentrum, 0, 0, 100, 1);
	m_auge_links->Verschieben(0, -augenAbstand/2, 0);
	
	m_auge_rechts = new Kamera(vZentrum, 0, 0, 100, 1);
	m_auge_rechts->Verschieben(0, augenAbstand/2, 0);
	
	timer.SetOwner(this, ID_TIMER);
	//timer.Start(timerTick);
	
	m_wertFkt = 1;
	
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
	wxClientDC dc(this);
	alteMousePosition = wxPoint(dc.GetSize().GetWidth()/2, dc.GetSize().GetHeight()/2);
	WarpPointer(alteMousePosition.x, alteMousePosition.y);
	
	if(timer.IsRunning())
	{
		m_menuTimer->SetItemLabel("Starte Timer");
		Unbind(wxEVT_PAINT, AktPaint, this);
		Bind(wxEVT_PAINT, &MainFrame::OnPaintIdle, this);
		timer.Stop();
		Refresh();
		return;
	}
	timer.Start(timerTick);
	m_menuTimer->SetItemLabel("Timer anhalten");
	Bind(wxEVT_PAINT, AktPaint, this);
	
	return;
}

void MainFrame::OnAnsichtWechsel(wxCommandEvent& event)
{
	Unbind(wxEVT_PAINT, AktPaint, this);
	if(AktPaint == &MainFrame::OnPaint3D)
	{
		AktPaint = &MainFrame::OnPaintAnaglyphe;
	}else{
		AktPaint = &MainFrame::OnPaint3D;
	}
	Bind(wxEVT_PAINT, AktPaint, this);
	Refresh();
	return;
}

void MainFrame::OnEraseBackground(wxEraseEvent& event)
{
	return;
}

void MainFrame::OnPaint3D(wxPaintEvent &event)
{
	wxPaintDC dc(this);
	int offsetx, offsety;
	offsetx = dc.GetSize().GetWidth()/2;
	offsety = dc.GetSize().GetHeight()/2;
	dc.SetBrush(wxBrush(dc.GetBackground()));
	dc.DrawRectangle(wxPoint(0, 0), dc.GetSize());
	dc.SetPen(wxPen(wxColor(0, 0, 0)));
	if((m_auge_links == NULL)||(m_auge_rechts == NULL))
	{
		dc.DrawText("Keine Kamera\nvorhanden", dc.GetSize().GetWidth() / 2, dc.GetSize().GetHeight() / 2);
		return;
	}
	
	m_auge_links->SetzeLeinwandBreite(dc.GetSize().GetWidth());
	m_auge_rechts->SetzeLeinwandBreite(dc.GetSize().GetWidth());
	
	Vektor tempOrt;
	Vektor Ansicht;
	Liste<PartikelBild> partBilder_links, partBilder_rechts;
	PartikelBild *pB_l, *pB_r;
	int malRadius;
	
	for(int i = 0; i < anzPartikel; i++)
	{
		tempOrt = Vektor(part_lst[i]->ort);
		Ansicht = m_auge_links->Aufnahme(tempOrt);
		Ansicht += Vektor(offsetx - 200, offsety, 0);

		malRadius = part_lst[i]->radius * Ansicht.z();
		if(malRadius < 1)malRadius = 1;
		pB_l = new struct PartikelBild;
		pB_l->ort = Ansicht;
		pB_l->radius = malRadius;
		pB_l->entfernung = -Ansicht.z();

		partBilder_links.Hinzufuegen(pB_l, false);

		Ansicht = m_auge_rechts->Aufnahme(tempOrt);
		Ansicht += Vektor(offsetx + 200, offsety, 0);

		malRadius = part_lst[i]->radius * Ansicht.z();
		if(malRadius < 1)malRadius = 1;
		pB_r = new struct PartikelBild;
		pB_r->ort = Ansicht;
		pB_r->radius = malRadius;
		pB_r->entfernung = -Ansicht.z();

		partBilder_rechts.Hinzufuegen(pB_r, false);
	}

	partBilder_links.ListeNachWertSortieren(&WertErmitteln);
	partBilder_rechts.ListeNachWertSortieren(&WertErmitteln);
	
	for(PartikelBild* aktPB = partBilder_links.GetErstesElement(); aktPB != NULL; aktPB = partBilder_links.GetNaechstesElement())
	{
		if(aktPB->entfernung < 0)dc.DrawCircle(aktPB->ort.x(), aktPB->ort.y(), aktPB->radius);
	}
	for(PartikelBild* aktPB = partBilder_rechts.GetErstesElement(); aktPB != NULL; aktPB = partBilder_rechts.GetNaechstesElement())
	{
		if(aktPB->entfernung < 0)dc.DrawCircle(aktPB->ort.x(), aktPB->ort.y(), aktPB->radius);
	}
	
	partBilder_links.ListeLoeschen("3D");
	partBilder_rechts.ListeLoeschen("3D");
	
	return;
}

void MainFrame::OnPaintAnaglyphe(wxPaintEvent &event)
{
	wxPaintDC dc(this);
	int offsetx, offsety;
	offsetx = dc.GetSize().GetWidth()/2;
	offsety = dc.GetSize().GetHeight()/2;
	dc.SetPen(wxPen(wxColor(0, 0, 0)));
	if((m_auge_links == NULL)||(m_auge_rechts == NULL))
	{
		dc.DrawText("Keine Kamera\nvorhanden", dc.GetSize().GetWidth() / 2, dc.GetSize().GetHeight() / 2);
		return;
	}
	
	m_auge_links->SetzeLeinwandBreite(dc.GetSize().GetWidth());
	m_auge_rechts->SetzeLeinwandBreite(dc.GetSize().GetWidth());
	
	Vektor tempOrt;
	Vektor Ansicht;
	Liste<PartikelBild> partBilderL, partBilderR;
	PartikelBild *pB;
	int malRadius;

	for(int i = 0; i < anzPartikel; i++)
	{
		tempOrt = Vektor(part_lst[i]->ort);
		Ansicht = m_auge_links->Aufnahme(tempOrt);
		Ansicht += Vektor(offsetx, offsety, 0);
		
		malRadius = part_lst[i]->radius * Ansicht.z();
		if(malRadius < 1)malRadius = 1;
		pB = new struct PartikelBild;
		pB->ort = Ansicht;
		pB->radius = malRadius;
		pB->entfernung = -Ansicht.z();
		
		partBilderL.Hinzufuegen(pB, false);
		
		tempOrt = Vektor(part_lst[i]->ort);
		Ansicht = m_auge_rechts->Aufnahme(tempOrt);
		Ansicht += Vektor(offsetx, offsety, 0);
		
		malRadius = part_lst[i]->radius * Ansicht.z();
		if(malRadius < 1)malRadius = 1;
		pB = new struct PartikelBild;
		pB->ort = Ansicht;
		pB->radius = malRadius;
		pB->entfernung = -Ansicht.z();
		
		partBilderR.Hinzufuegen(pB, false);
	}
	
	partBilderL.ListeNachWertSortieren(&WertErmitteln);
	partBilderR.ListeNachWertSortieren(&WertErmitteln);
	
	wxImage img;
	bool erfolg = img.Create(dc.GetSize());
	if(!erfolg)return;
	
	aruZeichnerR bildR(img.GetData(), img.GetHeight(), img.GetWidth());
	aruZeichnerGB bildGB(img.GetData(), img.GetHeight(), img.GetWidth());
	
	bildR.HintergrundZeichnen(255, 255, 255);
	bildGB.HintergrundZeichnen(255, 255, 255);
	
	bildR.SetzeFarbe(0, 0, 0);
	bildGB.SetzeFarbe(0, 0, 0);
	
	for(PartikelBild* aktPB = partBilderL.GetErstesElement(); aktPB != NULL; aktPB = partBilderL.GetNaechstesElement())
	{
		if(aktPB->entfernung < 0)bildGB.ZeichneKreis(aktPB->ort.x(), aktPB->ort.y(), aktPB->radius);
	}
	for(PartikelBild* aktPB = partBilderR.GetErstesElement(); aktPB != NULL; aktPB = partBilderR.GetNaechstesElement())
	{
		if(aktPB->entfernung < 0)bildR.ZeichneKreis(aktPB->ort.x(), aktPB->ort.y(), aktPB->radius);
	}

	partBilderL.ListeLoeschen("Anaglyphe");
	partBilderR.ListeLoeschen("Anaglyphe");
	
	dc.DrawBitmap(wxBitmap(img), 0, 0);
	return;
}

double WertErmitteln(void* a)
{
	return -((PartikelBild*)(a))->entfernung;
}

void MainFrame::OnPaintIdle(wxPaintEvent& event)
{
	wxPaintDC dc(this);
	dc.SetBrush(wxBrush(dc.GetBackground()));
	dc.DrawRectangle(wxPoint(0, 0), dc.GetSize());
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
    
	if(event.GetWheelRotation() < 0)
	{
		if(m_ctrl)
		{
			
		}else{
			m_auge_links->Verschieben(0, 1.0 * m_wertFkt, 0);
			m_auge_rechts->Verschieben(0, 1.0 * m_wertFkt, 0);
		}
	}
	if(event.GetWheelRotation() > 0)
	{
		if(m_ctrl)
		{
			
		}else{
			m_auge_links->Verschieben(0, -1.0 * m_wertFkt, 0);
			m_auge_rechts->Verschieben(0, -1.0 * m_wertFkt, 0);
		}
	}

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

void MainFrame::OnMouseLook(wxMouseEvent& event)
{
	wxClientDC dc(this);
	wxPoint neueMousePosition = event.GetLogicalPosition(dc);
	
	m_auge_links->Verschieben(0, augenAbstand/2, 0);
	m_auge_links->Drehen((neueMousePosition.y-alteMousePosition.y)*0.001, (-neueMousePosition.x+alteMousePosition.x)*0.001);
	m_auge_links->Verschieben(0, -augenAbstand/2, 0);

	m_auge_rechts->Verschieben(0, -augenAbstand/2, 0);
	m_auge_rechts->Drehen((neueMousePosition.y-alteMousePosition.y)*0.001, (-neueMousePosition.x+alteMousePosition.x)*0.001);
	m_auge_rechts->Verschieben(0, augenAbstand/2, 0);

	WarpPointer(alteMousePosition.x, alteMousePosition.y);
	if(!(timer.IsRunning()))Refresh();
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

void MainFrame::OnRightClick(wxMouseEvent& event)
{
	if(timer.IsRunning())
	{
		wxClientDC dc(this);
		alteMousePosition = event.GetLogicalPosition(dc);
		Unbind(wxEVT_MOTION, &MainFrame::OnMouseMove, this);
		Bind(wxEVT_MOTION, &MainFrame::OnMouseLook, this);
		SetCursor(wxCURSOR_BLANK);
	}
	event.Skip();
    return;
}

void MainFrame::OnRightUp(wxMouseEvent& event)
{
	if(timer.IsRunning())
	{
		Unbind(wxEVT_MOTION, &MainFrame::OnMouseLook, this);
		Bind(wxEVT_MOTION, &MainFrame::OnMouseMove, this);
		SetCursor(wxCURSOR_ARROW);
	}
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
		m_wertFkt = 10.0;
	}
	if(event.GetKeyCode() == WXK_CONTROL)
	{
		m_ctrl = true;
	}
	if(event.GetKeyCode() == WXK_SPACE)
	{
		m_auge_links->Verschieben(0, 0, -1.0 * m_wertFkt);
		m_auge_rechts->Verschieben(0, 0, -1.0 * m_wertFkt);
	}
	if(event.GetKeyCode() == WXK_CONTROL)
	{
		m_auge_links->Verschieben(0, 0, 1.0 * m_wertFkt);
		m_auge_rechts->Verschieben(0, 0, 1.0 * m_wertFkt);
	}
	if(event.GetKeyCode() == 'W')
	{
		m_auge_links->Verschieben(1.0 * m_wertFkt, 0, 0);
		m_auge_rechts->Verschieben(1.0 * m_wertFkt, 0, 0);
	}
	if(event.GetKeyCode() == 'S')
	{
		m_auge_links->Verschieben(-1.0 * m_wertFkt, 0, 0);
		m_auge_rechts->Verschieben(-1.0 * m_wertFkt, 0, 0);		
	}
	if(event.GetKeyCode() == 'A')
	{
		m_auge_links->Verschieben(0, -1.0 * m_wertFkt, 0);
		m_auge_rechts->Verschieben(0, -1.0 * m_wertFkt, 0);		
	}
	if(event.GetKeyCode() == 'D')
	{
		m_auge_links->Verschieben(0, 1.0 * m_wertFkt, 0);
		m_auge_rechts->Verschieben(0, 1.0 * m_wertFkt, 0);		
	}
	if(event.GetKeyCode() == 'O')
	{
		m_auge_links->FOV(m_auge_links->FOV() + 1.0 * m_wertFkt);
		m_auge_rechts->FOV(m_auge_rechts->FOV() + 1.0 * m_wertFkt);		
	}
	if(event.GetKeyCode() == 'P')
	{
		m_auge_links->FOV(m_auge_links->FOV() - 1.0 * m_wertFkt);
		m_auge_rechts->FOV(m_auge_rechts->FOV() - 1.0 * m_wertFkt);
	}
	SetStatusText(wxString::Format("Auge_links: %.3f | %.3f | %.3f -- FOV = %.2f",
									m_auge_links->HoleOrt().x(), m_auge_links->HoleOrt().y(), m_auge_links->HoleOrt().z(),
									m_auge_links->FOV()));
	Refresh();
	return;
}

void MainFrame::OnKeyUp(wxKeyEvent& event)
{
	if(event.GetKeyCode() == WXK_SHIFT)
	{
		m_shift = false;
		m_wertFkt = 1.0;
	}
	if(event.GetKeyCode() == WXK_CONTROL)
	{
		m_ctrl = false;
	}
	if(event.GetKeyCode() == '+')
	{
		augenAbstand += m_wertFkt * 1;
		SetStatusText(wxString::Format("Augenabstand = %.2f", augenAbstand));
	}
	if(event.GetKeyCode() == '-')
	{
		augenAbstand -= m_wertFkt * 1;
		SetStatusText(wxString::Format("Augenabstand = %.2f", augenAbstand));
	}
	return;
}