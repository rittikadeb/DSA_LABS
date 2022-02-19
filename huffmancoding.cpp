#include<iostream>
#include<string.h>
#include<fstream>
#include<conio.h>
#include<process.h>
using namespace std;
struct node
{
char data;
int freq;
char *code;
node *Llink;
node *Rlink;
};
struct node nn[100];
char name[20];
int function()
{
cout<<"\n\t\t\t\t\tHuffman's Code\n-----------------------------------------------------------------------------------------------------------------------\n\nCompression:\n\nEnter the name of the file you want to compress: \n";
cin>>name;
ifstream fin(name);
for(int i=0;i<10;i++)
{
nn[i].freq=0;
}
int j=0,num=0,flg=0,yo=-1;
char ab=' ';
while(!fin.eof())
{
int ff=0;
for(int k=0;k<num;k++)
{
if(ab==nn[k].data)
{
nn[k].freq++;
ff=1;
}
}
if(ff==0)
{
num=num+1;
nn[j].data=ab;
nn[j].freq++;
j++;
}
fin>>ab;
}
fin.close();
char aa[80];
ifstream finn(name);
cout<<"\nInputted file contains:\n-----------------------------------------------------------------------------------------------------------------------\n";
finn.getline(aa,80);
cout<<aa<<"\nSize of file: "<<strlen(aa)<<" bytes.\n";
finn.close();
return num-1;
}
class BinaryTree
{
private:
node *root;
public:
BinaryTree() { root=NULL; }
void print();
void assign_code(int);
void print_code(char );
void encode(const char[]);
void print_symbol(char [], int &, int);
void decode(char [], int);
friend class minHeap;
friend class HuffmanCode;
};
class minHeap
{
private:
BinaryTree *T;
int n;
public:
minHeap();
void heapify(int i);
BinaryTree remove();
void insert(BinaryTree b);
void print();
friend class HuffmanCode;
};
int sum=0;
class HuffmanCode
{
private:
BinaryTree HuffmanTree;
public:
HuffmanCode();
};
ofstream fout("compressed.dat",ios::binary|ios::out);
HuffmanCode::HuffmanCode()
{
minHeap Heap;
while (Heap.T[0].root->freq>1)
{
BinaryTree l=Heap.remove();
BinaryTree r=Heap.remove();
HuffmanTree.root=new node;
HuffmanTree.root->data='\0';
HuffmanTree.root->freq=l.root->freq + r.root->freq;
HuffmanTree.root->Llink=l.root;
HuffmanTree.root->Rlink=r.root;
Heap.insert(HuffmanTree);
}
HuffmanTree=Heap.T[1];
delete []Heap.T;
cout<<"\nAssigning Codes: \n-----------------------------------------------------------------------------------------------------------------------\n";
cout<<"\nThe symbols with their codes are as follows\n";
HuffmanTree.assign_code(0);
cout<<"Total memory = \t\t\t"<<sum<<" bits = "<<sum/8<<" bytes\n";
cout<<"\nEncoding: \n-----------------------------------------------------------------------------------------------------------------------\n";
char str[100];
ifstream fin(name);
fin.getline(str,100);
fin.close();
HuffmanTree.encode(str);
fout.close();
int length;
char cd[100];
fin.open("compressed.dat",ios::binary|ios::in);
fin>>cd;
length=strlen(cd);
fin.close();
HuffmanTree.decode(cd,length);
}
minHeap::minHeap()
{
n=function();
T= new BinaryTree [n+1];
T[0].root=new node;
T[0].root->freq=n; //Number of elements in min. Heap is stored in the zeroth element of the heap
for (int i=1; i<=n; i++)
{
T[i].root=new node;
T[i].root->data=nn[i].data;
T[i].root->freq=nn[i].freq;
T[i].root->code=NULL;
T[i].root->Llink=NULL;
T[i].root->Rlink=NULL;
}
cout<<endl;
int i;
i=(int)(n/2);
while (i>0)
{
heapify(i);
i--;
}
}
int min(node *a, node *b)
{if (a->freq <= b->freq) return a->freq; else return b->freq;}
void swap(BinaryTree &a, BinaryTree &b)
{BinaryTree c=a; a=b; b=c;}
void minHeap::heapify(int i)
{
while(1)
{
if (2*i > T[0].root->freq)
return;
if (2*i+1 > T[0].root->freq)
{
if (T[2*i].root->freq <= T[i].root->freq)
swap(T[2*i],T[i]);
return;
}
int m=min(T[2*i].root,T[2*i+1].root);
if (T[i].root->freq <= m)
return;
if (T[2*i].root->freq <= T[2*i+1].root->freq)
{
swap(T[2*i],T[i]);
i=2*i;
}
else
{
swap(T[2*i+1],T[i]);
i=2*i+1;
}
}
}
BinaryTree minHeap::remove()
{
BinaryTree b=T[1];
T[1]= T[T[0].root->freq];
T[0].root->freq--;
if (T[0].root->freq!=1)
heapify(1);
return b;
}
void minHeap::insert(BinaryTree b)
{
T[0].root->freq++;
T[T[0].root->freq]=b;
int i=(int) (T[0].root->freq /2 );
while (i>0)
{
heapify (i);
i=(int) (i /2 );
}
}
int isleaf(node *nd)
{ if(nd->data=='\0') return 0; else return 1;}
void BinaryTree::assign_code(int i)
{
if (root==NULL)
return;
if (isleaf(root))
{
root->code[i]='\0';
cout<<root->data<<":\t"<<root->freq<<" occurences\t"<<root->code<<" = \t";
sum+=root->freq*strlen(root->code);
cout<<root->freq<<"*"<<strlen(root->code)<<" = "<<root->freq*strlen(root->code)<<" bits."<<endl;
return;
}
BinaryTree l,r;
l.root=root->Llink;
r.root=root->Rlink;
l.root->code=new char[i+1];
r.root->code=new char[i+1];
for (int k=0; k<i; k++)
{
l.root->code[k]=root->code[k];
r.root->code[k]=root->code[k];
}
l.root->code[i]='0';
r.root->code[i]='1';
i++;
l.assign_code(i);
r.assign_code(i);
}
void BinaryTree::encode(const char str[])
{
if (root==NULL)
return;
int i=0;
cout<<"Encoded code for the input string '"<<str<<"' is\n";
while (1)
{
if (str[i]=='\0')
{
cout<<endl;
return;
}
print_code(str[i]);
i++;
}
}
char *r[40];
int ii=-1;
void BinaryTree::print_code(char c)
{
int f=0;
if (isleaf(root))
{
if (c==root->data)
{
f=1;
cout<<root->code;
fout<<root->code;
}
return ;
}
BinaryTree l,r;
l.root=root->Llink;
if (f!=1)
l.print_code(c);
r.root=root->Rlink;
if(f!=1)
r.print_code(c);
}
int isequal(const char a[], const char b[], int length)
{
int i=0;
while (i<length)
{
if(b[i]!=a[i])
return 0;
i++;
}
if (a[i]!='\0')
return 0;
return 1;
}
ofstream fouttt("uncompressed.txt");
void BinaryTree::decode(char cd[], int size)
{
if (root==NULL)
return;
int i=0;
int length=0;
int f;
char *s;
cout<<"\nDecoding: \n-----------------------------------------------------------------------------------------------------------------------\n";
cout<<"Decoded string for the input code '"<<cd<<"' is\n";
while (i<size)
{
f=0;
s=&cd[i];
while (f==0)
{
length++;
print_symbol(s,f,length);
}
i=i+length;
length=0;
}
fouttt.close();
cout<<endl;
}
void BinaryTree::print_symbol(char cd[], int &f, int length)
{
if (isleaf(root))
{
if (isequal(root->code, cd, length))
{
f=1;
cout<<root->data;
fouttt<<root->data;
}
return;
}
BinaryTree l,r;
l.root=root->Llink;
if (f!=1)
l.print_symbol(cd,f,length);
r.root=root->Rlink;
if (f!=1)
r.print_symbol(cd,f,length);
}
void BinaryTree::print()
{
if (root==NULL)
return;
cout<<root->data<<"\t"<<root->freq<<"\n";
if (isleaf(root))
return;
BinaryTree l,r;
l.root=root->Llink;
r.root=root->Rlink;
l.print();
r.print();
}
int power(int i, int j)
{
int n=1;
for (int k=1; k<=j; k++)
n=n*i;
return n;
}
int ispowerof2(int i)
{
if (i==1)
return 0;
if (i==0)
return 1;
while (i>2)
{
if (i%2!=0)
return 0;
i=i/2;
}
return 1;
}
int fn(int l)
{
if (l==1||l==0)
return 0;
return 2*fn(l-1)+1;
}
void minHeap::print()
{
cout<<"The Heap showing the root frequencies of the Binary Trees are:\n";
if (T[0].root->freq==0)
{
cout<<endl;
return;
}
int level=1;
while( T[0].root->freq >= power(2,level) )// 2^n-1 is the max. no. of nodes
///in a complete tree of n levels
level++;
if(level==1)
{
cout<<T[1].root->freq<<"\n";
return;
}
for (int i=1; i<=T[0].root->freq; i++)
{
if (ispowerof2(i))
{cout<<"\n"; level--;}
for (int k=1; k<=fn(level); k++)
cout<<" ";
cout<<T[i].root->freq<<" ";
for (int k=1; k<=fn(level); k++)
cout<<" ";
}
cout<<endl;
}
int main()
{
HuffmanCode c;
getch();
return 0;
}