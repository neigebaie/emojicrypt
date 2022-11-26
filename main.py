import emojicrypt as ec

a = int(input("a = "))
b = int(input("b = "))

enc_msg = ec.encrypt(input("message : "), a, b)

print("message encrypté : " + enc_msg)

clear_msg = ec.decrypt(enc_msg, a + 1, b)

print("message decryptée : " + clear_msg)