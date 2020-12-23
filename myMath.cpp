#include "myMath.h"

namespace myMath
{

	int MyMath::max_in_arr(int arr[], int n)
	{
		if (n <= 0)
			return -1;

		int max = arr[0];
		int idx = 0;
		for (int i = 0; i < n; i++)
		{
			if (arr[i] > max)
			{
				idx = i;
				max = arr[i];
			}
		}

		return idx;
	}
}