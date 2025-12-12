from heapq import heappush, heappop
from collections import defaultdict

def part1(adj):
	q = []
	heappush(q, "you")
	paths = 0
	while q:
		u = heappop(q)
		if u == "out":
			paths += 1
			continue
		for v in adj[u]:
			heappush(q, v)
	return paths

def topsort(adj):
	indegree = defaultdict(lambda: 0)
	for u, edges in adj.items():
		for v in edges:
			indegree[v] += 1
	
	q = []
	for v in adj.keys():
		if indegree[v] == 0:
			heappush(q, v)
	
	topord = []
	while q:
		u = heappop(q)
		topord.append(u)
		for v in adj[u]:
			if v == "out":
				continue
			indegree[v] -= 1
			if indegree[v] == 0:
				heappush(q, v)
	
	topord.append("out")
	return topord

def paths(adj,topord,src,dst):
	dp = defaultdict(lambda: 0)
	dp[src] = 1; i = topord.index(src); j = topord.index(dst)
	
	for u in topord[i:j+1]:
		if dp[u] > 0:
			if u == "out":
				break
			for v in adj[u]:
				dp[v] += dp[u]
	
	return dp[dst]

def part2(adj):
	topord = topsort(adj)
	x = paths(adj,topord,"svr","fft")
	y = paths(adj,topord,"fft","dac")
	z = paths(adj,topord,"dac","out")
	return x*y*z

def main():
	adj = {}

	with open("data/day11.txt", "r") as f:
		lines = f.read().splitlines()
		for i, line in enumerate(lines):
			u = line.split(":")[0]
			edges = line.split(":")[1].split(" ")[1:]
			adj[u] = edges

	print(part1(adj))
	print(part2(adj))
if __name__ == "__main__":
	main()


