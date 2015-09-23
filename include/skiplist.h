#ifndef SKIPLIST_H
#define SKIPLIST_H

//This simply exists as a space to clean up code...

#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <cstring>

using namespace std;

template<class T> inline
int compare(T &x, T &y) {
	if (x < y) return -1;
	if (y < x) return 1;
	return 0;
}

template<class T>
class skiplist
{
protected:
    T null;
    struct Node {
		T x;
		int height;     // length of next
		int *length;
		Node **next;
	};
	Node *sentinel;
	int h;
	int n;
    Node *newNode(T x, int h) {
		Node *u = new Node;
		u->x = x;
		u->height = h;
		u->length = new int[h+1];
		u->next = new Node*[h+1];
		return u;
	}
	void deleteNode(Node *u) {
		delete[] u->length;
		delete[] u->next;
		delete u;
	}

	Node* findPred(int i) {
		Node *u = sentinel;
		int r = h;
		int j = -1;   // the index of the current node in list 0
		while (r >= 0) {
			while (u->next[r] != NULL && j + u->length[r] < i) {
				j += u->length[r];
				u = u->next[r];
			}
			r--;
		}
		return u;
	}

	Node* findPredNode(T x) {
        Node *u = sentinel;
        int r = h;
        while (r >= 0) {
            while (u->next[r] != NULL
                   && compare(u->next[r]->x, x) < 0)
                u = u->next[r]; // go right in list r
            r--; // go down into list r-1
        }
        return u;
    }

    int findIndOf(T x) {
        Node *u = sentinel;
        int j = -1;
        int r = h;
        while (r >= 0) {
			while (u->next[r] != NULL && compare(u->next[r]->x, x) < 0) {
				j += u->length[r];
				u = u->next[r];
			}
			r--;
		}
		return j;
    }

	Node* add(int i, Node *w) {
		Node *u = sentinel;
		int k = w->height;
		int r = h;
		int j = -1; // index of u
		while (r >= 0) {
			while (u->next[r] != NULL && j + u->length[r] < i) {
				j += u->length[r];
				u = u->next[r];
			}
			u->length[r]++; // to account for new node in list 0
			if (r <= k) {
				w->next[r] = u->next[r];
				u->next[r] = w;
				w->length[r] = u->length[r] - (i - j);
				u->length[r] = i - j;
			}
			r--;
		}
		n++;
		return u;
	}

	T removeT(T x) {
		T t = null;
		Node *u = sentinel, *del;
		int r = h;
		int j = -1; // index of node u
		while (r >= 0) {
			while (u->next[r] != NULL && compare(u->next[r]->x, x) < 0) {
				j += u->length[r];
				u = u->next[r];
			}
			u->length[r]--; // for the node we are removing
			if (compare(u->next[r]->x, x) == 0 && u->next[r] != NULL) {
				t = u->next[r]->t;
				u->length[r] += u->next[r]->length[r];
				del = u->next[r];
				u->next[r] = u->next[r]->next[r];
				if (u == sentinel && u->next[r] == NULL)
					h--;
			}
			r--;
		}
		deleteNode(del);
		n--;
		return t;
	}

	T removeInd(int i) {
		T x = null;
		Node *u = sentinel, *del;
		int r = h;
		int j = -1; // index of node u
		while (r >= 0) {
			while (u->next[r] != NULL && j + u->length[r] < i) {
				j += u->length[r];
				u = u->next[r];
			}
			u->length[r]--; // for the node we are removing
			if (j + u->length[r] + 1 == i && u->next[r] != NULL) {
				x = u->next[r]->x;
				u->length[r] += u->next[r]->length[r];
				del = u->next[r];
				u->next[r] = u->next[r]->next[r];
				if (u == sentinel && u->next[r] == NULL)
					h--;
			}
			r--;
		}
		deleteNode(del);
		n--;
		return x;
	}

public:
	skiplist();
	virtual ~skiplist();


	T get(int i) {
	    Node *u = findPred(i);
		return u->next[0] == NULL ? null : u->next[0]->x;
	}

	void add(T x) {
		Node *w = newNode(x, pickHeight());
		if (w->height > h)
			h = w->height;
		add(findIndOf(x), w);
	}

	T remove(T x) {
		return removeT(x);
	}

	T find(T x) {
        Node *u = findPredNode(x);
        return u->next[0] == NULL ? null : u->next[0]->x;
    }

	int pickHeight() {
		int z = rand();
		int k = 0;
		int m = 1;
		while ((z & m) != 0) {
			k++;
			m <<= 1;
		}
		return k;
	}

	void clear() {
		Node *u = sentinel->next[0];
		while (u != NULL) {
			Node *n = u->next[0];
			deleteNode(u);
			u = n;
		}
		memset(sentinel->next, '\0', sizeof(Node*)*h);
		h = 0;
		n = 0;
	}

	int size() {
		return n;
	}

	bool empty() {
	    return n == 0;
	}

};

template<class T>
skiplist<T>::skiplist() {
	null = (T)NULL;
	n = 0;
	sentinel = newNode(null, sizeof(int)*8);
	memset(sentinel->next, '\0', sizeof(Node*)*sentinel->height);
	h = 0;
}

template<class T>
skiplist<T>::~skiplist() {
	clear();
	deleteNode(sentinel);
}
#endif // SKIPLIST_H
