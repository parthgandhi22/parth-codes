#include<iostream>
#include<fstream>
#include<cstdio>   //connecting cpp with c for file deletion
#include<dirent.h>
using namespace std;
void create();
void remove();
void move();
void copy();
void filestruct(string path,int x);
int main(){
    string pathx;
    cout<<endl;
    cout<<"Welcome to File Management System"<<endl;
    cout<<"1. Create a file"<<endl;
    cout<<"2. Delete a file"<<endl;
    cout<<"3. Moving a file"<<endl;
    cout<<"4. Copying a file"<<endl;
    cout<<"5. Show file structure"<<endl;
    cout<<"6. Help"<<endl;
    int choice;
    cout<<"Enter your choice:";
    cin>>choice;
    switch(choice){
        case 1:
            create();
            break;
        case 2:
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
            cout<<endl;
            cout<<"For writing path of new directory, use \\."<<endl;;
            cout<<"Make sure to enter full address(starting from drive)."<<endl;
            cout<<endl;
            main();
            break;
        default:
            cout<<"Invalid choice."<<endl;
            main();
    }
}

void create(){
    string path;
    cout<<"Enter the path:";
    cin>>path;
    ofstream file;
    file.open(path);
    if (file){
        cout<<"FILE CREATED SUCCESSFULLY."<<endl;
        file.close();
    }else
        cout<<"Incorrect path."<<endl;
    cout<<endl;
    main();
}

void remove(){
    string path;
    cout<<"Enter the path of file you want to delete:";
    cin>>path;
    int x=remove(path.c_str()); //using cstdio library to delete
    if (x==0){
        cout<<"FILE DELETED SUCCESSFULLY."<<endl;
    }
    else{
        cout<<"Incorrect path."<<endl;
    }
    cout<<endl;
    main();
}

void move(){           //can be done easily through filesystem but I realized lately
    string path1,path2,name;
    cout<<"Enter the path of file you want to move:";
    cin>>path1;
    cout<<"Enter your file name:";
    cin>>name;
    cout<<"Enter the path where you want to move:";
    cin>>path2;
    if (path1==path2+"\\"+name){
        cout<<"File already exist in this directory."<<endl;
        main();
    }
    else{
        ifstream src;
        ofstream dest;
        src.open(path1);
        dest.open(path2+"\\" + name);
        if (src && dest){
        }
        else{
            cout<<"Incorrect path."<<endl;        
            main();
        }
        while(src.eof()==0){
            string x;
            getline(src,x);
            dest<<x;
        }
        src.close();
        dest.close();
        remove(path1.c_str());
        cout<<"FILE MOVED SUCCESSFULLY."<<endl;
        main();
    }   
}

void copy(){
    string path1,path2,name;
    cout<<"Enter the path of file you want to copy:";
    cin>>path1;
    cout<<"Enter your file name:";
    cin>>name;
    cout<<"Enter the path where you want to copy:";
    cin>>path2;
    if (path1==path2+"\\"+name){
        cout<<"File already exist in this directory."<<endl;
        main();
    }
    else{
        ifstream src;
        ofstream dest;
        src.open(path1);
        dest.open(path2+"\\" + name);
        if (src && dest){
        }
        else{
            cout<<"Incorrect path."<<endl;        
            main();
        }
        while(src.eof()==0){
            string x;
            getline(src,x);
            dest<<x;
        }
        src.close();
        dest.close();
        cout<<"FILE COPIED SUCCESSFULLY."<<endl;
        main();
    }
}

void filestruct(string path,int x){
    DIR *dir=opendir(path.c_str());
    if (dir == nullptr) {
        cout<<"Incorrect path."<<endl;
        main();
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
        for (int i=0;i<x;i++) {
            cout<<"   ";
        }
        cout<<fname<<endl;
        if (dir1->d_type==DT_DIR){
            filestruct(path+"\\"+ fname,x+1);
        }  
    }
}