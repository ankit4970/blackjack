#include "../blackjack.h"

/*
Please implement a command-line blackjack game using C, C++, or Objective-C:

Requirements

•   Dealer must hit on soft 17
•   Single Deck. The deck is shuffled every 6 rounds.
•   Player is not allowed to split cards.
•   Keep track of win percentage for the player.
•   Provide a readme file explaining how to compile the source and other info that might be interesting.

You don't have to implement any AI other than the one mentioned above - it's just one player vs. dealer.

If any third party code is used, please give credit and cite source.
*/
int main()
{
	BlackJack blackjack;
	blackjack.play();
	return 0;
}