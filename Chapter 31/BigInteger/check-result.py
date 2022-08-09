from os import system

if __name__ == '__main__':
    system('.\\bigint-test.exe')
    e = int('1' + '0' * 4096, 16)

    with open('output') as result:
        while True:
            try:
                a = int(result.readline(), 16)
                b = int(result.readline(), 16)
                c = int(result.readline(), 16)
                d = (a + b) % e
                if d != c:
                    print('An a + b doesn\'t equal c. Check check.log for detailed information.')
                    with open('check.log', 'w') as log:
                        log.writelines(('A = %X\n' % a, 
                                        'B = %X\n' % b, 
                                        'C = %X\n' % c,
                                        'C should be %X\n' % d))
                    break
            except ValueError:
                break
    
    print('All tests passed.')
    system('del output')
