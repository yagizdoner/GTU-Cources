###########################
#                         #
# YAĞIZ DÖNER - 141044062 #
# CSE 321 - HW_5          #
#                         #
###########################

def part1(n,M,N,S):
    # For the first case, I append the zero head of the lists.
    N.insert(0,0)
    S.insert(0,0)

    minNY = [0]*len(N) # Cost of ending in NewYork    
    minSF = [0]*len(S) # Cost of ending in SanFrancisco
    
    for i in range(0,n):
        # Append NewYork.
        if minNY[i] < M + minSF[i]:
            minNY[i+1] = N[i+1] + minNY[i]
        else:
            minNY[i+1] = N[i+1] + M + minSF[i]
            
        # Append SanFrancisco.
        if minSF[i] < M + minNY[i]:
            minSF[i+1] = S[i+1] + minSF[i]
        else:
            minSF[i+1] = S[i+1] + M + minNY[i]
    
    # The last index of minNy and minSF has the total cost of this destination.
    # The smaller one of these is the minimum Cost.   
    if minNY[n] < minSF[n]:
        return minNY[n]
    else:
        return minSF[n]


def part2(s , f ):
    # Part2 has the random order starting and finishing times.
    # Helper function has the increasing order finishing time.
    # part2_helper is a greedy algorithm technique.
    def part2_helper(start,finish): 
        activityIndex = [] # Index of Selected activities.
        activity = [] # return values of activities
        activityPair = [] #activity pairs. start-finish times
        # Select the first activity. 
        activityIndex.append(0)
        activityPair.append(start[0])
        activityPair.append(finish[0])
        activity.append(activityPair)

        for i in range(len(start)): 
            # If next activity >= finishing time of the last 
            # attended activity, then select it 
            if start[i] >= finish[ activityIndex[len(activityIndex)-1] ]:
                # activityIndex[len(activityIndex)-1] has the finishing time of the
                # last attended activity.
                activityPair = []
                activityPair.append(start[i])
                activityPair.append(finish[i])
                activity.append(activityPair) 
                activityIndex.append(i)
        return activity


    # creating activity pairs {{start-finish},{...},...}
    pairs = []
    for i in range (len(s)):
        pair = []
        pair.append(f[i])
        pair.append(s[i])
        pair.append(i)
        pairs.append(pair)

    pairs.sort(key= lambda x: x[0]) # sorted in increasing order (in finish time)

    s=[]
    f=[]
    for i in pairs:
        s.append(i[1])
        f.append(i[0])
    # sorted pairs are used in part2_helper.
    return part2_helper(s,f)



def main():
    print("\nYağız Döner - 141044062 ")

    print ("\n------------ Examples of PART 1 ------------")
    N = [1,3,20,30]
    S = [50,20,2,4]
    print("N = [1,3,20,30] , S = [50,20,2,4] , M = 10. Min Cost is : " ,part1(4,10,N,S))

    N = [50,9,120,10]
    S = [50,20,8,4]
    print("N = [50,9,120,10] , S = [50,20,8,4] , M = 20. Min Cost is : " ,part1(4,20,N,S))

    N = [1,15,3,30,7,30]
    S = [5,3,20,4,20,6]
    print("N = [1,15,3,30,7,30] , S = [5,3,20,4,20,6] , M = 15. Min Cost is : " ,part1(6,15,N,S))

    #----------------------------------------------------

    print ("\n------------ Examples of PART 2 ------------")
    start = [1,12,1,7,2,3,3,7,10,1,10,2] 
    finish = [8,13,5,12,4,5,8,9,13,3,11,8] 
    print("Starting Times : " , start)
    print("Finishing Times : " , finish)
    print("Selected activities are : ", part2(start,finish))
    start = [2,1,1,7,11] 
    finish = [4,6,3,9,13] 
    print("Starting Times : " , start)
    print("Finishing Times : " , finish)
    print("Selected activities are : ", part2(start,finish))
    start = [1,1,3,5,6,6,8,8,10,11] 
    finish = [5,3,5,6,11,8,13,10,13,13] 
    print("Starting Times : " , start)
    print("Finishing Times : " , finish)
    print("Selected activities are : ", part2(start,finish))

    #----------------------------------------------------

    print ("\n------------ Examples of PART 3 ------------")
    
    #----------------------------------------------------

    print ("\n------------ Examples of PART 4 ------------")

    #----------------------------------------------------

    print ("\n------------ Examples of PART 5 ------------")    
    
    
if __name__ == "__main__":
    main()
