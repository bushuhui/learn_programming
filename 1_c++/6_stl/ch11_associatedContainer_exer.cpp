//12/16
//数据结构 第五章 set~multiset 练习题
//C++ Primer 第十一章 关联容器 练习题

#include <map>
#include <set>
#include <vector>
#include <list>
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;

//11.3 单词计数
void q11_3_wordCount()
{
    fstream hp("./hp.txt");
    map<string, size_t> words;
    if(hp.fail())
    {
        cerr << "File open error." << endl;
        abort();
    }
    else
    {
        string word;
        while(!hp.eof())
        {
            hp >> word;
            ++words[word];
        }
        for(const auto &w: words)
        {
            cout << w.first << " occurs " << w.second << ((w.second) > 1 ? " times" : " time") << endl;
        }
    }
}

//11.7 map操作,家族及成员存储
void printFamily(map<string, vector<string>> ftree)
{
    for(auto i: ftree)
    {
        cout << i.first << ", kids: ";
        for(auto j: i.second)
        {
            cout << j << " ";
        }
        cout << endl;
    }
}

void addNewFamily(map<string, vector<string>> &ftree, map<string, vector<string>> new_family)
{
    for(auto fname: new_family)
    {
        if(ftree.find(fname.first) == ftree.end())
        {
            ftree.insert(fname);
        }
        else
        {
            auto tree_iter = ftree.find(fname.first);
            for(auto i: fname.second)
            {
                int judge = 0;
                for(auto j: tree_iter->second)
                {
                    if(i == j)
                    {
                        judge++;
                    }
                }
                if(judge == 0)
                {
                    (tree_iter->second).push_back(i);
                }
            }
        }
    }
}


void q11_7_mapOperations()
{
    map<string, vector<string>> family_tree{{"Smith",{"Bob","John","Alice"}}, {"Andrew",{"Alex","Jane"}}};
    map<string, vector<string>> new_family1{{"Khan",{"Anto","Anna"}}};  //={}不可行，赋值操作未定义
    map<string, vector<string>> new_family2{{"Smith",{"Bob","Nier"}}};
    addNewFamily(family_tree, new_family1);
    printFamily(family_tree);
    cout << "-------" << endl;

    addNewFamily(family_tree, new_family2);
    printFamily(family_tree);
}

//11.8 不重复vector
void addWord(vector<string> &v, string word)
{
    int unique = 0;
    for(auto i: v)
    {
        if(i == word)
        {
            unique++;
        }
    }
    if(unique == 0)
    {
        v.push_back(word);
    }
}

void q11_8_uniqueVector()
{
    vector<string> v{"soar", "knight", "year"};
    string word = "soar";
    addWord(v, word);
    string word2 = "string";
    addWord(v, word2);

    for(auto i: v)
    {
        cout << i << " ";
    }
    cout << endl;
}

//11.9 map操作
void q11_9_mapWithList()
{
    map<string, list<int>> ml;
    list<int> line{1, 3, 4};
    string word = "pairs";

    ml.insert(make_pair(word, line));
    for(auto i: ml)
    {
        cout << i.first << " occurs at ";
        for(auto j: i.second)
        {
            cout << "line " << j << " ";
        }
    }
}

//11.12 pair操作
void mergeVector(vector<string> vs, vector<int> vi, vector<pair<string, int>> &vo)
{
    int j = 0;
    for(auto i: vs)
    {
        //vo.push_back(make_pair(i, vi.at(j))); //method 1
        //vo.push_back({i, vi.at(j)});  //method2
        pair<string, int> p(i, vi.at(j));   //method3
        vo.push_back(p);
        j++;
    }
}

void q11_12_pairToVector()
{
    vector<string> vs{"Tear", "Rain", "Drop"};
    vector<int> vi{7, 999, 33};
    vector<pair<string, int>> vo;
    mergeVector(vs, vi, vo);
    for(auto i: vo)
    {
        cout << i.first << " of " << i.second << endl;
    }
}

