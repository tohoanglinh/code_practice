/*******************************************************************************
 * Description:
 * FR_EMB_HN17_01
 * mentor: @hungnv8
 * Function and Array (16-Jan-2017)
 * Deadline: 17:00 25-Jan-2017
 * dev: @linhth8
 ******************************************************************************/
#ifndef _HEADER_H_
#define _HEADER_H_

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define MAX 10		/* max elements of row and col */

/*******************************************************************************
 * API
 ******************************************************************************/
float rectangle_area(float perimeter, float diagonal);
/*!
 * @brief Tinh dien tich hinh chu nhat, biet chu vi va duong cheo
 *
 * @param perimeter: chu vi hinh chu nhat.
 * @param diagonal: duong cheo hinh chu nhat.
 *
 * @return area: dien tich hinh chu nhat.
 */
 
int isRectangle(float perimeter, float diagonal); 
/*!
 * @brief Kiem tra dieu kien la hinh chu nhat hay khong
 *
 * @param perimeter: chu vi hinh chu nhat.
 * @param diagonal: duong cheo hinh chu nhat.
 *
 * @return 1 neu la hinh chu nhat, 0 neu khong phai hinh chu nhat.
 */

void matrix_input_row_col(void);
/*!
 * @brief Nhap so hang va cot cua ma tran
 *
 * @param void
 *
 * @return void
 */
 
int matrix_check_add_condition(void);
/*!
 * @brief Kiem tra dieu kien co the cong ma tran
 *
 * @param void
 *
 * @return 0 neu khong cong duoc, 1 neu cong duoc.
 */
 
int matrix_check_mul_condition(void);
/*!
 * @brief Kiem tra dieu kien co the nhan ma tran
 *
 * @param void
 *
 * @return 0 neu khong nhan duoc, 1 neu nhan duoc.
 */
 
void matrix_input_elements(void);
void matrix_display(int row, int col, int a[MAX][MAX]);
void matrix_add(int a[MAX][MAX], int b[MAX][MAX]);
void matrix_multiply(int a[MAX][MAX], int b[MAX][MAX]);

#endif /* _HEADER_H_ */
