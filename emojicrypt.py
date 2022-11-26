alpha_1="abcdefghijklmnopqrstuvwxyz'!?à "
alpha_2=["🐒", "🦍", "🐶", "🐺", "🦊", "🦟", "🦝", "🐱", "🦁", "🐯", "🐴", "🦄", "🦌", "🦬", "🐮", "🐖", "🐐", "🐪", "🦒", "🐘", "🦏", "🦣", "🐀", "🦦", "🐼", "🦫", "🐇", "🦆", "🐋", "🐬", "🦭"]

def test_alpha():
	if len(alpha_1) != len(alpha_2):
		raise Exception("Longueurs des deux alphabets différentes ! (%d != %d)" % (len(alpha_1), len(alpha_2)))
	for char in alpha_1:
		if alpha_1.count(char) > 1:
			raise Exception("DUPPLICATE %s" % char)
	for char in alpha_2:
		if alpha_2.count(char) > 1:
			raise Exception("DUPPLICATE %s" % char)

test_alpha() # stops importation if errors found


def encrypt(msg, a, b):
	enc_msg = []
	i = 0

	for m in msg.lower():
		try:
			c = (a * alpha_1.index(m) + (b + i)) % len(alpha_1)
			enc_msg.append(alpha_2[c])
			# i += 1
		except:
			print("caractère \"" + m + "\" non trouvé !")

	return "".join(enc_msg)


def decrypt(msg, a, b):
	clear_msg = []
	i = 0
	a_1 = 0

	for a_1 in range(len(alpha_1)):
		if (a_1 * a) % len(alpha_1) == 1:
			break

	for c in msg:
		m = a_1 * (alpha_2.index(c) - (b + i)) % len(alpha_1)
		clear_msg.append(alpha_1[m])
		# i += 1

	return "".join(clear_msg)