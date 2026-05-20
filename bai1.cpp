#include <iostream>
#include <vector>
using namespace std;
const int N = 31; 
//1. cau truc luu tru tuan tu
struct DynamicArrayTree {
    vector<int> data; 
};
void initArrayTree(DynamicArrayTree &t) {
    t.data.clear();
    t.data.push_back(-1); // Bỏ qua index 0
}
// 1.1 Cài đặt cây đầy đủ bằng mảng động
void buildFullTreeArray(DynamicArrayTree &t) {
    initArrayTree(t);
    t.data.resize(N + 1, -1); 
    for(int i = 1; i <= N; i++) t.data[i] = i; 
}
// 1.2 Cài đặt cây lệch trái bằng mảng động (Chặn giới hạn 2000 ô nhớ)
void buildLeftSkewedArray(DynamicArrayTree &t) {
    initArrayTree(t);
    int currentIndex = 1; 
    for(int val = 1; val <= N; val++) {
        if (currentIndex > 2000) break; 
        if (currentIndex >= t.data.size()) t.data.resize(currentIndex + 1, -1);
        t.data[currentIndex] = val;
        currentIndex = 2 * currentIndex; 
    }
}
// 1.3 Cài đặt cây lệch phải bằng mảng động
void buildRightSkewedArray(DynamicArrayTree &t) {
    initArrayTree(t);
    int currentIndex = 1; 
    for(int val = 1; val <= N; val++) {
        if (currentIndex > 2000) break; 
        if (currentIndex >= t.data.size()) t.data.resize(currentIndex + 1, -1);
        t.data[currentIndex] = val;
        currentIndex = 2 * currentIndex + 1; 
    }
}
void printArrayTree(DynamicArrayTree t, string name) {
    cout << name << ": ";
    for(size_t i = 1; i < t.data.size(); i++) {
        if(t.data[i] != -1) cout << t.data[i] << " ";
    }
    cout << "\n";
}
// cau truc luu tru moc noi
struct Node {
    int data;
    Node* left;
    Node* right;
};
Node* createNode(int val) {
    Node* newNode = new Node();
    newNode->data = val;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}
// 2.1 Cài đặt cây đầy đủ bằng con trỏ
Node* buildFullTreeLinked() {
    Node* refs[N + 1];
    for(int i = 1; i <= N; i++) refs[i] = createNode(i);
    for(int i = 1; i <= N / 2; i++) {
        if(2 * i <= N)     refs[i]->left = refs[2 * i];
        if(2 * i + 1 <= N) refs[i]->right = refs[2 * i + 1];
    }
    return refs[1];
}
// 2.2 Cài đặt cây lệch trái bằng con trỏ
Node* buildLeftSkewedLinked() {
    Node* root = createNode(1);
    Node* current = root;
    for(int i = 2; i <= N; i++) {
        current->left = createNode(i);
        current = current->left;
    }
    return root;
}
// 2.3 Cài đặt cây lệch phải bằng con trỏ
Node* buildRightSkewedLinked() {
    Node* root = createNode(1);
    Node* current = root;
    for(int i = 2; i <= N; i++) {
        current->right = createNode(i);
        current = current->right;
    }
    return root;
}
// 2.4 Cài đặt cây Zigzac bằng con trỏ
Node* buildZigzagLinked() {
    Node* root = createNode(1);
    Node* current = root;
    for(int i = 2; i <= N; i++) {
        if(i % 2 == 0) {
            current->left = createNode(i);
            current = current->left;
        } else {
            current->right = createNode(i);
            current = current->right;
        }
    }
    return root;
}
// Duyệt Pre-order để in cây con trỏ
void preOrder(Node* root) {
    if(root != NULL) {
        cout << root->data << " ";
        preOrder(root->left);
        preOrder(root->right);
    }
}
void freeTree(Node* root) {
    if(root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    delete root;
}
int main() {
    DynamicArrayTree arrTree;
    cout << "Cau truc luu tru tuan tu\n";
    buildFullTreeArray(arrTree);   printArrayTree(arrTree, "Cay day du ");
    buildLeftSkewedArray(arrTree);  printArrayTree(arrTree, "Cay lech trai");
    buildRightSkewedArray(arrTree); printArrayTree(arrTree, "Cay lech phai");
    cout << "\nCau truc luu tru moc noi\n";
    cout << "Cay day du   : "; Node* linkedFull = buildFullTreeLinked(); preOrder(linkedFull); cout << "\n";
    cout << "Cay lech trai: "; Node* linkedLeft = buildLeftSkewedLinked(); preOrder(linkedLeft); cout << "\n";
    cout << "Cay lech phai: "; Node* linkedRight = buildRightSkewedLinked(); preOrder(linkedRight); cout << "\n";
    cout << "Cay Zigzac   : "; Node* linkedZigzag = buildZigzagLinked(); preOrder(linkedZigzag); cout << "\n";
    freeTree(linkedFull); freeTree(linkedLeft); 
    freeTree(linkedRight); freeTree(linkedZigzag);
    return 0;
}