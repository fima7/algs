#include <time.h>

class StopWatch
{
private:
	clock_t m_start;
	clock_t m_finish;
public:
	void start();
	double stop();
};
