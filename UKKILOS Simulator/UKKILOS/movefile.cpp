#include <iostream>
#include <cstdio>
#include <gtkmm.h>

void on_button_clicked(Gtk::Entry* fileEntry, Gtk::Entry* pathEntry) {
    std::string fileName = fileEntry->get_text();
    std::string destinationPath = pathEntry->get_text();

    std::string currentPath = "./" + fileName;
    std::string newPath = destinationPath + "/" + fileName;

    int result = std::rename(currentPath.c_str(), newPath.c_str());
    if (result == 0) {
        std::cout << "File moved successfully.\n";
    } else {
        std::perror("Error moving file");
    }
}

void movefile()
{
  auto app = Gtk::Application::create();

    Gtk::Window window;
    window.set_default_size(300, 200);

    Gtk::VBox vbox;
    window.add(vbox);

    Gtk::Label fileLabel("File Name:");
    vbox.pack_start(fileLabel);

    Gtk::Entry fileEntry;
    vbox.pack_start(fileEntry);

    Gtk::Label pathLabel("Destination Path:");
    vbox.pack_start(pathLabel);

    Gtk::Entry pathEntry;
    vbox.pack_start(pathEntry);

    Gtk::Button button("Move File");
    button.signal_clicked().connect(sigc::bind<Gtk::Entry*, Gtk::Entry*>(sigc::ptr_fun(&on_button_clicked), &fileEntry, &pathEntry));
    vbox.pack_start(button);

    window.show_all();

    app->run(window);
}

//int main(int argc, char* argv[]) {
  //  auto app = Gtk::Application::create(argc, argv);

    //Gtk::Window window;
    //window.set_default_size(300, 200);

    //Gtk::VBox vbox;
    //window.add(vbox);

    //Gtk::Label fileLabel("File Name:");
    //vbox.pack_start(fileLabel);

    //Gtk::Entry fileEntry;
    //vbox.pack_start(fileEntry);

    //Gtk::Label pathLabel("Destination Path:");
    //vbox.pack_start(pathLabel);

    //Gtk::Entry pathEntry;
    //vbox.pack_start(pathEntry);

    //Gtk::Button button("Move File");
    //button.signal_clicked().connect(sigc::bind<Gtk::Entry*, Gtk::Entry*>(sigc::ptr_fun(&on_button_clicked), &fileEntry, &pathEntry));
    //vbox.pack_start(button);

    //window.show_all();

    //return app->run(window);
//}
