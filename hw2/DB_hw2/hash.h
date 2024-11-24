#include <vector>
#include <string>

using namespace std;

class hash_entry {
public:
    int key;
    int value;
    hash_entry *next; // 以link list結構儲存資料
    hash_entry *pre;
    hash_entry(int key, int value);
};

class hash_bucket {
public:
    int local_depth; // 2進位時目前所數的bit
    int num_entries; // 當前所放的entry數量
    int hash_key; // 紀錄目前的hash index
    hash_entry* first; // 所指向的entry位址
    hash_bucket(int hash_key, int depth);

    void clear();
    // bool remove(int key);
    int query(int key);
    void query_all();
};

class hash_table {
public:
    int table_size; // 當前hash index的數量
    int bucket_size; // bucket可放entry最大上限
    int global_depth; // 2進位時目前所數到的值
    int num_local_glo_dpeth;
    vector<hash_bucket*> bucket_table; // 所擁有的bucket
    hash_table(int table_size, int bucket_size, int num_rows, vector<int> key, vector<int> value);

    void extend(hash_bucket *bucket);
    void half_table();
    void shrink(hash_bucket *bucket);
    void insert(int key, int value);
    void remove(int key);

    void key_query(vector<int> query_keys, string file_name);
    void remove_query(vector<int> query_remove_keys);

    void clear();
    void query_all();

};
