public class Nqueens {
    private int[][] grid;
    private int size;


    public int numSolutions;

    Nqueens(int s) {
        size = s;

        grid = new int[s][s];

        for (int[] row : grid)
            for (int element : row)
                element = 0;
    }

    private boolean checkValid(int row, int col) {
        for (int i = 0; i < size; i++) {
            if (grid[row][i] != 0)
                return false;
            else if (grid[i][col] != 0)
                return false;

            for (int j = 0; j < size; j++) {
                if (grid[i][j] == 1 && Math.abs(i - row) == Math.abs(j - col))
                    return false;
            }
        }

        return true;
    }

    public int solve(boolean printSol) {
        numSolutions = 0;

        solve(0, printSol);

        return numSolutions;
    }

    private void solve(int row, boolean printSol) {
        if (row >= size) {
            numSolutions++;
            if (printSol) printGrid();
            return;
        }

        for (int col = 0; col < size; col++) {
            if (checkValid(row, col)) {
                grid[row][col] = 1;

                solve(row + 1, printSol);

                grid[row][col] = 0;
            }
        }
    }

    void printGrid() {
        for (int[] row : grid) {
            for (int val : row) {
                System.out.print(val + " ");
            }
            System.out.println();
        }
        System.out.println();
    }

    int getValue(int row, int col) {
        return grid[row][col];
    }

    public static void main(String[] args) {
        for (int i = 1; i <= 20; i++) {
            Nqueens q = new Nqueens(i);

            System.out.println(i + ": " + q.solve(false));
        }
    }
}
