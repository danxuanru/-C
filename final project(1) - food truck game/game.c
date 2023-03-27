#include <stdio.h>
#include <math.h>
#include <stdlib.h> 
#include <time.h>

// choose prize -> rand() 
// randomly generate the number of slots for boosters in the range of 5 - 15 at the beginning of the game.

// map system (8*8)
// p = player(left-top corner)
// rand() 0~7 -> index of M、B
// M = money bag (row*col*10)
// B = booster (rand())
// action: 1(up)、2(down)、3(left)、4(right)、5(finish) - $25 / 1 time 
// (money not enough & out of range => warning message、stop action)

int random_number(int, int);
int *set_booster_slot(void);
void add_booster(int, int[], int[]);
void use_booster(int, int[], int[]);
void booster_system(int[], int[], int[]);

void set_map(int (*)[3]);
void map_system(int (*)[3], int*, int[], int[], int*, int*, int, int*);
void get_money(int*, int*);
void get_booster(int*, int[], int[]);

void ask_action(int[], int, int);
void ask_action_again(int[], int);
void area_action(int[], int[], int[], int[], int[], int*, int*, int*, int*, int*, int*);
void check_result(int[], int[], int[], int, int[][3], int*, int[], int[], int*, int*, int, int*);
void continue_(void);

int* set_lottery(int);
void displayBorad(int, int*);
void lottery_system(int*, int*, int*, int*, int*, int*, int[], int[], int, int*, int*, double, int*);
void open_lottery(int, int, int, int*, int*, int*, int*, int*, int[], int[]);

void bank_system(int*, int*, int*, double, int*, double , int*);
void lending(int*, int*, int*, double , int*);
void deposit(int*, int*, double);
void withdraw(int*, int*);
void repayment(int*, int*, int*, int*, int*, double*, double*);


int main() {

    int money=100, making_time=15, hotdog_price=30;
    int booster[3]={0};  // number of 3 kinds of booster
    int b_status[3]={0};
    int speed_cost=50, flavor_cost=100, t_earn;
    int l_size=3, lottery_cost=500;
    int l_time=0, free_chance = 0;
    
    // bank system variable
    int loan = 0, credit = 100, period = 0, saving = 0;
    double l_rate = 1+(double)random_number(10,50)/100.0;
    double s_rate = 1+(double)random_number(1,10)/100.0;;


    // set lottery board
    int *lottery = set_lottery(l_size);
    
    // dynamic decide booster slop array
    int *booster_slots = set_booster_slot();

    // set map
    int map[5][3];  // row: area , col: P/M/B
    int (*p)[3];
    for(p = map; p<map+5; p++)
    {
        set_map(p);
    }
    
    printf("Welcome, young boss!\n");

    while(1) { // start day

        // reset action (area 5: action=1)
        int earn[5]={0}, action[5]={0,0,0,0,1}, situation[5]={0}, hotdog[5]={0};
        t_earn=0;
        
        printf("Chop chop, It's dawn.\n");
        printf("You have %d dollars.\n", money);
        printf("You need %d minutes to make a hotdog.\n", making_time);
        printf("The price of a hotdog is $%d.\n", hotdog_price);
        printf("You have %d speed booster(s), %d price booster(s), %d area booster(s).\n", booster[0], booster[1], booster[2]);

        // booster system 
        booster_system(b_status, booster, booster_slots);
        
        // ask 4 action at the beginning 
        ask_action(action, speed_cost, flavor_cost);

        // area loop
        // area_action(&action, &hotdog, &earn, &situation);
        area_action(action, hotdog, earn, situation, b_status, &t_earn, &money, &making_time, &hotdog_price, &speed_cost, &flavor_cost);
        printf("Well done, you earn $%d today.\n", t_earn);
        check_result(situation, hotdog, earn, b_status[2], map, &money, booster_slots, booster, &loan, &period, l_rate, &credit);
        
        continue_();
        free_chance++;
        printf("You get one free choice.\n");
        lottery_system(&l_time, &l_size, &money, &lottery_cost, &free_chance, lottery, booster_slots, booster, hotdog_price, &loan, &period, l_rate, &credit);

        // bank 還款
        // 還不起 credit-1 -> credit決定最大借款金額
        repayment(&money, &loan, &credit, &period, &saving, &l_rate, &s_rate);
        printf("Welcome to C bank!\n");
        bank_system(&money, &loan, &period, l_rate, &saving, s_rate, &credit);
    }
	return 0;
}

