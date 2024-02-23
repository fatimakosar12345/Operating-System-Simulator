#include <iostream>
#include <ctime>
#include <gtkmm.h>

class DigitalClock : public Gtk::Window {
public:
  DigitalClock() {
    set_title("Digital Clock");
    set_default_size(200, 100);

    label.set_alignment(Gtk::ALIGN_CENTER);
    label.set_padding(10, 0);
    label.set_size_request(200, 60);
    add(label);

    Glib::signal_timeout().connect(
      sigc::mem_fun(*this, &DigitalClock::updateTime), 1000);

    updateTime();
    show_all_children();
  }

private:
  bool updateTime() {
    std::time_t now = std::time(nullptr);
    std::tm* current_time = std::localtime(&now);

    int hours = current_time->tm_hour;
    int minutes = current_time->tm_min;
    int seconds = current_time->tm_sec;

    char time_str[9];
    std::strftime(time_str, sizeof(time_str), "%H:%M:%S", current_time);

    char date_str[12];
    std::strftime(date_str, sizeof(date_str), "%d-%m-%Y", current_time);

    char day_str[10];
    std::strftime(day_str, sizeof(day_str), "%A", current_time);

    std::string display_text = time_str + std::string("\n") + day_str + std::string(", ") + date_str;
    label.set_text(display_text);

    return true;
  }

  Gtk::Label label;
};
void time()
{ 
  auto app = Gtk::Application::create();

  DigitalClock clock;
  app->run(clock);
}
//int main(int argc, char* argv[]) {
  //auto app = Gtk::Application::create(argc, argv);

  //DigitalClock clock;
  //return app->run(clock);
//}
