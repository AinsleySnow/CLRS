#include <stdlib.h>
#include <stdio.h>

void water_stops(int miles[], int output[], int m)
{
    int startpoint = 0, endpoint = m, prev_stop = 0, i_output = 0;
    int n = sizeof(miles) / sizeof(int);
    for (int i = 1; i < n; ++i)
    {
        if (miles[i] < endpoint && miles[i] >= startpoint)
            prev_stop = i;
        else
        {
            output[i_output] = prev_stop;
            prev_stop = i;
            startpoint = miles[prev_stop];
            endpoint = startpoint + m;
        }
    }
}

void print_solution(int output[], int miles[])
{
    int n = sizeof(output) / sizeof(int);
    for (int i = 0; i < n; ++i)
    {
        if (!output[i])
            break;
        printf("%d ", miles[output[i]]);
    }
}

int main(void)
{
    int miles[] = { 50, 62, 78, 104, 180, 210, 
                    252, 270, 297, 327, 374, 413, 
                    455, 463, 486, 505, 531, 558, 
                    590, 603, 621, 656, 682, 708, 
                    730, 780, 812, 850, 896, 949, 
                    996, 1050, 1090, 1105, 1141, 1169 };
    int output[36] = { 0 };

    water_stops(miles, output, 100);
    print_solution(output, miles);
}