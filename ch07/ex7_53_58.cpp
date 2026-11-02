#include <iostream>
#include <vector>

class Debug
{
  public:
    constexpr explicit Debug(bool enabled = false)
        : hardware_(enabled), io_(enabled), other_(enabled)
    {
    }

    constexpr Debug(bool hardware, bool io, bool other)
        : hardware_(hardware), io_(io), other_(other)
    {
    }

    constexpr bool any() const
    {
        return hardware_ || io_ || other_;
    }

    void set_io(bool value)
    {
        io_ = value;
    }

    void set_hardware(bool value)
    {
        hardware_ = value;
    }

    void set_other(bool value)
    {
        other_ = value;
    }

  private:
    bool hardware_;
    bool io_;
    bool other_;
};

class Account
{
  public:
    explicit Account(double balance) : balance_(balance)
    {
    }

    void accrue()
    {
        balance_ += balance_ * interest_rate_;
    }

    static void set_rate(double rate)
    {
        interest_rate_ = rate;
    }

    double balance() const
    {
        return balance_;
    }

  private:
    double balance_;
    static double interest_rate_;
};

double Account::interest_rate_ = 0.0;

class Example
{
  public:
    static double rate;
    static const int vec_size = 20;
    static std::vector<double> values;
};

double Example::rate = 6.5;
std::vector<double> Example::values(Example::vec_size);

int main()
{
    constexpr Debug debug(false, true, false);
    static_assert(debug.any(), "IO debugging should be enabled");
    Account::set_rate(0.1);
    Account account(100.0);
    account.accrue();
    std::cout << account.balance() << ' ' << Example::rate << ' ' << Example::values.size() << '\n';
    return 0;
}
