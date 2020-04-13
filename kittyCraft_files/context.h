
#define max_items_per_instance 100

struct fwindow
{
	int screen;
	int x;
	int y;
	int width;
	int height;
};

struct fractal
{
	int x;
	int y;
	int xstep;
	int ystep;
	int cr;		// for julia
	int ci;		// for julia
	int start;
	int height;
	int iterations;
	struct fwindow window;
};

struct context
{
// !!	lazy should have a allocator. !!

	APTR dir_context[max_items_per_instance];
	struct ExamineData *examineData[max_items_per_instance];
	ULONG used_dir_contexts;

	// other data.

	ULONG multiOffCount;
	struct fractal fractal;
};
