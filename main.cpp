#include <iostream>

#include "interval_tree.hpp"

int main(){
	Interval_Tree::Interval_Tree *interval_tree = new Interval_Tree::Interval_Tree(100);
	unsigned int op=1;
	int key=0, key2=0;
	float capacity=0;
	while(op!=0) {
		std::cin>>op;
		switch(op) {
		case 1:
			std::cin>>key>>key2>>capacity;
			interval_tree->insert(key,key2,capacity);
			break;
		case 2:
			std::cin>>key>>key2;
			interval_tree->remove(key,key2);
			break;
		case 3:
			std::cin>>key>>key2;
			{
				float cap = interval_tree->getMinCapacityInterval(key,key2);
				// if(temp!=NULL)
				std::cout<<"Node ["<<key<<";"<<key2<<"] found! Capacity "<<cap<<"\n";
				// else
				// 	std::cout<<"Node not found\n";
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
