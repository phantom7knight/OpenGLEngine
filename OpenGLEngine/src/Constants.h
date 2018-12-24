

#define Screen_Width  1600
#define Screen_Height  900 


#define PI 3.14


#define SAFE_DELETE(pointer)\
if(pointer)			\
{					\
delete pointer;		\
pointer = nullptr;	\
}					\

#define SAFE_DELETE_ARRAY_PTR(arrpointer)\
if(arrpointer)							 \
{										 \
	delete[]arrpointer;					 \
	arrpointer = nullptr;				 \
}										 \

#define FUNCTION_INITIALIZE(functionname)	\
if (!functionname())						\
{											\
return false;								\
}											\


#define PRINT_LOG(infohere) \
printf(infohere);			\

