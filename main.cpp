#include <iostream>

#include "interval_tree.hpp"

int main(){
	Interval_Tree::Interval_Tree *interval_tree = new Interval_Tree::Interval_Tree(100);
	unsigned int op=1;
	int key=0, key2=0;
	float capacity=0;
	while(op!=0) {
		scanf("%d ",&op);
		switch(op) {
		case 1:
			scanf("%d %d %f",&key,&key2,&capacity);
			interval_tree->insert(key,key2,capacity);
			break;
		case 2:
			scanf("%d %d %f",&key,&key2, &capacity);
			interval_tree->remove(key,key2,capacity);
			break;
		case 3:
			scanf("%d %d", &key, &key2);
			{
				Interval_Tree::interval_t *result = interval_tree->getInterval(key,key2);

				if(result!=NULL) {
					for(int i=0; i<result->size; i++)
						std::cout<<"["<<result->nodes[i].low<<","<<result->nodes[i].high<<"]=>"<<result->nodes[i].capacity<<"\n";
					result->clear();
					free(result);
					result = NULL;
				}else{
					std::cout<<"Node not found\n";
				}
			}
			break;
		case 4:
			interval_tree->show();
			break;
		case 5:
			scanf("%d %d", &key, &key2);
			printf("Min capacity %f\n", interval_tree->getMinCapacityInterval(key, key2));
			break;
		case 0:
			delete(interval_tree);
			break;
		default:
			std::cout<<"Valor invalido "<<op<<"\n";
			break;
		}
	}
	return 0;
}
