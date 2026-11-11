#include <iostream>
#include <memory>
#include <string>

// 16.28: our own reference-counted SharedPtr and move-only UniquePtr,
// built on the chapter-13 knowledge. The SharedPtr keeps the control count
// next to the pointer; the UniquePtr forbids copies and supports release
// and reset.

template <typename T>
class SharedPtr
{
public:
    explicit SharedPtr(T *initial = nullptr) : count(nullptr)
    {
        std::unique_ptr<T> owned(initial);
        if (initial != nullptr)
        {
            count = new std::size_t(1);
        }
        pointer = owned.release();
    }

    SharedPtr(const SharedPtr &other)
        : pointer(other.pointer), count(other.count)
    {
        if (count != nullptr)
        {
            ++*count;
        }
    }

    SharedPtr &operator=(const SharedPtr &other)
    {
        if (this != &other)
        {
            release();
            pointer = other.pointer;
            count = other.count;
            if (count != nullptr)
            {
                ++*count;
            }
        }
        return *this;
    }

    ~SharedPtr()
    {
        release();
    }

    T &operator*() const
    {
        return *pointer;
    }

    T *get() const
    {
        return pointer;
    }

    std::size_t use_count() const
    {
        return count == nullptr ? 0 : *count;
    }

private:
    void release()
    {
        if (count != nullptr && --*count == 0)
        {
            delete pointer;
            delete count;
        }
        pointer = nullptr;
        count = nullptr;
    }

    // The manually shared count requires external synchronization.
    T *pointer;
    std::size_t *count;
};

template <typename T>
class UniquePtr
{
public:
    explicit UniquePtr(T *initial = nullptr) : pointer(initial)
    {
    }

    UniquePtr(const UniquePtr &) = delete;
    UniquePtr &operator=(const UniquePtr &) = delete;

    UniquePtr(UniquePtr &&other) noexcept : pointer(other.pointer)
    {
        other.pointer = nullptr;
    }

    UniquePtr &operator=(UniquePtr &&other) noexcept
    {
        if (this != &other)
        {
            delete pointer;
            pointer = other.pointer;
            other.pointer = nullptr;
        }
        return *this;
    }

    ~UniquePtr()
    {
        delete pointer;
    }

    T &operator*() const
    {
        return *pointer;
    }

    T *get() const
    {
        return pointer;
    }

    T *release()
    {
        T *result = pointer;
        pointer = nullptr;
        return result;
    }

    void reset(T *next = nullptr)
    {
        delete pointer;
        pointer = next;
    }

private:
    T *pointer;
};

int main()
{
    SharedPtr<std::string> first(new std::string("shared"));
    SharedPtr<std::string> second(first);
    std::cout << "SharedPtr: " << *second << " with " << second.use_count()
              << " user(s)\n";

    UniquePtr<std::string> unique(new std::string("unique"));
    std::cout << "UniquePtr: " << *unique << '\n';
    UniquePtr<std::string> moved(std::move(unique));
    std::cout << "moved UniquePtr: " << *moved << ", old one is "
              << (unique.get() == nullptr ? "empty" : "not empty") << '\n';
    return 0;
}
