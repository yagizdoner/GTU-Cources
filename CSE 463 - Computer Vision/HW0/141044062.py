
# Yağız Döner - 141044062 - HW1

import cv2
import time

# 480 * 640  Images

def hw1_141044062():
	camera = cv2.VideoCapture(0)
	start = time.time()
	for i in range(5):
		return_value, image = camera.read()
		img = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)		
		proImg = process3(img)
		cv2.imwrite(str(i)+'.png', proImg)
		#if(time.time() - start > 1):
		#	break
	print("Total Process Time : " + str(time.time()-start))
	del(camera)

def process3(img):
	darkest = 6375 # 255 * 25
	di = 0
	dj = 0
	brightest = 0  # -> 6375
	bi = 0
	bj = 0
								
	for i in range (60,len(img)-65,3): # 65 = 60 + 5  -> 60 resim dışı için, 5 loop için
		total = 0
		for j in range (0,len(img[i])-5,3):
			if(j==0):
				for ii in range(i,i+5,2):
					for ij in range(j,j+5,2):
						total += img[ii][ij]
			else:
				for ii in range(i,i+5,2):
					total -= img[ii][j-1]
					total += img[ii][j+4]
			if(total <= darkest):
				darkest = total
				di = i + 2
				dj = j + 2
			if(total >= brightest):
				brightest = total
				bi = i + 2
				bj = j + 2
				
	imag = cv2.cvtColor(img, cv2.COLOR_GRAY2RGB)
				
	cv2.circle (imag,(dj,di),5,(0,255,0))   #circle -> önce column sonra row olarak ver!!!
	cv2.circle (imag,(bj,bi),5,(0,0,255))
	
	return imag


def process2(img):
	darkest = 6375 # 255 * 25
	di = 0
	dj = 0
	brightest = 0  # -> 6375
	bi = 0
	bj = 0
	
	total = 0								
	
	for i in range (60,len(img)-65,3): # 65 = 60 + 5  -> 60 resim dışı için, 5 loop için
		for j in range (0,len(img[i])-5,3):
			if(i==60 & j==0):
				for ii in range(i,i+5,2):
					for ij in range(j,j+5,2):
						total += img[ii][ij]
			elif(j==0):
				for ij in range(j,j+5,2):
					total -= img[i-1][ij]
					total += img[i+4][ij]
			else:
				for ii in range(i,i+5,2):
					total -= img[ii][j-1]
					total += img[ii][j+4]
			if(total <= darkest):
				darkest = total
				di = i + 2
				dj = j + 2
			if(total >= brightest):
				brightest = total
				bi = i + 2
				bj = j + 2
				
	imag = cv2.cvtColor(img, cv2.COLOR_GRAY2RGB)
				
	cv2.circle (imag,(dj,di),5,(0,255,0))   #circle -> önce column sonra row olarak ver!!!
	cv2.circle (imag,(bj,bi),5,(0,0,255))
	
	return imag



def process1(img):
	darkest = 6375 # 255 * 25
	di = 0
	dj = 0
	brightest = 0  # -> 6375
	bi = 0
	bj = 0
								
	for i in range (60,len(img)-65): # 65 = 60 + 5  -> 60 resim dışı için, 5 loop için
		for j in range (0,len(img[i])-5):
			total = 0
			for ii in range(i,i+5):
				for ij in range(j,j+5):
					total += img[ii][ij]
			if(total <= darkest):
				darkest = total
				di = i + 2
				dj = j + 2
			if(total >= brightest):
				brightest = total
				bi = i + 2
				bj = j + 2
				
	imag = cv2.cvtColor(img, cv2.COLOR_GRAY2RGB)
				
	cv2.circle (imag,(dj,di),5,(0,255,0))   #circle -> önce column sonra row olarak ver!!!
	cv2.circle (imag,(bj,bi),5,(0,0,255))
	
	return imag
	

def main():
	hw1_141044062()


if __name__ == "__main__":
    main()