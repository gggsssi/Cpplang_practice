
/*
==========================================================
   STUDY COMPANION v1.1
   Linear Algebra & Computer Science - Offline Edition

   For Dev C++ 5.11:
   Tools -> Compiler Options -> Add: -std=c++11
   OR just compile as-is (all C++98 compatible)

   Compile:  g++ -o study study_companion.cpp
   Run:      study.exe
==========================================================
*/

#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <iomanip>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <windows.h>
#include <conio.h>

using namespace std;

/* =========================================
   WINDOWS COLOR SYSTEM
   ========================================= */
HANDLE hConsole;

void setColor(int fg, int bg) {
    SetConsoleTextAttribute(hConsole, (bg << 4) | fg);
}

void setColor(int fg) {
    SetConsoleTextAttribute(hConsole, fg);
}

void resetColor() {
    SetConsoleTextAttribute(hConsole, 7);
}

void printColor(const string& s, int fg) {
    setColor(fg);
    cout << s;
    resetColor();
}

/* =========================================
   MATRIX TYPE  (space between >> for C++98)
   ========================================= */
typedef vector<vector<double> > Matrix;
typedef vector<vector<int> >    IntGrid;
typedef vector<pair<double,double> > VecList;

Matrix makeMatrix(int r, int c, double val) {
    return Matrix(r, vector<double>(c, val));
}

Matrix makeMatrix(int r, int c) {
    return Matrix(r, vector<double>(c, 0.0));
}

/* =========================================
   CONSOLE SETUP
   ========================================= */
void setupConsole() {
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleOutputCP(CP_UTF8);
    system("mode con: cols=100 lines=50");
}

void clearScreen() {
    system("cls");
}

void hideCursor() {
    CONSOLE_CURSOR_INFO info;
    info.dwSize   = 1;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(hConsole, &info);
}

void showCursor() {
    CONSOLE_CURSOR_INFO info;
    info.dwSize   = 1;
    info.bVisible = TRUE;
    SetConsoleCursorInfo(hConsole, &info);
}

void pauseKey() {
    printColor("\n  [Press any key to continue]", 8);
    _getch();
}

string intToStr(int n) {
    ostringstream ss;
    ss << n;
    return ss.str();
}

string dblToStr(double d, int prec) {
    ostringstream ss;
    ss << fixed << setprecision(prec) << d;
    return ss.str();
}

/* =========================================
   BORDER HELPERS
   ========================================= */
void drawBorder(int w) {
    printColor("  +", 11);
    printColor(string(w - 4, '-'), 11);
    printColor("+\n", 11);
}

void drawTitled(const string& title, int w) {
    int pad = (w - 4 - (int)title.size()) / 2;
    if (pad < 0) pad = 0;
    int right = w - 4 - pad - (int)title.size();
    if (right < 0) right = 0;
    printColor("  |", 11);
    cout << string(pad, ' ');
    printColor(title, 14);
    cout << string(right, ' ');
    printColor("|\n", 11);
}

void drawLine(int w) {
    printColor("  |", 11);
    cout << string(w - 4, ' ');
    printColor("|\n", 11);
}

/* =========================================
   SPLASH SCREEN
   ========================================= */
void showSplash() {
    clearScreen();
    hideCursor();
    cout << "\n\n";
    printColor("    _____ _             _         \n", 11);
    printColor("   / ____| |           | |        \n", 11);
    printColor("  | (___ | |_ _   _  __| |_   _  \n", 10);
    printColor("   \\___ \\| __| | | |/ _` | | | | \n", 10);
    printColor("   ____) | |_| |_| | (_| | |_| | \n", 9);
    printColor("  |_____/ \\__|\\__,_|\\__,_|\\__, | \n", 9);
    printColor("                            __/ | \n", 9);
    printColor("                           |___/  \n\n", 9);
    printColor("       C O M P A N I O N  -  Offline Study Tool\n", 14);
    printColor("       Linear Algebra  &  Computer Science\n\n", 8);
    drawBorder(60);
    drawTitled("v1.1  |  No internet needed  |  100% Offline", 60);
    drawBorder(60);
    cout << "\n";
    printColor("  Loading", 8);
    for (int i = 0; i < 5; i++) {
        Sleep(180);
        printColor(".", 10);
    }
    cout << "\n";
    Sleep(300);
    showCursor();
}

/* =========================================
   PRINT MATRIX
   ========================================= */
void printMatrix(const Matrix& M, const string& name) {
    int rows = (int)M.size();
    int cols = (int)M[0].size();
    if (!name.empty()) {
        printColor("  " + name + " =\n", 14);
    }
    for (int i = 0; i < rows; i++) {
        printColor("  [ ", 11);
        for (int j = 0; j < cols; j++) {
            double v = M[i][j];
            if (fabs(v) < 1e-9) v = 0.0;
            setColor(15);
            cout << setw(8) << fixed << setprecision(3) << v;
            resetColor();
            if (j < cols - 1) cout << "  ";
        }
        printColor("  ]\n", 11);
    }
    cout << "\n";
}

