def koperta(n):
	print((2 * n + 1)* "*")
	for i in range(n-1):
		print("*" + (i) * " " + "*" + (n - i - 2) * " " + " " + (n - i - 2) * " " + "*" + (i) * " " + "*")
	print("*"+ (n-1)* " " + "*" + (n-1)* " " + "*")
	for i in range(n-1):
		print("*" + (n - i - 2) * " " + "*" + (i) * " " + " " + (i) * " " + "*" + (n - i - 2) * " " + "*")
	print((2 * n + 1) * "*")

koperta(5)
