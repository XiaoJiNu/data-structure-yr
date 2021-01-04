#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <cassert>

using namespace std;

template <typename Key, typename Value>
class BST{
private:
    // 创建一个结点结构体
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
        // 传入一个节点构造一个新节点
        Node(Node* node){
            this -> key = node -> key;
            this -> value = node -> value;
            left = right = nullptr;
        }
    };

    Node *root;  // 创建树的根节点
    int count;   // 用于计算树的节点个数

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

    // 删除最大节点
    void removeMax(){
        if (root == nullptr)
            return;
        else 
            root = removeMax(root);
            return;
    }

    // 删除任意节点
    void remove(Key key){
        // 删除节点后最终返回树的根节点赋值给root，完成删除操作
        root = remove(root, key);
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

    // 删除任意节点，返回删除后的根节点
    Node* remove(Node* node, Key key){
        if (key < node->key){
        // 如果key小于当前节点key，递归删除左子树的节点key，并将返回值赋值给左节点
            node -> left = remove(node->left, key);
            return node;
        }
        else if (key > node->key){
            // 如果key大于当前节点key，递归删除左子树的节点key，并将返回值赋值给右节点
            node -> right = remove(node->right, key);
            return node;
        }
        else{  // 如果key等于当前节点key，删除当前节点key
            if (node->left == nullptr){  
                // 如果左子节点为空，保存右子节点，删除当前节点，返回保存的右子节点(即替换当前节点)
                Node* rightNode = node -> right;
                delete node;
                count --;
                return rightNode;
            }
            else if (node->right == nullptr){  
                // 如果右子节点为空，保存左子节点，删除当前节点，返回保存的左子节点(即替换当前节点)
                Node* leftNode = node -> left;
                delete node;
                count --;
                return leftNode;
            }
            else{ 
                // 左右子节点都不为空，找到后继节点替换当前节点
                // 生成当前节点的后继节点，即复制当前节点右子树中最小节点
                Node* successor = new Node(minimum(node->right));
                count ++;
                successor -> right = removeMin(node->right);  // 将后继节点的右节点指向当前节点右子
                                                              // 树删除最小节点后子树
                successor -> left = node -> left;             // 将后继节点的右节点指向当前节点左子树
                delete node;                                  // 删除当前节点   
                count --;
                return successor;                             // 返回successor，它将赋值给当前节点父节点
                                                              // 的子节点中递归下来的子节点
            }
        }
    }
};

void shuffle( int arr[], int n ){

    srand( time(NULL) );
    for( int i = n-1 ; i >= 0 ; i -- ){
        int x = rand()%(i+1);
        swap( arr[i] , arr[x] );
    }
}

// 测试 remove
int main() {

    srand(time(NULL));
    BST<int,int> bst = BST<int,int>();

    // 取n个取值范围在[0...n)的随机整数放进二分搜索树中
    int n = 10000;
    for( int i = 0 ; i < n ; i ++ ){
        int key = rand()%n;
        // 为了后续测试方便,这里value值取和key值一样
        int value = key;
        bst.insert(key,value);
    }
    // 注意, 由于随机生成的数据有重复, 所以bst中的数据数量大概率是小于n的

    // order数组中存放[0...n)的所有元素
    int order[n];
    for( int i = 0 ; i < n ; i ++ )
        order[i] = i;
    // 打乱order数组的顺序
    shuffle( order , n );

    // 乱序删除[0...n)范围里的所有元素
    for( int i = 0 ; i < n ; i ++ )
        if( bst.contain( order[i] )){
            bst.remove( order[i] );
            cout<<"After remove "<<order[i]<<" size = "<<bst.size()<<endl;
        }

    // 最终整个二分搜索树应该为空
    cout << bst.size() << endl;

    return 0;
}