#include <iostream>
#include <vector>
#include <string>


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

    ~BST(){
        destory(root);
    }

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

    // 前序遍历，为了隐藏实现细节，用户不需要操作具体的节点，
    // 这里真正的前序遍历函数为private
    void preOrder(){
        preOrder(root);
    }

    // 中序遍历
    void inOrder(){
        inOrder(root);
    }

    void postOrder(){
        postOrder(root);
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

    void preOrder(Node* node){
        // 递归终止条件：访问的节点为空时，终止递归
        if (node == nullptr)
            return;
        cout << node -> value << endl;
        preOrder(node -> left);
        preOrder(node -> right);
    }

    void inOrder(Node* node){
        if (node == nullptr)
            return;
        inOrder(node -> left);
        cout << node -> value << endl;
        inOrder(node -> right);
    }

    void postOrder(Node* node){
        if (node == nullptr)
            return;
        postOrder(node -> left);
        postOrder(node -> right);
        cout << node -> value << endl;
    }

    // 销毁二分搜索树，需要对每个节点进行delete，可以用递归方式进行
    // 只能采用后序遍历方式进行销毁，只有把子节点销毁后才能销毁根节点
    void destory(Node* node){
        if (node == nullptr)
            return;
        destory(node->left);
        destory(node->right);
        delete node;
        // ### 删除一个节点后需要对count减1
        count --;
    }
};

// 测试二分搜索树的前中后序遍历
int main() {
    // 创建一个二分搜索树
    BST<int, int> bst = BST<int, int>();

    srand(time(NULL));  // 给随机种子
    // 生成n个(0, 1 ... M)范围内的数
    int n = 10;
    int M = 100;
    for (int i = 0; i < n; i++) {
        int key = rand() % M;
        int value = key;
        bst.insert(key, value);
        cout << key << " ";
    }
    cout << endl;
    
    cout << "preOrder: " << endl;
    bst.preOrder();

    cout << "inOrder: " << endl;
    bst.inOrder();

    cout << "postOrder: " << endl;
    bst.postOrder();
    
    return 0;
}