#ifndef __ARU_EVENTS_H
#define __ARU_EVENTS_H

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

class aruDblEvent;
class aruColourEvent;

/*aruDblEvent*/
wxDECLARE_EVENT(aruEVT_DOUBLE, aruDblEvent);
class aruDblEvent: public wxCommandEvent
{
public:
    aruDblEvent(wxEventType commandType = aruEVT_DOUBLE, int id = 0);
    aruDblEvent(const aruDblEvent&);
    wxEvent* Clone()const;
    double HoleWert(void)const;
    void SetzeWert(const double);
private:
    double m_wert;
};
/*ENDE aruDblEvent*/

/*aruColourEvent*/
wxDECLARE_EVENT(aruEVT_COLOUR, aruColourEvent);
class aruColourEvent: public wxCommandEvent
{
public:
    aruColourEvent(wxEventType commandType = aruEVT_COLOUR, int id = 0);
    aruColourEvent(const aruColourEvent&);
    wxEvent* Clone()const;
    wxColour HoleWert(void)const;
    void SetzeWert(const wxColour);
private:
    wxColour m_wert;
};
/*ENDE aruColourEvent*/

#endif //__ARU_EVENTS_H