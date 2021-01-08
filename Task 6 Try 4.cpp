// PHYS 30762 Programming in C++
// Assignment 6
// Jack McGinn

/*Note that the input for a in this code matrix should look like this (for example a 3 by 3, where any number can be put instead of 1)
Input row number 1 of the matrix: 1 1 1
Input row number 2 of the matrix: 1 1 1
Input row number 3 of the matrix: 1 1 1
*/

#include<iostream>
#include<ostream>
#include<sstream>

class matrix
{
    // Friends
    friend ostream& operator<<(ostream& output, const matrix& mat);
    friend void operator>>(std::istream& input, matrix& mat);
private:
    int rows{};
    int columns{};
    double* matrix_data{ nullptr };
public:
    // Default constructor
    matrix() { std::cout << "Default constructor called" << std::endl; }

    // Parameterized constructor (prototyoe)
    matrix(int row, int column);

    // Copy constructor (prototype)
    matrix(matrix&);

    // Move constructor (prototype
    matrix(matrix&& mat);

    // Destructor
    ~matrix() {}

    // Access functions
    int get_rows() const { return rows; } // Return number of rows
    int get_cols() const { return columns; } // Return number of columns

    // Return position in array of element (row_number,column_number)
    int index(int row_number, int column_number) const
    {
        //Conditional to check matrix index is within matrix dimensions then return the position in the array for the entry at this index
        if (row_number > 0 && row_number <= rows && column_number > 0 && column_number <= columns) return (column_number - 1) + (row_number - 1) * columns;
        else { std::cout << "Error: out of range" << endl; exit(1); }
    }

    // Copy  Assignment operator (prototype)
    matrix& operator=(matrix&);

    // Move Assignment operator
    matrix& operator=(matrix&&);

    // Overloading addition operator to deal with adding two matrices
    matrix operator+(const matrix& mat) const
    {
        //Define tempoary matrix to hold the summation to be returned
        matrix addition{ rows,columns };
        if (rows == mat.rows && columns == mat.columns) {
            //For loop to run through all positions in the matrix array to add them together
            for (int i{}; i < rows * columns; i++) {
                addition.matrix_data[i] = matrix_data[i] + mat.matrix_data[i];
            }
        }else {
            std::cout << "Matrix not of same dimensions, could not be added" << std::endl;
        }
        return addition;
    }

    // Overloading subtraction operator to deal with adding two matrices
    matrix operator-(const matrix& mat) const
    {
        //Define tempoary matrix to hold the subtraction to be returned
        matrix subtraction{ rows,columns };
        if (rows == mat.rows && columns == mat.columns) {
            //For loop to run through all positions in the matrix array to add them together
            for (int i{}; i < rows * columns; i++) {
                subtraction.matrix_data[i] = matrix_data[i] - mat.matrix_data[i];
            }
        }else {
            std::cout << "Matrix not of same dimensions, could not be subtracted" << std::endl;
        }
        return subtraction;
    }

    // Overloading multiplication operator to deal with adding two matrices
    matrix operator*(const matrix& mat) const
    {
        //Define tempoary matrix to hold the multiplication to be returned
        matrix multiplication{ rows,mat.columns };
        if (columns == mat.rows) {
            int array_position = 0;//Runs through the positions in the new multiplication matrix to store the sum from the multiplication at each position
            //For loops run indexes through the matrices being multiplied so each seperate entry can be accessed
            for (int i{ 1 }; i <= rows; i++) {
                for (int j{ 1 }; j <= columns; j++) {
                    double sum = 0;//Keeps track for the sum for each entry in the multiplication
                    for (int k{ 1 }; k <= columns; k++) {
                        sum += matrix_data[index(i, k)] * mat.matrix_data[index(k, j)];
                    }
                    multiplication.matrix_data[array_position] = sum;
                    array_position++;
                }
            }
        }else {
            std::cout << "Matrix of incorrect dimensions to be multiplied" << std::endl;
        }
        return multiplication;
    }

    // Function to remove a specified row and column from the matrix
    matrix remove_row_and_column(int row_number, int column_number)
    {
        //Create matrix for within this function that will store the old matrix without the row and column
        matrix new_matrix(rows - 1, columns - 1);
        int array_position{};
        //For loops to run the index through each position in the matrix
        for (int i{ 1 }; i <= rows; i++) {
            for (int j{ 1 }; j <= columns; j++) {
                //Conditional to make sure only add the entries to the new matrix if it is not from the row or columns specified
                if (i != row_number && j != column_number) {
                    new_matrix.matrix_data[array_position] = matrix_data[index(i, j)];
                    array_position++;
                }
            }
        }
        return new_matrix;
    }

