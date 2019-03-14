vector<int> prime;
bool notPrime[ms];

//O(nlogn)
for(int i = 2; i<ms; ++i){
    if(!notPrime[i]){
        prime.push_back(i);
        for(int j = 2*i; j < ms; j += i){
            notPrime[j] = true;
        }
    }
}
