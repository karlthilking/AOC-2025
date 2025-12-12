#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <utility>
#include <queue>

std::vector<std::string> split(std::string&& s, char c) {
	std::vector<std::string> temp;
	while(true) {
		size_t end = s.find(c);
		if(end == std::string::npos) {
			temp.push_back(s);
			break;
		} else {
			temp.push_back(s.substr(0,end));
		}
		s = s.substr(end + 1);
	}
	return temp;
}

int part1(std::map<std::string,std::vector<std::string>>& adj) {
	int total = 0;
	std::queue<std::string> q({std::move(std::string("you"))});
	while(!q.empty()) {
		std::string u(std::move(q.front())); q.pop();
		if(u == "out") {
			total++; continue;
		}
		for(const auto& v: adj[u]) {
			q.push(v);
		}
	}
	return total;
}

std::vector<std::string> topsort(std::map<std::string,std::vector<std::string>>& adj) {
	std::map<std::string,int> indegree;
	for(const auto& [u, edges]: adj) {
		if(indegree.find(u) == indegree.end()) {
			indegree[u] = 0;
		}
		for(const auto& v: edges) {
			indegree[v]++;
		}
	}
	std::queue<std::string> q;
	for(const auto& [u,in]: indegree) {
		if(in == 0) {
			q.push(u);
		}
	}
	std::vector<std::string> topord;
	while(!q.empty()) {
		std::string u(std::move(q.front())); q.pop();
		topord.push_back(u);
		for(const auto& v: adj[u]) {
			if(v == "out") {
				continue;
			}
			indegree[v]--;
			if(indegree[v] == 0) {
				q.push(v);
			}
		}
	}
	topord.push_back(std::string("out"));
	return topord;
}

long long paths(std::map<std::string,std::vector<std::string>>& adj, std::vector<std::string>& topord, std::string&& src, std::string&& dst)
{
	std::map<std::string,long long> dp;
	dp[src] = 1;
	auto begin = std::find(topord.begin(), topord.end(), src); 
	auto end = std::find(topord.begin(), topord.end(), dst);
	for(auto it = begin; it < end; ++it) {
		std::string u(*it);
		for(const auto& v: adj[u]) {
			dp[v] += dp[u];
		}
	}
	return dp[dst];
}
long long part2(std::map<std::string,std::vector<std::string>>& adj) {
	std::vector<std::string> topord(std::move(topsort(adj)));

	auto fft_pos = std::find(topord.begin(), topord.end(), std::string("fft"));
	auto dac_pos = std::find(topord.begin(), topord.end(), std::string("dac"));

	std::string first("svr");
	std::string second = (dac_pos < fft_pos) ? "dac" : "fft";
	std::string third = (second == "dac") ? "fft" : "dac";
	std::string last("out");

	long long x = paths(adj,topord,std::forward<std::string>(first),std::forward<std::string>(second));
	long long y = paths(adj,topord,std::forward<std::string>(second),std::forward<std::string>(third));
	long long z = paths(adj,topord,std::forward<std::string>(third),std::forward<std::string>(last));
	return x * y * z;
}

int main() {
	std::fstream input("data/day11.txt");
	std::map<std::string,std::vector<std::string>> adj;
	std::string s;
	
	int i = 0;
	while(std::getline(input,s)) {
		std::vector<std::string> line(std::move(split(std::forward<std::string>(s),':')));
		std::string u(std::move(line[0]));
		std::vector<std::string> edges(std::move(split(std::forward<std::string>(line[1].substr(1)),' ')));
		adj[u] = edges;
	}
	
	std::cout << "Part 1: " << part1(adj) << "\n";
	std::cout << "Part 2: " << part2(adj) << "\n";
	return 0;
}
