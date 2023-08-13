#include "definition.h"
/**********
function: Display menu
Date created: 2/10/2022
Date last modified: 2/10/2022, 2/11/2022, 2/13/2022
Description: Displays the menu options from 1-11 and allows the user to pick an option to execute the command
Input parameters: Nothing
Returns: returns the integer option chosen by the user
preconditions: none
postconditions: if executed right, will send the option the user wants to execute
**/
void display_menu() {
	int option = 0;
	printf("1. Load\n2. Store\n3. Display\n4. Insert\n5.Delete\n6. Edit\n7. Sort\n8. Rate\n9. Play\n10. Shuffle\n11. Exit\n");
	printf("choose an option: ");
	scanf("%d", &option);
	return option;
}
/**********
function:get node
Date created: 1/31/2022
Date last modified: 1/31/2022
Description: allocates space for new node, and inserts data into the node 
Input parameters: data to store in node in the form of Record Struct
Returns: returns new node with the data
preconditions:data must be inputted and stored in struct
postconditions: if executed right, this will alloctae space for node on the heap and return it 
**/
Node* get_node(Record value) {
	Node* new_node = (Node*)malloc(sizeof(Node));
	if (new_node == NULL) {
		return new_node;
	}
	new_node->data = value;
	new_node->prev = NULL;
	new_node->next = NULL;
	return new_node;
}
/**********
function:get node
Date created: 1/31/2022
Date last modified: 1/31/2022
Description: takes the new node and connects it using links from the head
Input parameters: data to store in form of Record Struct, and the address of head
Returns: returns one if insertion is successful and 0 if its not
preconditions:data must be inputted and stored in struct, and head pointer must be set to NULL or another node
postconditions: if executed right, this will insert the node before head
**/
int insert_from_head(Node** head, Record value) {
	Node* new_node = get_node(value);
	if (new_node == NULL) {
		return 0;
	}
	if ((*head) == NULL) {
		(*head) = new_node; // since no value exists, the new node becomes head
		return;
	}
	(*head)->prev = new_node;
	new_node->next = (*head);
	(*head) = new_node;
	return 1;
}
/**********
function:print doubly linked list
Date created: 1/31/2022
Date last modified: 1/31/2022, 2/1/2022, 2/2/2022
Description: prints the doubly linked list to the screen, by moving from head to NULL and prinitng each data
Input parameters: the head node
Returns: none
preconditions:data should be stored in head atleast
postconditions: if executed right, this will print out the entire list
**/
void print_doublelist(Node* head) {
	Node* temp;
	temp = head;
	while (temp != NULL) {
		printf("%s\n", temp->data.Artist);
		printf("%s\n", temp->data.Album_title);
		printf("%s\n", temp->data.Song_title);
		printf("%s\n", temp->data.Genre);
		printf("%d:", temp->data.song_length.minutes);
		printf("%d\n", temp->data.song_length.seconds);
		printf("%d\n", temp->data.times_played);
		printf("%d\n", temp->data.rating);
		temp = temp->next;
	}
}
/**********
function:print specific artist
Date created: 2/1/2022
Date last modified: 2/1/2022, 2/1/2022, 2/5/2022
Description: prints the node containing a specific aritst and their records
Input parameters: the head node of the list and the specific artist you want to print
Returns: none
preconditions:data must be inserted in the list 
postconditions: if executed right, this will return all nodes containing records of the target artist
**/
void print_by_artist(Node* head, char* artist_name) {
	Node* temp;
	temp = head;
	while (temp != NULL) {
		if (strcmp(artist_name, temp->data.Artist) == 0) {
			printf("%s\n", temp->data.Album_title);
			printf("%s\n", temp->data.Song_title);
			printf("%s\n", temp->data.Genre);
			printf("%d:", temp->data.song_length.minutes);
			printf("%d\n", temp->data.song_length.seconds);
			printf("%d\n", temp->data.times_played);
			printf("%d\n", temp->data.rating);
		}
		temp = temp->next;
	}
}
/**********
function: rate song
Date created: 2/1/2022
Date last modified: 2/1/2022, 2/1/2022, 2/5/2022, 2/6/2022
Description: prints the node containing a specific song and then when inputted new rating in Main
will replace the new rating in that node
Input parameters: the head node of the list and the specific song you want to change rating to and the 
new rating
Returns: none
preconditions:data must be inserted in the list
postconditions: if executed right, this will change the rating of a specific song
**/
void rate_song(Node* head, int rating, char* song_title) {
	Node* temp;
	temp = head;
	while (temp != NULL) {
		if (strcmp(song_title, temp->data.Song_title) == 0) {
			temp->data.rating = rating;
			return;
		}
		temp = temp->next;
	}
	return;
}
/**********
function:get node
Date created: 1/31/2022
Date last modified: 1/31/2022
Description: takes the new node and connects it using links from the head
Input parameters: data to store in form of Record Struct, and the address of head
Returns: returns one if insertion is successful and 0 if its not
preconditions:data must be inputted and stored in struct, and head pointer must be set to NULL or another node
postconditions: if executed right, this will insert the node before head
**/
void insert_at_front(Node** head, Record value) {
	Node* new_node = get_node(value);
	if (new_node->data.rating < 1 || new_node->data.rating > 5) {
		printf("\ninvalid rating\n");
		return;
	}
	if (new_node->data.times_played < 0) {
		printf("\ninvalid time played\n");
		return;
	}
	if ((*head) == NULL) {
		(*head) = new_node; // since no value exists, the new node becomes head
		return;
	}
	(*head)->prev = new_node;
	new_node->next = (*head);
	(*head) = new_node;
}
/**********
function:delete node
Date created: 2/7/2022
Date last modified:2/7/2022, 2/8/2022,2/9/2022
Description: deletes the specific node containing the song inputted from user
Input parameters: the target song to delete and the address of head
Returns: none
preconditions:data must be inputted for usefulness but not required
postconditions: if executed right, this will free the node that contains the target song
**/
void delete_a_specific(Node** head, char *song_title) {
	Node* temp = (*head);
	while (temp != NULL) {
		if (strcmp(song_title, temp->data.Song_title) == 0) {
			if (temp == (*head)) {
				(*head) = (*head)->next;
				(*head)->prev = NULL;
			}
			else {
				temp->prev->next = temp->next;
				temp->next->prev = temp->prev;
			}
			free(temp);
			return;
		}
		temp = temp->next;
	}
}
/**********
function:sort rating
Date created: 2/7/2022
Date last modified:2/7/2022, 2/8/2022,2/9/2022, 2/10/2022
Description: sorts the rating in ascending order
Input parameters: the address of head
Returns: none
preconditions:data must be inputted for usefulness but not required
postconditions: if executed right, this will arrange the data of rating in ascending order
**/
void sort_list_rating(Node** head) {
	Node* temp;
	Node* temp_next;
	temp = (*head);
	int value = 0;
	while (temp != NULL) {
		temp_next = temp->next;
		while (temp_next != NULL) {
			if (temp->data.rating > temp_next->data.rating) {
				value = temp->data.rating;
				temp->data.rating = temp_next->data.rating;
				temp_next->data.rating = value;
			}
			temp_next = temp_next->next;
		}
		temp = temp->next;
	}
}
/**********
function:sort Artist
Date created: 2/7/2022
Date last modified:2/7/2022, 2/8/2022,2/9/2022, 2/10/2022
Description: sorts the Artists alphabetically
Input parameters: the address of head
Returns: none
preconditions:data must be inputted for usefulness but not required
postconditions: if executed right, this will arrange the data of Artists alphabetically
**/
void sort_list_artist(Node** head) {
	Node* temp;
	Node* temp_next;
	temp = (*head);
	char place_holder[100];
	while (temp != NULL) {
		temp_next = temp->next;
		while (temp_next != NULL) {
			if (strcmp(temp->data.Artist, temp_next->data.Artist) > 0) {
				strcpy(place_holder, temp->data.Artist);
				strcpy(temp->data.Artist, temp_next->data.Artist);
				strcpy(temp_next->data.Artist, place_holder);
			}
			temp_next = temp_next->next;
		}
		temp = temp->next;
	}
}
/**********
function:sort Album title
Date created: 2/7/2022
Date last modified:2/7/2022, 2/8/2022,2/9/2022, 2/10/2022
Description: sorts the Albums alphabetically
Input parameters: the address of head
Returns: none
preconditions:data must be inputted for usefulness but not required
postconditions: if executed right, this will arrange the data of Albums alphabetically
**/
void sort_list_albumtitle(Node** head) {
	Node* temp;
	Node* temp_next;
	temp = (*head);
	char place_holder[100];
	while (temp != NULL) {
		temp_next = temp->next;
		while (temp_next != NULL) {
			if (strcmp(temp->data.Album_title, temp_next->data.Album_title) > 0) {
				strcpy(place_holder, temp->data.Album_title);
				strcpy(temp->data.Album_title, temp_next->data.Album_title);
				strcpy(temp_next->data.Album_title, place_holder);
			}
			temp_next = temp_next->next;
		}
		temp = temp->next;
	}
}
/**********
function:sort rating
Date created: 2/7/2022
Date last modified:2/7/2022, 2/8/2022,2/9/2022, 2/10/2022
Description: sorts the rating in descending order
Input parameters: the address of head
Returns: none
preconditions:data must be inputted for usefulness but not required
postconditions: if executed right, this will arrange the data of rating in descending order
**/
void sort_list_times_played(Node** head) {
	Node* temp;
	Node* temp_next;
	temp = (*head);
	int value = 0;
	while (temp != NULL) {
		temp_next = temp->next;
		while (temp_next != NULL) {
			if (temp->data.times_played < temp_next->data.times_played) {
				value = temp->data.times_played;
				temp->data.times_played = temp_next->data.times_played;
				temp_next->data.times_played = value;
			}
			temp_next = temp_next->next;
		}
		temp = temp->next;
	}
}
/**********
function: Play song
Date created: 2/11/2022
Date last modified:2/11/2022, 2/12/2022, 2/13/2022,2/14/2022
Description: Plays from a certain song till the end, stays on screen for couple seconds using sleep
Input parameters: the address of head, and the specific song you want to play from
Returns: none
preconditions:data must be inputted from the csv file
postconditions: if executed right, this will play all songs from a specific song
**/
void play_song(Node** head, char* song_select) {
	Node* temp;
	temp = (*head);
	Node* song_beg = NULL;
	while (temp != NULL) {
		if (strcmp(song_select, temp->data.Song_title) == 0) {
			song_beg = temp;
		}
		temp = temp->next;
	}
	while (song_beg != NULL) {
		printf("%s\n", song_beg->data.Artist);
		printf("%s\n", song_beg->data.Album_title);
		printf("%s\n", song_beg->data.Song_title);
		printf("%s\n", song_beg->data.Genre);
		printf("%d:", song_beg->data.song_length.minutes);
		printf("%d\n", song_beg->data.song_length.seconds);
		printf("%d\n", song_beg->data.times_played);
		printf("%d\n", song_beg->data.rating);
		Sleep(30);
		system("cls");
		song_beg = song_beg->prev;
	}
}
/**********
function:shuffle
Date created: 2/7/2022
Date last modified:2/7/2022, 2/8/2022,2/9/2022, 2/10/2022
Description: generates a random order and if its smaller than previous index it goes backwards else forwards,
rearranges the data in the nodes to match order
Input parameters: the address of head
Returns: none
preconditions:data must be inputted, the order must generate the amount of numbers as size
postconditions: if executed right, this will shuffle the playlist to match the order
**/
void shuffle(Node** head) {
	Node* temp = (*head);
	Node* current = (*head);
	int size = 0, current_index = 0;
	int x = 0;
	time_t t;
	srand((unsigned)time(&t));
	while (temp != NULL) {
		size++;
		temp = temp->next;
	}
	current = (*head);
	for (int i = 0; i < size; i++) {
		x = rand() % size;
		printf("Record number: %d\n", x);
		if (current_index < x) {
			for (int i = current_index+1; i <= x;i++) {
				current = current->next;
			}
			if (current != NULL) {
				printf("%s\n", current->data.Artist);
				printf("%s\n", current->data.Album_title);
				printf("%s\n", current->data.Song_title);
				printf("%s\n", current->data.Genre);
				printf("%d:", current->data.song_length.minutes);
				printf("%d\n", current->data.song_length.seconds);
				printf("%d\n", current->data.times_played);
				printf("%d\n", current->data.rating);
			}
		}
		else {
			for (int i = current_index-1; i >= x; i--) {
				current = current->prev;
			}
			if (current != NULL) {
				printf("%s\n", current->data.Artist);
				printf("%s\n", current->data.Album_title);
				printf("%s\n", current->data.Song_title);
				printf("%s\n", current->data.Genre);
				printf("%d:", current->data.song_length.minutes);
				printf("%d\n", current->data.song_length.seconds);
				printf("%d\n", current->data.times_played);
				printf("%d\n", current->data.rating);
			}
		}
		current_index = x;
	}
}
/**********
function:write to file
Date created: 2/7/2022
Date last modified:2/7/2022, 2/8/2022,2/9/2022, 2/10/2022
Description: writes the update data back to excel file
Input parameters: the address of head, and the pointer to the output file
Returns: none
preconditions:data must be inputted
postconditions: if executed right, this will output the data and overwrite the musicPlayList file
**/
void write_to_file(FILE* outfile, Node* head) {
	Node* temp = head;
	int index = 0;
	char temp_arr[100];
	while (temp->next != NULL) {
		temp = temp->next;
	}

	while (temp != NULL) {
		int count_comma = 0;
		strcpy(temp_arr, temp->data.Artist);
		for (int i = 0; i < strlen(temp_arr); i++) {
			if (temp_arr[i] == ',') {
				count_comma++;
			}
		}
		if (count_comma == 0) {
			fprintf(outfile, "%s,", temp->data.Artist);
			fprintf(outfile, "%s,", temp->data.Album_title);
			fprintf(outfile, "%s,", temp->data.Song_title);
			fprintf(outfile, "%s,", temp->data.Genre);
			fprintf(outfile, "%d:", temp->data.song_length.minutes);
			fprintf(outfile, "%d,", temp->data.song_length.seconds);
			fprintf(outfile, "%d,", temp->data.times_played);
			fprintf(outfile, "%d\n", temp->data.rating);
		}
		if (count_comma == 1) {
			strcpy(temp_arr, "\0");
			temp_arr[0] = '"';
			for (index = 0; index < strlen(temp->data.Artist); index++) {
				temp_arr[index + 1] = temp->data.Artist[index];
			}
			temp_arr[index+1] = '"';
			temp_arr[index+2] = '\0';
			fprintf(outfile, "%s,", temp_arr);
			fprintf(outfile, "%s,", temp->data.Album_title);
			fprintf(outfile, "%s,", temp->data.Song_title);
			fprintf(outfile, "%s,", temp->data.Genre);
			fprintf(outfile, "%d:", temp->data.song_length.minutes);
			fprintf(outfile, "%d,", temp->data.song_length.seconds);
			fprintf(outfile, "%d,", temp->data.times_played);
			fprintf(outfile, "%d\n", temp->data.rating);
		}
		temp = temp->prev;
	}
}
void edit(Node* head, char* target_artist) {
	Node* temp = head;
	Node** arr;
	char null_arr[100];
	char arr_to_change[100];
	int user_value = 0;
	arr = malloc(sizeof(Node*) * 3);
	int i = 0, choice = 0, attri_choice = 0;
	while (temp != NULL) {
		if (strcmp(target_artist, temp->data.Artist) == 0) {
			arr[i] = temp;
			i++;
		}
		temp = temp->next;
	}
	if (i == 0) {
		printf("\nNo matches found\n");
		return;
	}
	for (int j = 0; j < i; j++) {
		printf("\nRecord: %d\n", j+1);
		printf("%s\n", arr[j]->data.Artist);
		printf("%s\n", arr[j]->data.Album_title);
		printf("%s\n", arr[j]->data.Song_title);
		printf("%s\n", arr[j]->data.Genre);
		printf("%d:", arr[j]->data.song_length.minutes);
		printf("%d\n", arr[j]->data.song_length.seconds);
		printf("%d\n", arr[j]->data.times_played);
		printf("%d\n", arr[j]->data.rating);
		printf("\n");
	}
	printf("\nEnter record you want to edit: (enter integer 1 for first record)\n");
	scanf("%d", &choice);
	if ((choice - 1) <= i) {
		while (attri_choice != 9) {
			printf("Which do you want to edit:\n 1. Artist name\n2. Album title\n3. Song title\n4. Genre\n5. Song minutes\n6. Song seconds\n7. Song times played\n8. Song rating\n9. Exit\n");
			scanf("%d", &attri_choice);
			switch (attri_choice) {
			case 1:
				printf("\nenter value to change: ");
				strcpy(arr_to_change, "\0");
				gets(null_arr);
				gets(arr_to_change);
				strcpy(arr[choice - 1]->data.Artist, arr_to_change);
				break;
			case 2:
				printf("\nenter value to change: ");
				strcpy(arr_to_change, "\0");
				gets(null_arr);
				gets(arr_to_change);
				strcpy(arr[choice - 1]->data.Album_title, arr_to_change);
				break;
			case 3:
				printf("\nenter value to change: ");
				strcpy(arr_to_change, "\0");
				gets(null_arr);
				gets(arr_to_change);
				strcpy(arr[choice - 1]->data.Song_title, arr_to_change);
				break;
			case 4:
				printf("\nenter value to change: ");
				strcpy(arr_to_change, "\0");
				gets(null_arr);
				gets(arr_to_change);
				strcpy(arr[choice - 1]->data.Genre, arr_to_change);
				break;
			case 5:
				printf("\nenter value to change: ");
				scanf("%d", &user_value);
				arr[choice - 1]->data.song_length.minutes = user_value;
				break;
			case 6:
				printf("\nenter value to change: ");
				scanf("%d", &user_value);
				arr[choice - 1]->data.song_length.seconds = user_value;
				break;
			case 7:
				printf("\nenter value to change: ");
				scanf("%d", &user_value);
				arr[choice - 1]->data.times_played = user_value;
				break;
			case 8:
				printf("\nenter value to change: ");
				scanf("%d", &user_value);
				arr[choice - 1]->data.rating = user_value;
				break;
			case 9:
				printf("\nexiting");
				system("pause");
				system("cls");
				break;
			}
		}
	}
}