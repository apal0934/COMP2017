#include "supergraph.h"
#include <string.h>
query_helper* engine_setup(size_t n_processors) {
	return NULL;
}

result* find_all_reposts(post* posts, size_t count, uint64_t post_id, query_helper* helper) {
	struct result *result = malloc(sizeof(struct result));
	if (count == 0 || posts == NULL || post_id < 0 || post_id > count) {
		result->elements = NULL;
		result->n_elements = 0;
		return result;
	}
	
	size_t i = 0;
	for ( ; i < count; i++) {
		if (posts[i].pst_id == post_id) {
			// found
			
			//printf("found post %zu\n", i);
			
			break;
		} else if (i == (count - 1)) {
			// not found
			result->elements = NULL;
			result->n_elements = 0;
			return result;
		}
	}
	
	if (posts[i].n_reposted == 0) {
		result->elements = malloc(sizeof(posts[i]));
		result->elements[0] = &posts[i];
		result->n_elements = 1;
		return result;
	}

	//printf("n_reposted: %zu\n", n_reposted);

	result->elements = malloc(sizeof(struct post) * count);
	result->n_elements = 1;
	// set first post to be originating post
	result->elements[0] = &posts[i];
	
	// initalise mark
	int visited[count];
	for (size_t i = 0; i < count; i++) {
			visited[i] = 0;
	}
	visited[0] = 1;

	// initialise queue
	struct queue *queue = malloc(sizeof(struct queue));
	queue->queue = malloc(sizeof(size_t) * count);
	queue->front = 0;
	queue->rear = -1;
	queue->queue_size = 0;
	
	// enqueue post we want to find reposts of
	queue->rear++;
	queue->queue[queue->rear] = i;
	queue->queue_size++;
	int j = 1;
	int k = 0;
	// BFS
	while (queue->queue_size != 0) {
		// dequeue current post
	
		size_t current_vertex = queue->queue[queue->front];
		k++;
		queue->front++;
		queue->queue_size--;
		
		for (size_t i = 0; i < posts[current_vertex].n_reposted; i++) {
			size_t index = posts[current_vertex].reposted_idxs[i];
			if (visited[index] == 0) {
				visited[index] = 1;
				result->elements[j] = &posts[index];
				result->n_elements++;
				j++;
				if (queue->front == -1) {
					queue->front = 0;
				}

				queue->rear++;
				queue->queue[queue->rear] = index;
				queue->queue_size++;
			}
		}
	}
	
	free(queue->queue);
	free(queue);	
	return result;
}

result* find_original(post* posts, size_t count, uint64_t post_id, query_helper* helper) {
	struct result *result = malloc(sizeof(struct result));
	result->n_elements = 0;
	
	if (count == 0 || posts == NULL || post_id < 0 || post_id > count) {
		result->elements = NULL;
		result->n_elements = 0;
		return result;
	}
	
	size_t i = 0;
	for ( ; i < count; i++) {
		if (posts[i].pst_id == post_id) {
			// found

			//printf("Found post_id: %zu\n", i);
			
			break;
		} else if (i == (count - 1)) {
			// not found
			
			//printf("Did not find post\n");
			
			result->elements = NULL;
			result->n_elements = 0;
			return result;
		}
	}

	result->elements = malloc(sizeof(struct post));
	for (size_t j = 0; j < count; j++) {
		for (size_t k = 0; k  < posts[j].n_reposted; k++) {
			
			//printf("i %zu j %zu k %zu\n", i, j, posts[j].reposted_idxs[k]);
			
			if (i == posts[j].reposted_idxs[k]) {
				// j is the parent of i
				
				//printf("Found parent of %zu @ %zu\n", i, j);
				
				i = j;
				j = -1;
				break;
			}
		}

		if (j == (count - 1)) {
			// j is the OG post.
			
			//printf("Found root @ %zu\n", i);
			
			result->n_elements ++;
			result->elements[0] = &posts[i];
			break;
		}
                
	}
	return result;
}

