#ifndef BNB_H
#define BNB_H
#include <cstddef>
#include <iostream>
#include <utility>
#include <vector>
#include <list>
#include "hungarian.h"

typedef struct Node{

    std::vector<std::pair<int, int>> forbidden_arcs;
    std::vector<int> subtours;
    double lower_bound = 0; 
    bool viable = false;
    double **cost_ = NULL; //matriz de custos
    
}Node;

void bnb(hungarian_problem_t *p, int branching, double** cost, double tsp_heuristic);

void init_node(Node *node, hungarian_problem_t *p);

void init_cost(Node *node, hungarian_problem_t *p, double** cost);

std::list<Node>::iterator branching(std::list<Node> tree, int branching);

void erase_node(std::list<Node>::iterator &node, hungarian_problem_t *p, std::list<Node> *tree);

void erase_tree(std::list<Node> *tree, hungarian_problem_t *p);

void print_viable(Node *node);

void print_cost_matrix(Node *node, hungarian_problem_t *p);
#endif