int random_number(int min, int max)
{
    srand( time(NULL) ); // 亂數種子 
    int x = rand() % (max - min + 1) + min;
    return x;
    // return rand() % 10; 1~9
}

int *set_booster_slot(void)
{
    int N = random_number(5,15);
    int *slots = (int*) malloc((N+1)*sizeof(int)); 
    for(int i=0; i<N; i++) slots[i]=-1;  // 預設-1
    slots[N] = -2; // 計算長度的保留值
    
    // for(int i=0; i<N+1; i++) printf("%d ", slots[i]);
    // printf("\n");

    return slots;
}

void add_booster(int k, int slot[], int b[]) // k: 0,1,2 kinds of booster
{
    // int length = (int) sizeof(*slot) / sizeof(slot[0]);
    int length = 0;
    while(slot[length]!=-2) length++;
    int b_now = 0;
    while(slot[b_now]!=-1) b_now++;  // 現在的booster數量

    if(slot[length-1]!=-1) // slot full
    {
        b[slot[0]]--; // discard first booster
        // 全部左移
        for(int i=0; i<length; i++) slot[i] = slot[i+1];
        b[k]++;
    }
    else
    {
        slot[b_now] = k;
        b[k]++;
    }
    // message
    if(k==0) printf("You add a speed booster\n");
    else if(k==1) printf("You add a price booster\n");
    else if(k==2) printf("You add an area booster\n");
}

void use_booster(int k, int slot[], int b[])
{
    int length = 0;
    while(slot[length]!=-2) length++;
    int b_now = 0;
    while(slot[b_now]!=-1) b_now++;  // 現在的booster數量

    for(int n=0; n<b_now; n++)
    {  // search first booster 
        if(slot[n]==k) 
        {
            b[k]--; // booster數量-1
            b_now--; 

            // 剩餘左移
            for(int i=n; n<b_now; i++) slot[i] = slot[i+1];
            break;
        }
    }
}

void booster_system(int status[], int b[], int slot[])
{
    int action;

    while(1) {
        printf("Open/Close boosters:\n");
        printf("  [1] Speed booster (now %s)\n", status[0]==1 ? "open" : "close");
        printf("  [2] Price booster (now %s)\n", status[1]==1 ? "open" : "close");
        printf("  [3] Area booster (now %s)\n", status[2]==1 ? "open" : "close");
        printf("  [4] Finish\n");
        printf("Enter the number(s): ");
        scanf("%d", &action);

        if(action == 1) status[0]==1 ? (status[0] = 0) : (status[0] = 1);
        else if(action == 2) status[1]==1 ? (status[1] = 0) : (status[1] = 1);
        else if(action == 3) status[2]==1 ? (status[2] = 0) : (status[2] = 1);
        else if (action == 4) break; //finish
        else printf("Invalid input!!!!\n");
    }

    for(int i=0; i<3; i++){
        if(status[i] == 1){
            if(b[i]==0) status[i] = 0;
            else use_booster(i, slot, b);
        }
    }
    return;
}

void ask_action(int action[], int s_cost, int f_cost)
{
    printf("Actions you can take for each area:\n");
    printf("  [1] Sell the hotdogs\n");
    printf("  [2] Improve your cooking speed\n"); 
    printf("      (- $%d, - $%d, - $%d, - $%d for next four upgrades)\n", s_cost, s_cost*2, s_cost*4, s_cost*8);
    printf("  [3] Improve your hotdog flavor\n");
    printf("      (- $%d, - $%d, - $%d, - $%d for next four upgrades)\n", f_cost, f_cost*2, f_cost*4, f_cost*8);
    printf("Enter the number(s): ");
    scanf("%d %d %d %d", &action[0], &action[1], &action[2], &action[3]);
    for(int i=0; i<4; i++){
        if(action[i]>3 || action[i]<1) ask_action_again(action, i);
    }
}

void ask_action_again(int action[], int n)
{
    
    // second input
    printf("Actions you can take at Area %d:\n", n+1); // area = i+1
    printf("  [1] Sell the hotdogs\n");
    printf("  [2] Improve your cooking speed\n");
    printf("  [3] Improve your hotdog flavor\n");
    printf("Enter the number(s): ");
    scanf("%d", &action[n]);
    
    for(int i=n; i<4; i++)
    {    
        if (action[i]>3 || action[i]<1) // wrong input => go_on = 0
        {
            printf("Invalid input!!!!\n");
            ask_action_again(action, i);
            return;
        }
        // go_on = 1;  // all correct
    }
    return;
}

