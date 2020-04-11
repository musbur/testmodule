from spam import Spam, make_spam

print("---------\nFrom Python")
s1 = Spam()
del s1

print("---------\nFrom C")
s2 = make_spam()
del s2
print("---------")
