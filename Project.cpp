#include<iostream>
#include<string.h>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <sstream>
#include <bits/stdc++.h>
#include <stdio.h>
using namespace std;


string pof;
string pof1;


static int preorder_idx = 1;

struct AVLNode{
    AVLNode *left;
    AVLNode *right;
    int height;
    string key;
    string mean;
    string pof_speech;
    int frequency;
}*root,*rootF;

struct FNode{
    AVLNode *ptr;
    FNode *next;
    FNode *previous;
    int frequency;
    string key;
    string mean;
}*head,*tail,*headF,*tailF;

vector<AVLNode*> tree_ptrs;
static bool check = false;

AVLNode* frenchCreate(AVLNode *node);
AVLNode* minNode(AVLNode *node);
AVLNode* createNode(string key,string mean,string pof_speech);
AVLNode* deleteNode(AVLNode *node, string key, bool &check);
AVLNode* insert(AVLNode *node, string key, string mean, string pof_speech);
AVLNode* rotateRight(AVLNode *node);
AVLNode* rotateLeft(AVLNode *node);

int compare(string key, string to_check);
int getHeight(AVLNode *node);
int calBalance(AVLNode *node);
int max(int a, int b);

void sortFrequency(AVLNode *node,AVLNode *root,FNode *&head,FNode *&tail);
void inOrderDisplay(AVLNode *node);
void createFNodeSpecific(int f , AVLNode *node,FNode *&head);
void preOrderDisplay(AVLNode *node);
void searchWord(AVLNode *node,string key);
void createFNode(int freq, AVLNode *node, FNode *&head, FNode *&tail);
void deleteFromSortedList(FNode *head,string key);
void createFNodeStart(int f, AVLNode *node, FNode *&head);
void display();
void displayPOF(AVLNode* Node);

void insertFile(string filename);
void createTree(vector<string> v_arr1, vector<string> v_arr2 );
void readFile(string filename);
bool checkTree(vector<string> prearray);
AVLNode* constructTree(vector<string> inorder, vector<string> preorder,int inorder_start,int inorder_end);




