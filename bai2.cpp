#include <iostream>
#include <string>
#include <stack>
using namespace std;
struct Node {
    char data;
    Node *left, *right;
};
Node* createNode(char val) {
    Node* newNode = new Node();
    newNode->data = val;
    newNode->left = newNode->right = NULL;
    return newNode;
}
// Hàm trả về độ ưu tiên của toán tử
int priority(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    if (op == '^') return 3;
    return 0;
}
// 1. Chuyển biểu thức Trung tố sang Hậu tố 
string infixToPostfix(string infix) {
    string postfix = "";
    stack<char> s;
    for (char c : infix) {
        if (isalpha(c)) { // Nếu là toán hạng (a, b, c...)
            postfix += c;
        } else if (c == '(') {
            s.push(c);
        } else if (c == ')') {
            while (!s.empty() && s.top() != '(') {
                postfix += s.top();
                s.pop();
            }
            if (!s.empty()) s.pop(); // Bỏ dấu '('
        } else { // Nếu là toán tử
            while (!s.empty() && priority(s.top()) >= priority(c)) {
                postfix += s.top();
                s.pop();
            }
            s.push(c);
        }
    }
    while (!s.empty()) {
        postfix += s.top();
        s.pop();
    }
    return postfix;
}
//  Dựng cây biểu thức từ chuỗi Hậu tố (Postfix)
Node* buildExpressionTree(string postfix) {
    stack<Node*> s;
    for (char c : postfix) {
        Node* t = createNode(c);
        if (isalpha(c)) { // Nếu là nút lá (toán hạng)
            s.push(t);
        } else { // Nếu là toán tử -> lấy 2 nút trên cùng của stack làm con
            t->right = s.top(); s.pop();
            t->left = s.top(); s.pop();
            s.push(t);
        }
    }
    return s.top(); // Nút gốc của cây biểu thức
}
//  hàm duyệt cây
void preOrder(Node* root) { // Duyệt trước (NLR) -> Biểu thức Tiền tố
    if (root != NULL) {
        cout << root->data << " ";
        preOrder(root->left);
        preOrder(root->right);
    }
}
void inOrder(Node* root) { // Duyệt giữa (LNR) -> Biểu thức Trung tố
    if (root != NULL) {
        if (!isalpha(root->data)) cout << "( "; // Thêm ngoặc cho dễ nhìn
        inOrder(root->left);
        cout << root->data << " ";
        inOrder(root->right);
        if (!isalpha(root->data)) cout << ") ";
    }
}
void postOrder(Node* root) { // Duyệt sau (LRN) -> Biểu thức Hậu tố
    if (root != NULL) {
        postOrder(root->left);
        postOrder(root->right);
        cout << root->data << " ";
    }
}
// Giải phóng bộ nhớ
void freeTree(Node* root) {
    if (root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    delete root;
}
int main() {
    string infix = "(a*b+c)/d-(e*f-h)^g";
    //Chuyển sang hậu tố
    string postfix = infixToPostfix(infix);
    //Dựng cây
    Node* root = buildExpressionTree(postfix);
    //In kết quả duyệt
    cout << "Bieu thuc goc: " << infix << "\n\n";
    cout << "Duyet truoc (Pre-order): ";
    preOrder(root); 
    cout << "\n\n";
    cout << "Duyet giua  (In-order) : ";
    inOrder(root); 
    cout << "\n\n";
    cout << "Duyet sau   (Post-order): ";
    postOrder(root); 
    cout << "\n";
    freeTree(root);
    return 0;
}