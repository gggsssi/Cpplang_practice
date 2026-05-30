/*
==========================================================
   STUDY COMPANION v1.0
   Linear Algebra & Computer Science - Offline Edition

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

// ─────────────────────────────────────────
//  WINDOWS COLOR SYSTEM
// ─────────────────────────────────────────
HANDLE hConsole;

void setColor(int fg, int bg = 0) {
    SetConsoleTextAttribute(hConsole, (bg << 4) | fg);
}
void resetColor() { setColor(7); }

void printColor(const string& s, int fg, int bg = 0) {
    setColor(fg, bg);
    cout << s;
    resetColor();
}

// ─────────────────────────────────────────
//  CONSOLE SETUP
// ─────────────────────────────────────────
void setupConsole() {
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleOutputCP(CP_UTF8);
    system("mode con: cols=100 lines=50");
}

void clearScreen() { system("cls"); }

void hideCursor() {
    CONSOLE_CURSOR_INFO info = {1, FALSE};
    SetConsoleCursorInfo(hConsole, &info);
}
void showCursor() {
    CONSOLE_CURSOR_INFO info = {1, TRUE};
    SetConsoleCursorInfo(hConsole, &info);
}

void pauseKey() {
    printColor("\n  [Press any key to continue]", 8);
    _getch();
}

// ─────────────────────────────────────────
//  MATRIX TYPE
// ─────────────────────────────────────────
typedef vector<vector<double>> Matrix;

Matrix makeMatrix(int r, int c, double val = 0) {
    return Matrix(r, vector<double>(c, val));
}

// ─────────────────────────────────────────
//  BORDER HELPERS
// ─────────────────────────────────────────
void drawBorder(int w = 60) {
    printColor("  +", 11);
    printColor(string(w - 4, '-'), 11);
    printColor("+\n", 11);
}

void drawTitled(const string& title, int w = 60) {
    int pad = (w - 4 - (int)title.size()) / 2;
    if (pad < 0) pad = 0;
    printColor("  |", 11);
    cout << string(pad, ' ');
    printColor(title, 14);
    cout << string(w - 4 - pad - (int)title.size(), ' ');
    printColor("|\n", 11);
}

void drawLine(int w = 60) {
    printColor("  |", 11);
    cout << string(w - 4, ' ');
    printColor("|\n", 11);
}

// ─────────────────────────────────────────
//  SPLASH SCREEN
// ─────────────────────────────────────────
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
    printColor("                           |___/  \n", 9);
    cout << "\n";
    printColor("       C O M P A N I O N  -  Offline Study Tool\n", 14);
    printColor("       Linear Algebra  &  Computer Science\n\n", 8);
    drawBorder();
    drawTitled("v1.0  |  No internet needed  |  100% Offline");
    drawBorder();
    cout << "\n";
    printColor("  Loading", 8);
    for (int i = 0; i < 5; i++) { Sleep(200); printColor(".", 10); }
    cout << "\n";
    Sleep(400);
    showCursor();
}

// ─────────────────────────────────────────
//  PRINT MATRIX
// ─────────────────────────────────────────
void printMatrix(const Matrix& M, const string& name = "") {
    int rows = M.size(), cols = M[0].size();
    if (!name.empty()) printColor("  " + name + " =\n", 14);
    for (int i = 0; i < rows; i++) {
        printColor("  [ ", 11);
        for (int j = 0; j < cols; j++) {
            double v = M[i][j];
            if (fabs(v) < 1e-9) v = 0;
            setColor(15);
            cout << setw(8) << fixed << setprecision(3) << v;
            resetColor();
            if (j < cols-1) cout << "  ";
        }
        printColor("  ]\n", 11);
    }
    cout << "\n";
}

// ─────────────────────────────────────────
//  VISUALIZER: 2D VECTOR PLOT
// ─────────────────────────────────────────
void plotVectors2D(vector<pair<double,double>> vecs, vector<string> labels) {
    const int W = 41, H = 21;
    const int cx = W/2, cy = H/2;
    vector<string> grid(H, string(W, ' '));
    vector<vector<int>> colorGrid(H, vector<int>(W, 7));

    // Axes
    for (int i = 0; i < W; i++) { grid[cy][i] = '-'; colorGrid[cy][i] = 8; }
    for (int i = 0; i < H; i++) { grid[i][cx] = '|'; colorGrid[i][cx] = 8; }
    grid[cy][cx] = '+'; colorGrid[cy][cx] = 8;

    // Scale
    double maxv = 1.0;
    for (auto& v : vecs) maxv = max(maxv, max(fabs(v.first), fabs(v.second)));
    double scaleX = (cx - 2) / maxv;
    double scaleY = (cy - 1) / maxv;

    // Draw vectors
    int vecColors[] = {10, 11, 14, 13, 12};
    char syms[] = {'>', '^', '#', '~', '@'};

    for (int vi = 0; vi < (int)vecs.size(); vi++) {
        int steps = 50;
        for (int s = 1; s <= steps; s++) {
            double t = (double)s / steps;
            int gx = cx + (int)(vecs[vi].first * scaleX * t);
            int gy = cy - (int)(vecs[vi].second * scaleY * t);
            if (gx >= 0 && gx < W && gy >= 0 && gy < H) {
                grid[gy][gx] = syms[vi % 5];
                colorGrid[gy][gx] = vecColors[vi % 5];
            }
        }
        // tip
        int gx = cx + (int)(vecs[vi].first * scaleX);
        int gy = cy - (int)(vecs[vi].second * scaleY);
        if (gx >= 0 && gx < W && gy >= 0 && gy < H) {
            grid[gy][gx] = '*';
            colorGrid[gy][gx] = 12;
        }
    }

    cout << "\n";
    printColor("    2D Vector Space Visualizer\n", 14);
    printColor("    " + string(W+2, '-') + "\n", 8);
    for (int i = 0; i < H; i++) {
        printColor("    |", 8);
        for (int j = 0; j < W; j++) {
            setColor(colorGrid[i][j]);
            cout << grid[i][j];
        }
        resetColor();
        printColor("|\n", 8);
    }
    printColor("    " + string(W+2, '-') + "\n\n", 8);

    for (int i = 0; i < (int)labels.size(); i++) {
        printColor("    [" + string(1, syms[i%5]) + "] ", vecColors[i%5]);
        printColor(labels[i] + "\n", 7);
    }
    cout << "\n";
}

// ─────────────────────────────────────────
//  VISUALIZER: MATRIX HEATMAP
// ─────────────────────────────────────────
void matrixHeatmap(const Matrix& M) {
    int rows = M.size(), cols = M[0].size();
    double maxv = 0;
    for (auto& r : M) for (auto& v : r) maxv = max(maxv, fabs(v));
    if (maxv == 0) maxv = 1;

    printColor("\n  Matrix Heatmap:\n\n", 14);
    for (int i = 0; i < rows; i++) {
        cout << "  ";
        for (int j = 0; j < cols; j++) {
            double ratio = fabs(M[i][j]) / maxv;
            int col;
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
    printColor("[##]High ", 12);
    printColor("[==]Med  ", 14);
    printColor("[--]Low  ", 10);
    printColor("[..]Tiny\n\n", 11);
}

// ─────────────────────────────────────────
//  VISUALIZER: SUBSPACE DIAGRAM
// ─────────────────────────────────────────
void drawSubspaceVisual(int rank, int nullDim, int totalCols) {
    printColor("\n  Fundamental Subspaces:\n\n", 14);

    // Input space bar
    printColor("  Input Space R^" + to_string(totalCols) + ":  [", 11);
    for (int i = 0; i < totalCols - nullDim; i++) printColor("=", 10);
    for (int i = 0; i < nullDim; i++) printColor("~", 8);
    printColor("]\n", 11);
    printColor("                   ", 7);
    for (int i = 0; i < totalCols - nullDim; i++) printColor("^", 10);
    for (int i = 0; i < nullDim; i++) printColor("^", 8);
    cout << "\n";
    printColor("                   ", 7);
    printColor("Row Space(" + to_string(totalCols-nullDim) + "d) ", 10);
    if (nullDim > 0) printColor("Null(" + to_string(nullDim) + "d)", 8);
    cout << "\n\n";

    printColor("                   A maps  vvv\n\n", 8);

    // Output space bar
    printColor("  Output Space:    [", 11);
    for (int i = 0; i < rank; i++) printColor("=", 14);
    printColor("   ]\n", 11);
    printColor("                    ", 7);
    for (int i = 0; i < rank; i++) printColor("^", 14);
    cout << "\n";
    printColor("                    Col(A)(" + to_string(rank) + "d)", 14);
    printColor("  <- only reachable b's!\n\n", 8);
}

// ─────────────────────────────────────────
//  GAUSSIAN ELIMINATION (step by step)
// ─────────────────────────────────────────
int gaussElim(Matrix& M, bool verbose = true) {
    int rows = M.size(), cols = M[0].size();
    int pivotRow = 0, rank = 0;

    for (int col = 0; col < cols && pivotRow < rows; col++) {
        int maxRow = -1; double maxVal = 1e-9;
        for (int r = pivotRow; r < rows; r++)
            if (fabs(M[r][col]) > maxVal) { maxVal = fabs(M[r][col]); maxRow = r; }
        if (maxRow == -1) continue;

        if (maxRow != pivotRow) {
            swap(M[maxRow], M[pivotRow]);
            if (verbose) {
                printColor("  Swap R" + to_string(pivotRow+1) + " <-> R" + to_string(maxRow+1) + "\n", 11);
                printMatrix(M);
            }
        }

        double piv = M[pivotRow][col];
        for (int j = 0; j < cols; j++) M[pivotRow][j] /= piv;
        if (verbose && fabs(piv-1.0) > 1e-9) {
            printColor("  R" + to_string(pivotRow+1) + " /= " + to_string(piv).substr(0,5) + "\n", 11);
            printMatrix(M);
        }

        for (int r = 0; r < rows; r++) {
            if (r == pivotRow || fabs(M[r][col]) < 1e-9) continue;
            double f = M[r][col];
            for (int j = 0; j < cols; j++) M[r][j] -= f * M[pivotRow][j];
            if (verbose) {
                string sign = f > 0 ? "-" : "+";
                printColor("  R" + to_string(r+1) + " " + sign + "= " +
                           to_string(fabs(f)).substr(0,5) + " * R" + to_string(pivotRow+1) + "\n", 11);
                printMatrix(M);
            }
        }
        pivotRow++; rank++;
    }
    return rank;
}

// ─────────────────────────────────────────
//  MODULE 1: ROW REDUCTION
// ─────────────────────────────────────────
void moduleRowReduction() {
    clearScreen();
    printColor("\n  === ROW REDUCTION - Step by Step ===\n\n", 14);

    printColor("  CONCEPT:\n", 10);
    printColor("  Row reduction transforms A into RREF using 3 operations:\n", 7);
    printColor("  [1] Swap two rows\n", 11);
    printColor("  [2] Scale a row by nonzero scalar\n", 11);
    printColor("  [3] Add multiple of one row to another\n\n", 11);

    int rows, cols;
    printColor("  Enter matrix size (rows cols): ", 15);
    cin >> rows >> cols;

    Matrix M = makeMatrix(rows, cols);
    printColor("  Enter values row by row:\n", 7);
    for (int i = 0; i < rows; i++) {
        printColor("  Row " + to_string(i+1) + ": ", 11);
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

    printColor("  Rank    = ", 7); printColor(to_string(rank) + "\n", 10);
    printColor("  Nullity = ", 7); printColor(to_string(cols-rank) + "\n", 11);
    printColor("  (rank + nullity = cols: ", 8);
    printColor(to_string(rank) + " + " + to_string(cols-rank) + " = " + to_string(cols) + ")\n", 8);

    drawSubspaceVisual(rank, cols-rank, cols);
    pauseKey();
}

// ─────────────────────────────────────────
//  MODULE 2: VECTOR OPERATIONS
// ─────────────────────────────────────────
void moduleVectors() {
    clearScreen();
    printColor("\n  === VECTOR OPERATIONS + VISUALIZER ===\n\n", 14);

    printColor("  How many 2D vectors? (max 4): ", 15);
    int n; cin >> n;
    if (n > 4) n = 4;

    vector<pair<double,double>> vecs(n);
    vector<string> labels(n);
    for (int i = 0; i < n; i++) {
        printColor("  v" + to_string(i+1) + " (x y): ", 11);
        cin >> vecs[i].first >> vecs[i].second;
        labels[i] = "v" + to_string(i+1) + " = (" +
            to_string(vecs[i].first).substr(0,5) + ", " +
            to_string(vecs[i].second).substr(0,5) + ")";
    }

    clearScreen();
    plotVectors2D(vecs, labels);

    printColor("  -- Properties --\n\n", 14);
    for (int i = 0; i < n; i++) {
        double mag = sqrt(vecs[i].first*vecs[i].first + vecs[i].second*vecs[i].second);
        double angle = atan2(vecs[i].second, vecs[i].first) * 180.0 / M_PI;
        printColor("  v" + to_string(i+1) + ":\n", 11);
        printColor("    |v| = ", 7); printColor(to_string(mag).substr(0,7) + "\n", 15);
        printColor("    angle = ", 7); printColor(to_string(angle).substr(0,6) + " deg\n", 15);
        double nx = vecs[i].first/mag, ny = vecs[i].second/mag;
        printColor("    unit = ", 7);
        printColor("(" + to_string(nx).substr(0,5) + ", " + to_string(ny).substr(0,5) + ")\n\n", 15);
    }

    if (n >= 2) {
        printColor("  -- Dot Products --\n\n", 14);
        for (int i = 0; i < n; i++) for (int j = i+1; j < n; j++) {
            double dot = vecs[i].first*vecs[j].first + vecs[i].second*vecs[j].second;
            double mi = sqrt(vecs[i].first*vecs[i].first + vecs[i].second*vecs[i].second);
            double mj = sqrt(vecs[j].first*vecs[j].first + vecs[j].second*vecs[j].second);
            double cosA = max(-1.0, min(1.0, dot/(mi*mj)));
            double angle = acos(cosA) * 180.0 / M_PI;
            printColor("  v" + to_string(i+1) + " . v" + to_string(j+1) + " = ", 7);
            printColor(to_string(dot).substr(0,7), 15);
            printColor("  |  angle = ", 7);
            printColor(to_string(angle).substr(0,6) + " deg", 14);
            if (fabs(dot) < 1e-6) printColor("  [ORTHOGONAL!]", 10);
            cout << "\n";
        }
        cout << "\n";
        double sx = 0, sy = 0;
        for (auto& v : vecs) { sx += v.first; sy += v.second; }
        vecs.push_back({sx, sy});
        labels.push_back("SUM = (" + to_string(sx).substr(0,5) + ", " + to_string(sy).substr(0,5) + ")");
        printColor("  -- Result with Sum Vector --\n", 14);
        plotVectors2D(vecs, labels);
    }
    pauseKey();
}

// ─────────────────────────────────────────
//  MODULE 3: CONCEPT CARDS
// ─────────────────────────────────────────
struct Concept {
    string name, def;
    vector<string> steps;
    string visual, example;
};

void printConceptCard(const Concept& c) {
    clearScreen();
    cout << "\n";
    drawBorder();
    drawTitled("CONCEPT: " + c.name);
    drawBorder();
    cout << "\n";

    printColor("  DEFINITION:\n", 14);
    printColor("  " + c.def + "\n\n", 7);

    printColor("  KEY IDEAS:\n", 10);
    for (int i = 0; i < (int)c.steps.size(); i++) {
        printColor("  [" + to_string(i+1) + "] ", 11);
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
    vector<Concept> concepts = {
        {"Column Space",
         "Col(A) = all vectors b reachable as Ax. Spanned by columns of A.",
         {"Col(A) = {x1*c1 + x2*c2 + ... : xi in R}",
          "Col(A) is a subspace of R^m",
          "dim(Col(A)) = rank(A)",
          "b reachable <=> b in Col(A) <=> Ax=b has solution"},
         "  Columns of A span a subspace:\n"
         "  c1=[1,2], c2=[0,1] -> Col(A) = all combos\n"
         "  [a*1+b*0, a*2+b*1] for any a,b in R\n",
         "A=[[1,0],[2,1]] -> Col(A) is a plane in R^2 (all of R^2)"},

        {"Null Space",
         "Null(A) = {x : Ax = 0}. All inputs A 'kills'. Always contains 0.",
         {"Row reduce [A|0] to find null space",
          "Free variables -> null space basis vectors",
          "dim(Null(A)) = nullity = n - rank(A)",
          "Null(A) = {0} means columns are independent"},
         "  Ax = 0\n"
         "  [1 2][x1] = [0]  =>  x1 = -2t\n"
         "  [2 4][x2]   [0]      x2 =  t\n"
         "  Null(A) = span{[-2, 1]^T}\n",
         "A=[[1,2],[2,4]]: rank=1, nullity=1, Null=span[-2,1]"},

        {"Left Null Space",
         "Null(A^T) = {y : A^T y = 0}. Orthogonal complement of Col(A).",
         {"Find y s.t. A^T * y = 0",
          "y . (Ax) = (A^T y) . x = 0 for ALL x",
          "y is perpendicular to every vector in Col(A)",
          "y defines hyperplane {b: y.b=0} containing Col(A)",
          "R^m = Col(A) + Left Null Space (orthogonal decomp)"},
         "         y (left null vector)\n"
         "          ^\n"
         "          |  <- NORMAL to Col(A) plane\n"
         "  ........+..........\n"
         "  .   Col(A) plane  .\n"
         "  ...................\n",
         "A=[[1,0],[0,0]]: Col=x-axis, Left Null=y-axis"},

        {"Rank-Nullity Theorem",
         "rank(A) + nullity(A) = n  (number of columns). Always.",
         {"rank = # pivot columns = dim(Col(A))",
          "nullity = # free variables = dim(Null(A))",
          "pivots + free vars = total variables = n",
          "rank=n: only solution to Ax=0 is x=0 (injective)"},
         "  n columns:\n"
         "  [====|~~~]\n"
         "   rank  null\n"
         "  <----n---->\n",
         "3x5 matrix, rank=2: nullity=3 (5-2=3)"},

        {"Eigenvalues & Eigenvectors",
         "Av = lambda*v: A only scales v, no rotation. v is eigenvector.",
         {"Solve det(A - lambda*I) = 0 for eigenvalues",
          "For each lambda, solve (A-lambda*I)v=0 for eigenvectors",
          "Trace(A) = sum of eigenvalues",
          "Det(A) = product of eigenvalues",
          "A = P*D*P^-1 if A is diagonalizable"},
         "  Normal:      Av = (rotated + scaled)\n"
         "  Eigenvector: Av = lambda * v\n"
         "                    ^\n"
         "               same direction! just scaled.\n",
         "A=[[2,0],[0,3]]: lambda=2,3  v=[1,0],[0,1]"},

        {"Big-O Notation",
         "Describes how runtime GROWS with input n. Upper bound.",
         {"O(1)     - constant: array index, hash lookup",
          "O(log n) - binary search, balanced BST",
          "O(n)     - single loop, linear scan",
          "O(n log n) - merge sort, heap sort",
          "O(n^2)   - nested loops, bubble sort",
          "O(2^n)   - brute force subsets"},
         "  O(1) < O(logn) < O(n) < O(nlogn) < O(n^2) < O(2^n)\n\n"
         "  n=1000:\n"
         "  O(1)=1  O(log)~10  O(n)=1000  O(n^2)=1,000,000\n",
         "Binary search 1M items: ~20 steps. Linear: 1M steps."},

        {"Graph Traversals (BFS/DFS)",
         "BFS: level-by-level (queue). DFS: deep first (stack/recursion).",
         {"BFS uses Queue (FIFO) -> shortest path in unweighted graph",
          "DFS uses Stack/recursion -> good for cycle detection, topological sort",
          "BFS time: O(V+E), space: O(V)",
          "DFS time: O(V+E), space: O(V) worst case",
          "BFS finds shortest path; DFS finds all paths"},
         "  Graph:  A-B-D\n"
         "          |   |\n"
         "          C---E\n\n"
         "  BFS from A: A B C D E  (level by level)\n"
         "  DFS from A: A B D E C  (deep first)\n",
         "Shortest path in a map -> BFS. Maze solution -> DFS."},

        {"Dynamic Programming",
         "Store subproblem results to avoid recomputing. Memoization.",
         {"Identify overlapping subproblems",
          "Define recurrence relation",
          "Memoize (top-down) or build table (bottom-up)",
          "Fibonacci: O(2^n) naive -> O(n) with DP!",
          "DP = recursion + caching"},
         "  fib(5) naive:         fib(5) with memo:\n"
         "    fib(4) fib(3)         compute each once\n"
         "    fib(3) fib(2)         store in table\n"
         "    fib(2) fib(2)  <---   O(n) not O(2^n)!\n",
         "Fibonacci, Longest Common Subseq, 0/1 Knapsack"}
    };

    while (true) {
        clearScreen();
        printColor("\n  === CONCEPT EXPLAINER ===\n\n", 14);
        for (int i = 0; i < (int)concepts.size(); i++) {
            printColor("  [" + to_string(i+1) + "] ", 11);
            printColor(concepts[i].name + "\n", 7);
        }
        printColor("  [0] Back\n\n  > ", 8);

        int ch; cin >> ch;
        if (ch == 0) break;
        if (ch < 1 || ch > (int)concepts.size()) continue;
        printConceptCard(concepts[ch-1]);
        pauseKey();
    }
}

// ─────────────────────────────────────────
//  MODULE 4: QUIZ MODE
// ─────────────────────────────────────────
struct Question {
    string q;
    vector<string> opts;
    int ans;
    string expl;
};

void moduleQuiz() {
    vector<Question> pool = {
        {"rank(A) + nullity(A) = ?",
         {"# rows", "# columns", "determinant", "trace"}, 1,
         "Rank-Nullity: rank + nullity = n (number of columns)."},
        {"Ax=b has no solution means:",
         {"b in Col(A)", "b NOT in Col(A)", "A is invertible", "rank=0"}, 1,
         "Ax=b solvable iff b is in the column space of A."},
        {"Left null space of A is Null(...):",
         {"A", "A^(-1)", "A^T", "A^2"}, 2,
         "Left null = {y: A^T y = 0} = Null(A^T)."},
        {"Which has O(n log n) average time?",
         {"Bubble Sort", "Insertion Sort", "Merge Sort", "Selection Sort"}, 2,
         "Merge Sort: T(n)=2T(n/2)+O(n) solves to O(n log n)."},
        {"Eigenvectors satisfy:",
         {"Av=0", "Av=v", "Av=lambda*v", "A^T v=v"}, 2,
         "Definition: Av = lambda*v for eigenvalue lambda."},
        {"BFS uses which structure?",
         {"Stack", "Queue", "Heap", "Set"}, 1,
         "BFS uses a Queue (FIFO) to explore level by level."},
        {"det(A)=0 implies:",
         {"A invertible", "unique solution", "cols linearly dependent", "Null={0}"}, 2,
         "det=0 means columns are linearly dependent, A is singular."},
        {"Nullity of a 3x5 matrix with rank 2:",
         {"2", "3", "5", "1"}, 1,
         "nullity = n - rank = 5 - 2 = 3."},
        {"Which recurrence is Merge Sort?",
         {"T(n)=T(n-1)+O(1)", "T(n)=2T(n/2)+O(n)", "T(n)=T(n/2)+O(1)", "T(n)=n*T(n-1)"}, 1,
         "Merge sort splits in half, merge costs O(n)."},
        {"In DP, memoization means:",
         {"Sorting results", "Caching subproblem results", "Using recursion only", "Greedy approach"}, 1,
         "Memoization = storing computed results to avoid recomputation."},
    };

    srand((unsigned)time(0));
    for (int i = pool.size()-1; i > 0; i--) swap(pool[i], pool[rand()%(i+1)]);
    int total = min((int)pool.size(), 7), score = 0;

    for (int qi = 0; qi < total; qi++) {
        clearScreen();
        printColor("\n  === QUIZ [" + to_string(qi+1) + "/" + to_string(total) +
                   "]  Score: " + to_string(score) + "/" + to_string(qi) + " ===\n\n", 14);

        auto& Q = pool[qi];
        printColor("  Q: " + Q.q + "\n\n", 15);
        for (int i = 0; i < (int)Q.opts.size(); i++) {
            printColor("  [" + string(1,'A'+i) + "] ", 11);
            printColor(Q.opts[i] + "\n", 7);
        }
        cout << "\n";
        printColor("  Answer (A/B/C/D): ", 15);
        char ans; cin >> ans;
        int idx = toupper(ans) - 'A';

        if (idx == Q.ans) {
            printColor("\n  CORRECT! ", 10);
            score++;
        } else {
            printColor("\n  Wrong. Answer: ", 12);
            printColor(string(1,'A'+Q.ans) + "\n", 14);
        }
        printColor("  " + Q.expl + "\n", 8);
        pauseKey();
    }

    clearScreen();
    cout << "\n\n";
    drawBorder();
    drawTitled("QUIZ COMPLETE!");
    drawLine();
    int pct = score * 100 / total;
    drawTitled("Score: " + to_string(score) + "/" + to_string(total) + "  (" + to_string(pct) + "%)");
    drawLine();
    string msg = pct==100 ? "PERFECT!" : pct>=70 ? "Great job!" : pct>=40 ? "Keep practicing!" : "Review the concepts!";
    drawTitled(msg);
    drawBorder();
    cout << "\n  [";
    int filled = pct * 40 / 100;
    for (int i = 0; i < 40; i++) {
        if (i < filled) printColor("=", pct>=70 ? 10 : 14);
        else printColor("-", 8);
    }
    printColor("] " + to_string(pct) + "%\n\n", 7);
    pauseKey();
}

// ─────────────────────────────────────────
//  MODULE 5: DETERMINANT
// ─────────────────────────────────────────
double calcDet(Matrix M) {
    int n = M.size(); double det = 1; int swaps = 0;
    for (int col = 0; col < n; col++) {
        int mx = col;
        for (int r = col+1; r < n; r++) if (fabs(M[r][col]) > fabs(M[mx][col])) mx = r;
        if (mx != col) { swap(M[mx], M[col]); swaps++; }
        if (fabs(M[col][col]) < 1e-12) return 0.0;
        det *= M[col][col];
        for (int r = col+1; r < n; r++) {
            double f = M[r][col] / M[col][col];
            for (int j = col; j < n; j++) M[r][j] -= f * M[col][j];
        }
    }
    return swaps%2 ? -det : det;
}

void moduleDeterminant() {
    clearScreen();
    printColor("\n  === DETERMINANT CALCULATOR ===\n\n", 14);
    printColor("  det(A) tells you:\n", 10);
    printColor("  -> Area/volume scaling factor of the transformation\n", 7);
    printColor("  -> det=0: singular (not invertible)\n", 7);
    printColor("  -> det<0: orientation flipped\n\n", 7);

    int n;
    printColor("  Size of square matrix (n): ", 15);
    cin >> n;
    Matrix M = makeMatrix(n, n);
    printColor("  Enter values:\n", 7);
    for (int i = 0; i < n; i++) {
        printColor("  Row " + to_string(i+1) + ": ", 11);
        for (int j = 0; j < n; j++) cin >> M[i][j];
    }

    printMatrix(M, "A");
    matrixHeatmap(M);

    double det = calcDet(M);
    if (fabs(det) < 1e-9) det = 0;

    printColor("  det(A) = ", 7);
    setColor(fabs(det) < 1e-6 ? 12 : 10);
    cout << fixed << setprecision(4) << det << "\n\n";
    resetColor();

    if (fabs(det) < 1e-6) {
        printColor("  [SINGULAR] Not invertible. Columns dependent.\n", 12);
        printColor("  Ax=b may have no solution or infinitely many.\n\n", 12);
    } else {
        printColor("  [INVERTIBLE] Unique solution for any b.\n", 10);
        printColor("  Volume scaling: |det| = " + to_string(fabs(det)).substr(0,7) + "\n\n", 10);
    }
    pauseKey();
}

// ─────────────────────────────────────────
//  MODULE 6: LINEAR INDEPENDENCE CHECKER
// ─────────────────────────────────────────
void moduleLinearIndep() {
    clearScreen();
    printColor("\n  === LINEAR INDEPENDENCE CHECKER ===\n\n", 14);
    printColor("  CONCEPT: Vectors v1..vk are linearly independent if\n", 7);
    printColor("  the ONLY solution to c1*v1+...+ck*vk=0 is all ci=0.\n\n", 7);

    int n, k;
    printColor("  Vector dimension (n): ", 15); cin >> n;
    printColor("  Number of vectors (k): ", 15); cin >> k;

    Matrix M = makeMatrix(n, k);
    for (int j = 0; j < k; j++) {
        printColor("  v" + to_string(j+1) + " (" + to_string(n) + " values): ", 11);
        for (int i = 0; i < n; i++) cin >> M[i][j];
    }

    cout << "\n";
    printColor("  Matrix of vectors as columns:\n", 7);
    printMatrix(M, "V");

    Matrix copy = M;
    int rank = gaussElim(copy, false);

    cout << "\n";
    printColor("  Rank = " + to_string(rank) + " out of " + to_string(k) + " vectors\n\n", 15);

    if (rank == k) {
        printColor("  LINEARLY INDEPENDENT!\n", 10);
        printColor("  All " + to_string(k) + " vectors are independent.\n", 10);
        printColor("  Only solution to c1*v1+...+ck*vk=0 is all ci=0.\n\n", 10);
    } else {
        printColor("  LINEARLY DEPENDENT!\n", 12);
        int dep = k - rank;
        printColor("  " + to_string(dep) + " vector(s) can be written as combo of others.\n", 12);
        printColor("  Null space has dimension " + to_string(dep) + " (nonzero solutions exist).\n\n", 12);
    }

    // Visual bar
    printColor("  Independent: [", 7);
    for (int i = 0; i < k; i++) {
        if (i < rank) printColor("v" + to_string(i+1) + " ", 10);
        else          printColor("v" + to_string(i+1) + " ", 12);
    }
    printColor("]\n", 7);
    printColor("               ", 7);
    for (int i = 0; i < k; i++) {
        if (i < rank) printColor("^  ", 10);
        else          printColor("x  ", 12);
    }
    cout << "\n";
    printColor("               ", 7);
    for (int i = 0; i < k; i++) {
        if (i < rank) printColor("ok ", 10);
        else          printColor("dep", 12);
    }
    cout << "\n\n";

    pauseKey();
}

// ─────────────────────────────────────────
//  MAIN MENU
// ─────────────────────────────────────────
void mainMenu() {
    while (true) {
        clearScreen();
        cout << "\n";
        printColor("  +==============================================+\n", 11);
        printColor("  |       STUDY COMPANION  v1.0                 |\n", 11);
        printColor("  |    Linear Algebra  &  Computer Science      |\n", 11);
        printColor("  +==============================================+\n\n", 11);

        struct MenuItem { string num, name, desc; };
        vector<MenuItem> items = {
            {"1", "Row Reduction      ", "RREF step-by-step + subspace diagram"},
            {"2", "Vector Operations  ", "2D plot, dot product, angles, sum"},
            {"3", "Concept Cards      ", "Col space, Null space, Big-O, Graphs..."},
            {"4", "Quiz Mode          ", "Test yourself (7 random questions)"},
            {"5", "Determinant        ", "Calculate + meaning + heatmap"},
            {"6", "Linear Independence", "Check if vectors are independent"},
        };

        for (auto& m : items) {
            printColor("  [" + m.num + "] ", 14);
            printColor(m.name, 15);
            printColor("- " + m.desc + "\n", 8);
        }
        printColor("\n  [0] Exit\n\n", 8);
        printColor("  Choose: ", 15);

        int ch; cin >> ch;
        switch(ch) {
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
                printColor("  Invalid.\n", 12);
                Sleep(500);
        }
    }
}

// ─────────────────────────────────────────
//  MAIN
// ─────────────────────────────────────────
int main() {
    setupConsole();
    showSplash();
    mainMenu();
    return 0;
}