int main(){
    rootF = frenchCreate(root);
    insertFile("input words.txt");

    sortFrequency(rootF,rootF,headF,tailF);
    string key;
    int num;
    string choice;
    string choice2;
    int num_again;
    while(true){
        cout << "\n<------------------------------!!!!!!!!--------------------------------->\n"<< endl;
        cout << "Select one of the option!"<< endl;
        cout << "\n1.	View the English-French List"<< endl;
        cout << "\n2.	View the French-English List"<< endl;
        cout << "\n3.	View High Frequency English Words"<< endl;
        cout << "\n4.	View High Frequency French Words"<< endl;
        cout << "\n5.	Search the English List"<< endl;
        cout << "\n6.	Search the French List"<< endl;
        cout << "\n7.	Modify Lists"<< endl;
        cout << "\n8.	Create trees from given traversals"<< endl;
        cout << "\n9.	Quit"<< endl;
        cout << "\nYour Selection:	"<< endl;
        cin >> choice;
        stringstream convert(choice);
        convert >> num;
        convert.clear();
        cout << "\n<------------------------------!!!!!!!!--------------------------------->\n"<< endl;
        switch(num) {
            case 1: {
                cout<<"\n1.  View the list in alphabetical order"<<endl;
                cout<<"\n2.  View the list in descending order of frequency"<<endl;
                cout <<"\n3.  View the list by specific part of speech\n"<<endl;
                cin >> choice2;
                stringstream convert(choice2);
                convert >> num_again;
                convert.clear();
                switch(num_again){
                    case 1:
                        cout << setw(25)<< left << "Word:" << "\t" << setw(25)<< left<< "Meaning:" << "\t" << setw(25)<< left<< "Part of Speech:" << "\t" << setw(25)<< left<< "Frequency:"<< "\n"<< endl;
                        inOrderDisplay(root);
                        continue;
                    case 2:
                        preOrderDisplay(root);
                        display();
                        continue;
                    case 3:{

                        cout<<"Enter POF : ";
                        cin>>pof;
                        displayPOF(root);
                        continue;
                    }
                    default:
                        cout << "Wrong input!\n"<< endl;
                        continue;
                }
            }
            case 2: {
                cout<<"\n1.  View the list in alphabetical order"<<endl;
                cout<<"\n2.  View the list in descending order of frequency"<<endl;
                cout <<"\n3.  View the list by specific part of speech\n"<<endl;
                cin >> choice2;
                stringstream convert(choice2);
                convert >> num_again;
                convert.clear();
                switch(num_again){
                    case 1:
                        cout << setw(25)<< left << "Word:" << "\t" << setw(25)<< left<< "Meaning:" << "\t" << setw(25)<< left<< "Part of Speech:" << "\t" << setw(25)<< left<< "Frequency:"<< "\n"<< endl;
                        inOrderDisplay(rootF);
                        break;
                    case 2:
                        preOrderDisplay(rootF);
                        display();
                        break;
                    case 3:{
                        cout<<"Enter POF : ";
                        cin>>pof1;
                        displayPOF(rootF);

                        break;
                    }
                    default:
                        cout << "Wrong input!\n" << endl;
                        continue;
                }
                continue;
            }
            case 3:
                preOrderDisplay(root);
                cout << "\n" << endl;
                cout << setw(25)<< left << "Word:" << "\t" << setw(25)<< left<< "Meaning:" << "\t" << setw(25)<< left<< "Part of Speech:" << "\t" << setw(25)<< left<< "Frequency:"<< "\n"<< endl;
                cout << setw(25)<< left << tail->key << "\t" << setw(25)<< left<< tail->mean << "\t" << setw(25)<< left<< "Part of Speech:" << "\t" << setw(25)<< left<< tail->frequency<< "\n"<< endl;
                continue;
            case 4:
                preOrderDisplay(rootF);
                cout << "\n" << endl;
                cout << setw(25)<< left << "Word:" << "\t" << setw(25)<< left<< "Meaning:" << "\t" << setw(25)<< left<< "Part of Speech:" << "\t" << setw(25)<< left<< "Frequency:"<< "\n"<< endl;
                cout << setw(25)<< left << tail->key << "\t" << setw(25)<< left<< tail->mean << "\t" << setw(25)<< left<< "Part of Speech:" << "\t" << setw(25)<< left<< tail->frequency<< "\n"<< endl;
                continue;
            case 5:{
                cout << "\n" << endl;
                cout << "Enter key to search: " << endl;
                cin.sync();
                getline(cin,key);
                searchWord(root,key);
                continue;
            }
            case 6:
                cout << "\n" << endl;
                cout << "Enter key to search: " << endl;
                cin.sync();
                getline(cin,key);
                cout << key<<"\n";
                searchWord(rootF,key);
                continue;
            case 7:{
                cout << "\n"<< endl;
                string choice;
                int num;
                cout << "Which list you want to modify:"<< endl;
                cout << "\n1. English to French"<< endl;
                cout << "\n2. French to English"<< endl;
                cin >> choice;
                stringstream convert(choice);
                convert >> num;
                convert.clear();
                switch(num){
                    case 1:{
                        cout<<"\nGive input: \n"<<endl;
                        vector<string> temp_array;
                        string str;
                        cin.sync();
                        getline(cin,str);
                        string item;
                        stringstream ss(str);
                        while (getline(ss,item,'\t'))
                            temp_array.push_back(item);
                        if(compare(temp_array[0],"i")==0 && temp_array.size() == 4){
                            root = insert(root,temp_array[1],temp_array[2],temp_array[3]);
                        }
                        else if(compare(temp_array[0],"d")==0 && temp_array.size() == 2){
                            deleteFromSortedList(head,temp_array[1]);
                            root = deleteNode(root,temp_array[1],check);
                            if(!check)
                                cout << "Element not found!\n" << endl;
                            check = false;
                        }
                        else{
                            cout << "Wrong Input!\n" << endl;
                            cout << "Correct Syntax for insertion is: \"i	wordToBeAdded	meaning	  parOfSpeech\"\n"<<endl;
                            cout << "Correct Syntax for deletion is: \"d	ElementToBeDeleted\"\n"<<endl;
                            cout << "One tab space between each word!\n"<<endl;
                        }
                        continue;
                    }
                    case 2:{
                        string str;
                        cout<<"\nGive input:\n"<<endl;
                        vector<string> temp_array;
                        cin.sync();
                        getline(cin,str);
                        string item;
                        stringstream ss(str);
                        while (getline(ss,item,'\t'))
                            temp_array.push_back(item);
                        if(compare(temp_array[0],"i")== 0 && temp_array.size() == 4)
                            rootF = insert(rootF,temp_array[1],temp_array[2],temp_array[3]);
                        else if(compare(temp_array[0],"d")== 0 && temp_array.size() == 2){
                            deleteFromSortedList(headF,temp_array[1]);
                            rootF = deleteNode(rootF,temp_array[1],check);
                            if(!check)
                                cout << "Element not found!\n"<<endl;
                        }
                        else
                            cout << "Wrong Input!\n" << endl;
                        continue;
                    }
                    default:
                        cout << "wrong input!\n" << endl;
                        continue;
                }
            }
            case 8:
                readFile("input traversals.txt");
                cout << setw(25)<< left << "Word:" << "\t" << setw(25)<< left<< "Meaning:" << "\t" << setw(25)<< left<< "Part of Speech:" << "\t" << setw(25)<< left<< "Frequency:"<< "\n"<< endl;
                inOrderDisplay(tree_ptrs[0]);
                continue;
            case 9:
                exit(0);
            default:
                cout<<"Wrong Input! Enter again: "<<endl;
        }
    }
}



