#include <iostream>
#include <gtkmm.h>

// Function to delete a file
void deleteFile(const std::string& filename) {
    int result = std::remove(filename.c_str());
    if (result == 0) {
        std::cout << "File deleted successfully!\n";
    } else {
        std::cerr << "Error deleting file!\n";
    }
}

void deletefile()
{
  Gtk::Main kit();

    Gtk::Window window;
    window.set_default_size(400, 300);
    window.set_title("File Deletion");

    Gtk::VBox mainBox;
    window.add(mainBox);

    Gtk::Label label("Enter the file name:");
    mainBox.pack_start(label, Gtk::PACK_SHRINK);

    Gtk::Entry entry;
    mainBox.pack_start(entry, Gtk::PACK_SHRINK);

    Gtk::Button deleteButton("Delete File");
    //Gtk::Buttonoverride_background_color(Gdk::RGBA("red"), Gtk::STATE_FLAG_NORMAL);
    deleteButton.signal_clicked().connect([&]() {
        std::string filename = entry.get_text();
        deleteFile(filename);
    });
    
    mainBox.pack_start(deleteButton, Gtk::PACK_SHRINK);

    window.show_all();

    Gtk::Main::run(window);

}

//int main(int argc, char* argv[]) {
  //  Gtk::Main kit(argc, argv);

    //Gtk::Window window;
    //window.set_default_size(400, 300);
    //window.set_title("File Deletion");

    //Gtk::VBox mainBox;
    //window.add(mainBox);

    //Gtk::Label label("Enter the file name:");
    //mainBox.pack_start(label, Gtk::PACK_SHRINK);

    //Gtk::Entry entry;
    //mainBox.pack_start(entry, Gtk::PACK_SHRINK);

    //Gtk::Button deleteButton("Delete File");
    //Gtk::Buttonoverride_background_color(Gdk::RGBA("red"), Gtk::STATE_FLAG_NORMAL);
    //deleteButton.signal_clicked().connect([&]() {
    //    std::string filename = entry.get_text();
      //  deleteFile(filename);
    //});
    
    //mainBox.pack_start(deleteButton, Gtk::PACK_SHRINK);

    //window.show_all();

    //Gtk::Main::run(window);

    //return 0;
//}
