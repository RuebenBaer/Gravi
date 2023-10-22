#include "aru_events.h"

/*Event für double Übergabe*/
wxDEFINE_EVENT(aruEVT_DOUBLE, aruDblEvent);

aruDblEvent::aruDblEvent(wxEventType commandType, int id):wxCommandEvent(commandType, id)
{

}
 aruDblEvent::aruDblEvent(const aruDblEvent& event):wxCommandEvent(event)
{
    this->SetzeWert(event.HoleWert());
}

wxEvent* aruDblEvent::Clone()const
{
    return(new aruDblEvent(*this));
}

double aruDblEvent::HoleWert(void)const
{
    return(m_wert);
}

void aruDblEvent::SetzeWert(const double wert)
{
    m_wert = wert;
    return;
}
/*ENDE Event für double Übergabe*/

/*Event für wxColour Übergabe*/
wxDEFINE_EVENT(aruEVT_COLOUR, aruColourEvent);

aruColourEvent::aruColourEvent(wxEventType commandType, int id):wxCommandEvent(commandType, id)
{

}

aruColourEvent::aruColourEvent(const aruColourEvent& event):wxCommandEvent(event)
{
    this->SetzeWert(event.HoleWert());
}

wxEvent* aruColourEvent::Clone()const
{
    return(new aruColourEvent(*this));
}

wxColour aruColourEvent::HoleWert(void)const
{
    return(m_wert);
}

void aruColourEvent::SetzeWert(const wxColour wert)
{
    m_wert = wert;
    return;
}
/*ENDE Event für wxColour Übergabe*/