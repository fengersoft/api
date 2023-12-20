
#include "stingwidthconvert.h"

std::string utf8_tohalf(std::string input)
{
    std::string temp;
    for (size_t i = 0; i < input.size(); i++)
    {
        if (((input[i] & 0xF0) ^ 0xE0) == 0)
        {
            int old_char = (input[i] & 0xF) << 12 | ((input[i + 1] & 0x3F) << 6 | (input[i + 2] & 0x3F));
            if (old_char == 0x3000)   // blank
            {
                char new_char = 0x20;
                temp += new_char;
            }
            else if (old_char >= 0xFF01 && old_char <= 0xFF5E)     // full char
            {
                char new_char = old_char - 0xFEE0;
                temp += new_char;
            }
            else     // other 3 bytes char
            {
                temp += input[i];
                temp += input[i + 1];
                temp += input[i + 2];
            }
            i = i + 2;
        }
        else
        {
            temp += input[i];
        }
    }
    return temp;
}



QString toHalfWidthString(QString s)
{
    string dest = utf8_tohalf(s.toStdString());
    return QString::fromStdString(dest);

}
