#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "unionfind.h"
#include "percolationstats.h"
#include "stopwatch.h"


StatsData::StatsData(double *data, int size)
{
	m_mean = 0;
	m_stddev = 0;
	m_confidenceHigh = 0;
	m_confidenceLow = 0;

	// Mean
	for (int i =0; i < size; i++)
		m_mean += data[i];
	m_mean = m_mean/double(size);

	// Deviation
	for (int i =0; i < size; i++) 
		m_stddev += (data[i] - m_mean)*(data[i] - m_mean);
	m_stddev = sqrt(m_stddev/double(size - 1));

	// Confedence interval
	m_confidenceLow = m_mean - 1.96*m_stddev/sqrt(double(size));
	m_confidenceHigh = m_mean + 1.96*m_stddev/sqrt(double(size));
}

StatsData::~StatsData()
{

}

double StatsData::mean()
{
	return m_mean;
}

double StatsData::stddev()
{
	return m_stddev;
}

void StatsData::confidence(double & low, double & high)
{
	low = m_confidenceLow;
	high = m_confidenceHigh;
}


PercolationStats::PercolationStats(int N, int T, IUnionFind *uf)
{
	m_percolation = new Percolation(N, uf);
	m_experimentsNumber = T;
	m_size = N;
	m_threshold = new double [m_experimentsNumber];
	m_time = new double [m_experimentsNumber];
}

double PercolationStats::experiment()
{
	srand(time(0));
	int opened_sites = 0;

	do {
		int i = rand() % m_size;
		int j = rand() % m_size;
		
		if (m_percolation->isOpen(i,j) == false) {
			m_percolation->open(i,j);
			opened_sites ++;
		} else
			continue;

	} while( m_percolation->percolates() == false );


	return ( double(opened_sites) / double (m_size * m_size) ); 
}


void PercolationStats::run()
{
	int i;
	// perform T independent computational experiments on an N-by-N grid
	StopWatch watch;
	for (int i = 0; i < m_experimentsNumber; i++) {

		watch.start();
		m_threshold[i] = experiment();
		m_time[i] = watch.stop();
		m_percolation->reset();
	}
	// Stats
	m_timeStats = new StatsData(m_time, m_experimentsNumber);
	m_thresholdStats = new StatsData(m_threshold, m_experimentsNumber);
}



PercolationStats::~PercolationStats()
{
	delete m_percolation;
	delete [] m_time;
	delete [] m_threshold;
	delete m_timeStats;
	delete m_thresholdStats;
}

StatsData* PercolationStats::timeStats()
{
	return  m_timeStats;
}

StatsData* PercolationStats::thresholdStats()
{
	return m_thresholdStats;
}



