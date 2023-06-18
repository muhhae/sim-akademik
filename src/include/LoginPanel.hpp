#include <wx/wx.h>

class LoginPanel : public wxPanel
{
    private :
        wxTextCtrl* userID;
        wxTextCtrl* password;
    public :
        LoginPanel(wxFrame* parent);
        void login(wxEvent& evt);
};