#ifndef CH12_STR_BLOB_H
#define CH12_STR_BLOB_H

#include <initializer_list>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

class StrBlobPtr;
class ConstStrBlobPtr;

// 12.2: a string container that shares its elements. Copying a StrBlob
// copies the shared_ptr, so every copy sees the same vector; the check
// helper guards front, back and pop_back against empty containers.

class StrBlob
{
    friend class StrBlobPtr;
    friend class ConstStrBlobPtr;

public:
    using size_type = std::vector<std::string>::size_type;

    StrBlob() : data(std::make_shared<std::vector<std::string>>())
    {
    }
    StrBlob(std::initializer_list<std::string> initializer)
        : data(std::make_shared<std::vector<std::string>>(initializer))
    {
    }

    size_type size() const
    {
        return data->size();
    }

    bool empty() const
    {
        return data->empty();
    }

    void push_back(const std::string &value)
    {
        data->push_back(value);
    }

    void pop_back();

    const std::string &front() const;
    const std::string &back() const;

    StrBlobPtr begin();
    StrBlobPtr end();
    ConstStrBlobPtr cbegin() const;
    ConstStrBlobPtr cend() const;

    // 14.16/14.18: relational operators on the underlying vector.
    bool operator==(const StrBlob &other) const
    {
        return *data == *other.data;
    }

    bool operator!=(const StrBlob &other) const
    {
        return !(*this == other);
    }

    bool operator<(const StrBlob &other) const
    {
        return *data < *other.data;
    }

private:
    std::shared_ptr<std::vector<std::string>> data;

    void check(size_type position, const std::string &message) const;
};

inline void StrBlob::check(size_type position, const std::string &message) const
{
    if (position >= data->size())
    {
        throw std::out_of_range(message);
    }
}

inline void StrBlob::pop_back()
{
    check(0, "pop_back on empty StrBlob");
    data->pop_back();
}

inline const std::string &StrBlob::front() const
{
    check(0, "front on empty StrBlob");
    return data->front();
}

inline const std::string &StrBlob::back() const
{
    check(0, "back on empty StrBlob");
    return data->back();
}

// 12.19: an iterator over StrBlob. The weak_ptr keeps no reference count,
// so the container can still be destroyed while iterators exist; deref
// reports a dangling iterator instead of reading freed memory.

class StrBlobPtr
{
    friend bool operator!=(const StrBlobPtr &left, const StrBlobPtr &right);

public:
    StrBlobPtr() : current(0)
    {
    }

    explicit StrBlobPtr(StrBlob &blob, std::size_t position = 0)
        : data(blob.data), current(position)
    {
    }

    std::string &deref() const;
    StrBlobPtr &increment();

    // 14.26-14.30: iterator-style operators over the same checks.
    std::string &operator*() const
    {
        return deref();
    }

    std::string *operator->() const
    {
        return &this->operator*();
    }

    StrBlobPtr &operator++();
    StrBlobPtr &operator--();
    StrBlobPtr operator++(int);
    StrBlobPtr operator--(int);
    StrBlobPtr operator+(std::size_t offset) const;
    StrBlobPtr operator-(std::size_t offset) const;
    std::string &operator[](std::size_t index) const;

    // 14.16/14.18: two iterators are equal when they address the same
    // position in the same underlying vector; less-than orders by the
    // vector contents first and the position second.
    bool operator==(const StrBlobPtr &other) const
    {
        return data.lock() == other.data.lock() && current == other.current;
    }

    bool operator<(const StrBlobPtr &other) const
    {
        auto left_data = data.lock();
        auto right_data = other.data.lock();
        if (left_data == right_data)
        {
            return current < other.current;
        }
        if (!left_data || !right_data)
        {
            throw std::runtime_error("cannot compare a bound and an unbound StrBlobPtr");
        }
        if (*left_data != *right_data)
        {
            return *left_data < *right_data;
        }
        return current < other.current;
    }

private:
    std::shared_ptr<std::vector<std::string>> lock_data() const;
    std::shared_ptr<std::vector<std::string>>
    check(std::size_t position, const std::string &message) const;

    std::weak_ptr<std::vector<std::string>> data;
    std::size_t current;
};

inline std::shared_ptr<std::vector<std::string>> StrBlobPtr::lock_data() const
{
    auto data_pointer = data.lock();
    if (!data_pointer)
    {
        throw std::runtime_error("unbound StrBlobPtr");
    }
    return data_pointer;
}

