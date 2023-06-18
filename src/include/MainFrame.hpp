#ifndef _MAINFRAME_HPP
#define _MAINFRAME_HPP

#include <wx/wx.h>
#include <wx/listctrl.h>
#include <vector>

#include "CustomParser.hpp"

class MainFrame : public wxFrame
{
    public: 
        MainFrame(const wxString& title);
        void logOut(wxEvent& evt);
        void login(std::string userID, std::string password);
    private:
        wxPanel* panel;
        wxBoxSizer* base;

        dt::CustomParser mahasiswa;
        dt::CustomParser dosen;
        dt::CustomParser tendik;
        dt::CustomParser currentParser;
};

#endif