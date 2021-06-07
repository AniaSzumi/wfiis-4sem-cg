#include "PorzadkowanieZdjecFrame.h"

PorzadkowanieZdjecFrame::PorzadkowanieZdjecFrame(wxWindow* parent)
	: PhotoOrganizer(parent),
	m_image(new wxImage())
{
	m_panel->Bind(wxEVT_CHAR_HOOK, &PorzadkowanieZdjecFrame::_KeyPressed, this);
	wxInitAllImageHandlers();
	m_maxWidthControl->Disable();
	m_maxHeightControl->Disable();
}

PorzadkowanieZdjecFrame::~PorzadkowanieZdjecFrame()
{
	delete m_image;
}


void PorzadkowanieZdjecFrame::_LoadFolder(wxCommandEvent& event)
{
	m_imagesPathArray.Empty();
	wxString defaultPath = wxT("/");
	wxDirDialog dialog(this, wxT("Wybiez folder"), defaultPath, wxDD_NEW_DIR_BUTTON);
	if (dialog.ShowModal() == wxID_OK)
	{
		m_sourcePath = dialog.GetPath();
		wxDir current(m_sourcePath);
		_GetPaths(current);

		if (m_counter == 0)
		{
			wxMessageBox("W folderze nie ma zadnych zdjec");
			m_sourcePath = "";
		}
		else
		{
			
			m_saved = 0;
			m_progressBar->SetValue(0);
			wxMessageBox("Wczytane zdjecia: " + std::to_string(m_counter));
		}
	}
	else 
	{
		wxMessageBox("Error.");
	}
}

void PorzadkowanieZdjecFrame::_Export(wxCommandEvent& event)
{
	wxString defaultPath = wxT("/");
	wxDirDialog dialog(this, wxT("Wybierz folder"), defaultPath, wxDD_NEW_DIR_BUTTON);

	if (dialog.ShowModal() == wxID_OK)
	{
		m_destinationPath = dialog.GetPath();
		wxDir target(m_destinationPath);

		bool wasOpened = target.IsOpened();

		if (wasOpened) 
		{
			if (m_destinationPath != m_sourcePath) 
			{
				if (m_isSemiAutomaticModeOn)
				{
					_CopyDir(m_sourcePath, m_destinationPath);
					m_isLoadingImages = true;
					m_saved = 0;
					_NextImage();
				}
				else if (!m_isSemiAutomaticModeOn)
				{
					_CopyDir(m_sourcePath, m_destinationPath);
					for (int i = 0; i < m_counter; ++i)
						#pragma omp parallel for
						_SaveOne(i);
					m_saved = m_counter;
					m_progressBar->SetValue(0);
					wxMessageBox("Konwersja zako�czona.");
				}
			}
			else 
			{
				wxMessageBox("Error. Docelowy folder musi byc inny ni� obecny folder.");
			}
		}
		else
		{
			wxMessageBox("Error. Nie mo�na otworzyc folderu.");
		}

		
	}
}

void PorzadkowanieZdjecFrame::_UpdateInterface(wxUpdateUIEvent& event)	
{
	_Repaint();
}

void PorzadkowanieZdjecFrame::_KeyPressed(wxKeyEvent& event)
{
	if (m_isSemiAutomaticModeOn && m_isLoadingImages)
	{
		switch ((int)event.GetKeyCode()) 
		{
		case 316:
			m_angle += 1;
			_Repaint();
			break;
		case 314:
			m_angle -= 1;
			_Repaint();
			break;
		case 13:
			_SaveOne(m_saved);
			_NextImage();
			break;
		default:
			break;
		}
	}
	event.Skip();
}

void PorzadkowanieZdjecFrame::_WidthCheckBox(wxCommandEvent& event)
{
	m_isCustomWidth = m_checkBoxWidth->GetValue();
	m_isCustomWidth ? m_maxWidthControl->Enable() : m_maxWidthControl->Disable();
}

void PorzadkowanieZdjecFrame::_HeightCheckBox(wxCommandEvent& event)
{
	m_isCustomHeight = m_checkBoxHeight->GetValue();
	m_isCustomHeight ? m_maxHeightControl->Enable() : m_maxHeightControl->Disable();
}

void PorzadkowanieZdjecFrame::_SemiAutomaticMode(wxCommandEvent& event)
{
	m_isSemiAutomaticModeOn = m_checkBoxSemiAutomaticMode->GetValue();
}

