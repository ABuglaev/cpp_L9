#include "pch.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>


using namespace std;

//node struct
struct person {
    int key;
    string name;
    string pass;
    string color;
    struct person* left;
    struct person* right;
};

//new node creation function
struct person *newNode(int _key, string _name, string _pass) {
    struct person* node = new person;
    node->key = _key;
    node->name = _name;
    node->pass = _pass;
    node->left = NULL;
    node->right = NULL;
    node->color = "black";
    return node;

}
//make root
person *root = newNode(0, "", "");

//add root to the tree
void addNode(person *_node) {
    root = newNode(_node->key, _node->name, _node->pass);
    root->color = "black";
    root->left = NULL;
    root->right = NULL;
}
//add node to tree/subtree function
void addNode(person _node, person *_subroot) {
    if (_node.key < _subroot->key) {
        if (!_subroot->left) {
            _subroot->left = newNode(_node.key, _node.name, _node.pass);
            return;
        }
        else {
            addNode(_node, _subroot->left);
        }
    }

    if (_node.key > _subroot->key) {
        if (!_subroot->right) {
            _subroot->right = newNode(_node.key, _node.name, _node.pass);
            return;
        }
        else {
            addNode(_node, _subroot->right);
        }
    }

}
//remove node by key || Caution!!! Don't even try to understand
int removeNode(int _key, person *_subroot) {
    if (_key == root->key) {
        person *leftmost = _subroot->right;
        person *leftmostParent = _subroot;
        person *temp = leftmost;

        if (_subroot->right->left == NULL) {
            _subroot->right->left = _subroot->left;
            root = _subroot->right;
            return 0;
        };

        while (temp->left) {
            leftmostParent = temp;
            leftmost = temp->left;
            temp = temp->left;
        }

        leftmostParent->left = leftmost->right;
        leftmost->left = _subroot->left;
        leftmost->right = _subroot->right;
        root = leftmost;

        return 0;
    }

    if (_key < _subroot->key) {
        if (removeNode(_key, _subroot->left) == 0) return 0;
        if (removeNode(_key, _subroot->left) == 1) {
            _subroot->left = NULL; return 0;
        }
        if (removeNode(_key, _subroot->left) == 2) {
            _subroot->left = _subroot->left->left; return 0;
        }
        if (removeNode(_key, _subroot->left) == 3) {
            _subroot->left = _subroot->left->right; return 0;
        }
        if (removeNode(_key, _subroot->left) == 4) {
            person *leftmost = _subroot->left->right;
            person *leftmostParent = _subroot->left;
            person *temp = leftmost;

            if (leftmost->left == NULL) {
                leftmost->left = leftmostParent->left;
                _subroot->left = leftmost;
                return 0;
            };

            while (temp->left) {
                leftmostParent = temp;
                leftmost = temp->left;
                temp = temp->left;
            }

            leftmostParent->left = leftmost->right;
            leftmost->left = _subroot->left->left;
            leftmost->right = _subroot->left->right;
            
            _subroot->left = leftmost;

            return 0;
        }
    }
    if (_key > _subroot->key) {
        if (removeNode(_key, _subroot->right) == 0) return 0;
        if (removeNode(_key, _subroot->right) == 1) {
            _subroot->right = NULL; return 0;
        }
        if (removeNode(_key, _subroot->right) == 2) {
            _subroot->right = _subroot->right->left; return 0;
        }
        if (removeNode(_key, _subroot->right) == 3) {
            _subroot->right = _subroot->right->right; return 0;
        }
        if (removeNode(_key, _subroot->right) == 4) {
            person *leftmost = _subroot->right->right;
            person *leftmostParent = _subroot->right;
            person *temp = leftmost;

            if (leftmost->left == NULL) {
                leftmost->left = leftmostParent->left;
                _subroot->right = leftmost;
                return 0;
            };

            while (temp->left) {
                leftmostParent = temp;
                leftmost = temp->left;
                temp = temp->left;
            }

            leftmostParent->left = leftmost->right;
            leftmost->left = _subroot->right->left;
            leftmost->right = _subroot->right->right;

            _subroot->right = leftmost;

            return 0;
        }
    }

    if (_key == _subroot->key) {
        if (!_subroot->left && !_subroot->right) { return 1; } //return "1" if deleting node is a leave
        if ( _subroot->left && !_subroot->right) { return 2; } //return "2" if there is node at left only
        if (!_subroot->left &&  _subroot->right) { return 3; } //return "3" if there is node at right only
        if ( _subroot->left &&  _subroot->right) { return 4; } //return "4" if there are both nodes
    }

}
vector<person> nodes; //vector like [0,1,1,2,2,2,2,3,3,3,3,3,3,...]. shows on what level each node is
vector<int> nodesLevel; // vector for nodes

int countLevels(person *_subroot) {
    nodes.push_back(*_subroot);
    nodesLevel.push_back(0);

    //fill vector with nodes
    for (int i = 0; i < nodes.size(); i++) {
        if (nodes[i].left)  { nodes.push_back( *(nodes[i].left)  );  }
        if (nodes[i].right) { nodes.push_back( *(nodes[i].right) );  }
    }

    int l = 1; 
    int c = 1;
    for (int i = 1; i < nodes.size(); i++) {
        if (nodes[i].key < nodes[i -1].key || (nodes[i - 1].right && nodes[i].key == nodes[i-1].right->key)) {
            cout << "Level " << l << " has " << c << " nodes" << endl;
            c = 1;
            l++;
        }
        else {
            c++;
        }
    }

    cout << "Level " << l << " has " << c << " nodes" << endl;
    return 0;
}

//convert object to string
string toString(person _node) {
    string sl = (_node.left)  ? toString(*_node.left) : "null";
    string sr = (_node.right) ? toString(*_node.right) : "null";
    return "{\"key\":" + to_string(_node.key) + "," + \
            "\"name\":\"" + _node.name + "\"," + \
            "\"pass\":\"" + _node.pass + "\"," + \
            "\"color\":\"" + _node.color + "\"," + \
            "\"left\":" + sl + "," +\
            "\"right\":" + sr + \
            "}";
}

void main() {

    vector<person> pv;

    ifstream fin;
    fin.open("tree_template.json");

    int n = 0;
    while (!fin.eof()) {
        n++;
        person a;
        fin >> a.key >> a.name >> a.pass;
        pv.push_back(a);
    }
    fin.close();

    //initiate tree root
    addNode(newNode(pv[0].key, pv[0].name, pv[0].pass));

    for (int i = 1; i < n; i++) {
        addNode(*newNode(pv[i].key, pv[i].name, pv[i].pass), root);
    }

    //remove smthg
    //removeNode(50, root);
    //removeNode(39, root);
    removeNode(50, root);
    removeNode(56, root);

    countLevels(root);

    string s = "let tree = " + toString(*root);

    ofstream fout;
    fout.open("../../tree/output_tree.json");
    fout << s;
    fout.close();
    return;
}