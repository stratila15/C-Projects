#include <curses.h>
#include <panel.h>
#include <string.h>
#include <stdlib.h>
#include <menu.h>
#include <unistd.h>
#include <time.h>

#define K_DOWN        0102            /* down-arrow key */
#define K_UP          0101            /* up-arrow key */

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))
#define CTRLD   4

char *choices[] = {
	"New Game",
	"Resume Game",
	"Quit"
};
char *choices1[] = {
	"SKIP",
	"50/50"
};

char *choices2[] = {
	" ",
	" ",
	" ",
	" "
};
unsigned int resume_enable = 0;
unsigned int EOF_FI = 0;
unsigned int NLINES = 40;
unsigned int NCOLS = 120;
unsigned int right, left;
unsigned int right_res, left_res;

void get_lines_blank(void);
void check_ans(char * name, char * ans);
void new_game(void);
void resume_game(void);
void func(char * name);
void func1(char * name);
void init_wins(WINDOW **wins, int n);
void win_show(WINDOW *win, char *label,char * label1, int label_color);
void print_in_middle(WINDOW *win, int starty, int startx, int width, char *string, chtype color);


PANEL *my_panels[3];
WINDOW *my_wins[3];
ITEM **main_items;
MENU *main_menu;
MENU *act_menu;
MENU *opt_menu;
MENU *fif_menu;
MENU *fif_res_menu;
MENU *opt_res_menu;
MENU *res_menu;
ITEM *cur_item;
PANEL *top;


FILE *fp, *fs;
int score = 0;
int lala = 0;
int kaka = 0;
int ca = 0;
int wa = 0;
char s_old[10]="";
int score_old;
unsigned int resume_abnormal = 0;
int main(int argc,char *argv[])
{  
	time_t t1;
	struct tm *t2;
	time(&t1);
	t2=localtime(&t1);
	int n_choices, i;
	int ch;


	fp = fopen(argv[1],"r");
	if (fp == 0){
		printf("File Is missing\n");
		return -1;
	}
	fs = fopen("score","r+");
	if (fs == 0){
		printf("Score File Is missing\n");
		return -1;
	}

	fgets(s_old,10,fs);
	score_old = atoi(s_old);


	/* Initializarea curses */
	initscr();
	start_color();
	cbreak();
	noecho();
	curs_set(FALSE);
	keypad(stdscr, TRUE);


	/* Initializarea culorilor */
	init_pair(3, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_YELLOW, COLOR_BLACK);
	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	init_pair(4, COLOR_CYAN, COLOR_BLACK);
	bkgd(COLOR_PAIR(2));
	init_wins(my_wins, 2);
	
	/* Attach a panel to each window */
	my_panels[0] = new_panel(my_wins[0]);
	my_panels[1] = new_panel(my_wins[1]);

	/* Set up the user pointers to the next panel */
	set_panel_userptr(my_panels[0], my_panels[1]);
	set_panel_userptr(my_panels[1], my_panels[0]);
	/* Update the stacking order. 2nd panel will be on top */
	update_panels();
	/* Afisarea pe ecran */
	attron(COLOR_PAIR(4));
	mvprintw(LINES - 2, 0, "Foloseste sagetile SUS si JOS pentru a alege optiunea din menu (Q pentru a iesi)");
	attroff(COLOR_PAIR(4));
	doupdate();

	/* Initializarea itemilor */
	n_choices = ARRAY_SIZE(choices);
	main_items = (ITEM **)calloc(n_choices + 1, sizeof(ITEM *));
	for(i = 0; i < n_choices; ++i)
	{
		main_items[i] = new_item(choices[i], choices[i]);        /* Set the user pointer */
		set_item_userptr(main_items[i], func);
	}
	main_items[n_choices] = (ITEM *)NULL;     /* Crearea meniului */
	main_menu = new_menu((ITEM **)main_items);  /* Postarea meniului */

	set_menu_win(main_menu, my_wins[1]);
	set_menu_sub(main_menu, derwin(my_wins[1], 6, 38, NLINES/3, NCOLS/3));

	set_menu_format(main_menu, 3, 1);
	menu_opts_off(main_menu, O_SHOWDESC);
	/* Setarea semnului pentru menu " -->" */
	set_menu_mark(main_menu, " --> ");
	
	/*Putina creativitate*/	
	wattron(my_wins[1], COLOR_PAIR(3));
	mvwprintw(my_wins[1], 6, 40, " .--|''''''''''''''''''''|");
	mvwprintw(my_wins[1], 7, 40, " / - | 'CHRISTMAS TRIVIA' |");
	mvwprintw(my_wins[1], 8, 40, "''-O-'''''''''''''''O''O''''-");
	wattroff(my_wins[1], COLOR_PAIR(3));


	wattron(my_wins[1], COLOR_PAIR(1));
	mvwprintw(my_wins[1],10,18,",''.");
	mvwprintw(my_wins[1],11,7,"       ._.,-   ,");
	mvwprintw(my_wins[1],12,7,"         ,'...'___'");
	mvwprintw(my_wins[1],13,7,"         .,......~.'-.");
	mvwprintw(my_wins[1],14,7,"        .;........O..O__");
	mvwprintw(my_wins[1],15,7,"       ._|............(#)");
	mvwprintw(my_wins[1],16,7,"      ._.''~-...........;");
	mvwprintw(my_wins[1],17,7,"    ,.,.,-~-;-.,...'--~'");
	mvwprintw(my_wins[1],18,7,"    ../../....}..'-.,/");
	mvwprintw(my_wins[1],19,7,"    ./.;___.../......");
	mvwprintw(my_wins[1],20,7,"   ./'-.|...'-........");
	mvwprintw(my_wins[1],21,7,"  .;.............)-....|");
	mvwprintw(my_wins[1],22,7,"  .|.....'---....-'..;");
	mvwprintw(my_wins[1],23,7,"  .',.,...............;");
	mvwprintw(my_wins[1],24,7,"   .',/....',........;");
	mvwprintw(my_wins[1],25,7,"    .............,.-'");
	mvwprintw(my_wins[1],26,7,"     .',.....',-~'.;");
	mvwprintw(my_wins[1],27,7,"      .|.....;.../__");
	mvwprintw(my_wins[1],28,7,"     ./....../__.....)");
	mvwprintw(my_wins[1],29,7,"    .'-.........)");


	/*Inca putin creativitate*/

	wattron(my_wins[1], COLOR_PAIR(2));
	mvwprintw(my_wins[1],10,75,"              ,.-''.''.''-,");
	mvwprintw(my_wins[1],11,75,"              /________;..|");
	mvwprintw(my_wins[1],12,75,"             {_________}.||");
	mvwprintw(my_wins[1],13,73,"             (./.O..O..| )(_)");
	mvwprintw(my_wins[1],14,75,"         .....(.,-, ),-,.)");
	mvwprintw(my_wins[1],15,73,"..___OOO__(....^....)_________");
	mvwprintw(my_wins[1],16,68,"./.............'-.___.-'..............|");
	mvwprintw(my_wins[1],17,71,".|......  BUN VENIT !!!! ...........|");
	mvwprintw(my_wins[1],18,70,".|........ VA DORESC ...............|");
	mvwprintw(my_wins[1],19,71,".|........... DISTRACTIE .........|");
	mvwprintw(my_wins[1],20,74,".|........ PLACUTA !!! .....|");
	mvwprintw(my_wins[1],21,75,"|___________________OOO___/");
	mvwprintw(my_wins[1],22,75,"                |_...|..._|");
	mvwprintw(my_wins[1],23,76,"                |___|___/");
	mvwprintw(my_wins[1],24,76,"                {___|___}");
	mvwprintw(my_wins[1],25,76,"                  |_.|._|");
	mvwprintw(my_wins[1],26,75,"                  /-'.Y.'-|");
	mvwprintw(my_wins[1],27,76,"                 (__/.|__)");
	wattroff(my_wins[1], COLOR_PAIR(2));
	post_menu(main_menu);
	wrefresh(my_wins[1]);
	refresh();


	top = my_panels[1];
	/*Afisarea data si ora*/
	mvprintw(LINES - 3, 0, "Cel mai mare scor %d", score_old);
	mvprintw(LINES - 5, 0, "Data si ora : %s      ", ctime(&t1));

	while((ch = getch()) != KEY_F(1))
	{
		switch(ch)
		{

			case KEY_DOWN:
			time(&t1);
	        t2=localtime(&t1);
				mvprintw(LINES - 5, 0, "Data si ora : %s     ", asctime(t2));
				menu_driver(main_menu, REQ_DOWN_ITEM);
				break;
			case KEY_UP:
			time(&t1);
	        t2=localtime(&t1);
				mvprintw(LINES - 5, 0, "Data si ora : %s     ", ctime(&t1));
				menu_driver(main_menu, REQ_UP_ITEM);
				break;
			case 10: /* Enter */
				{	time(&t1);
	                t2=localtime(&t1);
					mvprintw(LINES - 5, 0, "Data si ora : %s     ", ctime(&t1));
					ITEM *cur;
					void (*p)(char *);
					cur = current_item(main_menu);
					p = item_userptr(cur);
					p((char *)item_name(cur));
					pos_menu_cursor(main_menu);
					if (strcmp((char *)item_name(cur),choices[2]) == 0)
						goto out;
					if (strcmp((char *)item_name(cur),choices[0]) == 0){	
						EOF_FI = 0;
						rewind(fp);
						score = 0;
						resume_enable = 1;
						wa=0;
						ca=0;
						 lala = 0;
						 kaka = 0;
						new_game();
					}
					if (strcmp((char *)item_name(cur),choices[1]) == 0)
					{
						if(resume_enable)
							resume_game();
					}	
					break;
				}
				break;

			case 'q':
				goto out;
				time(&t1);
	                t2=localtime(&t1);
					mvprintw(LINES - 5, 0, "Data si ora : %s     ", ctime(&t1));
				top = (PANEL *)panel_userptr(top);
				top_panel(top);
				break;
		}

		int  height, width;
		char label[50]="";	/*Afisarea scorului ultimului joc*/
		sprintf(label, "Ultimul scor = %d",score);		
		getmaxyx(my_wins[1], height, width);
		print_in_middle(my_wins[1], height - 5, 0, width, label, COLOR_PAIR(2));

		if(score >= score_old && EOF_FI){
			score_old = score;
			sprintf(s_old,"%d",score_old);
			mvprintw(LINES - 3, 0, "Cel mai mare scor : %d      ", score_old);
			
		}
		update_panels();
		doupdate();
	}
out:	/*Eliberarea memoriei*/
	unpost_menu(main_menu); 
	for(i = 0; i < n_choices; ++i) 
	free_item(main_items[i]); 
	free_menu(main_menu);  
	refresh();
	endwin();
	if( score >= score_old && EOF_FI){
		score_old = score;
		sprintf(s_old,"%d",score_old);
		fclose(fs);
		fs = fopen("score","w");
		rewind(fs);
		fputs(s_old, fs);
	}
	return 0;
}
struct que_ans{
	char que[100];
	char ans[20];
	char options[4][20];
	int Q_num;
}Q;
int Q_num = 0;
static char que[100];
static char ans[20];
static char options[4][20];
static char fifty[2][20];
unsigned int fif_opt = 0;

