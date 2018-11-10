#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>
using namespace std;

#include "Param.h"

void process(const string& filename) {
	ifstream in(filename);
	vector<double> raw;
	copy(istream_iterator<double>(in), istream_iterator<double>(), back_inserter(raw));
	vector<double> vals(raw.size());
	copy(begin(raw), begin(raw) + 3, begin(vals));
	transform(begin(raw) + 3, end(raw) - 3, begin(vals) + 3, [](double& val) {
		double *cur = &val;
		return cur[-3] +  2 * cur[-2] + 3 * cur[-1] + 3 * cur[0] 
			+ 3 * cur[1] + 2 * cur[2] + cur[3];
	});
	copy(end(raw) - 3, end(raw), end(vals) - 3);
	
}

int main(int argc, char *argv[]) {
	if (argc != 2) {
		cout << "Usage: main.exe *.ini" << endl;
		return 0;
	}
	Param *p = nullptr;
	try {
		p = new Param(argv[1]);
	}
	catch (runtime_error& e) {
		cout << e.what() << endl;
		return -1;
	}

#ifdef _WIN32
	system("dir *dat /B > list.txt");
	ifstream in("list.txt");
	for_each(istream_iterator<string>(in), istream_iterator<string>(), process);
	in.close();
	system("del list.txt");
#elif
	static_assert(false);
#endif	

}

