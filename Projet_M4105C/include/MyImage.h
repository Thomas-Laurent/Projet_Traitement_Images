#ifndef MYIMAGE_H
#define MYIMAGE_H
#include <wx/wx.h>


class MyImage : public wxImage
{
    public:
        MyImage(const wxString& fileName) ;
        MyImage(wxImage image) ;
        MyImage(int largeur, int hauteur);
        MyImage() ;
        virtual ~MyImage();
        void Negative();
        void Desaturate();
        void VLum();
        void Crop(wxRect rect);

    private:

};

#endif // MYIMAGE_H

