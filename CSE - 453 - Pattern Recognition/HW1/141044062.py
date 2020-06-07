
# Yağız DÖNER - 141044062 - Pattern Recognition HW-1

from math import sqrt

def gradient_descent_runner(data, learningRate, numOfIterations):
	def step_gradient(b_current, m_current, data, learningRate):
		b_gradient = 0
		m_gradient = 0
		N = float(len(data))
		for i in range(0, len(data)):
			x = data[i][0]
			y = data[i][1]
			b_gradient += -(2/N) * (y - (m_current * x + b_current))
			m_gradient += -(2/N) * x * (y - (m_current * x + b_current))
		new_b = b_current - (learningRate * b_gradient)
		new_m = m_current - (learningRate * m_gradient) 
		return [new_b,new_m]

	b = 0
	m = 0
	for i in range(numOfIterations):
		b,m = step_gradient(b, m, data, learningRate)
	return [b,m]
	
def takePredictions(testAge,b0,b1):
	predictions = list()
	for i in testAge:
		pre = b0 + b1 * i
		predictions.append(pre)
	return (predictions)
	
def meanSquaredError(blood, predicted):
	mse = 0.0
	for i in range(len(blood)):
		dif = predicted[i] - blood[i]
		mse += (dif * dif)
	return sqrt(mse / len(blood))
	
def main():
	data = [[39,144],[47,220],[45,138],[47,145],[65,162],
			[46,142],[67,170],[42,124],[67,158],[56,154],
			[64,162],[56,150],[59,140],[34,110],[42,128],
			[48,130],[45,135],[17,114],[20,116],[19,124],
			[36,136],[50,142],[39,120],[21,120],[44,160]]
			
	testAge = [53,63,29,25,69]
	testBlood = [158,144,130,125,175]
	
	print("-------------------------------------------")
	b0,b1 = gradient_descent_runner(data, 0.0001, 1000)
	predictedBlood = takePredictions(testAge,b0,b1)
	print("The Learning Rate = 0.0001 and Iteration = 1000") 
	for i in  range (5):
		print("The Age is : " + str(testAge[i]) + "   Blood is : " + str(testBlood[i]) + 
					"  ---  And Prediction is : " + str(predictedBlood[i]) )
	print("Mean Squared Error is : " + str( meanSquaredError(testBlood, predictedBlood)) ) 
	print("-------------------------------------------")
	b0,b1 = gradient_descent_runner(data, 0.000001, 1000)
	predictedBlood = takePredictions(testAge,b0,b1)
	print("The Learning Rate = 0.000001 and Iteration = 1000") 
	for i in  range (5):
		print("The Age is : " + str(testAge[i]) + "   Blood is : " + str(testBlood[i]) + 
					"  ---  And Prediction is : " + str(predictedBlood[i]) )
	print("Mean Squared Error is : " + str( meanSquaredError(testBlood, predictedBlood)) )
	print("-------------------------------------------")
	b0,b1 = gradient_descent_runner(data, 0.00000001, 1000)
	predictedBlood = takePredictions(testAge,b0,b1)
	print("The Learning Rate = 0.00000001 and Iteration = 1000") 
	for i in  range (5):
		print("The Age is : " + str(testAge[i]) + "   Blood is : " + str(testBlood[i]) + 
					"  ---  And Prediction is : " + str(predictedBlood[i]) )
	print("Mean Squared Error is : " + str( meanSquaredError(testBlood, predictedBlood)) )
	print("-------------------------------------------")
	b0,b1 = gradient_descent_runner(data, 0.0001, 10000)
	predictedBlood = takePredictions(testAge,b0,b1)
	print("The Learning Rate = 0.0001 and Iteration = 10000") 
	for i in  range (5):
		print("The Age is : " + str(testAge[i]) + "   Blood is : " + str(testBlood[i]) + 
					"  ---  And Prediction is : " + str(predictedBlood[i]) )
	print("Mean Squared Error is : " + str( meanSquaredError(testBlood, predictedBlood)) )
	
if __name__ == "__main__":
	main()