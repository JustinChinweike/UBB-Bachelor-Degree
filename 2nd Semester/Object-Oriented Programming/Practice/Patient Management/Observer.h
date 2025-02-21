#ifndef OBSERVER_H
#define OBSERVER_H

#include <vector>

class Observer {
public:
    virtual ~Observer() {}
    virtual void update() = 0;
};

class Subject {
public:
    void addObserver(Observer* observer) {
        observers.push_back(observer);
    }

    void notify() {
        for (Observer* observer : observers) {
            observer->update();
        }
    }

private:
    std::vector<Observer*> observers;
};

#endif // OBSERVER_H
