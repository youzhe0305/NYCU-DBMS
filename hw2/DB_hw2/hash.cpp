#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <cmath>
#include "hash.h"
#include <bitset>
#include "utils.h"

using namespace std;

hash_entry::hash_entry(int key, int value){
    this->key = key;
    this->value = value;
    this->next = nullptr;
    this->pre = nullptr;
}

// -------------------------------------------------------------------------------------------------------------------------------------------

hash_bucket::hash_bucket(int hash_key, int depth){
    this->local_depth = depth;
    this->num_entries = 0;
    this->hash_key = hash_key;
    this->first = nullptr;
}

/* Free the memory allocated to this->first
*/
void hash_bucket::clear(){
    hash_entry* to_del = nullptr;
    hash_entry* now = this->first;
    while(now != nullptr){
        to_del = now;
        now = now->next;
        delete to_del;
    }
    this->first = nullptr;
}

/*bool hash_bucket::remove(int key){
    hash_entry *now = this->first;
    hash_entry *next = nullptr;
    while(now != nullptr){
        next = now->next;
        if(now->key == key){
            if(now->pre != nullptr)
                now->pre->next = now->next;
            else // only when delete first
                this->first = now->next;

            if(now->next != nullptr)
                now->next->pre = now->pre;
            delete now;
            this->num_entries--;
            return true;
        }
        now = next;
    }
    return false;
}*/

int hash_bucket::query(int key){

    if(this->first == nullptr){
        return -1;
    }
    hash_entry* now = this->first;
    while(now != nullptr){
        if(now->key == key) return now->value;
        now = now->next;
    }
    return -1;
}

void hash_bucket::query_all(){
    hash_entry* now = this->first;
    while(now != nullptr){
        cout<<now->key<<" : "<<now->value<<endl;
        now = now->next;
    }
}

// -------------------------------------------------------------------------------------------------------------------------------------------

hash_table::hash_table(int table_size, int bucket_size, int num_rows, vector<int> key, vector<int> value){
    this->table_size = table_size;
    this->bucket_size = bucket_size;
    this->global_depth = 1;
    this->num_local_glo_dpeth = 2;
    for(int i=0;i<table_size;i++)
        bucket_table.push_back(new hash_bucket(i, 1));
    for(int i=0;i<num_rows;i++){
        this->insert(key[i], value[i]);
    }
}

/* When insert collide happened, it needs to do rehash and distribute the entries in the bucket.
** Furthermore, if the global depth equals to the local depth, you need to extend the table size.
*/
void hash_table::extend(hash_bucket *bucket){

    if(bucket->local_depth == this->global_depth){
        this->bucket_table.resize(table_size << 1);
        for(int i=table_size;i < (table_size << 1);i++){
            this->bucket_table[i] = this->bucket_table[i-table_size];
        }
        table_size *= 2;
        this->global_depth++;
        this->num_local_glo_dpeth = 0;
    }
    int new_bucket_idx = bucket->hash_key | (1 << bucket->local_depth);

    hash_bucket* new_bucket = new hash_bucket(new_bucket_idx, bucket->local_depth+1);
    this->bucket_table[new_bucket_idx] = new_bucket;
    // !!!
    const int step = 1 << new_bucket->local_depth;
    for(int i = new_bucket_idx;i < this->table_size;i += step){ // 1XXX, 10XXX, 11XXX, 100XXX
        this->bucket_table[i] = new_bucket; // repoint to nearest
    }

    bucket->local_depth++;
    if(bucket->local_depth == this->global_depth) this->num_local_glo_dpeth += 2;

    hash_entry *now = bucket->first;
    hash_entry *next = nullptr;
    bucket->first = nullptr;
    bucket->num_entries = 0;

    while(now != nullptr){
        next = now->next;
        now->next = nullptr;
        now->pre = nullptr;

        if( (now->key & ((1 << bucket->local_depth)-1) ) == new_bucket->hash_key){ // 1XXX
            hash_entry* add = now;
            if(new_bucket->first == nullptr){
                new_bucket->first = add;
                new_bucket->num_entries++;
            }
            else{
                hash_entry* bucket_now = new_bucket->first;
                while(bucket_now->next != nullptr) bucket_now = bucket_now->next;
                bucket_now->next = add;
                add->pre = bucket_now;
                new_bucket->num_entries++;
            }
        }
        else{ // 0XXX
            hash_entry* add = now;
            if(bucket->first == nullptr){
                bucket->first = add;
                bucket->num_entries++;
            }
            else{
                hash_entry* bucket_now = bucket->first;
                while(bucket_now->next != nullptr) bucket_now = bucket_now->next;
                bucket_now->next = add;
                add->pre = bucket_now;
                bucket->num_entries++;
            }
        }
        now = next;
    }
    if(bucket->num_entries > this->bucket_size) this->extend(bucket);
    if(new_bucket->num_entries > this->bucket_size) this->extend(new_bucket);
    return;
}

