import sys
import random

def question_one(box_sequence):
    box_count=len(box_sequence)
    half_len=int(box_count/2)
    i=1
    operation_count=0
    while(i<half_len):
        temp=box_sequence[i]
        box_sequence[i] = box_sequence[box_count-1-i]
        box_sequence[box_count-1-i]=temp
        i+=2
        operation_count+=1
    print(operation_count)
    return box_sequence

def question_two(coin_sequence):
    fake_coin=None
    coins_count=len(coin_sequence)
    first_coin_index=0
    while (coins_count>1):
        left_sum=0
        right_sum=0
        if coins_count%2==0:
            mid_point=int(coins_count/2)
            mid_coin=None
        else:
            mid_point=int((coins_count+1)/2)
            mid_coin=int((coins_count-1)/2)
        for i in range(mid_point-(coins_count%2)):
            left_sum += coin_sequence[first_coin_index+i]
            # print(mid_point+i,coins_count)
            right_sum += coin_sequence[first_coin_index+mid_point+i]
        # print(first_coin_index,right_sum,coins_count,mid_point)
        if right_sum==left_sum:
            fake_coin=mid_coin
            # print(first_coin_index,right_sum,coins_count,mid_point)
            break
        else:
            coins_count=int(coins_count/2)
            if right_sum>left_sum:
                first_coin_index+=mid_point
            fake_coin=first_coin_index
    if fake_coin!=None:
        fake_coin+=1 # for abstraction from index
    return fake_coin

def partition(arr,low,high):
    i = ( low-1 )
    pivot = arr[high]
    swap_count=0
    for j in range(low , high):

        if   arr[j] < pivot:

            i = i+1
            arr[i],arr[j] = arr[j],arr[i]
            swap_count+=1


    arr[i+1],arr[high] = arr[high],arr[i+1]
    swap_count+=1
    return ( i+1 ),swap_count

def quickSort(arr,low,high):
    total_swap_count=0
    if low < high:
        pi,swap_count = partition(arr,low,high)
        total_swap_count+=swap_count
        total_swap_count+=quickSort(arr, low, pi-1)
        total_swap_count+=quickSort(arr, pi+1, high)
    return total_swap_count

def insertionSort(arr):
    swap_count=0
    for i in range(1, len(arr)):
        key = arr[i]
        j = i-1
        while j >= 0 and key < arr[j] :
                swap_count+=1
                arr[j + 1] = arr[j]
                j -= 1
        arr[j + 1] = key
    return swap_count

def question_four(arr, l, r, k):
    if (k > 0 and k <= r - l + 1):
        pos,junk = partition(arr, l, r)
        if (pos - l == k - 1):
            return arr[pos]
        if (pos - l > k - 1):
            return question_four(arr, l, pos - 1, k)
        return question_four(arr, pos + 1, r, k - pos + l - 1)
    return sys.maxsize

def multiplyList(myList):
    result = 1
    for x in myList:
         result = result * x
    return result

def question_five(arr,current_arr,current_index):
    if sum(current_arr)>=(min(arr)+max(arr))*len(arr)/4:
        return multiplyList(current_arr),current_arr
    elif len(arr)==current_index:
        return sys.maxsize,current_arr
    local_best=sys.maxsize
    local_best_array=[]
    for i in range(current_index,len(arr)):
        temp_current=current_arr.copy()
        temp_current.append(arr[i])
        temp_value, temp_array=question_five(arr, temp_current, i+1)
        if temp_value<local_best:
            local_best_array=temp_array
            local_best=temp_value
    return local_best,local_best_array

def main():
    # # Q1 Driver:
    # box_sequence=[]
    # box_count=100
    # for i in range(box_count):
    #     if i<box_count/2:
    #         box_sequence.append("B")
    #     else:
    #         box_sequence.append("W")
    # print(box_sequence)
    # box_sequence=question_one(box_sequence)
    # print(box_sequence)

    # # Q2 Driver
    # coins_count=40
    # coins_sequence = [1]*coins_count
    # random_fake=random.randint(0,40)
    # coins_sequence[random_fake]=2
    # fake_coin=question_two(coins_sequence)
    # print("Fake coin should be "+str(random_fake+1)+". coin and the algorithm found : "+str(fake_coin))

    # # Q3 Driver
    # quicksort_avg_swap=0
    # insertionsort_avg_swap=0
    # fold_count=20
    # for i in range(fold_count):
    #     arr_1=[]
    #     arr_2=[]
    #     item_count=1018
    #     for i in range(item_count):
    #         temp_rand=random.randint(0,1000)
    #         arr_1.append(temp_rand)
    #         arr_2.append(temp_rand)
    #     # print(arr_1)
    #     total_swap_count=quickSort(arr_1,0,item_count-1) #Thanks Mohit Kumra for this implementation
    #     quicksort_avg_swap+=total_swap_count
    #     print("Number of swaps done by quicksort : "+str(total_swap_count))
    #     #print(arr_1)
    #     total_swap_count=insertionSort(arr_2) #Thanks Mohit Kumra for this implementation
    #     insertionsort_avg_swap+=total_swap_count
    #     print("Number of swaps done by insertionsort : "+str(total_swap_count))
    #     #print(arr_2)
    # quicksort_avg_swap/=fold_count
    # insertionsort_avg_swap/=fold_count
    # print("Average QSort swap count: ",quicksort_avg_swap,", average ISort swap count: ",insertionsort_avg_swap)

    # #Q4 Driver
    # arr=[]
    # item_count=11
    # for i in range(item_count):
    #     temp_rand=random.randint(0,1000)
    #     arr.append(temp_rand)
    # if item_count%2==0:
    #     median_index=item_count/2
    # else:
    #     median_index=(item_count+1)/2
    # median=question_four(arr,0,item_count-1,median_index)
    # print(arr)
    # print("Median is ",median)

    # Q5 Driver
    arr=[2, 4, 7, 5, 22, 11]
    optimal_value, optimal_array=question_five(arr,[],0)
    print("The optimal sub-array is :",optimal_array,"that satisfy the rule with optimality score ",optimal_value)
if __name__ == '__main__':
    sys.exit(main())


