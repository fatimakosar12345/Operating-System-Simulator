#include <iostream>
#include <string>
#include <sys/stat.h>
#include <ctime>
#include <gtkmm.h>
#include <gdkmm/pixbuf.h>

std::string getExecutablePath() {
    char path[PATH_MAX];
    ssize_t count = readlink("/proc/self/exe", path, PATH_MAX);
    std::string execPath(path, (count > 0) ? count : 0);
    size_t found = execPath.find_last_of('/');
    return execPath.substr(0, found);
}

void on_button_clicked(Gtk::Entry* entry, Gtk::Label* resultLabel, Gtk::Image* image) {
    std::string imageName = entry->get_text();
    std::string imagePath = getExecutablePath() + "/" + imageName;

    struct stat fileStat;

    if (stat(imagePath.c_str(), &fileStat) == 0) {
        std::string creationTime = std::ctime(&fileStat.st_ctime);
        std::string imageSize = std::to_string(fileStat.st_size / 1024) + " KB";
        std::string imageLocation = imagePath;

        resultLabel->set_text("Image Name: " + imageName + "\nCreation Time: " + creationTime + "Image Size: " + imageSize + "\nImage Location: " + imageLocation);

        // Load the image file
        Glib::RefPtr<Gdk::Pixbuf> originalPixbuf = Gdk::Pixbuf::create_from_file(imagePath);

        // Calculate the desired width and height
        int desiredWidth = 400;
        int desiredHeight = 300;

        // Scale the image to the desired dimensions
        Glib::RefPtr<Gdk::Pixbuf> resizedPixbuf = originalPixbuf->scale_simple(desiredWidth, desiredHeight, Gdk::INTERP_BILINEAR);

        // Set the resized image in the image widget
        image->set(resizedPixbuf);
    } else {
        resultLabel->set_text("Failed to get file info!");
    }
}
void imageviewer()
{
  auto app = Gtk::Application::create();

    Gtk::Window window;
    window.set_default_size(800, 600);

    Gtk::HBox hbox;
    window.add(hbox);

    Gtk::VBox vbox;
    hbox.pack_start(vbox, Gtk::PACK_SHRINK);

    Gtk::Button button("Show Image");
    vbox.pack_start(button, Gtk::PACK_SHRINK);


    Gtk::Entry entry;
    vbox.pack_start(entry, Gtk::PACK_SHRINK);

    Gtk::Label resultLabel;
    vbox.pack_start(resultLabel, Gtk::PACK_SHRINK);

    Gtk::ScrolledWindow scrolledWindow;
    hbox.pack_start(scrolledWindow);

    Gtk::Image image;
    scrolledWindow.add(image);

    button.signal_clicked().connect(sigc::bind<Gtk::Entry*, Gtk::Label*, Gtk::Image*>(sigc::ptr_fun(&on_button_clicked), &entry, &resultLabel, &image));

    window.show_all();

    app->run(window);
}

//int main(int argc, char* argv[]) {
  //  auto app = Gtk::Application::create();

    //Gtk::Window window;
    //window.set_default_size(800, 600);

    //Gtk::HBox hbox;
    //window.add(hbox);

    //Gtk::VBox vbox;
    //hbox.pack_start(vbox, Gtk::PACK_SHRINK);

    //Gtk::Button button("Show Image");
    //vbox.pack_start(button, Gtk::PACK_SHRINK);

    //Gtk::Entry entry;
    //vbox.pack_start(entry, Gtk::PACK_SHRINK);

    //Gtk::Label resultLabel;
    //vbox.pack_start(resultLabel, Gtk::PACK_SHRINK);

    //Gtk::ScrolledWindow scrolledWindow;
    //hbox.pack_start(scrolledWindow);

    //Gtk::Image image;
    //scrolledWindow.add(image);

    //button.signal_clicked().connect(sigc::bind<Gtk::Entry*, Gtk::Label*, Gtk::Image*>(sigc::ptr_fun(&on_button_clicked), &entry, &resultLabel, &image));

    //window.show_all();

    //return app->run(window);
//}