void insert_end(string key, string mean, int freq){
    FNode * curr;
    curr = new FNode();
    curr -> next = NULL;
    curr->frequency = freq;
    curr->mean = mean;
    curr->key = key;

    if (head == NULL){
        head = tail = curr;
        tail->next = NULL;
    } else
    {
        tail -> next = curr;
        tail = curr;
        tail ->next = NULL;
    }
}

void sort(){
    FNode *ptr1 = head;
    FNode *curr = ptr1 -> next;
    while (ptr1 != tail){
        while (curr->next != NULL ){
            if (curr -> frequency < ptr1->frequency){
                int temp = ptr1->frequency;
                ptr1 ->frequency = curr->frequency;
                curr->frequency = temp;
            }else{
                curr = curr->next;
            }
        }
        ptr1 = ptr1 -> next;
    }
}

void display(){
    sort();
    FNode *curr;
    curr = head;
    cout << setw(25)<< left << "Word:" << "\t" << setw(25)<< left<< "Meaning:" << "\t" << setw(25)<< left<< "Part of Speech:" << "\t" << setw(25)<< left<< "Frequency:"<< "\n"<< endl;
    while (curr != nullptr){
        cout << setw(25)<< left << curr->key << "\t" << setw(25)<< left<< curr->mean << "\t" << setw(25)<< left<< "Part of Speech"<< "\t" << setw(25)<< left<< curr->frequency<< "\n"<< endl;


        curr = curr-> next;

    }
}




int compare(string key, string to_check){
    int index = 0;
    int key_l = key.length();
    int to_check_l = to_check.length();
    while(index < key_l and index < to_check_l){
        if(int(key.at(index)) < int(to_check.at(index)))
            return -1;
        else if(int(key.at(index)) > int(to_check.at(index)))
            return 1;
        index++;
    }
    if(key_l < to_check_l)
        return -1;
    else if(key_l > to_check_l)
        return 1;
    else
        return 0;
}

AVLNode* createNode(string key,string mean,string pof_speech){
    AVLNode *temp = new AVLNode();

    temp->key = key;
    temp->mean = mean;
    temp->pof_speech = pof_speech;
    temp->height = 1;
    temp->frequency = 1;


    return temp;
}




void preOrderDisplay(AVLNode *node){
    if(node != NULL)
    {
        insert_end(node->key, node->mean,node->frequency);
        preOrderDisplay(node->left);
        preOrderDisplay(node->right);
    }
}

