#include <iostream>
#include <vector>
using namespace std;
const int N = 31; // Số lượng phần tử từ 1 đến 31
struct DynamicArrayTree {
    vector<int> data; 
};
// Khởi tạo mảng động (bỏ qua index 0)
void initArrayTree(DynamicArrayTree &t) {
    t.data.clear();
    t.data.push_back(-1); 
}
// 1.1 Cài đặt cây đầy đủ bằng mảng động
void buildFullTreeArray(DynamicArrayTree &t) {
    initArrayTree(t);
    t.data.resize(N + 1, -1); 
    for(int i = 1; i <= N; i++) {
        t.data[i] = i; 
    }
}
// 1.2 Cài đặt cây lệch trái bằng mảng động
void buildLeftSkewedArray(DynamicArrayTree &t) {
    initArrayTree(t);
    int currentIndex = 1; 
    for(int val = 1; val <= N; val++) {
        if (currentIndex > 2000) break; // Chặn an toàn
        if (currentIndex >= t.data.size()) {
            t.data.resize(currentIndex + 1, -1);
        }
        t.data[currentIndex] = val;
        currentIndex = 2 * currentIndex; 
    }
}
// 1.3 Cài đặt cây lệch phải bằng mảng động
void buildRightSkewedArray(DynamicArrayTree &t) {
    initArrayTree(t);
    int currentIndex = 1; 
    for(int val = 1; val <= N; val++) {
        if (currentIndex > 2000) break; // Chặn an toàn
        if (currentIndex >= t.data.size()) {
            t.data.resize(currentIndex + 1, -1);
        }
        t.data[currentIndex] = val;
        currentIndex = 2 * currentIndex + 1; 
    }
}
void printArrayTreeInfo(DynamicArrayTree t, string name) {
    cout << name << " -> Kich thuoc mang dong can dung: " << t.data.size() - 1 << " o nho.\n";
    cout << "Cac phan tu thuc te: ";
    for(size_t i = 1; i < t.data.size(); i++) {
        if(t.data[i] != -1) cout << t.data[i] << " ";
    }
}
struct Node {
    int data;
    Node* left;
    Node* right;
};

// Hàm tạo nút mới
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
// Duyệt Pre-order
void preOrder(Node* root) {
    if(root != NULL) {
        cout << root->data << " ";
        preOrder(root->left);
        preOrder(root->right);
    }
}
// Giải phóng bộ nhớ cây con trỏ
void freeTree(Node* root) {
    if(root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    delete root;
}

int main() {
    cout << "CAU TRUC LUU TRU TUAN TU\n";
    DynamicArrayTree arrTree;
    buildFullTreeArray(arrTree);
    printArrayTreeInfo(arrTree, "[1.1] Cay day du");
    buildLeftSkewedArray(arrTree);cout << "\n";
    printArrayTreeInfo(arrTree, "[1.2] Cay lech trai");
    buildRightSkewedArray(arrTree);cout << "\n";
    printArrayTreeInfo(arrTree, "[1.3] Cay lech phai");cout << "\n";
    cout << "CAU TRUC LUU TRU MOC NOI\n";
    cout << "[2.1] Cay day du Duyet Pre-order : ";
    Node* linkedFull = buildFullTreeLinked(); preOrder(linkedFull); cout << "\n";
    cout << "[2.2] Cay lech trai Duyet Pre-order: ";
    Node* linkedLeft = buildLeftSkewedLinked(); preOrder(linkedLeft); cout << "\n";
    cout << "[2.3] Cay lech phai Duyet Pre-order: ";
    Node* linkedRight = buildRightSkewedLinked(); preOrder(linkedRight); cout << "\n";
    cout << "[2.4] Cay Zigzac duyet Pre-order   : ";
    Node* linkedZigzag = buildZigzagLinked(); preOrder(linkedZigzag); cout << "\n\n";
    // Dọn dẹp bộ nhớ con trỏ
    freeTree(linkedFull); freeTree(linkedLeft); 
    freeTree(linkedRight); freeTree(linkedZigzag);
    
    return 0;
}