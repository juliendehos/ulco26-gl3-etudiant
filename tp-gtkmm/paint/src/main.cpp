
#include "Ui.hpp"

int main(int argc, char ** argv) {
  auto app = Gtk::Application::create();
  return app->make_window_and_run<MyWindow>(argc, argv);
}