void new_game(void){


	static ITEM ** act_items;
	static ITEM ** opt_items;
	static ITEM ** fif_items;
	int ch,save_num=10;
	time_t t1;
	struct tm *t2;
	unsigned int n_choices=0,n_choices1=0,n_choices2=0,i=0;
	char *last;
	char temp[2] = "";
	

	top = (PANEL *)panel_userptr(top);
	top_panel(top);
	
	Q_num = 0;
	
	update_panels();
	n_choices1 = ARRAY_SIZE(choices1);
	opt_items = (ITEM **)calloc(n_choices1 + 1, sizeof(ITEM *));
	n_choices = ARRAY_SIZE(options);
	act_items = (ITEM **)calloc(n_choices + 1, sizeof(ITEM *));
	n_choices2 = ARRAY_SIZE(fifty);
	fif_items = (ITEM **)calloc(n_choices2 + 1, sizeof(ITEM *));

	mvwprintw(my_wins[0], 21, 7, "                			                       	");

repeat:
		
		for (int i = 6; i < 21; ++i)
	
		mvwprintw(my_wins[0], i, 1, "                                                                                                           ");	
	
	 	/*Iarasi creativitate*/
		wattron(my_wins[0], COLOR_PAIR(1));
		mvwprintw(my_wins[0], 6, 17, "*");
		mvwprintw(my_wins[0], 7, 16,  "***");
		mvwprintw(my_wins[0], 8, 15, "*****");
		mvwprintw(my_wins[0], 9, 14, "*******");
		mvwprintw(my_wins[0], 10, 13, "*********");
		mvwprintw(my_wins[0], 11, 12, "***********");
		mvwprintw(my_wins[0], 12, 11,  "*************");
		mvwprintw(my_wins[0], 13, 10, "***************");
		mvwprintw(my_wins[0], 14, 9, "*****************");
		mvwprintw(my_wins[0], 15, 8, "*******************");
		mvwprintw(my_wins[0], 16, 16, "||");
		wattroff(my_wins[0], COLOR_PAIR(1));
		wattron(my_wins[0], COLOR_PAIR(3));
		mvwprintw(my_wins[0], 20, 3, "()''()()''()");
		mvwprintw(my_wins[0], 21, 3,  "(,'o')('o',)");
		wattroff(my_wins[0], COLOR_PAIR(3));
		wattron(my_wins[0], COLOR_PAIR(1));
		mvwprintw(my_wins[0], 25, 15,   "__");
		mvwprintw(my_wins[0], 26, 12, "*_|  |_**");
		mvwprintw(my_wins[0], 27, 12, "**('o')");
		mvwprintw(my_wins[0], 28, 12, "* *(**)**");
		mvwprintw(my_wins[0], 29, 13, "**(***)");
		wattroff(my_wins[0], COLOR_PAIR(1));	


	    wattron(my_wins[0], COLOR_PAIR(1));
		mvwprintw(my_wins[0], 6, 100, "*");
		mvwprintw(my_wins[0], 7, 99,  "***");
		mvwprintw(my_wins[0], 8, 98, "*****");
		mvwprintw(my_wins[0], 9, 97, "*******");
		mvwprintw(my_wins[0], 10, 96, "*********");
		mvwprintw(my_wins[0], 11, 95, "***********");
		mvwprintw(my_wins[0], 12, 94,  "*************");
		mvwprintw(my_wins[0], 13, 93, "***************");
		mvwprintw(my_wins[0], 14, 92, "*****************");
		mvwprintw(my_wins[0], 15, 91, "*******************");
		mvwprintw(my_wins[0], 16, 99, "||");
		wattroff(my_wins[0], COLOR_PAIR(1));
		wattron(my_wins[0], COLOR_PAIR(3));
		mvwprintw(my_wins[0], 20, 105, "()''()()''()");
		mvwprintw(my_wins[0], 21, 105,  "(,'o')('o',)");
		wattroff(my_wins[0], COLOR_PAIR(3));
		wattron(my_wins[0], COLOR_PAIR(2));
		mvwprintw(my_wins[0], 25, 55, "'')");
		mvwprintw(my_wins[0], 26, 55, "'(,)");
		mvwprintw(my_wins[0], 27, 54, "'[___]");
		mvwprintw(my_wins[0], 28, 54, "'[___]");
		mvwprintw(my_wins[0], 29, 54, "'[___]");
		mvwprintw(my_wins[0], 30, 54, "(_____)");
		wattroff(my_wins[0], COLOR_PAIR(2));
		wattron(my_wins[0], COLOR_PAIR(1));
		mvwprintw(my_wins[0], 25, 101,   "__");
		mvwprintw(my_wins[0], 26, 98, "*_|  |_**");
		mvwprintw(my_wins[0], 27, 98, "**('o')");
		mvwprintw(my_wins[0], 28, 98, "* *(**)**");
		mvwprintw(my_wins[0], 29, 99, "**(***)");
		wattroff(my_wins[0], COLOR_PAIR(1));	

		save_num = 10;

	if( fif_opt == 0 ){
		
			if(Q_num >= 10)
			goto exit;
		fgets(que,500,fp);
		last = strchr((char *)(que),'\n');
		*last = '\0';

		fgets(ans,500,fp);
		last = strchr((char *)(ans),'\n');
		*last = '\0';
		

		wattron(my_wins[0], COLOR_PAIR(2));
		mvwprintw(my_wins[0], 7, 45, "%s", (que));	/*Afisarea intrebarilor*/
		wattroff(my_wins[0], COLOR_PAIR(2));

		for(i = 0; i < n_choices; ++i){
			fgets((options)[i],500,fp);
			last = strchr(options[i],'\n');
			*last = '\0';
		}

		for(i = 0; i < n_choices; ++i)
		{
			act_items[i] = new_item(options[i], choices[i]);        /* Set the user pointer */
			set_item_userptr(act_items[i], func);
		}
		act_items[n_choices] = (ITEM *)NULL;     /* Crearea meniului de raspunsuri */
		act_menu = new_menu((ITEM **)act_items);  /* Postarea meniului */

		set_menu_win(act_menu, my_wins[0]);
		set_menu_sub(act_menu, derwin(my_wins[0], 6, 38, NLINES/3, 45));

		
		menu_opts_off(act_menu, O_SHOWDESC);

		set_menu_format(act_menu, 5, 1);

		/* Setarea semnului pentru raspunsuri " # " */
		set_menu_mark(act_menu, " # ");

		for(i = 0; i < n_choices1; ++i)
		{
			opt_items[i] = new_item(choices1[i], choices[i]);        /* Set the user pointer */
			set_item_userptr(opt_items[i], func);
		}
		opt_items[n_choices1] = (ITEM *)NULL;     /* Crearea meniului pentru optiunile extra */
		opt_menu = new_menu((ITEM **)opt_items);  /* Postarea  meniului */

		set_menu_win(opt_menu, my_wins[0]);
		set_menu_sub(opt_menu, derwin(my_wins[0], 6, 38, NLINES/2,80));
		
		menu_opts_off(opt_menu, O_SHOWDESC);

		set_menu_format(opt_menu, 5, 2);

		/* Setarea semnului pentru meniul extra-optiunilor" * " */
		set_menu_mark(opt_menu, " * ");

		post_menu(opt_menu);

		post_menu(act_menu);
}

	
	else    {
		fifty[0][0]='\0';
		fifty[1][0]='\0';
		/*afisarea intrebarilor*/
		wattron(my_wins[0], COLOR_PAIR(2));
		mvwprintw(my_wins[0], 7, 45, "%s", (que));
		wattroff(my_wins[0], COLOR_PAIR(2));

		for (i=0;i<n_choices;i++){
			if (strcmp(options[i],ans)==0){
				save_num = i;
				if(i/2 < 1){
					strcpy(fifty[1],ans);

					
				}
				else
				{
					strcpy(fifty[0],ans);
				}
				break;	
			}
		}
		for (i=0;i<n_choices;i++){

			if((i + 1)<4 && save_num != i + 1){
				if(!fifty[0][0])
					strcpy(fifty[0],options[i+1]);
				else
					strcpy(fifty[1],options[i+1]);
				break;
			}
			else if ((i - 1) <= 0 && save_num != i - 1){
				if(!fifty[0][0])
					strcpy(fifty[0],options[i-1]);
				else
					strcpy(fifty[1],options[i-1]);
				break;
			}
		}		

		for(i = 0; i < n_choices2; ++i)
		{
			fif_items[i] = new_item(fifty[i], choices[i]);        /* Set the user pointer */
			set_item_userptr(fif_items[i], func);
		}
		fif_items[n_choices] = (ITEM *)NULL;     /* Crearea meniului pentru raspunsurile ramase dupa optiunea 50/50*/
		fif_menu = new_menu((ITEM **)fif_items);  /* Postarea meniului */

		set_menu_win(fif_menu, my_wins[0]);
		set_menu_sub(fif_menu, derwin(my_wins[0], 7, 38, NLINES/3, 45));
		
		menu_opts_off(fif_menu, O_SHOWDESC);

		set_menu_format(fif_menu, 5, 1);

		/* Setarea semnului pentru acest meniu " # " */
		set_menu_mark(fif_menu, " # ");
		post_menu(fif_menu);	/* code */
		
}




	wrefresh(my_wins[0]);
	//	refresh();
	doupdate();
	top = my_panels[0];
kita :
	while((ch = getch()) != KEY_F(1))
	{
		switch(ch)
		{

			case KEY_DOWN:
			time(&t1);
	                t2=localtime(&t1);
					mvprintw(LINES - 5, 0, "Data si ora : %s     ", ctime(&t1));
				if(fif_opt)
					menu_driver(fif_menu, REQ_DOWN_ITEM);
				else
					menu_driver(act_menu, REQ_DOWN_ITEM);
				right = 0;
				left = 0;
				break;
			case KEY_UP:
			time(&t1);
	                t2=localtime(&t1);
					mvprintw(LINES - 5, 0, "Data si ora : %s     ", ctime(&t1));
				if(fif_opt)
					menu_driver(fif_menu, REQ_UP_ITEM);
				else
					menu_driver(act_menu, REQ_UP_ITEM);
				right = 0;
				left = 0;
				break;
			case KEY_RIGHT:
			time(&t1);
	                t2=localtime(&t1);
					mvprintw(LINES - 5, 0, "Data si ora : %s     ", ctime(&t1));
				if(!fif_opt){
					menu_driver(opt_menu, REQ_RIGHT_ITEM);
					right = 1;
				}
				break;
			case KEY_LEFT:
			time(&t1);
	                t2=localtime(&t1);
					mvprintw(LINES - 5, 0, "Data si ora : %s     ", ctime(&t1));
				if(!fif_opt){
					menu_driver(opt_menu, REQ_LEFT_ITEM);
					left = 1;
				}
				break;
			case 10: /* Enter */
				{
					time(&t1);
	                t2=localtime(&t1);
					mvprintw(LINES - 5, 0, "Data si ora : %s     ", ctime(&t1));
					ITEM *cur;
					void (*p)(char *);
					if (right || left){
						cur = current_item(opt_menu);
						
					}
					else if (fif_opt == 1)
						cur = current_item(fif_menu);
					else
						cur = current_item(act_menu);
					p = item_userptr(cur);
					p((char *)item_name(cur));
					if (kaka == 0){
					if(strcmp((char *)item_name(cur),choices1[0]) == 0){ /*optiuniea skip,daaca este folosita odata kaka ia valoarea 1 si aceasta functie nu va mai putea fi folosita*/
								kaka = 1 ;
								goto go;
							}	
						}

						else
						{

							if(strcmp((char *)item_name(cur),choices1[0]) == 0){ /*in cazul cand aceasta functia Skip este dezactivata */

								mvwprintw(my_wins[0],24,45,"Ati folosit deja aceasta optiune");
								goto kita;
							}
								else
								{
									if(strcmp((char *)item_name(cur),choices1[1]) == 1)  {
										if (strcmp((char *)item_name(cur),choices1[0]) == 1){
										pos_menu_cursor(act_menu);
										check_ans((char *)item_name(cur),ans);
										}
										}


								}
								mvwprintw(my_wins[0],24,45,"                                                         ");
						}
					if (lala == 0) 
					{

						if (right || left){
							right = 0; left = 0;
							pos_menu_cursor(opt_menu);
						

						if(strcmp((char *)item_name(cur),choices1[1]) == 0) /*Optiunea fifty,daca este folosita odata  lala ia valoarea 1 si functie nu va mai putea fi folosita */
						{		
								
								fif_opt = 1;
							goto repeat;

						}
					}
				
					else if(fif_opt == 1){
								lala = 1;
								fif_opt = 0 ;
								pos_menu_cursor(fif_menu);
								check_ans((char *)item_name(cur),ans);

					}
					
									
					
					else { 
												
							pos_menu_cursor(act_menu);
							check_ans((char *)item_name(cur),ans);

						}

					}

					else 
					{	
						
						
						if(strcmp((char *)item_name(cur),choices1[1]) == 0)      /*in cazul cand aceasta functia Skip este dezactivata */
						{
							mvwprintw(my_wins[0],24,45,"Ati folosit deja aceasta optiune");	
							goto kita;
						}	

										pos_menu_cursor(act_menu);
										check_ans((char *)item_name(cur),ans);
										
					}


			
				
					mvwprintw(my_wins[0],24,45,"                                            ");
go:
					fgets(temp,25,fp);
					Q_num += 1; 
					if (temp[0] == '#'){
						rewind(fp);
						EOF_FI = 1;
						Q_num = 0; 
						time(&t1);
	        t2=localtime(&t1);
				mvprintw(LINES - 5, 0, "Data si ora : %s     ", asctime(t2));
						for (i = 5; i < 28 ; i++ )       
				mvwprintw(my_wins[0], i, 1, "                                                                          ");
						/*Creativitateeee*/
						mvwprintw(my_wins[0], 20, 45, "                                                            ");
						mvwprintw(my_wins[0], 14, 45, "                                          ");
						mvwprintw(my_wins[0], 20, 20, "                           ");
						mvwprintw(my_wins[0], 21, 25, "                           ");
						wattron(my_wins[0], COLOR_PAIR(2));
						mvwprintw(my_wins[0], 6, 45, " .--|''''''''''''''''''''|");
						mvwprintw(my_wins[0], 7, 45, " / - | 'JOCUL SA SFARSIT' |");
						mvwprintw(my_wins[0], 8, 45, "''-O-'''''''''''''''O''O''''-");
						wattroff(my_wins[0], COLOR_PAIR(2));
						mvwprintw(my_wins[0], 11, 45, "************************");
						mvwprintw(my_wins[0], 12, 45, "*Scorul Final este : %d*",score);
						mvwprintw(my_wins[0], 13, 45, "************************");
						wattron(my_wins[0], COLOR_PAIR(1));
						mvwprintw(my_wins[0], 15, 45, "************************");
						mvwprintw(my_wins[0], 16, 45, "*Raspunsuri Corecte : %d*",ca);
						mvwprintw(my_wins[0], 17, 45, "************************");
						wattroff(my_wins[0], COLOR_PAIR(1));
						wattron(my_wins[0], COLOR_PAIR(3));
						mvwprintw(my_wins[0], 19, 45, "************************");
						mvwprintw(my_wins[0], 20, 45, "*Raspunsuri Gresite : %d*",wa);
						mvwprintw(my_wins[0], 21, 45, "************************");
						wattroff(my_wins[0], COLOR_PAIR(3));
						wattron(my_wins[0], COLOR_PAIR(2));
						mvwprintw(my_wins[0], 25, 55, "'')");
						mvwprintw(my_wins[0], 26, 55, "'(,)");
						mvwprintw(my_wins[0], 27, 54, "'[___]");	
						mvwprintw(my_wins[0], 28, 54, "'[___]");
						mvwprintw(my_wins[0], 29, 54, "'[___]");
						mvwprintw(my_wins[0], 30, 54, "(_____)");
						wattroff(my_wins[0], COLOR_PAIR(2));
						wattron(my_wins[0], COLOR_PAIR(1));
						mvwprintw(my_wins[0], 25, 101,   "__");
						mvwprintw(my_wins[0], 26, 98, "*_|  |_**");
						mvwprintw(my_wins[0], 27, 98, "**('o')");
						mvwprintw(my_wins[0], 28, 98, "* *(**)**");
						mvwprintw(my_wins[0], 29, 99, "**(***)");
						wattroff(my_wins[0], COLOR_PAIR(1));
						wattron(my_wins[0], COLOR_PAIR(1));
						mvwprintw(my_wins[0], 6, 17, "*");
						mvwprintw(my_wins[0], 7, 16,  "***");
						mvwprintw(my_wins[0], 8, 15, "*****");
						mvwprintw(my_wins[0], 9, 14, "*******");
						mvwprintw(my_wins[0], 10, 13, "*********");
						mvwprintw(my_wins[0], 11, 12, "***********");
						mvwprintw(my_wins[0], 12, 11,  "*************");
						mvwprintw(my_wins[0], 13, 10, "***************");
						mvwprintw(my_wins[0], 14, 9, "*****************");
						mvwprintw(my_wins[0], 15, 8, "*******************");
						mvwprintw(my_wins[0], 16, 16, "||");
						wattroff(my_wins[0], COLOR_PAIR(1));
						wattron(my_wins[0], COLOR_PAIR(3));
						mvwprintw(my_wins[0], 20, 3, "()''()()''()");
						mvwprintw(my_wins[0], 21, 3,  "(,'o')('o',)");
						wattroff(my_wins[0], COLOR_PAIR(3));
						wattron(my_wins[0], COLOR_PAIR(1));
						mvwprintw(my_wins[0], 25, 15,   "__");
						mvwprintw(my_wins[0], 26, 12, "*_|  |_**");
						mvwprintw(my_wins[0], 27, 12, "**('o')");
						mvwprintw(my_wins[0], 28, 12, "* *(**)**");
						mvwprintw(my_wins[0], 29, 13, "**(***)");
						wattroff(my_wins[0], COLOR_PAIR(1));	
						wgetch(my_wins[0]);
						mvwprintw(my_wins[0], 11, 45, "                                 ");
						mvwprintw(my_wins[0], 12, 45, "                                 ");
						mvwprintw(my_wins[0], 13, 45, "                                 ");
						mvwprintw(my_wins[0], 15, 45, "                                 ");
						mvwprintw(my_wins[0], 16, 45, "                                 ");
						mvwprintw(my_wins[0], 17, 45, "                                 ");
						mvwprintw(my_wins[0], 19, 45, "                                 ");
						mvwprintw(my_wins[0], 20, 45, "                                 ");
						mvwprintw(my_wins[0], 21, 45, "                                 ");
						goto exit;


					}
					goto repeat;

				}
				break;

			case 'q':
			time(&t1);
	                t2=localtime(&t1);
					mvprintw(LINES - 5, 0, "Data si ora : %s     ", ctime(&t1));
				top = (PANEL *)panel_userptr(top);
				top_panel(top);
				return;                                                    
		}
		update_panels();
		doupdate();
	}

exit:
	update_panels();
	doupdate();
	top = (PANEL *)panel_userptr(top);
	top_panel(top);
	return;


}

