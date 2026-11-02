#include <iostream>
#include <sstream>
#include <string>

class SalesData
{
  public:
    SalesData(const std::string &isbn, unsigned count, double price)
        : isbn_(isbn), count_(count), revenue_(count * price)
    {
        std::cout << "three-argument constructor\n";
    }

    SalesData() : SalesData("", 0, 0.0)
    {
        std::cout << "default constructor\n";
    }

    explicit SalesData(const std::string &isbn) : SalesData(isbn, 0, 0.0)
    {
        std::cout << "ISBN constructor\n";
    }

    explicit SalesData(std::istream &input) : SalesData()
    {
        double price = 0.0;
        if (input >> isbn_ >> count_ >> price)
        {
            revenue_ = count_ * price;
        }
        std::cout << "stream constructor\n";
    }

  private:
    std::string isbn_;
    unsigned count_;
    double revenue_;
};

int main()
{
    SalesData empty;
    SalesData book("A");
    SalesData sale("B", 2, 10.0);
    std::istringstream input("C 3 5");
    SalesData from_stream(input);
    if (!input)
    {
        std::cerr << "Invalid sales record.\n";
        return 1;
    }
    return 0;
}
