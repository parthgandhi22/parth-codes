#include <iostream>
#include<fstream>
#include <string>
#include <dirent.h>
using namespace std;

void create();

struct Node {
    string fileName;   
    string path;   
    int height;        
    Node *left;
    Node *right;
    Node(string name, string path1){
        fileName=name;
        path=path1;
        height=1;
        left=nullptr;
        right=nullptr;
    }
};

int heightt(Node* node) {
    if (node)
        return node->height;
    else    
        return 0;
}

int bf(Node* node) {
    if (node)
        return heightt(node->left) - heightt(node->right);
    else    
        return 0;
}

Node* rotateright(Node* y) {
    Node* x = y->left;
    Node* T = x->right;

    x->right = y;
    y->left = T;
    
    x->height = max(heightt(x->left), heightt(x->right)) + 1;
    y->height = max(heightt(y->left), heightt(y->right)) + 1;

    return x;
}

Node* rotateleft(Node* x) {
    Node* y = x->right;
    Node* T = y->left;

    y->left = x;
    x->right = T;

    x->height = max(heightt(x->left), heightt(x->right)) + 1;
    y->height = max(heightt(y->left), heightt(y->right)) + 1;

    return y;
}

Node* insertfile(Node* node, string fileName, string Path) {
    ofstream newFile(Path);
    if (newFile) {
        cout << "FILE CREATED SUCCESSFULLY."<< endl;
        newFile.close();
    } else {
        cout << "Incorrect path."<< endl;
        return node;
    }
}

Node* insert(Node* node, string fileName, string Path) {
    if (!node) return new Node(fileName, Path);
    if (Path < node->path)
        node->left = insert(node->left, fileName,Path);
    else if (Path > node->path)
        node->right = insert(node->right, fileName, Path);
    else
        return node;

    node->height = 1 + max(heightt(node->left), heightt(node->right));

    // Balance the node
    int balance = bf(node);

        // Left heavy
    if (balance > 1 && Path < node->left->path)
        return rotateright(node);

        // Right heavy
    if (balance < -1 && Path > node->right->path)
        return rotateleft(node);

        // Left-Right case
    if (balance > 1 && Path > node->left->path) {
        node->left = rotateleft(node->left);
        return rotateright(node);
    }

        // Right-Left case
    if (balance < -1 && Path < node->right->path) {
        node->right = rotateright(node->right);
        return rotateleft(node);
    }

    return node;
}

void display(Node* node, int depth) {
    if (!node) return;
    display(node->right, depth + 1);
    cout << string(depth * 4, ' ') << node->fileName << endl;
    display(node->left, depth + 1);
}

void showfiles(Node *&root,const string& pathh) {
    DIR *dir=opendir(pathh.c_str());
    if (dir == nullptr) {
        cout<<"Incorrect path."<<endl;
    }
    struct dirent* dir1;
    while(1){
        dir1=readdir(dir);
        if (dir1==nullptr)
            break;
        string fname=dir1->d_name;
        if (fname[0]=='.') {
            continue;
        }
        root=insert(root,fname,pathh+'\\'+fname); 
    } 
    closedir(dir);
}

int main() {
    // Node *root=nullptr;
    // string filepath;
    // cin>>filepath;
    // size_t lastSeparator = filepath.find_last_of("/\\");
    // string directorypath=filepath.substr(0, lastSeparator);
    // showfiles(root,directorypath);
    // display(root,0);
    cout<<endl;
    cout<<"Welcome to File Management System"<<endl;
    cout<<"1. Create a file"<<endl;
    cout<<"2. Delete a file"<<endl;
    cout<<"3. Moving a file"<<endl;
    cout<<"4. Copying a file"<<endl;
    cout<<"5. Show file structure"<<endl;
    cout<<"6. Create a directory"<<endl;
    cout<<"7. Delete a directory"<<endl;
    cout<<"8. Moving a directory"<<endl;
    cout<<"9. Copying a directory"<<endl;
    cout<<"10. Help"<<endl;
    int choice;
    cout<<"Enter your choice:";
    cin>>choice;
    switch(choice){
        case 1:
            create();
            break;
        /*case 2:
            remove();
            break;
        case 3:
            move();
            break;
        case 4:
            copy();
            break;
        case 5:
            cout<<"Enter the path of directory:";
            cin>>pathx;
            filestruct(pathx,0);
            break;
        case 6:
            createdirect();
            break;
        case 7:
            removedirect();
            break;
        case 10:
            cout<<endl;
            cout<<"For writing path of new directory, use \\."<<endl;;
            cout<<"Make sure to enter full address(starting from drive)."<<endl;
            cout<<endl;
            main();
            break;*/
        default:
            cout<<"Invalid choice."<<endl;
            main();
    }
}

void create(){
    Node *root=nullptr;
    string path;
    cout<<"Enter the path:";
    cin>>path;
    size_t lastSeparator = path.find_last_of("/\\");
    string directorypath=path.substr(0, lastSeparator);
    string filename=path.substr(lastSeparator+1);
    insertfile(root,filename,path);
    insert(root,filename,path);
    showfiles(root,directorypath);
    display(root,0);
}