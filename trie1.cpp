#include<iostream>
using namespace std;
int main(){
    int choice;string input;
    do{
        cout<<"MENU\n";
        cout<<"1.Insert\n";
        cout<<"2.Search word\n";
        cout<<"3.Search with Prefix\n";
        cout<<"4.Exit\n";
        cout<<"Enter your choice:";
        cin>>choice;
        switch(choice){
            case 1:
            cout<<"Enter string:";
            cin>>input;
            t.insert(input);
            break;
            case 2:
            string search;
            cout<<"enter string to search:";
            cin>>search;
            t.search(search);
            break;
            case 3:
            string prefix;int n;
            do{
            cout<<"Enter prefix:";
            cin>>prefix;
            vector<Suggestion>res=t.autocomplete(prefix);
            if(res.empty()){
            cout<<"No suggestions found"<<endl;
            }
            else{
            cout<<"Suggestions:"<<endl;
            for(int i=0;i<res.size();i++){
cout<<i+1<<"."<<res[i].word<<":: frequency:"<<res[i].freq<<endl;
}
            int choice;
            cout<<"Select your choice: ";
            cin>>choice;
            if(choice>=1&&choice<=res.size()){
    t.increaseFrequency(res[choice-1].word);
}
            }
            cout<<"select n as 1 to continue:";
            cin>>n;
            }while(n==1);
            break;
            case 4:
            cout<<"Exiting the program\n";
            return 0;
            break;
            default:
            cout<<"INVALID\n";
        }
    }while(choice!=4);
}