void printMatrix(const Matrix& M) {
    printMatrix(M, "");
}

/* =========================================
   VISUALIZER: 2D VECTOR PLOT
   ========================================= */
void plotVectors2D(VecList vecs, vector<string> labels) {
    const int W = 41, H = 21;
    const int cx = W / 2, cy = H / 2;

    vector<string> grid(H, string(W, ' '));
    IntGrid colorGrid(H, vector<int>(W, 7));

    /* Axes */
    for (int i = 0; i < W; i++) { grid[cy][i] = '-'; colorGrid[cy][i] = 8; }
    for (int i = 0; i < H; i++) { grid[i][cx] = '|'; colorGrid[i][cx] = 8; }
    grid[cy][cx] = '+';
    colorGrid[cy][cx] = 8;

    /* Scale */
    double maxv = 1.0;
    for (int vi = 0; vi < (int)vecs.size(); vi++) {
        maxv = max(maxv, max(fabs(vecs[vi].first), fabs(vecs[vi].second)));
    }
    double scaleX = (cx - 2) / maxv;
    double scaleY = (cy - 1) / maxv;

    int vecColors[] = {10, 11, 14, 13, 12};
    char syms[]     = {'>', '^', '#', '~', '@'};

    for (int vi = 0; vi < (int)vecs.size(); vi++) {
        for (int s = 1; s <= 50; s++) {
            double t = (double)s / 50.0;
            int gx = cx + (int)(vecs[vi].first  * scaleX * t);
            int gy = cy - (int)(vecs[vi].second * scaleY * t);
            if (gx >= 0 && gx < W && gy >= 0 && gy < H) {
                grid[gy][gx]      = syms[vi % 5];
                colorGrid[gy][gx] = vecColors[vi % 5];
            }
        }
        /* tip */
        int gx = cx + (int)(vecs[vi].first  * scaleX);
        int gy = cy - (int)(vecs[vi].second * scaleY);
        if (gx >= 0 && gx < W && gy >= 0 && gy < H) {
            grid[gy][gx]      = '*';
            colorGrid[gy][gx] = 12;
        }
    }

    cout << "\n";
    printColor("    2D Vector Space Visualizer\n", 14);
    printColor("    " + string(W + 2, '-') + "\n", 8);
    for (int i = 0; i < H; i++) {
        printColor("    |", 8);
        for (int j = 0; j < W; j++) {
            setColor(colorGrid[i][j]);
            cout << grid[i][j];
        }
        resetColor();
        printColor("|\n", 8);
    }
    printColor("    " + string(W + 2, '-') + "\n\n", 8);

    for (int i = 0; i < (int)labels.size(); i++) {
        printColor("    [" + string(1, syms[i % 5]) + "] ", vecColors[i % 5]);
        printColor(labels[i] + "\n", 7);
    }
    cout << "\n";
}

/* =========================================
   VISUALIZER: MATRIX HEATMAP
   ========================================= */
void matrixHeatmap(const Matrix& M) {
    int rows = (int)M.size();
    int cols = (int)M[0].size();
    double maxv = 0.0;
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            maxv = max(maxv, fabs(M[i][j]));
    if (maxv == 0.0) maxv = 1.0;

    printColor("\n  Matrix Heatmap:\n\n", 14);
    for (int i = 0; i < rows; i++) {
        cout << "  ";
        for (int j = 0; j < cols; j++) {
            double ratio = fabs(M[i][j]) / maxv;
            int    col;
            string cell;
            if      (ratio > 0.8) { col = 12; cell = "##"; }
            else if (ratio > 0.6) { col = 14; cell = "=="; }
            else if (ratio > 0.4) { col = 10; cell = "--"; }
            else if (ratio > 0.2) { col = 11; cell = ".."; }
            else                  { col =  8; cell = "  "; }
            printColor("[" + cell + "]", col);
        }
        cout << "\n";
    }
    printColor("\n  Scale: ", 8);
    printColor("[##]High  ", 12);
    printColor("[==]Med   ", 14);
    printColor("[--]Low   ", 10);
    printColor("[..]Tiny\n\n", 11);
}

/* =========================================
   VISUALIZER: SUBSPACE DIAGRAM
   ========================================= */
