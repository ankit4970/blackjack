#include "../blackjack.h"

/**** Deck Class Definitions ****/

/****************************************************************************************
void Deck::createDeck()
	Creates the deck (adds 52 cards)
****************************************************************************************/
void Deck::createDeck()
{
	cards.reserve(MAX_CARDS);

    for (int i = 0 ; i < Suit.size() ; i++)
    {
        for (int  j = 0 ; j < Points.size() ; j++)
        {
            cards.push_back(Card(Suit[i], Points[j], true));
        }
    }
}

/****************************************************************************************
void Deck::resetDeck()
	Resets the deck (removes all cards from the deck)
****************************************************************************************/
void Deck::resetDeck()
{
	cards.clear();
}

/****************************************************************************************
void Deck::shuffle()
	shuffles the whole Deck (Cards will be random after the shuffle)
****************************************************************************************/
void Deck::shuffle()
{
	srand (time(NULL));
	for (int i = 0 ; i < cards.size() ; i++)
	{
		int j = rand()%52;
		Card temp = cards[j];
		cards[j] = cards[i];
		cards[i] = temp;
	}
}

/****************************************************************************************
bool Deck::isEmpty()
	returns true if the Deck is empty, else false
****************************************************************************************/
bool Deck::isEmpty()
{
	return cards.empty();
}

/****************************************************************************************
Card Deck::nextCard()
	adds next card to the hand if available, nothing if empty
****************************************************************************************/
bool Deck::drawNextCard(Hand& hand)
{
	if (!cards.empty())
	{
		hand.addCard(cards.front());
		cards.erase(cards.begin());
		return true;
	}

	cout << "Deck is empty" << endl;
	return false;
}

/****  Card class Definitions  ****/


int Card::getValue()
{
	if(isFaceUp) 
	{ 
		return value; 
	}

	return 0;
}

string Card::getSuite()
{
	if (isFaceUp)
	{
		return face;
	}
	return "";
}

void Card::flip()
{
	isFaceUp = !isFaceUp;
}

/* Hand Class Definitions */

void Hand::addCard(Card card)
{
	cards.push_back(card);
}

uint32_t Hand::getPoints()
{
	int total = 0;
						  /* Face down */
	if (cards.empty() || (cards.size() == 2 && cards[1].getValue() == 0))
	{
		return 0;
	}
	for (Card c : cards)
	{
		total += c.getValue();
		if (c.getValue() == 1) // Its ACE
		{
			isAceIncluded = true;
		}
	}

	if (isAceIncluded && total <= 11)
	{
		total += 10;
	}

	return total;
}

void Hand::clearHand()
{
	return;
}

void Hand::flipSecondCard()
{
	if (cards.size() == 2)
	{
		cards[1].flip();
	}
}

void Hand::printLastCard()
{
	cout << cards.back().getSuite() << cards.back().getValue() << endl;
}

int Player::getTotalPoints()
{
	return hand.getPoints();
}

void Deck::printDeck()
{
	for (int i = 0 ; i < cards.size() ; i++)
	{
		cout << cards[i].getSuite() <<  cards[i].getValue() << ",";
	}
	cout << endl;
}
void BlackJack::printDeck()
{
	deck.printDeck();
}

void Player::showHand()
{
	cout << "\033[1m" << name << "\033[0m" << "\x1b[31m : hands => " ;
	if (!hand.cards.size())
	{
		cout << "(empty)" << ",";
	}
	for (int i = 0 ; i < hand.cards.size() ; i++)
	{
		cout << hand.cards[i].getSuite() << hand.cards[i].getValue() << ",";
	}
	cout << " Total => " << getTotalPoints() << "\x1b[0m" << endl;
}

bool Player::hasBlackJack()
{
	return getTotalPoints() == 21;
}

