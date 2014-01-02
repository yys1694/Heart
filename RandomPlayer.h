#ifndef __RANDOMPLAYER_H__
#define __RANDOMPLAYER_H__

#include <iostream>
#include "Player.h"
#include "PRNG.h"

using namespace std;

class RandomPlayer : public Player {
   private:
      //For random decision while playing game
      PRNG prng;
   public:
      RandomPlayer(string name, uint32_t randomSeed);
      virtual ~RandomPlayer();
 
      //Part 4
      Card lead(int numCards, bool first);
      Card throwOff(int numCards);
      Card followSuit(int numCards, const Card &trumpCard);

};

#endif
