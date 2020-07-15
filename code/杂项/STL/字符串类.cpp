//任意进制转换：
itoa(int n,char* s,int r)  //将10进制n转换为r进制并赋给s
string:
//流：
#include<sstream>
stringstream stream;   //创建名为stream的流
stream.clear   //重复使用必须清空
string a,str;
stream(a);             //将字符串a放入流
while(a>>str)       //将a流入str中，以空格为拆分进行输出
cout<< str<< endl;
//迭代器：
string::iterator it  //创建名为it的迭代器
//反转：
reverse(s.begin(), s.end());   //原地反转
s1.assign(s.rbegin(), s.rend());   //反转并赋给s1

//大小写转换：
transform(s.begin(), s.end(), s.begin(), ::toupper);
transform(s.begin(), s.end(), s.begin(), ::tolower);

//类型转换：
string ->int : string s("123");
int i = atoi(s.c_str());

int -> string: int a;
stringstream(s) >> a;
//子串：
string substr(int pos = 0,int n = npos) const;//返回pos开始的n个字符组成的字符串
//插入：
s.insert(int p0,string s)    //在p0位置插入字符串s
//更改：
s.assign(str); //直接
s.assign(str,1,3);//如果str是”iamangel” 就是把”ama”赋给字符串
s.assign(str,2,string::npos);//把字符串str从索引值2开始到结尾赋给s
s.assign("gaint"); //不说
s.assign("nico",5);//把’n’ ‘I’ ‘c’ ‘o’ ‘\0’赋给字符串
s.assign(5,'x');//把五个x赋给字符串
//删除：
s.erase(13);//从索引13开始往后全删除
s.erase(7,5);//从索引7开始往后删5个
iterator erase(iterator it);//删除it指向的字符，返回删除后迭代器的位置
iterator erase(iterator first, iterator last);//删除[first，last）之间的所有字符，返回删除后迭代器的位置
//查找：
int find(char c, int pos = 0) const;//从pos开始查找字符c在当前字符串的位置
int find(const char *s, int pos = 0) const;//从pos开始查找字符串s在当前串中的位置
int find(const char *s, int pos, int n) const;//从pos开始查找字符串s中前n个字符在当前串中的位置
int find(const string &s, int pos = 0) const;//从pos开始查找字符串s在当前串中的位置。
//删除所有特定字符：
str.erase(std::remove(str.begin(), str.end(), 'a'), str.end());
//删除所有重复字符：
//要求对象有序O(n+n)，如果先排序O(nlogn+n+n)
str.erase(unique(str.begin(),str.end(),str.end());
