
#define max_items_per_instance 100

struct context
{
	APTR dir_context[max_items_per_instance];
	struct ExamineData *examineData[max_items_per_instance];
	ULONG used_dir_contexts;
};

