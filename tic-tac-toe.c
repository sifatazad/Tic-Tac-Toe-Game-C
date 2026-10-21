#include<stdio.h>
#include<conio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<windows.h>

static void board_print(char **b,int n) {
    char str[4*n-2];
    for (int i=0; i<=4*n-4; i++) {
        str[i]='-';
    }
    str[4*n-3]='\0';

    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            if (j!=n-1) {
                printf("%c | ",b[i][j]);
            }
            else {
                printf(" %c\n",b[i][j]);
            }
        }
        if (i!=n-1) {
            printf("%s-\n",str);
        }
        else
            printf("\n");
    }
}

static bool toss(char *s,char **board,int n) {
    // int cross=0;
    int choice;
    printf("Choose one symbol to play!\n1. Circle\t\t2.Cross\nYour choice: ");
    scanf("%d",&choice);
    if (choice!=1 && choice!=2) {
        while (1) {
            printf("\n\nWrong input! Press only 1 or 2.\n");
            printf("Your choice: ");
            scanf("%d",&choice);
            if (choice!=1 && choice!=2) {
                continue;
            }
            else {
                break;
            }
        }
    }
    Sleep(1000);
    // system("cls");
    if (rand()%2==choice%2) {
        char ch[10];
        if (choice%2)
            strcpy(ch,"Circle");
        else
            strcpy(ch,"Cross");

        printf("You won the toss! Play with %s.\n\n",ch);
        if (strcmp(ch,"Circle")) {
            *s='O';
        }
        else {
            *s='X';
        }
        return false;
    }
    else {
        char ch[10];
        if (choice%2)
            strcpy(ch,"Cross");
        else
            strcpy(ch,"Circle");
        printf("Computer won the toss! Play with %s.\n\n",ch);
        if (strcmp(ch,"Circle")) {
            *s='O';
        }
        else {
            *s='X';
        }
        return true;
    }
}

static bool horizontal_lose(char **board,char u_ch,int n) {
    for (int i=0; i<n; i++) {
        int cnt=0;
        for (int j=0; j<n; j++) {
            if (board[i][j]==u_ch)
                cnt++;
            else if (board[i][j]!='.')
                cnt--;
        }
        if (cnt==n-1)
            return true;
    }
    return false;
}

static bool horizontal_win(char **board,char c_ch,int n) {
    for (int i=0; i<n; i++) {
        int cnt=0;
        for (int j=0; j<n; j++) {
            if (board[i][j]==c_ch)
                cnt++;
            else if (board[i][j]!='.')
                cnt--;
        }
        if (cnt==n-1)
            return true;
    }
    return false;
}

static bool vertical_lose(char **board,char u_ch,int n) {
    for (int i=0; i<n; i++) {
        int cnt=0;
        for (int j=0; j<n; j++) {
            if (board[j][i]==u_ch)
                cnt++;
            else if (board[j][i]!='.')
                cnt--;
        }
        if (cnt==n-1)
            return true;
    }
    return false;
}

static bool vertical_win(char **board,char c_ch,int n) {
    for (int i=0; i<n; i++) {
        int cnt=0;
        for (int j=0; j<n; j++) {
            if (board[j][i]==c_ch)
                cnt++;
            else if (board[j][i]!='.')
                cnt--;
        }
        if (cnt==n-1)
            return true;
    }
    return false;
}

static bool diagonal_lose(char **board,char u_ch,int n) {
    int cnt=0;
    for (int i=0; i<n; i++) {
        if (board[i][i]==u_ch)
            cnt++;
        else if (board[i][i]!='.')
            cnt--;
    }
    if (cnt==n-1) {
        return true;
    }
    cnt=0;
    for (int i=0; i<n; i++) {
        if (board[i][n-1-i]==u_ch)
            cnt++;
        else if (board[i][n-1-i]!='.')
            cnt--;
    }
    if (cnt==n-1) {
        return true;
    }
    return false;
}

static bool diagonal_win(char **board,char c_ch,int n) {
    int cnt=0;
    for (int i=0; i<n; i++) {
        if (board[i][i]==c_ch)
            cnt++;
        else if (board[i][i]!='.')
            cnt--;
    }
    if (cnt==n-1) {
        return true;
    }
    cnt=0;
    for (int i=0; i<n; i++) {
        if (board[i][n-1-i]==c_ch)
            cnt++;
        else if (board[i][n-1-i]!='.')
            cnt--;
    }
    if (cnt==n-1) {
        return true;
    }
    return false;
}

static int is_losing(char **board,char u_ch,int n) {
    if (horizontal_lose(board,u_ch,n))
        return 1;
    if (vertical_lose(board,u_ch,n))
        return 2;
    if (diagonal_lose(board,u_ch,n))
        return 3;
    return 0;
}

