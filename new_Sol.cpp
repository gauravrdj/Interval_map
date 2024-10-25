#include<bits/stdc++.h>
using namespace std;
map<int,char>m;
char val_begin = 'A';
void assign(int start, int end, char val){
if(!(start<end)){
    return;
}

if(m.size()==0){
    if(val!=val_begin){
        m[start] = val;
        m[end] = val_begin;
    }
    return;
}

map<int,char>::iterator it_begin = m.lower_bound(start);
map<int,char>::iterator it_end = m.lower_bound(end);

char before_it_begin;
if(it_begin==m.begin()){
    before_it_begin = val_begin;
}
else{
    map<int,char>::iterator temp = it_begin;
    before_it_begin = (*--temp).second;
}

char after_it_end;
if(it_end==m.begin()){
    
    after_it_end = val_begin;
    
}
else{
if(it_end==m.end()){
    map<int,char>::iterator temp = m.end();
    after_it_end = (*--temp).second;
}
else{
    if((*it_end).first==end){
     after_it_end = (*it_end).second;
    }
    else{
        map<int,char>::iterator temp = it_end;
        after_it_end = (*--temp).second;
    }
}
}


m.erase(it_begin, it_end);

if(before_it_begin!=val){
    m[start]=val;
}

if(after_it_end==val){
    if(it_end!=m.end() && (*it_end).first==end){
        m.erase(it_end);
    }
}
else{
    
    m[end] = after_it_end;
}

}
char getValue(int key){
    if(m.find(key)!=m.end())return m[key];
    auto it = m.lower_bound(key);
    if(it==m.begin()){
        return val_begin;
    }
    else{
        return (*--it).second;
    }
}
int main(){
int t;
cin>>t;

for(int i=1;i<=t;i++){
    
    std::map<int, char> referenceMap;

    // Randomly generate startKey, endKey, and value
    int startKey = std::rand() % t;
    int endKey = startKey + std::rand() % 50;
    char value = static_cast<char>('A' + std::rand() % 26);

    // Perform the assignment in both the inter_map and referenceMap
    assign(startKey, endKey, value);
    for (int key = startKey; key < endKey; ++key) {
        referenceMap[key] = value;
    }

    // Compare the results of inter_map with the referenceMap
    // and print an error message if they differ
    for (const auto& entry : referenceMap) {
        int key = entry.first;
        char expectedValue = entry.second;
        char actualValue = getValue(key); // You may need a getValue() function in your inter_map class
        if (actualValue != expectedValue) {
            std::cout << "Test "<<i <<" failed: Key " << key << ", Expected " << expectedValue << ", Actual " << actualValue << std::endl;
        }
    }

    std::cout<<"Test Case "<<i<<" Passed"<<endl;

}
std::cout << "Randomized test completed." << std::endl;




}