    // Function to calculate the determinant of a square matrix
    double determinant() {
        double det{};
        // Define a matrix within the function to hold the submatrix of the original one so this determinat can be calculated iteratively till the submatrix is a 2 by 2
        matrix submatrix(columns - 1, rows - 1);
        //Conditional checks entred matrix is a 2 by 2 and if so does the calculation for determinant for it
        if (columns == 2) {
            return ((matrix_data[0] * matrix_data[3]) - (matrix_data[2] * matrix_data[1]));
        }else {
            //For loop to run through each value on the top row of the column to get the submatrix required for each
            for (int x{ 1 }; x <= columns; x++) {
                //Uses the previous function to get the submatrix then does the required calculation for the determinant
                submatrix = remove_row_and_column(1, x);
                det = det + (pow(-1, x-1) * matrix_data[index(1, x)] * submatrix.determinant());
            }
        }
        return det;
    }
};

// Member functions defined outside class
//Parameterised constructor
matrix::matrix(int row, int column)
{
    std::cout << "Parameterized constructor called" << std::endl;
    if (row < 1 or column < 1) {
        std::cout << "Error: trying to declare a matrix with size < 1 for rows or columns" << std::endl;
        throw("size not positive");
    }
    rows = row;
    columns = column;
    matrix_data = new double[rows * columns];
    //For loop to run through each point in the constructor and set it to be 0 for the parameterised constructor
    for (int i{}; i < rows * columns; i++) { matrix_data[i] = 0; }

}

// Copy constructor for deep copying
matrix::matrix(matrix& mat)
{
    // Copy size and declare new array
    std::cout << "Copy constructor called\n";
    //Create a blank matrix of the same dimensions of the one being copied
    matrix_data = nullptr; rows = mat.get_rows(); columns = mat.get_cols();
    if (rows > 0 && columns > 0) {
        matrix_data = new double[rows * columns];
        // For loop to run through each value in the matrix array and copy the values into new array
        for (int i{}; i < rows * columns; i++) {
            matrix_data[i] = mat.matrix_data[i];

        }
    }
}

//Copy assigment operator
matrix& matrix::operator=(matrix& mat)
{
    std::cout << "Copy assignment called\n";
    if (&mat == this) { return *this; } // no self assignment
    // First delete this object’s array
    delete[] matrix_data; matrix_data = nullptr; rows = 0; columns = 0;
    // Now copy size and declare new array
    rows = mat.get_rows(); columns = mat.get_cols();
    if (rows > 0 && columns > 0){
        matrix_data = new double[rows * columns];
        // For loop to run through each value in the matrix array and copy the values into new array
        for (int i{}; i < rows * columns; i++) {
            matrix_data[i] = mat.matrix_data[i];

        }
    }
    return *this; // Special pointer!!!
}

// Move constructor
matrix::matrix(matrix&& mat)
{    // Steal the data
    std::cout << "Move constructor called\n";
    rows = mat.get_rows();
    columns = mat.get_cols();
    matrix_data = mat.matrix_data;
    mat.rows = 0; mat.columns = 0;
    mat.matrix_data = nullptr;
}

// Move assignment operator
matrix& matrix::operator=(matrix&& mat)
{
    std::cout << "Move assignment called\n";
    std::swap(rows, mat.rows);
    std::swap(columns, mat.columns);
    std::swap(matrix_data, mat.matrix_data);
    return *this;
}

// Function to overload << operator for matrices so that they can be output to the user
std::ostream& operator<<(std::ostream& output, const matrix& mat)
{
    //For loops to run through index of each position in the matrix
    for (int i{ 1 }; i <= mat.get_rows(); i++) {
        for (int j{ 1 }; j <= mat.columns; j++) {
            //Output each entry at this position seperated by a space from the next
            output << mat.matrix_data[mat.index(i, j)] << "  ";
        }
        //Leave a new line for each row
        output << std::endl;
    }
    return output;
}

// Function to overload the input operator so that the user can input a matrix and it can be saved in the matrix class form
void operator>>(std::istream& input, matrix& mat)
{
    //Take input as each row entred as a new line and the entries in each row seperated by a space
    std::string input_row;
    //For loop to run through each row in the matrix
    for (int i{ 1 }; i <= mat.rows; i++) {
        //Variables save the positions of spaces in the string so each entry can be found
        int position_initial_space{};
        int position_next_space{};
        std::cout << "Input row number " << i << " of the matrix: ";
        std::getline(std::cin, input_row);
        //For loop to run index through matrix columns
        for (int j{ 1 }; j <= mat.columns; j++) {
            position_next_space = input_row.find(" ", position_initial_space + 1);
            //Take each entry between the spaces of the user input as the entry to the matrix and run it through the columns moving the spaces which the code is looking between along
            mat.matrix_data[mat.index(i, j)] = stod(input_row.substr(position_initial_space, (position_next_space - position_initial_space)));
            position_initial_space = position_next_space + 1;
        }
    }
    return;
}

