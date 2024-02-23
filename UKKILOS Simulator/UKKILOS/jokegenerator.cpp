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
    set_title("Joke Generator");
    set_size_request(400, 300);

    // Create the UI elements
    Gtk::Box* vbox = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL, 10));
    Gtk::Label* title_label = Gtk::manage(new Gtk::Label("Click the button below to generate a random joke."));
    Gtk::Button* generate_button = Gtk::manage(new Gtk::Button("Generate Joke"));
    joke_label_ = Gtk::manage(new Gtk::Label());

    // Connect the button to the generate_joke() method
    generate_button->signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::generate_joke));

    // Add the UI elements to the window
    vbox->pack_start(*title_label, Gtk::PACK_SHRINK);
    vbox->pack_start(*generate_button, Gtk::PACK_SHRINK);
    vbox->pack_start(*joke_label_, Gtk::PACK_SHRINK);
    add(*vbox);
    show_all_children();
  }

protected:
  // UI elements
  Gtk::Label* joke_label_;

  // Generates a random joke and sets the joke_label_ text
  void generate_joke() {
    // Open the file
    std::ifstream file("joke.txt");
    if (!file.is_open()) {
      joke_label_->set_text("Failed to open file.");
      return;
    }

    // Read the jokes into a vector
    std::vector<std::string> jokes;
    std::string joke;
    while (std::getline(file, joke)) {
      jokes.push_back(joke);
    }

    // Generate a random index and set the joke_label_ text
    std::srand(std::time(nullptr));
    int index = std::rand() % jokes.size();
    joke_label_->set_text(jokes[index]);

    // Close the file
    file.close();
  }
};

void joke()
{
  // Initialize Gtkmm
  auto app = Gtk::Application::create();

  // Create the main window and run the app
  MainWindow window;
  app->run(window);
}

//int main(int argc, char** argv) {
  // Initialize Gtkmm
  //auto app = Gtk::Application::create(argc, argv);

  // Create the main window and run the app
  //MainWindow window;
  //return app->run(window);
//}