inline std::shared_ptr<std::vector<std::string>>
StrBlobPtr::check(std::size_t position, const std::string &message) const
{
    auto data_pointer = lock_data();
    if (position >= data_pointer->size())
    {
        throw std::out_of_range(message);
    }
    return data_pointer;
}

inline std::string &StrBlobPtr::deref() const
{
    auto data_pointer = check(current, "dereference past end of StrBlobPtr");
    return (*data_pointer)[current];
}

inline StrBlobPtr &StrBlobPtr::increment()
{
    check(current, "increment past end of StrBlobPtr");
    ++current;
    return *this;
}

inline bool operator!=(const StrBlobPtr &left, const StrBlobPtr &right)
{
    return !(left == right);
}

inline StrBlobPtr &StrBlobPtr::operator++()
{
    // Advancing from the last element is allowed: it lands on the
    // past-the-end position used for loop termination.
    check(current, "increment past end of StrBlobPtr");
    ++current;
    return *this;
}

inline StrBlobPtr &StrBlobPtr::operator--()
{
    if (current == 0)
    {
        throw std::out_of_range("decrement before begin of StrBlobPtr");
    }
    --current;
    return *this;
}

inline StrBlobPtr StrBlobPtr::operator++(int)
{
    StrBlobPtr previous = *this;
    ++*this;
    return previous;
}

inline StrBlobPtr StrBlobPtr::operator--(int)
{
    StrBlobPtr previous = *this;
    --*this;
    return previous;
}

inline StrBlobPtr StrBlobPtr::operator+(std::size_t offset) const
{
    const auto size = lock_data()->size();
    if (current > size || offset > size - current)
    {
        throw std::out_of_range("advance past end of StrBlobPtr");
    }

    StrBlobPtr result = *this;
    result.current += offset;
    return result;
}

inline StrBlobPtr StrBlobPtr::operator-(std::size_t offset) const
{
    if (offset > current)
    {
        throw std::out_of_range("retreat before begin of StrBlobPtr");
    }
    StrBlobPtr result;
    result.data = data;
    result.current = current - offset;
    return result;
}

inline std::string &StrBlobPtr::operator[](std::size_t index) const
{
    return (*this + index).deref();
}

// 12.22: the read-only companion of StrBlobPtr. It accepts a const StrBlob
// and returns const references; the weak_ptr points at a const vector.

class ConstStrBlobPtr
{
    friend bool operator!=(const ConstStrBlobPtr &left, const ConstStrBlobPtr &right);

public:
    ConstStrBlobPtr() : current(0)
    {
    }

    explicit ConstStrBlobPtr(const StrBlob &blob, std::size_t position = 0)
        : data(blob.data), current(position)
    {
    }

    const std::string &deref() const;
    ConstStrBlobPtr &increment();

    // 14.30: read-only dereference for the const iterator.
    const std::string &operator*() const
    {
        return deref();
    }

    const std::string *operator->() const
    {
        return &this->operator*();
    }

private:
    std::shared_ptr<const std::vector<std::string>>
    check(std::size_t position, const std::string &message) const;

    std::weak_ptr<const std::vector<std::string>> data;
    std::size_t current;
};

inline std::shared_ptr<const std::vector<std::string>>
ConstStrBlobPtr::check(std::size_t position, const std::string &message) const
{
    auto data_pointer = data.lock();
    if (!data_pointer)
    {
        throw std::runtime_error("unbound ConstStrBlobPtr");
    }
    if (position >= data_pointer->size())
    {
        throw std::out_of_range(message);
    }
    return data_pointer;
}

inline const std::string &ConstStrBlobPtr::deref() const
{
    auto data_pointer = check(current, "dereference past end of ConstStrBlobPtr");
    return (*data_pointer)[current];
}

inline ConstStrBlobPtr &ConstStrBlobPtr::increment()
{
    check(current, "increment past end of ConstStrBlobPtr");
    ++current;
    return *this;
}

inline bool operator!=(const ConstStrBlobPtr &left, const ConstStrBlobPtr &right)
{
    return left.current != right.current;
}

// Defined here so both iterator classes are complete types when the
// StrBlob iterators are constructed.

inline StrBlobPtr StrBlob::begin()
{
    return StrBlobPtr(*this);
}

inline StrBlobPtr StrBlob::end()
{
    return StrBlobPtr(*this, data->size());
}

inline ConstStrBlobPtr StrBlob::cbegin() const
{
    return ConstStrBlobPtr(*this);
}

inline ConstStrBlobPtr StrBlob::cend() const
{
    return ConstStrBlobPtr(*this, data->size());
}
#endif
