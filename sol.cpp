#include<bits/stdc++.h>
using namespace std;
map<int,char>m;
char val_begin = 'A';

void assign(int begin, int end, char val){
    if(end<begin){
        return;
    }
     if(m.size()==0){
        if(val!=val_begin){
            m[begin]=val;
            m[end]=val_begin;
        }
     }
     else{
        map<int,char>::iterator it1 = m.lower_bound(begin);
        map<int,char>::iterator it2 = m.lower_bound(end);
        if(it1==it2){
            if(it2==m.end()){
                map<int,char>::iterator temp = it2;
                --temp;
                if(val!=(*temp).second){
                    m[begin] = val;
                    m[end] = (*temp).second;
                }
            }
            else if(it2==m.begin()){
                if(val!=val_begin){
                    char prev = (*m.begin()).second;
                    m[begin]=val;
                    if(val==(prev)){
                        m.erase(m.begin());
                    }
                }
            
            }
            else{
                map<int,char>::iterator temp = it2;
                --temp;
                if(val!=(*temp).second){
                    m[begin]=val;
                    if(end==(*it2).first){
                      if((*it2).second==val){
                        m.erase(it2);
                      }
                      else{
                        m[end] = (*temp).second;
                      }
                    }
                }
            }
        }
        else{
            if(it1!=m.end() && it2==m.end()){
                // cout<<"Executed"<<endl;
                char prev_val;
                if(it1==m.begin()){
                    prev_val=val_begin;
                }
                else{
                    map<int,char>::iterator temp = it1;
                    --temp;
                    prev_val = (*temp).second;
                    // cout<<prev_val<<endl;
                }
                if(prev_val==val){
                    map<int,char>::iterator temp = it1;
                    for(map<int,char>::iterator i=temp;i!=it2;i++){
                        m.erase(i);
                    }
                    map<int,char>::iterator x = it2;
                    --x;
                    char set_val = (*x).second;
                    m[end]=set_val;
                }
                else{
                    char set_val;
                    if((*it1).first==begin){
                        set_val=(*it1).second;
                    }
                    m[begin]=val;
                    map<int,char>::iterator temp = it1;
                    // cout<<(*it1).first<<endl;
                    if((*it1).first==begin) temp++;
                    map<int,char>::iterator x=it2;
                    
                    --x;
                    // cout<<(*x).first<<endl;
                    if((*it1).first!=begin)
                     set_val = (*x).second;
                    // cout<<set_val<<endl;
                //    cout<<(*(++temp)).first<<" "<<(*temp).second<<endl;
                //     for(map<int,char>::iterator i=temp;i!=it2;i++){
                //         m.erase(i);
                //     }
                for(auto &ele:m){
                    if(ele.first>=(*temp).first && ele.first<end){
                        cout<<1<<endl;
                        m.erase(ele.first);
                    }
                }
                    if(set_val!=val){
                        m[end] = set_val;
                    }
                }
            }


            if(it1!=m.end() && it2!=m.end()){
                char prev_val;
                if(it1==m.begin()){
                    prev_val=val_begin;
                }
                else{
                    map<int,char>::iterator temp = it1;
                    --temp;
                    prev_val = (*temp).second;
                }
                if(prev_val==val){
                    map<int,char>::iterator temp = it1;
                    if((*it1).first==begin) temp++;
                    for(map<int,char>::iterator i=temp;i!=it2;i++){
                        m.erase(i);
                    }
                    map<int,char>::iterator x = it2;
                    --x;
                    if(end = (*it2).first){
                        if(val==(*it2).second){
                            m.erase(it2);
                        }
                    }
                    else{
                        m[end] = (*x).second;
                    }
                }
                else{
                    char set_val;
                    if((*it1).first==begin){
                        set_val=(*it1).second;
                    }
                    m[begin] = val;
                    map<int,char>::iterator temp = it1;
                    if((*it1).first==begin) temp++;
                    map<int,char>::iterator x=it2;
                    --x;
                    if((*it1).first!=begin)
                    char set_val = (*x).second;
                    for(map<int,char>::iterator i=temp;i!=it2;i++){
                        m.erase(i);
                    }
                    if(end = (*it2).first){
                        if(val==(*it2).second){
                            m.erase(it2);
                        }
                    }
                    else{
                        m[end] = (*x).second;
                    }
                }
            }

        }

     }

}               
                

int main(){
    int t;
    cin>>t;
    while(t--){
        int begin,end;
        char val;
        cin>>begin>>end>>val;
        assign(begin,end, val);
    }
   
   for(auto &ele:m){
    cout<<ele.first<<" "<<ele.second<<endl;
   }
   return 0;
}
// 3 7 B
// 7 10 C
// 1 3 G
// 5 15 A
// 20 50 C