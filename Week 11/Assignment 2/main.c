#include <time.h>
#include "supergraph.h"
#include "supergraph_loader.h"
#include <unistd.h>


int main(void) {
	size_t *post_count = malloc(sizeof(size_t));
	struct post *posts = post_loader(post_count, "social.posts");
	size_t *user_count = malloc(sizeof(size_t));
	struct user *users = user_loader(user_count, "social.users");
	struct criteria *crit = malloc(sizeof(struct criteria));
	crit->oc_threshold = 0.5f;
	crit->acc_rep_threshold = 0.4f;
	crit->bot_net_threshold = 0.959f;

	// -----------
	// BEGIN TESTS
	// -----------
	printf("Starting tests!\n");
	// ------------
	// FIND REPOSTS
	// ------------
	printf("------------------------------------------\n");	
	printf("Running reposts...\n");
	clock_t begin_reposts = clock();
	struct result *find_reposts = find_all_reposts(posts, *post_count, 1251, NULL);
	clock_t end_reposts = clock();
	double elapsed_reposts = (double) (end_reposts - begin_reposts) / CLOCKS_PER_SEC;
	printf("Test finished: %zu element(s) in %fs.\n", find_reposts->n_elements, elapsed_reposts);
	printf("------------------------------------------\n");
	// -------------
	// FIND ORIGINAL
	// -------------
	printf("Running original...\n");
	clock_t begin_original = clock();
	struct result *original = find_original(posts, *post_count, 7041, NULL);
	clock_t end_original = clock();
	double elapsed_original = (double) (end_original - begin_original) / CLOCKS_PER_SEC;
	printf("Test finished: %zu element(s) in %fs.\n", original->n_elements, elapsed_original);
	printf("------------------------------------------\n");
	// -------------
	// SHORTEST USER
	// -------------
	printf("Running shortest user...\n");
	clock_t begin_user = clock();
	struct result *shortest_user = shortest_user_link(users, *user_count, 0, 5125, NULL);
	clock_t end_user = clock();
	double elapsed_user = (double) (end_user- begin_user) / CLOCKS_PER_SEC;
	printf("Test finished: %zu element(s) in %fs.\n", shortest_user->n_elements, elapsed_user);
	printf("------------------------------------------\n");
	// ---------
	// FIND BOTS
	// ---------
	printf("Running bots...\n");
	clock_t begin_bots = clock();
	struct result *bots = find_bots(users, *user_count, posts, *post_count, crit, NULL);
	clock_t end_bots = clock();
	double elapsed_bots = (double) (end_bots - begin_bots) / CLOCKS_PER_SEC;
	printf("Test finished: %zu element(s) in %fs.\n", bots->n_elements, elapsed_bots);
	printf("------------------------------------------\n");

	free(find_reposts->elements);
	free(original->elements);
	free(shortest_user->elements);
	free(bots->elements);
	free(find_reposts);
	free(original);
	free(shortest_user);
	free(bots);
	free(post_count);
	free(user_count);
	free(crit);
	return 0;
}
