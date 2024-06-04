#include <iostream>
#include <cstring>
#include <vector>
#include <bits/stdc++.h>

#define d 127

using namespace std;

void search_Karp(string T, string P, int q){
    int n = size(T);
    int m = size(P);
    int d_m = int(pow(d, m-1))%q;
    cout <<  d_m << endl;

    int hash_T = 0, hash_P = 0;
    vector<int> result;
    for(int i = 0; i < m; i++){
        hash_T = (d*hash_T + T[i])%q;
        hash_P = (d*hash_P + P[i])%q;
    }
    cout << hash_P << endl;

    for(int s = 0; s <= n - m; s++){
        int j;
        if (hash_T == hash_P){
            for (j = 0; j < m; j++){
                if (P[j] != T[s+j]) break;
            }
            if (j == m){
                result.push_back(s);
            }
        }
        if (s < n-m){
            hash_T = (d * (hash_T - T[s] * d_m) + T[s + m]) % q;
            if (hash_T < 0){
                hash_T = (hash_T + q);
            }
        }
    }
    cout << "search Karp:" << endl;
    for (int i = 0; i < result.size(); i++){
        cout << result[i] << " ";
    }
    cout << endl;
}

vector<int> prefix_function(string S){
    vector<int> pi(size(S));
    int k = 0;
    pi[0] = 0;
    for (int i = 1; i < size(S); i++){
        while(k>0 && S[k] != S[i]) k = pi[k-1];

        if (S[k] == S[i]){
            k = k + 1;
        }
        pi[i] = k;
    }
    return pi;
}

void knuth_morris_pratt(string T,string P){
    vector<int> pi = prefix_function(P);
    vector<int> res;
    int k = 0;
    for (int i = 0; i < size(T); i++){
        while(k>0 && P[k] != T[i]) k = pi[k-1];

        if (P[k] == T[i]){
            k = k + 1;
        }
        if (k == size(P)){
            res.push_back(i - size(P) + 1);
            k = pi[k-1];
        }
    }
    cout << "search Knuth:" << endl;
    for (int i = 0; i < res.size(); i++){
        cout << res[i] << " ";
    }
    cout << endl;
}

vector<int> getSuffix(string pattern){
    int m = size(pattern);
    vector<int> pref = prefix_function(pattern);
    reverse(pattern.begin(), pattern.end());
    vector<int> rpref = prefix_function(pattern);
    vector<int> table(m + 1);

    for (int i = 0; i < m + 1; i++){
        table[i] = m - pref.back();
    }
    for (int i = 0; i < m; i++){
        int ind = m - rpref[i];
        int shift = i - rpref[i] + 1;
        if (table[ind] > shift) table[ind] = shift;
    }
    return table;
}

map<char, int> getStopSymbol(string pattern){
    int m = pattern.size();
    map<char, int> stop;
    stop[pattern[m-1]] = m;
    for (int i = 0; i < m - 1; ++i) {
        stop[pattern[i]] = i;
    }
    return stop;
}

void boyer_moore(string T, string P){
    vector<int> suff = getSuffix(P);
    map<char,int> stop = getStopSymbol(P);
    vector<int> res;
    int delta_stop, delta_suff;

    for (int i = 0; i <= size(T) - size(P) + 1;){
        int j = size(P) - 1;
        while (j >= 0 && P[j] == T[i+j]) j = j - 1;
        if (j == -1){
            res.push_back(i);
            delta_stop = 1;
        }
        else{
            if (stop.find(T[i+j]) == stop.end()){
                delta_stop =  j - (-1);
            }
            else{
                delta_stop =  j - stop[T[i+j]];
            }
        }
        delta_suff = suff[j+1];
        i += max(delta_stop, delta_suff);
    }

    cout << "search Boyer:" << endl;
    for (int i = 0; i < res.size(); i++){
        cout << res[i] << " ";
    }
    cout << endl;
}

int main(){
    string txt = "Hello world!, Goodbye world!";
    //string txt = "qwabcqwabdbabertyuiop";
    string p = "world";
    //string p = "abdba";
    search_Karp(txt, p, 131);
    knuth_morris_pratt(txt, p);
    boyer_moore(txt, p);
    return 0;
}