#include "../blackjack.h"

/* Deck Class Definitions */

void Deck::createDeck()
{
	cards.reserve(MAX_CARDS);

    for (int i = 0 ; i < Suit.size() ; i++)
    {
        for (int  j = 0 ; j < Points.size() ; j++)
        {
            cards.push_back(Card(Suit[i],Points[j],true));
        }
    }
}

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
	returns true if Deck is empty, else false
****************************************************************************************/
bool Deck::isEmpty()
{
	return cards.empty();
}

/****************************************************************************************
Card Deck::nextCard()
	returns next card in the Deck, NULL if the Deck is empty
****************************************************************************************/
void Deck::drawNextCard(Hand& hand)
{
	if (!cards.empty())
	{
		hand.addCard(cards.front());
		cards.erase(cards.begin());
	}
	else
	{
		cout << "Deck is empty" << endl;
	}
}

//  Card class Definitions 


int Card::getValue()
{
	//cout << "isFaceUp : " << isFaceUp << endl;
	if(isFaceUp) 
	{ 
		return value; 
	}

	return 0;
}
string Card::getSuite()
{
	return face;
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
	if (cards.empty() || cards[0].getValue() == 0)
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

void Hand::flipFirstCard()
{
	if (!cards.empty())
	{
		cards[0].flip();
	}
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
		cout << "Welcome to BlackJack" << endl;
		
		cout << "Enter players name" << endl;
		cin >> name;

		Player p(name);
		Player d("Dealer");
			
		if (noOfRounds == maxNumberOfRoundsBeforeShuffle)
		{
			deck.resetDeck();
			deck.createDeck();
			deck.shuffle();		// Randomize
		}

		// Present 2 cards to player and 2 to dealer with one face down	
		deck.drawNextCard(p.hand);
		deck.drawNextCard(d.hand);
		d.hand.flipFirstCard();
		deck.drawNextCard(p.hand);
		deck.drawNextCard(d.hand);

		cout << p.name << endl;
		cout << "Player Hands -> " ;
		for (int i = 0 ; i < p.hand.cards.size() ; i++)
		{
			cout << p.hand.cards[i].getSuite() <<  p.hand.cards[i].getValue() << ",";
		}
		cout << " Total -> " << p.getTotalPoints();
		cout << endl;
		cout << "Dealer Hands -> ";
		for (int i = 0 ; i < d.hand.cards.size() ; i++)
		{
			cout << d.hand.cards[i].getSuite() <<  d.hand.cards[i].getValue() << ",";
		}
		cout << " Total -> " << d.getTotalPoints();
		cout << endl;

		// cout << "Deck after Initial deal" << endl;
		// printDeck();

		cout << "Player total points : " << p.getTotalPoints() << endl;
		cout << "Dealer total points : " << d.getTotalPoints() << endl;
		
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
				cout << "New card is " << p.hand.cards.back().getValue() << endl;
				cout << "Player Hands -> " ;
				for (int i = 0 ; i < p.hand.cards.size() ; i++)
				{
					cout << p.hand.cards[i].getSuite() <<  p.hand.cards[i].getValue() << ",";
				}
				cout << " Total -> " << p.getTotalPoints();
				cout << endl;
				cout << "Player has ace -> " << p.hand.isAceIncluded << endl;
				cout << "Dealer Hands -> ";
				for (int i = 0 ; i < d.hand.cards.size() ; i++)
				{
					cout << d.hand.cards[i].getSuite() <<  d.hand.cards[i].getValue() << ",";
				}
				cout << " Total -> " << d.getTotalPoints();
				cout << endl;
				cout << "Dealer has ace -> " << d.hand.isAceIncluded << endl;
				if (p.getTotalPoints() > 21)
				{
					cout << "You Lost!" << endl;
					break;
				}
			}
			else
			{
				cout << "Invalid choice, try again!" << endl;
			}
		}

		// cout << "Deck after player stands" << endl;
		// printDeck();

		d.hand.flipFirstCard();
		//cout << "Dealer total points after player stand : " << d.getTotalPoints() << endl;
		int playerPoints = p.getTotalPoints();
		int dealerPoints = d.getTotalPoints();
		

		if (playerPoints > 21)
		{
			cout << "Oh! Player Busted! Lost" << endl;
		}
		else // playerPoints <= 21
		{
			while (dealerPoints <= 16 || (dealerPoints == 17 && d.hand.isAceIncluded))
			{
				cout << "Dealing card to Dealer ";
				deck.drawNextCard(d.hand);
				cout << "New card is " << d.hand.cards.back().getValue() << endl;
				cout << "Player Hands -> " ;
				for (int i = 0 ; i < p.hand.cards.size() ; i++)
				{
					cout << p.hand.cards[i].getSuite() <<  p.hand.cards[i].getValue() << ",";
				}
				cout << endl;
				cout << "Player has ace -> " << p.hand.isAceIncluded << endl;
				cout << "Dealer Hands -> ";
				for (int i = 0 ; i < d.hand.cards.size() ; i++)
				{
					cout << d.hand.cards[i].getSuite() <<  d.hand.cards[i].getValue() << ",";
				}
				cout << endl;
				cout << "Dealer has ace -> " << d.hand.isAceIncluded << endl;
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

		cout << "Player P total points : " << playerPoints << endl;
		cout << "Dealer D total points : " << dealerPoints << endl;

		cout << "Quit(q) or Play(p)" << endl;
		cin >> playerChoice;

		if (playerChoice == "Q" || playerChoice == "q" || playerChoice == "quit")
		{
			playerQuits = true;
		}

		playerStand = false;
		noOfRounds++;
	}
	return;
}
