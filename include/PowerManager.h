#ifndef POWERMANAGER_H
#define POWERMANAGER_H

#include <chrono>
#include <vector>
#include "Power.h"
using namespace std;

enum PowerType {HEART, TITAN, SLOW};

class PowerManager
{
public:
    PowerManager();
    void activatePower(PowerType type);
    void update(); // Call this function periodically to update the state of active powers

private:
    void activateHeartPower();
    void activateTitanPower();
    void activateSlowPower();

    vector<Power> activePowers;
    chrono::steady_clock::time_point slowTimerStart;
    bool slowPowerActive = false;
    int slowDuration = 5; // Duration of the slow power in seconds
};

#endif // POWERMANAGER_H