void area_action(int action[], int hotdog[], int earn[], int situation[], int status[], int *t_earn, int *money, int *making_time, int *price, int *speed_cost, int *flavor_cost)
{
    for(int i=0; i<(4+status[2]); i++){  

        // set 
        if(status[0]==1) hotdog[i] = (180/(*making_time))*2;  // hotdog double
        else hotdog[i] = 180/(*making_time);

        if(status[1]==1) earn[i] = hotdog[i]*((*price)*2);  // price double
        else earn[i] = hotdog[i]*(*price);
        
        // area_action(action[i]);
        switch (action[i])
        {
            case 1:  // situation 1: sell hotdog
                situation[i] = 1;
                *t_earn += earn[i];
                *money += earn[i];
                break;

            case 2:  //improve speed
                // money not enough => limit => improve
                if(*money<*speed_cost){ // situation 2: money dosen't enough 

                    situation[i] = 2;
                    // force to sell hotdog
                    *t_earn += earn[i];
                    *money += earn[i];

                }
                else if(*making_time==1){  // situation 3: improve speed limit
                    situation[i] = 3;
                    // force to sell hotdog
                    *t_earn += earn[i];
                    *money += earn[i];
                
                }else{  // situation 4: improve speed
                    situation[i] = 4;
                    *making_time -= 1;  
                    *money -= *speed_cost;  
                    *speed_cost *= 2; // cost double
                }
                break;

            case 3:  //improve flavor
                if(*money<*flavor_cost){ // situation 2: money dosen't enough 
                    situation[i] = 2;
                    // force to sell hotdog
                    *t_earn += earn[i];
                    *money += earn[i];
                }else{  // situation 5: improve flavor
                    situation[i] = 5;
                    *price += 10;
                    *money -= *flavor_cost; 
                    *flavor_cost *= 2;  //double
                }
                break;
        }
    }
}

void check_result(int situation[], int hotdog[], int earn[], int area_status, int map[][3], int *money, int slot[], int b[], int *l, int *pd, int lr, int *cr)
{
    int check;
    // check the earn of each area
    while(1){
        printf("Which result of the area you want to check?\n");
        printf("  [1] Area 1\n");
        printf("  [2] Area 2\n");
        printf("  [3] Area 3\n");
        printf("  [4] Area 4\n");
        if(area_status==1){  // area expand
            printf("  [5] Area 5\n");
            printf("  [6] Done\n");
            printf("Enter the number(s): ");
            scanf("%d", &check);
            if(check==6) break;  // Done => jump loop
            if(check>6 || check<1) {  // invalid input => new loop
                printf("Invalid input!!!!\n");
                continue;
            }   
        } else { 
            printf("  [5] Done\n");
            printf("Enter the number(s): ");
            scanf("%d", &check);
            if(check==5) break;  // Done => jump loop
            if(check>5 || check<1) {  // invalid input => new loop
                printf("Invalid input!!!!\n");
                continue;
            }  
        }

        map_system(&map[check-1], money, slot, b, l, pd, lr, cr); // 要放在result前還是result後

        // result
        switch (situation[check-1])  // area-1
        {
            case 1:  // sell hotdog
                printf("You make %d hotdogs here!\n", hotdog[check-1]);  // hotdog數量 (hotdog[])
                printf("You earn $%d!\n", earn[check-1]);
                break;

            case 2:  // money dosen't enough 
                printf("Can't you tell how poor you are?\n");
                printf("Go vending your hotdogs instead of thinking about self-improvement!\n");
                printf("You make %d hotdogs here!\n", hotdog[check-1]);
                printf("You earn $%d!\n", earn[check-1]);
                break;

            case 3:  // speed limit
                printf("Do you want to travel through time?\n");
                printf("GO WORK!!\n");
                printf("You make %d hotdogs here!\n", hotdog[check-1]);
                printf("You earn $%d!\n", earn[check-1]);
                break;

            case 4:  // improve speed
                printf("You glimpse the secret of wind.\n");
                printf("Your hands can move faster now.\n");
                break;

            case 5:  // improve flavor
                printf("You feel the soul of the ingredients.\n");
                printf("Your hotdogs are more appetizing now.\n");
                break;
        }
    }
}

