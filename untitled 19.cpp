class A {
public:
    int x;        // public, non-static
    static int y; // static
};

int A::y = 0;

int main() {
    A a1, a2;

    a1.x = 10;
    a2.x = 20;

    A::y = 100;
}

