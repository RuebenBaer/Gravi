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
    steuerungsSizer->Add(new wxTextCtrl(this, -1, wxT("Programmsteuerung"), wxDefaultPosition, wxDefaultSize, wxTE_READONLY|wxBORDER_NONE),0, wxEXPAND|wxALL, 5);

    wxBoxSizer *verschubWeiteSizer = new wxBoxSizer(wxHORIZONTAL);
    verschubWeiteSizer->Add(new wxTextCtrl(this, -1, wxT("Schrittweite Verschub"), wxDefaultPosition, wxSize(180, 20), wxTE_READONLY|wxBORDER_NONE|wxTE_BESTWRAP),0, wxEXPAND|wxALL, 5);
    aruDblTxtCtrl *verschubWeiteCtrl = new aruDblTxtCtrl(this, IDverschubWeite, wxString::Format(wxT("%.2f"), pe_verschubWeite), wxDefaultPosition, wxSize(50, 20),
                                                         wxTE_PROCESS_ENTER|wxTE_RIGHT|wxBORDER_SIMPLE|wxTE_NOHIDESEL, wxDefaultValidator, wxT("verschubWeiteCtrl"));
    verschubWeiteSizer->Add(verschubWeiteCtrl, 0, wxALL, 5);
    steuerungsSizer->Add(verschubWeiteSizer, 1, wxEXPAND, 5);

    wxBoxSizer *pxSuchEntfernungSizer = new wxBoxSizer(wxHORIZONTAL);
    pxSuchEntfernungSizer->Add(new wxTextCtrl(this, -1, wxT("max. Abstand Markierung (px)"), wxDefaultPosition,  wxSize(180, 20), wxTE_READONLY|wxBORDER_NONE|wxTE_BESTWRAP),0, wxEXPAND|wxALL, 5);
    aruDblTxtCtrl *pxSuchEntfernungCtrl = new aruDblTxtCtrl(this, IDpxSuchEntfernung, wxString::Format(wxT("%.2f"), pe_pxSuchEntfernung), wxDefaultPosition, wxSize(50, 20),
                                                         wxTE_PROCESS_ENTER|wxTE_RIGHT|wxBORDER_SIMPLE|wxTE_NOHIDESEL, wxDefaultValidator, wxT("pxSuchEntfernungCtrl"));
    pxSuchEntfernungSizer->Add(pxSuchEntfernungCtrl, 0, wxALL, 5);
    steuerungsSizer->Add(pxSuchEntfernungSizer, 1, wxEXPAND, 5);

    wxBoxSizer *lnWandelGenauigkeitSizer = new wxBoxSizer(wxHORIZONTAL);
    lnWandelGenauigkeitSizer->Add(new wxTextCtrl(this, -1, wxT("Genauigkeit Strich->Linie"), wxDefaultPosition,  wxSize(180, 20), wxTE_READONLY|wxBORDER_NONE|wxTE_BESTWRAP),0, wxEXPAND|wxALL, 5);
    aruDblTxtCtrl *lnWandelGenauigkeitCtrl = new aruDblTxtCtrl(this, IDlnWandelGenauigkeit, wxString::Format(wxT("%.2f"), pe_lnWandelGenauigkeit), wxDefaultPosition, wxSize(50, 20),
                                                         wxTE_PROCESS_ENTER|wxTE_RIGHT|wxBORDER_SIMPLE|wxTE_NOHIDESEL, wxDefaultValidator, wxT("lnWandelGenauigkeitCtrl"));
    lnWandelGenauigkeitSizer->Add(lnWandelGenauigkeitCtrl, 0, wxALL, 5);
    steuerungsSizer->Add(lnWandelGenauigkeitSizer, 1, wxEXPAND, 5);

    wxBoxSizer *anzeigeGenauigkeitSizer = new wxBoxSizer(wxHORIZONTAL);
    anzeigeGenauigkeitSizer->Add(new wxTextCtrl(this, -1, wxT("Anzeigegenauigkeit (Nachkommastellen Zahlen)"), wxDefaultPosition,  wxSize(180, 20), wxTE_READONLY|wxBORDER_NONE|wxTE_BESTWRAP),0, wxEXPAND|wxALL, 5);
    aruDblTxtCtrl *anzeigeGenauigkeitCtrl = new aruDblTxtCtrl(this, IDanzeigeGenauigkeit, wxString::Format(wxT("%.2f"), pe_anzeigeGenauigkeit), wxDefaultPosition, wxSize(50, 20),
                                                         wxTE_PROCESS_ENTER|wxTE_RIGHT|wxBORDER_SIMPLE|wxTE_NOHIDESEL, wxDefaultValidator, wxT("anzeigeGenauigkeitCtrl"));
    anzeigeGenauigkeitSizer->Add(anzeigeGenauigkeitCtrl, 0, wxALL, 5);
    steuerungsSizer->Add(anzeigeGenauigkeitSizer, 1, wxEXPAND, 5);

    wxBoxSizer *pseudoSchattenFktSizer = new wxBoxSizer(wxHORIZONTAL);
    pseudoSchattenFktSizer->Add(new wxTextCtrl(this, -1, wxT("Pseudoschatten anpassen"), wxDefaultPosition,  wxSize(180, 20), wxTE_READONLY|wxBORDER_NONE|wxTE_BESTWRAP),0, wxEXPAND|wxALL, 5);
    aruDblTxtCtrl *pseudoSchattenFktCtrl = new aruDblTxtCtrl(this, IDpseudoSchattenFkt, wxString::Format(wxT("%.2f"), pe_pseudoSchattenFkt), wxDefaultPosition, wxSize(50, 20),
                                                         wxTE_PROCESS_ENTER|wxTE_RIGHT|wxBORDER_SIMPLE|wxTE_NOHIDESEL, wxDefaultValidator, wxT("pseudoSchattenFktCtrl"));
    pseudoSchattenFktSizer->Add(pseudoSchattenFktCtrl, 0, wxALL, 5);
    steuerungsSizer->Add(pseudoSchattenFktSizer, 1, wxEXPAND, 5);

    wxBoxSizer *gefaelleRasterSizer = new wxBoxSizer(wxHORIZONTAL);
    gefaelleRasterSizer->Add(new wxTextCtrl(this, -1, wxT("Rastergröße Gefälle"), wxDefaultPosition,  wxSize(180, 20), wxTE_READONLY|wxBORDER_NONE|wxTE_BESTWRAP),0, wxEXPAND|wxALL, 5);
    aruDblTxtCtrl *rasterGroesseCtrl = new aruDblTxtCtrl(this, IDgefaelleRasterGroesse, wxString::Format(wxT("%.2f"), pe_gefaelleRasterGroesse), wxDefaultPosition, wxSize(50, 20),
                                                         wxTE_PROCESS_ENTER|wxTE_RIGHT|wxBORDER_SIMPLE|wxTE_NOHIDESEL, wxDefaultValidator, wxT("rasterGroesseCtrl"));
    gefaelleRasterSizer->Add(rasterGroesseCtrl, 0, wxALL, 5);
    steuerungsSizer->Add(gefaelleRasterSizer, 1, wxEXPAND, 5);

    wxBoxSizer *gefaelleMinimumSizer = new wxBoxSizer(wxHORIZONTAL);
    gefaelleMinimumSizer->Add(new wxTextCtrl(this, -1, wxT("Mindestgefälle [%]"), wxDefaultPosition,  wxSize(180, 20), wxTE_READONLY|wxBORDER_NONE|wxTE_BESTWRAP),0, wxEXPAND|wxALL, 5);
    aruDblTxtCtrl *gefaelleMinimumCtrl = new aruDblTxtCtrl(this, IDgefaelleMinimum, wxString::Format(wxT("%.2f"), pe_gefaelleMinimum), wxDefaultPosition, wxSize(50, 20),
                                                         wxTE_PROCESS_ENTER|wxTE_RIGHT|wxBORDER_SIMPLE|wxTE_NOHIDESEL, wxDefaultValidator, wxT("gefaelleMinimumCtrl"));
    gefaelleMinimumSizer->Add(gefaelleMinimumCtrl, 0, wxALL, 5);
    steuerungsSizer->Add(gefaelleMinimumSizer, 1, wxEXPAND, 5);

    wxBoxSizer *gefaelleOptimumSizer = new wxBoxSizer(wxHORIZONTAL);
    gefaelleOptimumSizer->Add(new wxTextCtrl(this, -1, wxT("optimales Gefälle [%]"), wxDefaultPosition,  wxSize(180, 20), wxTE_READONLY|wxBORDER_NONE|wxTE_BESTWRAP),0, wxEXPAND|wxALL, 5);
    aruDblTxtCtrl *gefaelleOptimumCtrl = new aruDblTxtCtrl(this, IDgefaelleOptimum, wxString::Format(wxT("%.2f"), pe_gefaelleOptimum), wxDefaultPosition, wxSize(50, 20),
                                                         wxTE_PROCESS_ENTER|wxTE_RIGHT|wxBORDER_SIMPLE|wxTE_NOHIDESEL, wxDefaultValidator, wxT("gefaelleOptimumCtrl"));
    gefaelleOptimumSizer->Add(gefaelleOptimumCtrl, 0, wxALL, 5);
    steuerungsSizer->Add(gefaelleOptimumSizer, 1, wxEXPAND, 5);

    wxBoxSizer *gefaelleMaximumSizer = new wxBoxSizer(wxHORIZONTAL);
    gefaelleMaximumSizer->Add(new wxTextCtrl(this, -1, wxT("Maximalgefälle [%]"), wxDefaultPosition,  wxSize(180, 20), wxTE_READONLY|wxBORDER_NONE|wxTE_BESTWRAP),0, wxEXPAND|wxALL, 5);
    aruDblTxtCtrl *gefaelleMaximumCtrl = new aruDblTxtCtrl(this, IDgefaelleMaximum, wxString::Format(wxT("%.2f"), pe_gefaelleMaximum), wxDefaultPosition, wxSize(50, 20),
                                                         wxTE_PROCESS_ENTER|wxTE_RIGHT|wxBORDER_SIMPLE|wxTE_NOHIDESEL, wxDefaultValidator, wxT("gefaelleMaximumCtrl"));
    gefaelleMaximumSizer->Add(gefaelleMaximumCtrl, 0, wxALL, 5);
    steuerungsSizer->Add(gefaelleMaximumSizer, 1, wxEXPAND, 5);

    wxBoxSizer *flaechenRasterSizer = new wxBoxSizer(wxHORIZONTAL);
    flaechenRasterSizer->Add(new wxTextCtrl(this, -1, wxT("Rastergröße Flächenberechnung"), wxDefaultPosition,  wxSize(180, 20), wxTE_READONLY|wxBORDER_NONE|wxTE_BESTWRAP),0, wxEXPAND|wxALL, 5);
    aruDblTxtCtrl *flaechenGroesseCtrl = new aruDblTxtCtrl(this, IDflaechenRasterGroesse, wxString::Format(wxT("%.2f"), pe_flaechenRasterGroesse), wxDefaultPosition, wxSize(50, 20),
                                                         wxTE_PROCESS_ENTER|wxTE_RIGHT|wxBORDER_SIMPLE|wxTE_NOHIDESEL, wxDefaultValidator, wxT("flaechenGroesseCtrl"));
    flaechenRasterSizer->Add(flaechenGroesseCtrl, 0, wxALL, 5);
    steuerungsSizer->Add(flaechenRasterSizer, 1, wxEXPAND, 5);
    /*ENDE Programmsteuerung*/

    /*Farben*/
    wxBoxSizer *farbenSizer = new wxBoxSizer(wxVERTICAL);
    farbenSizer->Add(new wxTextCtrl(this, -1, wxT("Farbauswahl"), wxDefaultPosition, wxDefaultSize, wxTE_READONLY|wxBORDER_NONE), 0, wxEXPAND|wxALL, 5);

    wxBoxSizer *col_Pkt_Ln_Sizer = new wxBoxSizer(wxHORIZONTAL);
        col_Pkt_Ln_Sizer->Add(new wxTextCtrl(this, -1, wxT("Punkte und Linien"), wxDefaultPosition,  wxSize(150, 20), wxTE_READONLY|wxBORDER_NONE),0, wxALL, 5);
            wxButton *col_Pkt_Ln_Button = new wxButton(this, IDFarbePktLn, wxEmptyString, wxDefaultPosition, wxSize(20, 20), wxBORDER_NONE);
                col_Pkt_Ln_Button->SetBackgroundColour(pe_FarbePktLn);
            Bind(wxEVT_BUTTON, &Programm_Einstellungen_Dialog::OnColourButton, this, IDFarbePktLn);
        col_Pkt_Ln_Sizer->Add(col_Pkt_Ln_Button, 0,wxALL, 5);
    farbenSizer->Add(col_Pkt_Ln_Sizer, 1, wxEXPAND, 5);

    wxBoxSizer *col_Strich_Sizer = new wxBoxSizer(wxHORIZONTAL);
        col_Strich_Sizer->Add(new wxTextCtrl(this, -1, wxT("Striche"), wxDefaultPosition,  wxSize(150, 20), wxTE_READONLY|wxBORDER_NONE),0, wxALL, 5);
            wxButton *col_Strich_Button = new wxButton(this, IDFarbeStrich, wxEmptyString, wxDefaultPosition, wxSize(20, 20), wxBORDER_NONE);
                col_Strich_Button->SetBackgroundColour(pe_FarbeStrich);
            Bind(wxEVT_BUTTON, &Programm_Einstellungen_Dialog::OnColourButton, this, IDFarbeStrich);
        col_Strich_Sizer->Add(col_Strich_Button, 0,wxALL, 5);
    farbenSizer->Add(col_Strich_Sizer, 1, wxEXPAND, 5);

    wxBoxSizer *col_HM_Sizer = new wxBoxSizer(wxHORIZONTAL);
        col_HM_Sizer->Add(new wxTextCtrl(this, -1, wxT("Höhenmarken"), wxDefaultPosition,  wxSize(150, 20), wxTE_READONLY|wxBORDER_NONE),0, wxALL, 5);
            wxButton *col_HM_Button = new wxButton(this, IDFarbeHoehenMarke, wxEmptyString, wxDefaultPosition, wxSize(20, 20), wxBORDER_NONE);
                col_HM_Button->SetBackgroundColour(pe_FarbeHoehenMarke);
            Bind(wxEVT_BUTTON, &Programm_Einstellungen_Dialog::OnColourButton, this, IDFarbeHoehenMarke);
        col_HM_Sizer->Add(col_HM_Button, 0,wxALL, 5);
    farbenSizer->Add(col_HM_Sizer, 1, wxEXPAND, 5);

    wxBoxSizer *col_HL_Sizer = new wxBoxSizer(wxHORIZONTAL);
        col_HL_Sizer->Add(new wxTextCtrl(this, -1, wxT("Höhenlinien"), wxDefaultPosition,  wxSize(150, 20), wxTE_READONLY|wxBORDER_NONE),0, wxALL, 5);
            wxButton *col_HL_Button = new wxButton(this, IDFarbeHoehenlinie, wxEmptyString, wxDefaultPosition, wxSize(20, 20), wxBORDER_NONE);
                col_HL_Button->SetBackgroundColour(pe_FarbeHoehenlinie);
            Bind(wxEVT_BUTTON, &Programm_Einstellungen_Dialog::OnColourButton, this, IDFarbeHoehenlinie);
        col_HL_Sizer->Add(col_HL_Button, 0,wxALL, 5);
    farbenSizer->Add(col_HL_Sizer, 1, wxEXPAND, 5);

    wxBoxSizer *col_mark_Obj_Sizer = new wxBoxSizer(wxHORIZONTAL);
        col_mark_Obj_Sizer->Add(new wxTextCtrl(this, -1, wxT("Markierte Objekte"), wxDefaultPosition,  wxSize(150, 20), wxTE_READONLY|wxBORDER_NONE),0, wxALL, 5);
            wxButton *col_mark_Obj_Button = new wxButton(this, IDFarbeMarkiertesObjekt, wxEmptyString, wxDefaultPosition, wxSize(20, 20), wxBORDER_NONE);
                col_mark_Obj_Button->SetBackgroundColour(pe_FarbeMarkiertesObjekt);
            Bind(wxEVT_BUTTON, &Programm_Einstellungen_Dialog::OnColourButton, this, IDFarbeMarkiertesObjekt);
        col_mark_Obj_Sizer->Add(col_mark_Obj_Button, 0,wxALL, 5);
    farbenSizer->Add(col_mark_Obj_Sizer, 1, wxEXPAND, 5);

    wxBoxSizer *col_ausgew_Obj_Sizer = new wxBoxSizer(wxHORIZONTAL);
        col_ausgew_Obj_Sizer->Add(new wxTextCtrl(this, -1, wxT("Ausgewählte Objekte"), wxDefaultPosition,  wxSize(150, 20), wxTE_READONLY|wxBORDER_NONE),0, wxALL, 5);
            wxButton *col_ausgew_Obj_Button = new wxButton(this, IDFarbeAusgewaehltesObjekt, wxEmptyString, wxDefaultPosition, wxSize(20, 20), wxBORDER_NONE);
                col_ausgew_Obj_Button->SetBackgroundColour(pe_FarbeAusgewaehltesObjekt);
            Bind(wxEVT_BUTTON, &Programm_Einstellungen_Dialog::OnColourButton, this, IDFarbeAusgewaehltesObjekt);
        col_ausgew_Obj_Sizer->Add(col_ausgew_Obj_Button, 0,wxALL, 5);
    farbenSizer->Add(col_ausgew_Obj_Sizer, 1, wxEXPAND, 5);

    wxBoxSizer *col_flaeche_darueber_Sizer = new wxBoxSizer(wxHORIZONTAL);
        col_flaeche_darueber_Sizer->Add(new wxTextCtrl(this, -1, wxT("Flächen oberhalb"), wxDefaultPosition,  wxSize(150, 20), wxTE_READONLY|wxBORDER_NONE),0, wxALL, 5);
            wxButton *col_flaeche_darueber_Button = new wxButton(this, IDFarbeFlaecheDarueber, wxEmptyString, wxDefaultPosition, wxSize(20, 20), wxBORDER_NONE);
                col_flaeche_darueber_Button->SetBackgroundColour(pe_FarbeFlaecheDarueber);
            Bind(wxEVT_BUTTON, &Programm_Einstellungen_Dialog::OnColourButton, this, IDFarbeFlaecheDarueber);
        col_flaeche_darueber_Sizer->Add(col_flaeche_darueber_Button, 0,wxALL, 5);
    farbenSizer->Add(col_flaeche_darueber_Sizer, 1, wxEXPAND, 5);

    wxBoxSizer *col_flaeche_darunter_Sizer = new wxBoxSizer(wxHORIZONTAL);
        col_flaeche_darunter_Sizer->Add(new wxTextCtrl(this, -1, wxT("Flächen unterhalb"), wxDefaultPosition,  wxSize(150, 20), wxTE_READONLY|wxBORDER_NONE),0, wxALL, 5);
            wxButton *col_flaeche_darunter_Button = new wxButton(this, IDFarbeFlaecheDarunter, wxEmptyString, wxDefaultPosition, wxSize(20, 20), wxBORDER_NONE);
                col_flaeche_darunter_Button->SetBackgroundColour(pe_FarbeFlaecheDarunter);
            Bind(wxEVT_BUTTON, &Programm_Einstellungen_Dialog::OnColourButton, this, IDFarbeFlaecheDarunter);
        col_flaeche_darunter_Sizer->Add(col_flaeche_darunter_Button, 0,wxALL, 5);
    farbenSizer->Add(col_flaeche_darunter_Sizer, 1, wxEXPAND, 5);

    wxBoxSizer *col_Hintergrund_Layer_Sizer = new wxBoxSizer(wxHORIZONTAL);
        col_Hintergrund_Layer_Sizer->Add(new wxTextCtrl(this, -1, wxT("Hintergrundlayer"), wxDefaultPosition,  wxSize(150, 20), wxTE_READONLY|wxBORDER_NONE),0, wxALL, 5);
            wxButton *col_Hintergrund_Layer_Button = new wxButton(this, IDFarbeHintergrundLayer, wxEmptyString, wxDefaultPosition, wxSize(20, 20), wxBORDER_NONE);
                col_Hintergrund_Layer_Button->SetBackgroundColour(pe_FarbeHintergrundLayer);
            Bind(wxEVT_BUTTON, &Programm_Einstellungen_Dialog::OnColourButton, this, IDFarbeHintergrundLayer);
        col_Hintergrund_Layer_Sizer->Add(col_Hintergrund_Layer_Button, 0,wxALL, 5);
    farbenSizer->Add(col_Hintergrund_Layer_Sizer, 1, wxEXPAND, 5);

    wxBoxSizer *col_ZeichenHintergrund_Sizer = new wxBoxSizer(wxHORIZONTAL);
        col_ZeichenHintergrund_Sizer->Add(new wxTextCtrl(this, -1, wxT("Hintergrund Zeichenfl."), wxDefaultPosition,  wxSize(150, 20), wxTE_READONLY|wxBORDER_NONE),0, wxALL, 5);
            wxButton *col_ZeichenHintergrund_Button = new wxButton(this, IDFarbeZeichenHintergrund, wxEmptyString, wxDefaultPosition, wxSize(20, 20), wxBORDER_NONE);
                col_ZeichenHintergrund_Button->SetBackgroundColour(pe_FarbeZeichenHintergrund);
            Bind(wxEVT_BUTTON, &Programm_Einstellungen_Dialog::OnColourButton, this, IDFarbeZeichenHintergrund);
        col_ZeichenHintergrund_Sizer->Add(col_ZeichenHintergrund_Button, 0,wxALL, 5);
    farbenSizer->Add(col_ZeichenHintergrund_Sizer, 1, wxEXPAND, 5);

    wxBoxSizer *col_AuswahlRechteck_Sizer = new wxBoxSizer(wxHORIZONTAL);
        col_AuswahlRechteck_Sizer->Add(new wxTextCtrl(this, -1, wxT("Auswahlrechteck"), wxDefaultPosition,  wxSize(150, 20), wxTE_READONLY|wxBORDER_NONE),0, wxALL, 5);
            wxButton *col_AuswahlRechteck_Button = new wxButton(this, IDFarbeAuswahlRechteck, wxEmptyString, wxDefaultPosition, wxSize(20, 20), wxBORDER_NONE);
                col_AuswahlRechteck_Button->SetBackgroundColour(pe_FarbeAuswahlRechteck);
            Bind(wxEVT_BUTTON, &Programm_Einstellungen_Dialog::OnColourButton, this, IDFarbeAuswahlRechteck);
        col_AuswahlRechteck_Sizer->Add(col_AuswahlRechteck_Button, 0,wxALL, 5);
    farbenSizer->Add(col_AuswahlRechteck_Sizer, 1, wxEXPAND, 5);

    wxBoxSizer *col_Gefaelle_Sizer = new wxBoxSizer(wxHORIZONTAL);
        col_Gefaelle_Sizer->Add(new wxTextCtrl(this, -1, wxT("Gefälle"), wxDefaultPosition,  wxSize(150, 20), wxTE_READONLY|wxBORDER_NONE),0, wxALL, 5);
            wxButton *col_Gefaelle_Button = new wxButton(this, IDFarbeGefaelle, wxEmptyString, wxDefaultPosition, wxSize(20, 20), wxBORDER_NONE);
                col_Gefaelle_Button->SetBackgroundColour(pe_FarbeGefaelle);
            Bind(wxEVT_BUTTON, &Programm_Einstellungen_Dialog::OnColourButton, this, IDFarbeGefaelle);
        col_Gefaelle_Sizer->Add(col_Gefaelle_Button, 0,wxALL, 5);
    farbenSizer->Add(col_Gefaelle_Sizer, 1, wxEXPAND, 5);

    wxBoxSizer *col_Fangpunkt_Sizer = new wxBoxSizer(wxHORIZONTAL);
        col_Fangpunkt_Sizer->Add(new wxTextCtrl(this, -1, wxT("Fangpunkte"), wxDefaultPosition,  wxSize(150, 20), wxTE_READONLY|wxBORDER_NONE),0, wxALL, 5);
            wxButton *col_Fangpunkt_Button = new wxButton(this, IDFarbeFangpunkt, wxEmptyString, wxDefaultPosition, wxSize(20, 20), wxBORDER_NONE);
                col_Fangpunkt_Button->SetBackgroundColour(pe_FarbeFangpunkt);
            Bind(wxEVT_BUTTON, &Programm_Einstellungen_Dialog::OnColourButton, this, IDFarbeFangpunkt);
        col_Fangpunkt_Sizer->Add(col_Fangpunkt_Button, 0,wxALL, 5);
    farbenSizer->Add(col_Fangpunkt_Sizer, 1, wxEXPAND, 5);
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
    pe_verschubWeite = 0.01;                    //Schrittweite des Verschubs der Höhen
    pe_gefaelleRasterGroesse = 1.0;             //Rastergrösse in dem die Gefällemarken gesetzt werden
    pe_gefaelleMinimum = 1.8;             //Unteres Ende der Farbskala des Gefälles
    pe_gefaelleOptimum = 2.0;             //Mittelpunkt der Farbskala des Gefälles
    pe_gefaelleMaximum = 2.5;             //Oberes Ende der Farbskala des Gefälles
    pe_flaechenRasterGroesse = 1.0;             //Rastergrösse in dem Flächenpunkte berechnet werden (Integral, Schattierung etc.)
    pe_pxSuchEntfernung = 8;                    //Entfernung der Objekte zum Cursor in Pixeln bis zu der diese 'in der Nähe' sind
    pe_lnWandelGenauigkeit = 0.01;              //Entfernung von Linienendpunkt zu einem Punkt (absolut) bis zu dem diese als identisch erkannt werden
    pe_anzeigeGenauigkeit = 2;                  //Nachkommastellen der Zahlen
    pe_pseudoSchattenFkt = 1.0;                 //Faktor zur Anpassung der Schattenwirkung
    pe_FarbePktLn = wxColour(0, 0, 0);          //Farbe der Punkt und Linien
    pe_FarbeStrich = wxColour(74, 186, 240);    //usw.
    pe_FarbeHoehenMarke = wxColour(0, 128, 0);
    pe_FarbeHoehenlinie = wxColour(0, 0, 128);
    pe_FarbeMarkiertesObjekt = wxColour(255, 64, 64);
    pe_FarbeAusgewaehltesObjekt = wxColour(60, 160, 60);
    pe_FarbeHintergrundLayer = wxColour(145,145,64);
    pe_FarbeZeichenHintergrund = m_mama->GetBackgroundColour();
    pe_FarbeAuswahlRechteck = wxColour(255, 255, 240);
    pe_FarbeFlaecheDarueber = wxColour(180, 40, 0);
    pe_FarbeFlaecheDarunter = wxColour(40, 180, 0);
    pe_FarbeGefaelle = wxColour(0, 180, 255);
    pe_FarbeGefaelle = wxColour(85, 170, 255);

    char Zeile[50];
	ifstream PE_Parameter_Ini_Datei("Programmeinstellungen.ini", ios::in);
	if(PE_Parameter_Ini_Datei.good())
	{
	    double r, g, b;
		//cout<<"Neue_Ini_Datei existiert"<<endl;
		while(!PE_Parameter_Ini_Datei.eof())
		{
			PE_Parameter_Ini_Datei.getline(Zeile,50,':');
			if(!strcmp(Zeile,"verschubWeite"))
			{
				PE_Parameter_Ini_Datei.getline(Zeile,50);
				pe_verschubWeite = atof(Zeile);
				continue;
			}
			if(!strcmp(Zeile,"flaechenRasterGroesse"))
			{
				PE_Parameter_Ini_Datei.getline(Zeile,50);
				pe_flaechenRasterGroesse = atof(Zeile);
				continue;
			}
			if(!strcmp(Zeile,"gefaelleRasterGroesse"))
			{
				PE_Parameter_Ini_Datei.getline(Zeile,50);
				pe_gefaelleRasterGroesse = atof(Zeile);
				continue;
			}
			if(!strcmp(Zeile,"gefaelleMinimum"))
			{
				PE_Parameter_Ini_Datei.getline(Zeile,50);
				pe_gefaelleMinimum = atof(Zeile);
				continue;
			}
			if(!strcmp(Zeile,"gefaelleOptimum"))
			{
				PE_Parameter_Ini_Datei.getline(Zeile,50);
				pe_gefaelleOptimum = atof(Zeile);
				continue;
			}
			if(!strcmp(Zeile,"gefaelleMaximum"))
			{
				PE_Parameter_Ini_Datei.getline(Zeile,50);
				pe_gefaelleMaximum = atof(Zeile);
				continue;
			}
            if(!strcmp(Zeile,"pxSuchEntfernung"))
            {
				PE_Parameter_Ini_Datei.getline(Zeile,50);
                pe_pxSuchEntfernung = atof(Zeile);
				continue;
			}
            if(!strcmp(Zeile,"lnWandelGenauigkeit"))
            {
				PE_Parameter_Ini_Datei.getline(Zeile,50);
                pe_lnWandelGenauigkeit = atof(Zeile);
				continue;
			}
            if(!strcmp(Zeile,"anzeigeGenauigkeit"))
            {
				PE_Parameter_Ini_Datei.getline(Zeile,50);
                pe_anzeigeGenauigkeit = atof(Zeile);
				continue;
			}
            if(!strcmp(Zeile,"pseudoSchattenFkt"))
            {
				PE_Parameter_Ini_Datei.getline(Zeile,50);
                pe_pseudoSchattenFkt = atof(Zeile);
				continue;
			}
            if(!strcmp(Zeile,"FarbePktLn"))
            {
				PE_Parameter_Ini_Datei.getline(Zeile,50,',');
				r = atof(Zeile);
				PE_Parameter_Ini_Datei.getline(Zeile,50,',');
				g = atof(Zeile);
				PE_Parameter_Ini_Datei.getline(Zeile,50);
				b = atof(Zeile);
                pe_FarbePktLn = wxColour(r, g, b);
				continue;
			}
            if(!strcmp(Zeile,"FarbeStrich"))
            {
				PE_Parameter_Ini_Datei.getline(Zeile,50,',');
				r = atof(Zeile);
				PE_Parameter_Ini_Datei.getline(Zeile,50,',');
				g = atof(Zeile);
				PE_Parameter_Ini_Datei.getline(Zeile,50);
				b = atof(Zeile);
                pe_FarbeStrich = wxColour(r, g, b);
				continue;
			}
            if(!strcmp(Zeile,"FarbeHoehenMarke"))
            {
				PE_Parameter_Ini_Datei.getline(Zeile,50,',');
				r = atof(Zeile);
				PE_Parameter_Ini_Datei.getline(Zeile,50,',');
				g = atof(Zeile);
				PE_Parameter_Ini_Datei.getline(Zeile,50);
				b = atof(Zeile);
                pe_FarbeHoehenMarke = wxColour(r, g, b);
				continue;
			}
            if(!strcmp(Zeile,"FarbeHoehenlinie"))
            {
				PE_Parameter_Ini_Datei.getline(Zeile,50,',');
				r = atof(Zeile);
				PE_Parameter_Ini_Datei.getline(Zeile,50,',');
				g = atof(Zeile);
				PE_Parameter_Ini_Datei.getline(Zeile,50);
				b = atof(Zeile);
                pe_FarbeHoehenlinie = wxColour(r, g, b);
				continue;
			}
            if(!strcmp(Zeile,"FarbeMarkiertesObjekt"))
            {
				PE_Parameter_Ini_Datei.getline(Zeile,50,',');
				r = atof(Zeile);
				PE_Parameter_Ini_Datei.getline(Zeile,50,',');
				g = atof(Zeile);
				PE_Parameter_Ini_Datei.getline(Zeile,50);
				b = atof(Zeile);
                pe_FarbeMarkiertesObjekt = wxColour(r, g, b);
				continue;
			}
            if(!strcmp(Zeile,"FarbeAusgewaehltesObjekt"))
            {
				PE_Parameter_Ini_Datei.getline(Zeile,50,',');
				r = atof(Zeile);
				PE_Parameter_Ini_Datei.getline(Zeile,50,',');
				g = atof(Zeile);
				PE_Parameter_Ini_Datei.getline(Zeile,50);
				b = atof(Zeile);
                pe_FarbeAusgewaehltesObjekt = wxColour(r, g, b);
				continue;
			}
            if(!strcmp(Zeile,"FarbeHintergrundLayer"))
            {
				PE_Parameter_Ini_Datei.getline(Zeile,50,',');
				r = atof(Zeile);
				PE_Parameter_Ini_Datei.getline(Zeile,50,',');
				g = atof(Zeile);
				PE_Parameter_Ini_Datei.getline(Zeile,50);
				b = atof(Zeile);
                pe_FarbeHintergrundLayer = wxColour(r, g, b);
				continue;
			}
            if(!strcmp(Zeile,"FarbeZeichenHintergrund"))
            {
				PE_Parameter_Ini_Datei.getline(Zeile,50,',');
				r = atof(Zeile);
				PE_Parameter_Ini_Datei.getline(Zeile,50,',');
				g = atof(Zeile);
				PE_Parameter_Ini_Datei.getline(Zeile,50);
				b = atof(Zeile);
                pe_FarbeZeichenHintergrund = wxColour(r, g, b);
				continue;
			}
            if(!strcmp(Zeile,"FarbeAuswahlRechteck"))
            {
				PE_Parameter_Ini_Datei.getline(Zeile,50,',');
				r = atof(Zeile);
				PE_Parameter_Ini_Datei.getline(Zeile,50,',');
				g = atof(Zeile);
				PE_Parameter_Ini_Datei.getline(Zeile,50);
				b = atof(Zeile);
                pe_FarbeAuswahlRechteck = wxColour(r, g, b);
				continue;
			}
            if(!strcmp(Zeile,"FarbeFlaecheDarueber"))
            {
				PE_Parameter_Ini_Datei.getline(Zeile,50,',');
				r = atof(Zeile);
				PE_Parameter_Ini_Datei.getline(Zeile,50,',');
				g = atof(Zeile);
				PE_Parameter_Ini_Datei.getline(Zeile,50);
				b = atof(Zeile);
                pe_FarbeFlaecheDarueber = wxColour(r, g, b);
				continue;
			}
            if(!strcmp(Zeile,"FarbeFlaecheDarunter"))
            {
				PE_Parameter_Ini_Datei.getline(Zeile,50,',');
				r = atof(Zeile);
				PE_Parameter_Ini_Datei.getline(Zeile,50,',');
				g = atof(Zeile);
				PE_Parameter_Ini_Datei.getline(Zeile,50);
				b = atof(Zeile);
                pe_FarbeFlaecheDarunter = wxColour(r, g, b);
				continue;
			}
            if(!strcmp(Zeile,"FarbeGefaelle"))
            {
				PE_Parameter_Ini_Datei.getline(Zeile,50,',');
				r = atof(Zeile);
				PE_Parameter_Ini_Datei.getline(Zeile,50,',');
				g = atof(Zeile);
				PE_Parameter_Ini_Datei.getline(Zeile,50);
				b = atof(Zeile);
                pe_FarbeGefaelle = wxColour(r, g, b);
				continue;
			}
            if(!strcmp(Zeile,"FarbeFangpunkt"))
            {
				PE_Parameter_Ini_Datei.getline(Zeile,50,',');
				r = atof(Zeile);
				PE_Parameter_Ini_Datei.getline(Zeile,50,',');
				g = atof(Zeile);
				PE_Parameter_Ini_Datei.getline(Zeile,50);
				b = atof(Zeile);
                pe_FarbeFangpunkt = wxColour(r, g, b);
				continue;
			}
		}
		PE_Parameter_Ini_Datei.close();
	}
	else{
        wxMessageDialog(m_mama, wxString("Keine Ini-Datei")).ShowModal();
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
    case IDverschubWeite:
        uebergabe = pe_verschubWeite = atof(inhalt);
        break;
    case IDgefaelleMinimum:
        uebergabe = pe_gefaelleMinimum = atof(inhalt);
        break;
    case IDgefaelleOptimum:
        uebergabe = pe_gefaelleOptimum = atof(inhalt);
        break;
    case IDgefaelleMaximum:
        uebergabe = pe_gefaelleMaximum = atof(inhalt);
        break;
    case IDgefaelleRasterGroesse:
        uebergabe = pe_gefaelleRasterGroesse = atof(inhalt);
        break;
    case IDflaechenRasterGroesse:
        uebergabe = pe_flaechenRasterGroesse = atof(inhalt);
        break;
    case IDpxSuchEntfernung:
        uebergabe = pe_pxSuchEntfernung = atof(inhalt);
        break;
    case IDlnWandelGenauigkeit:
        uebergabe = pe_lnWandelGenauigkeit = atof(inhalt);
        break;
    case IDanzeigeGenauigkeit:
        uebergabe = pe_anzeigeGenauigkeit = atof(inhalt);
        break;
    case IDpseudoSchattenFkt:
        pe_pseudoSchattenFkt = atof(inhalt);
        if(pe_pseudoSchattenFkt < 0)
        {
            pe_pseudoSchattenFkt = 0;
        }
        uebergabe = pe_pseudoSchattenFkt;
        break;
    case IDFarbePktLn:
    case IDFarbeHoehenMarke:
    case IDFarbeHoehenlinie:
    case IDFarbeMarkiertesObjekt:
    case IDFarbeAusgewaehltesObjekt:
    case IDFarbeHintergrundLayer:
    case IDFarbeZeichenHintergrund:
    case IDFarbeAuswahlRechteck:
    case IDFarbeFlaecheDarueber:
    case IDFarbeFlaecheDarunter:
    case IDFarbeGefaelle:
    case IDFarbeFangpunkt:
        return;
    }
    aruDblEvent *myevent = new aruDblEvent();
    myevent->SetzeWert(uebergabe);
    myevent->SetId(event.GetId());
    m_mama->GetEventHandler()->AddPendingEvent(*myevent);
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
    case IDFarbePktLn:
        farbUebergabe = pe_FarbePktLn;
        Title = wxT("Punkte und Linien");
        break;
    case IDFarbeStrich:
        farbUebergabe = pe_FarbeStrich;
        Title = wxT("Striche");
        break;
    case IDFarbeHoehenMarke:
        farbUebergabe = pe_FarbeHoehenMarke;
        Title = wxT("Höhenmarken");
        break;
    case IDFarbeHoehenlinie:
        farbUebergabe = pe_FarbeHoehenlinie;
        Title = wxT("Höhenlinien");
        break;
    case IDFarbeMarkiertesObjekt:
        farbUebergabe = pe_FarbeMarkiertesObjekt;
        Title = wxT("Markierte Objekte");
        break;
    case IDFarbeAusgewaehltesObjekt:
        farbUebergabe = pe_FarbeAusgewaehltesObjekt;
        Title = wxT("Ausgewählte Objkete");
        break;
    case IDFarbeHintergrundLayer:
        farbUebergabe = pe_FarbeHintergrundLayer;
        Title = wxT("Hintergrundlayer");
        break;
    case IDFarbeZeichenHintergrund:
        farbUebergabe = pe_FarbeZeichenHintergrund;
        Title = wxT("Hintergrund Zeichenfläche");
        break;
    case IDFarbeAuswahlRechteck:
        farbUebergabe = pe_FarbeAuswahlRechteck;
        Title = wxT("Auswahlrechteck");
        break;
    case IDFarbeFlaecheDarueber:
        farbUebergabe = pe_FarbeFlaecheDarueber;
        Title = wxT("Farbe oberhalb");
        break;
    case IDFarbeFlaecheDarunter:
        farbUebergabe = pe_FarbeFlaecheDarunter;
        Title = wxT("Farbe unterhalb");
        break;
    case IDFarbeGefaelle:
        farbUebergabe = pe_FarbeGefaelle;
        Title = wxT("Gefälle");
        break;
    case IDFarbeFangpunkt:
        farbUebergabe = pe_FarbeFangpunkt;
        Title = wxT("Fangpunkte");
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
    case IDFarbePktLn:
        pe_FarbePktLn = farbUebergabe;
        break;
    case IDFarbeStrich:
        pe_FarbeStrich = farbUebergabe;
        break;
    case IDFarbeHoehenMarke:
        pe_FarbeHoehenMarke = farbUebergabe;
        break;
    case IDFarbeHoehenlinie:
        pe_FarbeHoehenlinie = farbUebergabe;
        break;
    case IDFarbeMarkiertesObjekt:
        pe_FarbeMarkiertesObjekt = farbUebergabe;
        break;
    case IDFarbeAusgewaehltesObjekt:
        pe_FarbeAusgewaehltesObjekt = farbUebergabe;
        break;
    case IDFarbeHintergrundLayer:
        pe_FarbeHintergrundLayer = farbUebergabe;
        break;
    case IDFarbeZeichenHintergrund:
        pe_FarbeZeichenHintergrund = farbUebergabe;
        break;
    case IDFarbeAuswahlRechteck:
        pe_FarbeAuswahlRechteck = farbUebergabe;
        break;
    case IDFarbeFlaecheDarueber:
        pe_FarbeFlaecheDarueber = farbUebergabe;
        break;
    case IDFarbeFlaecheDarunter:
        pe_FarbeFlaecheDarunter = farbUebergabe;
        break;
    case IDFarbeGefaelle:
        pe_FarbeGefaelle = farbUebergabe;
        break;
    case IDFarbeFangpunkt:
        pe_FarbeFangpunkt = farbUebergabe;
        break;
    default:
        break;
    }

    aruColourEvent *myevent = new aruColourEvent();
    myevent->SetzeWert(farbUebergabe);
    myevent->SetInt(event.GetId());
    m_mama->GetEventHandler()->AddPendingEvent(*myevent);
    return;
}