void set_map(int (*p)[3])
{
    // rand() decide col&row
    // [area][0]: player , [area][1]: M , [area][2]: B
    int row,col,i=1;
    (*p)[0] = 0; // player at left-top corner ([0][0])
    while(i<3){
        row = random_number(0,7);
        col = random_number(0,7);
        // position: row*8+col
        if((*p)[i-1] != (row*8+col))  // 確認位置沒有重複
        {
           (*p)[i] = (row*8+col);
           i++;
        }
    }
}

void map_system(int (*p)[3], int *money, int slot[], int b[], int *l, int *pd, int lr, int *cr)
{
    int action, a;
    int *player = &(*p)[0];  // 用player替代
    
    // show map 
    for(int row=0; row<8; row++){
        for(int col=0; col<8; col++){
            if(*player==row*8+col) printf("P ");
            else if(*(player+1)==row*8+col) printf("M ");
            else if(*(player+2)==row*8+col) printf("B ");
            else printf(". ");
        }
        printf("\n");
    }

    // player move
    // 可動多步還是一次一步??
    do{
        printf("How to move?\n");
        printf("[1] Up / [2] down / [3] left / [4] right\n");
        printf("[5] finish\n");
        printf("Enter the number: ");
        scanf("%d", &action);
    }
    while(action>5 || action<1);

    if(action == 5) return;
    
    // check money
    if(*money<25){
        printf("Not Enough Money!!\n");
        printf("Do you need to borrow some money? \n[1]Yes [2]No ");
        scanf("%d", &a);
        if(a==1) {
            lending(money, l, pd, lr, cr);
            map_system(p, money, slot, b, l, pd, lr, cr);
        }
        return;
    }

    // move
    if(action==1) 
    {  // Up: -8
        if(*player-8 < 0) printf("Out of map's boundary!!\n");
        else 
        {
            *player-=8;
            *money -= 25;
            if(*player ==  *(player+1)) get_money(money, player);
            else if(*player ==  *(player+2)) get_booster(player, slot, b);
        }
    }
    else if(action==2)
    {  // down: +8
        if(*player+8 > 63) printf("Out of map's boundary!!\n");
        else 
        {
            *player+=8;
            *money -= 25;
            if(*player ==  *(player+1)) get_money(money, player);
            else if(*player ==  *(player+2)) get_booster(player, slot, b);
        }
    }
    else if(action==3)
    { // left: -1
        if(*player%8 == 0) printf("Out of map's boundary!!\n");
        else 
        {
            *player-=1;
            *money -= 25;
            if(*player ==  *(player+1)) get_money(money, player);
            else if(*player ==  *(player+2)) get_booster(player, slot, b);
        }
    }
    else if(action==4)
    { // right: +1
        if(*player%8 == 7) printf("Out of map's boundary!!\n");
        else 
        {
            *player+=1;
            *money -= 25;
            if(*player ==  *(player+1)) get_money(money, player);
            else if(*player ==  *(player+2)) get_booster(player, slot, b);
        }
    }
    // all get: reset map
    if(*(player+1)==-1 && *(player+2)==-1) {
        set_map(p);
        printf("Reset the map!\n");
    }

    map_system(p, money, slot, b, l, pd, lr, cr);
    return;
}

void get_money(int *money, int *p)
{
    printf("you get $%d!\n", (*p/8)*(*p%8)*10);
    *money += (*p/8)*(*p%8)*10;
    *(p+1) = -1;  // wouldn't print on board
}
void get_booster(int *p, int slot[], int b[])
{
    printf("you get a booster!\n");
    add_booster(random_number(0,2), slot, b);
    *(p+2) = -1;  // wouldn't print on board
}
/*
void check_map(int P, int M, int B)
{
    int M_row = M/8;
    int M_col = M%8;
    if(P) printf("Out of map's boundary!!\n");

    if(P==M) money += M_col*M_row*10;
    else if(P==B) add_booster(random_number(0,2));
}
*/

void continue_(void)
{   
    int go_on;
    printf("Do you want to continue or exit?\n");
    printf("  [1] Continue\n");
    printf("  [2] Exit\n");
    printf("Enter the number(s): ");
    scanf("%d", &go_on);

    if(go_on == 1) return;  // continue
    else if(go_on == 2){ // exit
        printf("We will miss you. Bye!");
        exit(0);
    }
    printf("Invalid input!!!!\n");
    continue_(); // invalid input => repeat
    return;
}

