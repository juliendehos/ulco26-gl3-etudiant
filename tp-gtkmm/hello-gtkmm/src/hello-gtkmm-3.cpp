
#include <gtkmm.h>

///////////////////////////////////////////////////////////////////////////////
// window
///////////////////////////////////////////////////////////////////////////////

class MyWindow : public Gtk::Window {

  public:

    MyWindow() {

      // configure window
      set_title("hello-gtkmm-3");

      // main hbox
      auto hbox = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::HORIZONTAL);
      set_child(*hbox);

      // label
      auto label = Gtk::make_managed<Gtk::Label>("hello");
      label->set_size_request(150, -1);
      hbox->append(*label);

      // button 
      auto quitButton = Gtk::make_managed<Gtk::Button>("Quit");
      quitButton->set_hexpand(true);
      hbox->append(*quitButton);
      quitButton->signal_clicked().connect([this](){ 
          this->get_application()->quit();
        });

    }

};

///////////////////////////////////////////////////////////////////////////////
// application
///////////////////////////////////////////////////////////////////////////////

int main(int argc, char ** argv) {
  auto app = Gtk::Application::create();
  return app->make_window_and_run<MyWindow>(argc, argv);
}

