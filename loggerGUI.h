#ifndef loggerGUI_H
#define loggerGUI_H

#include <gtkmm.h>

class LoggerGUI : public Gtk::ApplicationWindow
{
public:
  LoggerGUI();
  void showAbout();

private:
  Gtk::Box m_Box;
  Glib::RefPtr<Gtk::Builder> m_refBuilder;
};

#endif
