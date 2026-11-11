#include <iostream>

#include "Message.h"

// 13.34-13.37: exercise the Message/Folder pair: save and remove, copying
// a message into new folders, assignment, copying a folder, swap and
// destruction all keep both sides consistent.

int main()
{
    Folder inbox;
    Folder archive;
    Message greeting("hello");
    Message farewell("goodbye");

    greeting.save(inbox);
    greeting.save(archive);
    farewell.save(inbox);
    std::cout << "after saves:\n";
    greeting.print();
    farewell.print();
    inbox.print();
    archive.print();

    Message copied(greeting);
    std::cout << "after copy:\n";
    copied.print();
    inbox.print();

    farewell = greeting;
    std::cout << "after assignment:\n";
    farewell.print();
    inbox.print();
    archive.print();

    Folder copied_folder(inbox);
    std::cout << "after folder copy:\n";
    copied_folder.print();

    greeting.remove(archive);
    std::cout << "after remove:\n";
    greeting.print();
    archive.print();
    return 0;
}
