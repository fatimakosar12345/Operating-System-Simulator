#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <gtkmm.h>

class MainWindow : public Gtk::Window {
public:
  MainWindow() {
    // Set the window title and size
    set_title("Novel Reader");
    set_size_request(400, 300);

    // Create the UI elements
    Gtk::Box* vbox = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL, 10));
    Gtk::Label* title_label = Gtk::manage(new Gtk::Label("Select a novel to read:"));
    Gtk::Box* button_box = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL, 10));
    Gtk::ScrolledWindow* scrolled_window = Gtk::manage(new Gtk::ScrolledWindow());
    scrolled_window->set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
    novel_textview_ = Gtk::manage(new Gtk::TextView());

    // Add the UI elements to the window
    vbox->pack_start(*title_label, Gtk::PACK_SHRINK);
    vbox->pack_start(*scrolled_window);
    scrolled_window->add(*button_box);
    button_box->set_border_width(10);
    vbox->pack_start(*novel_textview_);
    add(*vbox);

    // Load the novel names from the file system and create a button for each name
    std::ifstream name_file("names.txt");
    std::string name;
    while (std::getline(name_file, name)) {
      Gtk::Button* button = Gtk::manage(new Gtk::Button(name));
      button_box->pack_start(*button, Gtk::PACK_SHRINK);
      button->signal_clicked().connect(sigc::bind<std::string>(sigc::mem_fun(*this, &MainWindow::load_novel), name));
    }
    name_file.close();

    show_all_children();
  }

protected:
  // UI elements
  Gtk::TextView* novel_textview_;

  // Loads the novel with the given name from the file system and sets the novel_textview_ text
  void load_novel(std::string name) {
    // Open the file
    std::ifstream file(name + ".txt");
    if (!file.is_open()) {
      novel_textview_->get_buffer()->set_text("Failed to open file.");
      return;
    }

    // Read the novel into a string
    std::string novel((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

    // Set the novel_textview_ text
    novel_textview_->get_buffer()->set_text(novel);

    // Close the file
    file.close();
  }
};

void Novel()
{
  Gtk::Main kit;
  MainWindow window;

  // Display the window and run the application
  Gtk::Window* pWindow = &window;
  pWindow->show_all();

  Gtk::Main::run(*pWindow);
}

//int main() {
  //Gtk::Main kit;
  //MainWindow window;

  // Display the window and run the application
  //Gtk::Window* pWindow = &window;
  //pWindow->show_all();
  //Gtk::Main::run(*pWindow);

  //return 0;
//}
