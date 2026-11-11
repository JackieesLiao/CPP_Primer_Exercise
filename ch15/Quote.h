#ifndef CH15_QUOTE_H
#define CH15_QUOTE_H

#include <iostream>
#include <memory>
#include <string>

// 15.3/15.5/15.7/15.11/15.15/15.16/15.26/15.27: the book pricing hierarchy.
// Quote is the interface; Disc_quote factors out quantity and discount;
// Bulk_quote and Limit_quote apply different rules; every class carries
// debug() and a clone() used by the Basket of exercise 15.30. The copy and
// move operations print traces for exercise 15.26.

class Quote
{
    friend std::ostream &operator<<(std::ostream &output, const Quote &quote);

public:
    Quote() : price(0.0)
    {
    }

    Quote(const std::string &book, double sales_price)
        : bookNo(book), price(sales_price)
    {
    }

    Quote(const Quote &other) : bookNo(other.bookNo), price(other.price)
    {
        std::cout << "Quote copy constructor\n";
    }

    Quote(Quote &&other) noexcept : bookNo(std::move(other.bookNo)),
                                    price(other.price)
    {
        std::cout << "Quote move constructor\n";
    }

    Quote &operator=(const Quote &other)
    {
        bookNo = other.bookNo;
        price = other.price;
        std::cout << "Quote copy assignment\n";
        return *this;
    }

    Quote &operator=(Quote &&other) noexcept
    {
        bookNo = std::move(other.bookNo);
        price = other.price;
        std::cout << "Quote move assignment\n";
        return *this;
    }

    virtual ~Quote()
    {
    }

    std::string isbn() const
    {
        return bookNo;
    }

    virtual double net_price(std::size_t count) const
    {
        return count * price;
    }

    virtual void debug() const
    {
        std::cout << "Quote: isbn " << bookNo << ", price " << price << '\n';
    }

    virtual Quote *clone() const &
    {
        return new Quote(*this);
    }

    virtual Quote *clone() &&
    {
        return new Quote(std::move(*this));
    }

private:
    std::string bookNo;
protected:
    double price;
};

inline double print_total(std::ostream &output, const Quote &item,
                          std::size_t count)
{
    const double total = item.net_price(count);
    output << "ISBN: " << item.isbn() << " # sold: " << count
           << " total due: " << total << '\n';
    return total;
}

// 15.23: passing Quote by value slices the object; net_price of the base
// runs no matter what dynamic type was passed.
inline double print_total_by_value(std::ostream &output, Quote item,
                                   std::size_t count)
{
    return print_total(output, item, count);
}

class Disc_quote : public Quote
{
public:
    Disc_quote() : quantity(0), discount(0.0)
    {
    }

    Disc_quote(const std::string &book, double price, std::size_t qty,
               double disc)
        : Quote(book, price), quantity(qty), discount(disc)
               {
               }

    double net_price(std::size_t count) const = 0;

    void debug() const
    {
        Quote::debug();
        std::cout << "Disc_quote: quantity " << quantity << ", discount "
                  << discount << '\n';
    }

protected:
    std::size_t quantity;
    double discount;
};

class Bulk_quote : public Disc_quote
{
public:
    Bulk_quote()
    {
    }

    Bulk_quote(const std::string &book, double price, std::size_t qty,
               double disc)
        : Disc_quote(book, price, qty, disc)
               {
               }

    double net_price(std::size_t count) const
    {
        if (count >= quantity)
        {
            return count * (1 - discount) * price;
        }
        return count * price;
    }

    void debug() const
    {
        Disc_quote::debug();
    }

    Bulk_quote *clone() const &
    {
        return new Bulk_quote(*this);
    }

    Bulk_quote *clone() &&
    {
        return new Bulk_quote(std::move(*this));
    }
};

// 15.7: at most quantity copies get the discount, the rest are full price.
class Limit_quote : public Disc_quote
{
public:
    Limit_quote(const std::string &book, double price, std::size_t qty,
                double disc)
        : Disc_quote(book, price, qty, disc)
                {
                }

    double net_price(std::size_t count) const
    {
        if (count <= quantity)
        {
            return count * (1 - discount) * price;
        }
        const std::size_t discounted = quantity;
        return discounted * (1 - discount) * price +
               (count - discounted) * price;
    }

    void debug() const
    {
        Disc_quote::debug();
    }

    Limit_quote *clone() const &
    {
        return new Limit_quote(*this);
    }

    Limit_quote *clone() &&
    {
        return new Limit_quote(std::move(*this));
    }
};

inline std::ostream &operator<<(std::ostream &output, const Quote &quote)
{
    output << "ISBN " << quote.isbn() << " net_price(10) "
           << quote.net_price(10);
    return output;
}
#endif
