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
