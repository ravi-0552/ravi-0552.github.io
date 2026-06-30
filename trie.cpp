#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
class Node{
public:
    Node *children[26];
    bool isEnd;
    int freq;
    Node(){
        isEnd=false;
        freq=0;
        for(int i=0;i<26;i++)
            children[i]=NULL;
    }
};
struct Suggestion{
    string word;
    int freq;
};
class Trie{
public:
    Node *root;
    Trie(){
        root=new Node();
    }
    void insert(string word){
        Node *curr=root;
        for(char ch:word){
            int index=ch-'a';
            if(curr->children[index]==NULL){
                curr->children[index]=new Node();
            }
            curr=curr->children[index];
        }
        curr->isEnd=true;
    }
    bool search(string word){
        Node *curr=root;
        for(char ch:word){
            int index=ch-'a';
            if(curr->children[index]==NULL)
                return false;
            curr=curr->children[index];
        }
        return curr->isEnd;
    }
    bool startsWith(string prefix){
        Node *curr=root;
        for(char ch:prefix){
            int index=ch-'a';
            if(curr->children[index]==NULL)
                return false;
            curr=curr->children[index];
        }
        return true;
    }
    void increaseFrequency(string word){
        Node *curr=root;
        for(char ch:word){
            int index=ch-'a';
            if(curr->children[index]==NULL)
                return;
            curr=curr->children[index];
        }
        if(curr->isEnd)
            curr->freq++;
    }
    void dfs(Node *curr,string word,vector<Suggestion> &res){
        if(curr==NULL)
            return;
        if(curr->isEnd){
            res.push_back({word,curr->freq});
        }
        for(int i=0;i<26;i++){
            if(curr->children[i]!=NULL){
                dfs(curr->children[i],word+char('a'+i),res);
            }
        }
    }
    vector<Suggestion> autocomplete(string prefix){
        Node *curr=root;
        for(char ch:prefix){
            int index=ch-'a';
            if(curr->children[index]==NULL)
                return {};
            curr=curr->children[index];
        }
        vector<Suggestion> res;
        dfs(curr,prefix,res);
        sort(res.begin(),res.end(),[](Suggestion a,Suggestion b){
            if(a.freq==b.freq)
                return a.word<b.word;
            return a.freq>b.freq;
        });
        return res;
    }
    void wildcardDFS(Node *curr,string pattern,int pos,string word,vector<Suggestion> &res){
    if(curr==NULL)
        return;

    if(pos==pattern.length()){
        if(curr->isEnd)
            res.push_back({word,curr->freq});
        return;
    }

    if(pattern[pos]=='?'){
        for(int i=0;i<26;i++){
            if(curr->children[i]!=NULL){
                wildcardDFS(curr->children[i],pattern,pos+1,word+char('a'+i),res);
            }
        }
    }
    else{
        int index=pattern[pos]-'a';
        if(curr->children[index]!=NULL){
            wildcardDFS(curr->children[index],pattern,pos+1,word+pattern[pos],res);
        }
    }
}
vector<Suggestion> wildcardSearch(string pattern){
    vector<Suggestion> res;
    wildcardDFS(root,pattern,0,"",res);
    sort(res.begin(),res.end(),[](Suggestion a,Suggestion b){
            if(a.freq==b.freq)
                return a.word<b.word;
            return a.freq>b.freq;
        });
    return res;
}
};

int main(){
    Trie t;
    // Initial words
    t.insert("apple");
    t.insert("apps");
    t.insert("application");
    t.insert("bat");
    t.insert("bath");
    t.insert("ball");
    t.insert("banana");
    t.insert("bag");
    int choice;
    string input;
    do{
        cout<<"MENU\n";
        cout<<"1.Insert\n";
        cout<<"2.Search word\n";
        cout<<"3.Search with Prefix\n";
        cout<<"4.Wildcard Search\n";
        cout<<"5.Exit\n";
        cout<<"Enter your choice:";
        cin>>choice;
        switch(choice){
        case 1:{
            cout<<"Enter string:";
            cin>>input;
            t.insert(input);
            break;
        }
        case 2:{
            string search;
            cout<<"Enter string to search:";
            cin>>search;

            if(t.search(search))
                cout<<"Word Found"<<endl;
            else
                cout<<"Word Not Found"<<endl;

            break;
        }
        case 3:{
            string prefix;
            int n;
            do{
                cout<<"Enter prefix:";
                cin>>prefix;
                vector<Suggestion> res=t.autocomplete(prefix);
                if(res.empty()){
                    cout<<"No suggestions found"<<endl;
                }
                else{
                    cout<<"Suggestions:"<<endl;
                    for(int i=0;i<res.size();i++){
                        cout<<i+1<<". "<<res[i].word
                            <<" :: Frequency: "<<res[i].freq<<endl;
                    }
                    int choice;
                    cout<<"Select your choice: ";
                    cin>>choice;
                    if(choice>=1 && choice<=res.size()){
                        t.increaseFrequency(res[choice-1].word);
                    }
                }
                cout<<"Select n as 1 to continue: ";
                cin>>n;
            }while(n==1);
            break;
        }
        case 4:{
            string pattern;
            cout<<"Enter pattern (? for wildcard): ";
            cin>>pattern;
            vector<Suggestion> res=t.wildcardSearch(pattern);
            if(res.empty()){
                cout<<"No matching words found"<<endl;
            }
            else{
                cout<<"Matching words:"<<endl;
                for(int i=0;i<res.size();i++){
                    cout<<i+1<<". "<<res[i].word<<" :: Frequency: "<<res[i].freq<<endl;
                }
                int ch;
                cout<<"Select your choice:";
                cin>>ch;
                if(ch>=1&&ch<=res.size()){
                    t.increaseFrequency(res[ch-1].word);
                }
            }
            break;
        }
        case 5:{
            cout<<"Exiting the program\n";
            break;
        }
        default:{
            cout<<"INVALID"<<endl;
        }
        }
    }while(choice!=5);
   return 0;
}