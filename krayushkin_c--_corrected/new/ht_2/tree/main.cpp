#include <iostream>
#include <memory>

class tree {
    struct Node {
        std::weak_ptr<Node> parent;
        std::shared_ptr<Node> child_left;
        std::shared_ptr<Node> child_right;
        int value;
        Node(const int& Value) : value(Value) {}

        ~Node() {
            std::cout << "Node с значением: " << value << " удалён" << std::endl;
        }
    };


public:
    std::shared_ptr<Node> head;
    std::shared_ptr<Node> iter;

    tree(const int& Value) {
        head = std::make_shared<Node>(Value);
        iter = head;
    }

    int& get_value(){
        return iter->value;
    }
    void left_went() {
        iter = iter->child_left;
    }

    void right_went() {
        iter = iter->child_right;
    }

    void add_left(const int& Value) {
        iter->child_left = std::make_shared<Node>(Value);
        iter->child_left->parent = std::weak_ptr<Node>(iter);
    }

    void add_right(const int& Value) {
        iter->child_right = std::make_shared<Node>(Value);
        iter->child_right->parent = std::weak_ptr<Node>(iter);
    }

    void to_head() {
        iter = head;
    }
};

int main() {
    tree tree(5);
    tree.add_left(7);
    tree.add_left(5);
    tree.left_went();
    tree.add_right(13);
    tree.right_went();
    tree.add_right(12);
    tree.to_head();
    tree.add_left(3);
    std::cout << tree.get_value() << std::endl;
}