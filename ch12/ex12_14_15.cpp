#include <iostream>
#include <memory>
#include <string>

// 12.14: manage a connection with shared_ptr and a named cleanup function,
// so disconnect runs even when the block is left through an exception.
// 12.15: the same cleanup written as a lambda passed to the shared_ptr.

struct Connection
{
    std::string destination;
    bool open;
};

Connection connect(const std::string &destination)
{
    std::cout << "opening " << destination << '\n';
    Connection connection{destination, true};
    return connection;
}

void disconnect(Connection &connection)
{
    if (connection.open)
    {
        std::cout << "closing " << connection.destination << '\n';
        connection.open = false;
    }
}

void end_connection(Connection *connection)
{
    disconnect(*connection);
}

int main()
{
    Connection direct = connect("example.org");
    {
        std::shared_ptr<Connection> managed(&direct, end_connection);
        std::cout << "12.14 working with " << managed->destination << '\n';
    }

    Connection lambda_managed = connect("example.com");
    {
        std::shared_ptr<Connection> managed(
            &lambda_managed,
            [](Connection *connection)
            {
                disconnect(*connection);
            });
        std::cout << "12.15 working with " << managed->destination << '\n';
    }
    return 0;
}
