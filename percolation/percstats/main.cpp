#include <iostream>
#include <sstream>

#include "percolationstats.h"
#include "quickfind.h"
#include "quickunioncompressed.h"
#include "quickunion.h"
#include "unionfind.h"
#include "weightedquickunion.h"

using namespace std;

const string ufName[] = {"WeightedQuickUnionCompressed", 
			"QuickUnionCompressed", 
			"WeightedQuickUnion", 
			"QuickUnion",
			"QuickFind"};

	

#define UFALGS 5 

int main(int argc, char *argv[])
{
	if (argc < 3) {
		cout << "not enough parameters\n";
		return -1;
	}

	string sN(argv[1]);	
	string sT(argv[2]);
	
	stringstream ssN(sN);
	stringstream ssT(sT);

	int N;
	int T; 

	ssN >> N;
	if (!ssN) {
		cout << "wrong N\n";
		return -1;
	}

	ssT >> T;
	if (!ssT) {
		cout << "wrong T\n";
		return -1;
	}
		
	IUnionFind **uf = new IUnionFind* [5];


	//cout << "				Threshold 			Time \n";
	//cout << "UnionFind, T, size, mean, stddev, confidence interval, mean, stddev, confidence interval\n";
//	cout << "                    Time                                                Threshold\n";
	cout << "N,Size,";

	for (int i = 0; i < UFALGS; i++) {
		cout << ufName[i];
		if (i == (UFALGS-1))
			cout << "\n";
		else
			cout << ",";
	}
	
	
	for (int i = 2; i <= N; i*=2) {
		cout << i << ",";
		cout << i*i << ",";
		cerr << i << "\t"; 
		uf[0] = new WeightedQuickUnionCompressed(i*i+2);
		uf[1] = new QuickUnionCompressed(i*i+2);
		uf[2] = new WeightedQuickUnion(i*i+2);
		uf[3] = new QuickUnion(i*i+2);
		uf[4] = new QuickFind(i*i+2);

		for (int j = 0; j < UFALGS; j++) {
			PercolationStats percstats(i, T, uf[j]);
			percstats.run();
			StatsData* timeStats = percstats.timeStats();
			cout << timeStats->mean();
			StatsData* thresholdStats = percstats.thresholdStats();
			cerr << thresholdStats->mean();
			
			if (j == (UFALGS-1)) {
				cout << "\n";
				cerr << "\n";
			} else {
				cout << ",";
				cerr << "\t";
			}
		}

		for (int i = 0; i < 5; i++)
			delete uf[i];
	}

	
//	for (int i = 0; i < 2; i++) {
		/*
		for (int j = 0; j < N; j*=2) {

		PercolationStats percstats(N, T, uf[i]);
		percstats.run();

		StatsData* thresholdStats = percstats.thresholdStats();
		StatsData* timeStats = percstats.timeStats();
		double lowTime, highTime, lowThr, highThr;
		thresholdStats->confidence(lowThr, highThr);
		timeStats->confidence(lowTime, highTime);

		cout << ufName[i] << ", " << T << "," << N*N << ", " 
						<< thresholdStats->mean() << ", "
						<< thresholdStats->stddev() << ", " 
						<< "[" << lowThr << "-" << highThr << "], " 
						<< timeStats->mean() << ","
						<< timeStats->stddev() << ", " 
						<< "[" << lowTime << "-" << highTime << "] " 
						<< "\n";
		}
		*/

//	}
/*
	for (int i = 0; i < 5; i++)
		delete uf[i];
*/		
	delete [] uf;
	// cout << N;
	// cout << T;





}

