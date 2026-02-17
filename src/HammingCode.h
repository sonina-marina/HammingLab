#pragma once
#include <string>
#include <iostream>
#include <cmath>
#include <vector>

struct Answer {
    int k;
    int m;
    int n;
    std::vector<int> A;
    std::string combination;
};

struct Answer2 {
    std::vector<int> e;
    int s;
    int r;
    std::string n;
    std::string result;
};

class HammingCode {

    private:

        std::string s, newS;
        int k, m, n;

        bool is_pow_of_two(int num) {
            return (ceil(log2(num)) == floor(log2(num)));
        }

    public:
        
        Answer coding(std::string s) {

            Answer ans;
            newS = "";

            k = s.length();

            for (int i = 0; i < 6; i++) {
                if (std::pow(2, i) > k+i){
                    m = i;
                    break;
                }
            }
            n = k + m + 1;
            ans.k = k;
            ans.m = m;
            ans.n = n;

            int counter_s = 0;
            for (int i = 0; i < n; i++) {
                if (is_pow_of_two(i)) {
                    newS += "_";
                }
                else {
                    newS += s[counter_s];
                    counter_s++;
                }
            }
            
            std::vector<int> a(m + 1);

            for (int i = 1; i <= m; i++) {
                a[i] = 0;
                for (int j = 0; j < n; j++) {
                    if (j > std::pow(2, i - 1) && (j >> (i - 1)) % 2 == 1) {
                        a[i] ^= newS[j] - '0';
                    }
                }
                newS[std::pow(2, i-1)] = a[i] + '0';
            }

            a[0] = 0;
            for (int i = 1; i < n; i++) {
                a[0] ^= newS[i] - '0';
            }
            newS[0] = a[0] + '0';

            ans.A = a;
            ans.combination = newS;

            return ans;
            //здесь закончено составление C
        }


        Answer2 checking(std::string newS) {

            Answer2 ans;
            std::string s = newS, res = "";

            n = s.length();

            int m = 0;
            for (int i = 0; i < s.size(); i *= 2) {
                ++m;
                if (i == 0) {
                    ++i;
                }
            }
        
            k = n - m - 1;

            std::vector<int> E(m + 1);
            for (int i = 0; i <= m; i++) {
                E[i] = 0;
                for (int j = 0; j < n; j++) {
                    if ((j >> (i - 1)) % 2 || (i == 0)) {
                        E[i] ^= newS[j] - '0';
                    }
                }
            }

            int S = 0;
            for (int i = 1; i < E.size(); i++) {
                S += E[i] * std::pow(2, i-1);
            }

            std::string N;
            int R;

            if (S == 0 && E[0] == 0) {
                N = "";
                R = 0;
            }
            else if (S == 0 && E[0] == 1) {
                N = "";
                R = 2;
            }
            else if (S !=0 && E[0] == 0) {
               N = "";
               R = 2;
            }
            else {
                N = std::to_string(S);
                R = 1;
            }
            ans.e = E;
            ans.s = S;
            ans.n = N;
            ans.r = R;

            if (R == 1) {
                s[S] = s[S] == '0' ? '1' : '0'; 
            }

            for (int i = 0; i < s.size(); i++) {
                if (is_pow_of_two(i)) {
                    continue;
                }
                res += s[i];
            }
            ans.result = res;
            // for (int i = 0; i <= m; i++) {
            //     std::cout << "E[" << i << "] = " << E[i] << "\n";
            // }

            return ans;
        }
};