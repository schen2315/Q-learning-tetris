# generates a file w/ every combination of parameters
# for each file generate a random string for their name
import string
import random
def generateName(N):
	return ''.join(random.choice(string.ascii_uppercase + string.digits) for _ in range(N))
params = ["name", "ep", "alpha", "n_m_k", "pieces"]
#ep = [10, 10000, 1000000, 100000000]
ep = [10000]
#alpha = [0.2, 0.5, 0.8, 0.9]
alpha = [0.9]
#n_m_k = ["6 4 2", "9 7 2"]
n_m_k = ["6 4 2"]
pieces = ["tetris-piece-set-1.txt"]

for i in xrange(0, len(ep)):
	for j in xrange(0, len(alpha)):
		for k in xrange(0, len(n_m_k)):
			for l in xrange(0, len(pieces)):
				print generateName(20),ep[i], alpha[j], n_m_k[k], pieces[l] 