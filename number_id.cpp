#include <cstdlib>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <map>
#include <vector>

#include <boost/algorithm/string.hpp>

using namespace std;

typedef struct node {
    int point;
    int id;
    node* left;
    node* right;
} node;

bool buildTree(const vector<string>& points,
        node* node_list,
        int s,
        int e);

int getId(const node& t,
        int num);

void sequence(const node& t);

int main(int argc, char** argv) {
    int key;
    int num;
    ifstream dict_file("points.dict");
    string line;
    vector<string> points;
    vector<string> fields;
    map<int, pair<node*, int> > tree_dict;
    while (getline(dict_file, line)) {
        boost::split(fields, line, boost::is_any_of("\t"));
        boost::split(points, fields[1], boost::is_any_of(","));
        node* node_list = new node[points.size()];
        int root_ind = (0 + points.size() - 1) / 2;
        tree_dict.insert(pair<int, pair<node*, int> >(atoi(fields[0].c_str()), pair<node*, int>(node_list, root_ind)));
        buildTree(points, node_list, 0, points.size() - 1);
    }
    dict_file.close();

    ifstream data_file("test.in");
    while (getline(data_file, line)) {
        sscanf(line.c_str(), "%d\t%d", &key, &num);
        map<int, pair<node*, int> >::iterator it = tree_dict.find(key);
        if (it != tree_dict.end()) {
            cout << getId(it->second.first[it->second.second], num) << endl;
        }

    }



    // clean up
    for(map<int, pair<node*, int> >::iterator it = tree_dict.begin();
            it != tree_dict.end(); ++it) {
        delete[]  it->second.first;
    }
    return 0;
}


bool buildTree(const vector<string>& points,
        node* node_list,
        int s,
        int e) {
    int root_ind = (s + e) / 2;
    node* t = node_list + root_ind;
    if (s == e) {
        t->point = atoi(points[s].c_str());
        t->id = s + 1;
        t->left = NULL;
        t->right = NULL;
        return true;
    }
    if ((e - s + 1) == 2) {
        // root_ind == (s + e) / 2 == s
        t->point = atoi(points[root_ind].c_str());
        t->id = root_ind + 1;
        t->left = NULL;
        t->right = node_list + e;
        buildTree(points, node_list, e, e);
        return true;
    }
    t->point = atoi(points[root_ind].c_str());
    t->id = root_ind + 1;
    int left_s = s;
    int left_e = root_ind - 1;
    int right_s = root_ind + 1;
    int right_e = e;
    t->left = node_list + (left_s + left_e) / 2;
    buildTree(points, node_list, left_s, left_e);
    t->right = node_list + (right_s + right_e) / 2;
    buildTree(points, node_list, right_s, right_e);
    return true;
}

void sequence(const node& t) {
    if (t.left != NULL) {
        sequence(*t.left);
    }
    cout << t.id << ",";
    if (t.right != NULL) {
        sequence(*t.right);
    }
}

int getId(const node& t,
        int num) {
    if (num == t.point) {
        return t.id;
    }
    if (num < t.point) {
        if (t.left == NULL) return t.id - 1;
        else {
            return getId(*t.left, num);
        }
    } else {
        if (t.right == NULL) return t.id;
        else {
            return getId(*t.right, num);
        }
    }
}