void searchWord(AVLNode *node,string key){

    while(node!=NULL){
        if(compare(key,node->key) == 0){
            cout << setw(25)<< left << "Word:" << "\t" << setw(25)<< left<< "Meaning:" << "\t" << setw(25)<< left<< "Part of Speech:" << "\t" << setw(25)<< left<< "Frequency:"<< "\n"<< endl;
            cout << setw(25)<< left << node->key << "\t" << setw(25)<< left<< node->mean << "\t" << setw(25)<< left<< node->pof_speech << "\t" << setw(25)<< left<< node->frequency<< "\n"<< endl;
            node->frequency++;
            return;
        }
        if(compare(key,node->key) == -1){
            node = node->left;
        }
        else if(compare(key,node->key) == 1){
            node = node->right;
        }
    }
    cout << "The word was not found!"<< endl;
}

void Modify(AVLNode *node,string key){

    while(node!=NULL){
        if(key == node->key){
            cout << "Enter the modified meaning"<< endl;
            string str;
            cin >> str;
            node->mean = str;
            cout << key << " " << node->mean << " " << node->pof_speech<<" "<<node->frequency;
            return;
        }
        if(key < node->key ){
            node = node->left;
        }
        else if(key>node->key){
            node = node->right;
        }
    }
    cout << "The word does not exist!"<< endl;
}



void inOrderDisplay(AVLNode *node){
    if(node != NULL)
    {
        inOrderDisplay(node->left);
        cout << setw(25)<< left << node->key << "\t" << setw(25)<< left<< node->mean << "\t" << setw(25)<< left<< node->pof_speech << "\t" << setw(25)<< left<< node->frequency<< "\n"<< endl;
        inOrderDisplay(node->right);
    }
}


void createFNode(int freq, AVLNode *node, FNode *&head, FNode *&tail){
    FNode *temp = new FNode;
    temp->frequency = freq;
    temp->ptr = node;
    if(head==NULL){
        head = temp;
        tail = temp;
        tail->next = NULL;
        tail->previous = NULL;
    }
    else{
        tail->next = temp;
        temp->previous = tail;
        tail = temp;
        tail->next = NULL;
    }
}


void createFNodeStart(int f, AVLNode *node, FNode *&head){
    FNode *temp = new FNode;
    temp->frequency = f;
    temp->ptr = node;
    head->previous = temp;
    temp->next = head;
    head = temp;
}
void createFNodeSpecific(int f , AVLNode *node,FNode *&head){
    FNode *temp = new FNode;
    temp->frequency = f;
    temp->ptr = node;
    FNode *start = head;
    while(start!=NULL){
        if(start->frequency < f){
            temp->previous = start->previous;
            (start->previous)->next = temp;
            temp->next = start;
            start->previous = temp;
            break;
        }
        start = start->next;
    }
}




void sortFrequency(AVLNode *node,AVLNode *root,FNode *&head,FNode *&tail){
    if(node!=NULL){
        if(node == root)
            createFNode(node->frequency,node,head,tail);
        else if(node->frequency > head->frequency)
            createFNodeStart(node->frequency,node,head);
        else if(node->frequency <= tail->frequency )
            createFNode(node->frequency,node,head,tail);
        else
            createFNodeSpecific(node->frequency,node,head);

        sortFrequency(node->left,root,head,tail);
        sortFrequency(node->right,root,head,tail);
    }
}


AVLNode* minNode(AVLNode *node){
    while(node->left!=NULL){
        node = node->left;
    }
    return node;

}



int getHeight(AVLNode *node){
    if(node==NULL)
        return 0;
    else
        return(node->height);
}

int max(int a, int b){
    return (a > b)? a : b;
}

int calBalance(AVLNode *node){
    return(getHeight(node->left) - getHeight(node->right));
}


AVLNode* searchWordVal(AVLNode *node,string key){

    while(node!=NULL){
        if(key == node->key){
            node->frequency++;
            return node;
        }
        if(key < node->key ){
            node = node->left;
        }
        else if(key>node->key){
            node = node->right;
        }
    }
    cout << "The word was not found!"<< endl;
}


int search(vector<string> inorder, int start, int end, string key){
    for(int i = start;i<=end;i++){
        if(compare(inorder[i],key)==0)
            return i;
    }
}


