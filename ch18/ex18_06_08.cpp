#include <cstdio>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

// 18.6: each throw below selects the handler whose parameter best matches
// the thrown type. 18.8: a resource-owning guard releases the FILE* in its
// destructor, so no exception path can leak the handle.

class FileGuard
{
public:
    FileGuard(const char *path, const char *mode)
        : handle(std::fopen(path, mode))
    {
        if (handle == nullptr)
        {
            throw std::runtime_error("cannot open file");
        }
    }

    ~FileGuard()
    {
        if (handle != nullptr)
        {
            std::fclose(handle);
            std::cout << "file closed by guard\n";
        }
    }

    FileGuard(const FileGuard &) = delete;
    FileGuard &operator=(const FileGuard &) = delete;

    FILE *get() const
    {
        return handle;
    }

private:
    FILE *handle;
};

int main()
{
    try
    {
        throw std::overflow_error("number too big");
    }
    catch (const std::overflow_error &error)
    {
        std::cout << "caught overflow_error: " << error.what() << '\n';
    }

    try
    {
        throw std::underflow_error("number too small");
    }
    catch (const std::underflow_error &error)
    {
        std::cout << "caught underflow_error: " << error.what() << '\n';
    }

    try
    {
        throw "plain string literal";
    }
    catch (const char *message)
    {
        std::cout << "caught const char*: " << message << '\n';
    }

    try
    {
        FileGuard guard("never_opened_demo.tmp", "w");
        std::fputs("data", guard.get());
        throw std::runtime_error("aborting early");
    }
    catch (const std::runtime_error &error)
    {
        std::cout << "caught runtime_error: " << error.what() << '\n';
    }
    return 0;
}
