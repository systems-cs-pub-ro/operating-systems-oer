import std.stdio : writeln;

int random_func()
{
    int a = 101, b = 102, c = 103, d = 104;
    int e = 105, f = 106, g = 107;
    return 1;
}

int* bad()
{
    int p = 10;
    int *q = &p;
    return q;
}

void main()
{
    // 1st example
    int *q = bad();
    writeln(*q);
    random_func();
    writeln(*q);

    // 2nd example
    int[10] a;
    //a[20] = 5;

    // 3rd example
    //a[14] = 0;
}
