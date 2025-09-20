// This project was developed by Group 1
// Caleb Fitzsimonds
// Sundus Mahamud
// K.M Fazle Rabbi


#include <mutex>
#include <iostream>
#include <thread>
#include <array>
#include <random>

std::mutex m;

struct Game {
    std::array<char, 9> board{};
    std::mutex m;
    int turn = 0;               // This can either be 0 or 1 to indicate which player gets to play
    bool gameover = false;      // boolean to set game end state
    char winner = ' ';          // This will be X, O, or C (Cat's Game) if gameover True and ' ' if gameover false
    int moves_made = 0;         // let the game count # of moves made

    Game() {                    // this is a constructor which will initialize our gameboard and fill it with empty spaces
        board.fill(' ');
    }
};

static const int win_lines[8][3] = {    // creates a 2D array for referencing the winning lines
    {0,1,2},{3,4,5},{6,7,8},   // rows
    {0,3,6},{1,4,7},{2,5,8},   // cols
    {0,4,8},{2,4,6}            // diagonals
};

void print_board(const Game& g) {
    std::cout << '\n';
    std::cout << " " << g.board[0] << " | " << g.board[1] << " | " << g.board[2] << "\n";
    std::cout << "---+---+---\n";
    std::cout << " " << g.board[3] << " | " << g.board[4] << " | " << g.board[5] << "\n";
    std::cout << "---+---+---\n";
    std::cout << " " << g.board[6] << " | " << g.board[7] << " | " << g.board[8] << "\n";
    std::cout.flush();   // clears cout buffer to make sure that threads don't overlap their prints
}

bool check_for_win(const std::array<char, 9>& b, char mark) {
    for (auto line : win_lines) {
        if (b[line[0]] == mark && b[line[1]] == mark && b[line[2]] == mark)
            return true;
    }
    return false;
}

// Picks a random number 0 through 8 to be used to "randomly" select space on the board
int random_selection() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, 8);

    int rn = dist(gen);
    return rn;
}


void player(Game& g, char mark, int id) {
    std::this_thread::sleep_for(std::chrono::milliseconds(10 * id));
    // ensures threads don't hit the mutex at the same time on startup

    while (true) {
        std::unique_lock<std::mutex> lock(g.m);
        if (g.gameover) {
            break;
        }

        if (g.turn != id) {
            continue;
        }

        int selection = random_selection();
        while (g.board[selection] != ' ') {

            selection = random_selection();
        }
        g.board[selection] = mark;
        print_board(g);
        g.turn = 1 - g.turn;    // alternates between turns
        g.moves_made++;
        if (check_for_win(g.board, mark)) {
            g.gameover = true;
            g.winner = mark;
            break;
        }
        else if (g.moves_made == 9) {
            g.gameover = true;
            g.winner = 'C';
            break;
        }

        lock.unlock();
    }
}

int main() {
    Game g;

    std::cout << "Starting Tic-Tac-Toe:\n";
    print_board(g);

    std::thread x(player, std::ref(g), 'X', 0);
    std::thread o(player, std::ref(g), 'O', 1);

    x.join();
    o.join();

    if (g.winner == 'X') {
        std::cout << "Player X has won the game!";
    }
    else if (g.winner == 'O') {
        std::cout << "Player O has won the game!";
    }
    else if (g.winner == 'C') {
        std::cout << "Cat's Game! No winner!";
    }

    return 0;
}