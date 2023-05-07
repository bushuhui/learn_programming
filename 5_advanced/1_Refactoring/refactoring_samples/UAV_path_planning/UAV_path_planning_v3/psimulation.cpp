#include "psimulation.h"

Simulation::Simulation(State *state)
{
    s_state = state;
}

void Simulation::createSub(Simulation* m_simulation)
{
    QThread *sub = new QThread; //创建QThread对象 // FIXME: it is better to create thread in Simulation class, here just call its functions
                                // Simulation can inherit from QThread, and define a thread function to make the code clear
    m_simulation->QThread::moveToThread(sub);       //将Simulatin对象移动到创建的子线程对象中
    sub->start();               //启动子线程
}

State *Simulation::show()
{
    s_state->runPath();
    s_state->runLidar(); //得到状态数据
    return s_state;
}

RPath Simulation::pathPlan()
{
    s_state->runPath();
    RPath pathres1, pathres2;
    pathres1 = s_state->getPath(); //初始未探测到障碍物的路径
    int n1 = pathres1.size();
    int index;
    for (int i = 1; i < pathres1.size(); i++)
    {
        index = i;
        s_state->setLoc(pathres1[i].x, pathres1[i].y);
        s_state->runLidar();
        s_state->runPath();
        pathres2 = s_state->getPath();
        int n2 = pathres2.size();
        if (pathres2[n2 - 2].x != pathres1[n1 - 2].x)
        {
            break; //探测到所有障碍物后的可行路径
        }
    }
    pathres1.erase(pathres1.begin() + index + 1, pathres1.end());
    for (int i = 0; i < pathres2.size(); i++)
    {
        pathres1.push_back(pathres2[i]);
    }
    s_path = pathres1;
    return s_path;
}

State *Simulation::lidarScan()
{
    s_state->runLidar();
    return s_state;
}

State *Simulation::pointMove(int x, int y)
{
    s_state->setLoc(x, y);
}

State *Simulation::remake()
{

    s_state->clear(); //清空数据，重新开始
    s_state->runPath();
    s_state->runLidar();
}
