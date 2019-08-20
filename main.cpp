#include <iostream>

#include "interval_tree.hpp"

int main(){
	Interval_Tree::Interval_Tree *interval_tree = new Interval_Tree::Interval_Tree();
	unsigned int op=1;
	int key=0, key2=0;
	while(op!=0) {
		std::cin>>op;
		switch(op) {
		case 1:
			std::cin>>key>>key2;
			interval_tree->insert(key,key2);
			break;
		case 2:
			std::cin>>key>>key2;
			interval_tree->remove(key,key2);
			break;
		case 3:
			std::cin>>key;
			{
				Interval_Tree::node_t* temp = interval_tree->search(key);
				if(temp!=NULL)
					std::cout<<"Node ["<<temp->interval[0]<<temp->interval[1]<<"] found!\n";
				else
					std::cout<<"Node not found\n";
			}
			break;
		case 4:
			interval_tree->show();
			break;
		case 0:
			delete(interval_tree);
			break;
		default:
			std::cout<<"Valor invalido\n";
			break;
		}
	}
	return 0;
}
