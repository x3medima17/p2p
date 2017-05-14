import sys


KEY = None
VAL = 0
results = []

for line in sys.stdin:
	# print(line)
	try:
		key, val = line.strip().split(" ")
	except:
		print(line)
		continue
		
	if KEY == None:
		KEY = key

	if key != KEY:
		results.append((KEY, VAL))
		# print("{} {}".format(KEY, VAL))
		VAL = 0
		KEY = key
	VAL += int(val)

if VAL != 0:
	results.append((KEY, VAL))
	# print("{} {}".format(KEY, VAL))

results = sorted(results, key=lambda x: x[1])

for key, val in results:
	print("{} {}".format(key, val))

sys.exit()
while True:
	try:
		line = sys.stdin.readline()
		print(line)
	except EOFError:
		break