#include <iostream>
#include <gtkmm.h>
#include <cstdlib>
#include <ctime>

class TicTacToeGame : public Gtk::Window {
public:
  TicTacToeGame() : button_exit("Exit"), button_play_again("Play Again") {
    set_title("Tic Tac Toe");
    set_default_size(300, 300);
    set_border_width(10);

    // Initialize game state
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        gameBoard[i][j] = ' ';
      }
    }

    // Create buttons
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        buttons[i][j].signal_clicked().connect(sigc::bind<int, int>(
            sigc::mem_fun(*this, &TicTacToeGame::on_button_clicked), i, j));
        grid.attach(buttons[i][j], i, j, 1, 1);
      }
    }

    button_exit.signal_clicked().connect(sigc::mem_fun(*this, &TicTacToeGame::on_exit_clicked));
    grid.attach(button_exit, 0, 3, 1, 1);

    button_play_again.signal_clicked().connect(sigc::mem_fun(*this, &TicTacToeGame::on_play_again_clicked));
    grid.attach(button_play_again, 1, 3, 1, 1);

    // Add grid layout to window
    add(grid);

    show_all_children();
  }

protected:
  void on_button_clicked(int row, int col) {
    // Check if the clicked button is already filled
    if (gameBoard[row][col] != ' ') {
      return;
    }

    // Update the game state and button label for the player's move
    gameBoard[row][col] = 'X';
    buttons[row][col].set_label("X");

    // Check for a player win
    if (checkWinner('X')) {
      show_winner_dialog("Congratulations!👏🏻👏🏻🥳 You Won");
      disableButtons();
      return;
    }

    // Check for a draw
    if (turn == 8) {
      show_draw_dialog();
      disableButtons();
      return;
    }

    turn++;

    // Computer's move
    makeComputerMove();

    // Check for a computer win
    if (checkWinner('O')) {
      show_winner_dialog("Computer wins!");
      disableButtons();
      return;
    }

    // Check for a draw
    if (turn == 9) {
      show_draw_dialog();
      disableButtons();
      return;
    }

    turn++;
  }

  void makeComputerMove() {
    // Generate random coordinates for the computer's move
    int row, col;
    do {
      row = std::rand() % 3;
      col = std::rand() % 3;
    } while (gameBoard[row][col] != ' ');

    // Update the game state and button label for the computer's move
    gameBoard[row][col] = 'O';
    buttons[row][col].set_label("O");
  }

  void resetGame() {
    // Clear the game state and button labels
    turn = 0;
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        gameBoard[i][j] = ' ';
        gameBoard[i][j] = ' ';
        buttons[i][j].set_label("");
        buttons[i][j].set_sensitive(true);
      }
    }
  }

  bool checkWinner(char player) {
    // Check rows and columns for a win
    for (int i = 0; i < 3; i++) {
      if (gameBoard[i][0] == player && gameBoard[i][1] == player && gameBoard[i][2] == player) {
        return true;
      }
      if (gameBoard[0][i] == player && gameBoard[1][i] == player && gameBoard[2][i] == player) {
        return true;
      }
    }

    // Check diagonals for a win
    if (gameBoard[0][0] == player && gameBoard[1][1] == player && gameBoard[2][2] == player) {
      return true;
    }
    if (gameBoard[0][2] == player && gameBoard[1][1] == player && gameBoard[2][0] == player) {
      return true;
    }

    return false;
  }

  void disableButtons() {
    // Disable all buttons
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        buttons[i][j].set_sensitive(false);
      }
    }
  }

  void show_winner_dialog(const std::string& message) {
    Gtk::MessageDialog dialog(*this, "Game Over", false, Gtk::MESSAGE_OTHER);
    dialog.set_secondary_text(message);
    dialog.run();
  }

  void show_draw_dialog() {
    Gtk::MessageDialog dialog(*this, "Game Over", false, Gtk::MESSAGE_OTHER);
    dialog.set_secondary_text("It's a draw!");
    dialog.run();
  }

  void on_exit_clicked() {
    hide();
  }

  void on_play_again_clicked() {
    resetGame();
    enableButtons();
  }

  void enableButtons() {
    // Enable all buttons
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        buttons[i][j].set_sensitive(true);
      }
    }
  }

  // Widgets
  Gtk::Grid grid;
  Gtk::Button buttons[3][3];
  Gtk::Button button_exit;
  Gtk::Button button_play_again;

  char gameBoard[3][3];
  int turn = 0;
};

void rungame()
{
  // Seed the random number generator
  std::srand(std::time(0));

  auto app = Gtk::Application::create("org.tictactoegame");
  TicTacToeGame tic_tac_toe_game;
  app->run(tic_tac_toe_game);
}

//int main(int argc, char* argv[]) {
  // Seed the random number generator
  //std::srand(std::time(0));

  //auto app = Gtk::Application::create(argc, argv, "org.tictactoegame");
  //TicTacToeGame tic_tac_toe_game;
  //return app->run(tic_tac_toe_game);
//}
