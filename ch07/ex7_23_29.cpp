#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>

class Screen
{
  public:
    using pos = std::string::size_type;

    Screen() = default;

    Screen(pos height, pos width) : Screen(height, width, ' ')
    {
    }

    Screen(pos height, pos width, char fill)
        : height_(height), width_(width), contents_(checked_size(height, width), fill)
    {
    }

    Screen &move(pos row, pos column)
    {
        if (row >= height_ || column >= width_)
        {
            throw std::out_of_range("Screen position is outside the screen.");
        }
        cursor_ = row * width_ + column;
        return *this;
    }

    Screen &set(char value)
    {
        contents_.at(cursor_) = value;
        return *this;
    }

    Screen &display(std::ostream &output)
    {
        output << contents_;
        return *this;
    }

    const Screen &display(std::ostream &output) const
    {
        output << contents_;
        return *this;
    }

  private:
    static pos checked_size(pos height, pos width)
    {
        if (width != 0 && height > std::numeric_limits<pos>::max() / width)
        {
            throw std::length_error("Screen dimensions are too large.");
        }
        return height * width;
    }

    pos cursor_ = 0;
    pos height_ = 0;
    pos width_ = 0;
    std::string contents_;
};

class ValueScreen
{
  public:
    ValueScreen(Screen::pos height, Screen::pos width, char fill) : screen_(height, width, fill)
    {
    }

    ValueScreen move(Screen::pos row, Screen::pos column)
    {
        screen_.move(row, column);
        return *this;
    }

    ValueScreen set(char value)
    {
        screen_.set(value);
        return *this;
    }

    ValueScreen display(std::ostream &output)
    {
        screen_.display(output);
        return *this;
    }

  private:
    Screen screen_;
};

int main()
{
    Screen reference_screen(5, 5, 'X');
    reference_screen.move(4, 0).set('#').display(std::cout);
    std::cout << '\n';
    reference_screen.display(std::cout);
    std::cout << '\n';

    ValueScreen value_screen(5, 5, 'X');
    value_screen.move(4, 0).set('#').display(std::cout);
    std::cout << '\n';
    value_screen.display(std::cout);
    std::cout << '\n';
    return 0;
}
