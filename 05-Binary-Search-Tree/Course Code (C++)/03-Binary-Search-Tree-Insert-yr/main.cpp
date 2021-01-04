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

    // ----------版本一----------
    void insert(Key key, Value value){
        insert(root, key, value);
    }
    
    // ----------版本二----------
    void insert(Key key, Value value){
        root = insert(root, key, value);
    }

private:
    // 为了不让外部接触内部的节点结构体，
    // 真正的插入操作作为一个私有函数
    // ----------版本一----------
    void insert(Node *node, Key key, Value value){
        if(key == node->key){
            node -> value = value;
            return;
        }
        // 如果小于节点且左子节点为空，则生成一个节点并将结点赋值给左节点
        // 如果大于节点且右子节点为空，则生成一个节点并将结点赋值给右节点
        // 其余情况则递归调用insert函数
        else if(key < node->key){
            if(node->left != nullptr)
                insert(node -> left, key, value);
            else(node->left == nullptr){
                Node *newNode = new Node(key, value);
                node -> left = newNode;
                count ++;
                return;
            }
        }
        else if(key > node->key){
            if(node->right != nullptr)
                insert(node -> right, key, value);
            else(node->right == nullptr){
                Node *newNode = new Node(key, value);
                node -> right = newNode;
                count ++;
                return;
            }
        }
    }

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
        // 因为前面递归时对node的左右子节点进行赋值了，所以在最后进行返回
        // 如果没有赋值操作，直接将前面递归中赋值改成return即可
        return node;
    }

};


int main(){
    return 0;
}