void drawSubspaceVisual(int rank, int nullDim, int totalCols) {
    printColor("\n  Fundamental Subspaces:\n\n", 14);

    printColor("  Input Space R^" + intToStr(totalCols) + ":  [", 11);
    for (int i = 0; i < totalCols - nullDim; i++) printColor("=", 10);
    for (int i = 0; i < nullDim; i++)             printColor("~", 8);
    printColor("]\n", 11);

    printColor("                   ", 7);
    for (int i = 0; i < totalCols - nullDim; i++) printColor("^", 10);
    for (int i = 0; i < nullDim; i++)             printColor("^", 8);
    cout << "\n";

    printColor("                   ", 7);
    printColor("Row Space(" + intToStr(totalCols - nullDim) + "d) ", 10);
    if (nullDim > 0) printColor("Null(" + intToStr(nullDim) + "d)", 8);
    cout << "\n\n";

    printColor("                   A maps  vvv\n\n", 8);

    printColor("  Output Space:    [", 11);
    for (int i = 0; i < rank; i++) printColor("=", 14);
    printColor("   ]\n", 11);

    printColor("                    ", 7);
    for (int i = 0; i < rank; i++) printColor("^", 14);
    cout << "\n";

    printColor("                    Col(A)(" + intToStr(rank) + "d)", 14);
    printColor("  <- only reachable b's!\n\n", 8);
}

/* =========================================
   GAUSSIAN ELIMINATION
   ========================================= */
int gaussElim(Matrix& M, bool verbose) {
    int rows = (int)M.size();
    int cols = (int)M[0].size();
    int pivotRow = 0, rank = 0;

    for (int col = 0; col < cols && pivotRow < rows; col++) {
        int    maxRow = -1;
        double maxVal = 1e-9;
        for (int r = pivotRow; r < rows; r++) {
            if (fabs(M[r][col]) > maxVal) {
                maxVal = fabs(M[r][col]);
                maxRow = r;
            }
        }
        if (maxRow == -1) continue;

        if (maxRow != pivotRow) {
            swap(M[maxRow], M[pivotRow]);
            if (verbose) {
                printColor("  Swap R" + intToStr(pivotRow+1) +
                           " <-> R" + intToStr(maxRow+1) + "\n", 11);
                printMatrix(M);
            }
        }

        double piv = M[pivotRow][col];
        for (int j = 0; j < cols; j++) M[pivotRow][j] /= piv;
        if (verbose && fabs(piv - 1.0) > 1e-9) {
            printColor("  R" + intToStr(pivotRow+1) +
                       " /= " + dblToStr(piv, 4) + "\n", 11);
            printMatrix(M);
        }

        for (int r = 0; r < rows; r++) {
            if (r == pivotRow || fabs(M[r][col]) < 1e-9) continue;
            double f = M[r][col];
            for (int j = 0; j < cols; j++) M[r][j] -= f * M[pivotRow][j];
            if (verbose) {
                string sign = (f > 0) ? "-" : "+";
                printColor("  R" + intToStr(r+1) + " " + sign + "= " +
                           dblToStr(fabs(f), 4) + " * R" +
                           intToStr(pivotRow+1) + "\n", 11);
                printMatrix(M);
            }
        }
        pivotRow++;
        rank++;
    }
    return rank;
}

/* =========================================
   MODULE 1: ROW REDUCTION
   ========================================= */
void moduleRowReduction() {
    clearScreen();
    printColor("\n  === ROW REDUCTION - Step by Step ===\n\n", 14);
    printColor("  CONCEPT:\n", 10);
    printColor("  Row reduction transforms A into RREF using 3 ops:\n", 7);
    printColor("  [1] Swap two rows\n", 11);
    printColor("  [2] Scale a row by nonzero scalar\n", 11);
    printColor("  [3] Add a multiple of one row to another\n\n", 11);

    int rows, cols;
    printColor("  Enter matrix size (rows cols): ", 15);
    cin >> rows >> cols;

    Matrix M = makeMatrix(rows, cols);
    printColor("  Enter values row by row:\n", 7);
    for (int i = 0; i < rows; i++) {
        printColor("  Row " + intToStr(i+1) + ": ", 11);
        for (int j = 0; j < cols; j++) cin >> M[i][j];
    }

    cout << "\n";
    printColor("  -- Original Matrix --\n", 8);
    printMatrix(M, "A");
    matrixHeatmap(M);

    printColor("  -- Step by Step RREF --\n\n", 14);
    int rank = gaussElim(M, true);

    printColor("  -- Final RREF --\n", 10);
    printMatrix(M, "RREF(A)");

    printColor("  Rank    = ", 7); printColor(intToStr(rank) + "\n", 10);
    printColor("  Nullity = ", 7); printColor(intToStr(cols - rank) + "\n", 11);
    printColor("  Check   : rank + nullity = ", 8);
    printColor(intToStr(rank) + " + " + intToStr(cols-rank) +
               " = " + intToStr(cols) + " (= cols)\n", 8);

    drawSubspaceVisual(rank, cols - rank, cols);
    pauseKey();
}

/* =========================================
   MODULE 2: VECTOR OPERATIONS
   ========================================= */
