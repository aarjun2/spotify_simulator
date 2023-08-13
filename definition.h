#define _CRT_SECURE_NO_WARNINGS // necessary to ignore scanf_s () warnings


#include <string.h>
#include <stdio.h> // necessary to use printf () and scanf ()
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

typedef struct duration {
	int minutes;
	int seconds;
}Duration;
typedef struct record {
	char Artist[100];
	char Album_title[100];
	char Song_title[100];
	char Genre[100];
	Duration song_length;
	int times_played;
	int rating;
}Record;
typedef struct Nodes {
	Record data;
	struct Nodes* prev;
	struct Nodes* next;
}Node;
Node* get_node(Record value);
int insert_from_head(Node** head, Record value);
void insert_at_front(Node** head, Record value);
void print_doublelist(Node* head);
void print_by_artist(Node* head, char *artist_name);
void sort_list_rating(Node** head);
void sort_list_artist(Node** head);
void sort_list_albumtitle(Node** head);
void sort_list_times_played(Node** head);
void delete_a_specific(Node** head, char* song_title);
void play_song(Node** head, char* song_select);
void shuffle(Node** head);
void rate_song(Node* head, int rating, char* song_title);
void write_to_file(FILE* outfile, Node* head);
void edit(Node* head, char* target_artist);