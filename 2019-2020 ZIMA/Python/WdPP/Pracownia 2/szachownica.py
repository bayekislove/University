def kwadrat1(n, k):
	for i in range(k):
		print(n * (k * " " + k * "#"))
	for i in range(k):
		print(n * (k * "#" + k * " "))


def szachownica(n, k):
	for j in range(n):	
		kwadrat1(n, k)


szachownica(5, 2)