void moduleVectors() {
    clearScreen();
    printColor("\n  === VECTOR OPERATIONS + VISUALIZER ===\n\n", 14);
    printColor("  How many 2D vectors? (max 4): ", 15);
    int n; cin >> n;
    if (n > 4) n = 4;

    VecList      vecs(n);
    vector<string> labels(n);
    for (int i = 0; i < n; i++) {
        printColor("  v" + intToStr(i+1) + " (x y): ", 11);
        cin >> vecs[i].first >> vecs[i].second;
        labels[i] = "v" + intToStr(i+1) + " = (" +
                    dblToStr(vecs[i].first, 3) + ", " +
                    dblToStr(vecs[i].second, 3) + ")";
    }

    clearScreen();
    plotVectors2D(vecs, labels);

    printColor("  -- Properties --\n\n", 14);
    for (int i = 0; i < n; i++) {
        double mag   = sqrt(vecs[i].first*vecs[i].first +
                            vecs[i].second*vecs[i].second);
        double angle = atan2(vecs[i].second, vecs[i].first) * 180.0 / 3.14159265;
        double nx = (mag > 1e-9) ? vecs[i].first  / mag : 0.0;
        double ny = (mag > 1e-9) ? vecs[i].second / mag : 0.0;

        printColor("  v" + intToStr(i+1) + ":\n", 11);
        printColor("    |v| = ", 7);    printColor(dblToStr(mag,   5) + "\n", 15);
        printColor("    angle = ", 7);  printColor(dblToStr(angle, 4) + " deg\n", 15);
        printColor("    unit = ", 7);
        printColor("(" + dblToStr(nx,4) + ", " + dblToStr(ny,4) + ")\n\n", 15);
    }

    if (n >= 2) {
        printColor("  -- Dot Products --\n\n", 14);
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                double dot = vecs[i].first  * vecs[j].first +
                             vecs[i].second * vecs[j].second;
                double mi  = sqrt(vecs[i].first*vecs[i].first +
                                  vecs[i].second*vecs[i].second);
                double mj  = sqrt(vecs[j].first*vecs[j].first +
                                  vecs[j].second*vecs[j].second);
                double cosA = (mi*mj > 1e-9) ? dot/(mi*mj) : 0.0;
                if (cosA >  1.0) cosA =  1.0;
                if (cosA < -1.0) cosA = -1.0;
                double angle = acos(cosA) * 180.0 / 3.14159265;

                printColor("  v" + intToStr(i+1) + " . v" + intToStr(j+1) + " = ", 7);
                printColor(dblToStr(dot, 5), 15);
                printColor("  |  angle = ", 7);
                printColor(dblToStr(angle, 4) + " deg", 14);
                if (fabs(dot) < 1e-6) printColor("  [ORTHOGONAL!]", 10);
                cout << "\n";
            }
        }
        cout << "\n";

        double sx = 0.0, sy = 0.0;
        for (int i = 0; i < n; i++) { sx += vecs[i].first; sy += vecs[i].second; }
        vecs.push_back(make_pair(sx, sy));
        labels.push_back("SUM = (" + dblToStr(sx,3) + ", " + dblToStr(sy,3) + ")");
        printColor("  -- With Sum Vector Added --\n", 14);
        plotVectors2D(vecs, labels);
    }
    pauseKey();
}

/* =========================================
   MODULE 3: CONCEPT CARDS
   ========================================= */
struct Concept {
    string         name;
    string         def;
    vector<string> steps;
    string         visual;
    string         example;
};

void printConceptCard(const Concept& c) {
    clearScreen();
    cout << "\n";
    drawBorder(62);
    drawTitled("CONCEPT: " + c.name, 62);
    drawBorder(62);
    cout << "\n";

    printColor("  DEFINITION:\n", 14);
    printColor("  " + c.def + "\n\n", 7);

    printColor("  KEY IDEAS:\n", 10);
    for (int i = 0; i < (int)c.steps.size(); i++) {
        printColor("  [" + intToStr(i+1) + "] ", 11);
        printColor(c.steps[i] + "\n", 7);
    }

    if (!c.visual.empty()) {
        cout << "\n";
        printColor("  VISUAL:\n", 14);
        printColor(c.visual, 11);
    }

    if (!c.example.empty()) {
        cout << "\n";
        printColor("  EXAMPLE:\n", 14);
        printColor("  " + c.example + "\n", 15);
    }
}

