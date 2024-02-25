#include "loggerGUI.h"
#include "iostream"

LoggerGUI::LoggerGUI()
{

   set_border_width(10);
   // set_title("AKLogger");
   set_default_size(700, 600);
   add(m_Box);

   m_refBuilder = Gtk::Builder::create();

   show_all();
}

void LoggerGUI::showAbout()
{

   Gtk::MessageDialog dialog(*this, "This is a Logging Utility for Serial Port",
                             false /* use_markup */, Gtk::MESSAGE_INFO,
                             Gtk::BUTTONS_CLOSE);
   dialog.set_secondary_text(
       "Developers : Budhi Sagar Pande \n\
                     Ananth Kini");

   dialog.run();
}
