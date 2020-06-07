###########################
#                         #
# YAĞIZ DÖNER - 141044062 #
# CSE 321 - HW_3          #
#                         #
###########################

def part1(boxes,iteration): # in which Iteration
    if len(boxes) > 1:
        if iteration % 2 == 0 : # even
            boxes[1:len(boxes)-1] = part1(boxes[1:len(boxes)-1],iteration+1)
        elif iteration % 2 == 1 :
            boxes[0],boxes[len(boxes)-1] = boxes[len(boxes)-1],boxes[0] # first and last boxes changed.
            boxes[1:len(boxes)-1] = part1(boxes[1:len(boxes)-1],iteration+1)
    return boxes
  
        
        
def part2(coins,n): # n is starting index
    if len(coins) == 1:
        return(n)
    elif len(coins) == 2:
        if coins[0] < coins[1]:
            return(n)
        else:
            return(n+1)
    else:
        if (len(coins)%2 == 0) : # number of coins is even
            first = coins[0:(len(coins)//2)]
            second = coins[(len(coins)//2):len(coins)]
            if sum(first) < sum(second):
                return part2(first,n+0)
            elif sum(first) > sum(second):
                return part2(second,n+len(coins)//2)
        else: # number of coins is odd.
            first = coins[0:(len(coins)//2)]
            second = coins[(len(coins)//2):len(coins)-1]
            if sum(first) == sum(second) :
                return(len(coins)-1)
            elif sum(first) < sum(second) :
                return part2(first,n+0)
            else:
                return part2(second,n+len(coins)//2)

def part3(lst):
    arr = list(lst)
    def partition(arr,low,high): 
        s = 0
        i = ( low-1 )     
        pivot = arr[high]  
        for j in range(low , high):  
            if   arr[j] <= pivot: 
                i = i+1
                if arr[i]!=arr[j]:
                    s += 1
                arr[i],arr[j] = arr[j],arr[i] 
        if arr[high]!=arr[i+1]:
            s += 1
        arr[i+1],arr[high] = arr[high],arr[i+1]
        return ( i+1,s ) 

    def quickSort(arr,low,high): 
        sw = 0
        if low < high: 
            pi = partition(arr,low,high)
            sw += pi[1]
            sw += quickSort(arr, low, pi[0]-1) 
            sw += quickSort(arr, pi[0]+1, high) 
        return sw

    def insertionSort(arr):
        swa=0
        for i in range(1, len(arr)): 
            key = arr[i] 
            j = i-1
            while j >=0 and key < arr[j] : 
                    arr[j+1] = arr[j] 
                    swa += 1
                    j -= 1
            arr[j+1] = key 
        return swa
            
    swapQuick = quickSort(arr,0,len(arr)-1)
    swapInsertion= insertionSort(lst)
                
    return swapQuick,swapInsertion
  
def part4(unList):
	def median_of_medians(unList, i):
		sublists = []
		medians = []
		for j in range (0, len(unList) ,5):
			sublists.append(unList[j:j+5])
		for sublist in sublists:
			medians.append(sorted(sublist)[len(sublist)//2])
			
		if len(medians) <= 5:
		    pivot = sorted(medians)[len(medians)//2]
		else:
		    pivot = median_of_medians(medians, len(medians)//2)

		low = []
		high = []
		for j in unList:
			if j<pivot:
				low.append(j)
			elif j>pivot:
				high.append(j)
				
		if i < len(low):
		    return median_of_medians(low,i)
		elif i > len(low):
		    return median_of_medians(high,i-len(low)-1)
		else: #pivot = len(low)
		    return pivot
	
	if(len(unList) % 2 == 0):
		return (float(median_of_medians(unList,len(unList)//2) + median_of_medians(unList,(len(unList)//2)-1)) / 2)
	else:
		return (median_of_medians(unList,len(unList)//2))

def part5(A,B,total,upperBound):
    if A[0]+total <= upperBound:
        total += A[0]
        B.append(A[0])
        part5(A[1:],B,total,upperBound)
    else:
        if  (len(A) > 1) :
            if (A[1]+total > upperBound) :
                part5(A[1:],B,total,upperBound)
            else:
                B.append(A[0])
        else:
            B.append(A[0])
    
def main():
    print("\nYağız Döner - 141044062 ")
    print ("\n------------ Examples of PART 1 ------------")
    # 0 is black boxes and 1 is white boxes
    ex1 = [0,1]
    ex2 = [0,0,1,1]
    ex3 = [0,0,0,1,1,1]
    ex4 = [0,0,0,0,1,1,1,1]
    ex5 = [0,0,0,0,0,1,1,1,1,1]
    ex6 = [0,0,0,0,0,0,1,1,1,1,1,1]
    print("Before The Execution : [0,1] --> After The Execution : ", part1(ex1,0))
    print("Before The Execution : [0,0,1,1] --> After The Execution : ", part1(ex2,0))
    print("Before The Execution : [0,0,0,1,1,1] --> After The Execution : ", part1(ex3,0))
    print("Before The Execution : [0,0,0,0,1,1,1,1] --> After The Execution : ", part1(ex4,0))
    print("Before The Execution : [0,0,0,0,0,1,1,1,1,1] --> After The Execution : ", part1(ex5,0))
    print("Before The Execution : [0,0,0,0,0,0,1,1,1,1,1,1] --> After The Execution : ", part1(ex6,0))
    print ("\n------------ Examples of PART 2 ------------")
    ex1 = [1,1,1,1,0,1,1,1]
    ex2 = [1,0,1,1,1,1]
    ex3 = [1,0,1,1,1,1,1]
    ex4 = [1,1,1,1,0,1,1,1,1]
    ex5 = [1,1,1,1,1,1,1,1,0]
    ex6 = [1,1,1,1,1,1,0,1,1,1,1]
    print("If The Input is ", ex1, ". The Fake Coin is index of ", part2(ex1,0))
    print("If The Input is ", ex2, ". The Fake Coin is index of ", part2(ex2,0))
    print("If The Input is ", ex3, ". The Fake Coin is index of ", part2(ex3,0))
    print("If The Input is ", ex4, ". The Fake Coin is index of ", part2(ex4,0))
    print("If The Input is ", ex5, ". The Fake Coin is index of ", part2(ex5,0))
    print("If The Input is ", ex6, ". The Fake Coin is index of ", part2(ex6,0))
    print ("\n------------ Examples of PART 3 ------------")
    ex1 = [21,54,32,98,11,2] 
    r1=part3(ex1)
    print("If The Input is ", "[21,54,32,98,11,2]", ". Number of Swap in QuickSort : ",r1[0]," Number of Swap in InsertionSort : ",r1[1])
    ex2 = [11,10,9,8,7,6,5,4,3,2] 
    r2=part3(ex2)
    print("If The Input is ", "[11,10,9,8,7,6,5,4,3,2]", ". Number of Swap in QuickSort : ",r2[0]," Number of Swap in InsertionSort : ",r2[1])
    ex3 = [2,8,7,4,1,5,9] 
    r3=part3(ex3)
    print("If The Input is ", "[2,8,7,4,1,5,9]", ". Number of Swap in QuickSort : ",r3[0]," Number of Swap in InsertionSort : ",r3[1])
    ex4 = [5,6,7,8,9,10] 
    r4=part3(ex4)
    print("If The Input is ", "[5,6,7,8,9,10]", ". Number of Swap in QuickSort : ",r4[0]," Number of Swap in InsertionSort : ",r4[1])
    ex5 = [5,6,7,2] 
    r5=part3(ex5)
    print("If The Input is ", "[5,6,7,2]", ". Number of Swap in QuickSort : ",r5[0]," Number of Swap in InsertionSort : ",r5[1])
    ex6 = [5,44,22,38,47,56,98,42,25,68,74,21,58,54,66,63,32,69,65,95,94,96] 
    r6=part3(ex6)
    print("If The Input is ", "[5,44,22,38,47,56,98,42,25,68,74,21,58,54,66,63,32,69,65,95,94,96]", ". Number of Swap in QuickSort : ",r6[0]," Number of Swap in InsertionSort : ",r6[1])
    #----------------------------------------------------
    print ("\n------------ Examples of PART 4 ------------")
    ex1 = [3,2,4,1,5,8,9,6,7]
    ex2 = [3,7,4,6,1,2,5,8,9]
    ex3 = [3,2,4,1,5,8,6,7]
    ex4 = [1,2]
    ex5 = [11,21,25,66,87,2,5,7,77]
    ex6 = [9]
    print("The Median of ", ex1 ," is: ", part4(ex1))
    print("The Median of ", ex2 ," is: ", part4(ex2))
    print("The Median of ", ex3 ," is: ", part4(ex3))
    print("The Median of ", ex4 ," is: ", part4(ex4))
    print("The Median of ", ex5 ," is: ", part4(ex5))
    print("The Median of ", ex6 ," is: ", part4(ex6))
    #----------------------------------------------------
    print ("\n------------ Examples of PART 5 ------------")
    ex1 = [2, 4, 7, 5, 22, 11]
    ex2 = [53,42,17,66,82,20,30,44,16]
    ex3 = [5,6,11,21,10,8,4,1]
    ex4 = [25,6,8,44,27,30,38]
    b1 = []
    b2 = []
    b3 = []
    b4 = []
    part5(sorted(ex1,reverse= True),b1,0,(max(ex1)+min(ex1))*len(ex1)/4)
    part5(sorted(ex2,reverse= True),b2,0,(max(ex2)+min(ex2))*len(ex2)/4)
    part5(sorted(ex3,reverse= True),b3,0,(max(ex3)+min(ex3))*len(ex3)/4)
    part5(sorted(ex4,reverse= True),b4,0,(max(ex4)+min(ex4))*len(ex4)/4)
    print("If The Input is ", ex1, ". The optimal sub-array is ", b1)
    print("If The Input is ", ex2, ". The optimal sub-array is ", b2)
    print("If The Input is ", ex3, ". The optimal sub-array is ", b3)
    print("If The Input is ", ex4, ". The optimal sub-array is ", b4)


if __name__ == '__main__':
    main()