void moduleConcepts() {
    /* Build concepts without brace-init lists for C++98 safety */
    vector<Concept> concepts;
    Concept c;

    /* 1 - Column Space */
    c.name    = "Column Space";
    c.def     = "Col(A) = all vectors b reachable as Ax. Spanned by columns of A.";
    c.steps.clear();
    c.steps.push_back("Col(A) = {x1*c1 + x2*c2 + ... : xi in R}");
    c.steps.push_back("Col(A) is a subspace of R^m");
    c.steps.push_back("dim(Col(A)) = rank(A)");
    c.steps.push_back("b reachable <=> b in Col(A) <=> Ax=b has a solution");
    c.visual  = "  Columns c1,c2 of A span a subspace:\n"
                "  all combos a*c1 + b*c2 fill a plane in R^m\n";
    c.example = "A=[[1,0],[2,1]] -> Col(A) is all of R^2";
    concepts.push_back(c);

    /* 2 - Null Space */
    c.name    = "Null Space";
    c.def     = "Null(A) = {x : Ax = 0}. All inputs A kills. Always contains 0.";
    c.steps.clear();
    c.steps.push_back("Row reduce [A|0] to find null space");
    c.steps.push_back("Free variables -> null space basis vectors");
    c.steps.push_back("dim(Null(A)) = nullity = n - rank(A)");
    c.steps.push_back("Null(A) = {0} means columns are independent");
    c.visual  = "  Ax = 0\n"
                "  [1 2][x1] = [0]  =>  x1 = -2t\n"
                "  [2 4][x2]   [0]      x2 =  t\n"
                "  Null(A) = span{[-2, 1]^T}\n";
    c.example = "A=[[1,2],[2,4]]: rank=1, nullity=1, Null=span(-2,1)";
    concepts.push_back(c);

    /* 3 - Left Null Space */
    c.name    = "Left Null Space";
    c.def     = "Null(A^T) = {y : A^T y = 0}. Orthogonal complement of Col(A).";
    c.steps.clear();
    c.steps.push_back("Find y such that A^T * y = 0");
    c.steps.push_back("y . (Ax) = (A^T y) . x = 0 for ALL x");
    c.steps.push_back("y is perpendicular to every vector in Col(A)");
    c.steps.push_back("y defines hyperplane {b: y.b=0} that contains Col(A)");
    c.steps.push_back("R^m = Col(A) + Left Null Space (orthogonal decomp)");
    c.visual  = "         y (left null vector)\n"
                "          ^\n"
                "          |  <- NORMAL to Col(A) plane\n"
                "  ........+..........\n"
                "  .   Col(A) plane  .\n"
                "  ...................\n";
    c.example = "A=[[1,0],[0,0]]: Col=x-axis, Left Null=y-axis";
    concepts.push_back(c);

    /* 4 - Rank-Nullity */
    c.name    = "Rank-Nullity Theorem";
    c.def     = "rank(A) + nullity(A) = n  (number of columns). Always.";
    c.steps.clear();
    c.steps.push_back("rank    = number of pivot columns = dim(Col(A))");
    c.steps.push_back("nullity = number of free variables = dim(Null(A))");
    c.steps.push_back("pivots + free vars = total variables = n");
    c.steps.push_back("rank = n  =>  only solution to Ax=0 is x=0");
    c.visual  = "  n columns:\n"
                "  [====|~~~]\n"
                "   rank  null\n"
                "  <----n---->\n";
    c.example = "3x5 matrix, rank=2: nullity=3 because 5-2=3";
    concepts.push_back(c);

    /* 5 - Eigenvalues */
    c.name    = "Eigenvalues & Eigenvectors";
    c.def     = "Av = lambda*v: A only scales v, no rotation. v is eigenvector.";
    c.steps.clear();
    c.steps.push_back("Solve det(A - lambda*I) = 0 for eigenvalues");
    c.steps.push_back("For each lambda, solve (A - lambda*I)v = 0");
    c.steps.push_back("Trace(A) = sum of eigenvalues");
    c.steps.push_back("Det(A)   = product of eigenvalues");
    c.steps.push_back("A = P*D*P^-1  if A is diagonalizable");
    c.visual  = "  Normal:      Av = (rotated + scaled)\n"
                "  Eigenvector: Av = lambda * v\n"
                "                    ^\n"
                "               same direction! just scaled.\n";
    c.example = "A=[[2,0],[0,3]]: eigenvalues 2,3  eigenvecs [1,0],[0,1]";
    concepts.push_back(c);

    /* 6 - Big-O */
    c.name    = "Big-O Notation";
    c.def     = "Describes how runtime GROWS with input n. Upper bound.";
    c.steps.clear();
    c.steps.push_back("O(1)      - constant:   array index, hash lookup");
    c.steps.push_back("O(log n)  - log:        binary search");
    c.steps.push_back("O(n)      - linear:     single loop");
    c.steps.push_back("O(n logn) - linearithm: merge sort, heap sort");
    c.steps.push_back("O(n^2)    - quadratic:  nested loops, bubble sort");
    c.steps.push_back("O(2^n)    - exponential: brute force subsets");
    c.visual  = "  O(1) < O(logn) < O(n) < O(nlogn) < O(n^2) < O(2^n)\n\n"
                "  n=1000:\n"
                "  O(1)=1  O(log)~10  O(n)=1000  O(n^2)=1,000,000\n";
    c.example = "Binary search 1M items: ~20 steps. Linear scan: 1M steps.";
    concepts.push_back(c);

    /* 7 - BFS/DFS */
    c.name    = "Graph Traversals BFS/DFS";
    c.def     = "BFS: level-by-level (queue). DFS: deep first (stack/recursion).";
    c.steps.clear();
    c.steps.push_back("BFS uses Queue (FIFO) -> shortest path unweighted graph");
    c.steps.push_back("DFS uses Stack/recursion -> cycle detection, topo sort");
    c.steps.push_back("Both run in O(V + E) time");
    c.steps.push_back("BFS space: O(V),  DFS space: O(V) worst case");
    c.visual  = "  Graph:  A-B-D\n"
                "          |   |\n"
                "          C---E\n\n"
                "  BFS from A: A B C D E  (level by level)\n"
                "  DFS from A: A B D E C  (deep first)\n";
    c.example = "Shortest path -> BFS.   Maze/cycle detection -> DFS.";
    concepts.push_back(c);

    /* 8 - DP */
    c.name    = "Dynamic Programming";
    c.def     = "Store subproblem results to avoid recomputing. Memoization.";
    c.steps.clear();
    c.steps.push_back("Identify overlapping subproblems");
    c.steps.push_back("Write recurrence relation");
    c.steps.push_back("Memoize (top-down) or fill table (bottom-up)");
    c.steps.push_back("Fibonacci: O(2^n) naive -> O(n) with DP");
    c.steps.push_back("DP = recursion + caching");
    c.visual  = "  fib(5) naive:          fib(5) with memo:\n"
                "    fib(4)  fib(3)          compute each once\n"
                "    fib(3)  fib(2)          store in table\n"
                "    fib(2)  fib(2)  <--  O(n) not O(2^n)!\n";
    c.example = "Fibonacci, Longest Common Subsequence, 0/1 Knapsack";
    concepts.push_back(c);

    while (true) {
        clearScreen();
        printColor("\n  === CONCEPT EXPLAINER ===\n\n", 14);
        for (int i = 0; i < (int)concepts.size(); i++) {
            printColor("  [" + intToStr(i+1) + "] ", 11);
            printColor(concepts[i].name + "\n", 7);
        }
        printColor("  [0] Back\n\n  > ", 8);

        int ch; cin >> ch;
        if (ch == 0) break;
        if (ch < 1 || ch > (int)concepts.size()) continue;
        printConceptCard(concepts[ch - 1]);
        pauseKey();
    }
}

