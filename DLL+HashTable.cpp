class Node {
public:
    int key;
    int val;
    Node* prev;
    Node* next;

    Node(int key, int val) : key(key), val(val), prev(nullptr), next(nullptr) {}
};

class LRUCache {
    int CAP;
    std :: unordered_map<int, Node* > cache;
    Node* head;
    Node* tail;

    void insert(Node* node) {
        Node* prev = tail->prev;
        Node* next = tail;

        prev->next = node;
        node->prev = prev;

        next->prev = node;
        node->next = next;
    }

    void remove(Node* node) {
        Node* prev = node->prev;
        Node* next = node->next;
        prev->next = next;
        next->prev = prev;
    }

public:
    LRUCache(int capacity) {
        CAP = capacity;
        try {
            head = new Node(0, 0);
            tail = new Node(0, 0);
        } catch (const std :: bad_alloc& e) {
            std :: cerr << "Memory allocation failed: " << e.what() << std :: endl;
            if ( head ) delete head;
            if ( tail ) delete tail;
            throw;
        }
        head->next = tail;
        tail->prev = head;
    }
    
    int get(int key) {
        if ( cache.find( key ) != cache.end() ) {
            Node* node = cache[key];
            remove( node );
            insert( node );
            return node->val;
        }
        return -1;
    }
    
    void put(int key, int value) {
        if ( cache.find( key ) != cache.end() ) {
            Node* delNode = cache[key];
            remove( delNode );
            cache.erase( key );
            delete delNode;
        }
        Node* newNode = new Node(key, value);
        cache[key] = newNode;
        insert( newNode );

        if ( cache.size() > CAP ) {
            Node* lru = head->next;
            remove( lru );
            cache.erase( lru->key );
            delete lru;
        }
    }

    ~LRUCache() {

        cache.clear();

        Node* curr = head;
        while ( curr != nullptr ) {
            Node* next = curr->next;
            delete curr;
            curr = next;
        }
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
