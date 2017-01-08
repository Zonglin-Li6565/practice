def ransom_note(magazine, rasom):
    dictionary = {}
    for m in magazine:
        if m in dictionary:
            dictionary[m] += 1
        else:
            dictionary[m] = 1
    for r in rasom:
        if r in dictionary and dictionary[r] > 0:
            dictionary[r] = dictionary[r] - 1
        else:
            return False
    return True

m, n = map(int, raw_input().strip().split(' '))
magazine = raw_input().strip().split(' ')
ransom = raw_input().strip().split(' ')
answer = ransom_note(magazine, ransom)
if(answer):
    print "Yes"
else:
    print "No"