/* =========================================
   MODULE 4: QUIZ MODE
   ========================================= */
struct Question {
    string         q;
    vector<string> opts;
    int            ans;
    string         expl;
};

void moduleQuiz() {
    vector<Question> pool;
    Question q;

    q.q = "rank(A) + nullity(A) = ?";
    q.opts.clear(); q.opts.push_back("# rows"); q.opts.push_back("# columns");
    q.opts.push_back("determinant"); q.opts.push_back("trace");
    q.ans = 1; q.expl = "Rank-Nullity: rank + nullity = n (number of columns).";
    pool.push_back(q);

    q.q = "Ax=b has no solution means:";
    q.opts.clear(); q.opts.push_back("b in Col(A)"); q.opts.push_back("b NOT in Col(A)");
    q.opts.push_back("A is invertible"); q.opts.push_back("rank=0");
    q.ans = 1; q.expl = "Ax=b solvable iff b is in the column space of A.";
    pool.push_back(q);

    q.q = "Left null space of A is Null(...):";
    q.opts.clear(); q.opts.push_back("A"); q.opts.push_back("A^(-1)");
    q.opts.push_back("A^T"); q.opts.push_back("A^2");
    q.ans = 2; q.expl = "Left null = {y: A^T y = 0} = Null(A^T).";
    pool.push_back(q);

    q.q = "Which sorting has O(n log n) average?";
    q.opts.clear(); q.opts.push_back("Bubble Sort"); q.opts.push_back("Insertion Sort");
    q.opts.push_back("Merge Sort"); q.opts.push_back("Selection Sort");
    q.ans = 2; q.expl = "Merge Sort: T(n)=2T(n/2)+O(n) => O(n log n).";
    pool.push_back(q);

    q.q = "Eigenvectors satisfy:";
    q.opts.clear(); q.opts.push_back("Av=0"); q.opts.push_back("Av=v");
    q.opts.push_back("Av=lambda*v"); q.opts.push_back("A^T v=v");
    q.ans = 2; q.expl = "Definition: Av = lambda*v for some scalar lambda.";
    pool.push_back(q);

    q.q = "BFS uses which data structure?";
    q.opts.clear(); q.opts.push_back("Stack"); q.opts.push_back("Queue");
    q.opts.push_back("Heap"); q.opts.push_back("Set");
    q.ans = 1; q.expl = "BFS uses a Queue (FIFO) to explore level by level.";
    pool.push_back(q);

    q.q = "det(A)=0 implies:";
    q.opts.clear(); q.opts.push_back("A invertible"); q.opts.push_back("unique solution");
    q.opts.push_back("cols linearly dependent"); q.opts.push_back("Null={0}");
    q.ans = 2; q.expl = "det=0 means columns are linearly dependent, A is singular.";
    pool.push_back(q);

    q.q = "Nullity of 3x5 matrix with rank 2:";
    q.opts.clear(); q.opts.push_back("2"); q.opts.push_back("3");
    q.opts.push_back("5"); q.opts.push_back("1");
    q.ans = 1; q.expl = "nullity = n - rank = 5 - 2 = 3.";
    pool.push_back(q);

    q.q = "Memoization in DP means:";
    q.opts.clear(); q.opts.push_back("Sorting results"); q.opts.push_back("Caching subproblem results");
    q.opts.push_back("Using recursion only"); q.opts.push_back("Greedy approach");
    q.ans = 1; q.expl = "Memoization = storing computed results to avoid recomputation.";
    pool.push_back(q);

    q.q = "Which recurrence describes Merge Sort?";
    q.opts.clear(); q.opts.push_back("T(n)=T(n-1)+O(1)"); q.opts.push_back("T(n)=2T(n/2)+O(n)");
    q.opts.push_back("T(n)=T(n/2)+O(1)"); q.opts.push_back("T(n)=n*T(n-1)");
    q.ans = 1; q.expl = "Merge sort splits in half and merges in O(n).";
    pool.push_back(q);

    srand((unsigned int)time(0));
    for (int i = (int)pool.size()-1; i > 0; i--) {
        int j = rand() % (i + 1);
        swap(pool[i], pool[j]);
    }

    int total = (int)pool.size();
    if (total > 7) total = 7;
    int score = 0;

    for (int qi = 0; qi < total; qi++) {
        clearScreen();
        printColor("\n  === QUIZ [" + intToStr(qi+1) + "/" + intToStr(total) +
                   "]  Score: " + intToStr(score) + "/" + intToStr(qi) + " ===\n\n", 14);

        Question& Q = pool[qi];
        printColor("  Q: " + Q.q + "\n\n", 15);
        for (int i = 0; i < (int)Q.opts.size(); i++) {
            printColor("  [" + string(1, (char)('A'+i)) + "] ", 11);
            printColor(Q.opts[i] + "\n", 7);
        }
        cout << "\n";
        printColor("  Answer (A/B/C/D): ", 15);
        char ans; cin >> ans;
        int idx = (int)(toupper(ans) - 'A');

        if (idx == Q.ans) {
            printColor("\n  CORRECT!\n", 10);
            score++;
        } else {
            printColor("\n  Wrong. Correct: ", 12);
            printColor(string(1, (char)('A' + Q.ans)) + "\n", 14);
        }
        printColor("  " + Q.expl + "\n", 8);
        pauseKey();
    }

    clearScreen();
    cout << "\n\n";
    drawBorder(60);
    drawTitled("QUIZ COMPLETE!", 60);
    drawLine(60);
    int pct = score * 100 / total;
    drawTitled("Score: " + intToStr(score) + "/" + intToStr(total) +
               "  (" + intToStr(pct) + "%)", 60);
    drawLine(60);
    string msg;
    if      (pct == 100) msg = "PERFECT! Outstanding!";
    else if (pct >=  70) msg = "Great job! Keep it up!";
    else if (pct >=  40) msg = "Keep practising!";
    else                  msg = "Review the concept cards!";
    drawTitled(msg, 60);
    drawBorder(60);
    cout << "\n  [";
    int filled = pct * 40 / 100;
    for (int i = 0; i < 40; i++) {
        if (i < filled) printColor("=", pct >= 70 ? 10 : 14);
        else             printColor("-", 8);
    }
    printColor("] " + intToStr(pct) + "%\n\n", 7);
    pauseKey();
}

