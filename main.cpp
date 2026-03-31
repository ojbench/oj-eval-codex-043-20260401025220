#include <bits/stdc++.h>
using namespace std;

namespace LIST {

struct NODE {
    int data;
    NODE* next;
    NODE* prev;
};

static NODE* head = nullptr;
static NODE* tail = nullptr;
static int len = 0;

void Pre() {
    head = nullptr;
    tail = nullptr;
    len = 0;
}

// Move to node at index i (0-based). Assumes 0 <= i < len.
static NODE* move(int i) {
    if (i < 0 || i >= len) return nullptr;
    if (i <= len / 2) {
        NODE* cur = head;
        int idx = 0;
        while (idx < i && cur) {
            cur = cur->next;
            ++idx;
        }
        return cur;
    } else {
        NODE* cur = tail;
        int idx = len - 1;
        while (idx > i && cur) {
            cur = cur->prev;
            --idx;
        }
        return cur;
    }
}

void insert(int i, int x) {
    // insert so that new node ends up at position i
    // valid positions: 0..len
    NODE* node = new NODE{ x, nullptr, nullptr };
    if (len == 0) {
        // inserting into empty list, i must be 0
        head = tail = node;
    } else if (i == 0) {
        // insert at head
        node->next = head;
        head->prev = node;
        head = node;
    } else if (i == len) {
        // append at tail
        node->prev = tail;
        tail->next = node;
        tail = node;
    } else {
        // insert before node at position i
        NODE* p = move(i);
        // p must not be null here for valid i
        node->next = p;
        node->prev = p->prev;
        if (p->prev) p->prev->next = node;
        p->prev = node;
        if (i == 0) head = node; // defensive, though handled above
    }
    ++len;
}

void remove(int i) {
    if (len == 0) return; // defensive; input guarantees valid operations
    NODE* p = move(i);
    if (!p) return; // defensive
    if (p->prev) p->prev->next = p->next;
    else head = p->next;
    if (p->next) p->next->prev = p->prev;
    else tail = p->prev;
    delete p;
    --len;
}

int Get_length() {
    return len;
}

int Query(int i) {
    if (i < 0 || i >= len) return -1;
    NODE* p = move(i);
    if (!p) return -1;
    return p->data;
}

void Print() {
    if (len == 0) {
        cout << -1 << '\n';
        return;
    }
    NODE* cur = head;
    bool first = true;
    while (cur) {
        if (!first) cout << ' ';
        cout << cur->data;
        first = false;
        cur = cur->next;
    }
    cout << '\n';
}

void Clear() {
    NODE* cur = head;
    while (cur) {
        NODE* nxt = cur->next;
        delete cur;
        cur = nxt;
    }
    head = tail = nullptr;
    len = 0;
}

} // namespace LIST

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;
    int op, x, p, ans;
    LIST::Pre();
    for (int _ = 0; _ < n; ++_) {
        cin >> op;
        switch (op) {
            case 0:
                ans = LIST::Get_length();
                cout << ans << '\n';
                break;
            case 1:
                cin >> p >> x;
                LIST::insert(p, x);
                break;
            case 2:
                cin >> p;
                ans = LIST::Query(p);
                cout << ans << '\n';
                break;
            case 3:
                cin >> p;
                LIST::remove(p);
                break;
            case 4:
                LIST::Print();
                break;
        }
    }
    LIST::Clear();
    return 0;
}

