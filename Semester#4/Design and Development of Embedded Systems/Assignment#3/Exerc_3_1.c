/*

 File name: exerc_3_1.c (or cpp)

 Date: 2017-01-23

 Group Number:  #nr 4

 Members of students contributed:

 Rafael Antonino Sauleo

 Filip Isakovski

 Maria-Bianca Cindroi

 Demonstration code: [<Examen code> <0000>] PENDING

 Implement a test program for a robot. The program asks for the robot's starting position (x, y
coordinates) and then for a string of characters 'm' and 't', where m stands for move a step in current
direction and t for turn of direction as below..
move: means that the robot takes a step in the current direction.
turn: means that the robot turns 90 degrees clockwise. Start direction is always north.
The program performs the instructions of the string one by one. When all instructions are executed
robot stops and the program prints out the robot's position. The program then asks for new starting
position, etc.

 Implement the functions move() and turn() as two void functions and use a pointer parameters as
arguments so that the function can update the robot position which is a variable in the main function
(calling function).
Use enum and a record of type ROBOT as below for the robots position and direction.
enum DIRECTION {N,O,S,W};
typedef struct {
 int xpos;
 int ypos;
 enum DIRECTION dir;
} ROBOT;

 */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <memory.h>

#define MAX 2


enum DIRECTION {
    N = 'n' , O = 'o', S = 's', W = 'w'
};

typedef struct robot{
    int xpos;
    int ypos;
    enum DIRECTION dir;
} ROBOT;



enum COMMAND {
    M = 'm', T = 't'
};


//struct robot
ROBOT robot;

void robot_Command(int x, int y, enum DIRECTION direction) {
    robot.xpos = x;
    robot.ypos = y;
    robot.dir = direction;
}


void move(enum DIRECTION direction){
    switch( direction ) {
        case N:
            robot.ypos++;
            printf("it moved north!, %d\n", robot.ypos);
            break;
        case O:
            robot.xpos--;
            printf("it moved east!%d\n", robot.xpos);
            break;
        case S:
            robot.ypos--;
            printf("it moved south!%d\n", robot.ypos);
            break;
        case W:
            robot.xpos++;
            printf("it moved west! %d\n", robot.xpos);
            break;

        default:
            printf("INPUT ERROR");
            break;
    }


}


void turn(enum DIRECTION direction){
    switch( direction ) {
        case N:
            robot.dir = O;
            printf("DIRECTION east! %c\n", robot.dir);
            break;
        case O:
            robot.dir = S;
            printf("DIRECTION south! %c\n", robot.dir);
            break;
        case S:
            robot.dir = W;
            printf("DIRECTION west! %c\n", robot.dir);
            break;
        case W:
            robot.dir = N;
            printf("DIRECTION north! %c\n", robot.dir);
            break;

        default:
            printf("INPUT ERROR");
            break;
    }

}

void choose_Command(enum COMMAND command){
    switch( command ) {
        case M:
            move(robot.dir);
            break;
        case T:
            turn(robot.dir);
            break;

        default:
            printf("INPUT ERROR");
            break;
    }

}

char readInput(char *pointer){
    fgets(pointer, MAX, stdin);
    fseek(stdin,0,SEEK_END); //we need to flush the buffer
    fflush(stdin);
}

void printLocation(ROBOT robot){
    printf("THE ROBOT'S CURRENT LOCATION IS\n");
    printf("X Position: %d\n", robot.xpos);
    printf("Y Position: %d\n", robot.ypos);
    printf("Direction: %c\n", robot.dir);
}

int main(int argc, char **argv) {
    enum DIRECTION position;

    char x[MAX];
    char *xPointer = x;

    char y[MAX];
    char *yPointer = y;

    char choose[MAX];
    char *choosePointer = choose;

    do{
    printf("Insert X position:");
    readInput(xPointer);
    /*
    position = x[0];
    printf("position %c\n", position);
    move(position);
     */
    printf("x: %c\n", x[0]);

    printf("Insert Y position:\n");
    readInput(yPointer);
    printf("y: %c\n", y[0]);


    robot_Command(atoi(x), atoi(y), N);
    printLocation(robot);

        do {
            printf("Choose between 'm' and 't'\n");
            printf("where m stands for move a step in current direction and t for turn of direction as below\n");
            readInput(choosePointer);
            position = choose[0];
            choose_Command(position);
        }while (choose[0] != 'q');



    } while (choose[0] != 'q');






    return(0);
}