void resume_game(void){ 			/*Aceleasi optiuni precum si la functia New Game*/
	
	ITEM ** res_items;
	ITEM ** opt_res_items;
	static ITEM ** fif_res_items;
	int ch,save_num=10;;
	int first_skip=1;
	time_t t1;
	struct tm *t2;
	unsigned int n_choices=0,n_choices1=0,n_choices2=0,i=0;	
	char *last;
	char temp[2] = "";
	top = (PANEL *)panel_userptr(top);
	top_panel(top);

	update_panels();
	n_choices = ARRAY_SIZE(options);
	res_items = (ITEM **)calloc(n_choices + 1, sizeof(ITEM *));

	n_choices1 = ARRAY_SIZE(choices1);
	opt_res_items = (ITEM **)calloc(n_choices1 + 1, sizeof(ITEM *));
	n_choices2 = ARRAY_SIZE(fifty);
	fif_res_items = (ITEM **)calloc(n_choices2 + 1, sizeof(ITEM *));

repeat1:
for (int i = 6; i < 21; ++i)
	
	mvwprintw(my_wins[0], i, 1, "                                                                                                      ");	
	
	    wattron(my_wins[0], COLOR_PAIR(1));
		mvwprintw(my_wins[0], 6, 100, "*");
		mvwprintw(my_wins[0], 7, 99,  "***");
		mvwprintw(my_wins[0], 8, 98, "*****");
		mvwprintw(my_wins[0], 9, 97, "*******");
		mvwprintw(my_wins[0], 10, 96, "*********");
		mvwprintw(my_wins[0], 11, 95, "***********");
		mvwprintw(my_wins[0], 12, 94,  "*************");
		mvwprintw(my_wins[0], 13, 93, "***************");
		mvwprintw(my_wins[0], 14, 92, "*****************");
		mvwprintw(my_wins[0], 15, 91, "*******************");
		mvwprintw(my_wins[0], 16, 99, "||");
		wattroff(my_wins[0], COLOR_PAIR(1));
		wattron(my_wins[0], COLOR_PAIR(3));
		mvwprintw(my_wins[0], 20, 105, "()''()()''()");
		mvwprintw(my_wins[0], 21, 105,  "(,'o')('o',)");
		wattroff(my_wins[0], COLOR_PAIR(3));
		wattron(my_wins[0], COLOR_PAIR(2));
		mvwprintw(my_wins[0], 25, 55, "'')");
		mvwprintw(my_wins[0], 26, 55, "'(,)");
		mvwprintw(my_wins[0], 27, 54, "'[___]");
		mvwprintw(my_wins[0], 28, 54, "'[___]");
		mvwprintw(my_wins[0], 29, 54, "'[___]");
		mvwprintw(my_wins[0], 30, 54, "(_____)");
		wattroff(my_wins[0], COLOR_PAIR(2));
		wattron(my_wins[0], COLOR_PAIR(1));
		mvwprintw(my_wins[0], 25, 101,   "__");
		mvwprintw(my_wins[0], 26, 98, "*_|  |_**");
		mvwprintw(my_wins[0], 27, 98, "**('o')");
		mvwprintw(my_wins[0], 28, 98, "* *(**)**");
		mvwprintw(my_wins[0], 29, 99, "**(***)");
		wattroff(my_wins[0], COLOR_PAIR(1));
		wattron(my_wins[0], COLOR_PAIR(1));
		mvwprintw(my_wins[0], 6, 17, "*");
		mvwprintw(my_wins[0], 7, 16,  "***");
		mvwprintw(my_wins[0], 8, 15, "*****");
		mvwprintw(my_wins[0], 9, 14, "*******");
		mvwprintw(my_wins[0], 10, 13, "*********");
		mvwprintw(my_wins[0], 11, 12, "***********");
		mvwprintw(my_wins[0], 12, 11,  "*************");
		mvwprintw(my_wins[0], 13, 10, "***************");
		mvwprintw(my_wins[0], 14, 9, "*****************");
		mvwprintw(my_wins[0], 15, 8, "*******************");
		mvwprintw(my_wins[0], 16, 16, "||");
		wattroff(my_wins[0], COLOR_PAIR(1));
		wattron(my_wins[0], COLOR_PAIR(3));
		mvwprintw(my_wins[0], 20, 3, "()''()()''()");
		mvwprintw(my_wins[0], 21, 3,  "(,'o')('o',)");
		wattroff(my_wins[0], COLOR_PAIR(3));
		wattron(my_wins[0], COLOR_PAIR(1));
		mvwprintw(my_wins[0], 25, 15,   "__");
		mvwprintw(my_wins[0], 26, 12, "*_|  |_**");
		mvwprintw(my_wins[0], 27, 12, "**('o')");
		mvwprintw(my_wins[0], 28, 12, "* *(**)**");
		mvwprintw(my_wins[0], 29, 13, "**(***)");
		wattroff(my_wins[0], COLOR_PAIR(1));	
	
	if( fif_opt == 0 ) {
		
		if(EOF_FI)
			goto exit1;
		if(first_skip == 0) {
			if(Q_num >= 10)
				goto exit1;
			fgets(que,100,fp);
			last = strchr((char *)(que),'\n');
			*last = '\0';

			fgets(ans,100,fp);
			last = strchr((char *)(ans),'\n');
			*last = '\0';
			for(i = 0; i < n_choices; ++i){
				fgets((options)[i],100,fp);
				last = strchr(options[i],'\n');
				*last = '\0';
			}
       }
    
		
		wattron(my_wins[0], COLOR_PAIR(2));
		mvwprintw(my_wins[0], 7, 45, "%s", (que));
		wattroff(my_wins[0], COLOR_PAIR(2));

		
		for(i = 0; i < n_choices; ++i)
		{
			res_items[i] = new_item(options[i], choices[i]);        /* Set the user pointer */
			set_item_userptr(res_items[i], func);
		}
		res_items[n_choices] = (ITEM *)NULL;     /* Crearea meniului pentru raspunsuri */
		res_menu = new_menu((ITEM **)res_items);  /* Postarea  meniului */

		set_menu_win(res_menu, my_wins[0]);
		set_menu_sub(res_menu, derwin(my_wins[0], 6, 38, NLINES/3, 45));
		menu_opts_off(res_menu, O_SHOWDESC);

		set_menu_format(res_menu, 5, 1);

		/* Setarea semnului pentru raspunsuri " #" */
		set_menu_mark(res_menu, " # ");

		for(i = 0; i < n_choices1; ++i)
		{
			opt_res_items[i] = new_item(choices1[i], choices[i]);        /* Set the user pointer */
			set_item_userptr(opt_res_items[i], func);
		}
		opt_res_items[n_choices1] = (ITEM *)NULL;     /* Crearea meniului pentru optiunile extra */
		opt_res_menu = new_menu((ITEM **)opt_res_items);  /* Postarea meniului */

		set_menu_win(opt_res_menu, my_wins[0]);
		set_menu_sub(opt_res_menu, derwin(my_wins[0], 6, 38, NLINES/2, 80));
		
		menu_opts_off(opt_res_menu, O_SHOWDESC);

		set_menu_format(opt_res_menu, 5, 2);

		/* Setarea semnului pentru optiunile extra*/ 
		set_menu_mark(opt_res_menu, " * ");

		post_menu(opt_res_menu);
		
		post_menu(res_menu);

		 first_skip = 0;
	}

		
	else   {
	
		fifty[0][0]='\0';
		fifty[1][0]='\0';
		
		wattron(my_wins[0], COLOR_PAIR(2));
		mvwprintw(my_wins[0], 7, 45, "%s", (que));
		wattroff(my_wins[0], COLOR_PAIR(2));

		 for (i=0;i<n_choices;i++){
			if (strcmp(options[i],ans)==0){
				save_num = i;
				if(i/2 < 1)
					strcpy(fifty[1],ans);
				else
					strcpy(fifty[0],ans);
				break;	
			}
		}
		for (i=0;i<n_choices;i++){

			if((i + 1)<4 && save_num != i + 1){
				if(!fifty[0][0])
					strcpy(fifty[0],options[i+1]);
				else
					strcpy(fifty[1],options[i+1]);
				break;
			}
			else if ((i - 1) <= 0 && save_num != i - 1){
				if(!fifty[0][0])
					strcpy(fifty[0],options[i-1]);
				else
					strcpy(fifty[1],options[i-1]);
				break;
			}
		}		

		for(i = 0; i < n_choices2; ++i)
		{
			fif_res_items[i] = new_item(fifty[i], choices[i]);        /* Set the user pointer */
			set_item_userptr(fif_res_items[i], func);
		}
		fif_res_items[n_choices] = (ITEM *)NULL;     /* Crearea meniului pentru raspunsurile ramase dupa alegerea optiunii 50/50 */
		fif_res_menu = new_menu((ITEM **)fif_res_items);  /* Postarea meniului */

		set_menu_win(fif_res_menu, my_wins[0]);
		set_menu_sub(fif_res_menu, derwin(my_wins[0], 6, 38, NLINES/3, 45));
		/* Set menu option not to show the description */
		menu_opts_off(fif_res_menu, O_SHOWDESC);

		set_menu_format(fif_res_menu, 5, 1);

		/* Setarea semnului pentru meniu dupa alegerea extra-optiunii 50/50" # " */
		set_menu_mark(fif_res_menu, " # ");
		
		post_menu(fif_res_menu);


	
	}



	wrefresh(my_wins[0]);
	//	refresh();
	doupdate();
	top = my_panels[0];
	
kita:
	while((ch = getch()) != KEY_F(1))
	{
		switch(ch)
		{

			case KEY_DOWN:
			time(&t1);
	                t2=localtime(&t1);
					mvprintw(LINES - 5, 0, "Data si ora : %s     ", ctime(&t1));
				if(fif_opt)
					menu_driver(fif_res_menu, REQ_DOWN_ITEM);
				else
					menu_driver(res_menu, REQ_DOWN_ITEM);
				right_res = 0;
				left_res = 0;
				break;
			case KEY_UP:
			time(&t1);
	                t2=localtime(&t1);
					mvprintw(LINES - 5, 0, "Data si ora : %s     ", ctime(&t1));
				if(fif_opt)
					menu_driver(fif_res_menu, REQ_UP_ITEM);
				else
					menu_driver(res_menu, REQ_UP_ITEM);
				right_res = 0;
				left_res = 0;
				break;
			case KEY_RIGHT:
			time(&t1);
	                t2=localtime(&t1);
					mvprintw(LINES - 5, 0, "Data si ora : %s     ", ctime(&t1));
				if(!fif_opt){
					menu_driver(opt_res_menu, REQ_RIGHT_ITEM);
					right_res = 1;
				}
				break;
			case KEY_LEFT:
			time(&t1);
	                t2=localtime(&t1);
					mvprintw(LINES - 5, 0, "Data si ora : %s     ", ctime(&t1));
				if(!fif_opt){
					menu_driver(opt_res_menu, REQ_LEFT_ITEM);
					left_res = 1;
				}
				break;
			case 10: /* Enter */
				{
					time(&t1);
	                t2=localtime(&t1);
					mvprintw(LINES - 5, 0, "Data si ora : %s     ", ctime(&t1));
					ITEM *cur;
					void (*p)(char *);
					if (right_res || left_res){
						cur = current_item(opt_res_menu);
					}
					else if (fif_opt == 1)
						cur = current_item(fif_res_menu);
			
					else
						
						cur = current_item(res_menu);
					p = item_userptr(cur);
					p((char *)item_name(cur));

					if (kaka == 0){
					if(strcmp((char *)item_name(cur),choices1[0]) == 0){ /*optiuniea skip,daaca este folosita odata kaka ia valoarea 1 si aceasta functie nu va mai putea fi folosita*/
								kaka = 1 ;
								goto go;
							}	
						}

						else
						{

							if(strcmp((char *)item_name(cur),choices1[0]) == 0){ /*in cazul cand aceasta functia Skip este dezactivata */

								mvwprintw(my_wins[0],24,45,"Ati folosit deja aceasta optiune");
								goto kita;
							}
								else
								{
									if(strcmp((char *)item_name(cur),choices1[1]) == 1)  {
										if (strcmp((char *)item_name(cur),choices1[0]) == 1){
										pos_menu_cursor(res_menu);
										check_ans((char *)item_name(cur),ans);
										}
										}


								}
								mvwprintw(my_wins[0],24,45,"                                                         ");
						}
					if (lala == 0) 
					{

						if (right || left){
							right = 0; left = 0;
							pos_menu_cursor(opt_res_menu);
						

						if(strcmp((char *)item_name(cur),choices1[1]) == 0) /*Optiunea fifty,daca este folosita odata  lala ia valoarea 1 si functie nu va mai putea fi folosita */
						{		
								
								fif_opt = 1;
							goto repeat1;

						}
					
				}
					else if(fif_opt == 1){
								lala = 1;
								fif_opt = 0 ;
								pos_menu_cursor(fif_res_menu);
								check_ans((char *)item_name(cur),ans);

					}
					
									
					
					else { 
												
							pos_menu_cursor(res_menu);
							check_ans((char *)item_name(cur),ans);

						}

					}


					else 
					{	
						
						
						if(strcmp((char *)item_name(cur),choices1[1]) == 0)      /*in cazul cand aceasta functia Skip este dezactivata */
						{
							mvwprintw(my_wins[0],24,45,"Ati folosit deja aceasta optiune");	
							goto kita;
						}	

										pos_menu_cursor(res_menu);
										check_ans((char *)item_name(cur),ans);
										
					}


			
				
					mvwprintw(my_wins[0],24,45,"                                            ");
go:
					fgets(temp,5,fp);
					Q_num += 1; 
					if (temp[0] == '#'){
						EOF_FI = 1;
						rewind(fp);
						Q_num = 0;
						time(&t1);
	        t2=localtime(&t1);
				mvprintw(LINES - 5, 0, "Data si ora : %s     ", asctime(t2));
						for (i = 5; i < 28 ; i++ )
						mvwprintw(my_wins[0], i, 45, "                                      ");
						mvwprintw(my_wins[0], 20, 45, "                                                     ");
						mvwprintw(my_wins[0], 20, 20, "                           ");
						mvwprintw(my_wins[0], 21, 25, "                           ");
						mvwprintw(my_wins[0], 14, 45, "                           ");

						wattron(my_wins[0], COLOR_PAIR(2));
						mvwprintw(my_wins[0], 6, 45, " .--|''''''''''''''''''''|");
						mvwprintw(my_wins[0], 7, 45, " / - | 'JOCUL SA SFARSIT' |");
						mvwprintw(my_wins[0], 8, 45, "''-O-'''''''''''''''O''O''''-");
						wattroff(my_wins[0], COLOR_PAIR(2));

						mvwprintw(my_wins[0], 11, 45, "************************");
						mvwprintw(my_wins[0], 12, 45, "*Scorul Final este : %d*",score);
						mvwprintw(my_wins[0], 13, 45, "************************");
						wattron(my_wins[0], COLOR_PAIR(1));
						mvwprintw(my_wins[0], 15, 45, "************************");
						mvwprintw(my_wins[0], 16, 45, "*Raspunsuri Corecte : %d*",ca);
						mvwprintw(my_wins[0], 17, 45, "************************");
						wattroff(my_wins[0], COLOR_PAIR(1));
						wattron(my_wins[0], COLOR_PAIR(3));
						mvwprintw(my_wins[0], 19, 45, "************************");
						mvwprintw(my_wins[0], 20, 45, "*Raspunsuri Gresite : %d*",wa);
						mvwprintw(my_wins[0], 21, 45, "************************");
						wattroff(my_wins[0], COLOR_PAIR(3));
						wattron(my_wins[0], COLOR_PAIR(2));
						mvwprintw(my_wins[0], 25, 55, "'')");
						mvwprintw(my_wins[0], 26, 55, "'(,)");
						mvwprintw(my_wins[0], 27, 54, "'[___]");
						mvwprintw(my_wins[0], 28, 54, "'[___]");
						mvwprintw(my_wins[0], 29, 54, "'[___]");
						mvwprintw(my_wins[0], 30, 54, "(_____)");
						wattroff(my_wins[0], COLOR_PAIR(2));
						wattron(my_wins[0], COLOR_PAIR(1));
						mvwprintw(my_wins[0], 25, 101,   "__");
						mvwprintw(my_wins[0], 26, 98, "*_|  |_**");
						mvwprintw(my_wins[0], 27, 98, "**('o')");
						mvwprintw(my_wins[0], 28, 98, "* *(**)**");
						mvwprintw(my_wins[0], 29, 99, "**(***)");
						wattroff(my_wins[0], COLOR_PAIR(1));




						wgetch(my_wins[0]);
						mvwprintw(my_wins[0], 11, 45, "                                 ");
						mvwprintw(my_wins[0], 12, 45, "                                 ");
						mvwprintw(my_wins[0], 13, 45, "                                 ");
						mvwprintw(my_wins[0], 15, 45, "                                 ");
						mvwprintw(my_wins[0], 16, 45, "                                 ");
						mvwprintw(my_wins[0], 17, 45, "                                 ");
						mvwprintw(my_wins[0], 19, 45, "                                 ");
						mvwprintw(my_wins[0], 20, 45, "                                 ");
						mvwprintw(my_wins[0], 21, 45, "                                 ");
						goto exit1;
					}
					goto repeat1;
				}
				break;

			case 'q':
			time(&t1);
	                t2=localtime(&t1);
					mvprintw(LINES - 5, 0, "Data si ora : %s     ", ctime(&t1));
				resume_abnormal = 1;
				goto exit1;
		}
		update_panels();
		doupdate();
	}

exit1:
	update_panels();
	doupdate();
	top = (PANEL *)panel_userptr(top);
	top_panel(top);
	return;

}