void displaySortedList(FNode *node){

    if (head == nullptr){
        cout<<" Nothing !";
    }else{
        while(node->next!=head)
            cout << setw(25)<< left<< node->ptr->key << " ";
            cout << setw(25)<< left<< node->ptr->mean << " ";
            cout << setw(25)<< left<< node->ptr->pof_speech << " ";
            cout << node->ptr->frequency << " ";
            cout << "\n";
            node = node->next;
    }
}

void displayHighFrequency(FNode *head){
    FNode *start = head;
    while(start!=NULL){
        if(start->frequency == head->frequency){
            cout << setw(25)<< left<< start->ptr->key << "\t" << setw(25)<< left<< start->ptr->mean << "\t";
            cout << setw(25)<< left<< start->ptr->pof_speech << "\t" << setw(25)<< left<< start->ptr->frequency<<"\n";
            start = start->next;
        }
        else
            break;
    }
}

void displayPOF(AVLNode *node){

    if (node!= nullptr){
        displayPOF(node->left);
        if(node->pof_speech == pof){
            cout << setw(25)<< left << node->key << "\t" << setw(25)<< left<< node->mean << "\t" << setw(25)<< left<< node->pof_speech << "\t" << setw(25)<< left<< node->frequency<< "\n"<< endl;
        }
        displayPOF(node->right);
    }


}

void deleteFromSortedList(FNode *head,string key){
    FNode *start = head;
    while(start->next != NULL){
        if(compare(start->ptr->key,key) == 0 ){
            start->previous->next = start->next;
            start->next->previous = start->previous;
            free(start);
            break;
        }
        start = start->next;
    }

}




AVLNode* rotateLeft(AVLNode *node){
    AVLNode *p_node = node->right;
    AVLNode *p_subnode = p_node->left;

    p_node->left = node;
    node->right = p_subnode;

    node->height = 1 + max(getHeight(node->left),getHeight(node->right));
    p_node->height = 1 + max(getHeight(p_node->left),getHeight(p_node->right));


    return p_node;

}
AVLNode* rotateRight(AVLNode *node){
    AVLNode *p_node = node->left;
    AVLNode *p_subnode = p_node->right;

    p_node->right = node;
    node->left = p_subnode;

    node->height = 1 + max(getHeight(node->left),getHeight(node->right));
    p_node->height = 1 + max(getHeight(p_node->left),getHeight(p_node->right));

    return p_node;

}


