#include <iostream>

using namespace std;

int * maximum_subarray_brute(int * input_array, int array_size, int * start_idx, int * end_idx, int * max_sum);
int maximum_subarray_dnc(int * input_array, int* ldx, int* hdx);
int maximum_subarray_dnc_cross(int * input_array, int* ldx, int* mdx, int* hdx);

void printArraySlice(int * input_array, int * start_idx, int * end_idx);
void printArray(int * input_array, int array_size);

int main()
{
    //divide and conquer algo for maximum subarray problem
    int my_array[] = {-9,8,-7,6,-5,4,-3,2,-1,0};
//    int my_array[] = {0,-9,8,-7,6,-5,4,-3,2,-1};
//    int my_array[] = {13,-3,-25,20,-3,-16,-23,18,20,-7,12,-5,-22,15,-4,7}; // Introduction to Algorithms
//    int my_array[] = {-1,-2,-3,-4,-5};
//    int my_array[] = {-1,-1, -1};
//    int my_array[] = {-2, -5, 6, -2, -3, 1, 5, -6};  // Geeks for Geeks
//    int my_array[] = {0,-1,1,1,1};
//    int my_array[] = {-1, 1, 1, 1};
//    int my_array[] = {0,-1,1};
//    int my_array[] = {0};
//    int my_array[] = {1};
    int array_size = *(&my_array + 1) - my_array;
    cout<<"-- Original Array--\n";
    printArray(my_array, array_size);
    cout<<endl;

    int start_idx = 0;
    int end_idx = array_size - 1;
    int max_sum = 0;
    int* mptr = &max_sum;
//    cout<<"-- prt + 1"<<endl;
//    cout<<*mptr+1<<endl;

    // algorithm
//    maximum_subarray_brute(my_array, array_size, &start_idx, &end_idx, &max_sum);
    max_sum = maximum_subarray_dnc(my_array, &start_idx, &end_idx);

    // results
    cout<<endl;
    cout<<"max sum: "<<max_sum<<endl;
    cout<<"start index: "<<start_idx<<endl;
    cout<<"end index: "<<end_idx<<endl;
    printArraySlice(my_array, &start_idx, &end_idx);
    cout<<endl;


    return 0;
}

int * maximum_subarray_brute(int * input_array, int array_size, int * start_idx, int * end_idx, int * max_sum){
    *max_sum = input_array[0];
    *start_idx = 0;
    *end_idx = 0;
    int running_sum;

    for(int idx = 0; idx < array_size; ++idx){
        running_sum = input_array[idx];
        if (running_sum > *max_sum){
                *max_sum = running_sum;
                *start_idx = idx;
                *end_idx = idx;
        }

        for (int jdx = idx + 1; jdx < array_size; ++jdx){
            //update running sum;
            running_sum = running_sum + input_array[jdx];

            if (running_sum > *max_sum){
                *max_sum = running_sum;
                *start_idx = idx;
                *end_idx = jdx;
        }
    }
}
}


int maximum_subarray_dnc(int * input_array, int* ldx, int* hdx){
    int Leftldx = *ldx;
    int Lefthdx = *hdx;
    int LeftSum;
    int Rightldx = *ldx;
    int Righthdx = *hdx;
    int RightSum;
    int Crossldx = *ldx;
    int Crosshdx = *hdx;
    int CrossSum;

    if (*ldx == *hdx){  // if only one item left. base case
        return input_array[*ldx];
    }else{
        int mdxLeft = (*ldx + *hdx)/2;
        int mdxRight = (*ldx + *hdx)/2;
        int mdxCross = (*ldx + *hdx)/2;


        Lefthdx = mdxLeft;
        LeftSum = maximum_subarray_dnc(input_array, &Leftldx, &Lefthdx);

        CrossSum = maximum_subarray_dnc_cross(input_array, &Crossldx, &mdxCross, &Crosshdx);
        Rightldx = mdxRight + 1;
        RightSum = maximum_subarray_dnc(input_array, &Rightldx, &Righthdx);

        if (LeftSum>=RightSum && LeftSum>=CrossSum){
            *ldx = Leftldx;
            *hdx = Lefthdx;
            return LeftSum;
        }else if (RightSum>=LeftSum && RightSum>=CrossSum){
            *ldx = Rightldx;
            *hdx = Righthdx;
            return RightSum;
        }else{
            *ldx = Crossldx;
            *hdx = Crosshdx;
            return CrossSum;
        }
    }

}

int maximum_subarray_dnc_cross(int * input_array, int* ldx, int* mdx, int* hdx){
    int start_idx = *ldx;
    int mid_idx = *mdx;
    int end_idx = *hdx;

    int LeftSum = INT_MIN;
    int sum = 0;
    for (int i = *mdx; i > *ldx - 1; --i){
        sum += input_array[i];
        if (sum > LeftSum){
            LeftSum = sum;
            start_idx = i;
        }
    }

    int RightSum = INT_MIN;
    sum = 0;
    for (int i = *mdx + 1; i < *hdx + 1; ++i){
        sum += input_array[i];
        if (sum > RightSum){
            RightSum = sum;
            end_idx = i;
        }
    }
    *ldx = start_idx;
    *hdx = end_idx;
    return LeftSum + RightSum;
}



void printArraySlice(int * input_array, int * start_idx, int * end_idx){
    cout<<"[";
    for (int i = *start_idx; i <= *end_idx; ++i){
        cout<<input_array[i]<<" ";
    }
    cout<<"]";
}

void printArray(int * input_array, int array_size){
    cout<<"[";
    for(int i = 0; i < array_size; ++i){
        cout<<input_array[i]<<" ";
    }
    cout<<"]";
}







