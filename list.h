struct list {
	void*		data;
	struct list	succ;
	struct list	pred;
};

struct list* new_list(void*);

void add_last(struct list*, void*);

void* remove_first(struct list**);

void free_list(struct list**);
