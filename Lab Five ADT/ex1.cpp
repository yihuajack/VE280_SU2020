#include "ex1.h"

int dot(list_t v1, list_t v2){
	// TODO: implement dot function
	if (!list_isEmpty(v1) && !list_isEmpty(v2))
		return list_first(v1) * list_first(v2) + dot(list_rest(v1), list_rest(v2));
	else {
		return 0;
	}
}

list_t filter_odd(list_t list){
	// TODO: implement filter_odd function
	if (!list_isEmpty(list))
		return (list_first(list) % 2 == 1) ? list_make(list_first(list), filter_odd(list_rest(list))) : filter_odd(list_rest(list));
	else {
		return list;
	}
}

list_t filter(list_t list, bool (*fn)(int)){
	// TODO: implement filter function
	if (!list_isEmpty(list))
		return (fn(list_first(list))) ? list_make(list_first(list), filter(list_rest(list), fn)) : filter(list_rest(list), fn);
	else {
		return list;
	}
}
