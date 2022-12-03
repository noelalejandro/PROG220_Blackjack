// PROG 220-02
// Blackjack
// Noel Gutierrez

#pragma once
#include <iostream>
#include <algorithm>
#include <cassert>
#include <chrono>
#include <numeric>
#include <random>
#include <vector>

enum GameLogic
{
    WIN,
    LOSE,
    PUSH,
    BLACKJACK
};

enum Face
{
    NUMBER,
    JACK,
    QUEEN,
    KING
};

enum Suit
{
    HEART,
    DIAMOND,
    SPADE,
    CLUB
};

struct Card;

struct Deck;

class Player;

bool NaturalBlackjack(Player *p);

GameLogic Game();

std::string Result(GameLogic g);