/* =========================================
   MODULE 5: DETERMINANT
   ========================================= */
double calcDet(Matrix M) {
    int    n     = (int)M.size();
    double det   = 1.0;
    int    swaps = 0;
    for (int col = 0; col < n; col++) {
        int mx = col;
        for (int r = col+1; r < n; r++)
            if (fabs(M[r][col]) > fabs(M[mx][col])) mx = r;
        if (mx != col) { swap(M[mx], M[col]); swaps++; }
        if (fabs(M[col][col]) < 1e-12) return 0.0;
        det *= M[col][col];
        for (int r = col+1; r < n; r++) {
            double f = M[r][col] / M[col][col];
            for (int j = col; j < n; j++) M[r][j] -= f * M[col][j];
        }
    }
    return (swaps % 2) ? -det : det;
}

void moduleDeterminant() {
    clearScreen();
    printColor("\n  === DETERMINANT CALCULATOR ===\n\n", 14);
    printColor("  det(A) tells you:\n", 10);
    printColor("  -> Area/volume scaling factor of the transformation\n", 7);
    printColor("  -> det=0  : singular, not invertible\n", 7);
    printColor("  -> det<0  : orientation flipped\n\n", 7);

    int n;
    printColor("  Size of square matrix n: ", 15);
    cin >> n;
    Matrix M = makeMatrix(n, n);
    printColor("  Enter values:\n", 7);
    for (int i = 0; i < n; i++) {
        printColor("  Row " + intToStr(i+1) + ": ", 11);
        for (int j = 0; j < n; j++) cin >> M[i][j];
    }

    printMatrix(M, "A");
    matrixHeatmap(M);

    double det = calcDet(M);
    if (fabs(det) < 1e-9) det = 0.0;

    printColor("  det(A) = ", 7);
    setColor(fabs(det) < 1e-6 ? 12 : 10);
    cout << fixed << setprecision(4) << det << "\n\n";
    resetColor();

    if (fabs(det) < 1e-6) {
        printColor("  [SINGULAR]   Not invertible. Columns are dependent.\n", 12);
        printColor("  Ax=b may have no solution or infinitely many.\n\n", 12);
    } else {
        printColor("  [INVERTIBLE] Unique solution exists for any b.\n", 10);
        printColor("  Volume scaling factor: |det| = " +
                   dblToStr(fabs(det), 5) + "\n\n", 10);
    }
    pauseKey();
}

