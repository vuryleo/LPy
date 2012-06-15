print "---------------calculate 1 1 2 3 5 8--------------------"
N = 20
sum1 = 1
sum2 = 0
cnt = 1
while True:
	cnt = cnt + 1
	temp = 0
	temp = sum1 + sum2
	sum2 = sum1
	sum1 = temp
	if cnt==N:
		break
print "The 20 th Fibonnacci number is:"
print sum1
print "---------------written by Davy---------------------------"
