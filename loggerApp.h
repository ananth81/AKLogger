#ifndef LOGGER_APP_H
#define LOGGER_APP_H

#include <gtkmm.h>

class LoggerApplication : public Gtk::Application
{
protected:
  LoggerApplication();

public:
  static Glib::RefPtr<LoggerApplication> create();

protected:
  // Overrides of default signal handlers:
  void on_startup() override;
  void on_activate() override;

private:
  void create_window();

  void on_window_hide(Gtk::Window *window);

  void on_menu_file_quit();
  void on_menu_help_about();
  void on_menu_file_new_logs();
  void on_menu_port_open();
  void on_menu_port_close();

  Glib::RefPtr<Gtk::Builder> m_refBuilder;
};

#endif /* LOGGER_APP_H */
