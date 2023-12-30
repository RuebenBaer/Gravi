#include "ProgrammEinstellungenDlg.h"
#include "../Dbl_Eingabe/Dbl_Eingabe.h"

void KommaGegenPunkt(wxString *Txt)
{
	for(unsigned int i=0; i<Txt->Len(); i++)
	{
		if(Txt->GetChar(i) == ',') Txt->SetChar(i, '.');
	}
	return;
}

/*Programm_Einstellungen_Dialog*/
BEGIN_EVENT_TABLE(Programm_Einstellungen_Dialog, wxDialog)
    EVT_CLOSE(Programm_Einstellungen_Dialog::OnClose)
    EVT_TEXT(wxID_ANY, Programm_Einstellungen_Dialog::OnTextChange)
    EVT_TEXT_ENTER(wxID_ANY, Programm_Einstellungen_Dialog::OnTextChange)
    EVT_BUTTON(wxID_OK, Programm_Einstellungen_Dialog::OnOKButton)
END_EVENT_TABLE()

Programm_Einstellungen_Dialog::Programm_Einstellungen_Dialog(wxWindow* parent):wxDialog(parent, wxID_ANY, wxT("Allgmeine Programmeinstellungen"))
{
    m_mama = parent;
    PEDialogIni();

    wxBoxSizer *topsizer = new wxBoxSizer(wxVERTICAL);

    wxBoxSizer *parameterSizer = new wxBoxSizer(wxHORIZONTAL);

    /*Programmsteuerung*/
    wxBoxSizer *steuerungsSizer = new wxBoxSizer(wxVERTICAL);
    steuerungsSizer->Add(new wxTextCtrl(this, -1, wxT("Programmparameter und -einstellungen"), wxDefaultPosition, wxDefaultSize, wxTE_READONLY|wxBORDER_NONE),0, wxEXPAND|wxALL, 5);

	/*Anwendungsspezifische Felder*/
    wxBoxSizer *wGraviKonstSizer = new wxBoxSizer(wxHORIZONTAL);
    wGraviKonstSizer->Add(new wxTextCtrl(this, -1, wxT("Gravitationskonstante"), wxDefaultPosition, wxSize(180, 20), wxTE_READONLY|wxBORDER_NONE|wxTE_BESTWRAP),0, wxEXPAND|wxALL, 5);
    aruDblTxtCtrl *wGraviKonstCtrl = new aruDblTxtCtrl(this, IDwGraviKonst, wxString::Format(wxT("%.2f"), pe_wGraviKonst), wxDefaultPosition, wxSize(50, 20),
                                                         wxTE_PROCESS_ENTER|wxTE_RIGHT|wxBORDER_SIMPLE|wxTE_NOHIDESEL, wxDefaultValidator, wxT("wGraviKonstCtrl"));
    wGraviKonstSizer->Add(wGraviKonstCtrl, 0, wxALL, 5);
    steuerungsSizer->Add(wGraviKonstSizer, 1, wxEXPAND, 5);

    wxBoxSizer *wTimerTickSizer = new wxBoxSizer(wxHORIZONTAL);
    wTimerTickSizer->Add(new wxTextCtrl(this, -1, wxT("Timertick [ms]"), wxDefaultPosition, wxSize(180, 20), wxTE_READONLY|wxBORDER_NONE|wxTE_BESTWRAP),0, wxEXPAND|wxALL, 5);
    aruDblTxtCtrl *wTimerTickCtrl = new aruDblTxtCtrl(this, IDwTimerTick, wxString::Format(wxT("%.2f"), pe_wTimerTick), wxDefaultPosition, wxSize(50, 20),
                                                         wxTE_PROCESS_ENTER|wxTE_RIGHT|wxBORDER_SIMPLE|wxTE_NOHIDESEL, wxDefaultValidator, wxT("wTimerTickCtrl"));
    wTimerTickSizer->Add(wTimerTickCtrl, 0, wxALL, 5);
    steuerungsSizer->Add(wTimerTickSizer, 1, wxEXPAND, 5);
    /*ENDE Programmsteuerung*/

    /*Farben*/
    wxBoxSizer *farbenSizer = new wxBoxSizer(wxVERTICAL);
    farbenSizer->Add(new wxTextCtrl(this, -1, wxT("Farbauswahl"), wxDefaultPosition, wxDefaultSize, wxTE_READONLY|wxBORDER_NONE), 0, wxEXPAND|wxALL, 5);

    wxBoxSizer *farbe1Sizer = new wxBoxSizer(wxHORIZONTAL);
        farbe1Sizer->Add(new wxTextCtrl(this, -1, wxT("Farbe 1"), wxDefaultPosition,  wxSize(150, 20), wxTE_READONLY|wxBORDER_NONE),0, wxALL, 5);
            wxButton *farbe1Button = new wxButton(this, IDfarbe1, wxEmptyString, wxDefaultPosition, wxSize(20, 20), wxBORDER_NONE);
                farbe1Button->SetBackgroundColour(pe_farbe1);
            Bind(wxEVT_BUTTON, &Programm_Einstellungen_Dialog::OnColourButton, this, IDfarbe1);
        farbe1Sizer->Add(farbe1Button, 0,wxALL, 5);
    farbenSizer->Add(farbe1Sizer, 1, wxEXPAND, 5);

    wxBoxSizer *farbe2Sizer = new wxBoxSizer(wxHORIZONTAL);
        farbe2Sizer->Add(new wxTextCtrl(this, -1, wxT("Farbe 2"), wxDefaultPosition,  wxSize(150, 20), wxTE_READONLY|wxBORDER_NONE),0, wxALL, 5);
            wxButton *farbe2Button = new wxButton(this, IDfarbe2, wxEmptyString, wxDefaultPosition, wxSize(20, 20), wxBORDER_NONE);
                farbe2Button->SetBackgroundColour(pe_farbe2);
            Bind(wxEVT_BUTTON, &Programm_Einstellungen_Dialog::OnColourButton, this, IDfarbe2);
        farbe2Sizer->Add(farbe2Button, 0,wxALL, 5);
    farbenSizer->Add(farbe2Sizer, 1, wxEXPAND, 5);
    /*ENDE Farben*/


    topsizer->Add(new wxTextCtrl(this, -1, wxT("Einstellungen"), wxDefaultPosition, wxDefaultSize, wxTE_READONLY|wxBORDER_NONE),0, wxEXPAND|wxALL, 5);
    parameterSizer->Add(steuerungsSizer, 0, 0, 5);
    parameterSizer->Add(farbenSizer, 0, 0, 5);
    topsizer->Add(parameterSizer, 0, wxEXPAND, 5);
    topsizer->Add(new wxButton(this, wxID_OK, wxT("OK")), 0, wxSHAPED|wxRIGHT, 5);

    SetSizerAndFit(topsizer);
    SetEscapeId(wxID_CANCEL);
}

