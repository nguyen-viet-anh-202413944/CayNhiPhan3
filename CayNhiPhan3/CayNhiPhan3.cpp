#include <iostream>
using namespace std;
/*
Bài 1: Mục lục của một cuốn sách được lưu trữ dưới dạng một cây trong đó mỗi node có thể là chapter (chương), section (mục), subsection (mục con), subsubsection (các mục của mục con).
Khai báo cấu trúc cây để biểu diễn cuốn sách. Các thông tin chứa ở mỗi node sinh viên tự đưa vào (Gợi ý: có thể dùng số để đánh index cho các phần) để đảm bảo các nội dung sau được thực hiện:
1.	Xác định số chương của cuốn sách
2.	Tìm chương dài nhất của cuốn sách
3.	Thực hiện tìm một mục và xoá mục đó khỏi sách. Lưu ý cập nhật lại số trang của từng mục.
4.	Tìm một chương bất kỳ và in ra đề mục của chương đó
Bài 2: Thiết kế giải thuật để kiểm tra hai cuốn sách có phải là bản copy của nhau không (Gợi ý: Mỗi node chưa 2 thuộc tính là index dạng số, và tên mục dạng chuỗi ký tự)
Điều kiện:
1. Tạo 2 cây nhị phân bất kỳ để lưu chữ mục lục chứa đầu mục chương và các mục con
2. Kiểm tra từng node của cây nhị phân, nếu tất cả các nút trên cây nhị phân đều có giá trị như nhau thì hai cây nhị phân được gọi là giống nhau do đó in ra kết luận “hai cuốn sách là bản copy của nhau”
3. Tính độ phức tạp của giải thuật đề xuất và thời gian thực thi chương trình khi số mục con của quyển sách tăng lên N cấp
*/
struct Node
{
	int index;    
	char type;  // chapter, section, subsection, subsubsection
	char name[100]; // ten de muc
	Node* left;  
	Node* right; 

	Node(int v, Node* l, Node* r, char t, const char* n) // <-- change char* n to const char* n
	{
		index = v;
		left = l;
		right = r;
		type = t;
		strcpy_s(name, n);
	}
};

class Book
{
private:
	Node* root;
public:
	// Ham tao (ban dau cay rong).
	Book(Node* r = nullptr)
	{
		root = r;
	}

	// Kiem tra cay co rong hay khong.
	bool isEmpty() {
		return root == nullptr;
	}

	// Chen mot nut val1 moi vao cay.
	void insert(int val1, char type, char* n)
	{
		return insert(val1, root, type, n);
	}
	// Tra ve gia tri root
	Node* getRoot() {
		return root;
	}

	// Tim nut val2
	Node* search(int val2)
	{
		return search(val2, root);
	}

	// Chen mot nut val1 moi vao cay (viet theo kieu de quy).
	void insert(int val1, Node*& t, char type, char* n) {
		Node* newNode = new Node(val1, nullptr, nullptr, type, n);
		if (t == nullptr) {
			t = newNode;
			return;
		}
		if (val1 < t->index) {
			insert(val1, t->left, type, n);
		}
		else if (val1 > t->index) {
			insert(val1, t->right, type, n);
		}
	}

	// Tim kiem nut co gia tri cho truoc  (viet theo kieu de quy).
	Node* search(int val2, Node* t) {
		if (val2 == t->index) {
			return t;
		}
		else if (val2 < t->index) {
			if (t->left != nullptr) {
				return search(val2, t->left);
			}
			else {
				return nullptr;
			}
		}
		else {
			if (t->right != nullptr) {
				return search(val2, t->right);
			}
			else {
				return nullptr;
			}
		}
	}
	
	// Dem so chuong trong cuon sach
	int countChapters() {
		if (root == nullptr) {
			return 0;
		}
		else {
			if (root->type == 'C') {
				return 1 + countChapters(root->left) + countChapters(root->right);
			}
			else {
				return countChapters(root->left) + countChapters(root->right);
			}
		}
		
	}
	int countChapters(Node* t) {
		if (t == nullptr) {
			return 0;
		}
		else {
			if (t->type == 'C') {
				return 1 + countChapters(t->left) + countChapters(t->right);
			}
			else {
				return countChapters(t->left) + countChapters(t->right);
			}
		}
	}

	//Tim chuong dai nhat trong cuon sach
	char* longestChapter() {
		if (root == nullptr) {
			return nullptr;
		}
		else {
			char* longest = root->name;
			int maxLength = 0;
			longestChapter(root, root, maxLength, longest);
			cout << "Ten chuong dai nhat: " << longest << endl;
			cout << "Do dai chuong: " << maxLength << endl;
			return longest;
		}
	}
	void longestChapter(Node* t, Node* p, int maxLength, char* name) {
		if (t == nullptr) return;
		if (t->type == 'C'){
			int length = t->index - p->index;
			if (length > maxLength) {
				name = t->name;
				maxLength = length;
			}
		}
		longestChapter(t->left, t, maxLength, name);
		longestChapter(t->right, t, maxLength, name);
	}

	//Xoa mot muc khoi cuon sach
	void deleteNode(int index, char type) {
		root = deleteNode(root, index, type);
	}
	Node* deleteNode(Node* t, int index, char type) {
		if (t == nullptr) return t;
		if (index < t->index) {
			t->left = deleteNode(t->left, index, type);
		}
		else if (index > t->index) {
			t->right = deleteNode(t->right, index, type);
		}
		else {
			// Gan lai khi tim thay nut can xoa
			if (t->type == type) {
				if (t->left == nullptr) {
					Node* temp = t->right;
					delete t;
					return temp;
				}
				else if (t->right == nullptr) {
					Node* temp = t->left;
					delete t;
					return temp;
				}
				Node* temp = minValueNode(t->right);
				t->index = temp->index;
				t->type = temp->type;
				strcpy_s(t->name, temp->name);
				t->right = deleteNode(t->right, temp->index, temp->type);
			}
		}
		return t;
	}
	Node* minValueNode(Node* t) {
		Node* current = t;
		while (current && current->left != nullptr) {
			current = current->left;
		}
		return current;
	}

	// So sanh hai cuon sach co phai la ban sao cua nhau khong
	bool areIdentical(Node* t1, Node* t2) {
		if (t1 == nullptr && t2 == nullptr) {
			return true;
		}
		if (t1 == nullptr || t2 == nullptr) {
			return false;
		}
		return (t1->index == t2->index && strcmp(t1->name, t2->name) == 0 &&
			areIdentical(t1->left, t2->left) &&
			areIdentical(t1->right, t2->right));
	}
	// Do phuc tap cua giai thuat la O(N) voi N la so nut trong cay

};
//Test
int main() {
	Book book1;
	Book book2;
	Node* root1 = new Node(1, nullptr, nullptr, 'C', "Chapter 1");
	Node* root2 = new Node(1, nullptr, nullptr, 'C', "Chapter 1");
	Node* root3 = new Node(1, nullptr, nullptr, 'C', "Chapter 2");
	book1 = Book(root1);
	book2 = Book(root2);
	if (book1.areIdentical(book1.getRoot(), book2.getRoot())) {
		cout << "Hai cuon sach la ban copy cua nhau." << endl;
	}
	else {
		cout << "Hai cuon sach khong phai la ban copy cua nhau." << endl;
	}
	book1 = Book(root3);
	if (book1.areIdentical(book1.getRoot(), book2.getRoot())) {
		cout << "Hai cuon sach la ban copy cua nhau." << endl;
	}
	else {
		cout << "Hai cuon sach khong phai la ban copy cua nhau." << endl;
	}
	return 0;
}