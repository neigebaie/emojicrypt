import emojicrypt as ec

def score(msg):
    try:
        with open('fr_dic.txt', 'r') as f:
            wordlist = f.readlines()
            wordlist = [word.strip('\n') for word in wordlist]
        
        score = 0

        for word in msg.split(' '):
            if word in wordlist:
                score += len(word)
        
        return score
    except:
        print('Erreur : Le score n\'a pas pu être établi.')

print('-- Bruteforce Emojicrypt --\n')

enc_msg = input('message encrypté :')
max_a = int(input('max_a = '))
max_b = int(input('max_b = '))

attempts = []

print('\nbruteforcing in progress', end='')
for a in range(max_a):
    for b in range(max_b):
        print('.', end='', flush=True)
        attempt = {'msg': ec.decrypt(enc_msg, a, b), 'a': a, 'b': b}
        attempt['score'] = score(attempt['msg'])
        attempts.append(attempt)

attempts.sort(key=lambda attempt: attempt['score'])

res = attempts[-1:][0]

print('\n')
print('score : %d' % (100 * res['score']/len(res['msg'])))
print('message : %s' % res['msg'])
print('clé : (a = %d; b = %d)' % (res['a'], res['b']))
