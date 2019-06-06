vector<PT> cutPolygon(vector<PT> Q, PT a, PT b){
    PT vec = normalize(rotateCW((b-a)));
    vector<PT> resp;
    for(int i=0; i<Q.size(); i++){
        int j = (i+1)%Q.size();
        double n1 = (Q[i]-a)*(vec);
        double n2 = (Q[j]-a)*(vec);
        if(n1>=-eps) resp.push_back(Q[i]);
        if((n1<-eps && n2>eps) || (n1>eps && n2<-eps)){
            resp.push_back(computeLineIntersection(a, b, Q[i], Q[j]));
        }
    }
    return resp;
}
