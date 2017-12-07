# generates a file w/ every combination of parameters
# for each file generate a random string for their name
import string
import random
def generateName(N):
	return ''.join(random.choice(string.ascii_uppercase + string.digits) for _ in range(N))
params = ["name", "ep", "alpha", "n_m_k", "pieces"]
ep = [10, 10000, 1000000, 10000000]
alpha = [0.2, 0.5, 0.8, 0.9]
n_m_k = ["6 4 2", "9 7 2", " 24 10 4"]
pieces = ["tetris-piece-set-1.txt", "tetris-piece-set-3.txt"]

for i in xrange(0, len(ep)):
	for j in xrange(0, len(alpha)):
		for k in xrange(0, len(n_m_k)):
			for l in xrange(0, len(pieces)):
				if(l == 1 and k != 2):
					continue
				if(l == 0 and k == 2):
					continue
				print generateName(20),ep[i], alpha[j], n_m_k[k], pieces[l] 