void PorzadkowanieZdjecFrame::_MaxHeightSpinCtrl(wxSpinEvent& event)
{
	m_maxHeight = m_maxHeightControl->GetValue();
}

void PorzadkowanieZdjecFrame::_MaxHeightSpinCtrlText(wxCommandEvent& event)
{
	m_maxHeight = m_maxHeightControl->GetValue();
}

void PorzadkowanieZdjecFrame::_MaxHeightTextEnter(wxCommandEvent& event)
{
	m_maxHeight = m_maxHeightControl->GetValue();
}

void PorzadkowanieZdjecFrame::_MaxWidthSpinCtrl(wxSpinEvent& event)
{
	m_maxWidth = m_maxWidthControl->GetValue();
}

void PorzadkowanieZdjecFrame::_MaxWidthSpinCtrlText(wxCommandEvent& event)
{
	m_maxWidth = m_maxWidthControl->GetValue();
}

void PorzadkowanieZdjecFrame::_MaxWidthTextEnter(wxCommandEvent& event)
{
	m_maxWidth = m_maxWidthControl->GetValue();
}

void PorzadkowanieZdjecFrame::_CompressionLevel(wxCommandEvent& event)
{
	m_compression = 100 - m_compressionLevel->GetValue();
}


void PorzadkowanieZdjecFrame::_Repaint()
{
	if (m_image->Ok())
	{
		wxClientDC DC(m_panel);
		wxBufferedDC bufferedDC(&DC);

		wxImage tmp(*m_image);
		m_angle = (m_angle + 4) % 4;

		for (int i = 1; i <= m_angle; ++i)
		{
			tmp = tmp.Rotate90();
		}
		double currentRatio = (double)tmp.GetWidth() / tmp.GetHeight();

		int drawImageWidth = m_maxWidth;
		int drawImageHeight = m_maxHeight;

		if (m_angle % 2 == 1)
		{
			drawImageWidth = m_maxHeight;
			drawImageHeight = m_maxWidth;
		}

		int boxWitdth = DC.GetSize().x;
		int boxHeight = DC.GetSize().y;

		double customRatio = (double)boxWitdth / (double)boxHeight;

		if (customRatio > currentRatio)
		{
			drawImageHeight = boxHeight;
			drawImageWidth = currentRatio * drawImageHeight;
		}
		else if (customRatio < currentRatio)
		{
			drawImageWidth = boxWitdth;
			drawImageHeight = drawImageWidth / currentRatio;
		}
		else
		{
			drawImageWidth = boxWitdth;
			drawImageHeight = boxHeight;
		}

		tmp.Rescale(drawImageWidth, drawImageHeight);

		wxBitmap imgBitmap(tmp);
		bufferedDC.Clear();
		bufferedDC.DrawBitmap(imgBitmap, 0, 0);
	}
}

void PorzadkowanieZdjecFrame::_GetPaths(const wxDir& source)
{
	wxArrayString subDirs;
	wxString dirName;

	if (source.HasSubDirs())
	{
		bool isSubDir = source.GetFirst(&dirName, wxEmptyString, wxDIR_DIRS);
		while (isSubDir)
		{
			if (_ImageCheck(source.GetName() + '\\' + dirName))
			{
				subDirs.Add(dirName);
			}
			isSubDir = source.GetNext(&dirName);
		}

		for (wxString sub : subDirs)
		{
			_GetPaths(source.GetName() + '\\' + sub);
		}
	}

	wxString fileName;
	wxString fileNameWithSubDirs;
	wxArrayString fileNamesList;
	int index = 0;

	for (const auto& extension : c_extensions)
	{
		bool cont = source.GetFirst(&fileName, extension, wxDIR_DEFAULT);
		while (cont) 
		{
			fileNameWithSubDirs = source.GetName() + '\\' + fileName;
			fileNameWithSubDirs.Replace(m_sourcePath, "");
			m_imagesPathArray.Add(fileNameWithSubDirs);
			m_loadedImagesFormats.push_back(c_formats[index]);
			m_counter++;
			cont = source.GetNext(&fileName);
		}
		index++;
	}
}

const wxArrayString PorzadkowanieZdjecFrame::_GetAllFiles(const wxDir& dir, const wxString extension) const
{
	wxString fileName;
	wxArrayString files;
	bool cont = dir.GetFirst(&fileName, extension, wxDIR_DEFAULT);
	while (cont) 
	{
		files.Add(fileName);
		cont = dir.GetNext(&fileName);
	}
	return files;
}