static int is_winning(char **board,char c_ch,int n) {
    if (horizontal_win(board,c_ch,n)) {
        return 1;
    }
    if (vertical_win(board,c_ch,n)) {
        return 2;
    }
    if (diagonal_win(board,c_ch,n)) {
        return 3;
    }
    return 0;
}

static bool computer_won(char **board,char c_ch,int n) {
    // horizontal won
    for (int i=0; i<n; i++) {
        int cnt=0;
        for (int j=0; j<n; j++) {
            if (board[i][j]==c_ch) {
                cnt++;
            }
        }
        if (cnt==n) {
            return true;
        }
    }

    // vertical won
    for (int i=0; i<n; i++) {
        int cnt=0;
        for (int j=0; j<n; j++) {
            if (board[j][i]==c_ch) {
                cnt++;
            }
        }
        if (cnt==n) {
            return true;
        }
    }

    // diagonal won
    int cnt=0;
    for (int i=0; i<n; i++) {
        if (board[i][i]==c_ch)
            cnt++;
    }
    if (cnt==n) {
        return true;
    }
    cnt=0;
    for (int i=0; i<n; i++) {
        if (board[i][n-1-i]==c_ch)
            cnt++;
    }
    if (cnt==n) {
        return true;
    }
    return false;
}

static bool user_won(char **board,char u_ch,int n) {
    // horizontal won
    for (int i=0; i<n; i++) {
        int cnt=0;
        for (int j=0; j<n; j++) {
            if (board[i][j]==u_ch) {
                cnt++;
            }
        }
        if (cnt==n) {
            return true;
        }
    }

    // vertical won
    for (int i=0; i<n; i++) {
        int cnt=0;
        for (int j=0; j<n; j++) {
            if (board[j][i]==u_ch) {
                cnt++;
            }
        }
        if (cnt==n) {
            return true;
        }
    }

    // diagonal won
    int cnt=0;
    for (int i=0; i<n; i++) {
        if (board[i][i]==u_ch)
            cnt++;
    }
    if (cnt==n) {
        return true;
    }
    cnt=0;
    for (int i=0; i<n; i++) {
        if (board[i][n-1-i]==u_ch)
            cnt++;
    }
    if (cnt==n) {
        return true;
    }
    return false;
}

static bool check_range(int r,int c,int n) {
    if (r<1 || r>n || c<1 || c>n)
        return false;

    return true;
}

static bool check_blank(int r,int c,char **b,int n) {
    if (b[r-1][c-1]!='.')
        return false;

    return true;
}

static void get_move(char **board,int n,const char *prompt,int *pr,int *pc) {
    int r,c;
    printf("%s", prompt);
    while (1) {
        scanf("%d,%d",&r,&c);
        if (!check_range(r,c,n)) {
            printf("\n\nInvalid input! Please give a position on the board.\n");
            printf("Your input: ");
            continue;
        }
        if (!check_blank(r,c,board,n)) {
            printf("\n\nInvalid input! Please give a blank position on the board.\n");
            printf("Your input: ");
            continue;
        }
        break;
    }
    *pr=r;
    *pc=c;
}