result* shortest_user_link(user* users, size_t count, uint64_t userA, uint64_t userB, query_helper* helper) {
	struct result *result = malloc(sizeof(struct result));
	if (users == NULL || count == 0 || userA == userB) {
		result->elements = NULL;
		result->n_elements = 0;
		return result;
	}

	size_t index_a = 0;
	size_t index_b = 0;

	// found:
	// Neither userA nor userB = 0
	// Either userA or userB   = 1
	// Both userA and userB    = 2
	// found != 2 is fail condition
	size_t found = 0;
	for (size_t i = 0; i < count; i++) { 
		if (users[i].user_id == userA) {
			// found userA
			index_a = i;
		   	found ++;
		} else if (users[i].user_id == userB) {
			// found userB
			index_b = i;
			found ++;
		}
		if (found == 2) {
	   		break;
		}
	}
	if (found != 2) {
		result->elements = NULL;
		result->n_elements = 0;
		return result;
	}

	// anything beyond this is a-ok!
	
	//printf("%zu %zu\n %zu %zu\n", userA, userB, index_a, index_b);
	
	struct queue *queue = malloc(sizeof(struct queue));
	queue->front = 0;
	queue->rear = -1;
	queue->queue_size = 0;
	queue->queue = malloc(sizeof(size_t) * count);
	
	int visited[count];
	int distance[count];
	size_t parent_a[count];
	for (size_t i = 0; i < count; i++) {
		visited[i] = 0;
		distance[i] = 0;
		parent_a[i] = -1;
	}
	visited[index_a] = 1;
	distance[index_a] = 0;
	distance[index_b] = 0;
	queue->rear ++;
	queue->queue[queue->rear] = index_a;
	queue->queue_size ++;
	int cond = 1;	
	while (queue->queue_size != 0 && cond == 1) {

		size_t current_vertex = queue->queue[queue->front];
		queue->front ++;
		queue->queue_size --;
		
		for (size_t i = 0; i < users[current_vertex].n_following; i++) {
			size_t index = users[current_vertex].following_idxs[i];
			size_t id = users[users[current_vertex].following_idxs[i]].user_id;
			if (visited[index] == 0) {
				visited[index] = 1;
				distance[index] = distance[current_vertex] + 1;
				parent_a[index] = current_vertex;
				
				//printf("Current user %zu is following: %zu\n", users[current_vertex].user_id, id);
				if (queue->front == -1) {
					queue->front = 0;
				}
				queue->rear ++;
				queue->queue[queue->rear] = index;
				queue->queue_size ++;

				if (id == userB) {
					cond = 0;
					break;
				}
					
			}

		}
	}
	

	int dist_a_to_b = distance[index_b];

	//printf("The distance from A to B is %d!\n", dist_a_to_b);
	
	// now find b->a fml
	// reset
	int parent_b[count];
	for (int i = 0; i < count; i++) {
		visited[i] = 0;
		parent_b[i] = -1;
	}
	distance[index_b] = 0;
	distance[index_a] = 0;
	visited[index_b] = 1;
	
	//struct queue *queue2 = malloc(sizeof(struct queue));
	queue->front = 0;
	queue->rear = -1;
	queue->queue_size = 0;
	//queue2->queue = malloc(sizeof(size_t) * count * 10);

	queue->rear ++;
	queue->queue[queue->rear] = index_b;
	queue->queue_size ++;
	cond = 1;
	while (queue->queue_size != 0 && cond == 1) {
		
		size_t current_vertex = queue->queue[queue->front];
		queue->front ++;
		queue->queue_size --;
		
		for (size_t i = 0; i < users[current_vertex].n_following; i++) {
			size_t index = users[current_vertex].following_idxs[i];
			size_t id = users[users[current_vertex].following_idxs[i]].user_id;
			if (visited[index] == 0) {
				visited[index] = 1;
				distance[index] = distance[current_vertex] + 1;
				parent_b[index] = current_vertex;
				
				//printf("Current user %zu is following: %zu\n", users[current_vertex].user_id, id);
				if (queue->front == -1) {
					queue->front = 0;
				}
				queue->rear ++;
				queue->queue[queue->rear] = index;
				queue->queue_size ++;

				if (id == userA) {
					cond = 0;
					break;
				}
					
			}

		}
	}

	int dist_b_to_a = distance[index_a];
	
	//printf("The distance from B to A is %d!\n", dist_b_to_a);
	
	int j;
	size_t current;
	
	// no path exists
	if (dist_a_to_b == 0 && dist_b_to_a == 0) {
		result->elements = NULL;
		result->n_elements = 0;
		free(queue->queue);
		free(queue);
		return result;
	}
	// path A->B < B->A, or only path A->B
	if (dist_b_to_a == 0 || dist_a_to_b <= dist_b_to_a) {
		current = index_b;
		result->elements = malloc(sizeof(struct user) * dist_a_to_b + 1);
		result->n_elements = dist_a_to_b + 1;
		result->elements[0] = &users[index_a];
		j = dist_a_to_b;
		while (parent_a[current] != -1) {
			result->elements[j] = &users[current];
			j--;
			current = parent_a[current];
		}
	} else {
		current = index_a;
		result->elements = malloc(sizeof(struct user) * dist_b_to_a + 1);
		result->n_elements = dist_b_to_a + 1;
		j = dist_b_to_a;
		result->elements[0] = &users[index_b];
		while (parent_b[current] != -1) {
			result->elements[j] = &users[current];
			j--;
			current = parent_b[current];
		}
	}

	free(queue->queue);
	free(queue);
	return result;
}

