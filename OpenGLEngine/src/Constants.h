

#define SAFE_DELETE(pointer)\
if(pointer)			\
{					\
delete(pointer);	\
pointer = nullptr;	\
}					\

#define SAFE_DELETE_ARRAY_PTR(arrpointer)\
if(arrpointer)							 \
{										 \
	delete[]arrpointer;					 \
	arrpointer = nullptr;				 \
}										 \