void Programm_Einstellungen_Dialog::IniSpeichern(void)
{
    ofstream Neue_Ini_Datei("Programmeinstellungen.ini", ios::out|ios_base::trunc);
    if(Neue_Ini_Datei.good())
    {
        Neue_Ini_Datei<<"verschubWeite:"<<pe_verschubWeite<<"\n";
        Neue_Ini_Datei<<"gefaelleRasterGroesse:"<<pe_gefaelleRasterGroesse<<"\n";
        Neue_Ini_Datei<<"gefaelleMinimum:"<<pe_gefaelleMinimum<<"\n";
        Neue_Ini_Datei<<"gefaelleOptimum:"<<pe_gefaelleOptimum<<"\n";
        Neue_Ini_Datei<<"gefaelleMaximum:"<<pe_gefaelleMaximum<<"\n";
        Neue_Ini_Datei<<"flaechenRasterGroesse:"<<pe_flaechenRasterGroesse<<"\n";
        Neue_Ini_Datei<<"pxSuchEntfernung:"<<pe_pxSuchEntfernung<<"\n";
        Neue_Ini_Datei<<"lnWandelGenauigkeit:"<<pe_lnWandelGenauigkeit<<"\n";
        Neue_Ini_Datei<<"anzeigeGenauigkeit:"<<pe_anzeigeGenauigkeit<<"\n";
        Neue_Ini_Datei<<"pseudoSchattenFkt:"<<pe_pseudoSchattenFkt<<"\n";
        Neue_Ini_Datei<<"FarbePktLn:"<<(int)pe_FarbePktLn.Red()<<","<<(int)pe_FarbePktLn.Green()<<","<<(int)pe_FarbePktLn.Blue()<<"\n";
        Neue_Ini_Datei<<"FarbeStrich:"<<(int)pe_FarbeStrich.Red()<<","<<(int)pe_FarbeStrich.Green()<<","<<(int)pe_FarbeStrich.Blue()<<"\n";
        Neue_Ini_Datei<<"FarbeHoehenMarke:"<<(int)pe_FarbeHoehenMarke.Red()<<","<<(int)pe_FarbeHoehenMarke.Green()<<","<<(int)pe_FarbeHoehenMarke.Blue()<<"\n";
        Neue_Ini_Datei<<"FarbeHoehenlinie:"<<(int)pe_FarbeHoehenlinie.Red()<<","<<(int)pe_FarbeHoehenlinie.Green()<<","<<(int)pe_FarbeHoehenlinie.Blue()<<"\n";
        Neue_Ini_Datei<<"FarbeMarkiertesObjekt:"<<(int)pe_FarbeMarkiertesObjekt.Red()<<","<<(int)pe_FarbeMarkiertesObjekt.Green()<<","<<(int)pe_FarbeMarkiertesObjekt.Blue()<<"\n";
        Neue_Ini_Datei<<"FarbeAusgewaehltesObjekt:"<<(int)pe_FarbeAusgewaehltesObjekt.Red()<<","<<(int)pe_FarbeAusgewaehltesObjekt.Green()<<","<<(int)pe_FarbeAusgewaehltesObjekt.Blue()<<"\n";
        Neue_Ini_Datei<<"FarbeHintergrundLayer:"<<(int)pe_FarbeHintergrundLayer.Red()<<","<<(int)pe_FarbeHintergrundLayer.Green()<<","<<(int)pe_FarbeHintergrundLayer.Blue()<<"\n";
        Neue_Ini_Datei<<"FarbeZeichenHintergrund:"<<(int)pe_FarbeZeichenHintergrund.Red()<<","<<(int)pe_FarbeZeichenHintergrund.Green()<<","<<(int)pe_FarbeZeichenHintergrund.Blue()<<"\n";
        Neue_Ini_Datei<<"FarbeAuswahlRechteck:"<<(int)pe_FarbeAuswahlRechteck.Red()<<","<<(int)pe_FarbeAuswahlRechteck.Green()<<","<<(int)pe_FarbeAuswahlRechteck.Blue()<<"\n";
        Neue_Ini_Datei<<"FarbeFlaecheDarueber:"<<(int)pe_FarbeFlaecheDarueber.Red()<<","<<(int)pe_FarbeFlaecheDarueber.Green()<<","<<(int)pe_FarbeFlaecheDarueber.Blue()<<"\n";
        Neue_Ini_Datei<<"FarbeFlaecheDarunter:"<<(int)pe_FarbeFlaecheDarunter.Red()<<","<<(int)pe_FarbeFlaecheDarunter.Green()<<","<<(int)pe_FarbeFlaecheDarunter.Blue()<<"\n";
        Neue_Ini_Datei<<"FarbeGefaelle:"<<(int)pe_FarbeGefaelle.Red()<<","<<(int)pe_FarbeGefaelle.Green()<<","<<(int)pe_FarbeGefaelle.Blue()<<"\n";
        Neue_Ini_Datei<<"FarbeFangpunkt:"<<(int)pe_FarbeFangpunkt.Red()<<","<<(int)pe_FarbeFangpunkt.Green()<<","<<(int)pe_FarbeFangpunkt.Blue()<<"\n";
        Neue_Ini_Datei.close();
    }
    return;
}

