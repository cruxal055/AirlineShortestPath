#ifndef AIRPORT_H
#define AIRPORT_H
#include <string>
#include <set>

using namespace std;

struct airport
{
    string name;
    int code;

    airport();
    airport(const string &name, int code);
    airport(const airport &other);
    airport &operator=(const airport &other);

    bool operator<(const airport& other) const;


    private:
        void copyOther(const airport &other);
};

#endif // AIRPORT_H
