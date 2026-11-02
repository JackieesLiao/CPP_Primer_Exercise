#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

class Y;
class X
{
  public:
    Y *other = nullptr;
};
class Y
{
  public:
    X value;
};

class Screen;
class WindowManager
{
  public:
    using ScreenIndex = std::vector<Screen>::size_type;
    WindowManager();
    void clear(ScreenIndex index);
    void display(ScreenIndex index, std::ostream &output) const;

  private:
    std::vector<Screen> screens_;
};

class Screen
{
    friend void WindowManager::clear(WindowManager::ScreenIndex index);

  public:
    Screen(std::string::size_type height, std::string::size_type width, char fill)
        : height_(height), width_(width), contents_(height * width, fill)
    {
    }

    void display(std::ostream &output) const
    {
        output << contents_;
    }

  private:
    std::string::size_type height_;
    std::string::size_type width_;
    std::string contents_;
};

WindowManager::WindowManager()
{
    screens_.emplace_back(2, 3, 'X');
}

void WindowManager::clear(ScreenIndex index)
{
    Screen &screen = screens_.at(index);
    screen.contents_ = std::string(screen.height_ * screen.width_, ' ');
}

void WindowManager::display(ScreenIndex index, std::ostream &output) const
{
    screens_.at(index).display(output);
}

int main()
{
    X first;
    Y second;
    first.other = &second;
    WindowManager manager;
    manager.display(0, std::cout);
    std::cout << '\n';
    manager.clear(0);
    manager.display(0, std::cout);
    std::cout << '\n';
    return 0;
}
