#include <gtkmm.h>
#include <iostream>
#include <fstream>

class CopyFileWindow : public Gtk::Window {
public:
    CopyFileWindow() {
        set_title("Copy File");
        set_border_width(10);

        sourceFileChooserButton.set_title("Choose Source File");
        sourceFileChooserButton.signal_file_set().connect(
            sigc::mem_fun(*this, &CopyFileWindow::onSourceFileSelected));

        destinationFileChooserButton.set_title("Choose Destination File");
        destinationFileChooserButton.signal_file_set().connect(
            sigc::mem_fun(*this, &CopyFileWindow::onDestinationFileSelected));

        copyButton.set_label("Copy");
        copyButton.signal_clicked().connect(
            sigc::mem_fun(*this, &CopyFileWindow::onCopyButtonClicked));

        // Create a vertical box container
        Gtk::Box* vbox = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL, 10));
        vbox->pack_start(sourceFileChooserButton, Gtk::PACK_SHRINK);
        vbox->pack_start(destinationFileChooserButton, Gtk::PACK_SHRINK);
        vbox->pack_start(copyButton, Gtk::PACK_SHRINK);

        add(*vbox);
        show_all();
    }

protected:
    void onSourceFileSelected() {
        sourceFilePath = sourceFileChooserButton.get_filename();
    }

    void onDestinationFileSelected() {
        destinationFilePath = destinationFileChooserButton.get_filename();
    }

    void onCopyButtonClicked() {
        if (sourceFilePath.empty() || destinationFilePath.empty()) {
            std::cout << "Please select source and destination files." << std::endl;
            return;
        }

        std::ifstream sourceFile(sourceFilePath, std::ios::binary);     // Open source file in binary mode
        std::ofstream destinationFile(destinationFilePath, std::ios::binary);  // Open destination file in binary mode

        if (!sourceFile) {
            std::cout << "Error opening source file." << std::endl;
            return;
        }

        if (!destinationFile) {
            std::cout << "Error opening destination file." << std::endl;
            return;
        }

        // Copy the file content
        destinationFile << sourceFile.rdbuf();

        // Close the files
        sourceFile.close();
        destinationFile.close();

        showCopySuccessMessage();  // Display success message dialog
    }

    void showCopySuccessMessage() {
        Gtk::MessageDialog dialog(*this, "File Copied");
        dialog.set_secondary_text("The file has been successfully copied.");
        dialog.run();
    }

private:
    Gtk::FileChooserButton sourceFileChooserButton;
    Gtk::FileChooserButton destinationFileChooserButton;
    Gtk::Button copyButton;

    std::string sourceFilePath;
    std::string destinationFilePath;
};

void copyfile()
{
    auto app = Gtk::Application::create();

    CopyFileWindow window;
    window.set_default_size(400, 200);

    app->run(window);
}

//int main(int argc, char* argv[]) {
  //  auto app = Gtk::Application::create(argc, argv);

    //CopyFileWindow window;
    //window.set_default_size(400, 200);

    //return app->run(window);
//}
