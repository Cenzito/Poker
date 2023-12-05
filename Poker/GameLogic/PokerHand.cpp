#include "PokerHand.hpp"
#include <algorithm>
#include "vector"
#include "string"
using namespace std;
PokerHand :: PokerHand (std::vector<Card> cards){
    this->cards=cards;
}

std::vector <Card> PokerHand :: get_cards(){
    return cards;
}
void PokerHand :: order_cards(){
    std::sort(cards.begin(),cards.end());
}
bool PokerHand:: is_member(Card card){
    for(int i=0;i<cards.size();i++){
        if(cards[i]==card) return true;
    }
    return false;
}

bool PokerHand:: is_royal_flush(){ //for each royal flush, we check if we have it in the received cards. We assume the received cards are different
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
        cards[i]==Spades_royal_flush[4]) number_spades++; 
    } //we compute the number of cards from the spades royal flush in our hand, if it is 5, then we have a royal flush
     if(cards[i].getSuit()==suit[1]) {
        if (cards[i]==Hearts_royal_flush[0] || 
        cards[i]==Hearts_royal_flush[1] || 
        cards[i]== Hearts_royal_flush[2] || 
        cards[i]==Hearts_royal_flush[3] || 
        cards[i]==Hearts_royal_flush[4]) number_hearts++; 
    } //we compute the number of cards from the hearts royal flush in our hand, if it is 5, then we have a royal flush
    if(cards[i].getSuit()==suit[2]) {
        if (cards[i]==Diamonds_royal_flush[0] || 
        cards[i]==Diamonds_royal_flush[1] || 
        cards[i]== Diamonds_royal_flush[2] || 
        cards[i]==Diamonds_royal_flush[3] || 
        cards[i]==Diamonds_royal_flush[4]) number_diamonds++; 
    } //we compute the number of cards from the diamonds royal flush in our hand, if it is 5, then we have a royal flush
    if(cards[i].getSuit()==suit[3]) {
        if (cards[i]==Clubs_royal_flush[0] || 
        cards[i]==Clubs_royal_flush[1] || 
        cards[i]== Clubs_royal_flush[2] || 
        cards[i]==Clubs_royal_flush[3] || 
        cards[i]==Clubs_royal_flush[4]) number_clubs++; 
    } //we compute the number of cards from the clubs royal flush in our hand, if it is 5, then we have a royal flush
}
if(number_spades ==5 || number_hearts==5 || number_diamonds==5 || number_clubs==5)
{
    return true;
}
else return false;
}
bool PokerHand:: is_flush(){
    Suit suit[4] = {Suit:: Spades, Suit:: Hearts, Suit:: Diamonds, Suit:: Clubs};
    int number_spades=0;
    int number_hearts=0;
    int number_diamonds=0;
    int number_clubs=0;
    for(int i=0;i<cards.size();i++){
        if(cards[i].getSuit()==suit[0]) number_spades++; //we compute the number of spades in our hand
        if(cards[i].getSuit()==suit[1]) number_hearts++; //we compute the number of hearts in our hand
        if(cards[i].getSuit()==suit[2]) number_diamonds++; //we compute the number of diamonds in our hand
        if(cards[i].getSuit()==suit[3]) number_clubs++; //we compute the number of clubs in our hand
    }
    //std::cout<<"Number of spades: "<<number_spades<<std::endl;
    //std::cout<<"Number of hearts: "<<number_hearts<<std::endl;
    //std::cout<<"Number of diamonds: "<<number_diamonds<<std::endl;
    //std::cout<<"Number of clubs: "<<number_clubs<<std::endl;
    if(number_spades ==5 || number_hearts==5 || number_diamonds==5 || number_clubs==5)
    {
        return true;
    }
    else return false;
}
bool::PokerHand:: is_straight(){
    
    int ranks[15]; //for each rank, we will store if it is in the hand or not
    for (int i=1; i<15; i++) ranks[i]=0; //we initialize all the ranks to 0
    
    for (int i = 0; i < cards.size(); i++) {
        ranks[cards[i].getValue()]=1; //we increment the rank of the card
        if (cards[i].getValue()==14) ranks[1]=1; //if the card is an ace, we also increment the rank of the ace (because it can be used as a 1)
        
    }
   // std::cout<<"exited for loop"<<std::endl;
    for (int i=1 ; i<15; i++){
        //std::cout<<ranks[i]<<" "<<i<<std::endl;
    }
    //std:: cout<< "exited second for loop"<<std::endl;
    for (int i=1; i<11; i++){
        if (ranks[i]==1 && 
            ranks[i+1]==1 && 
            ranks[i+2]==1 && 
            ranks[i+3]==1 && 
            ranks[i+4]==1) return true; //if we have 5 consecutive ranks, then we have a straight
    }
    return false;
}




