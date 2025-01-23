//
//  AdjacencyListMatrix.h
//  tsp
//
//  Created by Aryan on 1/5/25.
//


#include <iostream>
#include <vector>

using namespace std;



struct link_list {
    int val;
    link_list *next;
};

class list_adj {
public:
    list_adj() {};
    list_adj(int N);
    void add_edg(int N, int M);
    void preorder(int start, std::vector<int>& res);
    bool is_branches(int n);
    int delete_branch(int n, const vector<vector<double>>& G);
    void Union(int n, const vector<vector<double>>& G);
    vector<int> findleaves(int root);
    ~list_adj();

private:
    void preorder_helper(int node, std::vector<int>& res);
    std::vector<link_list*> data;
};

list_adj::list_adj(int N) {
    for (int i = 0; i < N; ++i)
        data.push_back(NULL);
}

void list_adj::add_edg(int N, int M) {
    link_list* newnode = new link_list;
    newnode->val = M;
    newnode->next = NULL;

    if (data[N] == NULL) {
        data[N] = newnode;
    } else {
        link_list* curnNode = data[N];
        while (curnNode->next != NULL)
            curnNode = curnNode->next;
        curnNode->next = newnode;
    }
}

void list_adj::preorder_helper(int node, std::vector<int>& res) {
    res.push_back(node);
    
    link_list* curnNode = data[node];
    while (curnNode != NULL) {
        preorder_helper(curnNode->val, res);
        curnNode = curnNode->next;
    }
}

void list_adj::preorder(int start, std::vector<int>& res) {
    preorder_helper(start, res);
}



bool list_adj::is_branches(int n){
    link_list *curn;
    int countt=0;
    curn=data[n];
    while (curn != NULL) {
        curn=curn->next;
        countt++;
    }
    if(countt==1 || countt==0)
        return false;
    return true;
}



int list_adj::delete_branch(int n, const vector<vector<double>>& G){
    link_list *curn;
    curn=data[n];
    link_list *maxNode=curn;
    link_list *predNode=curn;
    link_list *deleter=curn->next;
    link_list *helper=NULL;
    double cost=G[n][curn->val];
    
    while (curn->next != NULL){
        curn=curn->next;
        if(G[n][curn->val]>cost){
            maxNode=curn;
            helper=predNode;
            deleter=curn->next;
            cost=G[n][curn->val];
        }
        predNode=curn;
    }
    
    helper->next=deleter;
    return maxNode->val;
    
}



vector<int> list_adj::findleaves(int root) {
    vector<int> leaves={root};
    vector<bool> visited(data.size(), false);
    vector<int> stack;

    stack.push_back(root);

    while (!stack.empty()) {
        int current = stack.back();
        stack.pop_back();

        if (visited[current]) continue;
        visited[current] = true;

        link_list* curnNode = data[current];
        if (curnNode == NULL) {
            leaves.push_back(current);
        } else {
            while (curnNode != NULL) {
                stack.push_back(curnNode->val);
                curnNode = curnNode->next;
            }
        }
    }

    return leaves;
}


void list_adj::Union(int n, const vector<vector<double>>& G){
    vector<int> leaves1;
    vector<int> leaves2;
    leaves1=findleaves(0);
    leaves2=findleaves(n);
    int leaf1=0;
    int leaf2=0;
    double minCost=(double)INFINITY;
    
    for(int i=0; i<leaves1.size(); ++i)
        for(int j=0; j<leaves2.size(); ++j)
            if(minCost>G[leaves1[i]][leaves2[j]]){
                minCost=G[leaves1[i]][leaves2[j]];
                leaf1=leaves1[i];
                leaf2=leaves2[j];
        }
    
    add_edg(leaf1, leaf2);
    
}

list_adj::~list_adj(){
    link_list *curNode=NULL;
    link_list *pred=NULL;
    for(int i=0; i<data.size(); ++i){
        curNode=data[i];
        if(curNode != NULL){
            while (curNode != NULL) {
                pred=curNode;
                curNode = curNode->next;
                delete pred;
            }
        }
    }
    
}