static void tic_tac_toe(const int n) {
    char **board= malloc(sizeof(char*)*n);
    if (!board) {
        return;
    }
    for (int i=0; i<n; i++) {
        board[i]=malloc(n);
        if (!board[i]) {
            free(board);
            return;
        }
    }

    char *c_sym=malloc(10);
    if (!c_sym) {
        free(board);
        return;
    }
    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            board[i][j]='.';
        }
    }

    bool first_done=false;
    bool toss_won=toss(c_sym,board,n);
    char u_sym=(*c_sym=='X')?'O':'X';
    if (toss_won) {
        Sleep(2000);
        system("cls");
        printf("Game starts......3\n");
        Sleep(1000);
        system("cls");
        printf("Game starts......2\n");
        Sleep(1000);
        system("cls");
        printf("Game starts......1\n");
        Sleep(1000);
        system("cls");
        printf("Let's go!!!\n");
        Sleep(1000);
        system("cls");

        printf("Computer's first move: %d,%d\n",n/2+1,n/2+1);

        if (!first_done && n%2) {
            board[n/2][n/2]=*c_sym;
        }
        else if (!first_done && n%2==0) {
            board[0][0]=*c_sym;
        }

        board_print(board,n);
        printf("\n");
        first_done=true;
    }
    else {
        Sleep(2000);
        system("cls");
        printf("Game starts......3\n");
        Sleep(1000);
        system("cls");
        printf("Game starts......2\n");
        Sleep(1000);
        system("cls");
        printf("Game starts......1\n");
        Sleep(1000);
        system("cls");
        printf("Let's go!!!\n");
        Sleep(1000);
        system("cls");

        board_print(board,n);
        int r,c;
        // scanf("%d,%d",&r,&c);
        get_move(board,n,"Your Turn!\nWrite the row,col format to"
                         " give the first move: ",&r,&c);

        Sleep(1000);
        system("cls");
        board[r-1][c-1]=u_sym;
        board_print(board,n);
        Sleep(1000);
        system("cls");

        if (n%2) {
            if (r!=n/2+1 || c!=n/2+1) {
                board[n/2][n/2]=*c_sym;
                printf("Computer's turn! First move of Computer: %d,%d\n",n/2+1,n/2+1);
            }
            else if (r==n/2+1 && c==n/2+1) {
                bool flag=false;
                for (int i=0; i<n; i++) {
                    for (int j=0; j<n; j++) {
                        if (board[i][j]=='.') {
                            board[i][j]=*c_sym;
                            flag=true;
                            printf("Computer's turn! First move of Computer: %d,%d\n",i+1,j+1);
                            break;
                        }
                    }
                    if (flag)
                        break;
                }
            }
        }
        else {
            bool flag=false;
            for (int i=0; i<n; i++) {
                for (int j=0; j<n; j++) {
                    if (board[i][j]=='.') {
                        board[i][j]=*c_sym;
                        flag=true;
                        printf("Computer's turn! First move of Computer: %d,%d\n",i+1,j+1);
                        break;
                    }
                }
                if (flag)
                    break;
            }
        }
        board_print(board,n);
        printf("\n");
        first_done=true;
    }

    while (1) {
        bool complete=true;
        for (int i=0; i<n; i++) {
            for (int j=0; j<n; j++) {
                if (board[i][j]=='.') {
                    complete=false;
                    break;
                }
            }
        }

        if (complete) {
            system("cls");
            board_print(board,n);
            printf("Game Draw! Play again!!");
            break;
        }

        int r,c;
        // scanf("%d,%d",&r,&c);
        get_move(board,n,"Your turn: ",&r,&c);

        printf("\n");
        board[r-1][c-1]=u_sym;
        board_print(board,n);
        Sleep(1000);
        system("cls");

        if (user_won(board,u_sym,n)) {
            printf("Congratulations! You won!!\n");
            board_print(board,n);
            break;
        }

        if (is_winning(board,*c_sym,n)) {
            int win_val= is_winning(board,*c_sym,n);
            if (win_val==1) {
                int row=-1;
                for (int i=0; i<n; i++) {
                    int cnt=0;
                    for (int j=0; j<n; j++) {
                        if (board[i][j]==*c_sym)
                            cnt++;
                        else if (board[i][j]==u_sym)
                            cnt--;
                    }
                    if (cnt==n-1) {
                        row=i;
                        break;
                    }
                }
                for (int j=0; j<n; j++) {
                    if (board[row][j]=='.') {
                        board[row][j]=*c_sym;
                        printf("Computer's turn: %d,%d\n",row+1,j+1);
                        board_print(board,n);
                        printf("\n");
                        break;
                    }
                }
            }
            else if (win_val==2) {
                int col=-1;
                for (int i=0; i<n; i++) {
                    int cnt=0;
                    for (int j=0; j<n; j++) {
                        if (board[j][i]==*c_sym)
                            cnt++;
                        else if (board[j][i]==u_sym)
                            cnt--;
                    }
                    if (cnt==n-1) {
                        col=i;
                        break;
                    }
                }
                for (int i=0; i<n; i++) {
                    if (board[i][col]=='.') {
                        board[i][col]=*c_sym;
                        printf("Computer's turn: %d,%d\n",i+1,col+1);
                        board_print(board,n);
                        printf("\n");
                        break;
                    }
                }
            }
            else if (win_val==3) {
                int cnt=0;
                bool done=false;
                for (int i=0; i<n; i++) {
                    if (board[i][i]==*c_sym)
                        cnt++;
                    else if (board[i][i]==u_sym)
                        cnt--;
                }
                if (cnt==n-1) {
                    for (int i=0; i<n; i++) {
                        if (board[i][i]=='.') {
                            board[i][i]=*c_sym;
                            printf("Computer's turn: %d,%d\n",i+1,i+1);
                            board_print(board,n);
                            printf("\n");
                            done=true;
                            break;
                        }
                    }
                }

                if (!done) {
                    cnt=0;
                    for (int i=0; i<n; i++) {
                        if (board[i][n-1-i]==*c_sym)
                            cnt++;
                        else if (board[i][n-1-i]==u_sym)
                            cnt--;
                    }
                    if (cnt==n-1) {
                        for (int i=0; i<n; i++) {
                            if (board[i][n-1-i]=='.') {
                                board[i][n-1-i]=*c_sym;
                                printf("Computer's turn: %d,%d\n",i+1,n-i);
                                board_print(board,n);
                                printf("\n");
                                break;
                            }
                        }
                    }
                }
            }
        }

        else if (is_losing(board,u_sym,n)) {
            int los_val=is_losing(board,u_sym,n);
            if (los_val==1) {
                int row=-1;
                for (int i=0; i<n; i++) {
                    int cnt=0;
                    for (int j=0; j<n; j++) {
                        if (board[i][j]==u_sym)
                            cnt++;
                        else if (board[i][j]==*c_sym)
                            cnt--;
                    }
                    if (cnt==n-1) {
                        row=i;
                        break;
                    }
                }
                for (int j=0; j<n; j++) {
                    if (board[row][j]=='.') {
                        board[row][j]=*c_sym;
                        printf("Computer's turn: %d,%d\n",row+1,j+1);
                        board_print(board,n);
                        printf("\n");
                        break;
                    }
                }
            }
            else if (los_val==2) {
                int col=-1;
                for (int i=0; i<n; i++) {
                    int cnt=0;
                    for (int j=0; j<n; j++) {
                        if (board[j][i]==u_sym)
                            cnt++;
                        else if (board[j][i]==*c_sym)
                            cnt--;
                    }
                    if (cnt==n-1) {
                        col=i;
                        break;
                    }
                }
                for (int i=0; i<n; i++) {
                    if (board[i][col]=='.') {
                        board[i][col]=*c_sym;
                        printf("Computer's turn: %d,%d\n",i+1,col+1);
                        board_print(board,n);
                        printf("\n");
                        break;
                    }
                }
            }
            else if (los_val==3) {
                int cnt=0;
                bool done=false;
                for (int i=0; i<n; i++) {
                    if (board[i][i]==u_sym)
                        cnt++;
                    else if (board[i][i]==*c_sym)
                        cnt--;
                }
                if (cnt==n-1) {
                    for (int i=0; i<n; i++) {
                        if (board[i][i]=='.') {
                            board[i][i]=*c_sym;
                            printf("Computer's turn: %d,%d\n",i+1,i+1);
                            board_print(board,n);
                            printf("\n");
                            done=true;
                            break;
                        }
                    }
                }

                if (!done) {
                    cnt=0;
                    for (int i=0; i<n; i++) {
                        if (board[i][n-1-i]==u_sym)
                            cnt++;
                        else if (board[i][n-1-i]==*c_sym)
                            cnt--;
                    }
                    if (cnt==n-1) {
                        for (int i=0; i<n; i++) {
                            if (board[i][n-1-i]=='.') {
                                board[i][n-1-i]=*c_sym;
                                printf("Computer's turn: %d,%d\n",i+1,n-i);
                                board_print(board,n);
                                printf("\n");
                                break;
                            }
                        }
                    }
                }
            }
        }

        else {
            if (check_range(r,c-1,n) && check_blank(r,c-1,board,n)) {
                board[r-1][c-2]=*c_sym;
                printf("Computer's turn: %d,%d\n",r,c-1);
                board_print(board,n);
                printf("\n");
            }
            else if (check_range(r,c+1,n) && check_blank(r,c+1,board,n)) {
                board[r-1][c]=*c_sym;
                printf("Computer's turn: %d,%d\n",r,c+1);
                board_print(board,n);
                printf("\n");
            }
            else if (check_range(r+1,c,n) && check_blank(r+1,c,board,n)) {
                board[r][c-1]=*c_sym;
                printf("Computer's turn: %d,%d\n",r+1,c);
                board_print(board,n);
                printf("\n");
            }
            else if (check_range(r-1,c,n) && check_blank(r-1,c,board,n)) {
                board[r-2][c-1]=*c_sym;
                printf("Computer's turn: %d,%d\n",r-1,c);
                board_print(board,n);
                printf("\n");
            }
            else {
                bool flag=false;
                for (int i=0; i<n; i++) {
                    for (int j=0; j<n; j++) {
                        if (board[i][j]=='.') {
                            board[i][j]=*c_sym;
                            printf("Computer's turn: %d,%d\n",i+1,j+1);
                            board_print(board,n);
                            printf("\n");
                            flag=true;
                            break;
                        }
                    }
                    if (flag)
                        break;
                }
            }
        }

        if (computer_won(board,*c_sym,n)) {
            Sleep(1000);
            system("cls");
            printf("Computer won the game!! Better luck next time!\n");
            board_print(board,n);
            break;
        }
    }

    for (int i=0; i<n; i++) {
        free(board[i]);
    }
    free(board);
    free(c_sym);
}

int main() {
    srand(time(NULL));
    tic_tac_toe(3);
    getch();
}