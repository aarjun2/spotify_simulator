#include "definition.h"
#include "test.h"

int main(void) {
	Node* head = NULL;
	FILE* infile = NULL;
	FILE* outfile = NULL;
	char line[100];
	char whole_line[100];
	char* token;
	Record records;
	Record new_rec;
	char artist_name[100];
	int count = 0, option = 0, print_option = 0, sort_option = 0, index = 0, new_rating = 0;
	char target_artist[100];
	char target_song[100];
	char target_album[100];
	char temp_arr[100];
	char empty_arr[100];
	strcpy(temp_arr, "\0");

	while (option != 11) {
		option = display_menu();
		system("pause");
		system("cls");
		switch (option) {
		case 1:
			infile = fopen("musicPlayList.csv", "r");
			if (infile == NULL) {
				printf("file cannot be opened");
				return 0; //stopping program here
			}
			while (!feof(infile)) {
				if (fgets(line, 100, infile) == NULL) {
					break; // error or end of file reached
				}
				count = 0;
				char* ptr;
				ptr = line;
				for (; *ptr != '\0'; ptr++) {
					if (*ptr == ',') {
						count++;
					}
				}
				if (count == 7) {
					token = strtok(line, ",");
					strcpy(records.Artist, token);
					token = strtok(NULL, ",");
					strcat(records.Artist, ",");
					strcat(records.Artist, token);
					for (index = 1; index < (strlen(records.Artist) - 1); index++) {
						temp_arr[index - 1] = records.Artist[index];
					}
					temp_arr[index - 1] = '\0';
					strcpy(records.Artist, temp_arr);
					token = strtok(NULL, ",");
					strcpy(records.Album_title, token);
					token = strtok(NULL, ",");
					strcpy(records.Song_title, token);
					token = strtok(NULL, ",");
					strcpy(records.Genre, token);
					token = strtok(NULL, ":");
					records.song_length.minutes = atoi(token);
					token = strtok(NULL, ",");
					records.song_length.seconds = atoi(token);
					token = strtok(NULL, ",");
					records.times_played = atoi(token);
					token = strtok(NULL, ",");
					records.rating = atoi(token);
					insert_from_head(&head, records);
				}
				else {
					token = strtok(line, ",");
					strcpy(records.Artist, token);
					token = strtok(NULL, ",");
					strcpy(records.Album_title, token);
					token = strtok(NULL, ",");
					strcpy(records.Song_title, token);
					token = strtok(NULL, ",");
					strcpy(records.Genre, token);
					token = strtok(NULL, ":");
					records.song_length.minutes = atoi(token);
					token = strtok(NULL, ",");
					records.song_length.seconds = atoi(token);
					token = strtok(NULL, ",");
					records.times_played = atoi(token);
					token = strtok(NULL, ",");
					records.rating = atoi(token);
					insert_from_head(&head, records);
				}
			}
			fclose(infile);
			printf("data loaded\n");
			break;
		case 2:
			if (head == NULL) {
				printf("\nno record to store\n");
				break;
			}
			outfile = fopen("musicPlayList.csv", "w");
			if (outfile != NULL) {
				write_to_file(outfile, head);
				fclose(outfile);
			}
			else {
				printf("\nfile cannot be opened to store\n");
			}
			break;
		case 3:
			if (head == NULL) {
				printf("\nno records to print\n");
				break;
			}
			printf("1. Print all records\n2. Print all records that match an Artist\n");
			printf("choose an option: ");
			scanf("%d", &print_option);
			if (print_option == 1) {
				print_doublelist(head);
			}
			if (print_option == 2) {
				printf("enter the name of artist: ");
				strcpy(target_artist, "\0");
				gets(empty_arr);
				gets(target_artist);
				print_by_artist(head, target_artist);
			}
			break;
		case 4:
			if (head == NULL) {
				printf("no data to insert");
				break;
			}
			strcpy(new_rec.Artist, "\0");
			strcpy(new_rec.Album_title, "\0");
			strcpy(new_rec.Song_title, "\0");
			strcpy(new_rec.Genre, "\0");
			printf("Enter artist name: ");
			gets(empty_arr);
			gets(new_rec.Artist);
			printf("Enter Album title: ");
			//gets(empty_arr);
			gets(new_rec.Album_title);
			printf("Enter Song title: ");
			gets(new_rec.Song_title);
			printf("Enter Genre: ");
			gets(new_rec.Genre);
			printf("Enter Duration minutes: ");
			scanf("%d", &new_rec.song_length.minutes);
			printf("Enter Duration seconds: ");
			scanf("%d", &new_rec.song_length.seconds);
			printf("Enter times played: ");
			scanf("%d", &new_rec.times_played);
			printf("Enter rating(between 1 to 5): ");
			scanf("%d", &new_rec.rating);
			insert_at_front(&head, new_rec);
			break;
		case 5:
			if (head == NULL) {
				printf("\nload data first, no record to delete\n");
				break;
			}
			printf("Enter a song record to delete: ");
			strcpy(target_song, "\0");
			gets(empty_arr);
			gets(target_song);
			delete_a_specific(&head, target_song);
			break;
		case 6:
			if (head == NULL) {
				printf("\nload data first, no record to edit\n");
				break;
			}
			printf("Enter an artist name to edit: ");
			strcpy(target_artist, "\0");
			gets(empty_arr);
			gets(target_artist);
			edit(head, target_artist);
			break;
		case 7:
			if (head == NULL) {
				printf("\nload data first, no record to sort\n");
				break;
			}
			printf("1.Sort based on Artist(A-Z)\n2. Sort based on Album title(A-Z)\n3. Sort based on rating(1-5)\n4. Sort based on Album title(largest to smallest)\n");
			scanf("%d", &sort_option);
			if (sort_option == 1) {
				sort_list_artist(&head);
				print_doublelist(head);
			}
			if (sort_option == 2) {
				sort_list_albumtitle(&head);
				print_doublelist(head);
			}
			if (sort_option == 3) {
				sort_list_rating(&head);
				print_doublelist(head);
			}
			if (sort_option == 4) {
				sort_list_times_played(&head);
				print_doublelist(head);
			}
			break;
		case 8:
			if (head == NULL) {
				printf("\nload data first, no record to rate\n");
				break;
			}
			printf("Enter a song record to change rating: \n");
			strcpy(target_song, "\0");
			gets(empty_arr);
			gets(target_song);
			printf("Enter new rating: \n");
			scanf("%d", &new_rating);
			if (new_rating < 1 || new_rating > 5) {
				printf("Enter new rating: \n");
				scanf("%d", &new_rating);
			}
			rate_song(head,new_rating,target_song);
			break;
		case 9:
			if (head == NULL) {
				printf("\nload data first, no record to play\n");
				break;
			}
			printf("Enter a song record to play from: \n");
			strcpy(target_song, "\0");
			gets(empty_arr);
			gets(target_song);
			play_song(&head, target_song);
			break;
		case 10:
			if (head == NULL) {
				printf("\nload data first, no record to shuffle\n");
				break;
			}
			shuffle(&head);
			break;
		case 11:
			if (head == NULL) {
				printf("\nexit\n");
				break;
			}
			if (head != NULL) {
				outfile = fopen("musicPlayList.csv", "w");
				write_to_file(outfile, head);
				fclose(outfile);
				Node* temp = head;
				Node* to_delete = NULL;
				while (temp != NULL) {
					to_delete = temp;
					temp = temp->next;
					free(to_delete);// clearing data in heap
				}
			}
			break;
		}
	}
	printf("\ntest functions: \n");
	test_insert();
	test_delete();
	test_shuffle();
	return 0;
} 
