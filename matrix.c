#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Method Declaration */
int **create_matrix(int row, int col);
void print_matrix(int **matrix, int row, int col);
int free_matrix(int **matrix, int row, int col);
int fill_data(int **matrix, int row, int col);
int addition_matrix(int **matrix_a, int **matrix_b, int row, int col);
int subtraction_matrix(int **matrix_a, int **matrix_b, int row, int col);
int transpose_matrix(int **matrix, int **matrix_t, int row, int col);
int multiply_matrix(int **matrix_a, int **matrix_t, int row, int col);

int main()
{

    char command;
    printf("[----- [Lee Jun Gi]  [2017035135] -----]\n");

    int row, col;
    srand(time(NULL));

    printf("Input row and col : ");
    scanf("%d %d", &row, &col);

    int **matrix_a = create_matrix(row, col);
    int **matrix_b = create_matrix(row, col);
    int **matrix_a_t = create_matrix(col, row);

    printf("Matrix Created.\n");

    if (matrix_a == NULL || matrix_b == NULL)
    {
        return -1;
    }

    do
    {
        printf("----------------------------------------------------------------\n");
        printf("                     Matrix Manipulation                        \n");
        printf("----------------------------------------------------------------\n");
        printf(" Initialize Matrix   = z           Print Matrix        = p \n");
        printf(" Add Matrix          = a           Subtract Matrix     = s \n");
        printf(" Transpose matrix_a  = t           Multiply Matrix     = m \n");
        printf(" Quit                = q \n");
        printf("----------------------------------------------------------------\n");

        printf("Command = ");
        scanf(" %c", &command);

        switch (command)
        {
        case 'z':
        case 'Z':
            printf("Matrix Initialized\n");
            fill_data(matrix_a, row, col);      // 행렬 초기화
            fill_data(matrix_b, row, col);      // 행렬 초기화
            printf("matrix_a\n");
            print_matrix(matrix_a, row, col);       // 행렬 출력
            printf("matrix_b\n");
            print_matrix(matrix_b, row, col);       // 행렬 출력
            break;
        case 'p':
        case 'P':
            printf("Print matrix\n");
            printf("matrix_a\n");
            print_matrix(matrix_a, row, col);       // 행렬 출력
            printf("matrix_b\n");
            print_matrix(matrix_b, row, col);       // 행렬 출력
            break;
        case 'a':
        case 'A':
            printf("Add two matrices\n");
            addition_matrix(matrix_a, matrix_b, row, col);       // (matrix_a + marix_b) 행렬 출력
            break;
        case 's':
        case 'S':
            printf("Subtract two matrices \n");
            subtraction_matrix(matrix_a, matrix_b, row, col);       // (matrix_a - marix_b) 행렬 출력
            break;
        case 't':
        case 'T':
            printf("Transpose matrix_a \n");
            printf("matrix_a\n");
            print_matrix(matrix_a, row, col);       // matrix_a 출력
            transpose_matrix(matrix_a, matrix_a_t, col, row);       // matrix_a의 전치 행렬을 matrix_a_t에 대입
            printf("matrix_a_t\n");
            print_matrix(matrix_a_t, col, row);     // matrix_a_t 출력
            break;
        case 'm':
        case 'M':
            printf("Multiply matrix_a with transposed matrix_a \n");
            transpose_matrix(matrix_a, matrix_a_t, col, row);       // matrix_a의 전치 행렬을 matrix_a_t에 대입
            multiply_matrix(matrix_a, matrix_a_t, row, col);        // (matrix_a * matrix_a_t) 행렬 출력
            break;
        case 'q':
        case 'Q':
            printf("Free all matrices..\n");
            free_matrix(matrix_a_t, col, row);      // matrix_a_t 동적할당 해제
            free_matrix(matrix_a, row, col);        // matrix_a 동적할당 해제
            free_matrix(matrix_b, row, col);        // matrix_b 동적할당 해제
            break;
        default:
            printf("\n       >>>>>   Concentration!!   <<<<<     \n");
            break;
        }

    } while (command != 'q' && command != 'Q');

    return 1;
}

/* create a 2d array whose size is row x col using malloc() */
int **create_matrix(int row, int col)
{
    /*check preconditions*/
    // 행, 열의 크기가 0보다 큰 경우만
    if (row <= 0 || col <= 0)
    {
        printf("Check the sizesof row and col!\n");
        return NULL;
    }

    int **matrix = (int **)malloc(sizeof(int *) * row);
    for (int i = 0; i < row; i++)
    {
        *(matrix + i) = (int *)malloc(sizeof(int) * col);
    }

    /*check extra-conditions*/
    // 행렬을 동적할당이 되었는지 확인
    if (matrix == NULL)
    { 
        /* proper actions for unexpected conditions */
        printf("matrix is emptied.\n");
        return NULL;
    }

    return matrix;
}

/* print matrix whose size is row x col */
void print_matrix(int **matrix, int row, int col)
{
    /*check preconditions*/
    // 행렬이 초기화 되었는지 확인
    for(int i = 0; i < row; i++)
        for(int j = 0; j < col; j++){
            if(*(*(matrix+i)+j) >= 20 || *(*(matrix+i)+j) < 0){
                printf("Matrix is not Initialize Matrix\n");                
                return ;
            }
        }
    // 행렬의 모든 원소 출력
    for (int i = 0; i < row; i++){
        for (int j = 0; j < col; j++)
            printf("%d\t", *(*(matrix + i) + j));
        printf("\n");
    }
    /*check extra-conditions*/
    // 행렬이 그대로 있는지 확인
    if (matrix == NULL)
    { 
        /* proper actions for unexpected conditions */
        printf("matrix is emptied.\n");
        return ;
    }
}

