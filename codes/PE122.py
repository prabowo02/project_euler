ans = [[[1]]]

for i in range(2, 276):
    ls = []
    for chains in ans:
        for chain in chains:
            if ((i - chain[-1]) in chain):
                if (len(ls) == 0) or (len(ls[-1]) == len(chain) + 1):
                    ls.append(chain[:])
                    ls[-1].append(i)
                elif (len(chain) + 1 < len(ls[-1])):
                    ls = []
                    ls.append(chain[:])
                    ls[-1].append(i)
                      
    ans.append(ls[:])
    
for tc in range(int(input())):
    k = int(input())
    print(len(ans[k-1][-1]) - 1)
        
    for i in range(1, len(ans[k-1][-1])):
        print ("n^{:d} * n^{:d} = n^{:d}".format(ans[k-1][-1][i-1], ans[k-1][-1][i] - ans[k-1][-1][i-1], ans[k-1][-1][i]))
