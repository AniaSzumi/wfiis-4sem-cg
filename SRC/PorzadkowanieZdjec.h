#pragma once

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/gdicmn.h>
#include <wx/button.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/checkbox.h>
#include <wx/stattext.h>
#include <wx/spinctrl.h>
#include <wx/sizer.h>
#include <wx/slider.h>
#include <wx/textctrl.h>
#include <wx/gauge.h>
#include <wx/panel.h>
#include <wx/frame.h>





class PorzadkowanieZdjec : public wxFrame
{
public:
	PorzadkowanieZdjec(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Porzadkowanie zdjec"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(836, 499), long style = wxDEFAULT_FRAME_STYLE | wxTAB_TRAVERSAL);
	~PorzadkowanieZdjec();

protected:
	wxButton* m_loadFolder;
	wxSpinCtrl* m_maxHeightControl;
	wxSpinCtrl* m_maxWidthControl;
	wxStaticText* m_staticText1;
	wxStaticText* m_staticText2;
	wxSlider* m_compressionLevel;
	wxStaticText* m_staticText3;
	wxButton* m_export;
	wxGauge* m_progressBar;
	wxPanel* m_panel;
	wxCheckBox* m_checkBoxWidth;
	wxCheckBox* m_checkBoxHeight;
	wxCheckBox* m_checkBoxSemiAutomaticMode;
	wxKeyEvent* m_key;

	virtual void _LoadFolder(wxCommandEvent& event) { event.Skip(); }
	virtual void _Export(wxCommandEvent& event) { event.Skip(); }
	virtual void _UpdateInterface(wxUpdateUIEvent& event) { event.Skip(); }
	virtual void _WidthCheckBox(wxCommandEvent& event) { event.Skip(); }
	virtual void _HeightCheckBox(wxCommandEvent& event) { event.Skip(); }
	virtual void _SemiAutomaticMode(wxCommandEvent& event) { event.Skip(); }
	virtual void _MaxHeightSpinCtrl(wxSpinEvent& event) { event.Skip(); }
	virtual void _MaxHeightSpinCtrlText(wxCommandEvent& event) { event.Skip(); }
	virtual void _MaxHeightTextEnter(wxCommandEvent& event) { event.Skip(); }
	virtual void _MaxWidthSpinCtrl(wxSpinEvent& event) { event.Skip(); }
	virtual void _MaxWidthControlOnSpinCtrlText(wxCommandEvent& event) { event.Skip(); }
	virtual void _MaxWidthTextEnter(wxCommandEvent& event) { event.Skip(); }
	virtual void _CompressionLevel(wxCommandEvent& event) { event.Skip(); }
};