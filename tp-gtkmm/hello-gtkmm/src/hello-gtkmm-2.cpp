
#include <gtkmm.h>

///////////////////////////////////////////////////////////////////////////////
// window
///////////////////////////////////////////////////////////////////////////////

class MyWindow : public Gtk::Window {

  Gtk::Box hbox;
  Gtk::Label label;
  // TODO Gtk::Button quitButton;

  public:

  MyWindow():
    hbox(Gtk::Orientation::HORIZONTAL),
    label("hello")
  {

      // configure window
      set_title("hello-gtkmm-2");

      // main hbox
      set_child(hbox);

      // label
      label.set_size_request(150, -1);
      hbox.append(label);

      // button 
      // TODO

  }

};

///////////////////////////////////////////////////////////////////////////////
// application
///////////////////////////////////////////////////////////////////////////////

int main(int argc, char ** argv) {
  auto app = Gtk::Application::create();
  return app->make_window_and_run<MyWindow>(argc, argv);
}

