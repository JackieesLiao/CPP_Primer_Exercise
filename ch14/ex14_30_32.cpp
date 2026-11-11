#include <iostream>
#include <string>

#include "../ch12/StrBlob.h"

// 14.30: the const iterator supports * and ->. 14.31: StrBlobPtr does not
// strictly need operator-> because it dereferences to string& (a class
// type), but the symmetric form keeps the two iterators alike. 14.32 adds
// a wrapper whose arrow reaches the iterator's own operators.

class StrBlobPtrProxy
{
public:
    explicit StrBlobPtrProxy(StrBlobPtr pointer) : pointer(pointer)
    {
    }

    StrBlobPtr *operator->()
    {
        return &pointer;
    }

private:
    StrBlobPtr pointer;
};

int main()
{
    const StrBlob lines{"const front", "const back"};
    ConstStrBlobPtr it = lines.cbegin();
    std::cout << "*it: " << *it << ", it->size(): " << it->size() << '\n';

    StrBlob editable{"one", "two"};
    StrBlobPtrProxy proxy(editable.begin());
    std::cout << "proxy->deref(): " << proxy->deref() << '\n';
    return 0;
}
