#include <iostream>
#include <typeinfo>

#include "../ch15/Quote.h"

// 19.6/19.7/19.8: three ways to reach the derived type from a Quote&.
// 19.6 uses dynamic_cast on a pointer, 19.7 the reference form with
// bad_cast, 19.8 a typeid comparison that never needs a cast.

int main()
{
    Bulk_quote bulk("0-201-70353-X", 20.0, 5, 0.2);
    Quote &reference = bulk;

    // 19.6: pointer version, null on failure
    if (const Bulk_quote *pointer =
            dynamic_cast<const Bulk_quote *>(&reference))
    {
        std::cout << "19.6 dynamic_cast ok, price(10) = " << pointer->net_price(10)
                  << '\n';
    }

    // 19.7: reference version, throws bad_cast on failure
    try
    {
        const Bulk_quote &as_bulk = dynamic_cast<const Bulk_quote &>(reference);
        std::cout << "19.7 reference ok, price(5) = " << as_bulk.net_price(5)
                  << '\n';
    }
    catch (const std::bad_cast &error)
    {
        std::cout << "19.7 bad_cast: " << error.what() << '\n';
    }

    // 19.8: typeid comparison, no cast needed
    if (typeid(reference) == typeid(Bulk_quote))
    {
        std::cout << "19.8 typeid says Bulk_quote, price(2) = "
                  << reference.net_price(2) << '\n';
    }
    return 0;
}