result* find_bots(user* users, size_t user_count, post* posts, size_t post_count, criteria* crit, query_helper* helper) {
	struct result *result = malloc(sizeof(struct result));
	if (users == NULL || user_count == 0 || posts == NULL || post_count == 0 || crit == NULL) {
		result->elements = NULL;
		result->n_elements = 0;
		return result;
	} else {
		if (crit->oc_threshold > 1 || crit->oc_threshold < 0) {
			result->elements = NULL;
			result->n_elements = 0;
			return result;

		} else if (crit->acc_rep_threshold > 1 || crit->acc_rep_threshold < 0) {
			result->elements = NULL;
			result->n_elements = 0;
			return result;
		} else if (crit->bot_net_threshold > 1 || crit->bot_net_threshold < 0) {
			result->elements = NULL;
			result->n_elements = 0;
			return result;
		}
	}

	// everything after here is a-ok to run!
	
	int repost[post_count];
	
	memset(repost, 0, post_count * sizeof(int));

	for (size_t i = 0; i < post_count; i++) {
		for (size_t j = 0; j < posts[i].n_reposted; j++) {
			repost[posts[i].reposted_idxs[j]] = 141;
		}	
	}
	//printf("Final: %d\n", repost[0]);
	int user[user_count];
	int bot[user_count];
	for (size_t i = 0; i < user_count; i++) {
		bot[i] = 0;
		user[i] = 0;
	}	
	result->elements = malloc(sizeof(struct user) * user_count);
	result->n_elements = 0;
	int index = 0;
	int user_index = 0;
	int update = 0;
	for (size_t i = 0; i < user_count; i++) {
		
		 //check account reputation
	      	 if (((float) users[i].n_followers / (float)(users[i].n_followers + users[i].n_following)) < crit->acc_rep_threshold) { 
		        // beep boop
		        bot[i] = 1;
		 } else {

			float user_reposts = 0;
			for (size_t j = 0; j < users[i].n_posts; j++) {
				if (repost[users[i].post_idxs[j]] == 141) {
					user_reposts++;
				}
			}

			// check OC content	
			if ((user_reposts /(float) users[i]. n_posts) > crit->oc_threshold) { 
				// beep boop
				bot[i] = 1;

			} else {

				float bots_following  = 0;
				for (size_t j = 0; j < users[i].n_followers; j++) {
					if (bot[users[i].follower_idxs[j]] == 1) {
						bots_following++;
					}
				}
			
				// check bot net
				if ((bots_following / (float) users[i].n_followers) > crit->bot_net_threshold) {				
					// beep boop
					bot[i] = 1;
					update = 1;
				}
			}
		}

		// add bot to list
		if (bot[i] == 1) {
			result->elements[index] = &users[i];
			index ++;
		} else {
			user[user_index] = 1;
			user_index ++;
		}
		
	}
	
	while (update == 1) {
		int changed = 0;
		for (size_t i = 0; i < user_count; i++) {
			if (user[i] != 1) {
				update = 0;
				break;
			}	
			float bots_following = 0;
			for (size_t j = 0; j < users[i].n_followers; j++) {
				if (bot[users[i].follower_idxs[j]] == 1) {
					bots_following++;
				}
			}
			float n_followers = users[i].n_followers;
			if ((bots_following / n_followers) > crit->bot_net_threshold) {
				result->elements[index] = &users[i];
				bot[i] = 1;
				index++;
				changed = 1;
			}
		}
		if (changed == 0) {
			break;
		}
	}

		
	result->n_elements = index;
	//free(repost);
	//free(bot);
	return result;
}

void engine_cleanup(query_helper* helpers) {
	//Clean up your engine
}


