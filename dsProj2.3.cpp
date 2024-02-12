#include <iostream> 
#include <string>
#include <sstream>
#include <vector>
#include <iomanip>
//#include <algorithm>
using namespace std;



struct Trie
{
    string maxName = "default";
    string minName = "default";
    Trie* children[26];
    bool isNew = true;
    //Person* person;
    bool isTheEnd;
    double balance;
    string name;
    Trie* gharz_ha = nullptr;

    Trie(double value){
        for (int i = 0; i < 26; i++)
        {
            children[i] = nullptr;
        }
        
        balance = value;
        isTheEnd = false;
    }

    int charToIndex(char c) {
            return c - 'a';
        }

        void gharz(const string name1, const string name2,string val) {
    
            double value = stod(val);
            Trie* p1 = search(name1);
            Trie* p2 = search(name2);
            if (p1->isNew)
            {
                p1->isNew = false;
                p1->gharz_ha = new Trie(0);
            }
            if (p2->isNew)
            {
                p2->isNew = false;
                p2->gharz_ha = new Trie(0);
            }
            p1->balance -= value;
            p2->balance += value;
            p1->gharz_ha->search(name2)->balance+=value;
            p2->gharz_ha->search(name1)->balance-=value;
           // cout<<"my val: "<<search("a")->gharz_ha->search("b")->balance<<endl;
        }

    Trie* search(string word) {
        Trie* current = this;
        for (char ch : word) {
            
            int index = charToIndex(ch);
            if (current->children[index] == nullptr) {
                current->children[index] = new Trie(0);
            }
            current = current->children[index];
        }
        current->isTheEnd = true;        
        current->name = word;
        return current;
    }

    void findMax2(){
        
         findMax(this);

         if (search(maxName)->balance == 0)
         {
            cout<<"-1"<<endl;
            return;
         }
         cout<<maxName<<endl;
    }

    double findMax(Trie* node){
        double maximum = node->balance;
        double t = maximum;
        string name = "default";
        for (int i = 25; i >= 0; i--)
            {   
                if (node->children[i]!=nullptr)
                    {
                    maximum = max(maximum, findMax(node->children[i]));
                    if (maximum==findMax(node->children[i])){
                        name=node->children[i]->name;
                        }
                    
                    }
            
        }
        maxName = name;
        return maximum;
        
        }

        void findMin2(){
        
         findMin(this);
         
         if (search(minName)->balance == 0)
         {
            cout<<"-1"<<endl;
            return;
         }
         
         cout<<minName<<endl;
        }

        double findMin(Trie* node){
        double minimum = node->balance;
        double t = minimum;
        string name = "default";
        for (int i = 25; i >= 0; i--)
            {   
                if (node->children[i]!=nullptr)
                    {
                    minimum = min(minimum, findMin(node->children[i]));
                    if (minimum==findMin(node->children[i]))
                    {
                        name=node->children[i]->name;
                    }
                    
                    }
            
        }
        minName = name;
        return minimum;
        
        }

        void bedehkariCounter(string name){
            Trie* trie = search(name);
            //cout<<trie->gharz_ha->balance<<endl;
            cout<<bedehkariCounter2(trie->gharz_ha)<<endl;
        }
        int bedehkariCounter2(Trie* node){
            
            int counter =0;
            for (int i = 0; i < 26; i++)
            {   
                if (node->children[i]!=nullptr){
                    if (node->children[i]->balance<0)
                    {
                        counter++;
                    }
                    counter+=bedehkariCounter2(children[i]);
                }
                
            }
            return counter;
            
        }

        void talabKariCounter(string name){
            Trie* trie = search(name);
            //cout<<trie->gharz_ha->balance<<endl;
            cout<<talabKariCounter2(trie->gharz_ha)<<endl;
        }
        
        int talabKariCounter2(Trie* node){
            
            int counter =0;
            for (int i = 0; i < 26; i++)
            {   
                if (node->children[i]!=nullptr){
                    if (node->children[i]->balance>0)
                    {
                        counter++;
                    }
                    counter+=bedehkariCounter2(children[i]);
                }
                
            }
            return counter;
            
        }

        void hesab(string name1,string name2){
            Trie* p2 = search(name2);
            double result = p2->gharz_ha->search(name1)->balance;
            //out<<result<<endl;
            cout << fixed << setprecision(2) << result << '\n';
            //printf("%.2lf\n",result);
        }
/*
        string findMaxPerson(){
            return findMaxPerson2(this,findMax2());
        }

        string findMaxPerson2(Trie* node , double maximum){
               
                if (node->balance == maximum)
                {
                    cout<<"max found."<<endl;
                    return node->name;
                }
                string s = "empty";
                for (int i = 25; i >=0; i--)
                {   
                    
                    if (node->children[i]!= nullptr){
                        cout<<"loop"<<endl;
                        s = findMaxPerson2(node->children[i],maximum);
                    }
                    else{
                        //cout << node->balance<<"-"<<maximum<<endl;
                    }
                }
                return s;
                
                
        }*/
    };


/*
 int main(){
    Trie people = Trie(0);
    people.gharz("a","b","200");
    people.gharz("a","b","100");
    people.gharz("c","b","100");
    people.gharz("h","z","100");
    people.hesab("a","b");
    cout<<"end"<<endl;
}*/



int main(){
    Trie people = Trie(0);
    int q;
    cin>>q;
    cin.ignore();

    for (int i = 0; i < q; i++)
    {
        //gets a line of command
        string line;
        getline(cin,line);
        stringstream ss(line);
        vector<string> arrayOfStrings;
        string tempString;
        while (ss >> tempString) {
        arrayOfStrings.push_back(tempString);
        }
    //proccess 

    switch (arrayOfStrings[0][0]){
        case '1':
            people.gharz(arrayOfStrings[1],arrayOfStrings[2],arrayOfStrings[3]);
            //cout<<"1 done!"<<endl;
            break;
        case '2':
            people.findMax2();
            //cout<<"2 done!"<<endl;
            break;
        case '3':
            people.findMin2();
            //cout<<"3 done!"<<endl;
            break;
        case '4':
            people.bedehkariCounter(arrayOfStrings[1]);
            //cout<<"4 done!"<<endl;
            break;
        case '5':
            people.talabKariCounter(arrayOfStrings[1]);
            //cout<<"5 done!"<<endl;
            break;
        case '6':
            people.hesab(arrayOfStrings[1],arrayOfStrings[2]);
            //cout<<"6 done!"<<endl;
            break;
        }
    }
    
}