void check_ans(char * name, char * ans){ /*Functie pentru verificarea raspunsului*/

	if(strcmp(name,ans) == 0){
		score += 10;
		ca +=1;
#if 1	
		wattron(my_wins[0], COLOR_PAIR(2));
		mvwprintw(my_wins[0], 20, 20, "Raspuns Corect +10");
		wattroff(my_wins[0], COLOR_PAIR(2));
#endif
	}
	else{	
		wattron(my_wins[0], COLOR_PAIR(3));
		mvwprintw(my_wins[0], 20, 20, "Raspuns gresit -05");
		wattroff(my_wins[0], COLOR_PAIR(3));	
		score -= 5;
		wa +=1;
	}
	wattron(my_wins[0], COLOR_PAIR(4));
	mvwprintw(my_wins[0], 21, 25, "SCORUL : %d ", score);
	wattroff(my_wins[0], COLOR_PAIR(4));	
	update_panels();
	doupdate();
	sleep(1);
}

void func(char * name){
	;
	}


/* Afisarea tuturor ferestrelor */
void init_wins(WINDOW **wins, int n)
{
	int x, y, i;
	char label[5][80];
	y = 2;
	x = 10;
	sprintf(label[0], "**** TRIVIA ****");
	sprintf(label[1], "**** GAME START ****");
	sprintf(label[2], "Pentru a folosi optiunile extra folositi sagetile dreapta si stanga");
	sprintf(label[3], " **** Ultimul scor = %d  ****",score);
	for(i = 0; i < n; ++i)
	{
		wins[i] = newwin(NLINES, NCOLS, y, x);
		win_show(wins[i], label[i], label[i+2], i + 1);
	}
}
/* Afisarea ferestrei cu limite si spatii */
void win_show(WINDOW *win, char *label, char *label1, int label_color)
{
	int  height, width;
	
	getmaxyx(win, height, width);
	box(win, 0, 0);

	mvwaddch(win, 2, 0, ACS_LTEE);
	mvwhline(win, 2, 1, ACS_HLINE,width - 2);
	mvwaddch(win, 2, width - 1, ACS_RTEE);
	print_in_middle(win, 1, 0, width, label, COLOR_PAIR(label_color));

	mvwaddch(win, height - 4, 0, ACS_LTEE);
	mvwaddch(win, height - 6, 0, ACS_LTEE);
	mvwhline(win, height - 4, 1, ACS_HLINE,width - 2);
	mvwhline(win, height - 6, 1, ACS_HLINE,width - 2);
	mvwaddch(win, height - 4, width - 1, ACS_RTEE);
	mvwaddch(win, height - 6, width - 1, ACS_RTEE);
	print_in_middle(win, height - 5, 0, width, label1, COLOR_PAIR(label_color));


}

/*Functie de printare in centrul ferestrei*/
void print_in_middle(WINDOW *win, int starty, int startx, int width, char *string, chtype color)
{
	int length, x, y;
	float temp;
	if(win == NULL)
		win = stdscr;
	getyx(win, y, x);
	if(startx != 0)
		x = startx;
	if(starty != 0)
		y = starty;
	if(width == 0)
		width = 120;
	length = strlen(string);
	temp = (width - length)/ 2;
	x = startx + (int)temp;
	wattron(win, color);
	mvwprintw(win, y, x, "%s", string);
	wattroff(win, color);
	refresh();
}
