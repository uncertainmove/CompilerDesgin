float cc[10][11];

struct Position
{
    float x = 3, y;
};

// Redefine field "x"
struct Pos {
    float x, y;
    int x;
};

// Duplicated name "Position1"
struct Position1 {
    float x;
};
struct Position1 {
    int x;
};

// Undefine variable "j"
int func1(int i) {
    int i = 0;
    j = i + 1;
}

// Undifine function "inc"
int func2(){
    int i = 0;
    int j[5];
    inc(i);
}

// Redefine variable "i"
int func3() {
    int i, j;
    int i;
}

// Redefine function "func"
int func(int i) {
    return i;
}
int func() {
    return 0;
}

// Type mismatched for assignment
int func4() {
    int i;
    i = 3.7;
}

// The left-hand side of an assignment must be a variable
int func5() {
    int i;
    10 = i;
}

// Type mismatched for operands
int func6() {
    float j;
    10 + j;
}

// Type mismatched for return
int func7() {
    float j = 1.7;
    return j;
}

// Function "func8(int)" is not applicable for arguments "(int, int)"
int func8(int i) {
    return i;
}
int func9() {
    func8(1, 2);
}

// "i" is not an array
int func10() {
    int i;
    i[0];
}

// "i" is not a function
int func11() {
    int i;
    i(10);
}

// "1.5" is not an integer
int func12() {
    int i[10];
    i[1.5] = 10;
}

// Illegal use of "."
int func13() {
    int i;
    i.x;
}

// Non-exitent field "n"
int func14() {
    struct Position p;
    int s = 0;
    if(p.n == 3.7)
        return 0;
    else {
        int s = 1;
        if(s == 0) {
            int s=3;
            if(s) {
                s=0;
            }
            else{
                int d=4;
                s=3;
            }
        }
    }
}

// Undefined structure "Position2"
int func15() {
    struct Position2 i;
}

/* 
 * choose to do
 */
// Incomplete definition of function "func"
