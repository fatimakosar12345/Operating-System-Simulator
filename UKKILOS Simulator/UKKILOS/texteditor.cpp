#include <gtkmm.h>
#include <fstream>

class TextEditor : public Gtk::Window {
public:
    TextEditor() {
        set_title("Text Editor");
        set_default_size(1400, 400);

        // Create a vertical box to hold the widgets
        Gtk::Box* box = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL));
        add(*box);

        text_view.set_wrap_mode(Gtk::WRAP_WORD_CHAR);
        box->pack_start(text_view, Gtk::PACK_EXPAND_WIDGET);

        open_button.set_label("Open");
        open_button.signal_clicked().connect(sigc::mem_fun(*this, &TextEditor::on_open_button_clicked));
        box->pack_start(open_button, Gtk::PACK_SHRINK);

        save_button.set_label("Save");
        save_button.signal_clicked().connect(sigc::mem_fun(*this, &TextEditor::on_save_button_clicked));
        box->pack_start(save_button, Gtk::PACK_SHRINK);

        show_all();
    }

protected:
    void on_open_button_clicked() {
        Gtk::FileChooserDialog dialog(*this, "Open File");
        dialog.set_action(Gtk::FILE_CHOOSER_ACTION_OPEN);

        dialog.add_button("_Cancel", Gtk::RESPONSE_CANCEL);
        dialog.add_button("_Open", Gtk::RESPONSE_OK);

        int result = dialog.run();
        if (result == Gtk::RESPONSE_OK) {
            std::string file_path = dialog.get_filename();
            std::ifstream file(file_path);
            if (file) {
                std::stringstream buffer;
                buffer << file.rdbuf();
                text_view.get_buffer()->set_text(buffer.str());
            }
        }
    }

    void on_save_button_clicked() {
        Gtk::FileChooserDialog dialog(*this, "Save File");
        dialog.set_action(Gtk::FILE_CHOOSER_ACTION_SAVE);

        dialog.add_button("_Cancel", Gtk::RESPONSE_CANCEL);
        dialog.add_button("_Save", Gtk::RESPONSE_OK);

        int result = dialog.run();
        if (result == Gtk::RESPONSE_OK) {
            std::string file_path = dialog.get_filename();
            std::ofstream file(file_path);
            if (file) {
                Glib::RefPtr<Gtk::TextBuffer> buffer = text_view.get_buffer();
                std::string text = buffer->get_text();
                file << text;
            }
        }
    }

private:
    Gtk::TextView text_view;
    Gtk::Button open_button;
    Gtk::Button save_button;
};

void editor()
{
  auto app = Gtk::Application::create("com.example.texteditor");
    TextEditor text_editor;
    app->run(text_editor);
}

//int main(int argc, char *argv[]) {
  //  auto app = Gtk::Application::create(argc, argv, "com.example.texteditor");
    //TextEditor text_editor;
    //return app->run(text_editor);
//}
