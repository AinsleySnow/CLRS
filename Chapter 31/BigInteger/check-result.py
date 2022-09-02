from os import system

def test_addition(times) -> bool:
    e = int('1' + '0' * 4096, 16)

    with open('add') as result:
        for i in range(times):
            a = int(result.readline(), 16)
            b = int(result.readline(), 16)
            c = int(result.readline(), 16)
            d = (a + b) % e
            if d != c:
                print('An a + b doesn\'t equal c. Check add.log for detailed information.')
                with open('add.log', 'w') as log:
                    log.writelines(('A = %X\n' % a, 
                                    'B = %X\n' % b, 
                                    'C = %X\n' % c,
                                    'C should be %X\n' % d))
                return False
    
    return True

def test_subtraction(times) -> bool:
    e = int('1' + '0' * 4096, 16)

    with open('sub') as result:
        for i in range(times):
            a = int(result.readline(), 16)
            b = int(result.readline(), 16)
            c = int(result.readline(), 16)
            d = (a - b) % e
            if d != c:
                print('An a - b doesn\'t equal c. Check sub.log for detailed information.')
                with open('sub.log', 'w') as log:
                    log.writelines(('A = %X\n' % a, 
                                    'B = %X\n' % b, 
                                    'C = %X\n' % c,
                                    'C should be %X\n' % d))
                return False
    
    return True


def test_multiply(times) -> bool:
    e = int('1' + '0' * 4096, 16)

    with open('mul') as result:
        for i in range(times):
            a = int(result.readline(), 16)
            b = int(result.readline(), 16)
            c = int(result.readline(), 16)
            d = (a * b) % e
            if d != c:
                print('An a * b doesn\'t equal c. Check mul.log for detailed information.')
                with open('mul.log', 'w') as log:
                    log.writelines(('A = %X\n' % a, 
                                    'B = %X\n' % b, 
                                    'C = %X\n' % c,
                                    'C should be %X\n' % d))
                return False
    
    return True


func_list = [ test_addition, test_subtraction, test_multiply ]


if __name__ == '__main__':
    system('.\\' + 'bigint-test.exe')

    for func in func_list:
        if not func(10000):
            break
    else:
        print('All tests passed.')
        system('del add')
        system('del sub')
        system('del mul')