void PorzadkowanieZdjecFrame::_NextImage()
{
	if (m_saved < m_counter)
	{
		m_image->LoadFile(m_sourcePath + m_imagesPathArray[m_saved], wxBITMAP_TYPE_ANY);
		if (!m_image)
		{
			m_saved++;
		}
		_Repaint();
	}
	else
	{
		m_image->Clear();
		wxMessageBox("Konwersja zakonczona");
		m_saved = 0;
		m_isLoadingImages = false;
		m_progressBar->SetValue(0);
	}
}

void PorzadkowanieZdjecFrame::_SaveOne(int index)
{
	int setHeight, setWidth;

	FIBITMAP* bitmap;
	FIBITMAP* bitmapRescaled, bitmapRotated;

	wxString pathToSource = m_sourcePath + '\\' + m_imagesPathArray[index];
	wxString pathToTarget = m_destinationPath + '\\' + m_imagesPathArray[index];
	
	pathToTarget.Replace(".png", ".jpg");
	pathToTarget.Replace(".raw", ".jpg");
	pathToTarget.Replace(".bmp", ".jpg");
	pathToTarget.Replace(".tiff", ".jpg");
	pathToTarget.Replace(".RAW", ".jpg");

	if (pathToSource == "*.raw") 
	{
		bitmap = FreeImage_Load(m_loadedImagesFormats[index], pathToSource, RAW_DEFAULT);
	}
	else 
	{
		bitmap = FreeImage_Load(m_loadedImagesFormats[index], pathToSource, 0);
	}
	if (bitmap)
	{
		m_ratio = (double)FreeImage_GetWidth(bitmap) / (double)(FreeImage_GetHeight(bitmap));
		if (m_isCustomHeight && m_isCustomWidth)
		{
			double customRatio = m_maxWidth / m_maxHeight;

			if (customRatio > m_ratio)
			{
				setHeight = m_maxHeight;
				setWidth = m_ratio * setHeight;
			}

			else if (customRatio < m_ratio)
			{
				setWidth = m_maxWidth;
				setHeight = setWidth / m_ratio;
			}

			else
			{
				setWidth = m_maxWidth;
				setHeight = m_maxHeight;
			}

		}
		else if (m_isCustomHeight && !m_isCustomWidth)
		{
			setHeight = m_maxHeight;
			setWidth = m_ratio * setHeight;
		}

		else if (m_isCustomWidth && !m_isCustomHeight)
		{
			setWidth = m_maxWidth;
			setHeight = setWidth / m_ratio;
		}

		else
		{
			setHeight = FreeImage_GetHeight(bitmap);
			setWidth = FreeImage_GetWidth(bitmap);
		}

		bitmapRescaled = FreeImage_Rescale(bitmap, setWidth, setHeight);
		bitmapRotated = *FreeImage_Rotate(bitmapRescaled, 90*m_angle);
		FreeImage_Save(FIF_JPEG, &bitmapRotated, pathToTarget, m_compression);
		FreeImage_Unload(bitmap);
		FreeImage_Unload(bitmapRescaled);
	}
	m_angle = 0;
	m_saved++;
	m_progressBar->SetValue((int)((m_saved * 100) / m_counter));
}

void PorzadkowanieZdjecFrame::_AddToMiniatures(FIBITMAP* miniatures, FIBITMAP* bitmap, int& widthIndex, int& heightIndex){
	FIBITMAP* bitmapNew;
	FIBITMAP* bitmapRescaled;

	int setWidth = 144;
	int setHeight = 128;
	std::vector<int> leftPositions = { 0, 144, 288, 432, 576 };
	std::vector<int> topPositions = { 0, 128, 256, 384, 512, 640, 768, 896 };
	double ratio = 144. / 128.;

	bitmapNew = FreeImage_Allocate(144, 128, 24);

	ratio = FreeImage_GetWidth(bitmap) / double(FreeImage_GetHeight(bitmap));
	if (FreeImage_GetWidth(bitmap) > setWidth || FreeImage_GetHeight(bitmap) > setHeight)
	{

		if (FreeImage_GetWidth(bitmap) > FreeImage_GetHeight(bitmap))
		{
			setHeight = setWidth / ratio;
		}
		else
		{
			setWidth = setHeight * ratio;
		}
	}
	else
	{
		setHeight = FreeImage_GetHeight(bitmap);
		setWidth = FreeImage_GetWidth(bitmap);
	}

	bitmapRescaled = FreeImage_Rescale(bitmap, setWidth, setHeight);
	if (bitmapRescaled)
	{
		FreeImage_Paste(bitmapNew, bitmapRescaled, (144 - setWidth) / 2, (128 - setHeight) / 2, 256);
		if (bitmapNew)
		{
			FreeImage_Paste(miniatures, bitmapNew, leftPositions[widthIndex], topPositions[heightIndex], 256);
		}
		else
		{
			wxMessageBox("powt�rzenie");
		}
	}
	else
	{
		wxMessageBox("nie przeskalowana");
	}
	if (widthIndex == 4 && heightIndex == 7)
	{
		wxString filename;
		wxString miniaturesCountString = wxString::Format(wxT("%i"), m_miniaturesCount);
		filename = "miniatures_" + miniaturesCountString + ".jpg";
		m_miniaturesCount++;
		
		FreeImage_Save(FIF_JPEG, miniatures, m_destinationPath + '\\' + filename, m_compression);
	}

	FreeImage_Unload(bitmapNew);
	FreeImage_Unload(bitmapRescaled);
}

