vector<int> prime;
bool notPrime[ms];

//O(nlogn)
void sieve(){
    for(int i = 2; i<ms; ++i){
        if(!notPrime[i]){
            prime.push_back(i);
            for(int j = 2*i; j < ms; j += i){
                notPrime[j] = true;
            }
        }
    }
}

//O(nloglogn)
void sieve(){
	prime.push_back(2);
	for(int i = 4; i<ms; i += 2){
		notPrime[i] = true;
	}
	for(ll i = 3; i<ms; i += 2){
		if(!notPrime[i]){
			prime.push_back(i);
			for(ll j = i*i; j < ms; j += i+i){
				notPrime[j] = true;
			}
		}
	}
}

vector<int> fact(int x){
    vector<int> ans;
    int idx = 0, pf = prime[idx];
    while(pf * pf <= x){
        while(x%pf == 0){
			x /= pf;
			ans.push_back(pf);
		}
		pf = prime[++idx];
    }
	if(x != 1){
		ans.push_back(x);
	}
	return ans;
}
