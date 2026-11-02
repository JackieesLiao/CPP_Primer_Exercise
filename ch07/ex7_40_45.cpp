#include <iostream>
#include <string>
#include <vector>

class Book
{
  public:
    Book() : Book("", "")
    {
    }

    explicit Book(const std::string &isbn) : Book(isbn, "")
    {
    }

    Book(const std::string &isbn, const std::string &title) : isbn_(isbn), title_(title)
    {
        std::cout << "Book initialized\n";
    }

    void print(std::ostream &output) const
    {
        output << isbn_ << ' ' << title_;
    }

  private:
    std::string isbn_;
    std::string title_;
};

class NoDefault
{
  public:
    explicit NoDefault(int value) : value_(value)
    {
    }

  private:
    int value_;
};

class C
{
  public:
    C() : member_(0)
    {
    }

  private:
    NoDefault member_;
};

int main()
{
    Book empty;
    Book with_isbn("123");
    Book complete("456", "Primer");
    complete.print(std::cout);
    std::cout << '\n';
    std::vector<C> values(10);
    std::cout << "C objects: " << values.size() << '\n';
    return 0;
}
