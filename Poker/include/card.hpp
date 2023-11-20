enum suitType {
    Diamond = 1, 
    Club = 2,
    Heart = 3,
    Spade = 4,
};
enum cardValue {
    Two = 2,
    Three = 3,
    Four = 4,
    Five = 5,
    Six = 6,
    Seven = 7, 
    Eight = 8,
    Nine = 9,
    Ten = 10,
    Jack = 11,
    Queen = 12,
    King = 13,
    Ace = 14
};
class Card {
private:
    suitType suit;
    cardValue value;
public:
    Card(suitType suit, cardValue value);
    suitType get_suit() const;
    cardValue get_value() const;
    bool operator == (Card const& another) const;
    bool operator > (Card const& another) const;
    bool operator < (Card const& another) const;
};