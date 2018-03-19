// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#include <MyImage.h>
#include <time.h>
#endif

class MyApp: public wxApp
{
public:
	virtual bool OnInit();
};


class MyPanel: public wxPanel
{
public:
    MyPanel( wxWindow *parent ) ;
    ~MyPanel() ;
    void OpenImage(wxString fileName);
    void SaveImage(wxString fileName);
    void OnPaint(wxPaintEvent &WXUNUSED(event));
    void MirrorImage(bool horizontal);
    void BlurImage();
    void NegativeImage();
    void DesaturateImage();
    void VLumImage();
    void RotateImage(int angle);
    int getWidth();
    int getHeight();

private:
    wxBitmap m_bitmap ;	// used to display the image
    MyImage *m_image ;  // used to load and process the image
    wxPaintDC *dc;
    int m_width = 0, m_height = 0;
};

class MyFrame: public wxFrame
{
public:
	MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
private:
	void OnHello(wxCommandEvent& event);
	void OnExit(wxCommandEvent& event);
	void OnResize(wxCommandEvent& event);
	void OnSouris(wxMouseEvent& event);
	void OnOpenImage(wxCommandEvent& event);
	void OnSaveImage (wxCommandEvent& event);
	void OnProcessImage (wxCommandEvent& event);
	MyPanel *m_panel; // the panel inside the main frame

};

enum	// énumération. Elle gère la numérotation automatiquement
{
	ID_Hello = 1,
	ID_DLF = 2,
	ID_Truc = 4,
	ID_Machin = 5,
	ID_PLarge = 6,
	ID_MLarge = 7,
	ID_OPEN = 8,
	ID_Save = 9,
	ID_HMirror = 10,
	ID_VMirror = 11,
	ID_Blur = 12,
	ID_Rot90 = 13,
	ID_Rot180 = 14,
	ID_RotM90 = 15,
	ID_Negative = 16,
	ID_Desaturate = 17,
	ID_VLum = 18,
};

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{
	MyFrame *frame = new MyFrame( wxT("Projet"), wxPoint(50, 50), wxSize(400,400) );
	frame->Show(true);
	wxInitAllImageHandlers();
	return true;
}

MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
: wxFrame(NULL, wxID_ANY, title, pos, size)
{
	wxMenu *menuFile = new wxMenu ;
	m_panel = new MyPanel(this) ;
	this->Centre() ;

	menuFile->Append(ID_OPEN, wxT("Ouvrir\tCtrl-F")) ;
	Bind(wxEVT_MENU, &MyFrame::OnOpenImage, this, ID_OPEN) ;

    menuFile->Append(ID_Save, wxT("Sauvegarder\tCtrl-S")) ;
	Bind(wxEVT_MENU, &MyFrame::OnSaveImage, this, ID_Save) ;

    menuFile->Append(ID_Hello, wxT("Crédits\tAlt-C")) ;
	Bind(wxEVT_MENU, &MyFrame::OnHello, this, ID_Hello) ;

	menuFile->Append(wxID_EXIT, wxT("Quitter\tAlt-W")) ;
	Bind(wxEVT_MENU, &MyFrame::OnExit, this, wxID_EXIT) ;

	wxMenu *menuFile2 = new wxMenu ;

    menuFile2->Append(ID_PLarge, wxT("Agrandir\tCtrl-A")) ;
	Bind(wxEVT_MENU, &MyFrame::OnResize, this, ID_PLarge) ;

    menuFile2->Append(ID_MLarge, wxT("Rétrécir\tCtrl-Q")) ;
	Bind(wxEVT_MENU, &MyFrame::OnResize, this, ID_MLarge) ;

	wxMenu *menuFile3 = new wxMenu ;

    menuFile3->Append(ID_HMirror, wxT("Miroir Horizontal\tCtrl-H")) ;
	Bind(wxEVT_MENU, &MyFrame::OnProcessImage, this, ID_HMirror) ;

    menuFile3->Append(ID_VMirror, wxT("Miroir Vertical\tCtrl-V")) ;
	Bind(wxEVT_MENU, &MyFrame::OnProcessImage, this, ID_VMirror) ;

    menuFile3->Append(ID_Blur, wxT("Flou (Blur)\tCtrl-B")) ;
	Bind(wxEVT_MENU, &MyFrame::OnProcessImage, this, ID_Blur) ;

	menuFile3->AppendSeparator();

	menuFile3->Append(ID_Rot90, wxT("Rotation à 90° \tCtrl-Y")) ;
	Bind(wxEVT_MENU, &MyFrame::OnProcessImage, this, ID_Rot90) ;

	menuFile3->Append(ID_RotM90, wxT("Rotation à -90° \tCtrl-U")) ;
	Bind(wxEVT_MENU, &MyFrame::OnProcessImage, this, ID_RotM90) ;

	menuFile3->Append(ID_Rot180, wxT("Rotation à 180° \tCtrl-I")) ;
	Bind(wxEVT_MENU, &MyFrame::OnProcessImage, this, ID_Rot180) ;

	menuFile3->AppendSeparator();

	menuFile3->Append(ID_Negative, wxT("Négatif \tCtrl-N")) ;
	Bind(wxEVT_MENU, &MyFrame::OnProcessImage, this, ID_Negative) ;

	menuFile3->Append(ID_Desaturate, wxT("Désaturation \tCtrl-D")) ;
	Bind(wxEVT_MENU, &MyFrame::OnProcessImage, this, ID_Desaturate) ;

	menuFile3->Append(ID_VLum, wxT("Vitesse Lumière \tAlt-V")) ;
	Bind(wxEVT_MENU, &MyFrame::OnProcessImage, this, ID_VLum) ;

	wxMenuBar *menuBar = new wxMenuBar ;
	menuBar->Append( menuFile, wxT("Fichier" )) ;
    menuBar->Append( menuFile3, wxT("Outils" )) ;
	menuBar->Append( menuFile2, wxT("Options" )) ;
	SetMenuBar(menuBar) ;

    CreateStatusBar();
    Bind(wxEVT_MOTION, &MyFrame::OnSouris, this) ;
}

