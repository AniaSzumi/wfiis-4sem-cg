#include <wx/wx.h>
#include <memory>
#pragma comment (lib, "FreeImage.lib")
#include "PorzadkowanieZdjecFrame.h"

class MyApp : public wxApp {

public:

	virtual bool OnInit();
	virtual int OnExit() { return 0; }

};

IMPLEMENT_APP(MyApp);

bool MyApp::OnInit()
{
	auto* mainFrame1 = new PorzadkowanieZdjecFrame(NULL);
	mainFrame1->Show(true);
	SetTopWindow(mainFrame1);

	return true;
}