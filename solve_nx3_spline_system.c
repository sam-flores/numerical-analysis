#define max_n 100

void nx3_eliminate_lower_diagonal(double lower[max_n], double middle[max_n], double upper[max_n],
                                  double v[max_n], int n)
{
    int i;
    for (i = 0; i < n - 2; i++)
    {
        v[i + 1] = middle[i] * v[i + 1] - lower[i] * v[i];
        middle[i + 1] = middle[i] * middle[i + 1] - lower[i] * upper[i + 1];
        upper[i + 2] = middle[i] * upper[i + 2] - lower[i] * 0;
        lower[i] = middle[i] * lower[i] - lower[i] * middle[i];
    }
    v[i + 1] = middle[i] * v[i + 1] - lower[i] * v[i];
    middle[i + 1] = middle[i] * middle[i + 1] - lower[i] * upper[i + 1];
    lower[i] = middle[i] * lower[i] - lower[i] * middle[i];
}

void nx3_eliminate_upper_diagonal(double lower[max_n], double middle[max_n], double upper[max_n],
                                  double v[max_n], int n)
{
    int i;
    for (i = n - 1; i > 0; i--)
    {
        v[i - 1] = middle[i] * v[i - 1] - upper[i] * v[i];
        middle[i - 1] = middle[i] * middle[i - 1] - upper[i] * lower[i - 1];
        upper[i] = middle[i] * upper[i] - upper[i] * middle[i];
    }
}

void nx3_eliminate_middle_diagonal(double lower[max_n], double middle[max_n], double upper[max_n],
                                   double v[max_n], int n)
{
    for (int i = 0; i < n; i++)
    {
        v[i] /= middle[i];
        middle[i] /= middle[i];
    }
}