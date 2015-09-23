#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <list>
#include <vector>
#include <chrono>
#include <ctime>
#include <cmath>

#include "skiplist.h"
#include "btree_set.h"

const double PI = atan(1.0)*4;

skiplist<double>* slist = nullptr;
stx::btree_set<double>* bt = nullptr;

clock_t start;

double* primes;

const int trials = 128;
const int ptr = 1000000;

int quantity[] = {1000, 10000, 100000, 1000000, 10000000};

clock_t* data;

void printData();

double* testdata;

void test(int q = ptr);
void testQ();
void testAll();

void sl_add(int q = ptr);
void bt_add(int q = ptr);

void sl_radd(int q = ptr);
void bt_radd(int q = ptr);

void sl_iget(int q = ptr);
void bt_iget(int q = ptr);

void sl_riget(int q = ptr);
void bt_riget(int q = ptr);

void sl_kget(int q = ptr);
void bt_kget(int q = ptr);

void sl_rkget(int q = ptr);
void bt_rkget(int q = ptr);

void init() {
    data = new clock_t[trials];
    testdata = new double[quantity[4]];
    for (int n = 0; n < quantity[4]; n++) {
        testdata[n] = PI * n;
    }
    testQ();
}

void testQ() {
    for (int t = 0; t < 5; t++) {
        test(quantity[t]);
    }
}

void test(int q) {
    cout << q << endl;
    for (int i = 0; i < trials; i++) {
        cout << "Trial " << (i + 1) << endl;
        start = clock();

        //What do you want to test?
        //Test Method Here

        clock_t take = clock() - start;
        data[i] = take;
        cout << data[i];
    }
    cout << endl;
    printData();
}

void sl_add(int q) {
    slist = new skiplist<double>();
    for (int n = 0; n < q; n++) {
        slist->add(testdata[n]);
    }
}

void bt_add(int q) {
    bt = new stx::btree_set<double>();
    for (int n = 0; n < q; n++) {
        bt->insert(testdata[n]);
    }
}

void sl_radd(int q) {
    slist = new skiplist<double>();
    for (int n = 0; n < q; n++) {
        slist->add(testdata[(rand() % q)]);
    }
    delete slist;
}

void bt_radd(int q) {
    bt = new stx::btree_set<double>();
    for (int n = 0; n < q; n++) {
        bt->insert(testdata[(rand() % q)]);
    }
    delete bt;
}

void sl_iget(int q) {
    if (slist == nullptr) {
        slist = new skiplist<double>();
        sl_add(q);
        start = clock();
    }
    for (int n = 0; n < q; n++) {
        slist->get(n);
    }
}

void bt_iget(int q) {
    if (bt == nullptr) {
        bt = new stx::btree_set<double>();
        bt_add(q);
        start = clock();
    }
    for (int n = 0; n < q; n++) {
        bt->get(n);
    }
}

void sl_riget(int q) {
    if (slist == nullptr) {
        slist = new skiplist<double>();
        sl_add(q);
        start = clock();
    }
    for (int n = 0; n < q; n++) {
        slist->get((rand() % q));
    }
}

void bt_riget(int q) {
    if (bt == nullptr) {
        bt = new stx::btree_set<double>();
        bt_add(q);
        start = clock();
    }
    for (int n = 0; n < q; n++) {
        bt->get((rand() % q));
    }
}

void sl_kget(int q) {
    if (slist == nullptr) {
        slist = new skiplist<double>();
        sl_add(q);
        start = clock();
    }
    for (int n = 0; n < q; n++) {
        slist->find(testdata[n]);
    }
}

void bt_kget(int q) {
    if (bt == nullptr) {
        bt = new stx::btree_set<double>();
        bt_add(q);
        start = clock();
    }
    for (int n = 0; n < q; n++) {
        bt->find(testdata[n]);
    }
}

void sl_rkget(int q) {
    if (slist == nullptr) {
        slist = new skiplist<double>();
        sl_add(q);
        start = clock();
    }
    for (int n = 0; n < q; n++) {
        slist->find(testdata[(rand() % q)]);
    }
}

void bt_rkget(int q) {
    if (bt == nullptr) {
        bt = new stx::btree_set<double>();
        bt_add(q);
        start = clock();
    }
    for (int n = 0; n < q; n++) {
        bt->find(testdata[(rand() % q)]);
    }
}

void printData() {
    for (int i = 0; i < trials; i++) {
        if (i == trials - 1) {
            cout << data[i] << endl;
        } else {
            cout << data[i] << ", ";
        }
    }
}
