#pragma once
#include "PorzadkowanieZdjec.h"



#include <wx/wx.h>
#include <wx/dir.h>
#include <wx/string.h>
#include <wx/filefn.h> 
#include <wx/image.h>
#include <wx/bitmap.h>
#include <wx/dcbuffer.h>
#include <wx/event.h>
#include <wx/utils.h> 
#include <iostream>
#include <string>
#include <vector>
#include "FreeImage.h"



class PorzadkowanieZdjecFrame : public PorzadkowanieZdjec
{
public:
	PorzadkowanieZdjecFrame(wxWindow* parent);
	~PorzadkowanieZdjecFrame();

protected:
	
	void _LoadFolder(wxCommandEvent& event);
	

	void _Export(wxCommandEvent& event);
	

	void _UpdateInterface(wxUpdateUIEvent& event);
	

	void _KeyPressed(wxKeyEvent& event);
	
	void _WidthCheckBox(wxCommandEvent& event);
	

	void _HeightCheckBox(wxCommandEvent& event);
	

	void _SemiAutomaticMode(wxCommandEvent& event);
	


	void _MaxHeightSpinCtrl(wxSpinEvent& event);
	void _MaxHeightSpinCtrlText(wxCommandEvent& event);
	void _MaxHeightTextEnter(wxCommandEvent& event);
	void _MaxWidthSpinCtrl(wxSpinEvent& event);
	void _MaxWidthSpinCtrlText(wxCommandEvent& event);
	void _MaxWidthTextEnter(wxCommandEvent& event);


	void _CompressionLevel(wxCommandEvent& event);


	void _Repaint();


	void _GetPaths(const wxDir& dir);


	const wxArrayString _GetAllFiles(const wxDir& dir, const wxString extension) const;


	void _NextImage();


	void _SaveOne(int index);


	void _AddToMiniatures(FIBITMAP* miniatures, FIBITMAP* bitmap, int& widthIndex, int& heightIndex);



	void _CopyDir(wxString& source, wxString& target);


	bool _ImageCheck(wxString& currPath) const;

private:	
	const std::vector<std::string> c_extensions = { "*.png", "*.jpg", "*.raw", "*.bmp", "*.tiff","*.RAW" };
	const std::vector<FREE_IMAGE_FORMAT> c_formats = { FIF_PNG, FIF_JPEG, FIF_RAW, FIF_BMP, FIF_TIFF,FIF_RAW };

	std::vector<FREE_IMAGE_FORMAT> m_loadedImagesFormats = {};
	wxArrayString& m_imagesPathArray = wxArrayString();
	
	wxString m_sourcePath = "";
	wxString m_destinationPath = "";
	wxImage* m_image;

	int m_counter = 0;
	int m_saved = 0;
	int m_compression = m_compressionLevel->GetValue();
	int m_maxWidth = m_maxWidthControl->GetValue();
	int m_maxHeight = m_maxHeightControl->GetValue();
	int m_angle = 0;
	int m_miniaturesCount = 1;

	double m_ratio = 4. / 3.;

	bool m_isCustomWidth = m_checkBoxWidth->GetValue();
	bool m_isCustomHeight = m_checkBoxHeight->GetValue();
	bool m_isSemiAutomaticModeOn = m_checkBoxSemiAutomaticMode->GetValue();
	bool m_isLoadingImages = false;
};