Programm_Einstellungen_Dialog::~Programm_Einstellungen_Dialog()
{

}

void Programm_Einstellungen_Dialog::OnClose(wxCloseEvent &event)
{
    IniSpeichern();
    event.Skip();
    return;
}

void Programm_Einstellungen_Dialog::PEDialogIni(void)
{
    /*Standardwerte setzen*/
    pe_wGraviKonst = 0.01;	//Beschreibung Wert 1
    pe_wTimerTick = 1.0;		//Beschreibung Wert 2

    pe_farbe1 = wxColour(0, 0, 0);			//Beschreibung Farbe 1
    pe_farbe2 = wxColour(74, 186, 240);	//Beschreibung Farbe 2

    char Zeile[50];
	std::ifstream PE_Parameter_Ini_Datei("Programmeinstellungen.ini", std::ios::in);
	if(PE_Parameter_Ini_Datei.good())
	{
	    double r, g, b;
		while(!PE_Parameter_Ini_Datei.eof())
		{
			PE_Parameter_Ini_Datei.getline(Zeile,50,':');
			if(!strcmp(Zeile,"wGraviKonst"))
			{
				PE_Parameter_Ini_Datei.getline(Zeile,50);
				pe_wGraviKonst = atof(Zeile);
				continue;
			}
			if(!strcmp(Zeile,"wTimerTick"))
			{
				PE_Parameter_Ini_Datei.getline(Zeile,50);
				pe_wTimerTick = atof(Zeile);
				continue;
			}
            if(!strcmp(Zeile,"farbe1"))
            {
				PE_Parameter_Ini_Datei.getline(Zeile,50,',');
				r = atof(Zeile);
				PE_Parameter_Ini_Datei.getline(Zeile,50,',');
				g = atof(Zeile);
				PE_Parameter_Ini_Datei.getline(Zeile,50);
				b = atof(Zeile);
                pe_farbe1 = wxColour(r, g, b);
				continue;
			}
            if(!strcmp(Zeile,"farbe2"))
            {
				PE_Parameter_Ini_Datei.getline(Zeile,50,',');
				r = atof(Zeile);
				PE_Parameter_Ini_Datei.getline(Zeile,50,',');
				g = atof(Zeile);
				PE_Parameter_Ini_Datei.getline(Zeile,50);
				b = atof(Zeile);
                pe_farbe2 = wxColour(r, g, b);
				continue;
			}
		}
		PE_Parameter_Ini_Datei.close();
	}
	else{
        wxMessageDialog(m_mama, wxString("Keine Ini-Datei\nStandardwerte werden gespeichert")).ShowModal();
        IniSpeichern();
	}
    return;
}

