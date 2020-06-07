###########################
#                         #
# YAĞIZ DÖNER - 141044062 #
# CSE 321 - HW_4          #
#                         #
###########################

def part1b(arr):
    for i in range(len(arr)-1):
        for j in range(len(arr[i])-1):
            if( arr[i][j] + arr[i+1][j+1] > arr[i][j+1] + arr[i+1][j] ):
                print("Changing Row ", i , "Column ", j+2)
                arr[i][j+1] = arr[i][j] + arr[i+1][j+1] - arr[i+1][j] + 1 
    return arr

def part1c(arr):
    def findMin(row):
        if len(row) == 1:
            return row[0]
        if len(row) == 2:
            if row[0] > row[1]:
                return row[1]
            else: # <=  to be leftmost
                return row[0]
        midd = len(row) // 2
        left = findMin(row[:midd])
        right = findMin(row[midd:])
        
        return min(left,right)
        
    list = []
    
    def part1_helper(arra):
        if len(arra) == 1:
            list.append(findMin(arra[0]))    
            return 
        list.append(findMin(arra[0]))
        part1_helper(arra[1:])
                     
    part1_helper(arr)
    return list

def part2 (A,B,kth):
	if(len(A) < 1):
		return B[kth]
	if(len(B) < 1):
		return A[kth]
	m1 = len(A) // 2
	m2 = len(B) // 2
	if(m1 + m2 < kth):
		if(A[m1] > B[m2]):
			return part2(A,B[m2+1:],kth-m2-1)
		else:
			return part2(A[m1+1:],B,kth-m1-1)
	else:
		if(A[m1] > B[m2]):
			return part2(A[:m1],B,kth)
		else:
			return part2(A,B[:m2],kth)
        
def part3(arr):
    def combine(arr, left, right):
        lSum = sum(arr[left[0]:left[1] + 1])
        rSum = sum(arr[right[0]:right[1] + 1])
        if (right[0] - left[1]) == 1:
            lrSum = lSum + rSum
            if rSum < lrSum and lSum < lrSum:
                return (left[0], right[1])
        else:
            midSum = sum(arr[left[0]:right[1] + 1])
            if rSum < midSum and lSum < midSum:
                return (left[0], right[1])

        if lSum < rSum:
            return right
        else:
            return left
        
    def part3_helper(arr, l, h):
        if l == h:  
            return (l, h)
        mid = (l + h) // 2
        left = part3_helper(arr, l, mid)
        right = part3_helper(arr, mid + 1, h)
        return combine(arr, left, right)
    
    low, high = part3_helper(arr, 0, len(arr) - 1)
    return arr[low:high + 1]

def part4(V,E):
    #-1 is not Visited.
    #1 is white
    #0 is black
    color = [-1]* len(V)
    def part4_helper(V,E,color):
        if len(V) == 0:
            return True
        if color[V[0]-1] == -1:
            color[V[0]-1] == 0
            for i in E[0]:
                color[i-1] = 1
        elif color[V[0]-1] == 1:
            for i in E[0]:
                if color[i-1] == 1:
                    return False
                elif color[i-1] == -1:
                    color[i-1] = 0
        elif color[V[0]-1] == 0:
            for i in E[0]:
                if color[i-1] == 0:
                    return False
                elif color[i-1] == -1:
                    color[i-1] = 1
        
        return part4_helper(V[1:],E[1:],color)
     
    return part4_helper(V,E,color)

def part5(arr1,arr2):
    def part5_helper(C,P):
        #lengths of C and P are equal.
        if len(C) == 1:
            return (P[0] - C[0],C[0])
        if len(C) == 2:
            if (P[0] - C[0] >= P[1] - C[1]):
                return (P[0] - C[0],C[0])
            else:
                return (P[1] - C[1],C[1])
            
        mid = len(C) // 2
        left_part = part5_helper(C[:mid],P[:mid])
        right_part = part5_helper(C[mid:],P[mid:])
        
        if(left_part[0] > right_part[0]):
            return (left_part[0],left_part[1])
        else:
            return (right_part[0],right_part[1])
            
    res = part5_helper (arr1[:len(arr1)-1],arr2[1:])
    if res[0] > 0:
        return (arr1.index(res[1])+1,res[0])
    else:
        return (-1,-1)
    
