#include "MyImage.h"

MyImage::MyImage(const wxString& fileName)
: wxImage(fileName)
{
}

MyImage::MyImage(wxImage image)
: wxImage(image)
{
}



MyImage::MyImage(int largeur, int hauteur)
: wxImage(largeur, hauteur)
{
}

MyImage::MyImage()
: wxImage()
{
}



MyImage::~MyImage()
{
}

void MyImage::Negative(){
    unsigned char * data = this->GetData();
    int taille = this->GetHeight()*this->GetWidth()*3;


    for(int i = 0; i < taille; i++){
        data[i] = 255 - data[i];
    }
}

void MyImage::Desaturate(){
    unsigned char * data = this->GetData();
    int taille = this->GetHeight()*this->GetWidth()*3;

    unsigned char Lumi;

    for(int i = 0; i < taille; i+=3){
        Lumi = 0.2126*data[i] + 0.7152*data[i+1] + 0.0722*data[i+2];

        for(int j = i; j < i+3; j++){
            data[j] = Lumi;
        }
    }
}

void MyImage::VLum(){
    unsigned char * data = this->GetData();
    int taille = this->GetHeight()*this->GetWidth()*3;

    unsigned char Lumi;

    for(int i = 0; i < taille; i++){
        Lumi = 0.2126*data[i] + 0.7152*data[i+1] + 0.0722*data[i+2];

        for(int j = i; j < i+3; j++){
            data[j] = Lumi;
        }
    }
}
