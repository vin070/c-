#include <climits>
#include <cmath>
#include <iostream>
#include <queue>

template <typename T> class binary_tree {
  T data;
  binary_tree<T> *left_node;
  binary_tree<T> *right_node;

public:
  binary_tree(T data) {
    this->data = data;
    left_node = NULL;
    right_node = NULL;
  }

  void update_data(T data) { this->data = data; }

  T get_data() const { return data; }

  void update_left_node(binary_tree<T> *const left_node) {
    this->left_node = left_node;
  }

  void update_right_node(binary_tree<T> *const right_node) {
    this->right_node = right_node;
  }

  binary_tree<T> *get_left_node() const { return left_node; }
  binary_tree<T> *get_right_node() const { return right_node; }

  static binary_tree<T> *take_input_levelwise() {
    int root_data = -1;
    std::cin >> root_data;
    if (root_data == -1)
      return NULL;
    binary_tree<T> *root = new binary_tree<T>(root_data);
    std::queue<binary_tree<T> *> q;
    q.push(root);

    while (!q.empty()) {
      binary_tree<T> *curr_node = q.front();
      q.pop();
      int left_child = -1, right_child = -1;
      std::cin >> left_child;
      if (left_child != -1) {
        binary_tree<T> *left_node = new binary_tree<T>(left_child);
        curr_node->update_left_node(left_node);
        q.push(left_node);
      }

      std::cin >> right_child;
      if (right_child != -1) {
        binary_tree<T> *right_node = new binary_tree<T>(right_child);
        curr_node->update_right_node(right_node);
        q.push(right_node);
      }
    }
    return root;
  }

  ~binary_tree() {
    delete left_node;
    delete right_node;
  }
};

template <typename T>
std::pair<int, int> get_min_and_max(binary_tree<T> *root) {
  if (!root) {
    std::pair<int, int> p(INT_MAX, INT_MIN);
    return p;
  }

  std::pair<int, int> left_ans = get_min_and_max(root->get_left_node());
  std::pair<int, int> right_ans = get_min_and_max(root->get_right_node());
  int min = std::min(root->get_data(), std::min(left_ans.first, right_ans.first));
  int max = std::max(root->get_data(), std::max(left_ans.second, right_ans.second));
  std::pair<int, int> p(min, max);
  return p;
}

int main() {
  binary_tree<int> *root = binary_tree<int>::take_input_levelwise();
  std::pair<int, int> p = get_min_and_max<int>(root);
  std::cout << p.first << " " << p.second << '\n';
  delete root;
  return 0;
}