/* free memory allocated by create_matrix() */
int free_matrix(int **matrix, int row, int col)
{
    /*check preconditions*/
    // 행렬이 할당해제되어 있는지 확인
    if (matrix == NULL)
    { 
        /* proper actions for unexpected conditions */
        printf("matrix is emptied.\n");
        return -1;
    }
    
    for (int i = 0; i < row; i++){
        for (int j = 0; j < col; j++){
            free((*(matrix + i) + j));
        }
        free(matrix+i);
    }
    return 1;
}

/* assign random values to the given matrix */
int fill_data(int **matrix, int row, int col)
{
    /*check preconditions*/
    //행렬이 할당되었는지 확인
    if (matrix == NULL)
    { 
        /* proper actions for unexpected conditions */
        printf("matrix is emptied.\n");
        return -1;
    }

    // 행렬의 모든 원소에 값을 할당
    for (int i = 0; i < row; i++){
        for (int j = 0; j < col; j++){
            *(*(matrix + i) + j) = rand() % 20;
        }
    }

    /*check extra-conditions*/
    // 행렬이 할당되었는지 확인
    if (matrix == NULL)
    { 
        /* proper actions for unexpected conditions */
        printf("matrix is emptied.\n");
        return -1;
    }
}

/* matrix_sum = matrix_a + matrix_b */
int addition_matrix(int **matrix_a, int **matrix_b, int row, int col)
{
    /*check preconditions*/
    // 행렬이 초기화 되었는지 확인
    for(int i = 0; i < row; i++)
        for(int j = 0; j < col; j++)
            if(*(*(matrix_a+i)+j) >= 20 || *(*(matrix_a+i)+j) < 0 || *(*(matrix_b+i)+j) >= 20 || *(*(matrix_b+i)+j) < 0){
                printf("Matrix is not Initialize Matrix\n");                
                return -1;
            }

    // matrix_a와 matrix_b의 행렬을 더하여 출력
    int sum = 0;        // 더한 값을 저장할 변수
    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            sum = *(*(matrix_a+i)+j) + *(*(matrix_b+i)+j);      // 더한 값을 sum에 저장
            printf("%d\t", sum);        // 더한 값을 출력
        }
        printf("\n");
    }
    /*check extra-conditions*/
    // 더한 후 행렬이 사라졌는지 확인
    if (matrix_a == NULL || matrix_b == NULL)
    { 
        /* proper actions for unexpected conditions */
        printf("matrix is emptied.\n");
        return -1;
    }

    return 1;
}

/* matrix_sub = matrix_a - matrix_b */
int subtraction_matrix(int **matrix_a, int **matrix_b, int row, int col)
{
    /*check preconditions*/
    // 행렬이 초기화 되었는지 확인
    for(int i = 0; i < row; i++)
        for(int j = 0; j < col; j++)
            if(*(*(matrix_a+i)+j) >= 20 || *(*(matrix_a+i)+j) < 0 || *(*(matrix_b+i)+j) >= 20 || *(*(matrix_b+i)+j) < 0){
                printf("Matrix is not Initialize Matrix\n");                
                return -1;
            }

    int sub = 0;        // 두 행렬의 뺀 값을 저장할 변수
    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            sub = *(*(matrix_a+i)+j) - *(*(matrix_b+i)+j);      // 뺀 값을 sub에 저장
            printf("%d\t", sub);
        }
        printf("\n");
    }
    /*check extra-conditions*/
    // 뺀 후 행렬이 사라졌는지 확인
    if (matrix_a == NULL || matrix_b == NULL)
    { 
        /* proper actions for unexpected conditions */
        printf("matrix is emptied.\n");
        return -1;
    }
}

/* transpose the matrix to matrix_t */
int transpose_matrix(int **matrix, int **matrix_t, int row, int col)
{
    /*check preconditions*/
    // 행렬이 초기화 되었는지 확인
    for(int i = 0; i < row; i++)
        for(int j = 0; j < col; j++)
            if(*(*(matrix+i)+j) >= 20 || *(*(matrix+i)+j) < 0){
                printf("Matrix is not Initialize Matrix\n");                
                return -1;
            }
    // 행렬의 전치행렬 만들기
    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            *(*(matrix_t+j)+i) = *(*(matrix+i)+j);
        }
    }
    /*check extra-conditions*/
    // 전치된 행렬의 모든 원소 값이 초기화되었는지 확인
    for(int i = 0; i < row; i++)
        for(int j = 0; j < col; j++)
            if(*(*(matrix_t+i)+j) >= 20 || *(*(matrix_t+i)+j) < 0){
                printf("Matrix_t is not Initialize Matrix\n");                
                return -1;
            }
}

/* matrix_axt - matrix_a x matrix_t */
int multiply_matrix(int **matrix_a, int **matrix_t, int row, int col)
{
    /*check preconditions*/
    // 행렬이 초기화 되었는지 확인
    for(int i = 0; i < row; i++)
        for(int j = 0; j < col; j++)
            if(*(*(matrix_a+i)+j) >= 20 || *(*(matrix_a+i)+j) < 0 || *(*(matrix_t+i)+j) >= 20 || *(*(matrix_t+i)+j) < 0){
                printf("Matrix is not Initialize Matrix\n");                
                return -1;
            }
    
    
    int mul = 0;        // 곱한 원소를 저장할 변수
    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            mul = *(*(matrix_a+i)+j) * *(*(matrix_t+j)+i);      // 행렬의 곱셈값을 mul에 저장
            printf("%d\t", mul);
        }
        printf("\n");
    }
    /*check extra-conditions*/
    // 곱셈 후 행렬이 사라졋는지 확인
    if (matrix_a == NULL || matrix_t == NULL)
    { 
        /* proper actions for unexpected conditions */
        printf("matrix is emptied.\n");
        return -1;
    }
}
