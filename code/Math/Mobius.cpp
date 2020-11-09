const int mv = 5e5 + 5;
int mob[mv];
bool prime[mv];

void mobius() {
	for(int i = 1; i < mv; ++i) mob[i] = 1, prime[i] = true;
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
