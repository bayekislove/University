def wieza(n, d):
    if d-8*n<0:
        return ValueError
    for i in range(n+1):
        print(4*(n-i) * " " + (d-8*((n-i)-1)) * "#")
        print(4*(n-i) * " " + "#" +  (d-2-8*((n-i)-1)) * "." + "#")
        print(4*(n-i) * " " + "#" +  (d-2-8*((n-i)-1)) * "." + "#")
        print(4*(n-i) * " " + (d-8*((n-i)-1)) * "#")

wieza(3,24)