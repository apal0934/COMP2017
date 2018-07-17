#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "supergraph.h"

#define MAX_BUFFER 65535

// Reads given graph file and returns a book graph.
post* post_loader(size_t* count, const char* filename) {

	char buffer[MAX_BUFFER];
	size_t n_posts = 0;

	// Open graph file
	FILE* f = fopen(filename, "r");
	if (f == NULL) {
		perror("Fatal error! Unable to open graph file");
		return NULL;
	}

	// Read book count
	if (fgets(buffer, MAX_BUFFER, f) == NULL || sscanf(buffer, "%zu", &n_posts) == 0) {
		fprintf(stderr, "Fatal error! Unable to read posts.\n");
		return NULL;
	}

	post* graph = malloc(sizeof(post) * n_posts);

	// Read books
	for (size_t i = 0; i < n_posts; i++) {

		// Read user id
		if (fgets(buffer, MAX_BUFFER, f) == NULL || sscanf(buffer, "%zu", &graph[i].pst_id) == 0) {
			fprintf(stderr, "Fatal error! Unable to read post id %zu.\n", i);
			return NULL;
		}

		// Read n_following
		if (fgets(buffer, MAX_BUFFER, f) == NULL || sscanf(buffer, "%zu", &graph[i].n_reposted) == 0) {
			fprintf(stderr, "Fatal error! Unable to read reposts%zu.\n", i);
			return NULL;
		}

		size_t cap = 10;
		size_t size = 0;

		buffer[MAX_BUFFER - 1] = '\0';
		size_t length = MAX_BUFFER - 1;
		graph[i].reposted_idxs = malloc(sizeof(size_t) * cap);

		// Read following edges
		while (length == MAX_BUFFER - 1 && buffer[length] != '\n') {
			if (fgets(buffer, MAX_BUFFER, f) == NULL) {
				fprintf(stderr, "Fatal error! Unable to read following  %zu.\n", i);
			}

			length = strlen(buffer);
			for (char* s = strtok(buffer, " "); s != NULL; s = strtok(NULL, " ")) {
				if (size == cap) {
					cap = cap * 2;
					graph[i].reposted_idxs = realloc(graph[i].reposted_idxs, sizeof(size_t) * cap);
				}
				if (strcmp("\n", s) != 0) {
					size_t k = strtol(s, NULL, 10);
					graph[i].reposted_idxs[size] = k;
					size++;
				}
			}
		}

		
	}
	fclose(f);
	*count = n_posts;

	return graph;
}


// Reads given graph file and returns a book graph.
user* user_loader(size_t* count, const char* filename) {

	char buffer[MAX_BUFFER];
	size_t n_users = 0;

	// Open graph file
	FILE* f = fopen(filename, "r");
	if (f == NULL) {
		perror("Fatal error! Unable to open graph file");
		return NULL;
	}

	// Read book count
	if (fgets(buffer, MAX_BUFFER, f) == NULL || sscanf(buffer, "%zu", &n_users) == 0) {
		fprintf(stderr, "Fatal error! Unable to read users.\n");
		return NULL;
	}

	user* graph = malloc(sizeof(user) * n_users);

	// Read books
	for (size_t i = 0; i < n_users; i++) {

		// Read user id
		if (fgets(buffer, MAX_BUFFER, f) == NULL || sscanf(buffer, "%zu", &graph[i].user_id) == 0) {
			fprintf(stderr, "Fatal error! Unable to read usr id for user %zu.\n", i);
			return NULL;
		}

		// Read n_following
		if (fgets(buffer, MAX_BUFFER, f) == NULL || sscanf(buffer, "%zu", &graph[i].n_followers) == 0) {
			fprintf(stderr, "Fatal error! Unable to read following for user %zu.\n", i);
			return NULL;
		}

		// Read n_followers
		if (fgets(buffer, MAX_BUFFER, f) == NULL || sscanf(buffer, "%zu", &graph[i].n_following) == 0) {
			fprintf(stderr, "Fatal error! Unable to read followers for user %zu.\n", i);
			return NULL;
		}
		
		// Read n_posts
		if (fgets(buffer, MAX_BUFFER, f) == NULL || sscanf(buffer, "%zu", &graph[i].n_posts) == 0) {
			fprintf(stderr, "Fatal error! Unable to read followers for user %zu.\n", i);
			return NULL;
		}

		size_t cap = 10;
		size_t size = 0;

		buffer[MAX_BUFFER - 1] = '\0';
		size_t length = MAX_BUFFER - 1;
		graph[i].follower_idxs = malloc(sizeof(size_t) * cap);

		// Read following edges
		while (length == MAX_BUFFER - 1 && buffer[length] != '\n') {
			if (fgets(buffer, MAX_BUFFER, f) == NULL) {
				fprintf(stderr, "Fatal error! Unable to read following  %zu.\n", i);
			}

			length = strlen(buffer);
			for (char* s = strtok(buffer, " "); s != NULL; s = strtok(NULL, " ")) {
				if (size == cap) {
					cap = cap * 2;
					graph[i].follower_idxs = realloc(graph[i].follower_idxs, sizeof(size_t) * cap);
				}
				if (strcmp("\n", s) != 0) {
					size_t k = strtol(s, NULL, 10);
					graph[i].follower_idxs[size] = k;
					size++;
				}
			}
		}

		cap = 10;
		size = 0;

		buffer[MAX_BUFFER - 1] = '\0';
		length = MAX_BUFFER - 1;
		graph[i].following_idxs = malloc(sizeof(size_t) * cap);

		// Read followers
		while (length == MAX_BUFFER - 1 && buffer[length] != '\n') {
			if (fgets(buffer, MAX_BUFFER, f) == NULL) {
				fprintf(stderr, "Fatal error! Unable to followers for user %zu.\n", i);
			}

			length = strlen(buffer);
			for (char* s = strtok(buffer, " "); s != NULL; s = strtok(NULL, " ")) {
				if (size == cap) {
					cap = cap * 2;
					graph[i].following_idxs = realloc(graph[i].following_idxs, sizeof(size_t) * cap);
				}
				if (strcmp("\n", s) != 0) {
					size_t k = strtol(s, NULL, 10);
					graph[i].following_idxs[size] = k;
					size++;
				}
			}
		}

		cap = 10;
		size = 0;

		buffer[MAX_BUFFER - 1] = '\0';
		length = MAX_BUFFER - 1;
		graph[i].post_idxs = malloc(sizeof(size_t) * cap);

		// Read posts
		while (length == MAX_BUFFER - 1 && buffer[length] != '\n') {
			if (fgets(buffer, MAX_BUFFER, f) == NULL) {
				fprintf(stderr, "Fatal error! Unable to read posts for user %zu.\n", i);
			}

			length = strlen(buffer);
			for (char* s = strtok(buffer, " "); s != NULL; s = strtok(NULL, " ")) {
				if (size == cap) {
					cap *= 2;
					graph[i].post_idxs = realloc(graph[i].post_idxs, sizeof(size_t) * cap);
				}
				if (strcmp("\n", s) != 0) {
					size_t k = strtol(s, NULL, 10);
					graph[i].post_idxs[size] = k;
					size++;
				}
			}
		}
	}



	*count = n_users;
	
	return graph;
}

