#ifndef VISUALPINFO_HPP
#define VISUALPINFO_HPP


#include "qlabel.h"
#include <vector>


class VisualPInfo
{
public:
    VisualPInfo(QLabel* name, QLabel* stack, QLabel* bet, QLabel* Card1, QLabel* Card2);

    std::vector<QLabel*> Cards;
    QLabel* name;
    QLabel* stack;
    QLabel* bet;

};

#endif // VISUALPINFO_HPP
