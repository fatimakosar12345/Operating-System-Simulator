#include <gtkmm.h>
#include <iostream>
#include <sstream>
#include <sys/ipc.h>
#include <sys/shm.h>
//#include"gtkmm_functions.h"


class CalculatorWindow : public Gtk::Window {
public:
    CalculatorWindow() {
        set_title("Calculator");
        set_border_width(10);

        // Create grid container
        Gtk::Grid* grid = Gtk::manage(new Gtk::Grid);
        grid->set_column_homogeneous(true);
        grid->set_row_homogeneous(true);
        add(*grid);

        
        // Create result label
        resultLabel.set_hexpand(true);
        resultLabel.set_vexpand(true);
        resultLabel.set_alignment(Gtk::ALIGN_END);
        resultLabel.set_margin_top(10);
        resultLabel.set_margin_bottom(10);
        resultLabel.set_margin_left(10);
        resultLabel.set_margin_right(10);
        grid->attach(resultLabel, 0, 0, 4, 1);

        // Create numeric buttons
        for (int i = 0; i < 10; ++i) {
            Gtk::Button* button = Gtk::manage(new Gtk::Button);
            button->set_label(std::to_string(i));
            button->set_margin_top(5);
            button->set_margin_bottom(5);
            button->set_margin_left(5);
            button->set_margin_right(5);
            button->signal_clicked().connect(
                sigc::bind<int>(sigc::mem_fun(*this, &CalculatorWindow::onNumericButtonClicked), i));
            grid->attach(*button, i % 4, i / 4 + 1, 1, 1);
        }

        // Create arithmetic operator buttons
        const std::string operators[6] = { "+", "-", "*", "/", ".", "=" };
        for (int i = 0; i < 6; ++i) {
            Gtk::Button* button = Gtk::manage(new Gtk::Button);
            button->set_label(operators[i]);
            button->set_margin_top(5);
            button->set_margin_bottom(5);
            button->set_margin_left(5);
            button->set_margin_right(5);
            button->signal_clicked().connect(
                sigc::bind<std::string>(sigc::mem_fun(*this, &CalculatorWindow::onOperatorButtonClicked), operators[i]));
            if (operators[i] == "=") {
                button->get_style_context()->add_class("green-button");
            }
            if (operators[i] == "Clear") {
                button->get_style_context()->add_class("red-button");
            }
            grid->attach(*button, i % 4, i / 4 + 5, 1, 1);
        }

        // Create clear button
        clearButton.set_label("Clear");
        clearButton.set_margin_top(5);
        clearButton.set_margin_bottom(5);
        clearButton.set_margin_left(5);
        clearButton.set_margin_right(5);
        clearButton.signal_clicked().connect(
            sigc::mem_fun(*this, &CalculatorWindow::onClearButtonClicked));
        clearButton.get_style_context()->add_class("red-button");
        grid->attach(clearButton, 0, 4, 1, 1);

        show_all();
    }

protected:
    void onNumericButtonClicked(int number) {
        currentNumber += std::to_string(number);
        updateResultLabel();
    }

    void onOperatorButtonClicked(const std::string& operatorString) {
        if (currentNumber.empty() && operatorString != "-")
            return;

        if (operatorString == "+") {
            currentOperator = Operator::ADD;
        } else if (operatorString == "-") {
            if (currentNumber.empty()) {
                currentNumber = "-";
                updateResultLabel();
                return;
            }
            currentOperator = Operator::SUBTRACT;
        } else if (operatorString == "*") {
            currentOperator = Operator::MULTIPLY;
        } else if (operatorString == "/") {
            currentOperator = Operator::DIVIDE;
        } else if (operatorString == "=") {
            onEqualButtonClicked();
            return;
        } else if (operatorString == ".") {
            // Check if decimal point already exists in the current number
            if (currentNumber.find('.') == std::string::npos) {
                currentNumber += '.';
                updateResultLabel();
            }
            return;
        }

        previousNumber = std::stod(currentNumber);
        currentNumber.clear();
    }

    void onEqualButtonClicked() {
        if (currentNumber.empty())
            return;

        double result = 0.0;
        double current = std::stod(currentNumber);

        switch (currentOperator) {
            case Operator::ADD:
                result = previousNumber + current;
                break;
            case Operator::SUBTRACT:
                result = previousNumber - current;
                break;
            case Operator::MULTIPLY:
                result = previousNumber * current;
                break;
            case Operator::DIVIDE:
                if (current != 0.0)
                    result = previousNumber / current;
                else
                    resultLabel.set_text("Error: Division by zero");
                break;
        }

        std::ostringstream oss;
        oss << result;
        resultLabel.set_text(oss.str());

        currentNumber = oss.str();
    }

    void onClearButtonClicked() {
        currentNumber.clear();
        previousNumber = 0.0;
        currentOperator = Operator::NONE;
        resultLabel.set_text("");
    }

    void updateResultLabel() {
        resultLabel.set_text(currentNumber);
    }

private:
    enum class Operator {
        NONE,
        ADD,
        SUBTRACT,
        MULTIPLY,
        DIVIDE
    };

    std::string currentNumber;
    double previousNumber = 0.0;
    Operator currentOperator = Operator::NONE;
    Gtk::Label resultLabel;
    Gtk::Button clearButton;
};

void my_gtkmm_function()
{
  auto app = Gtk::Application::create();

    // Load CSS style provider
    auto cssProvider = Gtk::CssProvider::create();
    cssProvider->load_from_data(".red-button { background-color: red; } .green-button { background-color: green; }");

    // Add style provider to the default screen
    auto styleContext = Gtk::StyleContext::create();
    styleContext->add_provider_for_screen(Gdk::Screen::get_default(), cssProvider, GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    CalculatorWindow window;
    window.set_default_size(200, 300);

    app->run(window);
}

//int main(int argc, char* argv[]) {

    
    //auto app = Gtk::Application::create();

    // Load CSS style provider
    //auto cssProvider = Gtk::CssProvider::create();
    //cssProvider->load_from_data(".red-button { background-color: red; } .green-button { background-color: green; }");

    // Add style provider to the default screen
    //auto styleContext = Gtk::StyleContext::create();
    //styleContext->add_provider_for_screen(Gdk::Screen::get_default(), cssProvider, GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    //CalculatorWindow window;
    //window.set_default_size(200, 300);

    //return app->run(window);
//}
