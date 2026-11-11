#ifndef CH15_BASKET_H
#define CH15_BASKET_H

#include <iostream>
#include <memory>
#include <set>
#include <string>

#include "Quote.h"

// 15.30: a Basket stores shared_ptr<Quote> so one book can appear many
// times without copying; add_item clones the argument through the virtual
// clone() so the dynamic type is preserved.

class Basket
{
public:
    Basket()
    {
    }

    void add_item(const Quote &sale)
    {
        items.insert(std::shared_ptr<Quote>(sale.clone()));
    }

    void add_item(Quote &&sale)
    {
        items.insert(std::shared_ptr<Quote>(std::move(sale).clone()));
    }

    std::size_t size() const
    {
        return items.size();
    }

    double total_receipt(std::ostream &output) const;

private:
    static bool compare(const std::shared_ptr<Quote> &left,
                        const std::shared_ptr<Quote> &right)
    {
        return left->isbn() < right->isbn();
    }

    std::multiset<std::shared_ptr<Quote>, bool (*)(const std::shared_ptr<Quote> &,
                                                   const std::shared_ptr<Quote> &)>
        items{compare};
};

inline double Basket::total_receipt(std::ostream &output) const
{
    double sum = 0.0;
    for (auto it = items.cbegin(); it != items.cend();
         it = items.upper_bound(*it))
    {
        sum += print_total(output, **it, items.count(*it));
    }
    output << "Total due: " << sum << '\n';
    return sum;
}
#endif
