import numpy as np
from collections import defaultdict

def part1(shapes, regions):
	total = 0
	for i, config in regions.items():
		for area, counts in config.items():
			space = 0
			for shape, count in enumerate(counts):
				sz = shapes[str(shape)]
				space += (sz * int(count))
			if space < area:
				total += 1
	return total

def main():
	shapes = defaultdict(lambda: 0)
	regions = defaultdict(lambda: 0)

	with open("data/day12.txt", "r") as f:
		lines = f.read().splitlines()
		i = 0
		while True:
			if "x" in lines[i]:
				break
			ix = lines[i][:-1]
			sz = 0
			shape = [[x for x in line] for line in lines[i+1:i+4]]
			for j in range(3):
				for k in range(3):
					if shape[j][k] == "#":
						sz += 1
			shapes[ix] = sz
			i += 5
		while i < len(lines):
			dim = lines[i].split(":")[0].split("x")
			area = int(dim[0]) * int(dim[1])
			counts = lines[i].split(":")[1].strip().split(" ")
			regions[i] = {area: counts}
			i += 1
	
	print(f"Part 1: {part1(shapes, regions)}")
if __name__ == "__main__":
	main()

