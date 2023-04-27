
void div_row(int index, double lower[], double middle[], double upper[],
             double v[], int n, double div)
{
    middle[index] /= div;
    if (index < n - 1)
        upper[index + 1] /= div;
    if (index > 0)
        lower[index - 1] /= div;
    v[index] /= div;
}

double find_max(double a, double b, double c)
{
    a = fabs(a);
    b = fabs(b);
    c = fabs(c);
    if (a > b && a > c)
        return a;
    else if (b > a && b > c)
        return b;
    else if (c > a && c > b)
        return c;
    else
        return a;
}

void normalize_matrix(double lower[], double middle[], double upper[],
                      double v[], int n)
{
    double max;
    if (fabs(middle[0]) < fabs(upper[1]))
        div_row(0, lower, middle, upper, v, n, fabs(upper[1]));
    else
        div_row(0, lower, middle, upper, v, n, fabs(middle[0]));

    for (int i = 1; i < n - 1; i++)
    {
        max = find_max(lower[i - 1], middle[i], upper[i + 1]);
        div_row(i, lower, middle, upper, v, n, max);
    }
    if (fabs(middle[n - 1]) < fabs(lower[n - 2]))
        div_row(0, lower, middle, upper, v, n, fabs(lower[n - 2]));
    else
        div_row(0, lower, middle, upper, v, n, fabs(middle[n - 1]));
}

void nx3_eliminate_lower_diagonal(double lower[], double middle[], double upper[],
                                  double v[], int n)
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
    normalize_matrix(lower, middle, upper, v, n);
}

void nx3_eliminate_upper_diagonal(double lower[], double middle[], double upper[],
                                  double v[], int n)
{
    int i;
    for (i = n - 1; i > 0; i--)
    {
        v[i - 1] = middle[i] * v[i - 1] - upper[i] * v[i];
        middle[i - 1] = middle[i] * middle[i - 1] - upper[i] * lower[i - 1];
        upper[i] = middle[i] * upper[i] - upper[i] * middle[i];
    }
}

void nx3_eliminate_middle_diagonal(double lower[], double middle[], double upper[],
                                   double v[], int n)
{
    for (int i = 0; i < n; i++)
    {
        v[i] /= middle[i];
        middle[i] /= middle[i];
    }
}