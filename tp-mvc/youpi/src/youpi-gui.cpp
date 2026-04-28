
#include "RendererCairo.hpp"
#include "Scene.hpp"

#include <gtkmm.h>

const int gWinWidth = 400;
const int gWinHeight = 400;

class MyView : public Gtk::DrawingArea {
  private:
    Scene _scene;

  public:
    MyView(Scene && scene) :
      _scene(std::move(scene))
    { 
      set_content_width(gWinWidth);
      set_content_height(gWinHeight);
      set_draw_func(sigc::mem_fun(*this, &MyView::on_draw));
    }

  protected:
    void on_draw(const Cairo::RefPtr<Cairo::Context>& cr, int width, int height) {
      RendererCairo renderer(cr, width, height);
      _scene.render(renderer);
    }

};

class MyWindow : public Gtk::Window {

  public:
    MyWindow() {
        set_title("Youpi");

        auto notebook = Gtk::make_managed<Gtk::Notebook>();
        set_child(*notebook);

        auto view1 = Gtk::make_managed<MyView>(mkHumanScene());
        notebook->append_page(*view1, "Human");

        auto view2 = Gtk::make_managed<MyView>(mkFaceScene());
        notebook->append_page(*view2, "Face");

    }
};

int main(int argc, char ** argv) {
  auto app = Gtk::Application::create();
  return app->make_window_and_run<MyWindow>(argc, argv);
}

