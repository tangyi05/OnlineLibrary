
int book_catalog(char lib[][3][50], int total, char rent_lib[][3][50], int rent_total);
int available_book_catalog(char lib[][3][50], int total);
int rented_book_catalog(char rent_lib[][3][50], int rent_total);

int add_book(char lib[][3][50], int *p_total);
int print_book(char lib[][3][50], int total, int book_num);
int search_menu(char lib[][3][50], int total);
int search_by_title(char lib[][3][50], int total, char *p_title);
int search_by_publisher(char lib[][3][50], int total, char *p_publisher);
int search_by_author(char lib[][3][50], int total, char *p_author);
int rent_book(char lib[][3][50], int *total, char rent[][3][50], int *rent_total);
int return_book(char lib[][3][50], int *total, char rent[][3][50], int *rent_total);