void Programm_Einstellungen_Dialog::OnOKButton(wxCommandEvent &event)
{
    IniSpeichern();
    event.Skip();
    return;
}

void Programm_Einstellungen_Dialog::OnTextChange(wxCommandEvent &event)
{
    wxString inhalt = event.GetString();
    KommaGegenPunkt(&inhalt);
    int textFeldID = event.GetId();
    double uebergabe = -1;
    switch(textFeldID)
    {
    case IDwGraviKonst:
        uebergabe = pe_wGraviKonst = atof(inhalt);
        break;
    case IDwTimerTick:
        uebergabe = pe_wTimerTick = atof(inhalt);
        break;
    default:
        return;
    }
    aruDblEvent myevent;
    myevent.SetzeWert(uebergabe);
    myevent.SetId(event.GetId());
    m_mama->GetEventHandler()->AddPendingEvent(myevent);
    return;
}

void Programm_Einstellungen_Dialog::OnColourButton(wxCommandEvent &event)
{
    wxColour farb;
    int ButtonID = event.GetId();
    wxColour farbUebergabe;
    wxString Title;
    switch(ButtonID)
    {
    case IDfarbe1:
        farbUebergabe = pe_farbe1;
        Title = wxT("Farbe 1");
        break;
    case IDfarbe2:
        farbUebergabe = pe_farbe2;
        Title = wxT("Farbe 2");
        break;
    default:
        break;
    }
    wxColourData farbDaten;
    farbDaten.SetColour(farbUebergabe);
    wxColourDialog CoDi((wxWindow*)this, &farbDaten);
    CoDi.SetTitle(Title);
    CoDi.ShowModal();
    farbDaten = CoDi.GetColourData();
    farbUebergabe = farbDaten.GetColour();

    static_cast<wxButton*>(event.GetEventObject())->SetBackgroundColour(farbUebergabe);

    switch(ButtonID)
    {
    case IDfarbe1:
        pe_farbe1 = farbUebergabe;
        break;
    case IDfarbe2:
        pe_farbe2 = farbUebergabe;
        break;
    default:
        break;
    }

    aruColourEvent myevent;
    myevent.SetzeWert(farbUebergabe);
    myevent.SetInt(event.GetId());
    m_mama->GetEventHandler()->AddPendingEvent(myevent);
    return;
}

void Programm_Einstellungen_Dialog::IniSpeichern(void)
{
    std::ofstream Neue_Ini_Datei("Programmeinstellungen.ini", std::ios::out|std::ios_base::trunc);
    if(Neue_Ini_Datei.good())
    {
        Neue_Ini_Datei<<"wGraviKonst:"<<pe_wGraviKonst<<"\n";
        Neue_Ini_Datei<<"wTimerTick:"<<pe_wTimerTick<<"\n";
        Neue_Ini_Datei<<"farbe1:"<<(int)pe_farbe1.Red()<<","<<(int)pe_farbe1.Green()<<","<<(int)pe_farbe1.Blue()<<"\n";
        Neue_Ini_Datei<<"farbe2:"<<(int)pe_farbe2.Red()<<","<<(int)pe_farbe2.Green()<<","<<(int)pe_farbe2.Blue()<<"\n";
        Neue_Ini_Datei.close();
    }
    return;
}

double Programm_Einstellungen_Dialog::HoleWert(programmEinstellungID retID) const
{
    switch (retID)
    {
    case IDwGraviKonst:
        return pe_wGraviKonst;
    case IDwTimerTick:
        return pe_wTimerTick;
	default:
        break;
    }
    return 0.0;
}

wxColour Programm_Einstellungen_Dialog::HoleFarbe(programmEinstellungID retID) const
{
    switch (retID)
    {
    case IDfarbe1:
        return pe_farbe1;
    case IDfarbe2:
        return pe_farbe2;
    default:
        break;
    }
    return wxColour(0, 0, 0);
}
/*ENDE Programm_Einstellungen_Dialog*/