#include<iostream>
#include<fstream>
#include<string>
using namespace std;


class linknode
{
public:
    int   age;
	string name;
	int birthday;
	string gender;
	string situation;
	string num;
    linknode* link;
    linknode(linknode* ptr = 0) { link = ptr; }         //仅初始化指针变量的构造函数
    linknode(string namef,int birthdayf,string genderf,string situationf,string numf,int agef) 
    { 
        name=namef;
        birthday=birthdayf;
        gender=genderf;
        situation=situationf;
        num=numf;
        link = 0;
        age = agef; 
        }      //初始化数据成员和指针变量的构造函数
};

class List :public linknode {
private:
    linknode* first;            //第一个节点
    linknode* last=0;
    int size;
public:
    List() {first = new linknode(); }
    List(int size){size=size; first = new linknode();}
    List(string namef,int birthdayf,string genderf,string situationf,string numf,int agef);
    ~List() { make_empty(); };
    void make_empty();
    void input(int size);
    void output();
    bool insert(int& x);   //将新元素插到第i个节点后
    linknode* Locate(int i);
    void del(int i);
    void f_write(string path);
    linknode* f_read(string path);
    void add();
    linknode* find(string i);
};


List::List(string namef,int birthdayf,string genderf,string situationf,string numf,int agef) {               
    //不设置表头结点，初始化好first指针中的数据
    first = new linknode(namef,birthdayf,genderf,situationf,numf,agef);
}


void List::make_empty() {
    linknode* q;
    while (first->link != 0)
    {
        q = first->link;
        first->link = q->link;
        delete q;
    }
    delete first;
}


void List::input(int size) {
    int i = size;
    linknode* ptr;
    ptr = first;
    while (i > 0)
    {
        cin >> ptr->name >>ptr->num>> ptr->age >> ptr->birthday;
		cin	>> ptr->gender >> ptr->situation;
        i--;
        ptr->link = new linknode;
        if (i==0)
            last=ptr;
        ptr = ptr->link;
    }
}

void List::add(){
    linknode* ptr;
    ptr=last->link;
    ptr=new linknode;
    cout<<"input the student information"<<endl;
    cin >> ptr->name >>ptr->num>> ptr->age >> ptr->birthday;
	cin	>> ptr->gender >> ptr->situation;
    ptr->link = 0;
    last=ptr;
}


void List::output() {
    linknode* ptr;
    ptr = first;
    cout << "name  age   birthday   gender    healthy situation" << endl;
    while (ptr->link != 0)
    {
        cout << ptr->name<<"    "
        << ptr->age<<"    "
        << ptr->birthday <<"       "
        << ptr->gender <<"      "
        << ptr->situation << endl;
    }
}


bool List::insert(int&x) {        //将元素插入到第x个元素后
    if (x == 0)
    {
        linknode* newnode = new linknode();
        cin>>newnode->name>>newnode->num>>newnode->age>>newnode->birthday;
		cin	>> newnode->gender >> newnode->situation;
        newnode->link = first;
        first = newnode;
        return true;
    }
    linknode* current = Locate(x);
    if (current == 0)
        return false;
    linknode* newnode = new linknode();
    if (newnode == 0) {
        cerr << "内存分配错误" << endl;
        exit(1);
    }
    cin>>newnode->name>>newnode->num>>newnode->age>>newnode->birthday;
	cin	>> newnode->gender >> newnode->situation;
    newnode->link = current->link;
    current->link = newnode;
    return true;
}


linknode* List::Locate(int i) {
    linknode* n = first;
    if (i < 0)
        return NULL;
    for (int j = 0; j < i-1; j++)
    {
        n = n->link;
    }
    return n;
}


void List::del(int i){
    linknode* ptr,*temp;
    if (i==1)
    {
        ptr = first;
        first = first->link;
        delete ptr;
        return;
    }
    ptr = Locate(i-1);
    if (ptr == 0)
        return;
    temp=ptr->link;
    ptr->link = ptr->link->link;
    delete temp;
}

void List::f_write(string path){
    ofstream out;
    out.open("data.txt",ios::app);
    if(out.fail()){
        cerr << "file open failed" << endl;
        return;
    }
    linknode* ptr = first;
    while (ptr != NULL) {
        out<<ptr->name<<"    "
			<<ptr->age<<"    "
            <<ptr->num<<"    "
			<<ptr->birthday <<"   "
			<<ptr->gender <<"      "
			<<ptr->situation << endl;
    }
    out.close();    
}


linknode* List::f_read(string path){
    linknode* ptr = new linknode;
    ifstream in;
    in.open("data.txt",ios::in);
    if(!in.is_open()){
        cerr << "file open failed" << endl;
        return nullptr;
    }
    string namef,genderf,situationf,numf;
    int birthdayf,agef;
    while(in >> namef >> agef >> numf >> birthdayf >> genderf >> situationf){
        ptr = new linknode(namef,birthdayf,genderf,situationf,numf,agef);
        ptr=ptr->link;
    }
    return ptr;
    in.close();
}


linknode* List::find(string i){
    linknode* ptr = first;
    for (int j = 0; j < size; j++)
    {
        if (ptr->num== i)
        {
            return ptr;
        }
        ptr = ptr->link;
    }
    return nullptr;
}

int main(){
    bool flag = true;
    
    while (flag)
    {
        cout << "1.set up new list " << "2.insert" << " 3.delete" << " 4.read from file" << " 5.write into file"  <<"6.find someone's infomation" 
        <<"7.output all the information"
        <<" 8.exit" << endl;
        cout << "input your choice: ";
        int choice;
        cin >> choice;
        List list;
        switch (choice)
        {
        case 1:
            int size;
            cout<<"input the number of people you want to set up: ";
            cin>>size;
            list.input(size);
        case 2:
        {
            int i;
            cout<<"input the number of position you want to insert: ";
            cin>>i;
            list.insert(i);
            break;
            }
        case 3:
            {
                int i;
                cout<<"input the number of position you want to delete: ";
                cin>>i;
                list.del(i);
                break;
            }
        case 4:
            {
                string path;
                cout<<"input the path of the file you want to read: ";
                cin>>path;
                list.f_read(path);
            }
        case 5:
            {
                string path;
                cout<<"input the path of the file you want to write: ";
                cin>>path;
                list.f_write(path);
                break;
            }
        case 6:
            {
                string i;
                cout<<"input the number of student you want to find: ";
                cin>>i;
                linknode *temp=list.find(i);
                if (temp==nullptr)
                {
                    cout<<"not found";
                }
                else
                {
                    cout<<"found"<<endl;
                    cout<<temp->name<<" "<<temp->age<<" "<<temp->birthday<<" "<<temp->gender<<" "<<temp->situation<<endl;
                }
                break;
                }
        case 7:  
        {
            list.output();
            break;
            }
        case 8:
            flag = false;
            break;
    }
    
}
    return 0;
}