#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>
#include <gtkmm.h>

class NotepadWindow : public Gtk::Window {
public:
    NotepadWindow() {
        // Set the window title and size
        set_title("Notepad");
        set_size_request(400, 300);
        
        // Create the UI elements
        Gtk::Box* vbox = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL, 10));
        Gtk::Label* filename_label = Gtk::manage(new Gtk::Label("Filename:"));
        filename_entry_ = Gtk::manage(new Gtk::Entry());
        Gtk::Label* text_label = Gtk::manage(new Gtk::Label("Text:"));
        text_view_ = Gtk::manage(new Gtk::TextView());
        Gtk::Button* save_button = Gtk::manage(new Gtk::Button("Save"));
        
        // Connect the button to the save_text() method
        save_button->signal_clicked().connect(sigc::mem_fun(*this, &NotepadWindow::save_text));
        
        // Add the UI elements to the window
        vbox->pack_start(*filename_label, Gtk::PACK_SHRINK);
        vbox->pack_start(*filename_entry_, Gtk::PACK_SHRINK);
        vbox->pack_start(*text_label, Gtk::PACK_SHRINK);
        vbox->pack_start(*text_view_, Gtk::PACK_EXPAND_WIDGET);
        vbox->pack_start(*save_button, Gtk::PACK_SHRINK);
        add(*vbox);
        show_all_children();
        
        // Start the autosave thread
        autosave_thread_ = std::thread(&NotepadWindow::autosave_text, this);
    }
    
    ~NotepadWindow() {
        // Join the autosave thread before the window is destroyed
        autosave_thread_.join();
    }
     // Autosave thread
    std::thread autosave_thread_;
    
    // Autosave interval in seconds
    int autosave_interval_ = 5;
protected:
    // UI elements
    Gtk::Entry* filename_entry_;
    Gtk::TextView* text_view_;
    
   
    
    // Saves the text in the text_view_ to a file with the name specified in filename_entry_
   void save_text() {
    // Get the filename and text
    std::string filename = filename_entry_->get_text();
    std::string text = text_view_->get_buffer()->get_text();

    // Open the file
    std::ofstream file(filename);
    if (!file.is_open()) {
        Gtk::MessageDialog dialog(*this, "Error", false, Gtk::MESSAGE_ERROR, Gtk::BUTTONS_OK, true);
        dialog.set_secondary_text("Unable to create file.");
        dialog.run();
        return;
    }

    // Write the text to the file
    file << text;
    file.close();

    // Show a message box for successful saving
    Gtk::MessageDialog dialog(*this, "File Saved", false, Gtk::MESSAGE_INFO, Gtk::BUTTONS_OK, true);
    dialog.set_secondary_text("The file has been saved successfully.");
    dialog.run();
}

    
    // Autosaves the text to a file every autosave_interval_ seconds
    void autosave_text() {
        while (true) {
            // Sleep for the autosave interval
            std::this_thread::sleep_for(std::chrono::seconds(autosave_interval_));
            
            // Save the text
            save_text();
        }
    }
};
void notepad()
{
// Initialize Gtkmm
    auto app = Gtk::Application::create();

    // Create the notepad window and run the app
    NotepadWindow window;
    int result = app->run(window);

    // When the app finishes, join the autosave thread
    window.autosave_thread_.join();

    result;
}
//int main(int argc, char** argv) {
    // Initialize Gtkmm
  //  auto app = Gtk::Application::create(argc, argv);

    // Create the notepad window and run the app
    //NotepadWindow window;
    //int result = app->run(window);

    // When the app finishes, join the autosave thread
    //window.autosave_thread_.join();

    //return result;
//}

