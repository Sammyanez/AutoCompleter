//
// Created by Sammy on 10/8/2021.
//

#include "autocompleter.h"
#include <iostream>
#include <utility>
void Autocompleter::left_rotate(Node *&p) {
Node* A = p;
Node* B = p->right;
Node* bl = B->left;

p=B;
B->left = A;
A->right = bl;

    update_height(A);
    update_height(B);

}

void Autocompleter::right_rotate(Node *&p) {
    Node* A = p;
    Node* B = p->left;
    Node* br = B->right;

    p=B;
    B->right = A;
    A->left = br;

    update_height(A);
    update_height(B);
}

void Autocompleter::insert_recurse(const Entry& e, Node *&p) {
    if(p == nullptr){
        p= new Node(e);
    }else{
        if(e.s < p->e.s){
            insert_recurse(e,p->left);
        }else{
            insert_recurse(e,p->right);
        }
        update_height(p);
        rebalance(p);
    }

}

void Autocompleter::rebalance(Node *&p) {
    if(height(p->right) - height(p->left) >= 2){
        if(height(p->right->right) > height(p->right->left)){
            left_rotate(p);
        }else{
            RLdouble(p);
        }
    }else if(height(p->left) - height(p->right) >= 2) {
        if (height(p->left->left) > height(p->left->right)) {
            right_rotate(p);
        } else {
            LRdouble(p);
        }
    }else {
        //do nothing please
    }

}

void Autocompleter::RLdouble(Node *& p) {
    right_rotate(p->right);
    left_rotate(p);

}

void Autocompleter::LRdouble(Node *& p) {
    left_rotate(p->left);
    right_rotate(p);

}

float Autocompleter::size_recurse(Node *p) {
    if (p == nullptr){
        return 0;
    }else{
        return (size_recurse(p->left) + 1 + size_recurse(p->right));
    }

}

void Autocompleter::insert(string x, float freq) {

auto *newEntry = new Entry;
newEntry->s = std::move(x);
newEntry->freq = freq;
insert_recurse(*newEntry,this->root);

}

float Autocompleter::height() {
    return this->root->height;
}

float Autocompleter::size() {
    return size_recurse(this->root);
}

void Autocompleter::completions(string x, vector<string> &T) {
    vector<Entry> Entries;
    completions_recurse(x,this->root, Entries);

}

void Autocompleter::completions_recurse(string x, Node *p, vector<Entry> &Entries) {
    if(p == nullptr){
        return;
    }
    string myString = p->e.s;
    int xLength = x.length();
    if(x > p->e.s && (myString.substr(0,xLength)) != x){
        return;
    }

    if(x < p->e.s){
        if(myString.substr(0,xLength) != x){
            completions_recurse(x,p->left,Entries);
        }else{
            Entries.push_back(p->e);
            cout << p->e.s<<endl;
            cout << p->e.freq<<endl;
            completions_recurse(x,p->left,Entries);
            completions_recurse(x,p->right,Entries);
        }
    }else{
        if(myString.substr(0,xLength) != x){
            completions_recurse(x,p->right,Entries);
        }else{
            Entries.push_back(p->e);
            cout << p->e.s<<endl;
            cout << p->e.freq<<endl;
            completions_recurse(x,p->left,Entries);
            completions_recurse(x,p->right,Entries);
        }
    }

}



float Autocompleter::max(float a, float b) {
    return (a > b) ? a : b;
}

Autocompleter::Autocompleter() = default;

