#ifndef CH16_BLOB_H
#define CH16_BLOB_H

#include <initializer_list>
#include <memory>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

// 16.12/16.13/16.24/16.58: the Blob class template. Data lives behind a
// shared_ptr, copies share their vector; BlobPtr is a friend so it can
// walk the elements. The iterator-range constructor and the variadic
// emplace_back cover exercises 16.24 and 16.58.

template <typename T>
class BlobPtr;

template <typename T>
class Blob
{
    friend class BlobPtr<T>;

public:
    using value_type = T;

    Blob() : data(std::make_shared<std::vector<T>>())
    {
    }

    Blob(std::initializer_list<T> initializer)
        : data(std::make_shared<std::vector<T>>(initializer))
    {
    }

    template <typename It>
    Blob(It first, It last)
        : data(std::make_shared<std::vector<T>>(first, last))
    {
    }

    T &operator[](std::size_t index)
    {
        check(index, "subscript out of range");
        return (*data)[index];
    }

    const T &operator[](std::size_t index) const
    {
        check(index, "subscript out of range");
        return (*data)[index];
    }

    std::size_t size() const
    {
        return data->size();
    }

    bool empty() const
    {
        return data->empty();
    }

    void push_back(const T &value)
    {
        data->push_back(value);
    }

    void push_back(T &&value)
    {
        data->push_back(std::move(value));
    }

    template <typename... Args>
    void emplace_back(Args &&...args)
    {
        data->emplace_back(std::forward<Args>(args)...);
    }

    void pop_back()
    {
        check(0, "pop_back on empty Blob");
        data->pop_back();
    }

    T &front()
    {
        check(0, "front on empty Blob");
        return data->front();
    }

    T &back()
    {
        check(0, "back on empty Blob");
        return data->back();
    }

    const T &front() const
    {
        check(0, "front on empty Blob");
        return data->front();
    }

    const T &back() const
    {
        check(0, "back on empty Blob");
        return data->back();
    }

    BlobPtr<T> begin();
    BlobPtr<T> end();

private:
    std::shared_ptr<std::vector<T>> data;

    void check(std::size_t index, const std::string &message) const
    {
        if (index >= data->size())
        {
            throw std::out_of_range(message);
        }
    }
};

template <typename T>
class BlobPtr
{
public:
    BlobPtr() : current(0)
    {
    }

    BlobPtr(Blob<T> &blob, std::size_t position = 0)
        : data(blob.data), current(position)
    {
    }

    T &operator*() const
    {
        auto data_pointer = check(current, "dereference past end of BlobPtr");
        return (*data_pointer)[current];
    }

    BlobPtr &operator++()
    {
        // Advancing from the last element is allowed: it lands on the
        // past-the-end position used for loop termination.
        check(current, "increment past end of BlobPtr");
        ++current;
        return *this;
    }

    BlobPtr &operator--()
    {
        if (current == 0)
        {
            throw std::out_of_range("decrement before begin of BlobPtr");
        }
        --current;
        return *this;
    }

    bool operator!=(const BlobPtr &other) const
    {
        return data.lock() != other.data.lock() || current != other.current;
    }

private:
    std::shared_ptr<std::vector<T>>
    check(std::size_t position, const std::string &message) const
    {
        auto data_pointer = data.lock();
        if (!data_pointer)
        {
            throw std::runtime_error("unbound BlobPtr");
        }
        if (position >= data_pointer->size())
        {
            throw std::out_of_range(message);
        }
        return data_pointer;
    }

    std::weak_ptr<std::vector<T>> data;
    std::size_t current;
};

template <typename T>
inline BlobPtr<T> Blob<T>::begin()
{
    return BlobPtr<T>(*this);
}

template <typename T>
inline BlobPtr<T> Blob<T>::end()
{
    return BlobPtr<T>(*this, data->size());
}
#endif
