using System;

class Program
{
    static int Main()
    {
        int[] array = {1837,3,48,90380809,763,9};
        MergeSort(ref array,0,5);
        foreach(int a in array)
            Console.Write("{0} ",a);
        return 0;
    }

    static void Merge(ref int[] array,int left,int middle,int right)
    {
        int[] leftNums = new int[middle - left + 2];
        int[] rightNums = new int[right - middle + 1];
        
        for(int i = 0; i < leftNums.Length - 1; ++i)
            leftNums[i] = array[left + i];
        for(int i = 0; i < rightNums.Length - 1;++i)
            rightNums[i] = array[middle + i + 1];
        
        leftNums[leftNums.Length - 1] = int.MaxValue;
        rightNums[rightNums.Length - 1] = int.MaxValue;

        int _1 = 0,_2 = 0;
        for(int i = left; i <= right; ++i)
        {
            if(leftNums[_1] < rightNums[_2])
                array[i] = leftNums[_1++];
            else
                array[i] = rightNums[_2++];
        }
    }

    static void MergeSort(ref int[] array,int left,int right)
    {
        if(left < right)
        {
            int middle = (left + right) / 2;
            MergeSort(ref array,left,middle);
            MergeSort(ref array,middle + 1,right);
            Merge(ref array,left,middle,right);
        }
    }
}