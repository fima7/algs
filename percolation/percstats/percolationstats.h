#include "percolation.h"
#include "unionfind.h"

class StatsData
{
private:

	double m_mean;
	double m_stddev;
	double m_confidenceHigh;
	double m_confidenceLow;
public:
	StatsData(double *data, int size);
	virtual ~StatsData();
	double mean();
	double stddev();
	void confidence(double & low, double & high); // const
};



class PercolationStats
{
private:
	Percolation *m_percolation;
	int m_experimentsNumber;
	int m_size;
	StatsData *m_thresholdStats;
	StatsData *m_timeStats;
	double experiment();
	double *m_threshold;
	double *m_time;

public:
	PercolationStats(int N, int T, IUnionFind *uf);
	virtual ~PercolationStats();
	void run();
	StatsData *timeStats();
	StatsData *thresholdStats();

};
