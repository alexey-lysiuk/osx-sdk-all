/////////////////////////////////////////////////////////////////////////////
// Name:        wx/spinbutt.h
// Purpose:     wxSpinButtonBase class
// Author:      Julian Smart, Vadim Zeitlin
// Modified by:
// Created:     23.07.99
// RCS-ID:      $Id: spinbutt.h,v 1.31 2004/09/22 14:38:29 ABX Exp $
// Copyright:   (c) Julian Smart
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

#ifndef _WX_SPINBUTT_H_BASE_
#define _WX_SPINBUTT_H_BASE_

// ----------------------------------------------------------------------------
// headers
// ----------------------------------------------------------------------------

#include "wx/defs.h"

#if wxUSE_SPINBTN

#include "wx/control.h"
#include "wx/event.h"

#define wxSPIN_BUTTON_NAME _T("wxSpinButton")

// ----------------------------------------------------------------------------
//  The wxSpinButton is like a small scrollbar than is often placed next
//  to a text control.
//
//  Styles:
//  wxSP_HORIZONTAL:   horizontal spin button
//  wxSP_VERTICAL:     vertical spin button (the default)
//  wxSP_ARROW_KEYS:   arrow keys increment/decrement value
//  wxSP_WRAP:         value wraps at either end
// ----------------------------------------------------------------------------

class WXDLLEXPORT wxSpinButtonBase : public wxControl
{
public:
    // ctor intiializes the range with the default (0..100) values
    wxSpinButtonBase() { m_min = 0; m_max = 100; }

    // accessors
    virtual int GetValue() const = 0;
    virtual int GetMin() const { return m_min; }
    virtual int GetMax() const { return m_max; }

    // operations
    virtual void SetValue(int val) = 0;
    virtual void SetMin(int minVal) { SetRange ( minVal , m_max ) ; }
    virtual void SetMax(int maxVal) { SetRange ( m_min , maxVal ) ; }
    virtual void SetRange(int minVal, int maxVal)
    {
        m_min = minVal;
        m_max = maxVal;
    }

    // is this spin button vertically oriented?
    bool IsVertical() const { return (m_windowStyle & wxSP_VERTICAL) != 0; }

protected:
    // the range value
    int   m_min;
    int   m_max;

    DECLARE_NO_COPY_CLASS(wxSpinButtonBase)
};

// ----------------------------------------------------------------------------
// include the declaration of the real class
// ----------------------------------------------------------------------------

#if defined(__WXUNIVERSAL__)
    #include "wx/univ/spinbutt.h"
#elif defined(__WXMSW__) && defined(__WIN95__)
    #include "wx/msw/spinbutt.h"
#elif defined(__WXMOTIF__)
    #include "wx/motif/spinbutt.h"
#elif defined(__WXGTK__)
    #include "wx/gtk/spinbutt.h"
#elif defined(__WXMAC__)
    #include "wx/mac/spinbutt.h"
#elif defined(__WXCOCOA__)
    #include "wx/cocoa/spinbutt.h"
#elif defined(__WXPM__)
    #include "wx/os2/spinbutt.h"
#endif

// ----------------------------------------------------------------------------
// the wxSpinButton event
// ----------------------------------------------------------------------------

class WXDLLEXPORT wxSpinEvent : public wxNotifyEvent
{
public:
    wxSpinEvent(wxEventType commandType = wxEVT_NULL, int winid = 0)
           : wxNotifyEvent(commandType, winid)
    {
    }

    // get the current value of the control
    int GetPosition() const { return m_commandInt; }
    void SetPosition(int pos) { m_commandInt = pos; }

private:
    DECLARE_DYNAMIC_CLASS_NO_COPY(wxSpinEvent)
};

typedef void (wxEvtHandler::*wxSpinEventFunction)(wxSpinEvent&);

// macros for handling spin events
#define EVT_SPIN_UP(winid, func) \
    DECLARE_EVENT_TABLE_ENTRY( wxEVT_SCROLL_LINEUP, winid, wxID_ANY, (wxObjectEventFunction) (wxEventFunction)  wxStaticCastEvent( wxSpinEventFunction, & func ), NULL ),
#define EVT_SPIN_DOWN(winid, func) \
    DECLARE_EVENT_TABLE_ENTRY( wxEVT_SCROLL_LINEDOWN, winid, wxID_ANY, (wxObjectEventFunction) (wxEventFunction)  wxStaticCastEvent( wxSpinEventFunction, & func ), NULL ),
#define EVT_SPIN(winid, func) \
    DECLARE_EVENT_TABLE_ENTRY( wxEVT_SCROLL_THUMBTRACK, winid, wxID_ANY, (wxObjectEventFunction) (wxEventFunction)  wxStaticCastEvent( wxSpinEventFunction, & func ), NULL ),

#endif // wxUSE_SPINBTN

#endif
    // _WX_SPINBUTT_H_BASE_
