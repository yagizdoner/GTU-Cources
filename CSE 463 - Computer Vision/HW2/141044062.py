# Yağız Döner - 141044062 - HW2

import numpy as np
import cv2 as cv
from matplotlib import pyplot as plt


def hw2_141044062(image1, image2, name):
	
    if image1 is None or image2 is None:
        print('Images Could not Open !!!')
        exit(0)
    im1 = cv.imread(image1)
    im2 = cv.imread(image2)
    gray1 = cv.cvtColor(im1,cv.COLOR_BGR2GRAY)
    gray2 = cv.cvtColor(im2,cv.COLOR_BGR2GRAY)
    
    #First Step
    # ORB point detector and descriptor
    orb = cv.ORB_create()
    key1, desc1 = orb.detectAndCompute(gray1,None)
    print("Descriptors of First Image : \n" , desc1)
    key2, desc2 = orb.detectAndCompute(gray2,None)
    print("Descriptors of Second Image : \n" , desc2)   
    
    #Print ORB Result
    img1 = cv.drawKeypoints(gray1, key1, None, color=(0,255,0), flags=0)
    cv.imshow("First Image ORB Result",img1)
    img2 = cv.drawKeypoints(gray2, key2, None, color=(0,255,0), flags=0)
    cv.imshow("Second Image ORB Result",img2)
    
    #Second Step
    #BFMatcher object
    bf = cv.BFMatcher(cv.NORM_HAMMING, crossCheck = True)
    matches = bf.match(desc1,desc2)
    print("There are ",len(desc1)," points before BFMatcher")
    print("There are ",len(matches)," matching points after BFMatcher")
    matches = sorted(matches, key = lambda x:x.distance)
    img3 = cv.drawMatches(gray1,key1,gray2,key2,matches,None,flags=cv.DrawMatchesFlags_NOT_DRAW_SINGLE_POINTS)
    cv.imshow("BF_Matcher Result",img3)
    
    #Third Step
    #Block Based Matcher
    stereo = cv.StereoBM_create(numDisparities=0, blockSize=25)
    disparity = stereo.compute(gray1,gray2)
    plt.imshow(disparity,'gray'),plt.show()
	
    
    
def main():
	print("Results of Barn1")
	hw2_141044062('images/barn11.ppm', 'images/barn12.ppm',"Barn1.jpg")
	print("Results of Barn2 : ")
	hw2_141044062('images/barn21.ppm', 'images/barn22.ppm',"Barn2.jpg")
	print("Results of Bull : ")
	hw2_141044062('images/bull1.ppm', 'images/bull2.ppm',"Bull.jpg")
	print("Results of Poster : ")
	hw2_141044062('images/poster1.ppm', 'images/poster2.ppm',"Poster.jpg")
	print("Results of Sawtooth : ")
	hw2_141044062('images/sawtooth1.ppm', 'images/sawtooth2.ppm',"Sawtooth.jpg")
	print("Results of Venus : ")
	hw2_141044062('images/venus1.ppm', 'images/venus2.ppm',"Venus.jpg")
	

if __name__ == "__main__":
    main()