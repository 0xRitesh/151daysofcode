
// Given a range of numbers, print all palindromes in the given range. For example if the 
// given range is {10, 115}, then output should be {11, 22, 33, 44, 55, 66, 77, 88, 99, 101, 111}
// We can run a loop from min to max and check every number for palindrome. 
// If the number is a palindrome, we can simply print it. 

#include<bits/stdc++.h>
using namespace std;

void palinRange(int, int);
int createPalin(int, int);

int main(){
    int t, mi, ma;

    cin >> t;
    while(t--){
        cin >> mi >> ma;
        palinRange(mi, ma);
        cout << endl;
    }
    return 0;
}

void palinRange(int mi, int ma){
    string str = to_string(mi);
    int len = str.length() / 2 + str.length() % 2;
    str = str.substr(0, len);
    int s = stoi(str);
    for(int i = s; i < ma; i++){
        int temp = createPalin(i, 0);
        if(mi <= temp && temp <= ma){
            cout << temp << " ";
        }
        if(temp > ma)
            break;
    }
    for(int i = s; i < ma; i++){
        int temp = createPalin(i, 1);
        if(mi <= temp && temp <= ma){
            cout << temp << " ";
        }
        if(temp > ma)
            break;
    }
}

int createPalin(int num, int isOdd){
    int palin = num;

    if(isOdd)
        num /= 10;
    while(num){
        palin = palin * 10 + (num % 10);
        num /= 10;
    }
    return palin;
}