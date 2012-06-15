i=3
while i<10000:
	j=2
	sign=True
	while j*j<i:
		if i%j==0:
			sign=False
			break
		j=j+1
	if sign:
		print i
	i=i+1
print "END"
