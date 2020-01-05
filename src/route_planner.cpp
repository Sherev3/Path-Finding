#include "route_planner.h"
#include <algorithm>

RoutePlanner::RoutePlanner(RouteModel &model, float start_x, float start_y, float end_x, float end_y): m_Model(model) {
    // Convert inputs to percentage:
    start_x *= 0.01;
    start_y *= 0.01;
    end_x *= 0.01;
    end_y *= 0.01;

    // TODO 2: Use the m_Model.FindClosestNode method to find the closest nodes to the starting and ending coordinates.
    // Store the nodes you find in the RoutePlanner's start_node and end_node attributes.
    start_node = &m_Model.FindClosestNode(start_x,start_y);
    end_node = &m_Model.FindClosestNode(end_x,end_y);
}


// TODO 3: Implement the CalculateHValue method.
// Tips:
// - You can use the distance to the end_node for the h value.
// - Node objects have a distance method to determine the distance to another node.

float RoutePlanner::CalculateHValue(RouteModel::Node const *node) {

  
    return this->end_node->distance(*node);
}


// TODO 4: Complete the AddNeighbors method to expand the current node by adding all unvisited neighbors to the open list.
// Tips:
// - Use the FindNeighbors() method of the current_node to populate current_node.neighbors vector with all the neighbors.
// - For each node in current_node.neighbors, set the parent, the h_value, the g_value. 
// - Use CalculateHValue below to implement the h-Value calculation.
// - For each node in current_node.neighbors, add the neighbor to open_list and set the node's visited attribute to true.

void RoutePlanner::AddNeighbors(RouteModel::Node *current_node) {
    current_node->FindNeighbors();
    for(RouteModel::Node* neighbor_node:current_node->neighbors)
    {
        neighbor_node->parent = current_node;
        neighbor_node->h_value = CalculateHValue(neighbor_node);
        neighbor_node->g_value = neighbor_node->distance(*current_node);  
        if(neighbor_node->visited  == false)
        {
            neighbor_node->visited = true;
            this->open_list.push_back(neighbor_node);
        }    
    }
}


// TODO 5: Complete the NextNode method to sort the open list and return the next node.
// Tips:
// - Sort the open_list according to the sum of the h value and g value.
// - Create a pointer to the node in the list with the lowest sum.
// - Remove that node from the open_list.
// - Return the pointer.

RouteModel::Node *RoutePlanner::NextNode() {
    /*
    int a = 4;
    int b = 3;
    int c = 2;
    int d = 1;
    int *pa = &a;
    int *pb = &b;
    int *pc = &c;
    int *pd = &d;
    std::vector<int *> f_values;
    f_values.push_back(pa);
    f_values.push_back(pb);
    f_values.push_back(pc);
    f_values.push_back(pd);
    int n = sizeof(f_values)/sizeof(f_values[0]);
    std::sort(f_values[0],f_values[3]);
    for(int *i:f_values)
    {
        std::cout << "value: " << *i << "\n";
    }*/
    
    
    //std::cout << "begin value: " <<f_values.begin()<<"\n";
    //std::cout << " address value of pa: "<< f_values[0] << "\n";
    //std::cout << " address of the first element in vector: "<< &f_values[0] << "\n";
    //std::cout << "front test: " << (*f_values.front()) << "\n";
    RouteModel::Node *lowest_sum;
    std::vector<float> f_values;
    std::vector<RouteModel::Node *> ordered_open_list;
    for(RouteModel::Node *i: this->open_list)
    {
        float tmp_f_value;
        tmp_f_value = i->g_value + i->h_value;
        f_values.push_back(tmp_f_value) ;
    }
    std::sort(f_values.begin(),f_values.end());

    for(float i : f_values)
    {
        for(RouteModel::Node *x : this->open_list)
        {
            if(x->g_value + x->h_value == i && std::find(ordered_open_list.begin(),ordered_open_list.end(),x) != ordered_open_list.end())
            {
                ordered_open_list.push_back(x);                
            }
        }
    }
    this->open_list= ordered_open_list;
    lowest_sum = open_list.front();
    this->open_list.erase(open_list.begin());

    return lowest_sum;
}


// TODO 6: Complete the ConstructFinalPath method to return the final path found from your A* search.
// Tips:
// - This method should take the current (final) node as an argument and iteratively follow the 
//   chain of parents of nodes until the starting node is found.
// - For each node in the chain, add the distance from the node to its parent to the distance variable.
// - The returned vector should be in the correct order: the start node should be the first element
//   of the vector, the end node should be the last element.

std::vector<RouteModel::Node> RoutePlanner::ConstructFinalPath(RouteModel::Node *current_node) {
    // Create path_found vector
    distance = 0.0f;
    std::vector<RouteModel::Node> path_found;
    //RouteModel::Node *dummy_address;
    // TODO: Implement your solution here.
    while(current_node != this->start_node)
    {
        distance += current_node->distance(*(current_node->parent)); 
        path_found.push_back(*current_node);
        current_node = current_node->parent;

    }
    path_found.push_back(*current_node);
    std::reverse(path_found.begin(),path_found.end());
    //dummy_address = this->NextNode();
    distance *= m_Model.MetricScale(); // Multiply the distance by the scale of the map to get meters.
    return path_found;

}


// TODO 7: Write the A* Search algorithm here.
// Tips:
// - Use the AddNeighbors method to add all of the neighbors of the current node to the open_list.
// - Use the NextNode() method to sort the open_list and return the next node.
// - When the search has reached the end_node, use the ConstructFinalPath method to return the final path that was found.
// - Store the final path in the m_Model.path attribute before the method exits. This path will then be displayed on the map tile.

void RoutePlanner::AStarSearch() {
    RouteModel::Node *current_node = nullptr;

    // TODO: Implement your solution here.

}