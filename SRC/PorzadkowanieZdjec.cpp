
#include "PorzadkowanieZdjec.h"

///////////////////////////////////////////////////////////////////////////

PorzadkowanieZdjec::PorzadkowanieZdjec(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style) : wxFrame(parent, id, title, pos, size, style)
{

	this->SetSizeHints(wxDefaultSize, wxDefaultSize);

	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer(wxVERTICAL);

	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer(wxVERTICAL);

	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer(wxHORIZONTAL);

	bSizer5->SetMinSize(wxSize(300, 100));
	wxBoxSizer* bSizer6;
	bSizer6 = new wxBoxSizer(wxVERTICAL);

	wxBoxSizer* bSizer8;
	bSizer8 = new wxBoxSizer(wxVERTICAL);

	m_loadFolder = new wxButton(this, wxID_ANY, wxT("Wczytaj Folder"), wxDefaultPosition, wxSize(100, -1), 0);
	bSizer8->Add(m_loadFolder, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);
	m_loadFolder->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_BACKGROUND));
	m_loadFolder->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_ACTIVECAPTION));


	m_export = new wxButton(this, wxID_ANY, wxT("Exportuj"), wxDefaultPosition, wxSize(100, -1), 0);
	bSizer8->Add(m_export, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);
	m_export->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_BACKGROUND));
	m_export->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_ACTIVECAPTION));


	bSizer6->Add(bSizer8, 1, wxEXPAND, 5);

	wxBoxSizer* bSizer9;
	bSizer9 = new wxBoxSizer(wxHORIZONTAL);

	wxBoxSizer* bSizer10;
	bSizer10 = new wxBoxSizer(wxVERTICAL);

	m_checkBoxWidth = new wxCheckBox(this, wxID_ANY, wxT("Szerokosc"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer10->Add(m_checkBoxWidth, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);

	m_maxWidthControl = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(70, -1), wxSP_ARROW_KEYS, 0, 1200, 0);
	bSizer10->Add(m_maxWidthControl, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 5);


	bSizer9->Add(bSizer10, 1, wxEXPAND, 5);

	wxBoxSizer* bSizer11;
	bSizer11 = new wxBoxSizer(wxVERTICAL);

	m_checkBoxHeight = new wxCheckBox(this, wxID_ANY, wxT("Wysokosc"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer11->Add(m_checkBoxHeight, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);

	m_maxHeightControl = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(70, -1), wxSP_ARROW_KEYS, 0, 1200, 0);
	bSizer11->Add(m_maxHeightControl, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 5);

	bSizer9->Add(bSizer11, 1, wxEXPAND, 5);


	bSizer6->Add(bSizer9, 1, wxEXPAND, 5);


	bSizer5->Add(bSizer6, 1, wxEXPAND, 5);

	wxBoxSizer* bSizer7;
	bSizer7 = new wxBoxSizer(wxVERTICAL);

	wxBoxSizer* bSizer12;
	bSizer12 = new wxBoxSizer(wxVERTICAL);

	wxBoxSizer* bSizer14;
	bSizer14 = new wxBoxSizer(wxVERTICAL);

	m_staticText1 = new wxStaticText(this, wxID_ANY, wxT("Kompresja"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticText1->Wrap(-1);
	bSizer14->Add(m_staticText1, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 5);

	bSizer12->Add(bSizer14, 1, wxEXPAND, 5);

	wxBoxSizer* bSizer15;
	bSizer15 = new wxBoxSizer(wxHORIZONTAL);

	m_staticText2 = new wxStaticText(this, wxID_ANY, wxT("Min"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticText2->Wrap(-1);
	bSizer15->Add(m_staticText2, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);

	m_compressionLevel = new wxSlider(this, wxID_ANY, 50, 0, 100, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL);
	bSizer15->Add(m_compressionLevel, 1, wxALL | wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL, 5);

	m_staticText3 = new wxStaticText(this, wxID_ANY, wxT("Max"), wxDefaultPosition, wxDefaultSize, 0);
	m_staticText3->Wrap(-1);
	bSizer15->Add(m_staticText3, 0, wxALIGN_CENTER_VERTICAL | wxALL, 5);

	bSizer12->Add(bSizer15, 1, wxEXPAND | wxALIGN_CENTER_HORIZONTAL, 5);


	bSizer7->Add(bSizer12, 1, wxEXPAND, 5);

	wxBoxSizer* bSizer13;
	bSizer13 = new wxBoxSizer(wxVERTICAL);

	m_checkBoxSemiAutomaticMode = new wxCheckBox(this, wxID_ANY, wxT("Tryb polautomatyczny"), wxDefaultPosition, wxDefaultSize, 0);
	bSizer13->Add(m_checkBoxSemiAutomaticMode, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 5);


	m_progressBar = new wxGauge(this, wxID_ANY, 100, wxDefaultPosition, wxDefaultSize, wxGA_HORIZONTAL);
	m_progressBar->SetValue(0);
	bSizer13->Add(m_progressBar, 1, wxALIGN_BOTTOM | wxALIGN_CENTER_VERTICAL | wxALL | wxEXPAND, 5);


	bSizer7->Add(bSizer13, 1, wxEXPAND, 5);


	bSizer5->Add(bSizer7, 1, wxEXPAND, 5);


	bSizer3->Add(bSizer5, 0, wxEXPAND, 5);

	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer(wxVERTICAL);


	m_panel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(600, 600), wxTAB_TRAVERSAL);
	m_panel->SetMinSize(wxSize(600, 600));
	m_panel->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOWFRAME));

	bSizer4->Add(m_panel, 1, wxEXPAND | wxALL, 5);


	bSizer3->Add(bSizer4, 1, wxEXPAND, 5);


	bSizer2->Add(bSizer3, 1, wxEXPAND, 5);


	this->SetSizer(bSizer2);
	this->Layout();
	bSizer2->Fit(this);

	this->Centre(wxBOTH);
	/// ////////////////////////////////////////////////////////////////////////////

	
	m_checkBoxWidth->Connect(wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(PorzadkowanieZdjec::_WidthCheckBox), NULL, this);
	m_checkBoxHeight->Connect(wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(PorzadkowanieZdjec::_HeightCheckBox), NULL, this);
	m_checkBoxSemiAutomaticMode->Connect(wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(PorzadkowanieZdjec::_SemiAutomaticMode), NULL, this);
	m_loadFolder->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(PorzadkowanieZdjec::_LoadFolder), NULL, this);
	m_export->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(PorzadkowanieZdjec::Export), NULL, this);
	Connect(wxEVT_UPDATE_UI, wxUpdateUIEventHandler(PorzadkowanieZdjec::_UpdateInterface));
	m_maxHeightControl->Connect(wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler(PorzadkowanieZdjec::_MaxHeightSpinCtrl), NULL, this);
	m_maxHeightControl->Connect(wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(PorzadkowanieZdjec::_MaxHeightSpinCtrlText), NULL, this);
	m_maxHeightControl->Connect(wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler(PorzadkowanieZdjec::e_MaxHeightTextEnter), NULL, this);
	m_maxWidthControl->Connect(wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler(PorzadkowanieZdjec::e_MaxWidthSpinCtrl), NULL, this);
	m_maxWidthControl->Connect(wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(PorzadkowanieZdjec::_MaxWidthSpinCtrlText), NULL, this);
	m_maxWidthControl->Connect(wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler(PorzadkowanieZdjec::_MaxWidthTextEnter), NULL, this);
	m_compressionLevel->Connect(wxEVT_SLIDER, wxCommandEventHandler(PorzadkowanieZdjec::_CompressionLeve), NULL, this);
}