// Main program
int main()
{
    // First part of assignment: constructing and deep copying matrices
    // Demonstrate default constructor
    std::cout << "Default constructor used to set value of matrix_one. " << std::endl;
    matrix matrix_one;
    std::cout << "Output matrix_one:  " << std::endl << matrix_one;

    // Parameterized constructor
    std::cout << "Parameterised constructor used to set value of matrix_two" << std::endl;
    const int number_of_rows{ 3 };//NUMBER OF ROWS AND COLUMNS SET HERE FOR ALL THE CODE. CAN CHANGE IF YOU WANT TO TEST FEATURES.
    const int number_of_columns{ 3 };//ALL MATRICES IN THIS CODE WILL THEN HAVE THESE NUMBERS OF ROWS AND COLUMNS
    matrix matrix_two{ number_of_rows,number_of_columns };
   
    // User inputs values for matrix_two here
    std::cout << "Number of rows and columns for the matrices is set to be " << number_of_rows << " by " << number_of_columns << ", this can be changed in the code. " << std::endl;
    std::cout << "To input a matrix, after each entry put in the matrix press space and after the row is done press enter. Do the amount of entries for rows and columns specified above" << std::endl;
    std::cout<< "Input matrix_two" << std::endl;
    std::cin >> matrix_two;
   
    // Print matrix matrix_two
    std::cout << "Output matrix_two" << std::endl << matrix_two << std::endl;
   
    // Deep copy by assignment: define new matrix_three then copy from matrix_two to matrix_three
    std::cout << "Parameterised constructor used to initialise matrix_3" << std::endl;
    matrix matrix_three{ number_of_rows,number_of_columns };
    std::cout << "Output matrix_three" << std::endl << matrix_three;
    std::cout << "matrix_3 set to be same as matrix_2." << std::endl;
    matrix_three = matrix_two;
    std::cout << "Output matrix_three again" << std::endl << matrix_three;
    
    // Modify contents of original matrix and show assigned matrix is unchanged here
    std::cout << "Reinput contents of original matrix (matrix_two) and show assigned matrix (matrix_three) is unchanged " << std::endl << "Input a new matrix_two" << std::endl;
    std::cin >> matrix_two;
    std::cout << "Output matrix_two" << std::endl << matrix_two;
    std::cout << "Output matrix_three" << std::endl << matrix_three;

    // Deep copy using copy constructor 
    std::cout << "matrix_four copied to be same as matrix_two." << std::endl;
    matrix matrix_four{ matrix_two };
    std::cout << "Output matrix_four" << std::endl << matrix_four;

    // Modify contents of original matrix and show copied matrix is unchanged here
    std::cout << "Reinput contents of original matrix (matrix_two) and show copied matrix (matrix_four) is unchanged " << std::endl << "Input a new matrix_two" << std::endl;
    std::cin >> matrix_two;
    std::cout << "Output matrix_two" << std::endl << matrix_two;
    std::cout << "Output matrix_four" << std::endl << matrix_four;

    // Move copy construction demonstration
    std::cout << "A new matrix matrix_five is made from a move copy construction of matrix_three " << std::endl;
    matrix matrix_five{ std::move(matrix_three) };
    std::cout << "Output matrix_five" << std::endl << matrix_five << std::endl;
    
    // Move assignment demonstration
    std::cout << "matrix_five is now move assigned to equal matrix_2" << std::endl;
    matrix_five = std::move(matrix_two);
    std::cout << "Output matrix_five" << std::endl << matrix_five << std::endl;

    // Second part of assignment: matrix operations
    std::cout << "Now arithematic operations will be applied to matrix_four and matrix_five. For note the values of these matrices are." << std::endl;
    std::cout << "matrix_four: " << std::endl << matrix_four << std::endl << "matrix_five" <<std::endl << matrix_five << std::endl;

    // Addition of 2 matrices
    std::cout << "Adding matrix_five and matrix_four " << std::endl;
    std::cout << matrix_four + matrix_five << std::endl;
    // Subtraction of 2 matrices
    std::cout << "Subtracting matrix_four from matrix_five " << std::endl;
    std::cout << matrix_five - matrix_four << std::endl;
    // Multiplication of 2 matrices
    std::cout << "Multiplying matrix_five and matrix_four " << std::endl;
    std::cout << matrix_five * matrix_four << std::endl;

    std::cout << "Removing row and column one from matrix_five " << std::endl;
    std::cout << matrix_five.remove_row_and_column(1, 1) << std::endl; //(remove_row_and_column(row number, column number)
    std::cout << "Which row and column that is removed can also be changed in the code" << std::endl;

    // Determinant of square matrix, conditional to check that it is infact square first
    std::cout << "Finally input a matrix to calculate the determinant of. " << std::endl;
    std::cout << "Parameterised constructor used to make this matrix. It is made to be " << number_of_rows<< " by " << number_of_columns << " matrix."<< std::endl;
    matrix matrix_six{ number_of_rows,number_of_columns };
    std::cout << "Now input the values of this matrix" << std::endl;
    std::cin >> matrix_six;
    if (matrix_six.get_cols() == matrix_six.get_rows()) {
        std::cout <<std::endl<< "Submatrices are made to calculate the determinant, so  constructors are called." << std::endl<<std::endl;
        std::cout << std::endl << "The determinant of this matrix is is " << matrix_six.determinant()<<std::endl;
    }else {
        std::cout << "Only the determinant of square matrices can be found in this code. This matrix is not square so its determinant can not be found.";
    }
    return 0;
}