double Programm_Einstellungen_Dialog::HoleWert(programmEinstellungID retID) const
{
    switch (retID)
    {
    case IDverschubWeite:
        return pe_verschubWeite;
    case IDgefaelleRasterGroesse:
        return pe_gefaelleRasterGroesse;
    case IDflaechenRasterGroesse:
        return pe_flaechenRasterGroesse;
    case IDgefaelleMinimum:
        return pe_gefaelleMinimum;
    case IDgefaelleOptimum:
        return pe_gefaelleOptimum;
    case IDgefaelleMaximum:
        return pe_gefaelleMaximum;
    case IDpxSuchEntfernung:
        return pe_pxSuchEntfernung;
    case IDlnWandelGenauigkeit:
        return pe_lnWandelGenauigkeit;
    case IDanzeigeGenauigkeit:
        return pe_anzeigeGenauigkeit;
    case IDpseudoSchattenFkt:
        return pe_pseudoSchattenFkt;
    case IDFarbePktLn:
    case IDFarbeHoehenMarke:
    case IDFarbeHoehenlinie:
    case IDFarbeMarkiertesObjekt:
    case IDFarbeAusgewaehltesObjekt:
    case IDFarbeHintergrundLayer:
    case IDFarbeZeichenHintergrund:
    case IDFarbeAuswahlRechteck:
    case IDFarbeStrich:
    case IDFarbeFlaecheDarueber:
    case IDFarbeFlaecheDarunter:
    case IDFarbeGefaelle:
    case IDFarbeFangpunkt:
        break;
    }
    return 0.0;
}

