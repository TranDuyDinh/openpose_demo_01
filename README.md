# openpose_demo_01

//*****************************************************************************
//! \brief  This funtions multiplies 2 matrices
//! \param  n row of first matrix
//! \param  w col. of 1st matrix & row of 2rd matrix
//! \param  m col. of second matrix
//! \param  mat1[] first matrix
//! \param  mat2[] second matrix
//! \return res[] result
//*****************************************************************************
void mult2Matrix(float res[sizeMax],
				 int n, int w, int m,
				 int mat1[sizeMax], int mat2[sizeMax])
{
	int pos; // position of the current value
	int j;
	int row, col;
	int dim = n*m;	// dimemtion of output matrix
	
	for (pos = 0; pos < dim; pos++)
	{
		res[pos] = 0;		// reset value
		row = pos / m;		// row of pos
		col = pos % m;		// collow of pos

		for (j = 0; j < w; j++)
		{
			res[pos] = res[pos] + (mat1[row * w + j] * mat2[col + (j * m)]);
		}
	}
}
