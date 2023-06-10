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
    private:
        dt::CustomParser mahasiswa;
        wxListView* list;
        void onListResize(wxEvent& evt);
        void listUpdate(dt::CustomParser& customParser);
        void addToList(int index, std::vector<std::string> str);
        void okbt(wxEvent& evt);
};  

#endif