#include <iostream>
#include <fstream>
#include <gtkmm.h>

// Function to create a file
void createFile(const std::string& filename) {
    std::ofstream file(filename);
    if (file) {
        std::cout << "File created successfully!\n";
    } else {
        std::cerr << "Error creating file!\n";
    }
}
void createfile()
{
  Gtk::Main kit();

    Gtk::Window window;
    window.set_default_size(400, 300);
    window.set_title("File Creation");

    Gtk::VBox mainBox;
    window.add(mainBox);

    Gtk::Label label("Enter the file name:");
    mainBox.pack_start(label, Gtk::PACK_SHRINK);

    Gtk::Entry entry;
    mainBox.pack_start(entry, Gtk::PACK_SHRINK);

    Gtk::Button createButton("Create File");
    createButton.signal_clicked().connect([&]() {
        std::string filename = entry.get_text();
        createFile(filename);
    });

    mainBox.pack_start(createButton, Gtk::PACK_SHRINK);

    window.show_all();

    Gtk::Main::run(window);
}
//int main(int argc, char* argv[]) {
    //Gtk::Main kit(argc, argv);

    //Gtk::Window window;
    //window.set_default_size(400, 300);
    //window.set_title("File Creation");

    //Gtk::VBox mainBox;
    //window.add(mainBox);

    //Gtk::Label label("Enter the file name:");
    //mainBox.pack_start(label, Gtk::PACK_SHRINK);

    //Gtk::Entry entry;
    //mainBox.pack_start(entry, Gtk::PACK_SHRINK);

    //Gtk::Button createButton("Create File");
    //createButton.signal_clicked().connect([&]() {
      //  std::string filename = entry.get_text();
       // createFile(filename);
    //});

    //mainBox.pack_start(createButton, Gtk::PACK_SHRINK);

    //window.show_all();

    //Gtk::Main::run(window);

    //return 0;
    //}
