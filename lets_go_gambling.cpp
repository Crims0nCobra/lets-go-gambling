#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <random>
#include <algorithm>

std::vector<std::string> deck {
//spades
"SP-A",
"SP-2",
"SP-3",
"SP-4",
"SP-5",
"SP-6",
"SP-7",
"SP-8",
"SP-9",
"SP-X",
"SP-J",
"SP-Q",
"SP-K",
//clubs
"CL-A",
"CL-2",
"CL-3",
"CL-4",
"CL-5",
"CL-6",
"CL-7",
"CL-8",
"CL-9",
"CL-X",
"CL-J",
"CL-Q",
"CL-K",
//hearts
"HE-A",
"HE-2",
"HE-3",
"HE-4",
"HE-5",
"HE-6",
"HE-7",
"HE-8",
"HE-9",
"HE-X",
"HE-J",
"HE-Q",
"HE-K",
//diamonds
"DI-A",
"DI-2",
"DI-3",
"DI-4",
"DI-5",
"DI-6",
"DI-7",
"DI-8",
"DI-9",
"DI-X",
"DI-J",
"DI-Q",
"DI-K"
};

int main() {
    //initializing the mersenne twister random engine and seeding it.
    std::mt19937 gen(std::random_device{}());
    //creates a vector string that accesses the contnets of deck.
    std::vector<std::string> getdeck = deck;
    //shuffles the deck.
    std::shuffle(getdeck.begin(), getdeck.end(), gen);

    bool blackjack = 1;
    bool players_turn = 1;
    bool dealers_turn = 0;
    bool game_start = 1;

    int player_score = 0;
    int dealer_score = 0;
    int new_cards = 0;

    std::string opt;

    std::vector<std::string> plr_hand;
    std::vector<std::string> dlr_hand;

    while (blackjack == true) {
        //Notes to self: ---//
            //KNOWN BUGS: N/A.
            //TO DO: ->add a split option if the player has a pair. ->add betting. ->fix the new hand/game restart function thing. ->weight it so if the player is winning too much then the house/dealer will get a large advantage and the player a disadvantage. "the house always wins."
        //------------------//
        
        //declaring some useful strings.
        std::string rank;
        std::string d_rank;

        //GAME START, PLAYER GETS DEALT 2 CARDS ----------
        for (int counter = 0; counter < 100; counter++){
        if (game_start == true){
            std::cout << "Welcome to Blackjack, \nwhere the stakes are higher than ever: the loser gets banished to the shadow realm. \npro tip: don't lose. \nglhf.\n\n";
            //player draws cards
                for (int i = 0; i < 2; i++) {
                    //copies cards from deck over to plr hand.
                    plr_hand.push_back(std::move(getdeck.back()));
                    //removes drawn cards from deck.
                    getdeck.pop_back();
                    new_cards += 1;
                }
                //print out player's hand.
                std::cout << "\nYour hand is:\n";
                for (int i = 0; i < 2; i++){
                    std::cout << plr_hand[i] << "\n";
                }
                //find sum of cards in hand.
                //grabs the rank of each card in the player's hand and throws it into a string.
                for (int i = 0; i < 2; i++){
                    int pos = plr_hand.size() - new_cards;
                    rank = plr_hand[pos + i].substr(3, 2);
                    //check whats in the players hand. assign the letters numeric value and add to player score.
                    if (!rank.empty()){
                        for (int a = 0; a < 1; a++){
                            //Aces valued at 11, face cards valued at 10, numbered cards valued at their number.
                            if (rank == "A" && (player_score+11) <= 21){player_score += 11;}
                            //this is a thing in blackjack for some reason.
                            else if (rank == "A" && (player_score+11) > 21){player_score += 1;};
                            if (rank == "2"){player_score += 2;};
                            if (rank == "3"){player_score += 3;};
                            if (rank == "4"){player_score += 4;};
                            if (rank == "5"){player_score += 5;};
                            if (rank == "6"){player_score += 6;};
                            if (rank == "7"){player_score += 7;};
                            if (rank == "8"){player_score += 8;};
                            if (rank == "9"){player_score += 9;};
                            if (rank == "X"){player_score += 10;};
                            if (rank == "J"){player_score += 10;};
                            if (rank == "Q"){player_score += 10;};
                            if (rank == "K"){player_score += 10;};
                        }
                    }
                }
                new_cards = 0;
                std::cout << "\nYour score is : \033[33m" << player_score << "\033[0m\n" << std::endl;
                game_start = false;
            }

        //PLAYER TURN ----------
        if (players_turn == true) {
            std::cout << "Hit or Stand?\n";
            //cin for "hit" or "stand"
            std::cin >> opt;
            if (opt == "Hit" || opt == "hit" || opt == "HIT" || opt == "h" || opt == "H"){
                //player draws cards
                for (int i = 0; i < 1; i++) {
                    //copies cards from deck over to plr hand.
                    plr_hand.push_back(std::move(getdeck.back()));
                    //removes drawn cards from deck.
                    getdeck.pop_back();
                    //tracks how many cards were drawn.
                    new_cards += 1;
                }
                //prints out the player's hand.
                std::cout << "\nYour hand is:\n";
                for (int i = 0; i < plr_hand.size(); i++){
                    std::cout << plr_hand[i] << "\n";
                }
                //find sum of cards in hand.
                //grabs the rank of each card in the player's hand and throws it into a string.
                for (int i = 0; i < new_cards; i++){
                    //if player hand had 3 cards and 2 new cards, then the pos(ition) would be 1, causing the program to ignore the first element in the array since it's already been calculated.
                    int pos = plr_hand.size() - new_cards;
                    //then, because the actual position is pos + i, then it would be 1+0=1 the first time, then it would be 1+1=2 next time, this makes it so the value increments w/ each loop.
                    rank = plr_hand[pos + i].substr(3, 2);
                    //check whats in the players hand. assign the letters numeric value and add to player score.
                    if (!rank.empty()){
                        for (int a = 0; a < 1; a++){
                            //Aces valued at 11, face cards valued at 10, numbered cards valued at their number.
                            if (rank == "A" && (player_score+11) <= 21){player_score += 11;}
                            //this is a thing in blackjack for some reason.
                            else if (rank == "A" && (player_score+11) > 21){player_score += 1;};
                            if (rank == "2"){player_score += 2;};
                            if (rank == "3"){player_score += 3;};
                            if (rank == "4"){player_score += 4;};
                            if (rank == "5"){player_score += 5;};
                            if (rank == "6"){player_score += 6;};
                            if (rank == "7"){player_score += 7;};
                            if (rank == "8"){player_score += 8;};
                            if (rank == "9"){player_score += 9;};
                            if (rank == "X"){player_score += 10;};
                            if (rank == "J"){player_score += 10;};
                            if (rank == "Q"){player_score += 10;};
                            if (rank == "K"){player_score += 10;};
                        }
                    }
                }
                new_cards = 0;

                std::cout << "\nPlayer score is : \033[33m" << player_score << "\033[0m\n" << std::endl;
                if (player_score > 21){
                    std::cout << "Bust.\nAw, dang it.\nYou've been banished to the shadow realm.";
                    blackjack = false;
                }       
                else {players_turn = 0; dealers_turn = 1;}
            }
            else if (opt == "stand" || opt == "Stand" || opt == "STAND" || opt == "s" || opt == "S"){
                //end of turn.
                players_turn = false;
                dealers_turn = true;
            }
        }

        //DEALER TURN ----------
        else if(dealers_turn == true) {
                //dealer draws cards
                for (int i = 0; i < 1; i++){
                    //copies cards from deck over to dlr hand.
                    dlr_hand.push_back(std::move(getdeck.back()));
                    //removes drawn cards from deck.
                    getdeck.pop_back();
                    new_cards += 1;
                }
                //prints out the dealer's hand.
                std::cout << "\nDealer's hand is:\n";
                for (int i = 0; i < dlr_hand.size(); i++){
                    std::cout << dlr_hand[i] << "\n";
                }
                //find sum of cards in dealer's hand.
                //grabs the rank of each card in the dealer's hand and throws it into a string.
                for (int i = 0; i < new_cards; i++){
                    int pos = dlr_hand.size() - new_cards;
                    d_rank = dlr_hand[pos + i].substr(3, 2);

                    //check whats in the dealers hand. assign the letters numeric value and add to dealer score.
                    if(!d_rank.empty()){
                        for (int a = 0; a < 1; a++){
                            //Aces valued at 11, face cards valued at 10, numbered cards valued at their number.
                            if (d_rank == "A" && (dealer_score+11) <= 21){dealer_score += 11;}
                            //this is a thing in blackjack for some reason.
                            else if (d_rank == "A" && (dealer_score+11) > 21){dealer_score += 1;};
                            if (d_rank == "2"){dealer_score += 2;};
                            if (d_rank == "3"){dealer_score += 3;};
                            if (d_rank == "4"){dealer_score += 4;};
                            if (d_rank == "5"){dealer_score += 5;};
                            if (d_rank == "6"){dealer_score += 6;};
                            if (d_rank == "7"){dealer_score += 7;};
                            if (d_rank == "8"){dealer_score += 8;};
                            if (d_rank == "9"){dealer_score += 9;};
                            if (d_rank == "X"){dealer_score += 10;};
                            if (d_rank == "J"){dealer_score += 10;};
                            if (d_rank == "Q"){dealer_score += 10;};
                            if (d_rank == "K"){dealer_score += 10;};
                        }
                    }
                }
                new_cards = 0;

                std::cout << "\nDealer score is : \033[33m" << dealer_score << "\033[0m\n" << std::endl;
                if (dealer_score > 21){
                    std::cout << "Dealer bust. \nYou can't stop winning!\n\n";
                    blackjack = false;
                }
                else{dealers_turn = 0; players_turn = 1;};
        }
        //ROUND END LOOGIC ----------
        if (player_score == dealer_score) {
            std::cout << "Push.\nUnfortunately, no one gets banished to the shadow realm.\n";
            blackjack = false;
        }
        if (player_score == 21) {std::cout << "Blackjack.\nYou can't stop winning!\n"; blackjack = false; break;};
        if (dealer_score == 21) {std::cout << "Dealer Blackjack.\nAw, dang it.\nYou get banished to the shadow realm.\n"; blackjack = false; break;};
    }
    };
    //BROKEN code for restarting the game. pls fix future me.
    //std::cout << "New hand? Y/N : \033[33m";
    //std::cin >> opt;
    //std::cout << "\033[0m\n\n";
        //if (opt == "Y" || opt == "y" || opt == "yes" || opt == "Yes" || opt == "YES"){blackjack = true; game_start = true;}
        //else if (opt == "N" || opt == "n" || opt == "no" || opt == "No" || opt == "NO"){}//blackjack = false;}
};