PorzadkowanieZdjec::~PorzadkowanieZdjec()
{
	// Disconnect Events
	m_checkBoxWidth->Disconnect(wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(PorzadkowanieZdjec::_WidthCheckBox), NULL, this);
	m_checkBoxHeight->Disconnect(wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(PorzadkowanieZdjec::_HeightCheckBox), NULL, this);
	m_checkBoxSemiAutomaticMode->Disconnect(wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(PorzadkowanieZdjec::_SemiAutomaticMode), NULL, this);
	m_loadFolder->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(PorzadkowanieZdjec::_LoadFolder), NULL, this);
	m_export->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(PorzadkowanieZdjec::Export), NULL, this);
	Disconnect(wxEVT_UPDATE_UI, wxUpdateUIEventHandler(PorzadkowanieZdjec::_UpdateInterface));
	m_maxHeightControl->Disconnect(wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler(PorzadkowanieZdjec::_MaxHeightSpinCtrl), NULL, this);
	m_maxHeightControl->Disconnect(wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(PorzadkowanieZdjec::_MaxHeightSpinCtrlText), NULL, this);
	m_maxHeightControl->Disconnect(wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler(PorzadkowanieZdjec::e_MaxHeightTextEnter), NULL, this);
	m_maxWidthControl->Disconnect(wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler(PorzadkowanieZdjec::e_MaxWidthControlO), NULL, this);
	m_maxWidthControl->Disconnect(wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(PorzadkowanieZdjec::_MaxWidthSpinCtrlText), NULL, this);
	m_maxWidthControl->Disconnect(wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler(PorzadkowanieZdjec::_MaxWidthTextEnter), NULL, this);
	m_compressionLevel->Disconnect(wxEVT_SLIDER, wxCommandEventHandler(PorzadkowanieZdjec::_CompressionLeve), NULL, this);

}