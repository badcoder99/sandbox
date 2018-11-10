#pragm once
#include <bitset>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
using namespace std;

constexpr char COMMENT = '#';

class Param {
private:
	enum { VT, WH, PD, DR, BDR };
	void fail() {
		throw runtime_error("Invalid *.ini file");
	}
	void read(ifstream& in) {
		bitset<5> flag;
		flag.reset();
		string line;
		while (getline(in, line)) {
			if (line.empty() || line.front() == COMMENT) {
				continue;
			}
			auto pos = line.find_first_of('=');
			if (pos == string::npos || pos + 1 == line.length()) {
				fail();
			}
			string key = line.substr(0, pos);
			string valStr = line.substr(pos + 1);
			double val = 0.0;
			try {
				val = stod(valStr);
			}
			catch (invalid_argument&) {
				fail();
			}
			if (key == "vt") {
				if (flag.test(VT)) fail();
				flag.set(VT);
				vt = val;
			}
			else if (key == "width") {
				if (flag.test(WH)) fail();
				flag.set(WH);
				width = val;
			}	
			else if (key == "pulse_delta") {
				if (flag.test(PD)) fail();
				flag.set(PD);
				pulse_delta = val;
			}	
			else if (key == "drop_ratio") {
				if (flag.test(DR)) fail();
				flag.set(DR);
				drop_ratio = val;
			}	
			else if (key == "below_drop_ratio") {
				if (flag.test(BDR)) fail();
				flag.set(BDR);
				below_drop_ratio = val;
			}	
			else {
				fail();
			}
		}	
		if (!flag.all()) {
			fail();
		}
	}	

public:
	double vt, width, pulse_delta, drop_ratio, below_drop_ratio;
	Param(const string& filename) {
		ifstream in(filename);
		if (!in) {
			throw runtime_error("Unable to open *.ini file");
		}
		else {
			read(in);
		}
	}
};		