int *set_lottery(int size)
{
    int *board = (int*) malloc(size*size*sizeof(int));

    for(int m=0; m<size; m++){
        for(int n=0; n<size; n++){
            board[m*size+n] = m*size+(n+1);
        }
    }

    // for(int m=0; m<size; m++){
    //     for(int n=0; n<size; n++){
    //         printf("%d ", board[m*size+n]);
    //     }
    //     printf("\n");
    // }
    return board;

}

void lottery_system(int *t, int *size, int *money, int *cost, int *chance, int *board, int slot[], int b[], int price, int *l, int *pd, double lr, int *cr)
{
    int row, col;
    while(1){  
        
        // all be chosen -> refreshing
        if(*t == (*size)*(*size)){  

            *size += 2;
            *t = 0;
            *cost = 500;
            
            free(board);
            board = set_lottery(*size);  // int return可以, 但 void傳值不行??
        }
        
        // choose
        int lottery_number;
        while(1) {

            // display board
            displayBorad(*size, board);
            
            printf("You can choose\n");
            printf("  [number on cell] to open (- $%d)\n", *chance > 0 ? 0 : *cost);
            printf("  [0] to continue the game\n");
            printf("Enter the number(s): ");
            scanf("%d", &lottery_number);

            
            // get col row
            row = (lottery_number -1) / *size;
            col = (lottery_number%(*size)==0) ? *size-1 : lottery_number%(*size)-1;

            if(lottery_number==0) return;  // end lottery system
            if((lottery_number<=((*size)*(*size)) && lottery_number>0) && board[row*(*size)+col]!=-1) break;  // correct input
            printf("Invalid input!!!!\n");
        } 

        // cost
        if(*chance>0){  // use free chance
            *chance -= 1;
            
        } else { // spend
        
            if(*money < *cost) {
                int a;
                printf("Not Enough Money!!\n");
                // borrowing or withdraw
                printf("Do you need to borrow some money? [1]Yes [2]No ");
                scanf("%d", &a);
                if(a==1) {
                    lending(money, l, pd, lr, cr);
                    continue;
                }
                else return;  // end lottery system
            }
            *money -= *cost;
            *cost += 500;
        }

        open_lottery(row, col, price, size, board, t, money, chance, slot, b);
        
    }
}

void displayBorad(int size, int *board)
{
    // amount of '-' = digit of (size*size) + 2
    int digit = 1;
    int max = size*size;
    while(max>9){
        max /= 10;
        digit++;
    }

    for(int row=0; row<size; row++){
        for(int col=0; col<size; col++){
            printf("+"); 
            for (int i=0; i<digit+2; i++) printf("-");  // max digit + 2
        }
        printf("+\n");
        printf("|");
        for(int col=0; col<size; col++){
            printf(" ");
            if(board[row*size+col]==-1){  // -1 chosen cell -> x
                for(int i=0; i<digit-1; i++) printf(" ");
                printf("x |");
                
            }else{
                int num=board[row*size+col];
                int d=1;  // cell digit
                while(num>9){
                    num /= 10;
                    d++;
                }
                for(int i=0; i<digit-d; i++) printf(" ");  // max digit - cell digit = extra space
                printf("%d |", board[row*size+col]);
            }
        }
        printf("\n");
    }
    for(int col=0; col<size; col++){
        printf("+");
        for (int i=0; i<digit+2; i++) printf("-");
    }
    printf("+\n");
}

void open_lottery(int row, int col, int price, int *size, int *board, int *t, int *money, int *chance, int slot[], int b[])
{
    // open prize
    int prize;
    while(1){  

        prize = random_number(1,9);
        board[row*(*size)+col] = -1;  // chosen
        *t+=1;

        if(prize == 1){
            printf("Fortune, fortune! You get $%d!\n", 100*price);
            *money += 100*price;
            break;
        }
        else if (prize == 2)
        {
            printf("You get an extra choice!\n");  // another free chance
            *chance+=1;
            break;
        }
        else if(prize>=3 && prize<=6)  // another open automatically
        {
            if(prize==3) { // above

                if(row==0) row = (*size-1); // row 已在最上面 => row=size-1
                else row-=1;  
                // lottery_number += (size-1)*size;
                // down (size-1) row / every row has 'size' cell
                // lottery_number -= size;
            }
            else if(prize==4){  // under

                if(row==(*size-1)) row = 0; // row 已在最下面 => row=0
                else row+=1; 
                // lottery_number -= (size-1)*size; 
                // up (size-1) row / every row has 'size' cell
                // lottery_number += size;
            }
            else if(prize==5) { // left

                if(col==0) col = (*size-1); // col 已在最左邊 => col = size-1
                else col-=1; 
                // lottery_number += (size-1);
                // lottery_number -= 1;
            }
            else if(prize==6) { // right

                if(col==(*size-1)) col = 0; // col 已在最右邊 => col=0
                else col+=1; 
                // lottery_number -= (size-1);
                // lottery_number += 1;
            }

            // new open
            if(board[row*(*size)+col] == -1){  // has been chosen
                printf("Bad Luck :(\n");
                break;
            }
            printf("Another open on %d!\n", board[row*(*size)+col]);
            continue;  // new prize -> new loop
        }
        else if(prize>=7)  // get booster
        {
            printf("You get a booster!!\n");
            if(prize==7) add_booster(0, slot, b);
            if(prize==8) add_booster(1, slot, b);
            if(prize==9) add_booster(2, slot, b);
            break;
        }
        
    }
}