void PorzadkowanieZdjecFrame::_CopyDir(wxString& currPath, wxString& targetPath)
{
	wxArrayString subdirectories;
	wxString dirName;
	wxDir source(currPath);
	wxDir target(targetPath);
	int index = 0;
	int filesInDir = 0;
	int widthIndex = 0;
	int heightIndex = 0;
	wxArrayString& files = wxArrayString();
	FIBITMAP* miniatures = FreeImage_Allocate(720, 1024, 24);
	FIBITMAP* bitmap;
	wxString pathToFile = currPath;
	wxString pathToTarget = targetPath;

	for (const auto& format : c_extensions)
	{
		files = _GetAllFiles(source, format);

		for (wxString name : files)
		{
			#pragma omp parallel for
			pathToFile = currPath + '\\' + name;
			pathToTarget = targetPath + '\\' + name;
			bitmap = FreeImage_Load(c_formats[index], pathToFile, 0);
			if (bitmap)
			{
				if (filesInDir == 40)
				{
					filesInDir = 0;
					FIBITMAP* temp = FreeImage_Allocate(720, 1024, 24);
					FreeImage_Paste(miniatures, temp, 0, 0, 256);
					FreeImage_Unload(temp);
				}

				widthIndex = filesInDir % 5;
				heightIndex = filesInDir / 5;
				if(miniatures)
				{
					_AddToMiniatures(miniatures, bitmap, widthIndex, heightIndex);
				}
				FreeImage_Unload(bitmap);
				filesInDir++;
			}
		}
		index++;
	}
	if (filesInDir != 0)
	{
		FreeImage_Save(FIF_JPEG, miniatures, targetPath + '\\' + "Mniatures.jpg", m_compression);
	}
		
	FreeImage_Unload(miniatures);


	if (source.HasSubDirs())
	{
		bool cont = source.GetFirst(&dirName, wxEmptyString, wxDIR_DIRS);
		while (cont)
		{
			if (m_destinationPath != currPath + '\\' + dirName && _ImageCheck(currPath + '\\' + dirName))
			{
				subdirectories.Add(dirName);
				wxMkdir(targetPath + '\\' + dirName);
			}
			cont = source.GetNext(&dirName);
		}

		for (wxString sub : subdirectories)
		{
			_CopyDir(currPath + '\\' + sub, targetPath + '\\' + sub);
		}
	}
}

bool PorzadkowanieZdjecFrame::_ImageCheck(wxString& currPath) const 
{
	bool isInsideImage = false;
	wxDir dir(currPath);
	wxString dirName = "";
	wxArrayString& files = wxArrayString();
	wxArrayString subdirectories;

	for (const auto& extension : c_extensions)
	{
		files = _GetAllFiles(dir, extension);

		if (files.GetCount() > 0)
		{
			return true;
		}
	}

	if (dir.HasSubDirs())
	{
		bool cont = dir.GetFirst(&dirName, wxEmptyString, wxDIR_DIRS);
		while (cont)
		{
			if (m_destinationPath != currPath + '\\' + dirName)
			{
				subdirectories.Add(dirName);
			}
			cont = dir.GetNext(&dirName);
		}

		for (wxString sub : subdirectories)
		{
			if (_ImageCheck(currPath + '\\' + sub))
			{
				return true;
			}
		}
	}
	return false;
}