void BlackJack::play()
{
	string playerChoice;
	bool playerStand = false;
	bool playerQuits = false;
	string name;
	deck.createDeck();
	deck.shuffle();
		
	while (!playerQuits)
	{
		cout << "\033[1mWelcome to BlackJack!\033[0m" << endl;
		cout << "Enter players name : ";
		cin >> name;

		Player p(name);
		Player d("Dealer");
		bool gameOver = false;

		cout << "Welcome \033[1m" << p.name << "\033[0m" << ",";
		cout << " Let's start the Game" << endl << endl;

		if (noOfRounds == maxNumberOfRoundsBeforeShuffle)
		{
			deck.resetDeck();
			deck.createDeck();
			deck.shuffle();		// Randomize
		}

		// Present 2 cards to player and 2 to dealer with one face down

		deck.drawNextCard(p.hand);
		cout << "Drawing First Card for You => ";
		p.hand.printLastCard();

		deck.drawNextCard(d.hand);
		cout << "Drawing First Card for Dealer => ";
		d.hand.printLastCard();

		cout << endl;
		p.showHand();
		d.showHand();
		cout << endl;

		deck.drawNextCard(p.hand);
		cout << "Drawing Second Card for You => ";
		p.hand.printLastCard();

		deck.drawNextCard(d.hand);
		d.hand.flipSecondCard();
		cout << "Drawing Second Card for Dealer => ";
		d.hand.printLastCard();

		cout << endl;
		p.showHand();
		d.showHand();
		cout << endl;

		int playerPoints = p.getTotalPoints();
		d.hand.flipSecondCard();
		int dealerPoints = d.getTotalPoints();

		if (p.hasBlackJack() && dealerPoints < 21)
		{
			cout << "You have BlackJack ! You Win" << endl;
			cout << endl;
			p.showHand();
			d.showHand();
			cout << endl;
			gameOver = true;
		}
		else if (d.hasBlackJack() && playerPoints < 21)
		{
			cout << "Dealer has BlackJack! Dealer Wins" << endl;
			cout << endl;
			p.showHand();
			d.showHand();
			cout << endl;
			gameOver = true;
		}
		else if (p.hasBlackJack() && d.hasBlackJack())
		{
			cout << "Tie" << endl;
			p.showHand();
			d.showHand(); 
			gameOver = true;
		}
		else
		{
			d.hand.flipSecondCard();

			while (!playerStand)
			{	
				cout << "Hit(h) or stay(s): ";
				cin >> playerChoice;
				if (playerChoice == "s" || playerChoice == "stay" || playerChoice == "S")
				{
					playerStand = true;
				}
				else if (playerChoice == "h" || playerChoice == "Hit" || playerChoice == "H")
				{
					deck.drawNextCard(p.hand);
					cout << "New card is ";
					p.hand.printLastCard();
					cout << endl;
					p.showHand();
					d.showHand();
					cout << endl;
					if (p.getTotalPoints() > 21)
					{
						cout << "Oh! You Busted! Lost" << endl;
						gameOver = true;
						break;
					}
				}
				else
				{
					cout << "Invalid choice, try again!" << endl;
				}
			}
		}

		if (!gameOver)
		{
			d.hand.flipSecondCard();

			cout << endl;
			p.showHand();
			d.showHand();
			cout << endl;

			playerPoints = p.getTotalPoints();
			dealerPoints = d.getTotalPoints();
			
			while (dealerPoints <= 16 || (dealerPoints == 17 && d.hand.isAceIncluded))
			{
				cout << "Dealing card to Dealer ";
				deck.drawNextCard(d.hand);
				cout << "New card is ";
				d.hand.printLastCard();
				cout << endl; 
				p.showHand();
				d.showHand();
				cout << endl;
				dealerPoints = d.getTotalPoints();
			}

			if (dealerPoints > 21)
			{
				cout << "Dealer Busted! You Win" << endl;
			}
			else if (dealerPoints == playerPoints)
			{
				cout << "Its a Tie!" << endl;
			}
			else if (dealerPoints > playerPoints)
			{
				cout << "Dealer Wins !" << endl;
			}
			else	// (dealerPoints < playerPoints)
			{
				cout << "Woha! You Win" << endl;
			}
		}

		cout << "Player P total points : " << p.getTotalPoints() << endl;
		cout << "Dealer D total points : " << d.getTotalPoints() << endl;

		cout << "Quit(q) or Play(p)" << endl;
		cin >> playerChoice;

		if (playerChoice == "Q" || playerChoice == "q" || playerChoice == "quit")
		{
			playerQuits = true;
		}

		playerStand = false;
		noOfRounds++;

		cout << "**************************************************************************************" << endl;
	}
	return;
}
