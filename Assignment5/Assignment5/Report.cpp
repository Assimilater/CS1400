#include "Report.h"
using namespace std;

// Formatting constant used in both report methods
const int LABEL_WIDTH = 15;

//---------------------------------------------------------------------------------+
// void BubbleSort                                                                 |
// Uses an enhanced bubble sort to order an array either ascending or descending   |
//---------------------------------------------------------------------------------+
void BubbleSort(double *vals, int *keys, int cnt, bool sort_Asc) {
	bool swap_Done = true, toSwap;
	for (int i = 0; i < cnt && swap_Done; i++) {
		swap_Done = false;
		for (int j = 0; j < cnt - (i + 1); j++) {

			toSwap = vals[j] > vals[j + 1] && sort_Asc;
			toSwap = (vals[j] < vals[j + 1] && !sort_Asc) || toSwap;
			toSwap = vals[j + 1] != -1 && toSwap;
			toSwap = (vals[j] == -1 && vals[j + 1] != -1) || toSwap;

			if (toSwap) {
				Swap(vals[j], vals[j + 1]);
				Swap(keys[j], keys[j + 1]);
				swap_Done = true;
			}
		}
	}
}

//---------------------------------------------------------------------------------+
// double median                                                                   |
// Simple method that returns the middle or the average of two that tie for middle |
//---------------------------------------------------------------------------------+
double median(const double *vals, int cnt) {
	int s_cnt = 0;
	for (int j = 0; j < cnt && vals[j] != -1; j++) {
		if (vals[j] != -1) {
			s_cnt++;
		}
	}
	if (s_cnt == 0) { return 0; }

	int i = s_cnt / 2;
	return (s_cnt % 2 != 0) ? vals[i] : (vals[i] + vals[i - 1]) / 2;
}

//---------------------------------------------------------------------------------+
// double mean                                                                     |
// Simple method that returns average of all elements in the array                 |
//---------------------------------------------------------------------------------+
double mean(const double *vals, int cnt) {
	int s_cnt = 0;
	double total = 0;
	for (int i = 0; i < cnt && vals[i] != -1; i++) {
		if (vals[i] != -1) {
			total += vals[i];
			s_cnt++;
		}
	}
	if (s_cnt != 0) {
		total /= s_cnt;
	}
	return total;
}

//---------------------------------------------------------------------------------+
// void report(Geometry**, int)                                                    |
// This overload of report generates a report of an array of Geometry              |
//---------------------------------------------------------------------------------+
void report(Geometry **objs, int cnt) {
	// Declare parallel arrays
	int *v_Index = new int[cnt],
		*a_Index = new int[cnt];
	double
		*vols = new double[cnt],
		*area = new double[cnt];

	// Initialize arrays to be copies of the data in objs
	for (int i = 0; i < cnt; i++) {
		v_Index[i] = i;
		a_Index[i] = i;
		vols[i] = objs[i] != NULL ? objs[i]->ComputeVolume() : -1;
		area[i] = objs[i] != NULL ? objs[i]->ComputeSurface() : -1;
	}

	// Sort volume ascending and area descending
	BubbleSort(vols, v_Index, cnt, true);
	BubbleSort(area, a_Index, cnt, false);

	// Report by volumes then by area
	cout << "Reporting Shapes in Order of Ascending Volume:" << endl;
	for (int i = 0; i < cnt; i++) {
		if (objs[v_Index[i]] != NULL) {
			report(objs[v_Index[i]]);
		}
	}
	system("pause");
	system("cls");

	cout << "Reporting Shapes in Order of Descending Area:" << endl;
	for (int i = 0; i < cnt; i++) {
		if (objs[a_Index[i]] != NULL) {
			report(objs[a_Index[i]]);
		}
	}
	system("pause");
	system("cls");

	// Report general statistics
	cout << left
		<< "----- General Statistics Report -----" << endl
		<< setw(LABEL_WIDTH) << "Mean Volume: " << mean(vols, cnt) << endl
		<< setw(LABEL_WIDTH) << "Median Volume: " << median(vols, cnt) << endl
		<< setw(LABEL_WIDTH) << "Mean Area: " << mean(area, cnt) << endl
		<< setw(LABEL_WIDTH) << "Median Area: " << median(area, cnt) << endl
		<< endl;

	delete[] v_Index;
	delete[] a_Index;
	delete[] vols;
	delete[] area;
}

//---------------------------------------------------------------------------------+
// void report(Geometry*)                                                          |
// This overload of report generates a report of a single Geometry object          |
//---------------------------------------------------------------------------------+
void report(const Geometry *obj) {
	cout << left
		<< "----- Geometry Report -----" << endl
		<< setw(LABEL_WIDTH) << "Type: " << obj->GetType() << endl
		<< setw(LABEL_WIDTH) << "Name: " << obj->GetName() << endl
		<< setw(LABEL_WIDTH) << "Volume: " << obj->ComputeVolume() << endl
		<< setw(LABEL_WIDTH) << "Surface Area: " << obj->ComputeSurface() << endl
		<< endl;
}
