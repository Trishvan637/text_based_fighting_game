#include<iostream>
#include<ctime>
#include<limits>
using namespace std;

class Player {
public:
    int health = 100;
    int mp = 0;

    bool attack() {
        mp += rand() % 20 + 1;
        constrainValues();
        return true;
    }

    bool specialAttack() {
        if (mp != 0) {
            int specialDamage = max(mp, 1) + rand() % 20 + 1;
            health += specialDamage;  // Increase the health of the player who used the special attack
            opponent->health -= specialDamage;  // Decrease the other player's health
            mp = 0;
            constrainValues();
        } else {
            cout << "Special Attack failed! MP is 0. Player loses the turn." << endl;
        }
        return true;
    }

    bool guard() {
        int guardIncrease = rand() % 15 + 1;  // Adjust the range for a more reasonable guard increase
        health += guardIncrease;
        constrainValues();
        cout << "Damage decreased by " << guardIncrease << ". Current health: " << max(health, 0) << endl;
        return true;
    }

    void setOpponent(Player* opp) {
        opponent = opp;
    }

    void displayStats() const {
        cout << "Health: " << max(health, 0) << " | MP: " << max(mp, 0) << endl;
    }

private:
    Player* opponent;

    void constrainValues() {
        // Constrain health and mp to a maximum value of 100
        health = min(health, 100);
        mp = min(mp, 100);
    }
};

int choice() {
    int ch;
    cout << "Choose your action:" << endl;
    cout << "1. Attack" << endl;
    cout << "2. Special Attack" << endl;
    cout << "3. Guard" << endl;
    while (!(cin >> ch) || ch < 1 || ch > 3) {
        cin.clear();  // Clear the error flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Discard invalid input
        cout << "Invalid choice. Please enter a number between 1 and 3." << endl;
    }
    return ch;
}

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));

    Player player1, player2;
    player1.setOpponent(&player2);
    player2.setOpponent(&player1);

    bool game = true;

    while (game) {
        cout << "Player 1's turn" << endl;
        player1.displayStats();
        int action = choice();

        switch (action) {
            case 1:
                player1.attack();
                player2.health -= rand() % 20 + 1;
                break;
            case 2:
                if (player1.mp == 0) {
                    cout << "Special Attack failed! MP is 0. Player loses the turn." << endl;
                    break;
                }
                player1.specialAttack();
                break;
            case 3:
                player1.guard();
                break;
            default:
                cout << "Invalid choice! Player 1 loses a turn." << endl;
                break;
        }

        cout << "Player 2's stats: ";
        player2.displayStats();

        // Check if Player 2 is defeated
        if (player2.health <= 0) {
            cout << "Player 1 wins!" << endl;
            game = false;
            break;
        }

        cout << "Player 2's turn" << endl;
        player2.displayStats();
        action = choice();

        switch (action) {
            case 1:
                player2.attack();
                player1.health -= rand() % 20 + 1;
                break;
            case 2:
                if (player2.mp == 0) {
                    cout << "Special Attack failed! MP is 0. Player loses the turn." << endl;
                    break;
                }
                player2.specialAttack();
                break;
            case 3:
                player2.guard();
                break;
            default:
                cout << "Invalid choice! Player 2 loses a turn." << endl;
                break;
        }

        cout << "Player 1's stats: ";
        player1.displayStats();

        // Check if Player 1 is defeated
        if (player1.health <= 0) {
            cout << "Player 2 wins!" << endl;
            game = false;
            break;
        }
    }

    cout << "Game Over!" << endl;

    return 0;
}
