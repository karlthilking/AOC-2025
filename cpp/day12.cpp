#include <fstream>
#include <iostream>
#include <string>
#include <vector>

std::vector<std::string> split(std::string& s, char c) {
	std::vector<std::string> temp;
	if(s[0] == c) {
		s = s.substr(1);
	}
	while(true) {
		size_t end = s.find(c);
		if (end == std::string::npos) {
			temp.push_back(s);
			break;
		} else {
			temp.push_back(s.substr(0,end));
		}
		s = s.substr(end + 1);
	}
	return temp;
}

int get_area(std::string& s) {
	size_t delim = s.find('x');
	int x = std::stoi(s.substr(0, delim));
	int y = std::stoi(s.substr(delim + 1));
	return x * y;
}

int part1(std::vector<int>& shapes, std::vector<std::vector<int>>& regions) {
	int total = 0;
	for(const auto& region: regions) {
		int area = region[0];
		int used = 0;
		for(size_t j=0; j<region.size() - 1; ++j) {
			used += shapes[j] * region[j + 1];
		}
		if(used < area) {
			++total;
		}
	}
	return total;
}

int main() {
	std::fstream input("data/day12.txt");
	std::vector<int> shapes;
	std::vector<std::vector<int>> regions;
	std::string s;

	for(int i=0; i<6; ++i) {
		std::getline(input,s);
		int sz = 0;
		for(int j=0; j<3; ++j) {
			std::getline(input,s);
			for(int k=0; k<3; ++k) {
				if(s[k] == '#') {
					sz++;
				}
			}
		}
		shapes.push_back(sz);
		std::getline(input,s);
	}
	while(std::getline(input,s)) {
		std::vector<std::string> temp(std::move(split(s,':')));
		int area = get_area(temp[0]);
		std::vector<std::string> counts(std::move(split(temp[1],' ')));
		std::vector<int> region{area};
		for(size_t i=0; i<counts.size(); ++i) {
			region.push_back(std::move(std::stoi(counts[i])));
		}
		regions.push_back(std::move(region));
	}
	std::cout << "Part 1: " << part1(shapes,regions) << "\n";
}




