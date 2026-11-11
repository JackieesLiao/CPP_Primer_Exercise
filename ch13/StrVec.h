#ifndef CH13_STR_VEC_H
#define CH13_STR_VEC_H

#include <algorithm>
#include <initializer_list>
#include <memory>
#include <string>
#include <utility>

// 13.39/13.40/13.43/13.49/13.55: the book's StrVec. Three pointers manage
// an array of strings allocated through an allocator; reallocation doubles
// the capacity and moves the elements. The allocator is a non-static
// member so the header stays self-contained; it carries no state.

class StrVec
{
public:
    StrVec() : elements(nullptr), first_free(nullptr), cap(nullptr)
    {
    }

    StrVec(std::initializer_list<std::string> initializer);

    StrVec(const StrVec &other);

    StrVec(StrVec &&other) noexcept
        : elements(other.elements), first_free(other.first_free), cap(other.cap)
    {
        other.elements = nullptr;
        other.first_free = nullptr;
        other.cap = nullptr;
    }

    StrVec &operator=(const StrVec &other);

    StrVec &operator=(StrVec &&other) noexcept;

    ~StrVec();

    void push_back(const std::string &value);

    void push_back(std::string &&value);

    std::size_t size() const
    {
        return elements == nullptr ? 0 : first_free - elements;
    }

    std::size_t capacity() const
    {
        return elements == nullptr ? 0 : cap - elements;
    }

    std::string *begin()
    {
        return elements;
    }

    std::string *end()
    {
        return first_free;
    }

    const std::string *begin() const
    {
        return elements;
    }

    const std::string *end() const
    {
        return first_free;
    }

    // 14.23/14.26: subscript and initializer-list assignment.
    std::string &operator[](std::size_t index)
    {
        return elements[index];
    }

    const std::string &operator[](std::size_t index) const
    {
        return elements[index];
    }

    StrVec &operator=(std::initializer_list<std::string> initializer);

private:
    using AllocatorTraits = std::allocator_traits<std::allocator<std::string>>;

    std::allocator<std::string> alloc;

    template <typename Value>
    void append(Value &&value);

    std::pair<std::string *, std::string *> alloc_n_copy(const std::string *begin,
                                                         const std::string *end);
    void free();

    std::string *elements;
    std::string *first_free;
    std::string *cap;
};

inline StrVec::StrVec(std::initializer_list<std::string> initializer)
    : elements(nullptr), first_free(nullptr), cap(nullptr)
{
    auto data = alloc_n_copy(initializer.begin(), initializer.end());
    elements = data.first;
    first_free = cap = data.second;
}

inline std::pair<std::string *, std::string *>
StrVec::alloc_n_copy(const std::string *begin, const std::string *end)
{
    if (begin == end)
    {
        return {nullptr, nullptr};
    }

    const auto count = end - begin;
    auto data = alloc.allocate(count);
    try
    {
        return {data, std::uninitialized_copy(begin, end, data)};
    }
    catch (...)
    {
        alloc.deallocate(data, count);
        throw;
    }
}

inline void StrVec::free()
{
    if (elements)
    {
        // 13.43: a for_each with a lambda replaces the explicit pointer
        // loop that destroyed each element.
        std::for_each(elements, first_free,
                      [this](std::string &value)
                      {
                          AllocatorTraits::destroy(alloc, &value);
                      });
        alloc.deallocate(elements, cap - elements);
    }
}

template <typename Value>
inline void StrVec::append(Value &&value)
{
    if (first_free != cap)
    {
        AllocatorTraits::construct(alloc, first_free, std::forward<Value>(value));
        ++first_free;
        return;
    }

    const std::size_t old_size = size();
    const std::size_t new_capacity = old_size == 0 ? 1 : 2 * old_size;
    auto new_data = alloc.allocate(new_capacity);
    try
    {
        // The argument may refer to an element in the old allocation.
        AllocatorTraits::construct(alloc, new_data + old_size, std::forward<Value>(value));
    }
    catch (...)
    {
        alloc.deallocate(new_data, new_capacity);
        throw;
    }

    for (std::size_t index = 0; index != old_size; ++index)
    {
        AllocatorTraits::construct(alloc, new_data + index, std::move(elements[index]));
    }

    free();
    elements = new_data;
    first_free = new_data + old_size + 1;
    cap = new_data + new_capacity;
}

inline void StrVec::push_back(const std::string &value)
{
    append(value);
}

inline void StrVec::push_back(std::string &&value)
{
    append(std::move(value));
}

inline StrVec &StrVec::operator=(std::initializer_list<std::string> initializer)
{
    auto data = alloc_n_copy(initializer.begin(), initializer.end());
    free();
    elements = data.first;
    first_free = cap = data.second;
    return *this;
}

inline StrVec::StrVec(const StrVec &other)
    : elements(nullptr), first_free(nullptr), cap(nullptr)
{
    auto data = alloc_n_copy(other.begin(), other.end());
    elements = data.first;
    first_free = cap = data.second;
}

inline StrVec &StrVec::operator=(const StrVec &other)
{
    auto data = alloc_n_copy(other.begin(), other.end());
    free();
    elements = data.first;
    first_free = cap = data.second;
    return *this;
}

inline StrVec &StrVec::operator=(StrVec &&other) noexcept
{
    if (this != &other)
    {
        free();
        elements = other.elements;
        first_free = other.first_free;
        cap = other.cap;
        other.elements = nullptr;
        other.first_free = nullptr;
        other.cap = nullptr;
    }
    return *this;
}

inline StrVec::~StrVec()
{
    free();
}
#endif
