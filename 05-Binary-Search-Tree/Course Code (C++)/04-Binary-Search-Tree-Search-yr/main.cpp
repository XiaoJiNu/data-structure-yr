#include <iostream>
#include <vector>
#include <string>
#include "SequenceST.h"
#include "FileOps.h"

using namespace std;

template <typename Key, typename Value>
class BST{
private:
    // 创建一个结点结构
    struct Node{
        Key key;
        Value value;
        Node *left;
        Node *right;
        // 构造函数
        Node(Key key, Value value){
            this -> key = key;
            this -> value = value;
            left = right = nullptr;
        }
    };

    Node *root;  // 创建根节点
    int count;   // 用于计算节点个数
public:
    BST(){
        root = nullptr;
        count = 0;
    }

    ~BST(){}

    int size(){
        return count;
    }

    bool isEmpty(){
        return count == 0;
    }

    
    // ----------版本二----------
    void insert(Key key, Value value){
        root = insert(root, key, value);
    }
    
    // 输入key和二分搜索树，如果不含key，返回false，否则返回true
    bool contain(Key key){
        return contain(root, key);
    }

    // 输入key和二分搜索树，输出value的地址
    Value* search(Key key){
        return search(root, key);
    }

private:
    // 为了不让外部接触内部的节点结构体，
    // 真正的插入操作作为一个私有函数
    // ----------版本二----------
    Node* insert(Node* node, Key key, Value value){
        // 与版本一不同，这里一直递归调用insert函数，直到递归到某个节点为空，
        // 生成新的节点并将它赋值给这个空节点。
        // 每次递归完成后会返回生成的节点或者当前比较的节点，最终返回根节点
        if (node == nullptr){
            // ### 插入一个节点时需要对二分搜索树的节点数加1
            count ++;
            Node *newNode = new Node(key, value);
            return newNode;
        }

        if(key == node->key){
            node -> value = value;
            return node;
        }
        else if(key < node->key)
            node -> left = insert(node->left, key, value);
        else if(key > node->key)
            node -> right = insert(node->right, key, value);

        // 最终递归返回到第一层时，返回根节点，在外层的insert中赋值给root
        return node;
    }

    Value* search(Node* node, Key key){
        // 递归终止条件：节点为空或者找到key对应的节点时终止递归
        if (node == nullptr)
            return nullptr;
        if(key == node->key)
            return &(node->value);

        else if (key < node->key)
            return search(node->left, key);
        else if (key > node->key)
            return search(node->right, key);
    }

    bool contain(Node* node, Key key){
        // 递归终止条件：节点为空或者找到key对应的节点时终止递归
        if (node == nullptr)
            return false;
        if(key == node->key)
            return true;
            
        else if(key < node->key)
            return contain(node->left, key);
        else if(key > node->key)
            return contain(node->right, key);
    }
};

// 测试二分搜索树和顺序查找表之间的性能差距
// 二分搜索树的性能远远优于顺序查找表
int main() {

    // 使用圣经作为我们的测试用例
    string filename = "bible.txt";
    vector<string> words;
    if( FileOps::readFile(filename, words) ) {

        cout << "There are totally " << words.size() << " words in " << filename << endl;
        cout << endl;

        // 测试 BST
        time_t startTime = clock();

        // 统计圣经中所有词的词频
        // 注: 这个词频统计法相对简陋, 没有考虑很多文本处理中的特殊问题
        // 在这里只做性能测试用
        BST<string, int> bst = BST<string, int>();
        for (vector<string>::iterator iter = words.begin(); iter != words.end(); iter++) {
            int *res = bst.search(*iter);
            if (res == NULL)
                bst.insert(*iter, 1);
            else
                (*res)++;
        }

        // 输出圣经中god一词出现的频率
        if(bst.contain("god"))
            cout << "'god' : " << *bst.search("god") << endl;
        else
            cout << "No word 'god' in " << filename << endl;

        time_t endTime = clock();

        cout << "BST , time: " << double(endTime - startTime) / CLOCKS_PER_SEC << " s." << endl;
        cout << endl;


        // 测试顺序查找表 SST
        startTime = clock();

        // 统计圣经中所有词的词频
        // 注: 这个词频统计法相对简陋, 没有考虑很多文本处理中的特殊问题
        // 在这里只做性能测试用
        SequenceST<string, int> sst = SequenceST<string, int>();
        for (vector<string>::iterator iter = words.begin(); iter != words.end(); iter++) {
            int *res = sst.search(*iter);
            if (res == NULL)
                sst.insert(*iter, 1);
            else
                (*res)++;
        }

        // 输出圣经中god一词出现的频率
        if(sst.contain("god"))
            cout << "'god' : " << *sst.search("god") << endl;
        else
            cout << "No word 'god' in " << filename << endl;

        endTime = clock();

        cout << "SST , time: " << double(endTime - startTime) / CLOCKS_PER_SEC << " s." << endl;
    }

    return 0;
}