const int mv = 5e5 + 5;
int mob[mv];
bool prime[mv];

void mobius() {
  memset(mob, 1, sizeof mob);
  memset(prime, true, sizeof prime);
	for(int i = 2; i < mv; i++) {
		if(!prime[i])
			continue;
		for(int j = i; j < mv; j += i) {
			if(j != i) prime[i] = false;
			mob[j] *= -1;
			if((j / i) % i == 0)
				mob[j] = 0;
		}
	}
}
