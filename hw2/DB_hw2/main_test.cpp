#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "utils.h"
#include <chrono>

#include "hash.h"


using namespace std;
/*
int main()
{

vector<int> key = {28};
vector<int> value = {1};
int num_rows = 1;

cout<<"init..."<<endl;
hash_table my_hash_table(1<<1, 3, num_rows, key, value);
my_hash_table.query_all();
cout<<"num_local_glo_dpeth: "<<my_hash_table.num_local_glo_dpeth<<endl;


vector<int> insert1_key = {124, 30, 12, 60};
vector<int> insert1_value = {2, 3, 0, 0};
int insert1_num_rows = 4;
cout<<"insert 1..."<<endl;
for(int i=0;i<insert1_num_rows;i++){
    my_hash_table.insert(insert1_key[i], insert1_value[i]);
}
my_hash_table.query_all();
cout<<"num_local_glo_dpeth: "<<my_hash_table.num_local_glo_dpeth<<endl;


vector<int> insert2_key = {62};
vector<int> insert2_value = {4};
int insert2_num_rows = 1;
cout<<"insert 2..."<<endl;
for(int i=0;i<insert2_num_rows;i++){
    my_hash_table.insert(insert2_key[i], insert2_value[i]);
}
my_hash_table.query_all();
cout<<"num_local_glo_dpeth: "<<my_hash_table.num_local_glo_dpeth<<endl;

vector<int> remove1_key = {12};
cout<<"remove 1..."<<endl;
my_hash_table.remove_query(remove1_key);
my_hash_table.query_all();
cout<<"num_local_glo_dpeth: "<<my_hash_table.num_local_glo_dpeth<<endl;

vector<int> remove2_key = {16, 4};
cout<<"remove 2..."<<endl;
my_hash_table.remove_query(remove2_key);
my_hash_table.query_all();
cout<<"num_local_glo_dpeth: "<<my_hash_table.num_local_glo_dpeth<<endl;

}*/

