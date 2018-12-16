#ifndef AIRLINE_H
#define AIRLINE_H
#include <string>

using namespace std;

struct airline
{
    string airName;
    int airlineID;

    airline();
    airline(string airName, int id);
    airline(const airline &other);
    airline& operator=(const airline &other);
    ~airline();

    private:
    void copy(const airline &other);
};

#endif // AIRLINE_H
