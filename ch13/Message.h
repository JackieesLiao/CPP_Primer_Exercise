#ifndef CH13_MESSAGE_H
#define CH13_MESSAGE_H

#include <iostream>
#include <set>
#include <string>

#include "Folder.h"

// 13.34/13.35/13.37: a Message belongs to any number of Folders. Saving
// and removing update both sides; copying, assigning or destroying a
// Message keeps every Folder's contents in step.

class Folder;

class Message
{
    friend class Folder;
    friend void swap(Message &left, Message &right);

public:
    explicit Message(const std::string &contents = "")
        : text(contents)
    {
    }

    Message(const Message &other);
    Message &operator=(const Message &other);
    ~Message();

    void save(Folder &folder);
    void remove(Folder &folder);
    void print() const;

private:
    std::string text;
    // Membership is non-owning. Each side removes its reverse links on destruction.
    std::set<Folder *> folders;

    void add_folder(Folder &folder)
    {
        folders.insert(&folder);
    }

    void rem_folder(Folder &folder)
    {
        folders.erase(&folder);
    }

    void link_new_folders(const std::set<Folder *> &next_folders);
    void undo_new_folder_links(const std::set<Folder *> &next_folders);
    void unlink_old_folders(const std::set<Folder *> &next_folders);
    void remove_from_folders();
};

inline void Message::link_new_folders(const std::set<Folder *> &next_folders)
{
    // Retain existing links until every new insertion has succeeded.
    try
    {
        for (Folder *folder : next_folders)
        {
            if (folders.count(folder) == 0)
            {
                folder->add_msg(*this);
            }
        }
    }
    catch (...)
    {
        undo_new_folder_links(next_folders);
        throw;
    }
}

inline void Message::undo_new_folder_links(const std::set<Folder *> &next_folders)
{
    for (Folder *folder : next_folders)
    {
        if (folders.count(folder) == 0)
        {
            folder->rem_msg(*this);
        }
    }
}

inline void Message::unlink_old_folders(const std::set<Folder *> &next_folders)
{
    for (Folder *folder : folders)
    {
        if (next_folders.count(folder) == 0)
        {
            folder->rem_msg(*this);
        }
    }
}

inline void Message::remove_from_folders()
{
    for (Folder *folder : folders)
    {
        folder->rem_msg(*this);
    }
}

inline Message::Message(const Message &other)
    : text(other.text)
{
    auto next_folders = other.folders;
    link_new_folders(next_folders);
    folders.swap(next_folders);
}

inline Message &Message::operator=(const Message &other)
{
    if (this != &other)
    {
        auto next_text = other.text;
        auto next_folders = other.folders;
        link_new_folders(next_folders);
        unlink_old_folders(next_folders);
        folders.swap(next_folders);
        text.swap(next_text);
    }
    return *this;
}

inline Message::~Message()
{
    remove_from_folders();
}

inline void Message::save(Folder &folder)
{
    auto inserted = folders.insert(&folder);
    if (!inserted.second)
    {
        return;
    }

    try
    {
        folder.add_msg(*this);
    }
    catch (...)
    {
        folders.erase(inserted.first);
        throw;
    }
}

inline void Message::remove(Folder &folder)
{
    folders.erase(&folder);
    folder.rem_msg(*this);
}

inline void Message::print() const
{
    std::cout << "Message \"" << text << "\" in " << folders.size()
              << " folder(s)\n";
}

inline void swap(Message &left, Message &right)
{
    if (&left == &right)
    {
        return;
    }

    left.link_new_folders(right.folders);
    try
    {
        right.link_new_folders(left.folders);
    }
    catch (...)
    {
        left.undo_new_folder_links(right.folders);
        throw;
    }

    left.unlink_old_folders(right.folders);
    right.unlink_old_folders(left.folders);
    left.text.swap(right.text);
    left.folders.swap(right.folders);
}

inline void Folder::add_msg(Message &message)
{
    messages.insert(&message);
}

inline void Folder::rem_msg(Message &message)
{
    messages.erase(&message);
}

inline void Folder::replace_messages(std::set<Message *> next_messages)
{
    try
    {
        for (Message *message : next_messages)
        {
            if (messages.count(message) == 0)
            {
                message->add_folder(*this);
            }
        }
    }
    catch (...)
    {
        for (Message *message : next_messages)
        {
            if (messages.count(message) == 0)
            {
                message->rem_folder(*this);
            }
        }
        throw;
    }

    for (Message *message : messages)
    {
        if (next_messages.count(message) == 0)
        {
            message->rem_folder(*this);
        }
    }
    messages.swap(next_messages);
}

inline void Folder::remove_from_messages()
{
    for (Message *message : messages)
    {
        message->rem_folder(*this);
    }
}

inline Folder::Folder(const Folder &other)
{
    replace_messages(other.messages);
}

inline Folder &Folder::operator=(const Folder &other)
{
    if (this != &other)
    {
        replace_messages(other.messages);
    }
    return *this;
}

inline Folder::~Folder()
{
    remove_from_messages();
}

inline void Folder::print() const
{
    std::cout << "Folder holds " << messages.size() << " message(s):";
    for (Message *message : messages)
    {
        std::cout << " \"" << message->text << '"';
    }
    std::cout << '\n';
}
#endif
