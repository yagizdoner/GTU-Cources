def h3p1(box_sequence):
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
    
def h3p2(coin_sequence):
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
            right_sum += coin_sequence[first_coin_index+mid_point+i]
        if right_sum==left_sum:
            fake_coin=mid_coin
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
 
def h3p4(arr, l, r, k):
    if (k > 0 and k <= r - l + 1):
        pos,junk = partition(arr, l, r)
        if (pos - l == k - 1):
            return arr[pos]
        if (pos - l > k - 1):
            return h3p4(arr, l, pos - 1, k)
        return h3p4(arr, pos + 1, r, k - pos + l - 1)
    return sys.maxsize
    
def h3p5(A,B,total,upperBound):
    if A[0]+total <= upperBound:
        total += A[0]
        B.append(A[0])
        h3p5(A[1:],B,total,upperBound)
    else:
        if  (len(A) > 1) :
            if (A[1]+total > upperBound) :
                h3p5(A[1:],B,total,upperBound)
            else:
                B.append(A[0])
        else:
            B.append(A[0])
            
def h4p2 (A,B,kth):
	if(len(A) < 1):
		return B[kth]
	if(len(B) < 1):
		return A[kth]
	m1 = len(A) // 2
	m2 = len(B) // 2
	if(m1 + m2 < kth):
		if(A[m1] > B[m2]):
			return h4p2(A,B[m2+1:],kth-m2-1)
		else:
			return h4p2(A[m1+1:],B,kth-m1-1)
	else:
		if(A[m1] > B[m2]):
			return h4p2(A[:m1],B,kth)
		else:
			return h4p2(A,B[:m2],kth)
    

def h4p3(arr):
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
        
    def h4p3_helper(arr, l, h):
        if l == h:  
            return (l, h)
        mid = (l + h) // 2
        left = h4p3_helper(arr, l, mid)
        right = h4p3_helper(arr, mid + 1, h)
        return combine(arr, left, right)
    
    low, high = h4p3_helper(arr, 0, len(arr) - 1)
    return arr[low:high + 1]
    
def h4p4(V,E):
    #-1 is not Visited.
    #1 is white
    #0 is black
    color = [-1]* len(V)
    def h4p4_helper(V,E,color):
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
        
        return h4p4_helper(V[1:],E[1:],color)
     
    return h4p4_helper(V,E,color)
    
def h4p5(arr1,arr2):
    def h4p5_helper(C,P):
        #lengths of C and P are equal.
        if len(C) == 1:
            return (P[0] - C[0],C[0])
        if len(C) == 2:
            if (P[0] - C[0] >= P[1] - C[1]):
                return (P[0] - C[0],C[0])
            else:
                return (P[1] - C[1],C[1])
            
        mid = len(C) // 2
        left_part = h4p5_helper(C[:mid],P[:mid])
        right_part = h4p5_helper(C[mid:],P[mid:])
        
        if(left_part[0] > right_part[0]):
            return (left_part[0],left_part[1])
        else:
            return (right_part[0],right_part[1])
            
    res = h4p5_helper (arr1[:len(arr1)-1],arr2[1:])
    if res[0] > 0:
        return (arr1.index(res[1])+1,res[0])
    else:
        return (-1,-1)