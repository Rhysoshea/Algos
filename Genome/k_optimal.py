# Uses python3
import sys

def isOptimized(k, reads):
	kmers = set()
	for read in reads:
		for i in range(0, len(read)-k+1):
			kmers.add(read[i:i+k])
	prefixes = set()
	suffixes = set()
	for kmer in kmers:
		prefixes.add(kmer[:-1])
		suffixes.add(kmer[1:])
	return prefixes == suffixes

reads = []
for i in range(400):
	read = sys.stdin.readline().strip()
	reads.append(read)
# print (reads[4])
for k in range(len(reads[2]), 1, -1):
	if isOptimized(k, reads):
		print(k)
		break
