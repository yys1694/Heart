#include <vector>
#include <algorithm>
#include <iostream>
#include "CardPile.h"
#include "Card.h"

const uint32_t CardPile::DefaultRandomSeed = 37;

CardPile::CardPile() : prng(DefaultRandomSeed) {}

void CardPile::setRandomSeed(uint32_t randomSeed) {
	prng.seed(randomSeed);
}

// Other stuff 

CardPile::~CardPile() {}

//Given function; for shuffle the deck
void CardPile::shuffle() {
	for (int i = size() - 1; i > 0; i--) {
		const int j = prng(i);
		Card* tmp = at(j);
		at(j) = at(i);
		at(i) = tmp;
	}
}

//Implemented function; for calculating the scores
int CardPile::heartsValue() {
	int scores = 0;
	
	for(unsigned int i=0; i<size(); i++){
		scores = scores + at(i)->getHeartsValue();
	}

	return scores;
}

//Implemented function; for print out the deck
void CardPile::print() {
	for(unsigned int i = 0; i < size(); i++){
		cout<<*at(i)<<" ";
	}
	cout<<endl;
}
