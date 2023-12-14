#include "PokerHand.hpp"
#include <algorithm>
#include "vector"
#include "string"
using namespace std;
PokerHand :: PokerHand (const std::vector<Card> &cards){
    this->cards=cards;
}

std::vector <Card> PokerHand :: get_cards(){
    return cards;
}
void PokerHand :: order_cards(){ //we order the cards in descending order, so that the highest card is the first one
    std::sort(cards.begin(),cards.end());
    std::reverse(cards.begin(),cards.end());
}
bool PokerHand:: is_member(Card card){
    for(int i=0;i<cards.size();i++){
        if(cards[i]==card) return true;
    }
    return false;
}

bool PokerHand:: has_royal_flush(){ //for each royal flush, we check if we have it in the received cards. We assume the received cards are different
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
bool PokerHand:: has_flush(){
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
bool::PokerHand:: has_straight(){
    
    int ranks[15]; //for each rank, we will store if it is in the hand or not
    for (int i=1; i<15; i++) ranks[i]=0; //we initialize the number of cards with rank i with 0
    
    for (int i = 0; i < cards.size(); i++) {
        ranks[cards[i].getValue()]=1; //we increment the number of cards with the rank/value of the current card
        if (cards[i].getValue()==14) ranks[1]=1; //if the card is an ace, we also increment the rank of the ace (because it can be used as a 1) (done for the purpose of the straight A,2,3,4,5)
        
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
int PokerHand:: max_straight(){
    int ranks[15]; //for each rank, we will store if it is in the hand or not
    for (int i=1; i<15; i++) ranks[i]=0; //we initialize the number of cards with rank i with 0
    
    for (int i = 0; i < cards.size(); i++) {
        ranks[cards[i].getValue()]=1; //we increment number of cards with rank i
        if (cards[i].getValue()==14) ranks[1]=1; //if the card is an ace, we also increment the number of cards of rank 1
        
    }
    int max=0;
    for (int i=1; i<11; i++){
        if (ranks[i]==1 && 
            ranks[i+1]==1 && 
            ranks[i+2]==1 && 
            ranks[i+3]==1 && 
            ranks[i+4]==1) max = i+4; //if we have 5 consecutive ranks, then we have a straight
    }
    return max;
}
bool PokerHand :: has_straight_flush(){
    PokerHand hearts({}); //we create 4 empty poker hands, one for each suit
    PokerHand spades({});
    PokerHand diamonds({});
    PokerHand clubs({});
    for(int i=0;i<cards.size();i++){ //we create the subhands formed by cards of the same suit, we check if any of these hands has a straight
        if(cards[i].getSuit()==Suit::Hearts) hearts.cards.push_back(cards[i]);
        if(cards[i].getSuit()==Suit::Spades) spades.cards.push_back(cards[i]);
        if(cards[i].getSuit()==Suit::Diamonds) diamonds.cards.push_back(cards[i]);
        if(cards[i].getSuit()==Suit::Clubs) clubs.cards.push_back(cards[i]);
    }
    if(hearts.has_straight()==true || spades.has_straight()==true || diamonds.has_straight()==true || clubs.has_straight()==true) return true;
    else return false;
}

bool PokerHand :: has_four_of_a_kind(){
    int ranks[15]; //for each rank, we will store if it is in the hand or not
    for (int i=1; i<15; i++) ranks[i]=0; //we initialize the number of cards with rank i with 0
    
    for (int i = 0; i < cards.size(); i++) {
        ranks[cards[i].getValue()]++; //we increment the number of cards with the rank/value of the current card    
    }
    for (int i=1; i<15; i++){
        if (ranks[i]==4) return true; //if we have 4 cards of the same rank, then we have four of a kind
    }
    return false;
}
bool PokerHand :: has_three_of_a_kind(){
    int ranks[15]; //for each rank, we will store if it is in the hand or not
    for (int i=1; i<15; i++) ranks[i]=0; //we initialize the number of cards with rank i with 0
    
    for (int i = 0; i < cards.size(); i++) {
        ranks[cards[i].getValue()]++; //we increment the number of cards with the rank/value of the current card    
    }
    for (int i=1; i<15; i++){
        if (ranks[i]>=3) return true; //if we have 3 cards of the same rank, then we have three of a kind
    }
    return false;
}
bool PokerHand :: has_pair(){
    int ranks[15]; //for each rank, we will store if it is in the hand or not
    for (int i=1; i<15; i++) ranks[i]=0; //we initialize the number of cards with rank i with 0
    
    for (int i = 0; i < cards.size(); i++) {
        ranks[cards[i].getValue()]++; //we increment the number of cards with the rank/value of the current card
    }
    for (int i=2; i<15; i++){
        if (ranks[i]>=2) return true; //if we have 2 cards of the same rank, then we have a pair
    }
    return false;
}
bool PokerHand :: has_two_pairs(){
    int ranks[15]; //for each rank, we will store if it is in the hand or not
    for (int i=1; i<15; i++) ranks[i]=0; //we initialize all the number of cards of rank i with 0
    
    for (int i = 0; i < cards.size(); i++) {
        ranks[cards[i].getValue()]++; //we increment the number of cards with rank i     
    }
    int number_pairs=0;
    for (int i=1; i<15; i++){
        if (ranks[i]>=2) number_pairs++; //if we have 2 cards of the same rank, then we have a pair
    }
    if(number_pairs>=2) return true;
    else return false;
}
bool PokerHand :: has_full_house(){
    if(has_two_pairs()==true && has_three_of_a_kind()==true) return true;
    else return false;
}
bool PokerHand :: has_high_card(){
    if(cards.size()>0)  return true;
}
PokerCombinations PokerHand :: get_combination(){
    if(has_royal_flush()==true) return PokerCombinations::RoyalFlush;
    else if(has_straight_flush()==true) return PokerCombinations::StraightFlush;
    else if(has_four_of_a_kind()==true) return PokerCombinations::FourOfAKind;
    else if(has_full_house()==true) return PokerCombinations::FullHouse;
    else if(has_flush()==true) return PokerCombinations::Flush;
    else if(has_straight()==true) return PokerCombinations::Straight;
    else if(has_three_of_a_kind()==true) return PokerCombinations::ThreeOfAKind;
    else if(has_two_pairs()==true) return PokerCombinations::TwoPairs;
    else if(has_pair()==true) return PokerCombinations::Pair;
    else if(has_high_card()==true) return PokerCombinations::HighCard;
    else return PokerCombinations::HighCard;
}
std::vector<int> PokerHand::get_score(){// for each hand, we create a score, which will be used to compare the hands
                                        //to create the score, on the first position of an array we store the value of the highest poker combination
                                        //on the second position we store the value of the first tie-breaker etc.

    std::vector<int> score(6,0); //we initialize the score with 0
    
    if(has_royal_flush()==true) 
    {score[0]=10;} //if we have a royal flush, we assign the score 10, no tie breakers
    else if(has_straight_flush()==true) {
        score[0]=9; 
        PokerHand hearts({}); //we create 4 empty poker hands, one for each suit
        PokerHand spades({});
        PokerHand diamonds({});
        PokerHand clubs({});
        for(int i=0;i<cards.size();i++){ //we create the subhands formed by cards of the same suit, we check if any of these hands has a straight
            if(cards[i].getSuit()==Suit::Hearts) hearts.cards.push_back(cards[i]);
            if(cards[i].getSuit()==Suit::Spades) spades.cards.push_back(cards[i]);
            if(cards[i].getSuit()==Suit::Diamonds) diamonds.cards.push_back(cards[i]);
            if(cards[i].getSuit()==Suit::Clubs) clubs.cards.push_back(cards[i]);
    }
    score[1]=std::max ({hearts.max_straight(), spades.max_straight(), diamonds.max_straight(), clubs.max_straight()});
    //std::cout<<"Straight Flush "<<score[0]<<" "<<score[1]<<std::endl;
    }
    else if(has_four_of_a_kind()==true) {
        score[0]=8;
        int ranks[15]; //for each rank, we will store if it is in the hand or not
    for (int i=1; i<15; i++) ranks[i]=0; //we initialize the number of cards with rank i with 0
    
    for (int i = 0; i < cards.size(); i++) {
        ranks[cards[i].getValue()]++; //we increment the number of cards with a given rank
    }
    int max=0;
    for (int i=1; i<15; i++){
        if (ranks[i]==4) max=i; //if we have 4 cards of the same rank, then we have four of a kind 

    }
    score[1]=max; // the first tie breaker is the rank of the four of a kind
    for(int i=14; i>1; i--){
        if(ranks[i]>=1 && i!=max) {score[2]=i; break;} //the second tie breaker is the highest rank of a card that is not from the quatruplet
    }

    }
    else if(has_full_house()==true) {
        score[0]=7; 
        int ranks[15]; //for each rank, we will store if it is in the hand or not
        for (int i=1; i<15; i++) ranks[i]=0; //we initialize the number of cards with rank i with 0
    
    for (int i = 0; i < cards.size(); i++) {
        ranks[cards[i].getValue()]++; //we increment the number of cards with rank i
        
        
    }
    int max=0;
    for (int i=1; i<15; i++){
        if (ranks[i]==3) max=i; 

    }
    score[1]=max; // the first tie breaker is the rank of the three of a kind
    for(int i=14; i>1; i--){
        if(ranks[i]>=2 && i!=max) {score[2]=i; break;} //the second tie breaker is the highest rank of a card that is not from the triplet
    }
    }
    else if(has_flush()==true) {
        score[0]=6; 
        PokerHand hearts({}); //we create 4 empty poker hands, one for each suit
        PokerHand spades({});
        PokerHand diamonds({});
        PokerHand clubs({});
        for(int i=0;i<cards.size();i++){ //we create the subhands formed by cards of the same suit, we check if any of these hands has a straight
            if(cards[i].getSuit()==Suit::Hearts) hearts.cards.push_back(cards[i]);
            if(cards[i].getSuit()==Suit::Spades) spades.cards.push_back(cards[i]);
            if(cards[i].getSuit()==Suit::Diamonds) diamonds.cards.push_back(cards[i]);
            if(cards[i].getSuit()==Suit::Clubs) clubs.cards.push_back(cards[i]);
    }
    if(hearts.cards.size()>=5){
        hearts.order_cards();
        for (int i=1; i<=5; i++){
            score[i]=hearts.cards[i-1].getValue(); //the tie breakers are the ranks of the cards that form the flush, from highest to lowest
        }
    }
    if (spades.cards.size()>=5){
        spades.order_cards();
        for (int i=1; i<=5; i++){
            score[i]=spades.cards[i-1].getValue(); //the tie breakers are the ranks of the cards that form the flush, from highest to lowest
        }
    }
    if(diamonds.cards.size()>=5){
        diamonds.order_cards();
        for (int i=1; i<=5; i++){
            score[i]=diamonds.cards[i-1].getValue(); //the tie breakers are the ranks of the cards that form the flush, from highest to lowest
        }
    }
    if(clubs.cards.size()>=5){
        clubs.order_cards();
        for (int i=1; i<=5; i++){
            score[i]=clubs.cards[i-1].getValue(); //the tie breakers are the ranks of the cards that form the flush, from highest to lowest
        }
    }

    }
    else if(has_straight()==true) {
        score[0]=5; 
        score[1]=max_straight(); //the tie breaker is the maximum straight
    }
    
    
    else if(has_three_of_a_kind()==true) {
    score[0]=4; 
    int ranks[15]; //for each rank, we will store if it is in the hand or not
        for (int i=1; i<15; i++) ranks[i]=0; //we initialize the number of cards with rank i with 0
    
    for (int i = 0; i < cards.size(); i++) {
        ranks[cards[i].getValue()]++; //we increment the number of cards with the rank of the current card
    }
    //for (int i=14; i>1; i--){
      //  std::cout<<ranks[i]<<" "<<i<<" "; //the tie breaker is the rank of the triplet
    //}
    //std::cout<<std::endl;
    for(int i=14; i>1; i--){
        if(ranks[i]==3) {score[1]=i; break;} //the tie breaker is the rank of the triplet
    }
    for (int i=14; i>1; i--){
        if(ranks[i]>=1 && i!=score[1]) {score[2]=i; break;} //the second tie breaker is the highest rank of a card that is not from the triplet
    }
    for (int i=14; i>1; i--){
        if(ranks[i]>=1 && i!=score[1] && i!=score[2]) {score[3]=i; break;} //the third tie breaker is the highest rank of a card that is not from the triplet or the pair
    }

    }
    else if(has_two_pairs()==true) {
    score[0]=3;
    int ranks[15]; //for each rank, we will store if it is in the hand or not
        for (int i=1; i<15; i++) ranks[i]=0; //we initialize the number of cards with rank i with 0
    for(int i=0; i<cards.size(); i++){
        ranks[cards[i].getValue()]++; //we increment the number of cards with the rank of the current card
    }
    for (int i=14; i>1; i--){
        if(ranks[i]==2) {score[1]=i; break;} //the first tie breaker is the rank of the first pair
    }
    for (int i=14; i>1; i--){
        if(ranks[i]==2 && i!=score[1]) {score[2]=i; break;} //the second tie breaker is the rank of the second pair
    }
    for (int i=14; i>1; i--){
        if(ranks[i]>=1 && i!=score[1] && i!=score[2]) {score[3]=i; break;} //the third tie breaker is the highest rank of a card that is not from the pairs
    }

    }
    else if(has_pair()==true) {
    score[0]=2;
    int ranks[15]; //for each rank, we will store if it is in the hand or not
        for (int i=1; i<15; i++) ranks[i]=0; //we initialize the number of cards with rank i with 0
    for(int i=0; i<cards.size(); i++){
        ranks[cards[i].getValue()]++; //we increment the number of cards the rank of the current card
    }
    for (int i=14; i>1; i--){
        if(ranks[i]==2) {score[1]=i; break;} //the first tie breaker is the rank of the pair
    }
    for (int i=14; i>1; i--){
        if(ranks[i]>=1 && i!=score[1]) {score[2]=i; break;} //the second tie breaker is the highest rank of a card that is not from the pair
    }
    for (int i=14; i>1; i--){
        if(ranks[i]>=1 && i!=score[1] && i!=score[2]) {score[3]=i; break;} //the third tie breaker is the highest rank of a card that is not from the pair or the first tie breaker
    }
    for (int i=14; i>1; i--){
        if(ranks[i]>=1 && i!=score[1] && i!=score[2] && i!=score[3]) {score[4]=i; break;} //the fourth tie breaker is the highest rank of a card that is not from the pair or the first or second tie breaker
    }
    }
    
   
    else if(has_high_card()==true) { 
    score[0]=1; 
    int ranks[15]; //for each rank, we will store if it is in the hand or not
        for (int i=1; i<15; i++) ranks[i]=0; //we initialize the number of cards with rank i with 0
    for(int i=0; i<cards.size(); i++){
        ranks[cards[i].getValue()]++; //we increment the number of cards with the rank of the current card
    }
    int j=0; //we create a counter for the tie breakers
    int i=14; // we begin with the highest value card and iteratively check the best ones in descending order
    while (j<5){
        if(ranks[i]==1) {
        score[j+1]=i; //the tie breakers are the ranks of the cards, from highest to lowest
        j++;
        }
        i--;
    }
        
    }
    else score[0]=0; 
    return score;
}
int compare_hands(PokerHand hand1, PokerHand hand2){
    std::vector<int> score1=hand1.get_score();
    std::vector<int> score2=hand2.get_score();
    for(int i=0; i<score1.size(); i++){ // we iteratively check the kickers, from the most important to the least important
        if(score1[i]>score2[i]) return 1; //if the first hand has a better score, we return 1
        if(score1[i]<score2[i]) return 2; //if the second hand has a better score, we return 2
    }
    return 0; //if the hands are equal, we return 0
}

