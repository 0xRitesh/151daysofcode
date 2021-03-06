// An IT company is working on a large project. The project is broken into N modules and distributed to different teams. The amount of time (in months) required to complete each module is given in an array duration[ ] i.e. time needed to complete ith module is duration[i] months. 
// You are also given M dependencies such that for each i (1 ≤ i ≤ M)  dependencies[i][1]th module can be started after dependencies[i][0]th module is completed.
// As the project manager, compute the minimum time required to complete the project.
// Note: It is guaranteed that a module is not dependent on itself.

// Example 1:

// Input:
// N = 6, M = 6
// duration[] = {1, 2, 3, 1, 3, 2}
// dependencies:
// 5 2
// 5 0
// 4 0 
// 4 1
// 2 3
// 3 1
// Output: 
// 8
// Explanation: 
// graph
// The Graph of dependency forms this and 
// the project will be completed when Module 
// 1 is completed which takes 8 months.

#include <bits/stdc++.h>
using namespace std;
#define endl '\n'


 // } Driver Code Ends


int visited[100005];
int counted[100005];
int isstack[100005];

class Solution{
 public:
    // refer https://www.geeksforgeeks.org/detect-cycle-in-a-graph/
    // for cycle detection in directed graph
    bool checkCycle(int i, vector<vector<int>> &ve) {
        if (isstack[i] == 1) return true;
    
        // insert into stack
        isstack[i] = 1;
        for (auto it : ve[i]) {
            // if next node is visited
            if (visited[it] == 1) {
                // if the node is in stack then cycle is found
                if (isstack[it] == 1) return true;
                continue;
            }
            visited[it] = 1;
            if (checkCycle(it, ve)) return true;
        }
        // removing from stack
        isstack[i] = 0;
        return false;
    }
    /*
        i: current node
        ve: adjacency list of the graph
        duration: time to complete each module
    */
    int dfs(int i, vector<vector<int>> &ve, int duration[]) {
        // return the time to complete the project starting from the node i if it is
        // already calculated
        if (counted[i] != -1) return counted[i];
        int x = 0;
    
        for (auto it : ve[i]) x = max(x, dfs(it, ve, duration));
    
        // time to complete this module and maximum time to complete child modules
        counted[i] = x + duration[i];
        return counted[i];
    }
    
    int minTime(vector<pair<int, int>> &vp, int duration[], int n, int m) {
        // stores which modules are independent
        int independent[n + 5] = {0};
        // create a graph from the dependency vector
        vector<vector<int>> ve(n + 2);
        for (int i = 0; i < m; i++) {
            int x = vp[i].first;
            int y = vp[i].second;
            ve[x].push_back(y);
            independent[y]++;
        }
        memset(visited, -1, sizeof(visited));
        memset(counted, -1, sizeof(counted));
        memset(isstack, -1, sizeof(isstack));
    
        int flag = 0;
        for (int i = 0; i < n; i++)
            if (independent[i] == 0) flag = 1;
    
        // if there is no independent module then the project can't be completed
        if (flag == 0) return -1;
    
        for (int i = 0; i < n; i++) {
            if (independent[i] != 0) {
                continue;
            }
            visited[i] = 1;
            // check if cycle is exist then project can't be completed
            if (checkCycle(i, ve)) return -1;
        }
    
        // starting from any independent module find the maximum time to complete
        // the project
        int ans = 0;
        for (int i = 0; i < n; i++)
            if (independent[i] == 0) ans = max(ans, dfs(i, ve, duration));
    
        return ans;
    }
};


// { Driver Code Starts.

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n, m, x, y;
        cin >> n >> m;
        int duration[n + 5];
        vector<pair<int, int>> dependency;
        for (int i = 0; i < n; i++) cin >> duration[i];
        for (int i = 0; i < m; i++) {
            cin >> x >> y;
            dependency.push_back({x, y});
        }
        Solution obj;
        cout << obj.minTime(dependency, duration, n, m) << endl;
    }
    return 0;
}  // } Driver Code Ends