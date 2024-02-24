#ifndef loggerGUI_H
#define loggerGUI_H


#include <gtkmm.h>



class LoggerGUI : public Gtk::ApplicationWindow{
     public:
       LoggerGUI();

     private:

     protected:
      Gtk::Box m_Box;
      Glib::RefPtr<Gtk::Builder> m_refBuilder;

};





#endif