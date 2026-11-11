#ifndef CH13_STRING_H
#define CH13_STRING_H

#include <algorithm>
#include <cstring>
#include <iostream>
#include <memory>

// 13.44/13.47/13.49: our own String built on a dynamically allocated char
// array. The copy operations trace themselves so the growth of a
// vector<String> can be watched; move operations are noexcept, which lets
// vector use moves instead of copies during reallocation.

class String
{
public:
    String() : data(nullptr), length(0)
    {
    }

    explicit String(const char *text) : data(nullptr), length(std::strlen(text))
    {
        if (length != 0)
        {
            data = alloc.allocate(length + 1);
            std::uninitialized_copy(text, text + length, data);
            alloc.construct(data + length, '\0');
        }
    }

    String(const String &other) : data(nullptr), length(other.length)
    {
        if (length != 0)
        {
            data = alloc.allocate(length + 1);
            std::uninitialized_copy(other.data, other.data + length, data);
            alloc.construct(data + length, '\0');
        }
        std::cout << "copy constructor: " << c_str() << '\n';
    }

    String(String &&other) noexcept : data(other.data), length(other.length)
    {
        other.data = nullptr;
        other.length = 0;
        std::cout << "move constructor: " << c_str() << '\n';
    }

    String &operator=(const String &other)
    {
        auto new_data = alloc.allocate(other.length + 1);
        std::uninitialized_copy(other.data, other.data + other.length, new_data);
        alloc.construct(new_data + other.length, '\0');
        free();
        data = new_data;
        length = other.length;
        std::cout << "copy assignment: " << c_str() << '\n';
        return *this;
    }

    String &operator=(String &&other) noexcept
    {
        if (this != &other)
        {
            free();
            data = other.data;
            length = other.length;
            other.data = nullptr;
            other.length = 0;
        }
        std::cout << "move assignment: " << c_str() << '\n';
        return *this;
    }

    ~String()
    {
        free();
    }

    const char *c_str() const
    {
        return data == nullptr ? "" : data;
    }

    std::size_t size() const
    {
        return length;
    }

    // 14.26: read-only subscript; writing through it would invalidate the
    // class invariants, so only the const version exists.
    char operator[](std::size_t index) const
    {
        return data[index];
    }

private:
    std::allocator<char> alloc;

    void free()
    {
        if (data != nullptr)
        {
            // The block holds length characters plus the terminator.
            std::for_each(data, data + length + 1,
                          [this](char &character)
                          {
                              alloc.destroy(&character);
                          });
            alloc.deallocate(data, length + 1);
            data = nullptr;
            length = 0;
        }
    }

    char *data;
    std::size_t length;
};
#endif
