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
        dt::CustomParser dosen;
        dt::CustomParser tendik;

        dt::CustomParser currentParser;

        wxListView* list;
        wxChoice* jenisCtrl;

        void onListResize(wxEvent& evt);
        void listUpdate(dt::CustomParser& customParser, std::vector<std::string> str);
        void addToList(int index, std::vector<std::string> str);
        void okbt(wxEvent& evt);
        void onChoiceUpdate(wxEvent& evt);
        void detailClicked(wxEvent& evt);
};  

#endif