#include "PokerHand.hpp"
#include <algorithm>
#include "vector"
#include "string"

PokerHand :: PokerHand (std::vector<Card> cards){
    this->cards=cards;
}

std::vector <Card> PokerHand :: get_cards(){
    return cards;
}
void PokerHand :: order_cards(){
    std::sort(cards.begin(),cards.end());
}

bool PokerHand:: is_royal_flush(){
Suit suit[4] = {Suit:: Spades, Suit:: Hearts, Suit:: Diamonds, Suit:: Clubs};
std::vector<Card> Spades_royal_flush={Card(suit[0], 10), Card(suit[0],11), Card(suit[0],12), Card(suit[0],13), Card(suit[0],14)}; //the spades royal flush
std::vector<Card> Hearts_royal_flush={Card(suit[1], 10), Card(suit[1],11), Card(suit[1],12), Card(suit[1],13), Card(suit[1],14)}; //the hearts royal flush
std::vector<Card> Diamonds_royal_flush={Card(suit[2], 10), Card(suit[2],11), Card(suit[2],12), Card(suit[2],13), Card(suit[2],14)}; //the diamonds royal flush   
std::vector<Card> Clubs_royal_flush={Card(suit[3], 10), Card(suit[3],11), Card(suit[3],12), Card(suit[3],13), Card(suit[3],14)}; //the clubs royal flush
int number_spades=0;
int number_hearts=0;
int number_diamonds=0;
int number_clubs=0;
for(int i=0;i<cards.size();i++){
    if(cards[i].getSuit()==suit[0]) {
        if (cards[i]==Spades_royal_flush[0] || 
        cards[i]==Spades_royal_flush[1] || 
        cards[i]== Spades_royal_flush[2] || 
        cards[i]==Spades_royal_flush[3] || 
        cards[i]==Spades_royal_flush[4]) number_spades++; std::cout<<number_spades;
    } //we compute the number of cards from the spades royal flush in our hand
     if(cards[i].getSuit()==suit[1]) {
        if (cards[i]==Hearts_royal_flush[0] || 
        cards[i]==Hearts_royal_flush[1] || 
        cards[i]== Hearts_royal_flush[2] || 
        cards[i]==Hearts_royal_flush[3] || 
        cards[i]==Hearts_royal_flush[4]) number_hearts++; 
    } //we compute the number of cards from the hearts royal flush in our hand
    if(cards[i].getSuit()==suit[2]) {
        if (cards[i]==Diamonds_royal_flush[0] || 
        cards[i]==Diamonds_royal_flush[1] || 
        cards[i]== Diamonds_royal_flush[2] || 
        cards[i]==Diamonds_royal_flush[3] || 
        cards[i]==Diamonds_royal_flush[4]) number_diamonds++; 
    } //we compute the number of cards from the diamonds royal flush in our hand
    if(cards[i].getSuit()==suit[3]) {
        if (cards[i]==Clubs_royal_flush[0] || 
        cards[i]==Clubs_royal_flush[1] || 
        cards[i]== Clubs_royal_flush[2] || 
        cards[i]==Clubs_royal_flush[3] || 
        cards[i]==Clubs_royal_flush[4]) number_clubs++; 
    } //we compute the number of cards from the clubs royal flush in our hand
}
if(number_spades ==5 || number_hearts==5 || number_diamonds==5 || number_clubs==5)
{
    return true;
}
else return false;
}



