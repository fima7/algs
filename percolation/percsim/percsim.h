#ifndef PERCSIM_H
#define PERCSIM_H

#include "percwindow.h"
#include "percthread.h"

class PercSim
{
public:
    PercSim(UFType uf_type, int sim_size, int sim_count);
    virtual ~PercSim();
    void start();
    void pause();
    void stop();
private:
    PercThread *m_thread;
    PercWindow *m_window;
};

#endif // PERCSIM_H
