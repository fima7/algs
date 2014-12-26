#include "stopwatch.h"

void StopWatch::start()
{
	m_start = clock();
}

double StopWatch::stop()
{
	m_finish = clock();
	return ((double) (m_finish - m_start) / CLOCKS_PER_SEC);
}

