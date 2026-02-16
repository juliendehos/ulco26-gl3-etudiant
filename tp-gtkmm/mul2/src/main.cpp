
#include <gtkmm.h>

///////////////////////////////////////////////////////////////////////////////
// window
///////////////////////////////////////////////////////////////////////////////

class MyWindow : public Gtk::Window {

  public:

    MyWindow() {

      // configure window
      set_title("mul2");

      // main hbox
      // TODO

      // entry
      // TODO

      // mul2 button
      // TODO

      // result label
      // TODO

      // quit button 
      // TODO

      // handlers
      // TODO mul2
      // TODO quit

    }

};

///////////////////////////////////////////////////////////////////////////////
// application
///////////////////////////////////////////////////////////////////////////////

int main(int argc, char ** argv) {
  auto app = Gtk::Application::create();
  return app->make_window_and_run<MyWindow>(argc, argv);
}