void MyFrame::OnHello(wxCommandEvent& event)
{
	wxLogMessage(wxT("Par Mathilde Benetti & Thomas Laurent"));
}

void MyFrame::OnExit(wxCommandEvent& event)
{
	Close( true );
}

void MyFrame::OnResize(wxCommandEvent& event)
{
    int w,h;

    if (event.GetId() == ID_PLarge) {
        GetSize(&w,&h);
        SetSize(w+100,h+100);
    } else {
        GetSize(&w,&h);

        if (w < 400 || h < 400) {
            w = 400;
            h = 400;
        }

        SetSize(w-100,h-100);
    }
}

void MyFrame::OnSouris(wxMouseEvent& event)
{
    wxPoint CoordSouris = event.GetPosition();
    wxString s;
    s.sprintf("%d ; %d",CoordSouris.x,CoordSouris.y);
    SetStatusText(s);
}

void MyFrame::OnOpenImage(wxCommandEvent& event)
{
    wxString nomImage = wxFileSelector();
    if (nomImage.empty()) {
        wxLogMessage(wxT("Vous n'avez pas choisi d'image"));
    } else {
        m_panel->OpenImage(nomImage);
    }
}

void MyFrame::OnSaveImage (wxCommandEvent& event)
{
    wxString nomImage = wxSaveFileSelector(wxT("Sauvegarde"),wxT(".png"));
    if (nomImage.empty()) {
        wxLogMessage(wxT("Vous n'avez pas sauvegardé l'image"));
    } else {
        m_panel->SaveImage(nomImage);
    }
}

void MyFrame::OnProcessImage (wxCommandEvent& event)
{
    clock_t delai = clock();

    switch (event.GetId()) {
        case ID_HMirror: m_panel->MirrorImage(true); break;
        case ID_VMirror: m_panel->MirrorImage(false); break;
        case ID_Blur: m_panel->BlurImage(); break;
        case ID_Rot90: m_panel->RotateImage(90); break;
        case ID_Rot180: m_panel->RotateImage(180); break;
        case ID_RotM90: m_panel->RotateImage(270); break;
        case ID_Negative: m_panel->NegativeImage(); break;
        case ID_Desaturate : m_panel->DesaturateImage(); break;
        case ID_VLum : m_panel->VLumImage(); break;
    }

    delai = clock() - delai;
    GetStatusBar()->SetStatusText("Temps Processus : " + std::to_string(((float)delai)/CLOCKS_PER_SEC) + " sec");

    Refresh();
}


////////////////////PANEL////////////////////


MyPanel::MyPanel(wxWindow *parent)
: wxPanel(parent)
{
    Bind(wxEVT_PAINT, &MyPanel::OnPaint, this);
}

MyPanel::~MyPanel()
{

}

void MyPanel::OpenImage(wxString fileName)
{
    if (m_image != nullptr) {
        delete m_image;
        m_image = new MyImage(fileName);
    } else {
        m_image = new MyImage(fileName);
    }
    m_width = m_image->GetWidth();
    m_height = m_image->GetHeight();
    this->GetParent()->SetClientSize(m_width, m_height);
    Refresh();
}

void MyPanel::OnPaint(wxPaintEvent &WXUNUSED(event))
{
    if (m_image != nullptr) {
        m_bitmap = wxBitmap(*m_image);
        wxPaintDC dc (this);
        dc.DrawBitmap(m_bitmap, wxPoint(0,0));
    }
}

void MyPanel::MirrorImage(bool horizontal){

    if (m_image == nullptr) {
            wxLogMessage(wxT("Vous n'avez pas d'image à modifier"));
    } else {
        if (horizontal == true) {
            *m_image = m_image->Mirror(true);
        } else {
            *m_image = m_image->Mirror(false);
        }
    }

}

void MyPanel::BlurImage()
{

    if (m_image == nullptr) {
        wxLogMessage(wxT("Vous n'avez pas d'image à flouter"));
    } else {
        *m_image = m_image->Blur(3);
    }

}

void MyPanel::RotateImage(int angle)
{
    if (m_image == nullptr) {
        wxLogMessage(wxT("Vous n'avez pas d'image à faire pivoter"));
    } else {
        if (angle == 90){
            *m_image = m_image->Rotate90(true);
        } else if (angle == 180){
            *m_image = m_image->Rotate180();
        } else {
            *m_image = m_image->Rotate90(false);
        }
    }
}

void MyPanel::NegativeImage()
{
    if (m_image == nullptr) {
        wxLogMessage(wxT("Vous n'avez pas d'image à modifier"));
    } else {
        m_image->Negative();
    }
}

void MyPanel::DesaturateImage()
{
    if (m_image == nullptr) {
        wxLogMessage(wxT("Vous n'avez pas d'image à modifier"));
    } else {
        m_image->Desaturate();
    }
}

void MyPanel::VLumImage()
{
    if (m_image == nullptr) {
        wxLogMessage(wxT("Vous n'avez pas d'image à modifier"));
    } else {
        m_image->VLum();
    }
}

void MyPanel::SaveImage(wxString fileName)
{
    if (m_image == nullptr) {
        wxLogMessage(wxT("Vous n'avez pas d'image à sauvegarder"));
    } else {
        m_image->SaveFile(fileName+".png");
    }
}

int MyPanel::getWidth(){
    return this->m_width;
}

int MyPanel::getHeight(){
    return this->m_height;
}


