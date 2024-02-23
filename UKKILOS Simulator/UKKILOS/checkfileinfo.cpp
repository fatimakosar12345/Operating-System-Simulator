#include <iostream>
#include <string>
#include <sys/stat.h>
#include <ctime>
#include <gtkmm.h>

void on_button_clicked(Gtk::Entry* entry, Gtk::Label* resultLabel) {
    std::string filePath = entry->get_text();
    struct stat fileStat;

    if (stat(filePath.c_str(), &fileStat) == 0) {
        std::string creationTime = std::ctime(&fileStat.st_ctime);
        std::string modificationTime = std::ctime(&fileStat.st_mtime);
        double fileSizeMB = static_cast<double>(fileStat.st_size) / (1024 * 1024);

        resultLabel->set_text("File Location: " + filePath +
                              "\nCreation Time: " + creationTime +
                              "Modification Time: " + modificationTime +
                              "File Size: " + std::to_string(fileSizeMB) + " MB");
    } else {
        resultLabel->set_text("Failed to get file info!");
    }
}
void checkinfo()
{
  auto app = Gtk::Application::create();

    Gtk::Window window;
    window.set_default_size(400, 200);

    Gtk::VBox vbox;
    window.add(vbox);

    Gtk::Label label("Enter the file path:");
    vbox.pack_start(label);

    Gtk::Entry entry;
    vbox.pack_start(entry);

    Gtk::Button button("Check File Info");
    vbox.pack_start(button);

    Gtk::Label resultLabel;
    vbox.pack_start(resultLabel);

    button.signal_clicked().connect(sigc::bind<Gtk::Entry*, Gtk::Label*>(sigc::ptr_fun(&on_button_clicked), &entry, &resultLabel));

    window.show_all();

    app->run(window);
}

//int main(int argc, char* argv[]) {
  //  auto app = Gtk::Application::create(argc, argv);

    //Gtk::Window window;
    //window.set_default_size(400, 200);

    //Gtk::VBox vbox;
    //window.add(vbox);

    //Gtk::Label label("Enter the file path:");
    //vbox.pack_start(label);

    //Gtk::Entry entry;
    //vbox.pack_start(entry);

    //Gtk::Button button("Check File Info");
    //vbox.pack_start(button);

    //Gtk::Label resultLabel;
    //vbox.pack_start(resultLabel);

    //button.signal_clicked().connect(sigc::bind<Gtk::Entry*, Gtk::Label*>(sigc::ptr_fun(&on_button_clicked), &entry, &resultLabel));

    //window.show_all();

    //return app->run(window);
//}
