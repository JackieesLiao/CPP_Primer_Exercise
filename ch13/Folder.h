#ifndef CH13_FOLDER_H
#define CH13_FOLDER_H

#include <set>

class Message;

// 13.36/13.37: a Folder keeps a set of pointers to the Messages that
// contain it. Copying, assigning or destroying a Folder updates every
// Message it holds so the two sides never disagree.

class Folder
{
    friend class Message;
    friend void swap(Message &, Message &);

public:
    Folder() = default;

    Folder(const Folder &other);
    Folder &operator=(const Folder &other);
    ~Folder();

    void add_msg(Message &message);
    void rem_msg(Message &message);
    void print() const;

private:
    std::set<Message *> messages;

    void replace_messages(std::set<Message *> next_messages);
    void remove_from_messages();
};
#endif