/* =========================================
   MODULE 6: LINEAR INDEPENDENCE
   ========================================= */
void moduleLinearIndep() {
    clearScreen();
    printColor("\n  === LINEAR INDEPENDENCE CHECKER ===\n\n", 14);
    printColor("  Vectors v1..vk are linearly independent if\n", 7);
    printColor("  the ONLY solution to c1*v1+...+ck*vk=0 is all ci=0.\n\n", 7);

    int n, k;
    printColor("  Vector dimension n: ", 15); cin >> n;
    printColor("  Number of vectors k: ", 15); cin >> k;

    Matrix M = makeMatrix(n, k);
    for (int j = 0; j < k; j++) {
        printColor("  v" + intToStr(j+1) + " (" + intToStr(n) + " values): ", 11);
        for (int i = 0; i < n; i++) cin >> M[i][j];
    }

    cout << "\n";
    printColor("  Vectors as columns:\n", 7);
    printMatrix(M, "V");

    Matrix copy = M;
    int rank = gaussElim(copy, false);

    cout << "\n";
    printColor("  Rank = " + intToStr(rank) + " out of " + intToStr(k) + " vectors\n\n", 15);

    if (rank == k) {
        printColor("  LINEARLY INDEPENDENT!\n", 10);
        printColor("  All " + intToStr(k) + " vectors are independent.\n\n", 10);
    } else {
        int dep = k - rank;
        printColor("  LINEARLY DEPENDENT!\n", 12);
        printColor("  " + intToStr(dep) + " vector(s) expressible as combo of others.\n\n", 12);
    }

    /* Visual bar */
    printColor("  [", 7);
    for (int i = 0; i < k; i++) {
        if (i < rank) printColor("v" + intToStr(i+1) + " ", 10);
        else          printColor("v" + intToStr(i+1) + " ", 12);
    }
    printColor("]\n", 7);
    printColor("   ", 7);
    for (int i = 0; i < k; i++) {
        if (i < rank) printColor("ok  ", 10);
        else          printColor("dep ", 12);
    }
    cout << "\n\n";
    pauseKey();
}

/* =========================================
   MAIN MENU
   ========================================= */
void mainMenu() {
    while (true) {
        clearScreen();
        cout << "\n";
        printColor("  +==============================================+\n", 11);
        printColor("  |       STUDY COMPANION  v1.1                 |\n", 11);
        printColor("  |    Linear Algebra  &  Computer Science      |\n", 11);
        printColor("  +==============================================+\n\n", 11);

        printColor("  [1] ", 14); printColor("Row Reduction       ", 15); printColor("RREF step-by-step + subspace diagram\n", 8);
        printColor("  [2] ", 14); printColor("Vector Operations   ", 15); printColor("2D plot, dot product, angles, sum\n", 8);
        printColor("  [3] ", 14); printColor("Concept Cards       ", 15); printColor("ColSpace, NullSpace, Big-O, Graphs...\n", 8);
        printColor("  [4] ", 14); printColor("Quiz Mode           ", 15); printColor("7 random questions with feedback\n", 8);
        printColor("  [5] ", 14); printColor("Determinant         ", 15); printColor("Calculate + meaning + heatmap\n", 8);
        printColor("  [6] ", 14); printColor("Linear Independence ", 15); printColor("Check if vectors are independent\n", 8);
        printColor("\n  [0] ", 8); printColor("Exit\n\n", 8);
        printColor("  Choose: ", 15);

        int ch; cin >> ch;
        switch (ch) {
            case 1: moduleRowReduction(); break;
            case 2: moduleVectors();      break;
            case 3: moduleConcepts();     break;
            case 4: moduleQuiz();         break;
            case 5: moduleDeterminant();  break;
            case 6: moduleLinearIndep();  break;
            case 0:
                clearScreen();
                printColor("\n  Study hard. Good luck!\n\n", 11);
                return;
            default:
                printColor("  Invalid choice.\n", 12);
                Sleep(500);
        }
    }
}

/* =========================================
   MAIN
   ========================================= */
int main() {
    setupConsole();
    showSplash();
    mainMenu();
    return 0;
}
