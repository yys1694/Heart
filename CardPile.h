#ifndef _CARDPILE_H_
#define _CARDPILE_H_

using namespace std;

#include <vector>
#include "Card.h"
#include "PRNG.h"

class CardPile : private vector<Card*> {
    public:
	// Constructors and destructor
	CardPile ();
	virtual ~CardPile ();

	void setRandomSeed(uint32_t randomSeed);
	// Other stuff needed

	//Added for using privately inherited vector<Card*>
	using vector<Card*>::iterator;
	using vector<Card*>::empty;
	using vector<Card*>::size;
	using vector<Card*>::clear;
	using vector<Card*>::at;
	using vector<Card*>::push_back;
	using vector<Card*>::begin;
	using vector<Card*>::erase;

	//Given and Added functions
	void shuffle();
	int heartsValue();
	virtual void print();
    private:
	PRNG prng;
	static const uint32_t DefaultRandomSeed;
};

#endif
