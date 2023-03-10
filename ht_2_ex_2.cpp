#include <iostream>
#include <iterator>
#include <list>

class Node: public std::enable_shared_from_this<A>{
public:
    Node(){
        parent = NULL;
    };
    ~Node() = default;

    void set_parent(std::shared_ptr<Node> par){
        this->parent = par;
    }
    void add_child(std::shared_ptr<Node> child){
        children->push_back(child);
        child->set_parent(share_from_this());
    };

private:
    std::list<std::shared_ptr<Node>> children;
    std::shared_ptr<Node> parent;
};

void make_relations(Node par, Node child){
    par.add_child(child);
    child.set_parent(par);
};


int main(){
    Node root;
    Node nod_11;
    Node nod_12;
    Node nod_21;
    Node nod_22;
    Node nod_23;
    Node nod_24;

    make_relations(root, nod_11);
    make_relations(root, nod_12);
    make_relations(nod_11, nod_21);
    make_relations(nod_12, nod_22);
    make_relations(nod_12, nod_23);
    make_relations(nod_12, nod_24);


};