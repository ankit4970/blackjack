#include <iostream>
#include <vector>
#include <string>
#include <unistd.h>
using namespace std;

class Card {
private:
    string face;
    int value;
    bool isFaceUp;
    
public:
    int getValue();
    string getSuite();
    void flip();
    Card(string suite, int points, bool faceUp)
    {
        face.assign(suite);
        value = points;
        isFaceUp = faceUp;
    }
};

class Hand
{
private:
    uint32_t totalPoints;
    
public:   
    bool isAceIncluded;
    vector<Card> cards;                // Move to 
    void addCard(Card card);           // Adds a card to Hand
    void clearHand();
    void flipSecondCard();
    uint32_t getPoints();               // Returns total points of the Hand , Decision on ACE is 1 or 11
    void printLastCard();
    Hand()
    {
        isAceIncluded = false;
    }
};

class Player
{
private:
    uint32_t score;
    
public:
    Hand hand; // @TODO
    string name;
    int getTotalPoints();
    void showHand();
    bool hasBlackJack();
    Player(string playername)
    {
        name = playername;
    }
    ~Player()
    {
        hand.cards.clear();
    }
};

class Deck {
private:
    vector<Card> cards;
    vector<string> Suit {
        "C",        // CLUB
        "D",        // DIAMOND
        "H",        // HEART
        "S"         // SPADE
    };
                     /* A                    J  Q  K */
    vector<int> Points {1,2,3,4,5,6,7,8,9,10,10,10,10};
public:
    void shuffle();                         // Shuffels the deck
    bool drawNextCard(Hand& hand);          // Deals the next card from the deck, if empty ?
    bool isEmpty();
    void createDeck();
    void resetDeck();
    void printDeck();        
    int MAX_CARDS = 52;         // Maximum number of cards in the Deck
    Deck(){}                    // Constructor
};


class BlackJack
{
private:
    Deck deck;
    uint8_t winPercent; // Player win percent
    int noOfRounds;
    vector<Player> players;
public:
    void play();
    void printDeck();
    const int maxNumberOfRoundsBeforeShuffle = 6;
};