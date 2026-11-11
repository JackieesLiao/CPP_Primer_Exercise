#ifndef CH16_SCREEN_H
#define CH16_SCREEN_H

#include <cstddef>
#include <istream>
#include <ostream>
#include <string>
#include <vector>

// 16.14/16.15: a small Screen with equality, ordering and stream
// operators. The stream operators are friends and non-members.

class Screen
{
    friend std::istream &operator>>(std::istream &input, Screen &screen);
    friend std::ostream &operator<<(std::ostream &output, const Screen &screen);

public:
    Screen() : height(0), width(0)
    {
    }

    Screen(std::size_t rows, std::size_t columns, char fill = ' ')
        : height(rows), width(columns), contents(rows * columns, fill)
    {
    }

    bool operator==(const Screen &other) const
    {
        return height == other.height && width == other.width &&
               contents == other.contents;
    }

    bool operator!=(const Screen &other) const
    {
        return !(*this == other);
    }

    bool operator<(const Screen &other) const
    {
        return contents < other.contents;
    }

private:
    std::size_t height;
    std::size_t width;
    std::vector<char> contents;
};

inline std::istream &operator>>(std::istream &input, Screen &screen)
{
    std::size_t rows = 0, columns = 0;
    std::string text;
    input >> rows >> columns >> text;
    if (input)
    {
        Screen built(rows, columns);
        for (std::size_t index = 0; index < rows * columns; ++index)
        {
            built.contents[index] =
                text[index % text.size()];
        }
        screen = built;
    }
    return input;
}

inline std::ostream &operator<<(std::ostream &output, const Screen &screen)
{
    for (std::size_t row = 0; row < screen.height; ++row)
    {
        for (std::size_t column = 0; column < screen.width; ++column)
        {
            output << screen.contents[row * screen.width + column];
        }
        output << '\n';
    }
    return output;
}
#endif