AVLNode* insert(AVLNode *node, string key, string mean, string pof_speech){



    if(node==NULL)
        return(createNode(key,mean,pof_speech));

    int comparison = compare(key,node->key);

    if(comparison==-1)
        node->left = insert(node->left,key,mean,pof_speech);

    else if(comparison == 1)
        node->right = insert(node->right,key,mean,pof_speech);

    else{
        node->frequency++;
        cout << "\nThis word already exist!\n"<< endl;
        return node;
    }

    node->height = 1 + max(getHeight(node->left),getHeight(node->right)) ;
    int balance = calBalance(node);

    if(balance > 1 and compare(key, (node->left)->key) == -1)
        return rotateRight(node);
    if(balance > 1 and compare(key, (node->left)->key) == 1){
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
    if(balance < -1 and compare(key, (node->right)->key) == 1)
        return rotateLeft(node);
    if(balance < -1 and compare(key, (node->right)->key) == -1){
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}


AVLNode* frenchCreate(AVLNode *node){
    if(node != NULL)
    {
        stringstream ss(node->mean);
        string element;
        while (getline(ss,element,',')) {
            rootF = insert(rootF,element,node->key,node->pof_speech);
        }
        frenchCreate(node->left);
        frenchCreate(node->right);
    }
    return rootF;

}

AVLNode* deleteNode(AVLNode *node, string key, bool &check){

    if(node==NULL)
        return node;
    int comparison = compare(key,node->key);
    if(comparison == -1)
        node->left = deleteNode(node->left,key,check);
    else if(comparison == 1)
        node->right = deleteNode(node->right,key,check);
    else{
        check = true;
        if(node->left==NULL or node->right == NULL){
            AVLNode *temp = node->left ?
                            node->left :
                            node->right;
            if(temp == NULL){
                temp = node;
                node = NULL;
            }
            else
                *node = *temp;
            free(temp);
        }
        else{
            AVLNode *temp = minNode(node->right);
            node->key = temp->key;
            node->mean = temp->mean;
            node->pof_speech = temp->pof_speech;
            node->frequency = temp->frequency;

            node->right = deleteNode(node->right,temp->key,check);

        }
    }
    if(node==NULL)
        return node;

    node->height = 1 + max(getHeight(node->left),getHeight(node->right));
    int balance = calBalance(node);
    if(balance > 1 and calBalance(node->left) >= 0)
        return rotateRight(node);
    if(balance > 1 and calBalance(node->left) < 0){
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
    if(balance < -1 and calBalance(node->right) <= 0)
        return rotateLeft(node);
    if(balance < -1 and calBalance(node->right) > 0){
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }
    return node;

}



void insertFile(string filename){
    vector<string> temp_arr;
    string line;
    ifstream myfile(filename.c_str());
    if (myfile.is_open())
    {
        while(getline (myfile,line)){
//	cout << "\n"<<line<<"\n";
            string buf;
            stringstream ss(line);
            while (getline(ss,buf,'\t'))
                temp_arr.push_back(buf);
            root = insert(root,temp_arr[0],temp_arr[1],temp_arr[2]);
            temp_arr.clear();
        }
    }
    myfile.close();
}
void readFile(string filename){
    string line;
    int check = false;
    ifstream myfile (filename.c_str());
    vector<string> arr1;
    vector<string> arr2;
    if (myfile.is_open())
    {
        while(getline (myfile,line)){
            if(line.empty()){
                if(check){
                    createTree(arr1,arr2);
                    arr2.clear();
                    check = false;
                    continue;
                }
                else{
                    arr1 = arr2;
                    arr2.clear();
                    check = true;
                    continue;
                }
            }
            string buf;
            stringstream ss(line);
            while (ss >> buf)
                arr2.push_back(buf);
        }
        createTree(arr1,arr2);

    }
    myfile.close();
}

void createTree(vector<string> v_arr1, vector<string> v_arr2 ){
    if(v_arr1[0] == "P:"){
        if(checkTree(v_arr1)){
            tree_ptrs.push_back(constructTree(v_arr1,v_arr2,1,v_arr1.size()-1));
            preorder_idx = 1;
        }

        else
            cout << "Tree cannot be made from the given traversal!\n"<< endl;
    }
    else{
        if(checkTree(v_arr2)){
            AVLNode *temp = constructTree(v_arr1,v_arr2,1,v_arr1.size()-1);
            preorder_idx = 1;
            tree_ptrs.push_back(temp);
        }

        else
            cout << "Tree cannot be made from the given traversal!\n"<< endl;
    }
}


AVLNode* constructTree(vector<string> inorder, vector<string> preorder,int inorder_start,int inorder_end){
    if(inorder_start > inorder_end)
        return NULL;
    AVLNode *temp = searchWordVal(root,preorder[preorder_idx++]);
    AVLNode *tree_node = createNode(temp->key,temp->mean,temp->pof_speech);

    if(inorder_start == inorder_end){
        tree_node->height = 1+ max(getHeight(tree_node->left),getHeight(tree_node->right));
        return tree_node;
    }


    int inorder_idx = search(inorder,inorder_start,inorder_end,tree_node->key);

    tree_node->left = constructTree(inorder,preorder,inorder_start,inorder_idx-1);
    tree_node->height = 1+ max(getHeight(tree_node->left),getHeight(tree_node->right));
    tree_node->right = constructTree(inorder,preorder,inorder_idx+1,inorder_end);
    tree_node->height = 1+ max(getHeight(tree_node->left),getHeight(tree_node->right));
    return tree_node;
}




bool checkTree(vector<string> prearray){
    stack<string> s;

    string root = "A";

    for (int i=1; i<prearray.size(); i++)
    {
        if (compare(prearray[i],root) == -1)
            return false;
        while (!s.empty() && compare(s.top(),prearray[i])==-1)
        {
            root = s.top();
            s.pop();
        }

        s.push(prearray[i]);
    }
    return true;
}