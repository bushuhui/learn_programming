#ifndef __PSIMULATION_H__
#define __PSIMULATION_H__

#include <QObject>
#include <QThread>
#include "pmap.h"
#include "pstate.h"

class Simulation : public QObject,public QThread
{
public:
    Simulation(State *state);

    void createSub(Simulation* m_simulation);
    State *show();
    State *lidarScan();
    State *pointMove(int x, int y);
    State *remake();
    RPath pathPlan();

protected:
    RMap *s_map;
    State *s_state;
    RPath s_path;
};
#endif
