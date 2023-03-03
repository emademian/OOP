//
// Created by Ema Demian on 26.05.2022.
//

#ifndef LAB10_11_OBSERVER_H
#define LAB10_11_OBSERVER_H
#include <vector>
#include <algorithm>
using std::remove;


class Observer {
public:
    virtual void update() = 0;
};


class Observable {
private:
    std::vector<Observer*> observers;
public:

    void addObserver(Observer* observer)
    {
        observers.push_back(observer);
    }
    void removeObserver(Observer* this_observer)
    {
        observers.erase(remove(observers.begin(), observers.end(), this_observer), observers.end());
    }

    void notify() {
        for (auto observer : observers)
        {
            observer->update();
        }
    }

};

#endif //LAB10_11_OBSERVER_H
