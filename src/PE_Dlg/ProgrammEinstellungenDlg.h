#ifndef __PE_ES_DLG_H
#define __PE_ES_DLG_H

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include <wx/colordlg.h>
#include <wx/sizer.h>
#include "../aru_events/aru_events.h"

#include <fstream>

class Programm_Einstellungen_Dialog: public wxDialog
{
    public:
		enum programmEinstellungID{
			IDwert1=2000,
			IDwert2, IDfarbe1, IDfarbe2
		};
		
        Programm_Einstellungen_Dialog(wxWindow* parent);
        ~Programm_Einstellungen_Dialog();
        double HoleWert(programmEinstellungID retID) const;
        wxColour HoleFarbe(programmEinstellungID retID) const;

    private:
        wxWindow* m_mama;
        /*Parameter*/
        double pe_wert1, pe_wert2;
        wxColour pe_farbe1, pe_farbe2;

        void PEDialogIni(void);
        void IniSpeichern(void);

        /*Event handling*/
        void OnClose(wxCloseEvent &event);
        void OnOKButton(wxCommandEvent &event);
        void OnTextChange(wxCommandEvent &event);
        void OnColourButton(wxCommandEvent &event);
        DECLARE_EVENT_TABLE()
};

#endif //__PE_ES_DLG_H