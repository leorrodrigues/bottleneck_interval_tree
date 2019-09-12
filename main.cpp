#define SPDLOG_TRACE_ON
#define SPDLOG_DEBUG_ON
#define SPDLOG_EOL ""

#include "interval_tree.hpp"

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

int main(){
	spdlog::set_level(spdlog::level::debug);     // Set global log level to debug
	spdlog::set_pattern("%v"); // change the log pattern
	Interval_Tree::Interval_Tree *interval_tree = new Interval_Tree::Interval_Tree(100);
	Interval_Tree::Interval_Tree *interval_tree_aux = new Interval_Tree::Interval_Tree(100);
	unsigned int op=1;
	int key=0, key2=0;
	float capacity=0;
	while(op!=0) {
		if(scanf("%d",&op)==0) SPDLOG_ERROR("CANT READ THE OP\n");
		switch(op) {
		case 1:
			if(scanf("%d %d %f",&key,&key2,&capacity)==0) SPDLOG_ERROR("CANT READ THE VALUES TO INSERT NODE");
			interval_tree->insert(key,key2,capacity);
			break;
		case 2:
			if(scanf("%d %d %f",&key,&key2, &capacity)==0) SPDLOG_ERROR("CANT READ THE VALUES TO REMOVE NODE");
			interval_tree->remove(key,key2,capacity);
			break;
		case 3:
			if(scanf("%d %d", &key, &key2)==0) SPDLOG_ERROR("CANT READ THE VALUES TO GET THE INTERVAL NODE(S)");
			{
				Interval_Tree::interval_t *result = interval_tree->getInterval(key,key2);

				if(result != NULL) {
					for(int i=0; i<result->size; i++)
						spdlog::debug("[{},{}]=>{}\n", result->nodes[i].low, result->nodes[i].high, result->nodes[i].capacity);
					result->clear();
					free(result);
					result = NULL;
				}else{
					spdlog::debug("Node not found\n");
				}
			}
			break;
		case 4:
			interval_tree->show();
			break;
		case 5:
			if(scanf("%d %d", &key, &key2)==0) SPDLOG_ERROR("CANT READ THE VALUES TO GET THE MIN CAPACITY AVAILABLE FROM INTERVAL");
			spdlog::debug("Min capacity {}\n", interval_tree->getMinValueAvailable(key, key2));
			break;
		case 6:
			if(scanf("%d %d %f",&key,&key2,&capacity)==0) SPDLOG_ERROR("CANT READ THE VALUES TO INSERT NODE IN AUX TREE");
			interval_tree_aux->insert(key,key2,capacity);
			break;
		case 7:
			if(scanf("%d %d %f",&key,&key2,&capacity)==0) SPDLOG_ERROR("CANT READ THE VALUES TO REMOVE NODE IN AUX TREE");
			interval_tree_aux->remove(key,key2,capacity);
			break;
		case 8:
			(*interval_tree) += (*interval_tree_aux);
			break;
		case 9:
			(*interval_tree) -= (*interval_tree_aux);
			break;
		case 10:
			interval_tree_aux->show();
			break;
		case 0:
			delete(interval_tree);
			delete(interval_tree_aux);
			break;
		default:
			spdlog::debug("Valor invalido {}\n",op);
			break;
		}
	}
	return 0;
}
