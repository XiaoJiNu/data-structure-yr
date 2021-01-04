#include <iostream>
#include <vector>
#include <string>
#include "SequenceST.h"
#include "FileOps.h"

using namespace std;

// 二分搜索树
// template <typename Key, typename Value>
// class BST{

// private:
//     // 树中的节点为私有的结构体, 外界不需要了解二分搜索树节点的具体实现
//     struct Node{
//         Key key;
//         Value value;
//         Node *left;
//         Node *right;

//         Node(Key key, Value value){
//             this->key = key;
//             this->value = value;
//             this->left = this->right = NULL;
//         }
//     };

//     Node *root; // 根节点
//     int count;  // 树中的节点个数

// public:
//     // 构造函数, 默认构造一棵空二分搜索树
//     BST(){
//         root = NULL;
//         count = 0;
//     }
//     ~BST(){
//         // TODO: ~BST()
//     }

//     // 返回二分搜索树的节点个数
//     int size(){
//         return count;
//     }

//     // 返回二分搜索树是否为空
//     bool isEmpty(){
//         return count == 0;
//     }

//     // 向二分搜索树中插入一个新的(key, value)数据对
//     void insert(Key key, Value value){
//         root = insert(root, key, value);
//     }

//     // 查看二分搜索树中是否存在键key
//     bool contain(Key key){
//         return contain(root, key);
//     }

//     // 在二分搜索树中搜索键key所对应的值。如果这个值不存在, 则返回NULL
//     Value* search(Key key){
//         return search( root , key );
//     }

// private:
//     // 向以node为根的二分搜索树中, 插入节点(key, value), 使用递归算法
//     // 返回插入新节点后的二分搜索树的根
//     Node* insert(Node *node, Key key, Value value){

//         if( node == NULL ){
//             count ++;
//             return new Node(key, value);
//         }

//         if( key == node->key )
//             node->value = value;
//         else if( key < node->key )
//             node->left = insert( node->left , key, value);
//         else    // key > node->key
//             node->right = insert( node->right, key, value);

//         return node;
//     }

//     // 查看以node为根的二分搜索树中是否包含键值为key的节点, 使用递归算法
//     bool contain(Node* node, Key key){

//         if( node == NULL )
//             return false;

//         if( key == node->key )
//             return true;
//         else if( key < node->key )
//             return contain( node->left , key );
//         else // key > node->key
//             return contain( node->right , key );
//     }

//     // 在以node为根的二分搜索树中查找key所对应的value, 递归算法
//     // 若value不存在, 则返回NULL
//     Value* search(Node* node, Key key){

//         if( node == NULL )
//             return NULL;

//         if( key == node->key )
//             return &(node->value);
//         else if( key < node->key )
//             return search( node->left , key );
//         else // key > node->key
//             return search( node->right, key );
//     }
// };


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

    // ----------版本一----------
    void insert(Key key, Value value){
        insert(root, key, value);
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
    // ----------版本一----------
    // void insert(Node *node, Key key, Value value){
    //     if(key == node->key){
    //         node -> value = value;
    //         return;
    //     }
    //     // 如果小于节点且左子节点为空，则生成一个节点并将结点赋值给左节点
    //     // 如果大于节点且右子节点为空，则生成一个节点并将结点赋值给右节点
    //     // 其余情况则递归调用insert函数
    //     else if(key < node->key){
    //         if(node->left != nullptr)
    //             insert(node -> left, key, value);
    //         else(node->left == nullptr){
    //             Node *newNode = new Node(key, value);
    //             node -> left = newNode;
    //             count ++;
    //             return;
    //         }
    //     }
    //     else if(key > node->key){
    //         if(node->right != nullptr)
    //             insert(node -> right, key, value);
    //         else(node->right == nullptr){
    //             Node *newNode = new Node(key, value);
    //             node -> right = newNode;
    //             count ++;
    //             return;
    //         }
    //     }
    // }

      void insert(Node *node, Key key, Value value){
        if(key == node->key){
            node -> value = value;
            return;
        }
        // 如果小于节点且左子节点为空，则生成一个节点并将结点赋值给左节点
        else if(key < node->key && node->left == nullptr){
            Node* newNode = new Node(key, value);
            node -> left = newNode;
            count ++;
            return;
        }
        // 如果大于节点且右子节点为空，则生成一个节点并将结点赋值给右节点
        else if(key > node->key && node->right == nullptr){
            Node* newNode = new Node(key, value);
            node -> right = newNode;
            count ++;
            return;
        }
        // 其余情况则递归调用insert函数
        else if(key < node->key && node->left != nullptr)
            insert(node->left, key, value);
        else if(key > node->key && node->left != nullptr)
            insert(node->right, key, value);

    }

    bool contain(Node* node, Key key){
        // 当打到key或者已经递归到叶子节点仍然没有找到key时终止递归
        if(key == node->key)
            return true;
        else if(key != node->key && node->left == nullptr \
                && node->right == nullptr)
            return false;
        // 小于节点的key则往左子节点递归
        else if(key < node->key && node->left != nullptr)
            return contain(node->left, key);
        // 大于于节点的key则往右子节点递归
        else if(key > node->key && node->right != nullptr)
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