/* When construct hash_table you can call insert() in the for loop for each key-value pair.
*/
void hash_table::insert(int key, int value){

    int idx = key & ((1 << this->global_depth) - 1); // depth 3 -> 111
    hash_bucket *bucket = this->bucket_table[idx];

    hash_entry* add = new hash_entry(key, value);
    if(bucket->first == nullptr){
        bucket->first = add;
        bucket->num_entries++;
    }
    else{
        bool same_key = false;
        hash_entry* now = bucket->first;
        if(now->key == key){
            now->value = value;
            same_key = true;
        }
        else{
            while(now->next != nullptr) {
                if(now->next->key == key){
                    now->next->value = value;
                    same_key = true;
                    break;
                }
                now = now->next;
            }
        }

        if(!same_key){
            now->next = add;
            add->pre = now;
            bucket->num_entries++;
        }
    }

    if(this->bucket_table[idx]->num_entries > this->bucket_size) this->extend(bucket_table[idx]);
}

/* The function might be called when shrink happened.
** Check whether the table necessory need the current size of table, or half the size of table
*/
void hash_table::half_table(){

}

/* If a bucket with no entries, it need to check whether the pair hash index bucket
** is in the same local depth. If true, then merge the two bucket and reassign all the
** related hash index. Or, keep the bucket in the same local depth and wait until the bucket
** with pair hash index comes to the same local depth.
*/
void hash_table::shrink(hash_bucket *bucket){

    int idx = bucket->hash_key; // dep=3, 1XX or 0XX & 11 = XX
    int pair_bucket_idx = idx ^ (1 << (bucket->local_depth-1));
    hash_bucket *pair_bucket = this->bucket_table[pair_bucket_idx];

    if(pair_bucket->local_depth != bucket->local_depth) return;

    this->bucket_table[idx] = pair_bucket;
    if(pair_bucket->local_depth == this->global_depth)this->num_local_glo_dpeth -= 2;
    pair_bucket->local_depth--;
    pair_bucket->hash_key = min(idx, pair_bucket_idx); // leave the small one: 0XX < 1XX

    const int step = 1 << pair_bucket->local_depth;
    for (int i = idx; i < table_size; i += step) {
        this->bucket_table[i] = pair_bucket;
    }

    if(this->num_local_glo_dpeth == 0) {
        this->global_depth--;
        this->table_size /= 2;
        for(int i=0;i<this->table_size;i++)
            if(this->bucket_table[i]->local_depth == this->global_depth) this->num_local_glo_dpeth++;
    }
    delete bucket;

    if(pair_bucket->num_entries==0 && this->bucket_table[idx]->local_depth > 1) this->shrink(pair_bucket);
    else if (pair_bucket->local_depth > 1 && bucket_table[pair_bucket->hash_key ^ (1 << (pair_bucket->local_depth - 1))]->num_entries == 0)
        this->shrink(bucket_table[pair_bucket->hash_key ^ (1 << (pair_bucket->local_depth - 1))]);
}

/* When executing remove_query you can call remove() in the for loop for each key.
*/
void hash_table::remove(int key){
}

void hash_table::key_query(vector<int> query_keys, string file_name){
    ofstream file (file_name);
    if(file.is_open())
    {
        file<<this->global_depth<<'\n';
        for(int i=0;i<query_keys.size();i++){
            int key = query_keys[i];
            int idx = key & ((1 << this->global_depth) - 1);
            // cout<<idx<<endl;
            int val = this->bucket_table[idx]->query(key);
            file<<val<<","<<this->bucket_table[idx]->local_depth<<'\n';
        }
        file.close();
    }

}

void hash_table::remove_query(vector<int> query_keys){


    for(int i=0;i<query_keys.size();i++){
        int key = query_keys[i];
        int idx = key & ((1 << this->global_depth) - 1);
        // bool flag = this->bucket_table[idx]->remove(key);

        hash_bucket *bucket = this->bucket_table[idx];
        hash_entry *now = bucket->first;
        hash_entry *next = nullptr;
        while(now != nullptr){
            next = now->next;
            if(now->key == key){
                if(now->pre != nullptr)
                    now->pre->next = now->next;
                else // only when delete first
                    bucket->first = now->next;

                if(now->next != nullptr)
                    now->next->pre = now->pre;
                delete now;
                bucket->num_entries--;
                break;
            }
            now = next;
        }

        if(this->bucket_table[idx]->num_entries==0 && this->bucket_table[idx]->local_depth > 1) this->shrink(this->bucket_table[idx]);
    }

}

/* Free the memory that you have allocated in this program
*/
void hash_table::clear(){
    for(int i=0;i<this->table_size;i++)
        this->bucket_table[i]->clear();
}

void hash_table::query_all(){

    cout<<"global depth: "<<this->global_depth<<endl;
    for(int i=0;i < this->table_size;i++){
        cout<<"bucket "<<i<<": \n";
        cout<<"local depth"<<bucket_table[i]->local_depth<<endl;
        this->bucket_table[i]->query_all();
        cout<<endl;
    }

}
