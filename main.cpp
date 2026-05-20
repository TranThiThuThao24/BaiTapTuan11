#include <iostream>
#include <cmath>
using namespace std;
const int N = 31; // Số lượng phần tử từ 1 đến 31
// 1.cau truc luu tru tuan tu
struct ArrayTree {
    int data[2000]; 
    int maxIndex;   
};
void initArrayTree(ArrayTree &t) {
    for(int i = 0; i < 2000; i++) {
        t.data[i] = -1; 
    }
    t.maxIndex = 0;
}
// 1.1 Cài đặt cây đầy đủ bằng mảng
void buildFullTreeArray(ArrayTree &t) {
    initArrayTree(t);
    for(int i = 1; i <= N; i++) {
        t.data[i] = i; // Nút i nằm đúng vị trí i luôn
    }
    t.maxIndex = N;
}
// 1.2 Cài đặt cây lệch trái bằng mảng
void buildLeftSkewedArray(ArrayTree &t) {
    initArrayTree(t);
    int currentIndex = 1; // Gốc ở 1
    for(int val = 1; val <= N; val++) {
        t.data[currentIndex] = val;
        t.maxIndex = currentIndex;
        currentIndex = 2 * currentIndex; // Con trái luôn là 2*i
    }
}
// 1.3 Cài đặt cây lệch phải bằng mảng
void buildRightSkewedArray(ArrayTree &t) {
    initArrayTree(t);
    int currentIndex = 1; // Gốc ở 1
    for(int val = 1; val <= N; val++) {
        t.data[currentIndex] = val;
        t.maxIndex = currentIndex;
        currentIndex = 2 * currentIndex + 1; // Con phải luôn là 2*i + 1
    }
}

// In mảng lưu trữ để giáo viên thấy sự lãng phí bộ nhớ của cây lệch
void printArrayTreeRaw(ArrayTree t) {
    cout << "Cac vi tri thuc te trong mang (chi in 1 so vi tri dau/cuoi):\n";
    for(int i = 1; i <= t.maxIndex; i++) {
        if(t.data[i] != -1) {
            cout << "Index [" << i << "]: " << t.data[i] << " | ";
        }
    }
    cout << "\n-> Chi so lon nhat phai dung trong mang: " << t.maxIndex << "\n";
}
//2. cai truc luu tru moc noi
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
    // Tạo sẵn các nút
    for(int i = 1; i <= N; i++) {
        refs[i] = createNode(i);
    }
    // Nối các nút lại theo quy thức 2*i và 2*i+1
    for(int i = 1; i <= N / 2; i++) {
        if(2 * i <= N)   refs[i]->left = refs[2 * i];
        if(2 * i + 1 <= N) refs[i]->right = refs[2 * i + 1];
    }
    return refs[1]; // Trả về nút gốc
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
// 2.4 Cài đặt cây Zigzac bằng con trỏ (Trái -> Phải -> Trái...)
Node* buildZigzagLinked() {
    Node* root = createNode(1);
    Node* current = root;
    for(int i = 2; i <= N; i++) {
        if(i % 2 == 0) { // Bước chẵn dạt sang trái
            current->left = createNode(i);
            current = current->left;
        } else {         // Bước lẻ dạt sang phải
            current->right = createNode(i);
            current = current->right;
        }
    }
    return root;
}
// Hàm duyệt cây theo thứ tự trước (Pre-order) để kiểm tra cấu trúc móc nối
void preOrder(Node* root) {
    if(root != NULL) {
        cout << root->data << " ";
        preOrder(root->left);
        preOrder(root->right);
    }
}

// Hàm giải phóng bộ nhớ cây con trỏ
void freeTree(Node* root) {
    if(root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    delete root;
}
int main() {
    cout << "CAU TRUC LUU TRU TUAN TU \n";
    ArrayTree arrTree;
    cout << "\n[1.1] Cay day du (Array):";
    buildFullTreeArray(arrTree);
    printArrayTreeRaw(arrTree);
    cout << "\n[1.2] Cay lech trai (Array):";
    buildLeftSkewedArray(arrTree);
    printArrayTreeRaw(arrTree);
    cout << "\n[1.3] Cay lech phai (Array):";
    buildRightSkewedArray(arrTree);
    printArrayTreeRaw(arrTree);
    cout << "CAU TRUC LUU TRU MOC NOI )\n";
    cout << "\n[2.1] Cay day du duyet Pre-order: ";
    Node* linkedFull = buildFullTreeLinked();
    preOrder(linkedFull); cout << "\n";
    cout << "[2.2] Cay lech trai duyet Pre-order: ";
    Node* linkedLeft = buildLeftSkewedLinked();
    preOrder(linkedLeft); cout << "\n";
    cout << "[2.3] Cay lech phai duyet Pre-order: ";
    Node* linkedRight = buildRightSkewedLinked();
    preOrder(linkedRight); cout << "\n";
    cout << "[2.4] Cay Zigzac duyet Pre-order: ";
    Node* linkedZigzag = buildZigzagLinked();
    preOrder(linkedZigzag); cout << "\n";
    
    // Giải phóng con trỏ dọn dẹp bộ nhớ
    freeTree(linkedFull);
    freeTree(linkedLeft);
    freeTree(linkedRight);
    freeTree(linkedZigzag);
    
    return 0;
}