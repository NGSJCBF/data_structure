#include<iostream>
#include<fstream>
using namespace std;
const int defaultSize=200;
template <class Type>	
class SeqList {
	Type* data;       //顺序表存储数组
	int MaxSize;	 //最大允许长度
	int last;                  //当前最后元素下标
public:
	SeqList(int MaxSize = defaultSize);
	~SeqList() { delete[] data; }
	void input();
	void output();
	int Find(Type& x);
	bool insert(Type& a,int i);
	bool Remove(int i);
	void file_write();
	void file_read();
	void output_special(int i);
	SeqList<Type> operator=(SeqList<Type>& T);
};

template<class Type>
void SeqList<Type>::input() {
	cout << "To start building the Student Health Sheet, enter the location of the last element" << endl;
	while (1)
	{
		cin >> last;
		if (last<=MaxSize-1)
		{
			break;
		}
		cout << "The maximum amount of data that the table can hold has been exceeded" << endl;
	}
	cout << "Please enter the student's name, student number, age, birthday, gender, and health status in order" << endl;
	for (int i = 0; i <last; i++)
	{
		cin >> data[i].name >>data[i].num>> data[i].age >> data[i].birthday;
		cin	>> data[i].gender >> data[i].situation;
	}
}

template<class Type>
void SeqList<Type>::output() {
	cout << "name  age   birthday   gender    healthy situation" << endl;
	for (int i = 0; i < last; i++)
	{
		cout << data[i].name<<"    "
			<< data[i].age<<"    "
			<< data[i].birthday <<"       "
			<< data[i].gender <<"      "
			<< data[i].situation << endl;
		cout << i + 1 << endl;
	}
}

template<class Type>
void SeqList<Type>::output_special(int i) {
	cout << data[i].name << "    "
		<< data[i].age << "    "
		<< data[i].birthday << "   "
		<< data[i].gender << "      "
		<< data[i].situation << endl;
}

template <class Type>
SeqList <Type>::SeqList(int sz) {
	if (sz > 0) {
		MaxSize = sz;  last = -1;
		data = new Type[MaxSize];
		if (data == 0) {
			MaxSize = 0;   last = -1;
			return;
		}
	}

};

typedef struct student
{
	int   age;
	char  name[10];
	int birthday;
	char gender[10];
	char situation[10];
	char num[13];
} stutype;

template <class Type>
int SeqList <Type> ::Find(Type& x) {
	//搜索函数：在顺序表中从头查找结点值等于
	//给定值x的结点
	int  i = 0;
	while (i <= last && data[i].num != x.num)
		i++;
	if (i > last) return -1;
	else return i;
};



template<class Type>
bool SeqList<Type>::Remove(int i) {
	if (last == -1)return false;
	if (i<1 || i>last + 1)return false;
	Type x = data[i - 1];
	for (int j = i; j <= last; j++) {
		data[j - 1] = data[j];
	}
	last--;
	return true;
}

template<class Type>
SeqList<Type> SeqList<Type>::operator=(SeqList<Type>& T) {
	this->data = T->data;
}

template<class Type>
void SeqList<Type>::file_write() {
	ofstream o;
    o.open("file.text",ios::app);
    if(!o) {
        cout<<"file open failed"<<endl;
        return; 
    }
	for (int i = 0; i < last; i++) {
		o<< data[i].name<<"    "
			<< data[i].age<<"    "
			<< data[i].birthday <<"   "
			<< data[i].gender <<"      "
			<< data[i].situation << endl;
	}
	o.close();
}

template<class Type>
void SeqList<Type>::file_read() {
	ifstream o;
    o.open("file.text",ios::out);
    if(!o) {
        cout<<"file open failed"<< endl;
        return; 
    }
    char ch[200];
	cout<<"Reading from the file"<< endl;
	while(o >> ch){
        cout<< ch << endl;
    }
	o.close();
}

template<class Type>
bool SeqList<Type>::insert(Type &a,int i) {
	if (last == MaxSize - 1)return false;
	if (i<0 || i>last + 1)return false;
	for (int j = last; j >= i; j--) {
		data[j + 1] = data[j];
	}
	data[i] = a;
	last++;
	return true;
}

int main()
{
	SeqList  <stutype> stu1(50);
	stutype x;
	int i = 0,j=1;
    while (j)
    {       
        int po;
        cout<<"input the numbers of the operation:"<<endl<<
        "1.setup the list"<<endl<<
        "2.insert"<<endl<<
        "3.delete"<<endl<<
        "4.read from files"<<endl<<
        "5.write into files"<<endl<<
        "6.find"<<endl<<
        "7.output"<<endl<<
        "8.exit"<<endl;
        cin>>i;
        switch (i)
        {
        case 1:
            stu1.input();stu1.output();
            break;
        case 2:
            cout << "Please enter the student's name, student number, age, birthday, gender, and health status in order" << endl;
            cin>>x.name>>x.num>>x.age>>x.birthday>>x.gender>>x.situation;
            cout<<"enter the position of the student"<<endl;
            cin>>po;
            stu1.insert(x,po-1);
            break;
        case 3:
            cout<<"enter the position of the student you want to delete"<<endl;
            cin>>po;
            stu1.Remove(po);
            break;
        case 4:
            stu1.file_read();
            break;
        case 5:
            stu1.file_write();
            break;
        case 6:
            cout<<"input the number of the student"<<endl;
            cin>>x.num;
            po=stu1.Find(x);
            stu1.output_special(po);
            break;
        case 7:
            stu1.output();
            break;
        case 8:
            j=0;
            break;
        
        }
    }
	return 0;
}

