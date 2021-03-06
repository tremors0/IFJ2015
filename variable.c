#include "variable.h"
#include "error.h"
#include <stdlib.h>
#include <stdio.h>

void variableCreate(tVariablePtr* var, tVariableType type) {
	//alokace promenne
    tVariablePtr v = (tVariablePtr) malloc(sizeof(struct tVariableStr));
    if(!v){
        FatalError(99, ERR_MESSAGES[ERR_ALLOC]);
    }
	//urceni typu
    v->type = type;
	//pokud je stringova alokujeme pamet pro string
    if(type==VAR_TYPE_STRING) {
        if(strInit(&v->data.stringVal)) //str init vraci 0 pri uspechu protoze str.c psal idiot
            FatalError(99, ERR_MESSAGES[ERR_ALLOC]);
    }
	//kazda promenna je na zacatku neinicializovana
	v->init = false;
    *var = v;
}
void variableDelete(void* var) {
	//pokud je promenna stringova musime dealokovat string
	if (((tVariablePtr)var)->type == VAR_TYPE_STRING) {
		strFree(&((tVariablePtr)var)->data.stringVal);
	}
	//smazeme samotnou promennou
	free(((tVariablePtr)var));
	//debug info
    // printf("Mazu promennou %d\n",((tVariablePtr)var)->data.intVal);
}

tVariableType tTabSymToVarNotatation(tTabSymVarDataType type) {
	switch (type) {
	case TAB_SYM_VAR_INTEGER:
		return VAR_TYPE_INT;
		break;
	case TAB_SYM_VAR_DOUBLE:
		return VAR_TYPE_DOUBLE;
		break;
	case TAB_SYM_VAR_STRING:
		return VAR_TYPE_STRING;
		break;
	case TAB_SYM_VAR_BOOLEAN:
		return VAR_TYPE_BOOL;
		break;
	default:
		break;
	}
	return 42; 
}