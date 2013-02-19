run-mix-linked_alloc: mix-linked_alloc.mixal
	mixasm mix-linked_alloc.mixal
	mixvm -r mix-linked_alloc

