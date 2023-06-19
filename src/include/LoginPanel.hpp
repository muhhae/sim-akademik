#include <wx/wx.h>

class LoginPanel : public wxPanel
{
    private :
        wxTextCtrl* userID;
        wxTextCtrl* password;
        wxImage* bg;
        wxPaintDC* dc;
    public :
        LoginPanel(wxFrame* parent);
        void login(wxEvent& evt);
        void drawBG(wxPaintEvent& evt);
};