alpha_1="abcdefghijklmnopqrstuvwxyz'!? "
alpha_2=["🐒", "🦍", "🐶", "🐺", "🦊", "🦟", "🦝", "🐱", "🦁", "🐯", "🐴", "🦄", "🦌", "🦬", "🐮", "🐖", "🐐", "🐪", "🦒", "🐘", "🦏", "🦣", "🐀", "🦦", "🐼", "🦫", "🐇", "🦆", "🐋", "🐬", "🦭"]

def encrypt(msg, a, b):
	enc_msg = []
	i = 0

	for m in msg.lower():
		try:
			c = (a * alpha_1.index(m) + (b + i)) % len(alpha_1)
			enc_msg.append(alpha_2[c])
			i += 1
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
		i += 1

	return "".join(clear_msg)

a = 11
b = 4

enc_msg = encrypt(input("message : "), a, b)

print("message encrypté : " + enc_msg)

clear_msg = decrypt(enc_msg, a, b)

print("message decryptée : " + clear_msg)