def main():
    print("\nYağız Döner - 141044062 ")

    print ("\n------------ Examples of PART 1 BBBB ------------")
    ex1b = [[6,4,3,4,10],[10,7,5,8,6],[15,8,2,4,1],[20,12,5,6,2]]
    print("Before the Execution", ex1b)
    print("After the Execution Part 1-b", part1b(ex1b))

    #----------------------------------------------------

    print ("\n------------ Examples of PART 1 CCCC ------------")
    ex1c = [[10,17,13,28,23],[17,22,16,29,23],[24,28,22,34,24],[11,13,6,17,7],[45,44,32,37,23],[36,33,19,21,6],[75,66,51,53,34]]
    print("Minumum elements of ",ex1c, " is : ", part1c(ex1c))
    ex1c = [[6,2,3,3,10],[10,11,5,8,6],[15,8,2,4,1],[7,12,9,12,15]]
    print("Minumum elements of ",ex1c, " is : ", part1c(ex1c))

    #----------------------------------------------------

    print ("\n------------ Examples of PART 2 ------------")
    A= [3,5,7,9,10,11,20,30,33] 
    B= [1,2,4,6,22,46]
    k=15
    print("Result is = ",part2(A,B,k-1))
    A= [3,5,7,9,10,11,20,30,33] 
    B= [1,2,4,6,22,46]
    k=14
    print("Result is = ",part2(A,B,k-1))
    A= [3,5,7,9,10,11,20,30,33] 
    B= [1,2,4,6,22,46]
    k=11
    print("Result is = ",part2(A,B,k-1))
    A= [3,5,7,9,10,11,20,30,33] 
    B= [1,2,4,6,22,46]
    k=3
    print("Result is = ",part2(A,B,k-1))

    #----------------------------------------------------

    print ("\n------------ Examples of PART 3 ------------")
    ex1 = [5, -6, 6, 7, -6, 7, -4, 3]
    e1=part3(ex1)
    print("For [5, -6, 6, 7, -6, 7, -4, 3] -> The largest contiguous subset for largest sum= ",e1,", Sum =",sum(e1))
    ex1 = [3,8,-7,6,5,-10,21,-4,-2,5]
    e1=part3(ex1)
    print("For [3,8,-7,6,5,-10,21,-4,-2,5] -> The largest contiguous subset for largest sum= ",e1,", Sum =",sum(e1))
    ex1 = [3,-3,4,-4,7,6,-13,5,7,-2,4]
    e1=part3(ex1)
    print("For [3,-3,4,-4,7,6,-13,5,7,-2,4] -> The largest contiguous subset for largest sum= ",e1,", Sum =",sum(e1))

    #----------------------------------------------------

    print ("\n------------ Examples of PART 4 ------------")
    v1 = [1,2,3,4,5,6,7,8]
    e1 = [[2,4,5],[1,3,7],[2,4,8],[1,3,6],[1,6,7],[4,5,8],[2,5,8],[3,6,7]]
    print("Vertex: ",v1," Edges : ",e1," Is BiPartite -> ", part4(v1,e1))
    v1 = [1,2,3,4]
    e1 = [[2,3,4],[1,4],[1,4],[1,2,3]]
    print("Vertex: ",v1," Edges : ",e1," Is BiPartite -> ", part4(v1,e1))
    v1 = [1,2,3]
    e1 = [[2],[1,3],[2]]
    print("Vertex: ",v1," Edges : ",e1," Is BiPartite -> ", part4(v1,e1))
    v1 = [1,2,3,4,5]
    e1 = [[2,3],[1,5],[1,4,5],[3,5],[2,3,4]]
    print("Vertex: ",v1," Edges : ",e1," Is BiPartite -> ", part4(v1,e1))

    #----------------------------------------------------

    print ("\n------------ Examples of PART 5 ------------")
    ar1 = [5,11,2,21,5,7,8,12,13,-1]
    ar2 = [-1,7,9,5,21,7,13,10,14,20]
    print("C = ", ar1 , " and P = ", ar2)
    result = part5(ar1,ar2)
    if ( result[1] > 0 ):
        print("The best day to buy goods is : ", result[0])
        print("Maximum Possible Gain is : ", result[1])
    else:
        print("There is no day to make money!!!")
    ar1 = [5,11,2,21,5,7,-1]
    ar2 = [-1,7,21,13,10,14,10]
    print("C = ", ar1 , " and P = ", ar2)
    result = part5(ar1,ar2)
    if ( result[1] > 0 ):
        print("The best day to buy goods is : ", result[0])
        print("Maximum Possible Gain is : ", result[1])
    else:
        print("There is no day to make money!!!")
    ar1 = [7,9,6,21,7,13,10,14,20,35,-1]
    ar2 = [-1,5,3,2,2,5,4,2,1,3,1]
    print("C = ", ar1 , " and P = ", ar2)
    result = part5(ar1,ar2)
    if ( result[1] > 0 ):
        print("The best day to buy goods is : ", result[0])
        print("Maximum Possible Gain is : ", result[1])
    else:
        print("There is no day to make money!!!")

if __name__ == '__main__':
    main()
