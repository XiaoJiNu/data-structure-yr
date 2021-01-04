#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <cassert>

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

    void levelTraverse(){
        levelTraverse(root);
    }

    // 求最小值，返回最小值的key
    Key minimum(){
        assert(root != nullptr);        // 树不能为空
        Node* minNode = minimum(root);  // 返回最小值节点
        return minNode -> key;          // 返回最小节点的key
    }

    // 求最小值，返回最小值的key
    Key maximum(){
        assert(root != nullptr);
        Node* maxNode = maximum(root);
        return maxNode -> key;
    }

    // 删除最小节点
    void removeMin(){
        if (root == nullptr)
            return;                   // 如果根结点为空，直接终止函数
        else
            root = removeMin(root);   // 将删除后的树的根节点重新赋值给root
            return;
    }

    void removeMax(){
        if (root == nullptr)
            return;
        else 
            root = removeMax(root);
            return;
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

    // 层序遍历
    void levelTraverse(Node* root){
        // 将根节点压入队列
        queue<Node*> Q = queue<Node*>();
        Q.push(root);
        // 当队列不为空时，一直遍历二分搜索树
        while(!Q.empty()){
            // 队首元素出队并输出
            // ### void value not ignored as it ought to be
            // 注意，pop()并不会返回被弹出元素的值，所以直接pop()后不能赋值给firstQNode
            // Node* firstQNode = Q.pop();
            Node* firstQNode = Q.front();  // 返回队首元素赋值给firstQNode
            Q.pop();                       // 弹出队首元素
            cout << firstQNode -> key << endl;
            // 将弹出元素中不为空的子节点压入队列
            if (firstQNode -> left != nullptr)
                Q.push(firstQNode -> left);
            if (firstQNode -> right != nullptr)
                Q.push(firstQNode -> right);
        }
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

    // 返回最小节点
    Node* minimum(Node* node){
        if (node->left == nullptr)
            return node;
        else 
            return minimum(node-> left);
    }

    // 返回最大节点
    Node* maximum(Node* node){
        if (node->right == nullptr)
            return node;
        else
            return maximum(node->right);
    }

    // 删除最小节点，返回删除后的根节点 
    Node* removeMin(Node* node){
        // 向左递归到左子节点为空的节点，该节点为最小节点
        if (node->left == nullptr){
            Node* rightNode = node -> right;  // 最小节点没有左子节点，将右子节点保存下来
            delete node;
            count --; 
            return rightNode;                 // 将删除节点的右子节点返回，赋值给级节点左子节点
        }
        else
            // 由于删除了节点，每次将递归返回的节点赋值给当前节点的左子节点
            node -> left = removeMin(node->left);
        return node;                          // 每次返回当前访问的节点，最终返回根节点
    }
    
    Node* removeMax(Node* node){
        if (node->right == nullptr){
            Node* leftNode = node -> left;    // 最大节点没有右子节点，将左子节点保存下来
            delete node;
            count --;
            return leftNode;
        }
        else
            node -> right = removeMax(node->right);
        return node;
        
    }
};


// 测试二分搜索树中的removeMin和removeMax
int main() {

    srand(time(NULL));
    BST<int,int> bst = BST<int,int>();

    // 取n个取值范围在[0...m)的随机整数放进二分搜索树中
    int n = 100;
    int m = 100;
    for( int i = 0 ; i < n ; i ++ ){
        int key = rand()%m;
        // 为了后续测试方便,这里value值取和key值一样
        int value = key;
        //cout<<key<<" ";
        bst.insert(key,value);
    }
    // 注意, 由于随机生成的数据有重复, 所以bst中的数据数量大概率是小于n的

    // 测试 removeMin
    // 输出的元素应该是从小到大排列的
    cout<<"Test removeMin: "<<endl;
    while( !bst.isEmpty() ){
        cout<<"min: "<<bst.minimum()<<" , ";
        bst.removeMin();
        cout<<"After removeMin, size = "<<bst.size()<<endl;
    }
    cout << endl;


    for( int i = 0 ; i < n ; i ++ ){
        int key = rand()%n;
        // 为了后续测试方便,这里value值取和key值一样
        int value = key;
        //cout<<key<<" ";
        bst.insert(key,value);
    }
    // 注意, 由于随机生成的数据有重复, 所以bst中的数据数量大概率是小于n的

    // 测试 removeMax
    // 输出的元素应该是从大到小排列的
    cout<<"Test removeMax: "<<endl;
    while( !bst.isEmpty() ){
        cout<<"max: "<<bst.maximum()<<" , ";
        bst.removeMax();
        cout<<"After removeMax, size = "<<bst.size()<<endl;
    }

    return 0;
}