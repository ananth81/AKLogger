#include "loggerApp.h"
#include "loggerGUI.h"
#include <iostream>

LoggerApplication::LoggerApplication()
    : Gtk::Application("AKLogger")
{
  Glib::set_application_name("AKLogger");
}

Glib::RefPtr<LoggerApplication> LoggerApplication::create()
{
  return Glib::RefPtr<LoggerApplication>(new LoggerApplication());
}

void LoggerApplication::on_startup()
{
  // Call the base class's implementation:
  Gtk::Application::on_startup();

  // Create actions for menus and toolbars.
  // We can use add_action() because Gtk::Application derives from Gio::ActionMap.

  // File|New sub menu:
  add_action("newlogs",
             sigc::mem_fun(*this, &LoggerApplication::on_menu_file_new_logs));

  add_action("portopen",
             sigc::mem_fun(*this, &LoggerApplication::on_menu_port_open));

  add_action("portclose",
             sigc::mem_fun(*this, &LoggerApplication::on_menu_port_close));

  // File menu:
  add_action("quit", sigc::mem_fun(*this, &LoggerApplication::on_menu_file_quit));

  // Help menu:
  add_action("about", sigc::mem_fun(*this, &LoggerApplication::on_menu_help_about));

  m_refBuilder = Gtk::Builder::create();

  // Layout the actions in a menubar and an application menu:
  Glib::ustring ui_info =
      "<interface>"
      "  <!-- menubar -->"
      "  <menu id='menu'>"
      "    <submenu>"
      "      <attribute name='label' translatable='yes'>_File</attribute>"
      "      <section>"
      "        <item>"
      "          <attribute name='label' translatable='yes'>New _Logs...</attribute>"
      "          <attribute name='action'>app.newlogs</attribute>"

      "        </item>"
      "      </section>"
      "      <section>"
      "        <item>"
      "          <attribute name='label' translatable='yes'>_Quit</attribute>"
      "          <attribute name='action'>app.quit</attribute>"
      "          <attribute name='accel'>&lt;Primary&gt;q</attribute>"
      "        </item>"
      "      </section>"
      "    </submenu>"
      "    <submenu>"
      "      <attribute name='label' translatable='yes'>_Ports</attribute>"
      "      <section>"
      "        <item>"
      "          <attribute name='label' translatable='yes'>_Open</attribute>"
      "          <attribute name='action'>app.portopen</attribute>"
      "        </item>"
      "        <item>"
      "          <attribute name='label' translatable='yes'>_Close</attribute>"
      "          <attribute name='action'>app.portclose</attribute>"
      "        </item>"
      "      </section>"
      "    </submenu>"
      "    <submenu>"
      "      <attribute name='label' translatable='yes'>_Help</attribute>"
      "      <section>"
      "        <item>"
      "          <attribute name='label' translatable='yes'>_About</attribute>"
      "          <attribute name='action'>app.about</attribute>"
      "        </item>"
      "      </section>"
      "    </submenu>"
      "  </menu>"
      "</interface>";

  try
  {
    m_refBuilder->add_from_string(ui_info);
  }
  catch (const Glib::Error &ex)
  {
    std::cerr << "Building menus failed: " << ex.what();
  }

  // Get the menubar and the app menu, and add them to the application:
  auto object = m_refBuilder->get_object("menu");
  auto gmenu = Glib::RefPtr<Gio::Menu>::cast_dynamic(object);

  if (!(gmenu))
  {
    g_warning("GMenu or AppMenu not found");
  }
  else
  {

    set_menubar(gmenu);
  }
}

void LoggerApplication::on_activate()
{
  // std::cout << "debug1: " << G_STRFUNC << std::endl;
  //  The application has been started, so let's show a window.
  //  A real application might want to reuse this window in on_open(),
  //  when asked to open a file, if no changes have been made yet.
  create_window();
}

void LoggerApplication::create_window()
{
  auto win = new LoggerGUI();

  // Make sure that the application runs for as long this window is still open:
  add_window(*win);

  // Delete the window when it is hidden.
  // That's enough for this simple example.
  win->signal_hide().connect(sigc::bind<Gtk::Window *>(
      sigc::mem_fun(*this, &LoggerApplication::on_window_hide), win));
  win->show_all();
}

void LoggerApplication::on_window_hide(Gtk::Window *window)
{
  delete window;
}

void LoggerApplication::on_menu_port_open()
{
  std::cout << "A Port|Open item was selected." << std::endl;
}

void LoggerApplication::on_menu_port_close()
{
  std::cout << "A Port|Close item was selected." << std::endl;
}
void LoggerApplication::on_menu_file_new_logs()
{
  std::cout << "A File|New logs item was selected." << std::endl;
}

void LoggerApplication::on_menu_file_quit()
{
  std::cout << G_STRFUNC << std::endl;
  quit(); // Not really necessary, when Gtk::Widget::hide() is called.

  // Gio::Application::quit() will make Gio::Application::run() return,
  // but it's a crude way of ending the program. The window is not removed
  // from the application. Neither the window's nor the application's
  // destructors will be called, because there will be remaining reference
  // counts in both of them. If we want the destructors to be called, we
  // must remove the window from the application. One way of doing this
  // is to hide the window.
  std::vector<Gtk::Window *> windows = get_windows();
  if (windows.size() > 0)
    windows[0]->hide(); // In this simple case, we know there is only one window.
}

void LoggerApplication::on_menu_help_about()
{
  std::cout << "App|Help|About was selected." << std::endl;
}
