
#include "letternumber.h"




QString number2Letter(int i)
{
    QString letters[26] =
    {
        "A",
        "B",
        "C",
        "D",
        "E",
        "F",
        "G",
        "H",
        "I",
        "J",
        "K",
        "L",
        "M",
        "N",
        "O",
        "P",
        "Q",
        "R",
        "S",
        "T",
        "U",
        "V",
        "W",
        "X",
        "Y",
        "Z"
    };
    int n = i % 26;
    int m = (i - n + 26) / 26 - 1;
    return letters[m] + letters[n];
}