void bank_system(int *money, int *loan, int *period, double l_rate, int *saving, double s_rate, int *credit)
{
    int action;
    printf("Now you have $%d cash on hand\n", *money);
    printf("Which banking service do you want?\n");

    while(1)
    {
        printf("[1] lending\n");
        printf("[2] saving\n");
        printf("[3] withdraw\n");
        printf("[4] finish\n");
        printf("Enter the number: ");
        scanf("%d", &action);
        if(action<=4 || action>=1) break;
        else printf("Invalid input!!!!\n");
    }

    if(action == 1) lending(money, loan, period, l_rate, credit);
    else if(action == 2) deposit(money, saving, s_rate);
    else if(action == 3) withdraw(money, saving);
    else return;
    // continue
    bank_system(money, loan, period, l_rate, saving, s_rate, credit);
}

void lending(int *m, int *l, int *pd, double r, int *cr)
{
    int lend, p; // 金額、分期
    int max = (*cr)*100;
    if(*pd!=0) printf("You haven't paid off ths loan!\n");
    else
    {
        printf("Interest rate: %.2f, maximum amount you can borrow: %d\n", r, max);
        printf("How much do you want to borrow? ");
        scanf("%d", &lend); 
        if(lend<=0)
        {
            printf("Invalid input!!!!\n");
            return;
        }
        if(lend>max)
        {
            printf("Lending Amount Exceeded!!\n");
            return;
        }
        printf("Number of installments? ");
        scanf("%d", &(*pd));
        if(*pd<=0)
        {
            printf("Invalid input!!!!\n");
            *pd=0;
            return;
        }
        *l += rint((lend*r) / *pd);
        *m += lend;
    }
    return;
}

void deposit(int *m, int *s, double r)
{
    int save;
    printf("You have $%d in your account\n", *s);
    printf("How much do you want to save? (Current interest rate: %.2f) ", r);
    scanf("%d", &save);
    if(save<=0)
    {
        printf("Invalid input!!!!\n");
        return;
    }
    if(save>*m)
    {
        printf("Not Enough Money!!\n");
        return;
    } 
    *m -= save;
    *s += save;
    return;
}

void withdraw(int *m, int *s)
{
    int wd;
    if(*s == 0)
    {
        printf("You haven't deposited any money in your account!");
        return;
    }
    else
    {
        printf("You have $%d in your account\n", *s);
        printf("How much do you want to withdraw? ");
        scanf("%d", &wd);
        if(wd<=0)
        {
            printf("Invalid input!!!!\n");
            return;
        }
        if(wd>*s)
        {
            printf("Not Enough Savings!!\n");
            return;
        } 
        *m += wd;
        *s -= wd;
    }
    return;
}

void repayment(int *m, int *l, int *cr, int *pd, int *s, double *lr, double *sr)
{
    if(*pd==0) return;  // no loan
    if(*m>*l)  // 可以還款
    {
        *m -= *l;
        *pd -= 1;
        if(*pd==0) *l = 0; // 還清
    }
    else 
    {
        *cr-=5; // 還不起
        printf("You can't pay back the loan! Your credit will be deducted 5 points.\n");
    }

    // saving interest rate
    *s *= *sr;
    
    // random decide interest rate tomorrow
    *lr = 1+(double)random_number(10,50)/100.0;
    *sr = 1+(double)random_number(1,10)/100.0;
}


/*
void array_moveLeft(int array[], int n)  // index:n之後的左移
{
    int now=0;
    while(array[now]!=-1) now++;
    for(int i=n; i<now; i++) array[i] = array[i+1];
}
*/