#include <algorithm>
#include <functional>
#include <iostream>
#include <map>
#include <string>
#include <vector>

// 19.11-19.18: pointers to members. A data member pointer names the
// Screen::title member (19.12/19.13); a table of member function pointers
// drives the cursor moves (19.14-19.17); count_if combines std::bind with
// &std::string::size to count long words (19.18).

class Screen
{
public:
    Screen() : cursor(0)
    {
    }

    Screen &forward()
    {
        ++cursor;
        return *this;
    }

    Screen &back()
    {
        --cursor;
        return *this;
    }

    Screen &up()
    {
        cursor += 5;
        return *this;
    }

    Screen &down()
    {
        cursor -= 5;
        return *this;
    }

    int position() const
    {
        return cursor;
    }

    std::string title;

private:
    int cursor;
};

using Action = Screen &(Screen::*)();

std::map<std::string, Action> build_menu()
{
    static const std::map<std::string, Action> menu{
        {"forward", &Screen::forward},
        {"back", &Screen::back},
        {"up", &Screen::up},
        {"down", &Screen::down}};
    return menu;
}

int main()
{
    // 19.12/19.13: a pointer to the string member of Screen.
    std::string Screen::*title_member = &Screen::title;
    Screen screen;
    screen.*title_member = "member pointer demo";
    std::cout << "title via .*: " << screen.*title_member << '\n';

    // 19.14-19.17: member function pointers invoked with .* and ->*.
    Screen *screen_pointer = &screen;
    const std::map<std::string, Action> menu = build_menu();
    (screen.*menu.at("forward"))();
    (screen.*menu.at("up"))();
    (screen_pointer->*menu.at("back"))();
    std::cout << "cursor now at " << screen.position() << '\n';

    // 19.18: member pointer combined with bind inside count_if.
    const std::vector<std::string> words{"stl", "algorithm", "iterator", "sort"};
    const std::size_t count = std::count_if(
        words.cbegin(), words.cend(),
        std::bind(std::greater<std::size_t>(), std::bind(&std::string::size, std::placeholders::_1),
                  6));
    std::cout << "words longer than 6: " << count << '\n';
    return 0;
}
