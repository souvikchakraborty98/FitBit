n=int(input(""))

a = input().split(" ")
a = [int(el) for el in a]
l=a[0]

for i in range(0,n):
    if a[i]%2==0 and a[i]>l:
        l=a[i]
print("Largest even number:"+str(l))
  
    
