#include <iostream>
#include <gtkmm.h>

class TimerWindow : public Gtk::Window {
public:
  TimerWindow() {
    set_title("Timer");
    set_default_size(200, 150);

    // Box container for widgets
    Gtk::Box* box = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL, 10));
    add(*box);

    // Entry boxes for hours, minutes, and seconds
    Gtk::Box* timeBox = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL, 5));
    labelHr.set_text("Hours:");
    timeBox->pack_start(labelHr);
    timeBox->pack_start(entryHr);
    labelMin.set_text("Minutes:");
    timeBox->pack_start(labelMin);
    timeBox->pack_start(entryMin);
    labelSec.set_text("Seconds:");
    timeBox->pack_start(labelSec);
    timeBox->pack_start(entrySec);
    box->pack_start(*timeBox);

    // Start button
    startButton.set_label("Start");
    startButton.signal_clicked().connect(sigc::mem_fun(*this, &TimerWindow::startTimer));
    box->pack_start(startButton);

    // Stop button
    stopButton.set_label("Stop");
    stopButton.signal_clicked().connect(sigc::mem_fun(*this, &TimerWindow::stopTimer));
    box->pack_start(stopButton);

// Resume button
    resumeButton.set_label("Resume");
    resumeButton.signal_clicked().connect(sigc::mem_fun(*this, &TimerWindow::resumeTimer));
    box->pack_start(resumeButton);
    
    // Reset button
    resetButton.set_label("Reset");
    resetButton.signal_clicked().connect(sigc::mem_fun(*this, &TimerWindow::resetTimer));
    box->pack_start(resetButton);

    

    // Label for displaying timer
    label.set_alignment(Gtk::ALIGN_CENTER);
    label.set_padding(10, 0);
    label.set_size_request(200, 60);
    box->pack_start(label);

    show_all_children();
  }

private:
  int totalTime = 0;
  sigc::connection timeoutConnection;

  void startTimer() {
    int hours = std::stoi(entryHr.get_text());
    int minutes = std::stoi(entryMin.get_text());
    int seconds = std::stoi(entrySec.get_text());

    totalTime = hours * 3600 + minutes * 60 + seconds;

    entryHr.set_sensitive(false);
    entryMin.set_sensitive(false);
    entrySec.set_sensitive(false);
    startButton.set_sensitive(false);

    timeoutConnection = Glib::signal_timeout().connect_seconds(
      sigc::mem_fun(*this, &TimerWindow::updateTime), 1);
  }

  void stopTimer() {
    entryHr.set_sensitive(true);
    entryMin.set_sensitive(true);
    entrySec.set_sensitive(true);
    startButton.set_sensitive(true);

    timeoutConnection.disconnect();
  }

  void resetTimer() {
    stopTimer();
    label.set_text("");
    entryHr.set_text("");
    entryMin.set_text("");
    entrySec.set_text("");
  }

  void resumeTimer() {
    entryHr.set_sensitive(false);
    entryMin.set_sensitive(false);
    entrySec.set_sensitive(false);
    startButton.set_sensitive(false);

    timeoutConnection = Glib::signal_timeout().connect_seconds(
      sigc::mem_fun(*this, &TimerWindow::updateTime), 1);
  }

  bool updateTime() {
    if (totalTime > 0) {
      int hours = totalTime / 3600;
      int minutes = (totalTime % 3600) / 60;
      int seconds = (totalTime % 3600) % 60;

      char time_str[9];
      std::sprintf(time_str, "%02d:%02d:%02d", hours, minutes, seconds);

      std::string display_text = time_str;
      label.set_text(display_text);

      totalTime--;
      return true;
    } else {
      label.set_text("Time's up!");
      stopTimer();
      return false;
    }
  }

  Gtk::Label label;
  Gtk::Label labelHr;
  Gtk::Label labelMin;
  Gtk::Label labelSec;
  Gtk::Entry entryHr;
  Gtk::Entry entryMin;
  Gtk::Entry entrySec;
  Gtk::Button startButton;
  Gtk::Button stopButton;
  Gtk::Button resetButton;
  Gtk::Button resumeButton;
};

void timer()
{
  auto app = Gtk::Application::create();

  TimerWindow window;
  window.set_position(Gtk::WIN_POS_CENTER);
  app->run(window);
}

//int main(int argc, char* argv[]) {
  //auto app = Gtk::Application::create(argc, argv);

  //TimerWindow window;
  //window.set_position(Gtk::WIN_POS_CENTER);
  //return app->run(window);
//}