wxColour Programm_Einstellungen_Dialog::HoleFarbe(programmEinstellungID retID) const
{
    switch (retID)
    {
    case IDverschubWeite:
    case IDgefaelleRasterGroesse:
    case IDgefaelleMinimum:
    case IDgefaelleOptimum:
    case IDgefaelleMaximum:
    case IDpxSuchEntfernung:
    case IDlnWandelGenauigkeit:
    case IDanzeigeGenauigkeit:
    case IDpseudoSchattenFkt:
        return wxColour(0, 0, 0);
    case IDFarbePktLn:
        return pe_FarbePktLn;
    case IDFarbeStrich:
        return pe_FarbeStrich;
    case IDFarbeHoehenMarke:
        return pe_FarbeHoehenMarke;
    case IDFarbeHoehenlinie:
        return pe_FarbeHoehenlinie;
    case IDFarbeMarkiertesObjekt:
        return pe_FarbeMarkiertesObjekt;
    case IDFarbeAusgewaehltesObjekt:
        return pe_FarbeAusgewaehltesObjekt;
    case IDFarbeHintergrundLayer:
        return pe_FarbeHintergrundLayer;
    case IDFarbeZeichenHintergrund:
        return pe_FarbeZeichenHintergrund;
    case IDFarbeAuswahlRechteck:
        return pe_FarbeAuswahlRechteck;
    case IDFarbeFlaecheDarueber:
        return pe_FarbeFlaecheDarueber;
    case IDFarbeFlaecheDarunter:
        return pe_FarbeFlaecheDarunter;
    case IDFarbeGefaelle:
        return pe_FarbeGefaelle;
    case IDFarbeFangpunkt:
        return pe_FarbeFangpunkt;
    default:
        break;
    }
    return wxColour(0, 0, 0);
}
/*ENDE Programm_Einstellungen_Dialog*/