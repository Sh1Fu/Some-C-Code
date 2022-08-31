from itertools import product
for i in range(1, 5, 1):
	for combos in product("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789_", repeat=i):
		S = "".join(combos)
		print(S)
