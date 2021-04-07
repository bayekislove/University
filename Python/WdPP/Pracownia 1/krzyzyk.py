def krzyzyk(n):
	m = 3 * n
	for i in range (n):
		print (n*' ' + n * '*')
	for i in range (n):
		print (m * '*')
	for i in range (n):
		print (n*' ' + n* '*')
	
krzyzyk(4)
