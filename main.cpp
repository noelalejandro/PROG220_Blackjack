// PROG 220-02
// Blackjack
// Noel Gutierrez

#include "main.hpp"

struct Card
{
  public:
    int value;
    Suit suit;
    Face face;
    Card(int val, Suit suit, Face face)
    {
        value = val;
        suit = suit;
        face = face;
    }
};

struct Deck
{
  public:
    std::vector<Card> stack = std::vector<Card>();

    Deck()
    {
        for (int suits = 0; suits < 4; suits++)
        {
            int val = 1;
            int face = 0;
            for (int cards = 0; cards < 13; cards++)
            {
                stack.push_back(std::move(Card(val, (Suit)suits, (Face)face)));
                if (val != 10)
                    val++;
                else
                {
                    face++;
                }
            }
        }
    }

    void ShuffleCards()
    {
        auto seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::shuffle(stack.begin(), stack.end(), std::default_random_engine(seed));
    }

    Card Deal()
    {
        Card ret = stack.back();
        stack.erase(stack.end()-1);
        return std::move(ret);
    }
};

class Player
{
  public:
  std::vector<Card> hand;

    Player()
    {
        hand = std::vector<Card>();
    }

    int CheckHand()
    {
        int total = 0;
        for(Card card:hand) total+=card.value;
        return total;
    }
};

bool NaturalBlackjack(Player *p)
{
    if (p->CheckHand() == 11 && (p->hand[0].value == 1 || p->hand[1].value == 1))
        return true;
    return false;
}

GameLogic Game()
{
    Deck deck = Deck();
    deck.ShuffleCards();
    Player *player = new Player();
    Player *dealer = new Player();

    player->hand.push_back(deck.Deal());
    player->hand.push_back(deck.Deal());
    dealer->hand.push_back(deck.Deal());
    dealer->hand.push_back(deck.Deal());

   if (NaturalBlackjack(player) && NaturalBlackjack(dealer))    
    {
        std::cout << "Dealer wins with a hand of " << dealer->CheckHand() << std::endl;
        return PUSH;
    }    

    while (player->CheckHand() < 17)
    {
        player->hand.push_back(deck.Deal());
        if (player->CheckHand() > 21)
            {
            std::cout << "Dealer wins with a hand of " << dealer->CheckHand() << std::endl;
            return LOSE;
            }
    }

    while (dealer->CheckHand() < 17)
    {
        dealer->hand.push_back(deck.Deal());
        if (dealer->CheckHand() > 21) 
        {
            std::cout << "Player wins with a hand of " << player->CheckHand() << std::endl;
            return WIN;
        }
    }

    if (NaturalBlackjack(player)) 
    {
        return BLACKJACK;
    }
    else if (player->CheckHand() == 21)
    {
        std::cout << "Player wins with a hand of " << player->CheckHand() << std::endl;
        return WIN;
    }
    else if (player->CheckHand() > dealer->CheckHand())
    {
        std::cout << "Player wins with a hand of " << player->CheckHand() << std::endl;
        return WIN;
    }
    else if ((player->CheckHand() == dealer->CheckHand()))
    {
         std::cout << "Player and dealer draw with a hand of " << dealer->CheckHand() << std::endl;
        return PUSH;  
    }
    else if (dealer->CheckHand() == 21)
    {
        std::cout << "Dealer wins with a hand of " << dealer->CheckHand() << std::endl;
        return LOSE;
    }
    std::cout << "Dealer wins with a hand of " << dealer->CheckHand() << std::endl;
    return LOSE;
}

std::string Result(GameLogic g)
{
   
       
    if (g==WIN) 
    {
        return ("");
    }
    else if(g==LOSE)
    {
        return ("");
    }
    else if(g==PUSH)
    {
        return ("\nPlayer receives money back\n");
    }
    else 
    {
        return ("\nPlayer receives natural blackjack. $1.5x the original bet!\n");
    }
}

int main()
{
    for (int game = 0; game < 100; game++)
    {        
        std::cout << Result(Game()) << std::endl;
    }
    return 0;
}