//11.14 11.7拓展，添加成员生日
void printFamily2(map<string, vector<pair<string, int>>> ftree)
{
    for(auto i: ftree)
    {
        cout << "Family " << i.first << ": kids: ";
        for(auto j: i.second)
        {
            cout << j.first << " born at " << j.second << "  ";
        }
        cout << endl;
    }
}

void addNewFamily2(map<string, vector<pair<string, int>>> &ftree, map<string, vector<pair<string, int>>> new_family)
{
    for(auto fname: new_family)
    {
        if(ftree.find(fname.first) == ftree.end())
        {
            ftree.insert(fname);
        }
        else
        {
            auto tree_iter = ftree.find(fname.first);
            for(auto i: fname.second)
            {
                int judge = 0;
                for(auto j: tree_iter->second)
                {
                    if(i.first == j.first)
                    {
                        judge++;
                    }
                }
                if(judge == 0)
                {
                    (tree_iter->second).push_back(i);
                }
            }
        }
    }
}


void q11_14_mapOperations()
{
    map<string, vector<pair<string, int>>> family_tree{{"Smith",{{"Bob", 19730101},{"John", 19970806},{"Alice", 19771112}}},\
                                                       {"Andrew",{{"Alex", 20020305},{"Jane", 20090806}}}};
    map<string, vector<pair<string, int>>> new_family1{{"Khan", {{"Anto", 19940705},{"Anna", 19880626}}}};
    map<string, vector<pair<string, int>>> new_family2{{"Smith", {{"Bob", 19990706},{"Nier", 20130708}}}};
    addNewFamily2(family_tree, new_family1);
    printFamily2(family_tree);
    cout << "-------" << endl;

    addNewFamily2(family_tree, new_family2);
    printFamily2(family_tree);
}

//11.27 find与count
void q11_27_findInMap()
{
    map<string, vector<int>> m{{"Ross",{3}}};
    map<string, vector<int>>::iterator s = m.find("Ross");
    cout << (s->second).at(0) << endl;
}

//11.31 查找并删除map元素,11.32或打印元素
void q11_31_findToErase()
{
    multimap<string, string> author{{"A", "B"},{"A","E"},{"C","D"},{"F","K"}};
    if(author.find("C") != author.end())
    {
        author.erase("C");
    }
    else
    {
        cout << "Element doesn't exist at author." << endl;
    }

    auto j =author.begin();
    for(auto i = author.begin(); i != author.end(); i++)
    {
        if(i == author.begin())
        {
            cout << "Author: " << i->first << endl;
            cout << "Books: " << i->second << " ";
        }
        else if(i->first != j->first)
        {
            cout << endl;
            cout << "Author: " << i->first << endl;
            cout << "Books: " << i->second << " ";
            j++;
        }
        else if(i->first == j->first)
        {
            cout << i->second << " ";
            j++;
        }
    }
}

//11.33 单词转换（简写->书面）
void wordConvert(map<string, string> rule, string &target)
{
    string word, line;
    istringstream txt(target);
    while(getline(txt, line))   //读取行
    {
        istringstream stream(line); //用流控制输出，方便读取单词
        while(stream >> word)
        {
            cout << " ";
            if(rule.find(word) != rule.end())
            {
                word = (rule.find(word))->second;
            }
            cout << word;
        }
        cout << endl;
    }

}

void q11_33_wordConvert()
{
    map<string, string> rule = {{"k", "okay?"},{"y","why"},{"r","are"},{"u","you"},\
                                {"pic","picture"},{"thk","thanks!"},{"18r","later"}};
    string target{"where r u\ny dont u send me a pic\nk thk 18r\n"};
    wordConvert(rule, target);

}

int main()
{
    //q11_3_wordCount();
    //q11_7_mapOperations();
    //q11_8_uniqueVector();
    //q11_9_mapWithList();
    //q11_12_pairToVector();
    //q11_14_mapOperations();
    //q11_27_findInMap();
    //q11_31_findToErase();
    q11_33_wordConvert();

    return 0;
}
