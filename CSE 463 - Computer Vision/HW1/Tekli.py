import sys
import math
import cv2
import numpy as np
from collections import defaultdict
import matplotlib.pyplot as plt


def main():        
    model = cv2.imread('soccer fieild.jpg')      
    height = model.shape[0]
    width = model.shape[1]
    modelNp = np.array([[0,0],[0,height],[width,0],[width,height]], dtype = "float32")

    src = cv2.imread('4.jpg', cv2.IMREAD_GRAYSCALE)  # Yüklenen Resim
    img, testNp  = houghOperation(src)
    res = perspectiveOperation(src,testNp,modelNp,model)
    
    cv2.namedWindow("Perspective", cv2.WINDOW_NORMAL)
    cv2.imshow("Perspective", res)
    
    cv2.waitKey()
    cv2.destroyAllWindows()
    return 0
    
def perspectiveOperation(src, testN, modelN,modelImg):
    matris = cv2.getPerspectiveTransform(testN,modelN)
    pers = cv2.warpPerspective(src, matris,(modelImg.shape[1],modelImg.shape[0]))
    return pers
    
def houghOperation(src):    
    dst = cv2.Canny(src, 50, 200, None, 3)
    
    cdst = cv2.cvtColor(dst, cv2.COLOR_GRAY2BGR)
    
    lines = cv2.HoughLines(dst, 1, np.pi / 180, 300, None, 0, 0)
    
    segmented = segment_by_angle_kmeans(lines)
    intersections = segmented_intersections(segmented)
    
    maxX, maxXY, maxY, maxYX = 0,0,0,0
    minX, minXY, minY, minYX = 100000, 100000, 100000, 100000
    
    for i in range(1,len(intersections)):
        x = intersections[i][0][0]
        y = intersections[i][0][1]
        if(x<minX):
            minX, minXY = x,y
        if(x>maxX):
            maxX, maxXY = x,y
        if(y<minY):
            minY, minYX = y,x
        if(y>maxY):
            maxY, maxYX = y,x
        cdst = cv2.circle(cdst, (x,y), 10, (0, 0, 255), 5) 
    
    if(minYX < maxYX):    
        nparr = np.array([[minYX,minY],[minX,minXY],[maxX,maxXY],[maxYX,maxY]], dtype = "float32")
    else:
        nparr = np.array([[minX,minXY],[maxYX,maxY],[minYX,minY],[maxX,maxXY]], dtype = "float32")
    
    return cdst,nparr
    
    
def segment_by_angle_kmeans(lines, k=2, **kwargs):
    default_criteria_type = cv2.TERM_CRITERIA_EPS + cv2.TERM_CRITERIA_MAX_ITER
    criteria = kwargs.get('criteria', (default_criteria_type, 10, 1.0))
    flags = kwargs.get('flags', cv2.KMEANS_RANDOM_CENTERS)
    attempts = kwargs.get('attempts', 10)
    angles = np.array([line[0][1] for line in lines])
    pts = np.array([[np.cos(2*angle), np.sin(2*angle)]
                    for angle in angles], dtype=np.float32)
    labels, centers = cv2.kmeans(pts, k, None, criteria, attempts, flags)[1:]
    labels = labels.reshape(-1)  
    segmented = defaultdict(list)
    for i, line in zip(range(len(lines)), lines):
        segmented[labels[i]].append(line)
    segmented = list(segmented.values())
    return segmented
    
def intersection(line1, line2):
    rho1, theta1 = line1[0]
    rho2, theta2 = line2[0]
    A = np.array([
        [np.cos(theta1), np.sin(theta1)],
        [np.cos(theta2), np.sin(theta2)]
    ])
    b = np.array([[rho1], [rho2]])
    x0, y0 = np.linalg.solve(A, b)
    x0, y0 = int(np.round(x0)), int(np.round(y0))
    return [[x0, y0]]

def segmented_intersections(lines):
    intersections = []
    for i, group in enumerate(lines[:-1]):
        for next_group in lines[i+1:]:
            for line1 in group:
                for line2 in next_group:
                    intersections.append(intersection(line1, line2)) 

    return intersections
    
if __name__ == "__main__":
    main()