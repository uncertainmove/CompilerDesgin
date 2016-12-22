// int i;

int fact(int n) {
    int i = 4;
    if(n == 1) {
        return n;
    }
    else {
        return (n * fact(n - 1));
    }
}

int main() {
    int m, result;
    m = 4;
    if(m > 1) {
        result = fact(m);
    }
    else {
        result = 1;
    }
    return 0;
}
