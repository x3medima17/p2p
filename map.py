import sys

BANNED_PAGES = """Media:
Special:
Talk:
User:
User_talk:
Project:
Project_talk:
File:
File_talk:
MediaWiki:
MediaWiki_talk:
Template:
Template_talk:
Help:
Help_talk:
Category:
Category_talk:
Portal:
Wikipedia:
Wikipedia_talk:""".split("\n")

BANNED_EXT = ".jpg, .gif, .png, .JPG, .GIF, .PNG, .txt, .ico".split(", ")

BANNED_EXACT = """404_error/
Main_Page
Hypertext_Transfer_Protocol
Search""".split("\n")

def validate(line):
	try:
		name, title, number_acc, byte = line.strip().split(" ")
	except ValueError:
		print(line, "---------------")
		return False, "", 0

	# print(name,)
	if not name.startswith("en"):
		return False, title, number_acc
	if len(title) < 1:
		return False, title, number_acc

	for page in BANNED_PAGES:
		if title.startswith(page):
			return False, title, number_acc

	for ext in BANNED_EXT:
		if title.endswith(ext):
			return False, title, number_acc

	for page in BANNED_EXACT:
		if title == page:
			return False, title, number_acc

	if title.isalpha():
		if title[0].islower():
			return False, title, number_acc


	return True, title, number_acc

# print(BANNED_EXACT)
# sys.exit()
for line in sys.stdin:
	res = validate(line)
	if res[0] == True:
		print(res[1]+" "+res[2])
	