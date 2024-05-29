#pragma once
#include <vector>
#include <algorithm>

using namespace std;

class Observer {
public:
    virtual void update() = 0;
};

class Observable {
private:
    vector<Observer*> observers;
protected:
    void notify();
public:
    void addObserver(Observer* observer);
    void removeObserver(Observer* observer);
};