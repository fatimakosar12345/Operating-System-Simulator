#include <gtkmm.h>
#include <iostream>
#include <vector>
#include <fstream>

// Contact structure
struct Contact {
    std::string name;
    std::string email;
    std::string phone;
};

class ContactManager : public Gtk::Window {
public:
    ContactManager() {
        set_title("Contact Manager");
        set_default_size(500, 500);

        Gtk::Box* mainBox = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL, 10));
        add(*mainBox);

        Gtk::Label* titleLabel = Gtk::manage(new Gtk::Label("===== Contact Manager ====="));
        mainBox->pack_start(*titleLabel, Gtk::PACK_SHRINK);

        Gtk::Button* addContactButton = Gtk::manage(new Gtk::Button("Add Contact"));
        addContactButton->signal_clicked().connect(sigc::mem_fun(*this, &ContactManager::onAddContactClicked));
        mainBox->pack_start(*addContactButton, Gtk::PACK_SHRINK);

        Gtk::Button* displayContactsButton = Gtk::manage(new Gtk::Button("Display Contacts"));
        displayContactsButton->signal_clicked().connect(sigc::mem_fun(*this, &ContactManager::onDisplayContactsClicked));
        mainBox->pack_start(*displayContactsButton, Gtk::PACK_SHRINK);

        Gtk::Button* saveContactsButton = Gtk::manage(new Gtk::Button("Save Contacts"));
        saveContactsButton->signal_clicked().connect(sigc::mem_fun(*this, &ContactManager::onSaveContactsClicked));
        mainBox->pack_start(*saveContactsButton, Gtk::PACK_SHRINK);

        Gtk::Button* exitButton = Gtk::manage(new Gtk::Button("Exit"));
        exitButton->signal_clicked().connect(sigc::mem_fun(*this, &ContactManager::onExitClicked));
        mainBox->pack_start(*exitButton, Gtk::PACK_SHRINK);

        show_all_children();
    }

    void onAddContactClicked() {
        std::cout << "Add Contact\n";

        // Open a dialog window to input contact details
        Gtk::Dialog dialog("Add Contact", *this);

        // Create input fields
        Gtk::Label nameLabel("Name:");
        Gtk::Entry nameEntry;
        Gtk::Label emailLabel("Email:");
        Gtk::Entry emailEntry;
        Gtk::Label phoneLabel("Phone:");
        Gtk::Entry phoneEntry;

        // Add input fields to the dialog window
        dialog.get_content_area()->add(nameLabel);
        dialog.get_content_area()->add(nameEntry);
        dialog.get_content_area()->add(emailLabel);
        dialog.get_content_area()->add(emailEntry);
        dialog.get_content_area()->add(phoneLabel);
        dialog.get_content_area()->add(phoneEntry);

        // Add buttons to the dialog window
        dialog.add_button("Cancel", Gtk::RESPONSE_CANCEL);
        dialog.add_button("Add", Gtk::RESPONSE_OK);

        dialog.show_all();

        int result = dialog.run();

        if (result == Gtk::RESPONSE_OK) {
            // Retrieve the entered contact details
            std::string name = nameEntry.get_text();
            std::string email = emailEntry.get_text();
            std::string phone = phoneEntry.get_text();

            // Create a new contact
            Contact contact;
            contact.name = name;
            contact.email = email;
            contact.phone = phone;

            // Add the contact to the vector
            contacts.push_back(contact);

            std::cout << "Contact added successfully!\n";
        } else {
            std::cout << "Contact addition canceled.\n";
        }
    }

        void onDisplayContactsClicked() {
        std::cout << "Display Contacts\n";
        std::cout << "====================\n";

        // Check if there are contacts to display
        if (contacts.empty()) {
            std::cout << "No contacts to display.\n";
            return;
        }

        // Iterate through the contacts vector and display each contact
        for (const Contact& contact : contacts) {
            std::cout << "Name: " << contact.name << "\n";
            std::cout << "Email: " << contact.email << "\n";
            std::cout << "Phone: " << contact.phone << "\n";
            std::cout << "-------------------\n";
        }
    }

    void onSaveContactsClicked() {
        std::cout << "Save Contacts\n";
        std::cout << "====================\n";

        // Check if there are contacts to save
        if (contacts.empty()) {
            std::cout << "No contacts to save.\n";
            return;
        }

        // Open a file for writing
        std::ofstream file("contacts.txt");

        if (!file) {
            std::cerr << "Error opening file for writing!\n";
            return;
        }

        // Iterate through the contacts vector and write each contact to the file
        for (const Contact& contact : contacts) {
            file << "Name: " << contact.name << "\n";
            file << "Email: " << contact.email << "\n";
            file << "Phone: " << contact.phone << "\n";
            file << "-------------------\n";
        }

        file.close();

        std::cout << "Contacts saved to file successfully!\n";
    }

    void onExitClicked() {
        std::cout << "Exiting program.\n";
        // Add your implementation for saving contacts before exiting here
        close();
    }

private:
    std::vector<Contact> contacts;
};

void contact()
{
  auto app = Gtk::Application::create("org.example.contact_manager");

    ContactManager contactManager;
    app->run(contactManager);
}

//int main(int argc, char** argv) {
  //  auto app = Gtk::Application::create(argc, argv, "org.example.contact_manager");

    //ContactManager contactManager;
    //return app->run(contactManager);
//}
